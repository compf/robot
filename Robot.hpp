#pragma once
#include<cstdint>
#include<vector>
#include<vector>

class Robot{
    public:
    Robot();
    int mouseMove(int x,int y,unsigned int delay=0);
    int mouseClick(int button,unsigned int delay=0);
    int keyPress(unsigned int key);
    int keyPress(std::vector<unsigned int> keys);
    int screenshot(std::vector<uint8_t>& pixels,int& width,int& height,int& endianess);
    int screenshot(std::vector<uint8_t>& pixels,int x,int y,int width,int height,int& endianess);
    int mousePos(int& x,int &y);
    void sleep(unsigned int ms);
	int pressedMouseButton();
    unsigned int KEY_NUM;
    unsigned int KEY_UP;
    unsigned int KEY_LEFT;
    unsigned int KEY_DOWN;
    unsigned int KEY_RIGHT;
    unsigned int KEY_CTRL;
    unsigned int KEY_SHIFT;
    unsigned int KEY_ALT;
    unsigned int KEY_ALPH;
    unsigned int KEY_ENTER;
    unsigned int KEY_ESC;
    unsigned int LeftMouseButton,MiddleMouseButton,RightMouseButton,MouseWheelUp,MouseWheelDown;
    int pixelColorCursor(uint8_t& r,uint8_t& g,uint8_t&b);
    unsigned long translateChar(char digit_or_letter);
    ~Robot();
    private:
     void init_keycodes();
   
   


};