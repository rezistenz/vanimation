#ifndef QTSCENEVIEW_H
#define QTSCENEVIEW_H

#include "../core/sceneview.h"
#include "timelinewidget.h"
#include "canvaswidget.h"

class QtSceneView:public SceneView {
public:
    QtSceneView();
    QtSceneView(TimelineWidget *tl, CanvasWidget *cw);

    void setTimeLineWidget(TimelineWidget *tl);
    void setCanvasWidget(CanvasWidget *cw);

    void configureTimeLineAndCanvasWidget();
    void connectTimeLineAndCanvasWidget();

    int getShapesCountForFrame(int clipIndex, int frameIndex);
    SceneShape getShapeForFrame(int clipIndex, int frameIndex, int shapeIndex);

    void setDefaultCanvasWidget();

    void refreshSceneView();
private:
    TimelineWidget *timelineWidget;
    void refreshTimeline();

    CanvasWidget *canvasWidget;
    void refreshCanvasWidget();
};

#endif // QTSCENEVIEW_H
