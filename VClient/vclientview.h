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

#ifndef VCLIENTVIEW_H
#define VCLIENTVIEW_H
#include <QPushButton>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QSpinBox>
#include <QLayout>
#include <QWidget>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenuItem>
#include <QAction>
#include "client.h"
#include "screenshareview.h"


class VClientView : public QMainWindow{
    Q_OBJECT
public:
    explicit VClientView(QWidget *parent = 0);

private:

    void setupUI();
    void addConnections();
    QPushButton *connectButton;
    QSpinBox *spinBox;
    QLineEdit *hostField;
    QPlainTextEdit *console;
    QLineEdit *inputConsole;
    QWidget *drawer;
    QPushButton *showHideDrawerButton;
    QPushButton *startScreenSaverButton;

    Client *client;
    ScreenShareView *screenShareview;


signals:

private slots:
    void showHideDrawer();
    void connectToServer();
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

#endif // VCLIENTVIEW_H
