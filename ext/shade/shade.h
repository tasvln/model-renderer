#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#ifndef SHADE_H
#define SHADE_H

using namespace std;

namespace sde
{
  class Shade
  {
  private:
    string file;

  public:
    Shade(const string &filePath);

    // function
    string loadFile();
  };
}

#endif