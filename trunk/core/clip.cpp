#include "defines.h"
#include "clip.h"
#include <iostream>

#include "scene.h"

using namespace std;

Clip::Clip(){
//
}

Clip::~Clip(){
	while (!frames.empty()){
		delete frames.back();
		frames.pop_back();
	}
}

void Clip::addFrame(){
	TIME_TYPE newTime=0;
	if (frames.size()>0){
		newTime=frames.back()->getTime()+1;
	}
	assert(newTime<=Scene::getMaxTime());

	Frame* pframe=new Frame(newTime);
	frames.push_back(pframe);
}

void Clip::addFrame(TIME_TYPE nTime){
	assert(nTime<=Scene::getMaxTime());

	Frame* pframe=new Frame(nTime);
	
	vector<Frame*>::iterator it, insIter;
	bool found=false;
	for(it=frames.begin(); it!=frames.end(); it++){
		TIME_TYPE time=(*it)->getTime();
		if (nTime <= time){
			found=true;
			break;
		}
	}
	if (found) {
		insIter = frames.insert(it,pframe);
		for (it=insIter+1; it!=frames.end(); it++){
			TIME_TYPE prevTime=(*(it-1))->getTime();
			TIME_TYPE nextTime=(*it)->getTime();
			if (prevTime == nextTime){
				(*it)->setTime(nextTime+1);
				}
		}
	}else{
		frames.push_back(pframe);
	}
}

void Clip::delFrame(int index){
	frames.erase(frames.begin()+index);
}

int Clip::getFramesCount(){
	return frames.size();
}

TIME_TYPE Clip::getFrameTime(int index){
    Frame * frame=frames.at(index);
    return frame->getTime();
}

void Clip::displayFrames(){
	vector< Frame* >::iterator iter;
	int i=0;
	for (iter=frames.begin(); iter!=frames.end(); ++iter){
		TIME_TYPE time = (*iter)->getTime();
		cout << i << " "<< time <<" "<< (*iter) << endl;
		i++;
	}
}

int Clip::moveFrameForward(int index){
	TIME_TYPE prevTime=frames.at(index)->getTime();
	TIME_TYPE nextTime=frames.at(index+1)->getTime();
	
	frames.at(index)->setTime(prevTime+1);
	if ((prevTime+1)==nextTime){
		frames.at(index+1)->setTime(nextTime-1);
		
		Frame* pnextFrame;
		pnextFrame=frames.at(index+1);
		frames.at(index+1)=frames.at(index);
		frames.at(index)=pnextFrame;

		return index+1;
	}
	return index;
}

int Clip::moveFrameBack(int index){
	assert(index!=0);

	TIME_TYPE thisTime=frames.at(index)->getTime();
	TIME_TYPE prevTime=frames.at(index-1)->getTime();
	
	frames.at(index)->setTime(thisTime-1);
	if ((thisTime-1)==prevTime){
		frames.at(index-1)->setTime(prevTime+1);
		
		Frame* pprevFrame;
		pprevFrame=frames.at(index-1);
		frames.at(index-1)=frames.at(index);
		frames.at(index)=pprevFrame;
	
		return index-1;
	}
	return index;
}

void Clip::moveFrameToTime(int index,TIME_TYPE time){
	assert(time>=0 && time<=Scene::getMaxTime());
	
	bool found = false;
	vector<Frame*>::iterator iter,foundIter;
	TIME_TYPE frameTime;

	for(iter=frames.begin();iter!=frames.end();iter++){

		frameTime=(*iter)->getTime();

		if (time<=frameTime){

			foundIter=iter;
			found = true;

			break;
		}
	}
	
	Frame* pThisFrame=NULL;

	if (found){
		iter=frames.begin()+index;
		pThisFrame=*iter;

		pThisFrame->setTime(time);

		frames.erase(iter);

		if ((foundIter-iter)>0){
			--foundIter;
		}

		frames.insert(foundIter,pThisFrame);

		if (time==frameTime){
			cout<<"yes "<< (*foundIter) <<endl;
			for (iter=foundIter+1;iter!=frames.end();iter++){
				TIME_TYPE prevTime=(*(iter-1))->getTime();
				TIME_TYPE thisTime=(*iter)->getTime();

				if (prevTime==thisTime) {
					(*iter)->setTime(thisTime+1);
				}
			}
		}
	}else{
		iter=frames.begin()+index;
		pThisFrame=*iter;

		pThisFrame->setTime(time);

		frames.erase(iter);

		frames.push_back(pThisFrame);
	}

}

void Clip::play(TIME_TYPE time){
	assert(time>=0 && time<=Scene::getMaxTime());
	
	vector<Frame*>::iterator iter,foundIter=frames.end()-1;
	TIME_TYPE frameTime;

	for(iter=frames.begin();iter!=frames.end();iter++){
		frameTime=(*iter)->getTime();

		if (time<=frameTime){
			foundIter=iter;
			break;
		}
	}

	(*foundIter)->draw();
}

void Clip::stop(){
	
}

void Clip::pause(){
	
}

void Clip::setShapesCountForFrame(int frameIndex, int countShapes){
    Frame *frame=this->frames.at(frameIndex);
    frame->setShapesCount(countShapes);
}

void Clip::setShapeForFrame(int frameIndex, int shapeIndex, SceneShape sceneShape){
    Frame *frame=this->frames.at(frameIndex);
    SceneShape * frameShape=frame->getShape(shapeIndex);

    frameShape->x=sceneShape.x;
    frameShape->y=sceneShape.y;
    frameShape->width=sceneShape.width;
    frameShape->height=sceneShape.height;
    frameShape->type=sceneShape.type;
}

int Clip::getShapesCountForFrame(int frameIndex){
    Frame *frame=this->frames.at(frameIndex);
    int shapesCount=frame->getShapesCount();

    return shapesCount;
}

SceneShape Clip::getShapeForFrame(int frameIndex, int shapeIndex){
    Frame *frame=this->frames.at(frameIndex);
    SceneShape* frameShape=frame->getShape(shapeIndex);

    SceneShape sceneShape;
    sceneShape.x=frameShape->x;
    sceneShape.y=frameShape->y;
    sceneShape.width=frameShape->width;
    sceneShape.height=frameShape->height;
    sceneShape.type=frameShape->type;

    return sceneShape;
}
