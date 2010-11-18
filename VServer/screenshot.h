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


#ifndef SCREENSHOT_H
#define SCREENSHOT_H
#include <QObject>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>
#include <QImage>
#include <QTimer>


class ScreenShot:public QObject{
    Q_OBJECT

public:
    ScreenShot(QWidget *parent=0);
    ~ScreenShot();

    QImage getImage();
    QImage getResizedImage(int width, int height,bool grayscale);
    void takeScreenShot();

private:
    QPixmap originalPixmap;
    QTimer *timer;
    void toGrayScale();

public slots:
    void updateCaption();
    void shotLoop(qint16 interval);
    void stop();

signals:
    void screenCaptured();

};

#endif // SCREENSHOT_H
