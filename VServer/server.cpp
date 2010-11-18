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

#include "server.h"
#include <QMessageBox>
Server::Server(qint16 port,QObject *parent): QTcpServer(parent){
    this->port= port;
    logger = new ErrorLogger(PATH_TO_FILE);
    id = 0;
}

void Server:: start(){
    if(this->listen(QHostAddress::Any, port)){
        connect(this, SIGNAL(newConnection()), this, SLOT(newConnection()));
        logError("server launched");
        serverStatus = 1;
    }else{
        logError("Unable to launch server on port");
        serverStatus = -1;
    }emit serverLaunched();
}

void Server::logError(QString error){
    Error e(error);
    e.log(this->logger);
}

void Server:: newConnection(){
    QTcpSocket *newClient = this->nextPendingConnection();
    ConnectedClient *conClient;
    conClient = new ConnectedClient(newClient, id);
    clients.append(conClient);
    lastClient = newClient;
    id++;
    connect(newClient,SIGNAL(disconnected()),this,SLOT(disconnectClient()));
    emit connectedClient();
}

void Server:: disconnectClient(){
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (socket == 0) //On a pas trouvé l'emmeteur;
        return;
    socket->close();
    socket->deleteLater();
    emit disconnectedClient();
}



