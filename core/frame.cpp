#include "defines.h"
#include "frame.h"
#include <iostream>

using namespace std;


Frame::Frame(){
	cout<<"new frame "<<this<<endl;
	time=0;
}

Frame::Frame(TIME_TYPE nTime){
	cout<<"new frame with time "<<nTime<<" "<<this<<endl;
	time=nTime;
}

Frame::~Frame(){
	cout<<"del frame "<<this<<endl;
	while (!shapes.empty()){
		delete shapes.back();
		shapes.pop_back();
	}
}		

TIME_TYPE Frame::getTime(){
	return time;
}

void Frame::setTime(TIME_TYPE nTime){
	time=nTime;
	}

void Frame::draw(){
	cout<<"draw "<<this<<" "<<time<<endl;
}

int Frame::getShapesCount(){
    return shapes.size();
}

void Frame::setShapesCount(int count){
    int oldCount=shapes.size();
    int newCount=count;
    int dCount=newCount-oldCount;

    if (dCount>0){
	for(int i=0;i<dCount;i++){
	    SceneShape *shape=new SceneShape();
	    shapes.push_back(shape);
	}
    }else{
	dCount*=(-1);
	for(int i=0;i<dCount;i++){
	    SceneShape *shape=shapes.back();
	    delete shape;
	    shapes.pop_back();
	}
    }
}

SceneShape * Frame::getShape(int index){
    SceneShape * shape=shapes.at(index);
    return shape;
}
