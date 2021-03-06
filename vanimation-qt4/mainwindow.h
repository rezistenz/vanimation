#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "timelinewidget.h"
#include "../core/sceneview.h"
#include "qtsceneview.h"
#include "qtscenecontroller.h"
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
    QtSceneController *controller;
public slots:
    void exit();
    void closeFile();
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
};

#endif // MAINWINDOW_H
