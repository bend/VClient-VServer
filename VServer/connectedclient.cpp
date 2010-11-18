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

#include "connectedclient.h"
#include "Constants.h"

ConnectedClient::ConnectedClient( QTcpSocket *socket, qint32 id):QObject(){
    this->clientSocket=socket;
    this->id=id;
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(receiveData()));
    packetsize=0;
    type=-1;
    shot = new ScreenShot;
    width = 640 ;
    height = 480;
    refreshInterval = 500;
    grayscale = false;
    screenShare = false;
}

void ConnectedClient::writeTypeOfData(qint16 type){
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    out<<type;
    clientSocket->write(paquet);
}

void ConnectedClient::writeString(QString str){
    QByteArray paquet;
    writeTypeOfData(Constants::STRING);
    QDataStream out(&paquet, QIODevice::WriteOnly);
    out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out << str; // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (paquet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message
    clientSocket->write(paquet);
    clientSocket->flush();
}

void ConnectedClient::writeInt8(qint8 i ){
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    out << i ;// On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    clientSocket->write(paquet);
}

QString ConnectedClient::receiveString(){
	QDataStream in(clientSocket);
    qint16 size;
    if(packetsize==0){
        in>>size;
        packetsize=size;
    }if(clientSocket->bytesAvailable()<packetsize)
        return NULL;
    data = "";
    in>>data;
    type=Constants::NOTYPE;
    packetsize=0;
    if(clientSocket->bytesAvailable()>0)
        receiveData();
    return data;
}

void ConnectedClient::captureAndSendImage(){
    writeTypeOfData(Constants::IMAGE);
    shot = new ScreenShot();
    shot->takeScreenShot();
    QImage img = shot->getResizedImage(width,height,grayscale);
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);
    out<<(qint32)0;
    out<<img;
    out.device()->seek(0);
    out<<(qint32)(packet.size() - sizeof(qint32));
    clientSocket->write(packet);
    clientSocket->flush();
}

void ConnectedClient::captureAndSendLoop(int interval){
    screenShare = true;
    shot->shotLoop(interval);
    connect(shot,SIGNAL(screenCaptured()),this,SLOT(sendImage()));
    connect(clientSocket,SIGNAL(disconnected()),shot,SLOT(stop()));
}

void ConnectedClient::updateScreenSize(qint8 ratio){
    QRect screenSize = QApplication::desktop()->screenGeometry();
    qreal r = (ratio/100.0);
    width = screenSize.width() * r;
    height= screenSize.height()* r;
}

void ConnectedClient::updateDelay(qint16 ms){
    refreshInterval = ms;
    if(screenShare){
        shot->stop();
        shot->shotLoop(refreshInterval);
    }
}

void ConnectedClient::setGrayScaleStatus(qint8 val){
    if(val==Constants::GRAYSCALEON)
        grayscale = true;
    else grayscale = false;
}

void ConnectedClient::executeCommand(QString command){
    size_t size = command.toStdString().size() + 1;
    char * buffer = new char[ size ];
    strncpy( buffer, command.toStdString().c_str(), size );
    system(buffer);
    delete buffer;
}


qint16 ConnectedClient::readType(){
    if(clientSocket->bytesAvailable()<sizeof(qint8))
        return -1;
    QDataStream in(clientSocket);
    qint16 type;
    in>>type;
    return type;
}

qint8 ConnectedClient::readInt8(){
    if(clientSocket->bytesAvailable()<sizeof(qint8))
        return -1;
    QDataStream in(clientSocket);
    qint8 size;
    in>>size;
    return size;
}

qint16 ConnectedClient::readInt16(){
    if(clientSocket->bytesAvailable()<sizeof(qint16)){
        return -1;
    }
    QDataStream in(clientSocket);
    qint16 delay;
    in>>delay;
    return delay;
}

void ConnectedClient::receiveData(){
       if(type == -1)
           type = readType();
       switch(type){
           case Constants::STRING:
               receiveString();
               type = Constants::NOTYPE;
               break;
           case Constants::SCREENSHARE:
               captureAndSendLoop(refreshInterval);
               type = Constants::NOTYPE;
               break;
           case Constants::STOPSCREENSHARE:
               shot->stop();
               type = Constants::NOTYPE;
               screenShare = false;
               break;
           case Constants::SCREENSIZE:{
               qint8 size = readInt8();
               if(size==-1)
                   break;
               updateScreenSize(size);
               type = Constants::NOTYPE;
               break;
           }case Constants::UPDATEDELAY:{
               qint16 delay = readInt16();
               if(delay==-1)
                   break;
               updateDelay(delay);
               type = Constants::NOTYPE;
               break;
           }case Constants::GRAYSCALESTATUS:{
               qint8 grayScaleStatus = readInt8();
               if(grayScaleStatus==-1)
                   break;
               setGrayScaleStatus(grayScaleStatus);
               type = Constants::NOTYPE;
               break;
           }case Constants::COMMANDEXEC:{
               if(receiveString()==NULL)
                   break;
               executeCommand(data);
               type =Constants::NOTYPE;
               break;
           }
       };
       if(clientSocket->bytesAvailable()>0)
           receiveData();
}

void ConnectedClient::sendImage(){
    writeTypeOfData(Constants::IMAGE);
    QImage img = shot->getResizedImage(width,height,grayscale);
    QByteArray packet;
    QDataStream out(&packet, QIODevice::WriteOnly);
    out<<(qint32)0;
    out<<img;
    out.device()->seek(0);
    out<<(qint32)(packet.size() - sizeof(qint32));
    clientSocket->write(packet);
    clientSocket->flush();
}

