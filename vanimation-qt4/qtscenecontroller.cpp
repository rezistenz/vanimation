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

void QtSceneController::setShapesCountForFrame(int clipIndex, int frameIndex, int newShapesCount){
    UpdateModelCommand cmd;
    cmd.CMD=SET_SHAPES_COUNT_FOR_FRAME;
    cmd.pointData.x=clipIndex;
    cmd.pointData.y=frameIndex;
    cmd.intData=newShapesCount;

    updateModel(cmd);
}

void QtSceneController::setShapeForFrame(int clipIndex, int frameIndex, int shapeIndex, SceneShape sceneShape){
    UpdateModelCommand cmd;
    cmd.CMD=SET_SHAPE_FOR_FRAME;
    cmd.pointData.x=clipIndex;
    cmd.pointData.y=frameIndex;
    cmd.intData=shapeIndex;
    cmd.sceneShapeData=sceneShape;

    updateModel(cmd);
}
