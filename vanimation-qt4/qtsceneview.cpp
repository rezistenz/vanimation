#include "qtsceneview.h"

QtSceneView::QtSceneView(){

}

QtSceneView::QtSceneView(TimelineWidget *tl)
{
    this->timelineWidget=tl;
}

void QtSceneView::refreshSceneView(){

    StateModelCommand cmd;
    cmd.CMD=GET_CLIP_COUNT;

    ModelState state;
    state=this->getSceneModel()->getStateModel(cmd);
    if (state.state==CLIP_COUNT){
	//timelineWidget->setClipCount(state.intData);
    }

}
