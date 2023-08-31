
#include "Robot.hpp"
#include <vector>
#include <iostream>
int Robot::keyPress(unsigned int key)
{
  std::vector<unsigned int> v(1);
  v[0] = key;
  keyPress(v);
  return 0;
}
#ifdef linux
#include "Robot_linux.cpp"
#endif
#ifdef _WIN32
#include "Robot_win.cpp"
#endif
