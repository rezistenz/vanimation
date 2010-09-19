#if !defined QTSCENECONTROLLER_H

#define QTSCENECONTROLLER_H

#include "../core/scenecontroller.h"

using namespace std;

class QtSceneController: public SceneController {
public:
    QtSceneController();
    void addClip();
    void addFrameToClip(int clipIndex, TIME_TYPE time);
};

#endif
