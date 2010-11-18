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

#ifndef HEADER_FENSERVEUR
#define HEADER_FENSERVEUR
#define PATH_TO_FILE "log.txt"

#include <QtNetwork>
#include <QObject>
#include "errorlogger.h"
#include "error.h"
#include "connectedclient.h"



class Server:public QTcpServer{
    Q_OBJECT

public:
    Server(qint16 port ,QObject *parent = 0);
    void   start();/*start server on port*/
    inline qint8 getStatus(){return serverStatus;}
    inline QTcpSocket* getLastClient(){return lastClient;}/*returns last connected client*/

private:
    /*----------------------------- methods ---------------------------------------*/
    void logError(QString error);

    /*----------------------------- variables ---------------------------------------*/
    ErrorLogger *logger;
    QTcpSocket *lastClient;
    QList<ConnectedClient *> clients;

    qint32 id;
    qint16 port;
    qint8 serverStatus;

public slots:
    void newConnection();//called when a new client is connected
    void disconnectClient();//called when a client has benn disconnected

signals:
    void connectedClient();
    void disconnectedClient();//emitted when a client is disconnected
    void startScreenShare();
    void serverLaunched();//emitted when server launched
};

#endif

