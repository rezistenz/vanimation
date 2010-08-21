#include "consolesceneview.h"

using namespace std;

ConsoleSceneView::ConsoleSceneView(){

}

ConsoleSceneView::~ConsoleSceneView(){

}

void ConsoleSceneView::refreshConsoleSceneView(){

}

void ConsoleSceneView::run(){
    char ch=0;
    bool is_exit=false;

    while (!is_exit)
    {
        cout <<
                "\n'd' - отобразить всЁ"
                "\n'x' - выход\n"
                "\nВаш выбор:";
        cin >> ch;
        switch (ch)
        {
        case 'd': {
                StateModelCommand cmd;
                cmd.CMD=GET_MAX_TIME;
                SceneModel* model=this->getSceneModel();
                ModelState modelState=model->getStateModel(cmd);
                cout << "MAX_TIME "<< modelState.timeData<<endl;

            };
            break;
        case 'x': is_exit = true; break;
        default: cout << "\nНеизвестная команда";
        }
    }
}
