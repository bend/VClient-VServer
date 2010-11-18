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

#include "vclientwindow.h"
#include "ui_vclientwindow.h"
#include <QMessageBox>
VClientWindow::VClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VClientWindow){
    ui->setupUi(this);
    this->setFixedSize(this->size());
    screenShareview = new ScreenShareView(this);
}

VClientWindow::~VClientWindow(){
    delete ui;
}

void VClientWindow::on_connectButton_clicked(){
    ui->connectButton->setEnabled(false);
    client= new Client(ui->hostTextField->text(),ui->portSpin->value(),this);
    connect(client,SIGNAL(connected()),this,SLOT(setConnected()));
    connect(client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));

    client->connectToServer();
    connect(client, SIGNAL(showData()),this,SLOT(showData()));
    connect(client,SIGNAL(showImage(QImage)),screenShareview,SLOT(showImage(QImage)));
    connect(ui->inputTextField,SIGNAL(textChanged()),this,SLOT(commandtyped()));

    connect(ui->actionScreen_Sharing,SIGNAL(triggered()),client,SLOT(startScreenShare()));
    connect(screenShareview->getStopScreenShareButton(),SIGNAL(clicked()),this,SLOT(stopScreenShare()));
    connect(screenShareview->getSizeSlider(),SIGNAL(sliderReleased()),this,SLOT(sendScreenSize()));
    connect(screenShareview->getTimeSlider(),SIGNAL(sliderReleased()),this,SLOT(sendDelayTime()));
    connect(screenShareview->getGrayScaleBox(),SIGNAL(toggled(bool)),client,SLOT(sendGrayScale(bool)));


}

void VClientWindow::setConnected(){
    ui->console->appendHtml("<em>You are now connected to the server.</em>");
}

void VClientWindow::setDisconnected(){
    ui->console->appendPlainText("<em>Disconnected from server.</em>");
    client->close();
    ui->connectButton->setEnabled(true);
}

void VClientWindow::showData(){
    ui->console->appendPlainText(client->getData());
}


void VClientWindow::socketError(QAbstractSocket::SocketError error){
    switch(error){
        case QAbstractSocket::HostNotFoundError:
            ui->console->appendHtml(tr("<em>ERROR : Server not found, check IP and PORT.</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            ui->console->appendHtml(tr("<em>ERROR : Server refused the connection.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            ui->console->appendHtml(tr("<em>ERROR : Server closed the connection.</em>"));
            break;
        default:
            ui->console->appendHtml(tr("<em>Error : ") + client->errorString() + tr("</em>"));
    }
    ui->connectButton->setEnabled(true);
}

void VClientWindow::commandtyped(){
    QString s = ui->inputTextField->toPlainText();
    if(s.size()>0){
        if(s.at(s.size()-1)=='\n'){
            s=s.trimmed();
            s=s.mid(s.lastIndexOf('\n')+1);
            client->sendCommand(s);
        }
    }

}

void VClientWindow::stopScreenShare(){
    client->stopScreenShare();
    screenShareview->getStopScreenShareButton()->setText("Start Screen Share");
    disconnect(screenShareview->getStopScreenShareButton(),SIGNAL(clicked()),this,SLOT(stopScreenShare()));
    connect(screenShareview->getStopScreenShareButton(),SIGNAL(clicked()),this,SLOT(startScreenShare()));
}

void VClientWindow::startScreenShare(){
    client->startScreenShare();
    screenShareview->getStopScreenShareButton()->setText("Stop Screen Share");
    disconnect(screenShareview->getStopScreenShareButton(),SIGNAL(clicked()),this,SLOT(startScreenShare()));
    connect(screenShareview->getStopScreenShareButton(),SIGNAL(clicked()),this,SLOT(stopScreenShare()));
}

void VClientWindow::sendScreenSize(){
    client->sendScreenSize(screenShareview->getSizeSlider()->value());
}

void VClientWindow::sendDelayTime(){
    client->sendDelayTime(screenShareview->getTimeSlider()->value());
}
