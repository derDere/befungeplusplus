#ifndef CLIPBOARD_CPP
#define CLIPBOARD_CPP

#include "clipboard.hpp"

using namespace std;

string Clipboard::GetText() {
  string text = "";
  FILE *fp = popen(Config::ClipBoardGetTextCmd.c_str(), "r");
  if (fp != NULL) {
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
      text += buffer;
    }
    pclose(fp);
  }
  return text;
}

void Clipboard::SetText(string text) {
  FILE *fp = popen(Config::ClipBoardSetTextCmd.c_str(), "w");
  if (fp != NULL) {
    fputs(text.c_str(), fp);
    pclose(fp);
  }
}

#endif
