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
    //if (event->button()==Qt::LeftButton){
	int curFrame=event->x()/frameWidth;

	emit currentClipChanged(index);
	emit currentFrameChanged(curFrame);
    //}
	event->ignore();
}

void ClipWidget::setIndex(int newIndex){
    index=newIndex;
}

int ClipWidget::getIndex(){
    return index;
}

bool ClipWidget::inFrame(const QPoint& point){
    QPoint pos=this->mapFromGlobal(point);
    int curFrame=pos.x()/frameWidth+1;
    qDebug()<<curFrame;

    for(int i=0; i<countFrames; i++){
	vector< TIME_TYPE >::iterator iter;
	iter=frameTimes.begin()+i;

	TIME_TYPE frameTime=*iter;
	TIME_TYPE nextFrameTime=frameTime;
	if (i < countFrames-1){
	    nextFrameTime=*(iter+1);
	}

	if( (frameTime<=curFrame) && (curFrame<=nextFrameTime) ){
	    return true;
	}

    }
    return false;
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

    //createContextMenu();
}

void ClipsPanelWidget::createContextMenu(){
    /*this->contextMenu=new QMenu(this);
    this->contextMenu->addAction("Add clip");
    this->contextMenu->addAction("Del clip");
    this->contextMenu->addSeparator();
    this->contextMenu->addAction("Add frame");
    this->contextMenu->addAction("Del frame");*/
}

/*void ClipsPanelWidget::mouseReleaseEvent(QMouseEvent* event){
    if (event->button()==Qt::RightButton){
	contextMenu->exec(event->globalPos());
    }
    event->ignore();
}
*/
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

void TimelineWidget::setController(SceneController* controller){
    this->controller=controller;
}

void TimelineWidget::setModel(SceneModel* model){
    this->model=model;
}

//this method from class CanvasWidget
// Nedd refactoring in to qtsceneview
int TimelineWidget::getValidFameIndex(int frameIndex){
    int validFrameIndex=-1;

    //SceneModel *model=view->getSceneModel();

    StateModelCommand cmd;
    ModelState state;

    cmd.CMD=GET_CLIP_FRAME_COUNT;
    cmd.intData=currentClip;
    state=model->getStateModel(cmd);
    int frameCount=state.intData;

    for(int index=0;index<frameCount;index++){
	cmd.CMD=GET_CLIP_FRAME_TIME;
	cmd.pointData.x=currentClip;
	cmd.pointData.y=index;

	state=model->getStateModel(cmd);
	TIME_TYPE this_time=state.timeData;

	if ( (index+1)!=frameCount ){

	    cmd.CMD=GET_CLIP_FRAME_TIME;
	    cmd.pointData.x=currentClip;
	    cmd.pointData.y=index+1;

	    state=model->getStateModel(cmd);
	    TIME_TYPE next_time=state.timeData;

	    if ( (frameIndex>=this_time-1) && (frameIndex<next_time-1) ){
		validFrameIndex=index;
	    }
	}else{
	    if ( frameIndex==this_time-1 ){
		validFrameIndex=index;
	    }
	}
    }

    return validFrameIndex;
}


void TimelineWidget::createView(){

    scrollArea=new QScrollArea(this);

    QVBoxLayout *vLayout=new QVBoxLayout();
    setLayout(vLayout);
    vLayout->addWidget(scrollArea);

    playPanel= new PlayPanelWidget(this);
    playPanel->setSceneView(this->model->getSceneView());
    connect(playPanel,SIGNAL(currentClipChanged(int)),this,SLOT(changeCurrentClip(int)));
    connect(this,SIGNAL(currentClipChanged(int)),playPanel,SLOT(changeCurrentClip(int)));

    connect(playPanel,SIGNAL(currentFrameChanged(int)),this,SLOT(changeCurrentFrame(int)));
    connect(this,SIGNAL(currentFrameChanged(int)),playPanel,SLOT(changeCurrentFrame(int)));
    vLayout->addWidget(playPanel);



    QVBoxLayout *vScrollLayout=new QVBoxLayout();

    clipsPanel=new ClipsPanelWidget(this);
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

    //clipsPanel->adjustSize();

    createContextMenu();
}

void TimelineWidget::createContextMenu(){
    this->contextMenu=new QMenu(this);
    this->contextMenu->addAction("Add clip");
    this->contextMenu->addAction("Del clip");
    this->contextMenu->addSeparator();
    this->contextMenu->addAction("Add frame");
    this->contextMenu->addAction("Del frame");

    connect(contextMenu->actions().at(0),SIGNAL(triggered()),this,SLOT(addClipSlot()));
    connect(contextMenu->actions().at(1),SIGNAL(triggered()),this,SLOT(delClipSlot()));

    connect(contextMenu->actions().at(3),SIGNAL(triggered()),this,SLOT(addFrameSlot()));
    connect(contextMenu->actions().at(4),SIGNAL(triggered()),this,SLOT(delFrameSlot()));
}

