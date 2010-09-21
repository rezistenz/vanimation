#if !defined FRAME_H

#define FRAME_H

#include "defines.h"
#include <vector>

using namespace std;

enum ShapeType {
    RECTANGLE,
    ELLIPSE
};

struct SceneShape{
    int x;
    int y;
    int width;
    int height;
    ShapeType type;
};

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

    int getShapesCount();
    void setShapesCount(int count);
    SceneShape * getShape(int index);
private:
    TIME_TYPE time;
    vector < SceneShape * > shapes;
};

#endif
