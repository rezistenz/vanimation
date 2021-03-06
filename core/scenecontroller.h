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
	virtual void delClip(int clipIndex)=0;

	virtual void addFrameToClip(int clipIndex, TIME_TYPE time)=0;
	virtual void delFrameFromClip(int clipIndex, int frameIndex)=0;


	virtual void setShapesCountForFrame(int clipIndex, int frameIndex, int newShapesCount)=0;
	virtual void setShapeForFrame(int clipIndex, int frameIndex, int shapeIndex, SceneShape sceneShape)=0;

	virtual void closeFile()=0;
	virtual void openFile(const std::string& fileName)=0;
	virtual void saveFile(const std::string& fileName)=0;
protected:
	void updateModel(UpdateModelCommand cmd);
private:
	SceneModel *model;
};

#endif
