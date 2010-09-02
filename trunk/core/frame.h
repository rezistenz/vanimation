#if !defined FRAME_H

#define FRAME_H

#include "defines.h"

using namespace std;

class Frame {
	public:
		Frame();
		Frame(TIME_TYPE nTime);
		~Frame();
		//Getters methods
		TIME_TYPE getTime();
		void setTime(TIME_TYPE nTime);
		//Setters methods
		//Others methods
		void draw();
	private:
		TIME_TYPE time;
};

#endif
