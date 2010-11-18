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

#ifndef SCREENSHAREVIEW_H
#define SCREENSHAREVIEW_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QLCDNumber>
#include <QSlider>
#include <QCheckBox>

class ScreenShareView : public QDialog{
    Q_OBJECT
public:
    explicit ScreenShareView(QWidget *parent = 0);
    inline QPushButton* getStopScreenShareButton(){return stopScreenShareButton;}
    inline QSlider* getSizeSlider(){return sliderSize;}
    inline QSlider* getTimeSlider(){return sliderTime;}
    inline QCheckBox* getGrayScaleBox(){return grayscalCheckBox;}



private:
    QLabel *imageLabel;
    QPushButton *stopScreenShareButton;
    QWidget *drawer;
    QSlider *sliderSize;
    QSlider *sliderTime;
    QCheckBox *grayscalCheckBox;

    void setupUi();


signals:

public slots:
    void showImage(QImage image);
};

#endif // SCREENSHAREVIEW_H
