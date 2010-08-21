#include "scenemodel.h"
#include "consolesceneview.h"

using namespace std;

int main(int argc, char** argv){
	/*Scene scene;
	
	scene.addClips(10);
	Clip* pclip=scene.getClip(3);
	
	pclip->addFrame(1); //0
	pclip->addFrame(2); //1
	pclip->addFrame(5); //2
	pclip->addFrame(7);
	pclip->addFrame(8);
	pclip->addFrame(9);
	pclip->addFrame(10);

	//pclip->moveFrameToTime(6,2);
	//pclip->moveFrameToTime(2,8);
	//pclip->moveFrameToTime(2,11);

	
	pclip->displayFrames();
	for(int i=0; i<12;i++){
		pclip->play(i);
	}*/

        SceneModel *model=new SceneModel();
        Scene *scene=new Scene();

        model->setScene(scene);

        ConsoleSceneView *view=new ConsoleSceneView();
        model->setSceneView(view);
        view->run();

	return 0;
}
