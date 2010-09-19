#include "qtsceneview.h"
#include <iostream>

using namespace std;

QtSceneView::QtSceneView(){

}

QtSceneView::QtSceneView(TimelineWidget *tl)
{
    this->timelineWidget=tl;
}

void QtSceneView::refreshTimeline(){
    StateModelCommand cmd;
    cmd.CMD=GET_CLIP_COUNT;

    ModelState state;
    state=this->getSceneModel()->getStateModel(cmd);
    int newCountClip=state.intData;
    int oldCountClip=this->timelineWidget->getCountClip();

    if(newCountClip>oldCountClip){
	int count=newCountClip-oldCountClip;
	for(int i=0;i<count;i++){
	    this->timelineWidget->addClip();
	}
    }else{
	int count=oldCountClip-newCountClip;
	for(int i=0;i<count;i++){
	    this->timelineWidget->delClip();
	}
    }

    //reconfigure clips
    for (int indexClip=0;indexClip<newCountClip;indexClip++){
	//get count frames for scene clip
	cmd.CMD=GET_CLIP_FRAME_COUNT;
	//for i-clip
	cmd.intData=indexClip;
	state=this->getSceneModel()->getStateModel(cmd);
	int countFrames=state.intData;
	//set count frames in visual clip
	this->timelineWidget->setClipCountFrames(indexClip,countFrames);

	//get max time scene
	cmd.CMD=GET_MAX_TIME;
	state=this->getSceneModel()->getStateModel(cmd);
	TIME_TYPE maxTime=state.timeData;
	//set maxtime for visual clip
	this->timelineWidget->setMaxTimeClip(indexClip,maxTime);

	//compare clip frames
	this->timelineWidget->clearClipFameTimes(indexClip);
	for(int indexFrame=0;indexFrame<countFrames;indexFrame++){
	    //get time of fames from scene clip
	    cmd.CMD=GET_CLIP_FRAME_TIME;
	    //index of clip in scene
	    cmd.pointData.x=indexClip;
	    //index of frame in clip
	    cmd.pointData.y=indexFrame;

	    state=this->getSceneModel()->getStateModel(cmd);
	    TIME_TYPE timeFrame=state.timeData;

	    //set time of frams for visual clip
	    this->timelineWidget->addClipFrameTime(indexClip,timeFrame);    
	}	
    }

    this->timelineWidget->adjustSizeClips();
}

void QtSceneView::refreshSceneView(){
    refreshTimeline();
}
