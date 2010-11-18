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

#ifndef VSERVERVIEW_H
#define VSERVERVIEW_H
#include <QMainWindow>
#include <QObject>
#include <QSpinBox>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include "server.h"

class VServerView:public QMainWindow{
    Q_OBJECT
public:
    VServerView();
    ~VServerView();
private:
    void setupUi();
    void addConnections();
    void addServerConnections();

    QSpinBox *spinBox;
    QPlainTextEdit *console;
    QPushButton *launchButton;
    QPushButton *closeButton;
    Server *server;

public slots:
    void launchServer();
    void setConnected();
    void connectedClient();
    void disconnectedClient();
};

#endif // VSERVERVIEW_H
