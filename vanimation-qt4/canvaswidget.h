#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QtGui>
#include <list>
#include <iostream>
#include "../core/frame.h"
#include "../core/scenecontroller.h"

using namespace std;

/*
=================================================================

    Shape

=================================================================
*/


/*enum ShapeType {
    RECTANGLE,
    ELLIPSE
};
*/


class Shape: public QRect{
public:
    virtual void draw(QPainter &painter)=0;
    virtual bool selected(QPoint &point)=0;
    ShapeType getType();
protected:
    ShapeType type;
};

class Rectangle: public Shape{
public:
    Rectangle();

    void draw(QPainter &painter);
    bool selected(QPoint &point);
};

class Ellipse: public Shape{
public:
    Ellipse();

    void draw(QPainter &painter);
    bool selected(QPoint &point);
};


/*
=================================================================

    Canvas

=================================================================
*/

enum Operations{
    SELECT,
    DRAW_RECTANGLE,
    DRAW_ELLIPSE
};

class Canvas : public QWidget{
Q_OBJECT
public:
    Canvas(QWidget *parent = 0);
    ~Canvas();

    void setCanvasColor(QColor &color);
    int getShapesCount();
    SceneShape getShapeForScene(int index);
    void clearShapes();
    void addShapeFromScene(SceneShape sceneShape);
    void setSelectShapeIndex(int index);
private:
    QColor *canvasColor;
    list <Shape *> shapes;
    Shape *getShape(int);

    bool drawing;
    QPoint startPosMouse;
    QPoint endPosMouse;
    ShapeType currentShapeType;
    Operations currentOperation;
    int selectShapeIndex;
    bool dragging;
    QPoint dPointMouseShape;

    void checkShapesSelect(QPoint);
    bool changing;
    bool clickChangeAnchors(QPoint);

    Shape *createShape(ShapeType type,QRect rect);

    void paintEvent ( QPaintEvent * event );

    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);

    void drawCanvas(QPainter &painter);
    void drawShapes(QPainter &painter);
    void drawSelectedShape(QPainter &painter);
    void drawChangeAnchors(QPainter &painter);
public slots:
    void setCurrentOperation(Operations);
};


/*
=================================================================

    CanvasWidget

=================================================================
*/


class CanvasWidget : public QWidget
{
Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = 0);
    void setSceneController(SceneController *newController);
    void setSceneView(SceneView *newView);
private:
    int canvasWidth;
    int canvasHeigth;
    QScrollArea *scrollArea;
    Canvas *canvas;
    QFrame *buttonsPanel;

    int currentClip;
    int currentFrame;

    int oldCurrentClip;
    int oldCurrentFrame;

    void createView();

    int getValidFameIndex(int frameIndex);
    void saveStateChange();
    void loadState();

    SceneController *controller;
    SceneView *view;

signals:
    void changeCurrentOperation(Operations);
public slots:
    void setOperationSelect();
    void setOperationDrawRectangle();
    void setOperationDrawEllipse();

    void changeCurrentClip(int newCurrentClip);
    void changeCurrentFrame(int newCurrentFrame);
};

#endif // CANVASWIDGET_H
