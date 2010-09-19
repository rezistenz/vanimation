#include "canvaswidget.h"

/*
=================================================================

    Shape

=================================================================
*/

ShapeType Shape::getType(){
    return type;
}

Rectangle::Rectangle(){
    this->type=RECTANGLE;
}

void Rectangle::draw(QPainter &painter){
    painter.setPen(QPen(QBrush(Qt::black),1));
    //painter.setBrush(QBrush(Qt::red));
    painter.drawRect(left(),top(),width(),height());
}

bool Rectangle::selected(QPoint &point){
    return this->contains(point);
}

Ellipse::Ellipse(){
    this->type=ELLIPSE;
}

void Ellipse::draw(QPainter &painter){
    painter.setPen(QPen(QBrush(Qt::black),1));
    //painter.setBrush(QBrush(Qt::red));
    painter.drawEllipse(left(),top(),width(),height());
}

bool Ellipse::selected(QPoint &point){
    //return this->contains(point);
    QRegion region(x(),y(),width(),height(),QRegion::Ellipse);
    return region.contains(point);
}

/*
=================================================================

    Canvas

=================================================================
*/


Canvas::Canvas(QWidget *parent){
    this->setParent(parent);
    canvasColor=new QColor(Qt::white);
    drawing=false;
    currentShapeType=RECTANGLE;
    currentOperation=SELECT;
    selectShapeIndex=-1;
    dragging=false;
    changing=false;
}

Canvas::~Canvas(){
    while (!shapes.empty()){
	    delete shapes.back();
	    shapes.pop_back();
    }
}
Shape * Canvas::getShape(int index){
    int curIndex=0;
    for( list< Shape * >::iterator shape=shapes.begin(); shape!=shapes.end(); shape++ ){
	if (curIndex==index){
	    return (*shape);
	}
	curIndex++;
    }
}

void Canvas::setCanvasColor(QColor &color){
    (*canvasColor)=color;
}

void Canvas::drawCanvas(QPainter &painter){
    QPen pen(Qt::NoPen);
    QBrush brash(*canvasColor);

    painter.setPen(pen);
    painter.setBrush(brash);
    //draw background
    painter.drawRect(this->rect());

    drawShapes(painter);

    if (drawing) {
	painter.setPen(QPen(QBrush(Qt::black),1,Qt::DashLine));
	painter.setBrush(QBrush(Qt::gray,Qt::Dense6Pattern));
	switch (currentShapeType){
	case RECTANGLE:{
	    painter.drawRect(QRect(startPosMouse,endPosMouse));
	    }
	    break;
	case ELLIPSE:{
	    painter.drawEllipse(QRect(startPosMouse,endPosMouse));
	    }
	    break;
	}
    }

    if (dragging) {
	painter.setPen(QPen(QBrush(Qt::black),1,Qt::DashLine));
	painter.setBrush(QBrush(Qt::gray,Qt::Dense6Pattern));
	Shape * shape=getShape(selectShapeIndex);
	switch (shape->getType()){
	case RECTANGLE:{
		QRect rect;
		rect.setTopLeft(shape->topLeft());
		rect.setBottomRight(shape->bottomRight());
		rect.moveCenter(endPosMouse+dPointMouseShape);
		painter.drawRect(rect);
	    }
	    break;
	case ELLIPSE:{
		QRect rect;
		rect.setTopLeft(shape->topLeft());
		rect.setBottomRight(shape->bottomRight());
		rect.moveCenter(endPosMouse+dPointMouseShape);
		painter.drawEllipse(rect);
	    }
	    break;
	}
    }

    if (changing) {
	painter.setPen(QPen(QBrush(Qt::black),1,Qt::DashLine));
	painter.setBrush(QBrush(Qt::gray,Qt::Dense6Pattern));
	Shape * shape=getShape(selectShapeIndex);
	switch (shape->getType()){
	case RECTANGLE:{
		QRect rect;
		rect.setTopLeft(shape->topLeft());
		rect.setBottomRight(endPosMouse+dPointMouseShape);
		painter.drawRect(rect);
	    }
	    break;
	case ELLIPSE:{
		QRect rect;
		rect.setTopLeft(shape->topLeft());
		rect.setBottomRight(endPosMouse+dPointMouseShape);
		painter.drawEllipse(rect);
	    }
	    break;
	}
	painter.setPen(QPen(Qt::black));
	painter.setBrush(QBrush(Qt::green));
	painter.drawRect(endPosMouse.x()+dPointMouseShape.x(),endPosMouse.y()+dPointMouseShape.y(),6,6);
    }
}

