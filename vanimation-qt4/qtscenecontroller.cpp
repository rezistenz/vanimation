#include "qtscenecontroller.h"

using namespace std;

QtSceneController::QtSceneController(){

}

void QtSceneController::addClip(){
    UpdateModelCommand cmd;
    cmd.CMD=ADD_CLIP;

    updateModel(cmd);
}

void QtSceneController::delClip(int clipIndex){
    UpdateModelCommand cmd;
    cmd.CMD=DEL_CLIP;
    cmd.intData=clipIndex;

    updateModel(cmd);
}

void QtSceneController::addFrameToClip(int clipIndex, TIME_TYPE time){
    UpdateModelCommand cmd;
    cmd.CMD=ADD_FRAME_TO_CLIP;
    cmd.intData=clipIndex;
    cmd.timeData=time;

    updateModel(cmd);
}

void QtSceneController::delFrameFromClip(int clipIndex, int frameIndex){
    UpdateModelCommand cmd;
    cmd.CMD=DEL_FRAME_FROM_CLIP;
    cmd.pointData.x=clipIndex;
    cmd.pointData.y=frameIndex;

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

void QtSceneController::closeFile(){
    UpdateModelCommand cmd;
    cmd.CMD=CLOSE_FILE;

    updateModel(cmd);
}

void QtSceneController::openFile(const std::string& fileName){
    UpdateModelCommand cmd;
    cmd.CMD=OPEN_FILE;
    cmd.stringData=fileName;

    updateModel(cmd);
}

void QtSceneController::saveFile(const std::string& fileName){
    UpdateModelCommand cmd;
    cmd.CMD=SAVE_FILE;
    cmd.stringData=fileName;

    updateModel(cmd);
}
