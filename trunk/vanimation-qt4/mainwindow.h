#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "timelinewidget.h"
#include "../core/sceneview.h"
#include "qtsceneview.h"
#include "canvaswidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    TimelineWidget *tl;
    CanvasWidget *cw;

    Scene *scene;

    SceneModel *model;
    QtSceneView *view;
    SceneController *controller;
};

#endif // MAINWINDOW_H
