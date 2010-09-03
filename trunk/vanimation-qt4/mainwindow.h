#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "timelinewidget.h"
#include "../core/sceneview.h"

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

    Scene *scene;

    SceneModel *model;
    SceneView *view;
    SceneController *controller;
};

#endif // MAINWINDOW_H
