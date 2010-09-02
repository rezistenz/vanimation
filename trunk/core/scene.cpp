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
