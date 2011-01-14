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
    int countShapes=shapes.size();

    assert(countShapes!=0);
    assert( (index >= 0) && (index <= (countShapes-1)) );

    if ( countShapes == 0 ){
	std::cerr << "ERROR: in function Canvas::getShape(int index) shapes is empty!" << std::endl;
	exit(EXIT_FAILURE);
    }

    if (!((index >= 0) && (index <= (countShapes-1)))){
	std::cerr << "ERROR: in function Canvas::getShape(int index) index out of bounds!" << std::endl;
	exit(EXIT_FAILURE);
    }

    Shape *shape=NULL;
    int curIndex=0;
    for( list< Shape * >::iterator shapeIter=shapes.begin(); shapeIter!=shapes.end(); shapeIter++ ){
	if (curIndex==index){
	    shape=(*shapeIter);
	    break;
	}
	curIndex++;
    }

    return shape;
}

void Canvas::setCanvasColor(QColor &color){
    (*canvasColor)=color;
}

void Canvas::setSelectShapeIndex(int index){
    this->selectShapeIndex=index;
}

void Canvas::delCurrentShape(){
    if (this->currentOperation==SELECT){
	if ( this->selectShapeIndex != -1 ){

	    Shape* shape=NULL;
	    int curIndex=0;
	    for( list< Shape * >::iterator shapeIter=shapes.begin(); shapeIter!=shapes.end(); shapeIter++ ){
		if (curIndex==this->selectShapeIndex){
		    shape=(*shapeIter);

		    delete shape;
		    shapes.erase(shapeIter);
		    //qDebug()<<shapes.size();
		    break;
		}
		curIndex++;
	    }

	    this->setSelectShapeIndex(-1);
	}
    }
    this->update();
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
	if (index==this->selectShapeIndex){
	    drawSelectedShape(painter);
	}else{
	    (*shape)->draw(painter);
	}
	index++;
    }

    drawChangeAnchors(painter);
}

void Canvas::drawSelectedShape(QPainter &painter){
    if (selectShapeIndex!=-1){
	Shape * shape=getShape(selectShapeIndex);

	painter.setBrush(QBrush(Qt::red));
	shape->draw(painter);
	painter.setBrush(QBrush(Qt::gray,Qt::Dense6Pattern));
	shape->draw(painter);
    }
}

