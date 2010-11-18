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

#include "vserverview.h"

VServerView::VServerView():QMainWindow(){
    setupUi();
    addConnections();
}

VServerView::~VServerView(){

}

void VServerView::setupUi(){
    this->setAttribute(Qt::WA_MacMetalStyle);
    this->setFixedSize(350,200);
    QGridLayout *grid = new QGridLayout();
    QLabel *portLabel = new QLabel("Port");
    QWidget *centerWidget = new QWidget();
    this->setCentralWidget(centerWidget);
    spinBox = new QSpinBox();
    spinBox->setRange(0,65536);
    launchButton= new QPushButton("Launch Server");
    closeButton = new QPushButton("Exit");
    console = new QPlainTextEdit();
    console->setReadOnly(true);
    spinBox->setValue(2000);
    grid->addWidget(portLabel,0,0);
    grid->addWidget(spinBox,0,1);
    grid->addWidget(console,1,0,2,2);
    grid->addWidget(closeButton,3,0);
    grid->addWidget(launchButton,3,1);
    centerWidget->setLayout(grid);
    this->raise();
}

void VServerView::addConnections(){
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(launchButton,SIGNAL(clicked()),this,SLOT(launchServer()));
}

void VServerView::launchServer(){
    server = new Server(spinBox->value());
    addServerConnections();
    server->start();
}

void VServerView::addServerConnections(){
    connect(server, SIGNAL(serverLaunched()), this,SLOT(setConnected()));
    connect(server, SIGNAL(connectedClient()), this,SLOT(connectedClient()));
    connect(server, SIGNAL(disconnectedClient()), this,SLOT(disconnectedClient()));
}

void VServerView::setConnected(){
    if(server->getStatus()>0){
        launchButton->setEnabled(false);
        console->appendHtml("<B><font color=\"blue\">Server Launched</font></B>");
        console->appendHtml("<Em>IP: "+server->serverAddress().toString()+" Port :"+QString::number(server->serverPort())+"</Em>");
    }else console->appendHtml("<B><font color=\"red\">Unable to lauch server</font></B>");
}

void VServerView::connectedClient(){
    console->appendHtml("<I><font color=\"green\">Connected client\nIP: "+server->getLastClient()->localAddress().toString()+"</font></I>");
}

void VServerView::disconnectedClient(){
    console->appendHtml("<I><font color=\"orange\">Disconnected client\n</font></I>");
}


