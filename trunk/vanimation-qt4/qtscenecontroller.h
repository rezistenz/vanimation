#if !defined QTSCENECONTROLLER_H

#define QTSCENECONTROLLER_H

#include "../core/scenecontroller.h"

using namespace std;

class QtSceneController: public SceneController {
public:
    QtSceneController();

    void addClip();
    void delClip(int clipIndex);

    void addFrameToClip(int clipIndex, TIME_TYPE time);
    void delFrameFromClip(int clipIndex, int frameIndex);

    void setShapesCountForFrame(int clipIndex, int frameIndex, int newShapesCount);
    void setShapeForFrame(int clipIndex, int frameIndex, int shapeIndex, SceneShape sceneShape);

    void closeFile();
    void openFile(const std::string& fileName);
    void saveFile(const std::string& fileName);
};

#endif