void  TimelineWidget::mouseReleaseEvent(QMouseEvent* event){
    if (event->button()==Qt::RightButton){
	if ( scrollArea->viewport()->rect().contains( event->pos() )  ){

	    contextMenu->actions().at(0)->setEnabled(true);
	    contextMenu->actions().at(1)->setEnabled(false);
	    contextMenu->actions().at(3)->setEnabled(false);
	    contextMenu->actions().at(4)->setEnabled(false);


	    for(QVector<ClipWidget*>::iterator iter=clips.begin();iter!=clips.end();iter++){
		ClipWidget *clip=*iter;
		QPoint point(event->globalPos());
		QRect rect(
			    clip->mapToGlobal(clip->rect().topLeft()),
			    clip->mapToGlobal(clip->rect().bottomRight())
			   );
		if( rect.contains(point) ){
		    contextMenu->actions().at(1)->setEnabled(true);
		    contextMenu->actions().at(3)->setEnabled(true);

		    if(clip->inFrame(point)){
			contextMenu->actions().at(4)->setEnabled(true);
		    }

		    break;
		}
	    }

	    this->contextMenu->exec(event->globalPos());
	}
    }
    this->playPanel->stop();
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

    newClip->changeCurrentClip(this->currentClip);
    newClip->changeCurrentFrame(this->currentFrame);
}

void TimelineWidget::delClip(){
    ClipWidget *deletingClip=clips.back();
    clips.pop_back();
    delete deletingClip;
}

void TimelineWidget::adjustSizeClips(){
    QApplication::processEvents();
    this->clipsPanel->adjustSize();
    this->clipsPanel->update();
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
    this->clipsPanel->update();
}

void TimelineWidget::changeCurrentFrame(int newCurrentFrame){
    currentFrame=newCurrentFrame;

    emit currentFrameChanged(currentFrame);
    qDebug()<<"currentFrame "<<currentFrame;
    this->clipsPanel->update();
}

void TimelineWidget::addClipSlot(){
    this->controller->addClip();
}

void TimelineWidget::addFrameSlot(){
    this->controller->addFrameToClip(this->currentClip,this->currentFrame+1);
    emit currentFrameChanged(currentFrame);
}

void TimelineWidget::delClipSlot(){
    this->controller->delClip(this->currentClip);
}

void TimelineWidget::delFrameSlot(){
    emit setDeletingOldCurrentFrame();
    this->controller->delFrameFromClip(this->currentClip,this->getValidFameIndex(this->currentFrame));
    emit currentFrameChanged(currentFrame);
}




/*-----------------------------------------------------------

    class PlayPanelWidget

------------------------------------------------------------*/

PlayPanelWidget::PlayPanelWidget(QWidget *parent){
    this->setParent(parent);
    currentFrame=1;

    QHBoxLayout *hLayout=new QHBoxLayout();
    this->setLayout(hLayout);

    this->btnPlay=new QPushButton(QString("Play"),this);
    this->btnPause=new QPushButton(QString("Pause"),this);
    this->btnStop=new QPushButton(QString("Stop"),this);

    QButtonGroup *btnGroup= new QButtonGroup(this);
    btnGroup->addButton(this->btnPlay);
    btnGroup->addButton(this->btnPause);
    btnGroup->addButton(this->btnStop);

    hLayout->addWidget(this->btnPlay);
    hLayout->addWidget(this->btnPause);
    hLayout->addWidget(this->btnStop);
    lbl = new QLabel( QString().setNum(this->currentFrame),this);
    hLayout->addWidget(lbl);
    hLayout->addStretch();

    connect(btnPlay,SIGNAL(clicked()),this,SLOT(play()));
    connect(btnPause,SIGNAL(clicked()),this,SLOT(pause()));
    connect(btnStop,SIGNAL(clicked()),this,SLOT(stop()));

    timer= new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerSlot()));
    timer->setInterval(100);
}

void PlayPanelWidget::timerSlot(){
    TIME_TYPE maxTime=view->getSceneModel()->getScene()->getMaxTime();

    if(this->currentFrame<maxTime){
	this->currentFrame++;
    }else{
	this->currentFrame=1;
    }
    emit currentClipChanged(currentClip);
    emit currentFrameChanged(currentFrame);
    lbl->setText(QString().setNum(this->currentFrame));
    QApplication::processEvents();
}

void PlayPanelWidget::play(){
    state=PLAY;
    timer->start();
    //qDebug()<<timer->timerId();
}

void PlayPanelWidget::pause(){
    if (state==PLAY){
	state=PAUSE;
    }
    timer->stop();
    //qDebug()<<timer->timerId();
}

void PlayPanelWidget::stop(){
    state=STOP;
    timer->stop();
    //qDebug()<<timer->timerId();
}

void PlayPanelWidget::changeCurrentClip(int newCurrentClip){
    this->currentClip=newCurrentClip;
}

void PlayPanelWidget::changeCurrentFrame(int newCurrentFrame){
    this->currentFrame=newCurrentFrame;
    lbl->setText(QString().setNum(this->currentFrame));
}

void PlayPanelWidget::setSceneView(SceneView *newView){
    this->view=newView;
}
