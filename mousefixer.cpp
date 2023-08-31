#include "Robot.hpp"
#include <thread>
#include <chrono>
#include <iostream>
//g++ mousefixer.cpp Robot.cpp  -lX11 -lXtst  -o mousefixer.a
int main(int argc,char** argv)
{
    bool fixing = false;
    bool noclick = true;
    unsigned int wait_time=250;
    if(argc>1){
        wait_time=std::atoi(argv[1]);
    }
    int y;
    Robot rob;
    while (true)
    {
        int btn = rob.pressedMouseButton();
        if (btn==0)
        {
            noclick=true;
           
        }

        //std::cout<<btn<<std::endl;
        if (btn == rob.RightMouseButton && !fixing  && noclick)
        {
            int x_dummy;
            rob.mousePos(x_dummy, y);
            fixing = true;
            noclick=false;
            //std::cout << "fixing" << std::endl;
        }

        else if (btn == rob.RightMouseButton && fixing && noclick)
        {
            //estd::cout << "disable" << std::endl;
            fixing = false;
            noclick = false;
        }
        else if (fixing)
        {

            int x;
            int y_dummy;
            rob.mousePos(x, y_dummy);
            rob.mouseMove(x, y, 0);
        }
		rob.sleep(wait_time);

    }
}