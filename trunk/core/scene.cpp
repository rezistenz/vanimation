#include "scene.h"
#include "clip.h"
#include <iostream>

using namespace std;

TIME_TYPE Scene::maxTime=defaultMaxTime;

Scene::Scene(){
	//
}

Scene::Scene(TIME_TYPE mTime){
	Scene::maxTime=mTime;
}

Scene::~Scene(){
	while (!clips.empty()){
		delete clips.back();
		clips.pop_back();
	}
}

void Scene::clear(){
    while (!clips.empty()){
	    delete clips.back();
	    clips.pop_back();
    }

    this->fileName.clear();
}

void Scene::addClip(){
	Clip* pclip=new Clip();
	clips.push_back(pclip);
}

void Scene::addClips(int clCount){
	for (int i=0;i<clCount;i++){
		addClip();
	}
}

void Scene::delClip(int index){
	clips.erase(clips.begin()+index);
}


int Scene::getClipCount(){
	return clips.size();
}
		
Clip* Scene::getClip(int index){
	return clips.at(index);
}

TIME_TYPE Scene::getMaxTime(){
	return Scene::maxTime;
}

void Scene::setMaxTime(TIME_TYPE mTime){
    Scene::maxTime=mTime;
}

void Scene::saveToFile(string fileName){
    ofstream file;
    file.open(fileName.c_str());

    file<<this->getMaxTime()<<endl;
    int clipsCount=0;
    clipsCount=this->getClipCount();
    file<<clipsCount<<endl;

    for(int i=0; i<clipsCount; i++){
	Clip* clip=this->getClip(i);
	int framesCount=clip->getFramesCount();
	file<<framesCount<<endl;

	for(int j=0; j<framesCount; j++){
	    int frameTime=clip->getFrameTime(j);
	    file<<frameTime<<endl;

	    int shapesCount=clip->getShapesCountForFrame(j);
	    file<<shapesCount<<endl;
	    for(int k=0; k<shapesCount; k++){
		SceneShape shape=clip->getShapeForFrame(j,k);

		ShapeType type=shape.type;
		int x=shape.x;
		int y=shape.y;
		int width=shape.width;
		int height=shape.height;

		file<<type<<endl;
		file<<x<<endl;
		file<<y<<endl;
		file<<width<<endl;
		file<<height<<endl;
	    }
	}
    }

    file.close();
}

void Scene::loadFromFile(string fileName){
    this->clear();

    ifstream file;
    file.open(fileName.c_str());


    file>>this->maxTime;
    int clipsCount=0;
    file>>clipsCount;

    for(int i=0; i<clipsCount; i++){
	this->addClip();
	Clip* clip=this->getClip(i);

	int framesCount=0;
	file>>framesCount;

	for(int j=0; j<framesCount; j++){
	    int frameTime=0;
	    file>>frameTime;

	    clip->addFrame(frameTime);

	    int shapesCount=0;
	    file>>shapesCount;

	    clip->setShapesCountForFrame(j,shapesCount);

	    for(int k=0; k<shapesCount; k++){
		SceneShape shape;
		int type=RECTANGLE;
		int x=0;
		int y=0;
		int width=0;
		int height=0;

		file>>type;
		file>>x;
		file>>y;
		file>>width;
		file>>height;

		shape.type=static_cast<ShapeType>(type);
		shape.x=x;
		shape.y=y;
		shape.width=width;
		shape.height=height;

		clip->setShapeForFrame(j,k,shape);
	    }
	}
    }

    file.close();

    this->setFileName(fileName);
}

const string& Scene::getFileName(){
    return this->fileName;
}

void Scene::setFileName(const string& newFileName){
    this->fileName=newFileName;
}
