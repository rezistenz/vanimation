#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timelinewidget.h"
#include "qtsceneview.h"
#include "qtscenecontroller.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->verticalLayout->setMargin(0);
    ui->verticalLayout->setSpacing(0);;

    QSplitter *splitter=new QSplitter(Qt::Vertical,this);
    ui->verticalLayout->addWidget(splitter);

    tl=new TimelineWidget(this);


    splitter->addWidget(tl);
    cw=new CanvasWidget(this);
    splitter->addWidget(cw);


    scene=new Scene();

    /*scene->addClip();
    scene->addClip();
    scene->addClip();

    scene->getClip(0)->addFrame(1);
    scene->getClip(0)->addFrame(10);
    scene->getClip(0)->addFrame(20);
    scene->getClip(0)->addFrame(30);
    scene->getClip(0)->addFrame(40);
    scene->getClip(0)->addFrame(50);

    scene->getClip(1)->addFrame(1);
    scene->getClip(1)->addFrame(4);

    scene->getClip(2)->addFrame(2);
    scene->getClip(2)->addFrame(5);
    scene->getClip(2)->addFrame(10);
    */
    model=new SceneModel();
    model->setScene(scene);
    controller=new QtSceneController();
    view=new QtSceneView();

    view->setSceneController(controller);
    view->setSceneModel(model);
    controller->setSceneModel(model);
    model->setSceneView(view);

    view->setCanvasWidget(cw);
    view->setTimeLineWidget(tl);
    view->configureTimeLineAndCanvasWidget();

    //view->refreshSceneView();

    /*controller->addClip();
    controller->addFrameToClip(0,1);
    controller->addFrameToClip(0,10);
    controller->addFrameToClip(0,20);
    controller->addFrameToClip(0,30);
    controller->addFrameToClip(0,40);
    controller->addFrameToClip(0,50);

    controller->addClip();
    controller->addFrameToClip(1,1);
    controller->addFrameToClip(1,4);
    controller->addClip();
    controller->addFrameToClip(2,2);
    controller->addFrameToClip(2,5);
    controller->addFrameToClip(2,10);

    tl->changeCurrentClip(0);
    tl->changeCurrentFrame(0);

    //tl->changeCurrentClip(0);
    //tl->changeCurrentFrame(0);

    scene->saveToFile("file.txt");
    scene->loadFromFile("file1.txt");

    view->refreshSceneView();
*/
    tl->contextMenu->addActions(ui->menuEdit->actions());
    cw->addAction(ui->actionDel_shepe);
    cw->setNewActionsForCanvas();

    QObject::connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(exit()));
    QObject::connect(ui->actionCloseFile,SIGNAL(triggered()),this,SLOT(closeFile()));
    QObject::connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(newFile()));
    QObject::connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openFile()));
    QObject::connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(saveFile()));
    QObject::connect(ui->actionSave_As,SIGNAL(triggered()),this,SLOT(saveFileAs()));

    QObject::connect(ui->actionAdd_clip,SIGNAL(triggered()),tl,SLOT(addClipSlot()));
    QObject::connect(ui->actionDel_clip,SIGNAL(triggered()),tl,SLOT(delClipSlot()));
    QObject::connect(ui->actionAdd_frame,SIGNAL(triggered()),tl,SLOT(addFrameSlot()));
    QObject::connect(ui->actionDel_frame,SIGNAL(triggered()),tl,SLOT(delFrameSlot()));
    QObject::connect(ui->actionDel_shepe,SIGNAL(triggered()),cw,SLOT(delCurrentShape()));

    this->ui->actionSave->setEnabled(false);
    this->ui->actionSave_As->setEnabled(false);
    this->ui->actionCloseFile->setEnabled(false);

    this->ui->actionAdd_clip->setEnabled(false);
    this->ui->actionDel_clip->setEnabled(false);
    this->ui->actionAdd_frame->setEnabled(false);
    this->ui->actionDel_frame->setEnabled(false);

    this->tl->hide();
    this->cw->hide();

    this->openFile();
}

MainWindow::~MainWindow()
{
    //scene->saveToFile("file1.txt");
    delete scene;
    delete model;
    delete view;
    delete controller;

    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void  MainWindow::exit(){
    QApplication::exit();
}

void  MainWindow::closeFile(){
    this->view->setDefaultCanvasWidget();
    this->controller->closeFile();

    this->ui->actionSave->setEnabled(false);
    this->ui->actionSave_As->setEnabled(false);
    this->ui->actionCloseFile->setEnabled(false);

    this->ui->actionAdd_clip->setEnabled(false);
    this->ui->actionDel_clip->setEnabled(false);
    this->ui->actionAdd_frame->setEnabled(false);
    this->ui->actionDel_frame->setEnabled(false);

    this->tl->hide();
    this->cw->hide();
}

void  MainWindow::newFile(){
    this->closeFile();

    this->controller->addClip();
    this->controller->addFrameToClip(0,1);

    this->tl->changeCurrentClip(0);
    this->tl->changeCurrentFrame(0);

    this->tl->checkFrame();

    this->ui->actionSave->setEnabled(true);
    this->ui->actionSave_As->setEnabled(true);
    this->ui->actionCloseFile->setEnabled(true);

    this->tl->show();
    this->cw->show();
}

void MainWindow::openFile(){    
    QString fileName = QFileDialog::getOpenFileName(this,
	 tr("Open..."), "", tr("Text files (*.txt)"));
    if (!fileName.isEmpty()){
	this->closeFile();
	this->controller->openFile(fileName.toStdString());
    }

    this->ui->actionAdd_clip->setEnabled(true);

    if (this->tl->getCountClip()>0){
	this->tl->changeCurrentClip(0);
	this->tl->changeCurrentFrame(0);

	this->tl->checkFrame();
    }
    this->ui->actionSave->setEnabled(true);
    this->ui->actionSave_As->setEnabled(true);
    this->ui->actionCloseFile->setEnabled(true);

    this->tl->show();
    this->cw->show();

    view->refreshSceneView();
}

void MainWindow::saveFile(){
    string oldFile=this->model->getScene()->getFileName();

    if ( oldFile.empty() ){
	QString fileName = QFileDialog::getSaveFileName(this,tr("Save..."), "", tr("Text files (*.txt)"));
	if (!fileName.isEmpty()){
	    this->controller->saveFile(fileName.toStdString());
	    this->model->getScene()->setFileName(fileName.toStdString());
	}
    }else{
	this->controller->saveFile(oldFile);
    }

    this->ui->actionSave->setEnabled(true);
    this->ui->actionSave_As->setEnabled(true);
    this->ui->actionCloseFile->setEnabled(true);
}

void MainWindow::saveFileAs(){

    QString fileName = QFileDialog::getSaveFileName(this,tr("Save As..."), "", tr("Text files (*.txt)"));
    if (!fileName.isEmpty()){
	this->controller->saveFile(fileName.toStdString());
    }

    this->ui->actionSave->setEnabled(true);
    this->ui->actionSave_As->setEnabled(true);
    this->ui->actionCloseFile->setEnabled(true);
}
