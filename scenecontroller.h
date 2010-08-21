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
                virtual void updateModel(UpdateModelCommand cmd);

                SceneModel* getSceneModel();
                void setSceneModel(SceneModel* model);
	private:
		SceneModel *model;
};

#endif
