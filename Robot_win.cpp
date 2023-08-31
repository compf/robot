#include <Windows.h>

int Robot::mouseMove(int x, int y, unsigned int delay)
{
  Sleep(delay);
  SetCursorPos(x, y);
  return 0;
}

int Robot::keyPress(std::vector<unsigned int> keys)
{
  INPUT *allInputs = new INPUT[2 * keys.size()];
  int index = 0;
  for (; index < keys.size(); index++)
  {
    auto inp = INPUT();
    inp.type = INPUT_KEYBOARD;
    inp.ki.wVk = keys[index];
    inp.ki.time = 0;

    allInputs[index] = inp;
  }
  for (int i = 0; i < keys.size(); i++)
  {
    auto inp = INPUT();
    inp.type = INPUT_KEYBOARD;
    inp.ki.time = 0;
    inp.ki.wVk = keys[i];
    inp.ki.dwFlags = KEYEVENTF_KEYUP;
    allInputs[index++] = inp;
  }
  SendInput(2 * keys.size(), allInputs, sizeof(INPUT));
  ZeroMemory(allInputs, sizeof(INPUT) * keys.size() * 2);

  return 0;
}
int Robot::mouseClick(int button, unsigned int delay)
{
  INPUT inputs[2];
  inputs[0].type = INPUT_MOUSE;
  inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
  inputs[0].mi.time = 0;
  inputs[1].type = INPUT_MOUSE;
  inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
  inputs[1].mi.time = 0;
  SendInput(2, inputs, sizeof(INPUT));
  return 0;
}
int Robot::mousePos(int &x, int &y)
{
  POINT pt;
  GetCursorPos(&pt);
  x = (int)pt.x;
  y = (int)pt.y;
  return 0;
}
void Robot::sleep(unsigned int ms)
{
  Sleep(ms);
}
int Robot::pixelColorCursor(uint8_t &r, uint8_t &g, uint8_t &b)
{
  std::vector<uint8_t> pixels;
  int x, y, en;
  mousePos(x, y);
  HDC hdcScreen = ::GetDC(NULL);
  auto px = GetPixel(hdcScreen, x, y);

  r = GetRValue(px);
  g = GetGValue(px);
  b = GetBValue(px);
}
unsigned long translateChar(char digit_or_letter)
{
  unsigned int key;
  if (digit_or_letter >= 'a' && digit_or_letter <= 'z')
  {
    key = 0x41 + (digit_or_letter - 'a');
  }
  else if (digit_or_letter >= 'A' && digit_or_letter <= 'Z')
  {
    key = 0x41 + (digit_or_letter - 'A');
  }
  else if (digit_or_letter >= '0' && digit_or_letter <= '9')
  {
    key = 0x30 + (digit_or_letter - '0');
  }
  return key;
}
Robot::~Robot()
{
}
Robot::Robot()
{
  init_keycodes();
  LeftMouseButton=VK_LBUTTON;
  RightMouseButton=VK_RBUTTON;
  MiddleMouseButton=VK_MBUTTON;
}
void Robot::init_keycodes()
{
  KEY_ALPH = 0x41;
  KEY_NUM = 0x30;
  KEY_ALT = VK_MENU;
  KEY_CTRL = VK_CONTROL;
  KEY_SHIFT = VK_SHIFT;
  KEY_ENTER = VK_RETURN;
  KEY_ESC = VK_ESCAPE;
  KEY_UP = VK_UP;
  KEY_DOWN = VK_DOWN;
  KEY_LEFT = VK_LEFT;
  KEY_RIGHT = VK_RIGHT;
}
int Robot::screenshot(std::vector<uint8_t> &pixels, int &width, int &height, int &endianess)
{
  return screenshot(pixels, width, height, endianess);
}
int Robot::screenshot(std::vector<uint8_t> &pixels, int x, int y, int width, int height, int &endianess)
{
  HDC hScreenDC = CreateDC("DISPLAY", NULL, NULL, NULL);
  // and a device context to put it in
  HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

  width = GetDeviceCaps(hScreenDC, HORZRES);
  height = GetDeviceCaps(hScreenDC, VERTRES);

  // maybe worth checking these are positive values
  HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);

  // get a new bitmap
  HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

  BitBlt(hMemoryDC, x, y, width, height, hScreenDC, 0, 0, SRCCOPY);
  hBitmap = (HBITMAP)SelectObject(hMemoryDC, hOldBitmap);
  char *data = (char *)GlobalLock(hBitmap);
  std::copy(data, data + width * height * 4, pixels.begin());
  GlobalUnlock(hBitmap);
  // clean up
  DeleteDC(hMemoryDC);
  DeleteDC(hScreenDC);
  pixels.resize(width * height * 3);

  return 0;
}
int Robot::pressedMouseButton()
{
  
  if ((GetKeyState(VK_LBUTTON)& 0x80)!=0)
  {
    return LeftMouseButton;
  }
  else if ((GetKeyState(VK_RBUTTON)& 0x80)!=0)
  {
    return RightMouseButton;
  }
  else
  {
    return 0;
  }
}