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
    view=new QtSceneView(tl);
    controller=new QtSceneController();

    view->setSceneController(controller);
    view->setSceneModel(model);
    controller->setSceneModel(model);
    model->setSceneView(view);

    //view->refreshSceneView();

    controller->addClip();
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


}

MainWindow::~MainWindow()
{
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
