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

    this->drawFrames(painter);

    painter.end();

}

void ClipWidget::drawFrames(QPainter &painter){
    painter.setBrush(QBrush(Qt::gray));
    for(int i=0; i<countFrames; ++i){
	painter.drawRect(0+(frameWidth)*i,0,frameWidth,frameHeight);
    }
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
    setFixedSize(300,200);

    QVBoxLayout *vScrollLayout=new QVBoxLayout();

    QWidget * clips=new QWidget();
    clips->setLayout(vScrollLayout);

    vScrollLayout->addWidget(new ClipWidget(this));
    vScrollLayout->addWidget(new ClipWidget(this));
    vScrollLayout->addWidget(new ClipWidget(this));
    vScrollLayout->addWidget(new ClipWidget(this));
    //vScrollLayout->addWidget(new ClipWidget(this));
    //vScrollLayout->addWidget(new ClipWidget(this));
    //vScrollLayout->addWidget(new ClipWidget(this));

    scrollArea->setWidget(clips);

    vScrollLayout->insertWidget(vScrollLayout->count()-1,new ClipWidget(this));

    clips->adjustSize();
}
