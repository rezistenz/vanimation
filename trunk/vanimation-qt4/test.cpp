
class Parent{
public:
    Parent(){

    };
    ~Parent(){

    };
    Parent(int i){

    };
    Parent(float f){

    };
};

class Child:public Parent{
public:
    Child():Parent(){

    };
};

int main(){
Parent p;
Child c;
    return 0;
}
