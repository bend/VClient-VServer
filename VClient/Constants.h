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

#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <QObject>

class Constants {
public:
    static const qint16 STRING              = 1;
    static const qint16 IMAGE               = 2;
    static const qint16 STARTSCREENSHARE    = 3;
    static const qint16 STOPSCREENSHARE     = 4;
    static const qint16 SCREENSIZE          = 5;
    static const qint16 UPDATEDELAY         = 6;
    static const qint16 GRAYSCALESTATUS     = 7;
    static const qint16 GRAYSCALEON         = 8;
    static const qint16 GRAYSCALEOFF        = 9;
    static const qint16 COMMANDEXEC         =10;
};
#endif // CONSTANTS_H
