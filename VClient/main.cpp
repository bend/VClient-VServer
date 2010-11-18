/*
*   Copyright © Benoit Daccache
*   ben.daccache@gmail.com
*
*   This file is part of VClient/VServer.
*
*   Foobar is free software: you can redistribute it and/or modify
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

#include <QtGui/QApplication>
#include "vclientwindow.h"
#include "screenshareview.h"
#include "vclientview.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //VClientWindow w;
    //w.show();
    VClientView *view = new VClientView;
    view->show();
    return a.exec();
}
