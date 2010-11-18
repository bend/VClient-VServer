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

#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
#include <QtNetwork>
#include "Constants.h"
#include <QImage>

class Client:public QTcpSocket{
    Q_OBJECT
public:
    Client(QString host, qint16 port,QObject *parent=0);
    ~Client();
    void   connectToServer();
    inline QString  getData()   {return data;}
    inline QImage   getImage()  {return image;}


private:
    qint16  readType();
    void    receiveString();
    void    receiveImage();

    void    writeTypeOfData(qint16 type);
    void    writeString(QString str);
    void    writeInt8(qint8 i);
    void    writeInt16(qint16 i);

    qint16  port;
    qint32  packetsize;
    qint16  type;
    QString host;
    QString data;
    QImage  image;

public slots:
    void receiveData();
    void stopScreenShare();
    void startScreenShare();
    void sendScreenSize(int);
    void sendDelayTime(int);
    void sendGrayScale(bool b);
    void sendCommand(QString command);

signals:
    void showData();
    void showImage(QImage);


};

#endif // CLIENT_H