void Canvas::drawChangeAnchors(QPainter &painter){

    if (selectShapeIndex!=-1){
	Shape * shape=getShape(selectShapeIndex);

	//draw selection rectangle for shape
	painter.setPen(QPen(QBrush(Qt::black),1,Qt::DashLine));
	painter.setBrush(QBrush(Qt::NoBrush));
	painter.drawRect(QRect(shape->left(),shape->top(),shape->width(),shape->height()));

	//draw bottomRight point anchor
	painter.setPen(QPen(Qt::black));
	painter.setBrush(QBrush(Qt::green));
	QPoint bottomRight=shape->bottomRight();
	painter.drawRect(bottomRight.x(),bottomRight.y(),6,6);


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

void Canvas::paintEvent(QPaintEvent */*event*/){
    QPainter painter;
    painter.begin(this);
    //painter.setRenderHint(QPainter::Antialiasing,true);

    drawCanvas(painter);

    painter.end();
}

void Canvas::mousePressEvent(QMouseEvent * event){ 

if(event->button()==Qt::LeftButton){
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



}

void Canvas::mouseMoveEvent(QMouseEvent * event){
//if(event->button()==Qt::LeftButton){
    switch (currentOperation) {
    case SELECT:{
	    if (changing){
		/*QPoint newPosMouse=event->pos();
		Shape * shape=getShape(this->selectShapeIndex);

		if (newPosMouse.x() <= shape->topLeft().x()+10){
		    endPosMouse.setX(shape->topLeft().x()+10);
		}else{
		    endPosMouse.setX(newPosMouse.x());
		}

		if (newPosMouse.y() <= shape->topLeft().y()+10){
		    endPosMouse.setY(shape->topLeft().y()+10);
		}else{
		    endPosMouse.setY(newPosMouse.y());
		}*/
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
//}
}

void Canvas::mouseReleaseEvent(QMouseEvent *event){


if(event->button()==Qt::LeftButton){
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

			QRect rectNormalised=shape->normalized();
			shape->setTopLeft(rectNormalised.topLeft());
			shape->setBottomRight(rectNormalised.bottomRight());
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

		    QRect rectNormalised=shape->normalized();
		    shape->setTopLeft(rectNormalised.topLeft());
		    shape->setBottomRight(rectNormalised.bottomRight());

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

		    QRect rectNormalised=shape->normalized();
		    shape->setTopLeft(rectNormalised.topLeft());
		    shape->setBottomRight(rectNormalised.bottomRight());

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
else{
    if(currentOperation==SELECT){
	checkShapesSelect(event->pos());
	this->update();
	this->createContextMenu(event->globalPos());
    }
}

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

int Canvas::getShapesCount(){
    return shapes.size();
}

SceneShape Canvas::getShapeForScene(int index){
    SceneShape sceneShape;
    Shape *shape=getShape(index);

    sceneShape.x=shape->x();
    sceneShape.y=shape->y();
    sceneShape.width=shape->width();
    sceneShape.height=shape->height();
    sceneShape.type=shape->getType();

    return sceneShape;
}

void Canvas::clearShapes(){
    while (!shapes.empty()){
	    delete shapes.back();
	    shapes.pop_back();
    }
}

void Canvas::addShapeFromScene(SceneShape sceneShape){
    Shape *shape=createShape(sceneShape.type,QRect(sceneShape.x,sceneShape.y,sceneShape.width,sceneShape.height));
    shapes.push_back(shape);
}

void Canvas::createContextMenu(const QPoint& pos){
    if ( this->currentOperation==SELECT && this->selectShapeIndex != -1 ){
	Shape* shape=this->getShape(this->selectShapeIndex);
	QPoint point=this->mapFromGlobal(pos);

	if ( shape->selected(point) ){
	    QMenu menu(this);

	    menu.addActions(this->actions());
	    menu.exec(pos);
	}
    }
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

    currentClip=-1;
    currentFrame=-1;

    oldCurrentClip=-1;
    oldCurrentFrame=-1;

    createView();
}

void CanvasWidget::setSceneController(SceneController *newController){
    controller=newController;
}

void CanvasWidget::setSceneView(SceneView *newView){
    view=newView;
}


void CanvasWidget::setCurrentClip(int newCurrentClip){
    this->currentClip=newCurrentClip;
}

void CanvasWidget::setOldCurrentClip(int newCurrentClip){
    this->oldCurrentClip=newCurrentClip;
}

void CanvasWidget::setCurrentFrame(int newCurrentFrame){
    this->currentFrame=newCurrentFrame;
}

void CanvasWidget::setOldCurrentFrame(int newCurrentFrame){
    this->oldCurrentFrame=newCurrentFrame;
}



void CanvasWidget::clearCanvas(){
    this->canvas->clearShapes();
    this->canvas->setSelectShapeIndex(-1);
    this->canvas->hide();
}

void CanvasWidget::setNewActionsForCanvas(){
    canvas->addActions(this->actions());
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

int CanvasWidget::getValidFameIndex(int frameIndex){
    int validFrameIndex=-1;

    SceneModel *model=view->getSceneModel();

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


void CanvasWidget::saveState(){

    bool changedClip=(oldCurrentClip!=currentClip);
    //bool changedFrame=(oldCurrentFrame!=currentFrame);

    qDebug()<<"State Change=true, Save changes in SceneModel...";

    int chapesCount=canvas->getShapesCount();

    if (changedClip){
	controller->setShapesCountForFrame(oldCurrentClip,oldCurrentFrame,chapesCount);
    }else{
	controller->setShapesCountForFrame(currentClip,oldCurrentFrame,chapesCount);
    }

    for (int index=0;index<chapesCount;index++){

	SceneShape sceneShape=canvas->getShapeForScene(index);

	if (changedClip){
	    controller->setShapeForFrame(oldCurrentClip,oldCurrentFrame,index,sceneShape);
	}else{
	    controller->setShapeForFrame(currentClip,oldCurrentFrame,index,sceneShape);
	}
    }

    canvas->clearShapes();
    canvas->update();

    canvas->setSelectShapeIndex(-1);
    canvas->hide();
}

void CanvasWidget::loadState(){

    int chapesCount=view->getShapesCountForFrame(currentClip,currentFrame);
    for (int index=0;index<chapesCount;index++){
	SceneShape sceneShape=view->getShapeForFrame(currentClip,currentFrame,index);
	canvas->addShapeFromScene(sceneShape);
    }


    canvas->update();

    canvas->setSelectShapeIndex(-1);
    canvas->show();
}

void CanvasWidget::updateState(){
    bool changedClip=false;
    bool changedFrame=false;
    bool isChange=false;
    changedClip=(oldCurrentClip!=currentClip);
    changedFrame=(oldCurrentFrame!=currentFrame);
    isChange=changedClip || changedFrame;

    if(isChange){

	if (changedClip){
	    bool b1=(oldCurrentClip != -1);
	    bool b2=(oldCurrentFrame != -1);
	    bool b3=b1 && b2;
	    if ( b3 ){
		saveState();
	    }
	}else{
	    bool b1=(currentClip != -1);
	    bool b2=(oldCurrentFrame != -1);
	    bool b3=b1 && b2;

	    if ( b3 ){
		saveState();
	    }
	}


	if ( (currentClip != -1) && (currentFrame != -1) ){
	    loadState();
	}

    }
}

void CanvasWidget::changeCurrentClip(int newCurrentClip){
    oldCurrentClip=currentClip;
    currentClip=newCurrentClip;

    //updateState();
}


void CanvasWidget::changeCurrentFrame(int newCurrentFrame){

    int	currentFrameIndex=getValidFameIndex(newCurrentFrame);

    oldCurrentFrame=currentFrame;
    currentFrame=currentFrameIndex;

    updateState();

    /*if (oldCurrentClip != -1){
	if (oldCurrentFrame != -1){
	    saveStateChange();

	    canvas->setSelectShapeIndex(-1);
	    canvas->hide();
	}
    }

	if(currentFrame != -1){
	    loadState();

	    canvas->setSelectShapeIndex(-1);
	    canvas->show();
	}
	*/


}

void CanvasWidget::setDeletingOldCurrentFrame(){
    this->currentFrame=-1;
    canvas->clearShapes();
    canvas->update();
    canvas->setSelectShapeIndex(-1);
    canvas->hide();
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

void CanvasWidget::delCurrentShape(){
    this->canvas->delCurrentShape();
}
