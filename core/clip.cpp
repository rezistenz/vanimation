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

int Clip::moveFrameToTime(int index,TIME_TYPE time){
	assert(time>=0 && time<=Scene::getMaxTime());
	
	bool found = false;
	vector<Frame*>::iterator iter,foundIter;
	TIME_TYPE frameTime;
	//цикл по всем фреймам
	for(iter=frames.begin();iter!=frames.end();iter++){
		//получить время i-го фрейма сохранить в переменной frameTime
		frameTime=(*iter)->getTime();
		//если time <= frameTime то
		if (time<=frameTime){
			//запомнить i фрейма
			foundIter=iter;
			found = true;
			//прервать цикл
			break;
		}//конец если
	}//конец цикла
	
	Frame* pThisFrame=NULL;
	//если found то 
	if (found){
		//перместить фрейм index в позицию i
		//запомнить ссылку на фрейм в позиции index  в переменной pThisFame
		iter=frames.begin()+index;
		pThisFrame=*iter;
		//задать время для перемещаемого фрейма как time
		pThisFrame->setTime(time);
		//удалить фрейим из позиции index
		frames.erase(iter);
		//cout<<(foundIter-iter)<<endl;
		if ((foundIter-iter)>0){
			--foundIter;
		}
		//вставить pThisFrame в позицию i
		frames.insert(foundIter,pThisFrame);
		//если time==frameTime то
		if (time==frameTime){
			cout<<"yes "<< (*foundIter) <<endl;
			//пересчитать время для всех фреймов начиная с i+1
			//цикл по фреймам начиная с позиции it=i
			for (iter=foundIter+1;iter!=frames.end();iter++){
				TIME_TYPE prevTime=(*(iter-1))->getTime();
				TIME_TYPE thisTime=(*iter)->getTime();
				//если prevTime==thisTime то
				if (prevTime==thisTime) {
					//установить время фрейма it в thisTime+1
					(*iter)->setTime(thisTime+1);
				}//конец если
			}//конец цикла
		}//конец если
	}else{//иначе
		//переместить фрейм index в конец
		//запомнить ссылку на фрейм в позиции index  в переменной pThisFame
		iter=frames.begin()+index;
		pThisFrame=*iter;
		//задать время для перемещаемого фрейма как time
		pThisFrame->setTime(time);
		//удалить фрейим из позиции index
		frames.erase(iter);
		//вставить pThisFrame в конец 
		frames.push_back(pThisFrame);
	}//конец если

}

void Clip::play(TIME_TYPE time){
	assert(time>=0 && time<=Scene::getMaxTime());
	
	vector<Frame*>::iterator iter,foundIter=frames.end()-1;
	TIME_TYPE frameTime;
	//цикл по всем фреймам
	for(iter=frames.begin();iter!=frames.end();iter++){
		//получить время i-го фрейма сохранить в переменной frameTime
		frameTime=(*iter)->getTime();
		//если time <= frameTime то
		if (time<=frameTime){
			//запомнить i фрейма
			foundIter=iter;
			//прервать цикл
			break;
		}//конец если
	}//конец цикла
	//draw frame
	(*foundIter)->draw();
}

void Clip::stop(){
	
}

void Clip::pause(){
	
}

