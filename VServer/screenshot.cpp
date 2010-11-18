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

#include "screenshot.h"
/*
    Constructor of the ScreenShot class
 */
ScreenShot::ScreenShot(QWidget *parent):QObject(parent){

}
/*
       Destructor
*/
ScreenShot::~ScreenShot(){

}


/*
     return the Qimage
*/
QImage ScreenShot::getImage(){
    return originalPixmap.toImage();
}

/*
     return the resized QImage
*/
QImage ScreenShot::getResizedImage(int width, int height,bool grayscale){
    if(grayscale)
        toGrayScale();
    return originalPixmap.toImage().scaled(width,height, Qt::IgnoreAspectRatio,Qt::FastTransformation);
}

/*
 takes a screenshot and store the pixmap in original pixmap
 */
void ScreenShot::takeScreenShot(){
    originalPixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
}

void ScreenShot::toGrayScale(){
    QImage image = originalPixmap.toImage();
    QRgb col;
    int gray;
    for (int i = 0; i < originalPixmap.width(); ++i)
    {
        for (int j = 0; j < originalPixmap.height(); ++j)
        {
            col = image.pixel(i, j);
            gray = qGray(col);
            image.setPixel(i, j, qRgb(gray, gray, gray));
        }
    }
    originalPixmap = originalPixmap.fromImage(image);
	
}


void ScreenShot::updateCaption(){
    takeScreenShot();
    emit screenCaptured();
}

void ScreenShot::shotLoop(qint16 interval){
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateCaption()));
    timer->setInterval(interval);
    timer->setSingleShot(false);
    timer->start();
}

void ScreenShot::stop(){
    timer->stop();
}
