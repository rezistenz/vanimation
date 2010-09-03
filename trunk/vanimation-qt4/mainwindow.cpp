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

    scene=new Scene();
    model=new SceneModel();
    model->setScene(scene);
    view=new QtSceneView(tl);
    controller=new SceneController();

    view->setSceneController(controller);
    view->setSceneModel(model);
    controller->setSceneModel(model);
    model->setSceneView(view);

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