void Canvas::drawShapes(QPainter &painter){
    int index=0;
    for( list< Shape * >::iterator shape=shapes.begin(); shape!=shapes.end(); shape++ ){
	painter.setBrush(QBrush(Qt::white));
	if (selectShapeIndex==index){
	    painter.setBrush(QBrush(Qt::red));
	}

	(*shape)->draw(painter);
	index++;
    }

    drawChangeAnchors(painter);
}

void Canvas::drawChangeAnchors(QPainter &painter){

    if (selectShapeIndex!=-1){
	Shape * shape=getShape(selectShapeIndex);

	painter.setPen(QPen(Qt::black));
	painter.setBrush(QBrush(Qt::green));

	switch (shape->getType()){
	case RECTANGLE:{
		QPoint bottomRight=shape->bottomRight();
		painter.drawRect(bottomRight.x(),bottomRight.y(),6,6);
	    }
	    break;
	case ELLIPSE:{
		QPoint bottomRight=shape->bottomRight();
		painter.drawRect(bottomRight.x(),bottomRight.y(),6,6);
	    }
	    break;
	}
    }
}

void Canvas::checkShapesSelect(QPoint pos){
    bool select=false;
    int index=shapes.size()-1;
    for( list< Shape * >::reverse_iterator shape=shapes.rbegin(); shape!=shapes.rend(); shape++ ){
	select=(*shape)->selected(pos);
	if (select){
	    selectShapeIndex=index;
	    return;
	}
	index--;
    }
    selectShapeIndex=-1;
}

bool Canvas::clickChangeAnchors(QPoint pos){
    bool click=false;
    Shape *shape=getShape(this->selectShapeIndex);
    QRect rectAnchor;
    rectAnchor.setRect(shape->bottomRight().x(),shape->bottomRight().y(),6,6);
    click=rectAnchor.contains(pos);
    return click;
}

void Canvas::paintEvent(QPaintEvent *event){
    QPainter painter;
    painter.begin(this);

    drawCanvas(painter);

    painter.end();
}

void Canvas::mousePressEvent(QMouseEvent * event){ 
    switch (currentOperation) {
    case SELECT:{
	    //check clic anchors
	    if (selectShapeIndex!=-1){
		if(clickChangeAnchors(event->pos())){
		    changing=true;
		    startPosMouse=event->pos();
		    endPosMouse=event->pos();

		    Shape *shape=getShape(this->selectShapeIndex);
		    QRect rectAnchor;
		    rectAnchor.setRect(shape->bottomRight().x(),shape->bottomRight().y(),6,6);
		    QPoint topLeftAnchor=rectAnchor.topLeft();
		    dPointMouseShape=topLeftAnchor-startPosMouse;
		    break;
		}
	    }
	    //check dragging
	    checkShapesSelect(event->pos());
	    if (selectShapeIndex!=-1){
		dragging=true;
		startPosMouse=event->pos();
		endPosMouse=event->pos();
		Shape * shape=getShape(selectShapeIndex);
		QPoint centerShape=shape->center();
		dPointMouseShape=centerShape-startPosMouse;
	    }
	}
	break;
    case DRAW_RECTANGLE:{
	    drawing=true;
	    currentShapeType=RECTANGLE;
	    startPosMouse=event->pos();
	    endPosMouse=event->pos();
	}
	break;
    case DRAW_ELLIPSE:{
	    drawing=true;
	    currentShapeType=ELLIPSE;
	    startPosMouse=event->pos();
	    endPosMouse=event->pos();
	}
	break;
    default:{
	    qDebug()<<"incorrect currentOperation mousePressEvent";
	}
    }
    this->update();
}

