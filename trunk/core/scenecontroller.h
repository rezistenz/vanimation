#if !defined SCENECONTROLLER_H

#define SCENECONTROLLER_H

#include "defines.h"
#include "scenemodel.h"

using namespace std;

class SceneController {
public:
	SceneController();
	SceneController(SceneModel *model);
	~SceneController();
	SceneModel* getSceneModel();
	void setSceneModel(SceneModel* model);

	virtual void addClip()=0;
	virtual void addFrameToClip(int clipIndex, TIME_TYPE time)=0;
	virtual void setShapesCountForFrame(int clipIndex, int frameIndex, int newShapesCount)=0;
	virtual void setShapeForFrame(int clipIndex, int frameIndex, int shapeIndex, SceneShape sceneShape)=0;
protected:
	void updateModel(UpdateModelCommand cmd);
private:
	SceneModel *model;
};

#endif
