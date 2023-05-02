#ifndef CLIPBOARD_HPP
#define CLIPBOARD_HPP

#include <string>
#include <fstream>
#include "config.hpp"

using namespace std;

class Clipboard {
public:
  static string GetText();
  static void SetText(string text);
};

#endif
