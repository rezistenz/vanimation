#include "timelinewidget.h"

ClipWidget::ClipWidget(QWidget *parent=0){
    countFrames=1;

    frameWidth=15;
    frameHeight=30;

    setParent(parent);
    setFixedSize(frameWidth*countFrames+1,frameHeight+1);
}

void ClipWidget::paintEvent(QPaintEvent *event){
    QPainter painter;
    painter.begin(this);

    painter.setBrush(QBrush(Qt::darkGray));
    painter.drawRect(0,0,width()-1,height()-1);
    for(int i=0; i<maxTime; i++){
	painter.drawRect(frameWidth*i,0,frameWidth,frameHeight);
    }
    this->drawFrames(painter);

    painter.end();

}

void ClipWidget::drawFrames(QPainter &painter){
    painter.setBrush(QBrush(Qt::gray));
    for(int i=0; i<countFrames; i++){
	vector< TIME_TYPE >::iterator iter;
	iter=frameTimes.begin()+i;
	TIME_TYPE frameTime=*iter;
	TIME_TYPE nextFrameTime=frameTime+1;
	if (i < countFrames-1){
	    nextFrameTime=*(iter+1);
	}
	painter.drawRect(frameWidth*(frameTime-1),0,frameWidth*(nextFrameTime-frameTime),frameHeight);
	painter.drawEllipse(0+(frameWidth*(frameTime-1))+(frameWidth/2-4),frameHeight/2-4,8,8);
    }
}

void ClipWidget::setCountFrames(int countFrames){
    this->countFrames=countFrames;
}

void ClipWidget::clearFrameTimes(){
    this->frameTimes.clear();
}

void ClipWidget::addFrameTimes(TIME_TYPE timeFrame){
    this->frameTimes.push_back(timeFrame);
}

void ClipWidget::setMaxTime(TIME_TYPE time){
    this->maxTime=time;
    setFixedSize(frameWidth*this->maxTime+1,frameHeight+1);
}

TimelineWidget::TimelineWidget(QWidget* parent=0)
{
    setParent(parent);
    createView();
}

void TimelineWidget::createView(){

    scrollArea=new QScrollArea();

    QVBoxLayout *vLayout=new QVBoxLayout();
    setLayout(vLayout);
    vLayout->addWidget(scrollArea);
    //setFixedSize(500,200);

    QVBoxLayout *vScrollLayout=new QVBoxLayout();

    QWidget * clips=new QWidget();
    clips->setLayout(vScrollLayout);

    /*vScrollLayout->addWidget(new ClipWidget(this));
    vScrollLayout->addWidget(new ClipWidget(this));
    vScrollLayout->addWidget(new ClipWidget(this));
    vScrollLayout->addWidget(new ClipWidget(this));
    //vScrollLayout->addWidget(new ClipWidget(this));
    //vScrollLayout->addWidget(new ClipWidget(this));
    //vScrollLayout->addWidget(new ClipWidget(this));
    */
    scrollArea->setWidget(clips);

    //vScrollLayout->insertWidget(vScrollLayout->count()-1,new ClipWidget(this));

    clips->adjustSize();
}

int TimelineWidget::getCountClip(){
    return scrollArea->widget()->layout()->count();
}

void TimelineWidget::addClip(){
    ClipWidget *newClip=new ClipWidget(this);
    clips.push_back(newClip);
    this->scrollArea->widget()->layout()->addWidget(newClip);
}

void TimelineWidget::delClip(){
    ClipWidget *deletingClip=clips.back();
    clips.pop_back();
    delete deletingClip;
}

void TimelineWidget::adjustSizeClips(){
    this->scrollArea->widget()->adjustSize();
}

void TimelineWidget::setClipCountFrames(int indexClip,int countFrames){
    QVector<ClipWidget*>::iterator iter=clips.begin()+indexClip;
    ClipWidget *clip=*iter;
    clip->setCountFrames(countFrames);
}

void TimelineWidget::clearClipFameTimes(int indexClip){
    QVector<ClipWidget*>::iterator iter=clips.begin()+indexClip;
    ClipWidget *clip=*iter;
    clip->clearFrameTimes();
}

void TimelineWidget::addClipFrameTime(int indexClip,TIME_TYPE timeFrame){
    QVector<ClipWidget*>::iterator iter=clips.begin()+indexClip;
    ClipWidget *clip=*iter;
    clip->addFrameTimes(timeFrame);
}

void TimelineWidget::setMaxTimeClip(int indexClip,TIME_TYPE time){
    QVector<ClipWidget*>::iterator iter=clips.begin()+indexClip;
    ClipWidget *clip=*iter;
    clip->setMaxTime(time);
}
