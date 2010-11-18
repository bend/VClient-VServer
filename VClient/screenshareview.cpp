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

#include "screenshareview.h"


ScreenShareView::ScreenShareView(QWidget *parent) :QDialog(parent){
    setupUi();
}

void ScreenShareView::showImage(QImage image){
    show();
    drawer->show();
    if(image.size().height()>400)
        setFixedSize(image.size());
    else setFixedSize(image.size().width(),400);
    imageLabel->setFixedSize(image.size());
    imageLabel->setPixmap(QPixmap::fromImage(image));
}

void ScreenShareView::setupUi(){
    setFixedSize(640,480);
    imageLabel = new QLabel(this);
    imageLabel->setFixedSize(this->size());
    this->setWindowIconText("Screen Sharing");
    drawer = new QDialog(this,Qt::Drawer);
    QVBoxLayout* layout = new QVBoxLayout(drawer);
    stopScreenShareButton = new QPushButton("Stop Screen Sharing");

    QLCDNumber *lcd = new QLCDNumber();
    QLCDNumber *lcdTime = new QLCDNumber();
    sliderSize = new QSlider(Qt::Horizontal);
    sliderTime = new QSlider(Qt::Horizontal);
    grayscalCheckBox = new QCheckBox("GrayScale");
    QLabel *sliderLabel = new QLabel("Screen Size (%)");
    QLabel *sliderTimeLabel = new QLabel("Update Delay (ms)");
    sliderSize->setRange(10,100);
    sliderTime->setRange(50,3000);
    lcd->display(20);
    sliderSize->setValue(20);

    drawer->setFixedWidth(200);
    layout->addWidget(stopScreenShareButton);
    layout->addWidget(grayscalCheckBox);
    layout->addWidget(sliderLabel);
    layout->addWidget(lcd);
    layout->addWidget(sliderSize);
    layout->addWidget(sliderTimeLabel);
    layout->addWidget(lcdTime);
    layout->addWidget(sliderTime);
    this->raise();
    connect(sliderSize,SIGNAL(valueChanged(int)),lcd,SLOT(display(int)));
    connect(sliderTime,SIGNAL(valueChanged(int)),lcdTime,SLOT(display(int)));

}

