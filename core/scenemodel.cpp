#include "defines.h"
#include <iostream>
#include <stdlib.h>

#include "scenemodel.h"

using namespace std;

SceneModel::SceneModel(){
    //scene=new Scene();

    //SceneController* controller=new SceneController(this);
    //view=new SceneView(this,controller);
}

SceneModel::~SceneModel(){
       //delete scene;
       //delete view;
}

SceneModel::SceneModel(Scene *scene, SceneView *view){
    assert(scene!=NULL);
    assert(view!=NULL);

    this->scene=scene;
    this->view=view;
}

ModelState SceneModel::getStateModel(StateModelCommand cmd){
    ModelState modelState;
    switch(cmd.CMD){
    case GET_CLIP_COUNT:{
            modelState.state=CLIP_COUNT;
            modelState.intData=this->scene->getClipCount();
        }
        break;

    case GET_MAX_TIME:{
            modelState.state=MAX_TIME;
            modelState.timeData=this->scene->getMaxTime();
        }
        break;

    case GET_CLIP_FRAME_COUNT:{
	    modelState.state=CLIP_FRAME_COUNT;
	    Clip* clip=this->scene->getClip(cmd.intData);
	    modelState.intData=clip->getFramesCount();
	}
	break;

    case GET_CLIP_FRAME_TIME:{
	    modelState.state=CLIP_FRAME_TIME;
	    Clip* clip=this->scene->getClip(cmd.pointData.x);

	    modelState.timeData=clip->getFrameTime(cmd.pointData.y);
	}
	break;

    default:{
            cerr<<"ERROR! StateModelCommand not found."<<endl;
            exit(EXIT_FAILURE);
        }
        break;
   }
   return modelState;
}

void SceneModel::updateModel(UpdateModelCommand cmd){
    switch(cmd.CMD){
    case ADD_CLIP:{
            this->scene->addClip();
        }
        break;

    case DEL_CLIP:{
            this->scene->delClip(cmd.intData);
        }
        break;

    case PLAY_CLIP:{
            //this->scene->playClip(cmd.intData);
        }
        break;

    case PLAY_ALL_CLIPS:{
            //this->scene->playAllClip();
        }
        break;

    case SET_MAX_TIME:{
            this->scene->setMaxTime(cmd.intData);
        }
        break;

    default:{
            cerr<<"ERROR! UpdateModelCommand not found."<<endl;
            exit(EXIT_FAILURE);
        }
        break;
    }
    updateView();
}

void SceneModel::updateView(){
    this->view->refreshSceneView();
}

Scene* SceneModel::getScene(){
    return this->scene;
}

void SceneModel::setScene(Scene* scene){
    assert(scene!=NULL);

    this->scene=scene;
}

SceneView* SceneModel::getSceneView(){
    return this->view;
}

void SceneModel::setSceneView(SceneView* view){
    assert(view!=NULL);

    this->view=view;
}

