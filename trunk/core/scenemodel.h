#if !defined SCENEMODEL_H

#define SCENEMODEL_H

#include "defines.h"
#include "scene.h"

using namespace std;

//STATE MODEL COMMAND
enum StateModelCommands{
	GET_CLIP_COUNT,
	GET_MAX_TIME
};

struct StateModelCommand{
	StateModelCommands CMD;
	int intData;
	TIME_TYPE timeData;
};

//MODEL STATE
enum ModelStates{
	CLIP_COUNT,
	MAX_TIME
};

struct ModelState{
	ModelStates state;
	int intData;
	TIME_TYPE timeData;
};

//UPDATE MODEL COMMAND
enum UpdateModelCommands{
	ADD_CLIP,
	DEL_CLIP,
	PLAY_CLIP,
        PLAY_ALL_CLIPS,
        SET_MAX_TIME
};

struct UpdateModelCommand{
	UpdateModelCommands CMD;
	int intData;
	TIME_TYPE timeData;
};

class SceneView;

//SCENE MODEL
class SceneModel {
	public:
		SceneModel();
		~SceneModel();

		SceneModel(Scene *scene, SceneView *view);
                ModelState getStateModel(StateModelCommand cmd);
		void updateModel(UpdateModelCommand cmd);
		void updateView();

                Scene* getScene();
                void setScene(Scene* scene);
                SceneView* getSceneView();
                void setSceneView(SceneView* view);
	private:
		Scene *scene;
		SceneView *view;
};

#include "sceneview.h"

#endif
