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

    case GET_SHAPES_COUNT_FOR_FRAME:{
	    modelState.state=SHAPES_COUNT_FOR_FRAME;
	    int clipIndex=cmd.pointData.x;
	    int frameIndex=cmd.pointData.y;

	    Clip* clip=this->scene->getClip(clipIndex);
	    int shapesCount=clip->getShapesCountForFrame(frameIndex);

	    modelState.intData=shapesCount;
	}
	break;

    case GET_SHAPE_FOR_FRAME:{
	    modelState.state=SHAPE_FOR_FRAME;
	    int clipIndex=cmd.pointData.x;
	    int frameIndex=cmd.pointData.y;
	    int shapeIndex=cmd.intData;

	    Clip* clip=this->scene->getClip(clipIndex);
	    SceneShape sceneShape=clip->getShapeForFrame(frameIndex,shapeIndex);

	    modelState.sceneShapeData=sceneShape;
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

    case ADD_FRAME_TO_CLIP:{
	    //cmd.intData - index of clip
	    //cmd.timeData - time for frame
	    Clip* clip=this->scene->getClip(cmd.intData);
	    clip->addFrame(cmd.timeData);
	}
	break;

    case SET_SHAPES_COUNT_FOR_FRAME:{
	    int clipIndex=cmd.pointData.x;
	    int frameIndex=cmd.pointData.y;
	    int countShapes=cmd.intData;

	    Clip* clip=this->scene->getClip(clipIndex);
	    clip->setShapesCountForFrame(frameIndex,countShapes);
	}
	break;

    case SET_SHAPE_FOR_FRAME:{
	    int clipIndex=cmd.pointData.x;
	    int frameIndex=cmd.pointData.y;
	    int shapeIndex=cmd.intData;
	    SceneShape sceneShape=cmd.sceneShapeData;

	    Clip* clip=this->scene->getClip(clipIndex);
	    clip->setShapeForFrame(frameIndex,shapeIndex,sceneShape);
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

