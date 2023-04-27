#ifndef MAIN_CPP
#define MAIN_CPP

#include <string>
#include <iostream>
#include <ncursesw/ncurses.h>
#include <unistd.h>
#include "app.hpp"

#define SLEEP(ms) usleep(ms)

#define DELAY 200

using namespace std;
using namespace BefungePlusPlus;

void quit();
void printHelp();
int getInput();

/**
 * @brief  The main function
 * @author https://github.com/derDere/
 * @file   main.cpp
 * @date   2023-04-14
 * @remark ...
 */
int main(int argc, const char *argv[])
{
  App* app = new App();

  // Init Curses ----------
  setlocale(LC_ALL, "");
  WINDOW* win = initscr();
  atexit(quit);
  raw(); // disable line buffering
  curs_set(0); // hide cursor
  use_default_colors(); // enable transparent black
  start_color(); // enable color
  clear(); // clear screen
  noecho(); // disable echo
  cbreak(); // disable line buffering
  keypad(stdscr, true); // enable function keys
  mousemask(ALL_MOUSE_EVENTS, NULL); // enable mouse events

  app->Init(win);

  long input;
  while (app->run) {
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
