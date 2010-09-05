#ifndef QTSCENEVIEW_H
#define QTSCENEVIEW_H

#include "../core/sceneview.h"
#include "timelinewidget.h"

class QtSceneView:public SceneView {
public:
    QtSceneView();
    QtSceneView(TimelineWidget *tl);

    void refreshSceneView();
private:
    TimelineWidget *timelineWidget;
    void refreshTimeline();
};

#endif // QTSCENEVIEW_H
