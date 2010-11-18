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

#include "vclientview.h"

VClientView::VClientView(QWidget *parent) : QMainWindow(parent){
    setupUI();
    addConnections();
    screenShareview = new ScreenShareView(this);
}

void VClientView::setupUI(){
    this->setAttribute(Qt::WA_MacMetalStyle);
    QWidget *central = new QWidget();
    this->setCentralWidget(central);
    QGridLayout *grid = new QGridLayout();
    QVBoxLayout *drawerGrid = new QVBoxLayout();
    connectButton = new QPushButton("Connect to Server");
    hostField = new QLineEdit();
    spinBox = new QSpinBox();
    spinBox->setRange(0,65536);
    console = new QPlainTextEdit();
    console->setReadOnly(true);
    QLabel *portLabel = new QLabel("Port");
    QLabel *hostLabel = new QLabel("host");
    drawer = new QWidget(this,Qt::Drawer);
    drawer->setAttribute(Qt::WA_MacMetalStyle);
    drawer->setLayout(drawerGrid);
    drawer->setVisible(false);
    showHideDrawerButton = new QPushButton("show Drawer");
    startScreenSaverButton = new QPushButton("Start ScreenShare");
    drawer->setFixedWidth(150);
    inputConsole = new QLineEdit();


    grid->addWidget(hostLabel,0,0);
    grid->addWidget(hostField,0,1);
    grid->addWidget(portLabel,0,2);
    grid->addWidget(spinBox,0,3);
    grid->addWidget(console,1,0,2,4);
    grid->addWidget(inputConsole,3,0,1,2);
    grid->addWidget(connectButton,4,3);
    grid->addWidget(showHideDrawerButton,4,0);
    central->setLayout(grid);

    drawerGrid->addWidget(startScreenSaverButton);

}

void VClientView::addConnections(){
    connect(showHideDrawerButton,SIGNAL(clicked()),this,SLOT(showHideDrawer()));
    connect(connectButton,SIGNAL(clicked()),this,SLOT(connectToServer()));
}

void VClientView::showHideDrawer(){
    if(!drawer->isVisible()){
        showHideDrawerButton->setText("Hide Drawer");
        drawer->setVisible(true);
    }else{
        showHideDrawerButton->setText("Show Drawer");
        drawer->setVisible(false);
    }
}

void VClientView::connectToServer(){
    connectButton->setEnabled(false);
    client= new Client(hostField->text(),spinBox->value(),this);
    connect(client,SIGNAL(connected()),this,SLOT(setConnected()));
    connect(client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));

    client->connectToServer();
    connect(client, SIGNAL(showData()),this,SLOT(showData()));
    connect(client,SIGNAL(showImage(QImage)),screenShareview,SLOT(showImage(QImage)));
    connect(inputConsole,SIGNAL(returnPressed()),this,SLOT(commandtyped()));

    connect(startScreenSaverButton,SIGNAL(clicked()),client,SLOT(startScreenShare()));
    connect(screenShareview->getStopScreenShareButton(),SIGNAL(clicked()),this,SLOT(stopScreenShare()));
    connect(screenShareview->getSizeSlider(),SIGNAL(sliderReleased()),this,SLOT(sendScreenSize()));
    connect(screenShareview->getTimeSlider(),SIGNAL(sliderReleased()),this,SLOT(sendDelayTime()));
    connect(screenShareview->getGrayScaleBox(),SIGNAL(toggled(bool)),client,SLOT(sendGrayScale(bool)));


}

void VClientView::setConnected(){
    console->appendHtml("<em>You are now connected to the server.</em>");
}

void VClientView::setDisconnected(){
    console->appendPlainText("<em>Disconnected from server.</em>");
    client->close();
    connectButton->setEnabled(true);
}

void VClientView::showData(){
    console->appendPlainText(client->getData());
}


void VClientView::socketError(QAbstractSocket::SocketError error){
    switch(error){
        case QAbstractSocket::HostNotFoundError:
            console->appendHtml(tr("<em>ERROR : Server not found, check IP and PORT.</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            console->appendHtml(tr("<em>ERROR : Server refused the connection.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            console->appendHtml(tr("<em>ERROR : Server closed the connection.</em>"));
            screenShareview->setVisible(false);
            this->connectButton->setEnabled(true);
            break;
        default:
            console->appendHtml(tr("<em>Error : ") + client->errorString() + tr("</em>"));
    }
    connectButton->setEnabled(true);
}

void VClientView::commandtyped(){
    QString s = inputConsole->text().trimmed();
    client->sendCommand(s);
    inputConsole->setText("");
}

void VClientView::stopScreenShare(){
    client->stopScreenShare();
    screenShareview->getStopScreenShareButton()->setText("Start Screen Share");
    disconnect(screenShareview->getStopScreenShareButton(),SIGNAL(clicked()),this,SLOT(stopScreenShare()));
    connect(screenShareview->getStopScreenShareButton(),SIGNAL(clicked()),this,SLOT(startScreenShare()));
}

void VClientView::startScreenShare(){
    client->startScreenShare();
    screenShareview->getStopScreenShareButton()->setText("Stop Screen Share");
    disconnect(screenShareview->getStopScreenShareButton(),SIGNAL(clicked()),this,SLOT(startScreenShare()));
    connect(screenShareview->getStopScreenShareButton(),SIGNAL(clicked()),this,SLOT(stopScreenShare()));
}

void VClientView::sendScreenSize(){
    client->sendScreenSize(screenShareview->getSizeSlider()->value());
}

void VClientView::sendDelayTime(){
    client->sendDelayTime(screenShareview->getTimeSlider()->value());
}
