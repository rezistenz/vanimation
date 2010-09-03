#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QtGui>

class ClipWidget:public QWidget{
public:
    ClipWidget(QWidget *parent);
private:
    int frameWidth;
    int frameHeight;

    int countFrames;

    void paintEvent ( QPaintEvent * event );
    void drawFrames(QPainter &painter);
};

class TimelineWidget : public QWidget
{    
public:
    TimelineWidget(QWidget *parent);
private:
    void createView();
    QScrollArea* scrollArea;
};

#endif // TIMELINEWIDGET_H
