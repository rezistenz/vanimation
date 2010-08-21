#if !defined CLIP_H

#define CLIP_H

#include "defines.h" 
#include "frame.h" 
#include <vector> 

using namespace std;

class Clip {
	public:
		Clip();
		~Clip();

		void addFrame();
		void addFrame(TIME_TYPE time);
		void delFrame(int index);
		int getFramesCount();
		void displayFrames();

		int moveFrameForward(int index); //return new index;
		int moveFrameBack(int index); //return new index;
		int moveFrameToTime(int index,TIME_TYPE time);

		void play(TIME_TYPE time);
		void stop();
		void pause();
	private:
		vector< Frame* > frames;
};

#endif
