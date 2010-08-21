#include "defines.h"
#include <iostream>
#include "scenecontroller.h"

using namespace std;

SceneController::SceneController(){

}

SceneController::SceneController(SceneModel *model){
	this->model=model;
}

SceneController::~SceneController(){

}

void SceneController::updateModel(UpdateModelCommand cmd){
/*
if (cmd.CMD==ADD_CLIP){cout<<"ADD_CLIP controller"<<endl;}
if (cmd.CMD==DEL_CLIP){cout<<"DEL_CLIP controller"<<endl;}
*/
model->updateModel(cmd);
}

SceneModel* SceneController::getSceneModel(){
    return this->model;
}

void SceneController::setSceneModel(SceneModel* model){
    assert(model!=NULL);

    this->model=model;
}
