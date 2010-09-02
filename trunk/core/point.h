#if !defined POINT_H

#define POINT_H

#include "defines.h"

using namespace std;

class Point {
	public:
		//Getters methods
		int getX();
		int getY();
		//Setters methods
		void setX(int x);
		void setY(int y);
		//Others methods
		void moveTo(int x,int y);

		void draw();
	private:
		int x;
		int y;
};

#endif
