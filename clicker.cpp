#include "Robot.cpp"
#include <cstdlib>
int main(int argc,char** argv){
    Robot rob;
    bool on=true;
    bool released=true;
    if(argc<2){
        return 0;
    }
    int rate=std::atoi(argv[1]);
    while(true){
        int btn=rob.pressedMouseButton();
        if(on)
            rob.mouseClick(rob.LeftMouseButton);
        if(released  &&btn==rob.RightMouseButton){
            on=!on;
            released=false;
        }
           
        else if(!released && btn!=rob.RightMouseButton)
            released=true;
       
        rob.sleep(rate);
    }
}