void Canvas::mouseMoveEvent(QMouseEvent * event){
    switch (currentOperation) {
    case SELECT:{
	    if (changing){
		endPosMouse=event->pos();
	    }

	    if (dragging){
		endPosMouse=event->pos();
	    }
	}
	break;
    case DRAW_RECTANGLE:{
	    if (drawing){
		endPosMouse=event->pos();
	    }
	}
	break;
    case DRAW_ELLIPSE:{
	    if (drawing){
		endPosMouse=event->pos();
	    }
	}
	break;
    default:{
	    qDebug()<<"incorrect currentOperation mouseMoveEvent";
	}
    }
    this->update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event){
    switch (currentOperation) {
    case SELECT:{	   
	    if (dragging){
		endPosMouse=event->pos();
		if(endPosMouse!=startPosMouse){
		    Shape * shape=getShape(this->selectShapeIndex);
		    shape->moveCenter(endPosMouse+dPointMouseShape);
		}
		dragging=false;
	    }else{
		if (changing){
		    endPosMouse=event->pos();
		    if(endPosMouse!=startPosMouse){
			Shape * shape=getShape(this->selectShapeIndex);
			shape->setBottomRight(endPosMouse+dPointMouseShape);
		    }
		    changing=false;
		}else{
		    checkShapesSelect(event->pos());
		}
	    }
	}
	break;
    case DRAW_RECTANGLE:{
	    if (drawing){
		endPosMouse=event->pos();
		if(endPosMouse!=startPosMouse){
		    Shape * shape=createShape(currentShapeType,QRect(startPosMouse,endPosMouse));
		    shapes.push_back(shape);
		}
		drawing=false;
	    }
	}
	break;
    case DRAW_ELLIPSE:{
	    if (drawing){
		endPosMouse=event->pos();
		if(endPosMouse!=startPosMouse){
		    Shape * shape=createShape(currentShapeType,QRect(startPosMouse,endPosMouse));
		    shapes.push_back(shape);
		}
		drawing=false;
	    }
	}
	break;
    default:{
	    qDebug()<<"incorrect currentOperation mouseReleaseEvent";
	}
    }

    this->update();
}

Shape * Canvas::createShape(ShapeType type,QRect rect){
    Shape *shape =NULL;
    switch (type) {
    case RECTANGLE:{
	    shape =new Rectangle();
	    shape->setTopLeft(rect.topLeft());
	    shape->setBottomRight(rect.bottomRight());
	}
	break;
    case ELLIPSE:{
	    shape =new Ellipse();
	    shape->setTopLeft(rect.topLeft());
	    shape->setBottomRight(rect.bottomRight());
	}
	break;
    }
    return shape;
}


void Canvas::setCurrentOperation(Operations operation){
    currentOperation=operation;
}


/*
=================================================================

    CanvasWidget

=================================================================
*/



CanvasWidget::CanvasWidget(QWidget *parent){
    this->setParent(parent);

    canvasWidth=640;
    canvasHeigth=480;

    createView();
}

void CanvasWidget::createView(){
    scrollArea=new QScrollArea();
    canvas=new Canvas(this);
    canvas->setFixedSize(canvasWidth,canvasHeigth);
    scrollArea->setWidget(canvas);

    QHBoxLayout *hLayout=new QHBoxLayout();
    this->setLayout(hLayout);
    buttonsPanel=new QFrame(this);
    buttonsPanel->setMinimumWidth(100);
    buttonsPanel->setMaximumWidth(100);

    hLayout->addWidget(buttonsPanel);
    QVBoxLayout *vLayout=new QVBoxLayout();
    buttonsPanel->setLayout(vLayout);

    QPushButton *btnSelect=new QPushButton(QString("Select"),this);
    btnSelect->setCheckable(true);
    btnSelect->setChecked(true);
    QPushButton *btnRect=new QPushButton(QString("Rect"),this);
    btnRect->setCheckable(true);
    QPushButton *btnEllipse=new QPushButton(QString("Ellipse"),this);
    btnEllipse->setCheckable(true);
    QButtonGroup *btnGroup= new QButtonGroup(this);
    btnGroup->addButton(btnSelect);
    btnGroup->addButton(btnRect);
    btnGroup->addButton(btnEllipse);

    QObject::connect(btnSelect,SIGNAL(clicked()),this,SLOT(setOperationSelect()));
    QObject::connect(btnRect,SIGNAL(clicked()),this,SLOT(setOperationDrawRectangle()));
    QObject::connect(btnEllipse,SIGNAL(clicked()),this,SLOT(setOperationDrawEllipse()));

    QObject::connect(this,SIGNAL(changeCurrentOperation(Operations)),canvas,SLOT(setCurrentOperation(Operations)));

    vLayout->addWidget(btnSelect);
    vLayout->addWidget(btnRect);
    vLayout->addWidget(btnEllipse);
    vLayout->addStretch();

    hLayout->addWidget(scrollArea);


}

void CanvasWidget::setOperationSelect(){
    emit changeCurrentOperation(SELECT);
}

void CanvasWidget::setOperationDrawRectangle(){
    emit changeCurrentOperation(DRAW_RECTANGLE);
}

void CanvasWidget::setOperationDrawEllipse(){
    emit changeCurrentOperation(DRAW_ELLIPSE);
}
