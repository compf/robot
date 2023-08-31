typedef uint8_t byte;
#include <X11/extensions/XTest.h>
#include <X11/Xutil.h>
#include <cstring>
#include <unistd.h>
Display *display;
Robot::Robot()
{
  display = XOpenDisplay(NULL);
  init_keycodes();
}
void Robot::init_keycodes()
{
  KEY_NUM = XKeysymToKeycode(display, XStringToKeysym("0"));
  ;
  KEY_UP = XKeysymToKeycode(display, XK_Up);
  KEY_LEFT = XKeysymToKeycode(display, XK_Left);

  KEY_DOWN = XKeysymToKeycode(display, XK_Down);

  KEY_RIGHT = XKeysymToKeycode(display, XK_Right);

  KEY_ALPH = XKeysymToKeycode(display, XK_A);

  KEY_ALT = XKeysymToKeycode(display, XK_Alt_L);

  KEY_CTRL = XKeysymToKeycode(display, XK_Control_L);

  KEY_SHIFT = XKeysymToKeycode(display, XK_Shift_L);
  KEY_ENTER = XKeysymToKeycode(display, XK_Return);
  KEY_ESC = XKeysymToKeycode(display, XK_Escape);

  LeftMouseButton=1;
  MiddleMouseButton=2;
  RightMouseButton=3;
  MouseWheelUp=4;
  MouseWheelDown=5;
}
int Robot::mouseMove(int x, int y, unsigned int delay)
{
  XTestFakeMotionEvent(display, -1, x, y, delay);
  XFlush(display);
  return 0;
}
int Robot::pressedMouseButton()
{
  Window root = DefaultRootWindow(display);
  Window qr, qc;
  int gx, gy, lx, ly;
  uint mask;
  XQueryPointer(display, root, &qr, &qc, &gx, &gy, &lx, &ly, &mask);
  //std::cout << "Mask " << mask << std::endl;
  //std::cout<<"Truth "<<((mask & Button1Mask) == Button1Mask)<<std::endl;
  //std::cout<<"bn3 "<<((mask & Button3Mask)==Button3Mask)<<std::endl;
  //std::cout<<"bn4 "<<( Button3Mask)<<std::endl;
  if ((mask & Button1Mask) == Button1Mask)
  {
    return LeftMouseButton;
  }
  else if ((mask & Button2Mask) == Button2Mask)
  {
    return MiddleMouseButton;
  }
  else if ((mask & Button3Mask) == Button3Mask)
  {
    return RightMouseButton;
  }
  else if ((mask & Button4Mask) == Button4Mask)
  {
    return  MouseWheelUp;
  }
    else if ((mask & Button5Mask) == Button5Mask)
  {
    return  MouseWheelDown;
  }
  else
  {
    return 0;
  }
}

int Robot::mouseClick(int button, unsigned int delay)
{
  XTestFakeButtonEvent(display, button, true, delay);
  XFlush(display);
  XTestFakeButtonEvent(display, button, false, delay);
  XFlush(display);
  return 0;
}
unsigned long Robot::translateChar(char digit_or_letter)
{
  int keycode;
  if (digit_or_letter >= 'a' && digit_or_letter <= 'z')
  {
    keycode = digit_or_letter - 'a' + XK_A;
  }
  else if (digit_or_letter >= 'A' && digit_or_letter <= 'Z')
  {
    keycode = digit_or_letter - 'A' + XK_A;
  }
  else if (digit_or_letter >= '0' && digit_or_letter <= '9')
  {
    keycode = digit_or_letter - '0' + XK_0;
  }
  return XKeysymToKeycode(display,keycode);
}

int Robot::keyPress(std::vector<unsigned int> keys)
{
  
  for (auto key : keys)
  {
    XTestFakeKeyEvent(display, key, true, 5);
    XFlush(display);
  }
  //usleep(1000);
  for (auto key : keys)
  {
    XTestFakeKeyEvent(display, key, false, 5);
    XFlush(display);
  }
  return 0;
}
void Robot::sleep(unsigned int ms)
{
  struct timespec ts;
  ts.tv_sec = ms / 1000;
  ts.tv_nsec = (ms % 1000) * 1000000;
  nanosleep(&ts, NULL);
}

Robot::~Robot()
{

  XCloseDisplay(display);
  display = nullptr;
}
int Robot::screenshot(std::vector<uint8_t> &pixels, int &width, int &height, int &endianess)
{
  Window root = DefaultRootWindow(display);

  XWindowAttributes attributes = {0};
  XGetWindowAttributes(display, root, &attributes);
  width = attributes.width;
  height = attributes.height;
  return this->screenshot(pixels, 0, 0, width, height, endianess);
}
int Robot::screenshot(std::vector<uint8_t> &pixels, int x, int y, int width, int height, int &endianess)
{
  Window root = DefaultRootWindow(display);

  auto img = XGetImage(display, root, x, y, width, height, AllPlanes, ZPixmap);
  endianess = img->byte_order;
  int size = width * height * img->bits_per_pixel / 8;
  pixels.resize(size);
  std::copy(img->data, img->data + size, pixels.begin());
  XDestroyImage(img);
  return 0;
}

int Robot::pixelColorCursor(uint8_t &r, uint8_t &g, uint8_t &b)
{

  int w, h, bpp;
  std::vector<uint8_t> pixels;
  int x, y;
  this->mousePos(x, y);
  this->screenshot(pixels, x, y, 1, 1, bpp);
  if (LSBFirst)
  {
    r = pixels[0];
    g = pixels[1];
    b = pixels[2];
  }
  else if (MSBFirst)
  {
    r = pixels[2];
    g = pixels[1];
    b = pixels[0];
  }

  return 0;
}
int Robot::mousePos(int &x, int &y)
{
  Window root = DefaultRootWindow(display);
  Window qr, qc;
  int gx, gy, lx, ly;
  uint mask;
  XQueryPointer(display, root, &qr, &qc, &gx, &gy, &lx, &ly, &mask);
  x = gx;
  y = gy;
  return 0;
}