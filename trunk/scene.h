#if !defined SCENE_H

#define SCENE_H

#include "defines.h"

#include <vector>
#include "clip.h"

using namespace std;

const TIME_TYPE defaultMaxTime=50;

class Scene {
	public:
		Scene();
		Scene(TIME_TYPE mTime);	
		~Scene();
		
		void addClip();
		void addClips(int clCount);
		void delClip(int index);
		int getClipCount();	

		static TIME_TYPE getMaxTime();
		static void setMaxTime(TIME_TYPE mTime);
		static void addMaxTime();
		static void subMaxTime();
		Clip* getClip(int index);
	private:
		static TIME_TYPE maxTime;
		vector< Clip* > clips;
};

#endif
