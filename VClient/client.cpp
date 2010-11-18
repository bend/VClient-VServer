/*
*   Copyright © Benoit Daccache
*   ben.daccache@gmail.com
*
*   This file is part of VClient/VServer.
*
*   VClient/VServer is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   VClient/VServer is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with VClient/VServer.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "client.h"
#include <QMessageBox>
#include <QApplication>

Client::Client(QString host, qint16 port,QObject *parent):QTcpSocket(parent){
        this->host = host;
        this->port = port;
        type=-1;
        packetsize = 0;
}

Client::~Client(){
    if(this!=NULL)
        this->close();
}

void Client::connectToServer(){
    this->connectToHost(host, port);
    connect(this, SIGNAL(readyRead()), this, SLOT(receiveData()));
}

void Client::receiveData(){
       if(type == -1)
           type = readType();
       switch(type){
       case Constants::STRING:
           receiveString();
           break;
       case Constants::IMAGE:
           receiveImage();
           break;
       };
}

qint16 Client::readType(){
    if(this->bytesAvailable()<sizeof(qint8))
        return -1;
    QDataStream in(this);
    qint16 type;
    in>>type;
    return type;
}

void Client::receiveString(){
    QDataStream in(this);
    qint16 size;
    if(packetsize==0){
        in>>size;
        packetsize=size;
    }if(this->bytesAvailable()<packetsize)
        return;
    in>>data;
    type=-1;
    packetsize=0;
    emit showData();
    if(this->bytesAvailable()>0)
        receiveData();
}

void Client::receiveImage(){
    QDataStream in(this);
    if(packetsize==0)
        in>>packetsize;
    if(this->bytesAvailable()<packetsize)
        return;
    in>>image;
    packetsize=0;
    type=-1;
    emit showImage(image);
    if(this->bytesAvailable()>0)
        receiveData();
}

void Client::writeTypeOfData(qint16 type){
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    out<<type;
    this->write(paquet);
    this->flush();
}


void Client::writeString(QString str){
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out << str; // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (paquet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message
    this->write(paquet);
    this->flush();
}

void Client::writeInt8(qint8 i ){
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    out << i ;// On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    this->write(paquet);
}

void Client::writeInt16(qint16 i ){
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    out << i ;// On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    this->write(paquet);
}


void Client::stopScreenShare(){
    writeTypeOfData(Constants::STOPSCREENSHARE);
}

void Client::startScreenShare(){
    writeTypeOfData(Constants::STARTSCREENSHARE);
}

void Client::sendScreenSize(int val){
    writeTypeOfData(Constants::SCREENSIZE);
    writeInt8((qint8)val);
}

void Client::sendDelayTime(int val){
    writeTypeOfData(Constants::UPDATEDELAY);
    writeInt16((qint16)val);
}

void Client::sendGrayScale(bool b){
    if(b){
        writeTypeOfData(Constants::GRAYSCALESTATUS);
        writeInt8((qint8)Constants::GRAYSCALEON);
    }else{
        writeTypeOfData(Constants::GRAYSCALESTATUS);
        writeInt8((qint8)Constants::GRAYSCALEOFF);
    }
}

void Client::sendCommand(QString command){
    qDebug()<<"command"<<command;
    writeTypeOfData(Constants::COMMANDEXEC);
    writeString(command);
}


