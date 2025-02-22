#include "shade.h"

namespace sde
{
  Shade::Shade(const string &filePath)
  {
    file = filePath;
  }

  string Shade::loadFile()
  {
    string finalStr = "";
    string lineStr = "";

    // open file
    ifstream actFile(file.c_str());

    // check if file is open
    if (actFile.is_open())
    {
      while (getline(actFile, lineStr))
      {
        finalStr += lineStr + '\n';
      }
      actFile.close();
    }
    else
    {
      cerr << "ERROR: File Not Opened" << endl;
    }

    return finalStr;
  }
}