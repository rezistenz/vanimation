#if !defined CONSOLESCENEVIEW_H

#define CONSOLESCENEVIEW_H

#include "defines.h"
#include <iostream>
#include "sceneview.h"

using namespace std;

class ConsoleSceneView:public SceneView {
	public:
		ConsoleSceneView();
		~ConsoleSceneView();

                virtual void refreshConsoleSceneView();
                void run();
	private:

};

#endif
