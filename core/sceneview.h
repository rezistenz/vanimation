#if !defined SCENEVIEW_H

#define SCENEVIEW_H

#include "defines.h"

using namespace std;

class SceneModel;
class SceneController;

class SceneView {
	public:
		SceneView();
		~SceneView();

                SceneView(SceneModel *model);
		SceneView(SceneModel *model, SceneController *controller);
                virtual void refreshSceneView();

                SceneModel* getSceneModel();
                void setSceneModel(SceneModel* model);
                SceneController* getSceneController();
                void setSceneController(SceneController* controller);
	private:
		SceneModel *model;
		SceneController *controller;
};

#include "scenemodel.h"
#include "scenecontroller.h"

#endif
