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

#ifndef VCLIENTWINDOW_H
#define VCLIENTWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "screenshareview.h"

namespace Ui {
    class VClientWindow;
}

class VClientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VClientWindow(QWidget *parent = 0);
    ~VClientWindow();

private:
    Ui::VClientWindow *ui;
    Client *client;
    ScreenShareView *screenShareview;

private slots:
    void on_connectButton_clicked();
    void setConnected();
    void setDisconnected();
    void showData();
    void socketError(QAbstractSocket::SocketError erreur);
    void commandtyped();
    void startScreenShare();
    void stopScreenShare();
    void sendScreenSize();
    void sendDelayTime();

};

#endif // VCLIENTWINDOW_H
