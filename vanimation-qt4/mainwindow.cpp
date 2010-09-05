#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "timelinewidget.h"
#include "qtsceneview.h"
#include "qtsceneview.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tl=new TimelineWidget(this);
    //QVBoxLayout *vlayout=new QVBoxLayout(this);
    //vlayout->addWidget(tl);
    //this->setLayout(vlayout);;
    ui->verticalLayout->addWidget(tl);

    scene=new Scene();

    scene->addClip();
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

    model=new SceneModel();
    model->setScene(scene);
    view=new QtSceneView(tl);
    controller=new SceneController();

    view->setSceneController(controller);
    view->setSceneModel(model);
    controller->setSceneModel(model);
    model->setSceneView(view);

    view->refreshSceneView();
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
