#if !defined SCENEMODEL_H

#define SCENEMODEL_H

#include "defines.h"
#include "scene.h"

using namespace std;

//STATE MODEL COMMAND
enum StateModelCommands{
	GET_CLIP_COUNT,
	GET_MAX_TIME,
	GET_CLIP_FRAME_COUNT,
	GET_CLIP_FRAME_TIME,
	GET_SHAPES_COUNT_FOR_FRAME,
	GET_SHAPE_FOR_FRAME
};

struct PointData{
    int x;
    int y;
};

struct StateModelCommand{
	StateModelCommands CMD;
	int intData;
	TIME_TYPE timeData;
	PointData pointData;
};

//MODEL STATE
enum ModelStates{
	CLIP_COUNT,
	MAX_TIME,
	CLIP_FRAME_COUNT,
	CLIP_FRAME_TIME,
	SHAPES_COUNT_FOR_FRAME,
	SHAPE_FOR_FRAME
};

struct ModelState{
	ModelStates state;
	int intData;
	TIME_TYPE timeData;
	SceneShape sceneShapeData;
};

//UPDATE MODEL COMMAND
enum UpdateModelCommands{
	ADD_CLIP,
	DEL_CLIP,

	ADD_FRAME_TO_CLIP,
	DEL_FRAME_FROM_CLIP,

	PLAY_CLIP,
        PLAY_ALL_CLIPS,
	SET_MAX_TIME,

	SET_SHAPES_COUNT_FOR_FRAME,
	SET_SHAPE_FOR_FRAME
};

struct UpdateModelCommand{
	UpdateModelCommands CMD;
	int intData;
	TIME_TYPE timeData;
	PointData pointData;
	SceneShape sceneShapeData;
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
