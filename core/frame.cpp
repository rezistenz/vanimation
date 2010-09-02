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
