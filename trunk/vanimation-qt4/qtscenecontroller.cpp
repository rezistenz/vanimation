#include "qtscenecontroller.h"

using namespace std;

QtSceneController::QtSceneController(){

}

void QtSceneController::addClip(){
    UpdateModelCommand cmd;
    cmd.CMD=ADD_CLIP;

    updateModel(cmd);
}

void QtSceneController::addFrameToClip(int clipIndex, TIME_TYPE time){
    UpdateModelCommand cmd;
    cmd.CMD=ADD_FRAME_TO_CLIP;
    cmd.intData=clipIndex;
    cmd.timeData=time;

    updateModel(cmd);
}
