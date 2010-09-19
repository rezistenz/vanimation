#ifndef TIMELINEWIDGET_H
#define TIMELINEWIDGET_H

#include <QtGui>
#include <vector>
#include "../core/defines.h"

using namespace std;

/*
================================================================

ClipWidget

================================================================
*/

class ClipWidget:public QWidget{

    Q_OBJECT

public:
    ClipWidget(QWidget *parent);
	void setCountFrames(int countFrames);
	void clearFrameTimes();
	void addFrameTimes(TIME_TYPE timeFrame);
	void setMaxTime(TIME_TYPE time);
	void setIndex(int newIndex);
	int getIndex();
private:
    int index;
    int currentClip;
    int currentFrame;

    int frameWidth;
    int frameHeight;

    int countFrames;
    vector< TIME_TYPE > frameTimes;
    TIME_TYPE maxTime;
    void paintEvent ( QPaintEvent * event );
    void drawFrames(QPainter &painter);

    void mouseReleaseEvent(QMouseEvent *event);
signals:
     void currentClipChanged(int newCurrentClip);
     void currentFrameChanged(int newCurrentFrame);
public slots:
    void changeCurrentClip(int newCurrentClip);
    void changeCurrentFrame(int newCurrentFrame);
};


/*
================================================================

ClipPanelWidget

================================================================
*/


class ClipsPanelWidget : public QWidget{
    Q_OBJECT
public:
     ClipsPanelWidget(QWidget *parent);
private:
    int frameWidth;
    int frameHeight;
    int currentFrame;
    int currentClip;
    void paintEvent ( QPaintEvent * event );
public slots:
    void changeCurrentClip(int newCurrentClip);
    void changeCurrentFrame(int newCurrentFrame);
};

/*
================================================================

TimelineWidget

================================================================
*/

class TimelineWidget : public QWidget{

    Q_OBJECT

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
    QScrollArea *scrollArea;
    ClipsPanelWidget *clipsPanel;
    void createView();
    int currentClip;
    int currentFrame;
signals:
     void currentClipChanged(int newCurrentClip);
     void currentFrameChanged(int newCurrentFrame);
public slots:
    void changeCurrentClip(int newCurrentClip);
    void changeCurrentFrame(int newCurrentFrame);
};

#endif // TIMELINEWIDGET_H
