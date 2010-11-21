#include "timelinewidget.h"

/*
================================================================

ClipWidget

==================================================================
*/

ClipWidget::ClipWidget(QWidget *parent=0){
    countFrames=1;

    frameWidth=15;
    frameHeight=30;

    currentClip=0;
    currentFrame=0;

    setParent(parent);
    setFixedSize(frameWidth*countFrames+1,frameHeight+1);
}

void ClipWidget::paintEvent(QPaintEvent */*event*/){

    QPainter painter;
    painter.begin(this);

    painter.setBrush(QBrush(Qt::darkGray));
    if (index==currentClip){
	painter.setBrush(QBrush(Qt::lightGray));
    }

    painter.drawRect(0,0,width()-1,height()-1);
    for(int i=0; i<maxTime; i++){
	painter.drawRect(frameWidth*i,0,frameWidth,frameHeight);
    }
    this->drawFrames(painter);

    //draw line on current frame
    int xPosCurrentFrame=currentFrame*frameWidth + frameWidth/2;
    QPen pen(Qt::green);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawLine(xPosCurrentFrame,0,xPosCurrentFrame,frameHeight);

    painter.end();

}

void ClipWidget::drawFrames(QPainter &painter){
    painter.setBrush(QBrush(Qt::gray));
    if (index==currentClip){
	painter.setBrush(QBrush(Qt::white));
    }
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

void ClipWidget::mouseReleaseEvent(QMouseEvent *event){
    if (event->button()==Qt::LeftButton){
	int curFrame=event->x()/frameWidth;

	emit currentClipChanged(index);
	emit currentFrameChanged(curFrame);
    }
}

void ClipWidget::setIndex(int newIndex){
    index=newIndex;
}

int ClipWidget::getIndex(){
    return index;
}

void ClipWidget::changeCurrentClip(int newCurrentClip){
    currentClip=newCurrentClip;
}


void ClipWidget::changeCurrentFrame(int newCurrentFrame){
    currentFrame=newCurrentFrame;
}

/*
================================================================

ClipPanelWidget

==================================================================
*/

ClipsPanelWidget::ClipsPanelWidget(QWidget *parent){
    setParent(parent);

    frameWidth=15;
    frameHeight=30;

    currentFrame=0;
    currentClip=0;
}

void ClipsPanelWidget::paintEvent( QPaintEvent * /*event*/ ){
    QPainter painter;
    painter.begin(this);

    QPen pen(Qt::darkGreen);
    pen.setWidth(3);
    painter.setPen(pen);

    int xPosFrame=currentFrame*frameWidth + frameWidth/2 +this->layout()->margin();
    painter.drawLine(xPosFrame,0,xPosFrame,this->height());

    int yPosClip=currentClip*frameHeight + frameHeight/2 +this->layout()->margin()+currentClip*this->layout()->spacing();

    painter.drawLine(0,yPosClip,this->width(),yPosClip);

    painter.end();
}

void ClipsPanelWidget::changeCurrentClip(int newCurrentClip){
    currentClip=newCurrentClip;
}

void ClipsPanelWidget::changeCurrentFrame(int newCurrentFrame){
    currentFrame=newCurrentFrame;
}


/*
================================================================

TimelineWidget

==================================================================
*/

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

    ClipsPanelWidget *clipsPanel=new ClipsPanelWidget(this);
    QObject::connect(this,SIGNAL(currentClipChanged(int)),clipsPanel,SLOT(changeCurrentClip(int)));
    QObject::connect(this,SIGNAL(currentFrameChanged(int)),clipsPanel,SLOT(changeCurrentFrame(int)));

    clipsPanel->setLayout(vScrollLayout);

    /*vScrollLayout->addWidget(new ClipWidget(this));
    vScrollLayout->addWidget(new ClipWidget(this));
    vScrollLayout->addWidget(new ClipWidget(this));
    vScrollLayout->addWidget(new ClipWidget(this));
    //vScrollLayout->addWidget(new ClipWidget(this));
    //vScrollLayout->addWidget(new ClipWidget(this));
    //vScrollLayout->addWidget(new ClipWidget(this));
    */
    scrollArea->setWidget(clipsPanel);

    //vScrollLayout->insertWidget(vScrollLayout->count()-1,new ClipWidget(this));

    clipsPanel->adjustSize();
}

int TimelineWidget::getCountClip(){
    return clips.count();
}

void TimelineWidget::addClip(){
    ClipWidget *newClip=new ClipWidget(this);
    clips.push_back(newClip);
    newClip->setIndex(clips.count()-1);
    this->scrollArea->widget()->layout()->addWidget(newClip);

    QObject::connect(newClip,SIGNAL(currentClipChanged(int)),this,SLOT(changeCurrentClip(int)));
    QObject::connect(newClip,SIGNAL(currentFrameChanged(int)),this,SLOT(changeCurrentFrame(int)));

    QObject::connect(this,SIGNAL(currentClipChanged(int)),newClip,SLOT(changeCurrentClip(int)));
    QObject::connect(this,SIGNAL(currentFrameChanged(int)),newClip,SLOT(changeCurrentFrame(int)));
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

void TimelineWidget::changeCurrentClip(int newCurrentClip){
    currentClip=newCurrentClip;

    emit currentClipChanged(currentClip);
    qDebug()<<"currentClip "<<currentClip;
    this->scrollArea->widget()->update();
}

void TimelineWidget::changeCurrentFrame(int newCurrentFrame){
    currentFrame=newCurrentFrame;

    emit currentFrameChanged(currentFrame);
    qDebug()<<"currentFrame "<<currentFrame;
    this->scrollArea->widget()->update();
}
