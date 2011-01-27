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

#ifndef CONNECTEDCLIENT_H
#define CONNECTEDCLIENT_H
#include <QObject>
#include <QtNetwork>
#include <QImage>
#include <QTimer>
#include <QDataStream>
#include "screenshot.h"
#include "commandexecuter.h"


class ConnectedClient : public QObject{
    Q_OBJECT

public:
    ConnectedClient(QTcpSocket *socket, qint32 id);

private:
    /*----------------------------- methods ---------------------------------------*/
    void writeTypeOfData(qint16 type);
    void writeString(QString str);
    void writeInt8(qint8 i);
    QString receiveString();
    void captureAndSendImage();
    void captureAndSendLoop(int interval);
    void updateScreenSize(qint8 ration);
    void updateDelay(qint16 ms);
    void setGrayScaleStatus(qint8 val);
    void executeCommand(QString command);
    qint16 readType();
    qint8 readInt8();
    qint16 readInt16();

    /*----------------------------- variables ---------------------------------------*/
    ScreenShot *shot;
    QTcpSocket *clientSocket;
    qint32 id;
    qint32  packetsize;
    qint16  type;
    QString data;
    qint16 height;
    qint16 width;
    qint16 refreshInterval;
    bool grayscale;
    bool screenShare;

signals:
    void takeScreenShot();

public slots:
    void receiveData();
    void sendImage();
};

#endif // CONNECTEDCLIENT_H
