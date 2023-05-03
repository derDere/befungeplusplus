#ifndef MAIN_CPP
#define MAIN_CPP

#include <string>
#include <iostream>
#include <ncursesw/ncurses.h>
#include <unistd.h>
//#include <termios.h>
//#include <signal.h>
#include "advkeys.hpp"
#include "app.hpp"
#include "config.hpp"

#define SLEEP(ms) usleep(ms)

#define DELAY 200

using namespace std;
using namespace BefungePlusPlus;

//void onSignal(int signal);
void quit();
void printHelp();

App* app = nullptr;

/**
 * @brief  The main function
 * @author https://github.com/derDere/
 * @file   main.cpp
 * @date   2023-04-14
 * @remark ...
 */
int main(int argc, const char *argv[])
{
  Config::Reload();
  app = new App();

  // Init Curses ----------
  setlocale(LC_ALL, "");
  WINDOW* win = initscr();
  atexit(quit);
  raw(); // disable line buffering and disable ctrl+c/ctrl+z/ctrl+s etc.
  //cbreak(); // disable line buffering but keep ctrl+c/ctrl+z/ctrl+s etc.
  curs_set(0); // hide cursor
  use_default_colors(); // enable transparent black
  start_color(); // enable color
  clear(); // clear screen
  noecho(); // disable echo
  keypad(stdscr, true); // enable function keys
  mousemask(ALL_MOUSE_EVENTS, NULL); // enable mouse events

  app->Init(win);

  long input;
  while (app->IsRunning()) {
    app->Draw();
    input = wgetch(win);
    app->Update(input);
  }

  return 0;
}

void printHelp() {}

void quit() {
  endwin();
}

#endif
