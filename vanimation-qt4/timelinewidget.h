#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QtGui>
#include <vector>
#include "../core/defines.h"

using namespace std;

class ClipWidget:public QWidget{
     //Q_OBJECT
public:
    ClipWidget(QWidget *parent);
	void setCountFrames(int countFrames);
	void clearFrameTimes();
	void addFrameTimes(TIME_TYPE timeFrame);
	void setMaxTime(TIME_TYPE time);
private:
    int frameWidth;
    int frameHeight;

    int countFrames;
    vector< TIME_TYPE > frameTimes;
    TIME_TYPE maxTime;
    void paintEvent ( QPaintEvent * event );
    void drawFrames(QPainter &painter);
};

class TimelineWidget : public QWidget
{    
public:
    TimelineWidget(QWidget *parent);
    int getCountClip();
    void adjustSizeClips();
    void addClip();
    void delClip();
    void setClipCountFrames(int indexClip,int countFrames);
    void clearClipFameTimes(int indexClip);
    void addClipFrameTime(int indexClip,TIME_TYPE timeFrame);
    void setMaxTimeClip(int indexClip,TIME_TYPE time);
private:
    QVector<ClipWidget*> clips;
    QScrollArea* scrollArea;
    void createView();
};

#endif // TIMELINEWIDGET_H
