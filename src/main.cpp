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
  app = new App();

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
  //cbreak(); // disable line buffering
  keypad(stdscr, true); // enable function keys
  mousemask(ALL_MOUSE_EVENTS, NULL); // enable mouse events

  // Disable Ctrl-C signal
  //signal(SIGINT, onSignal);

  // Enable Ctrl-Z and Ctrl-S keys
  // struct termios term;
  // tcgetattr(STDIN_FILENO, &term); // get terminal attributes
  // term.c_lflag &= ~(ICANON | ECHO); // disable canonical mode and echo
  // term.c_cc[VMIN] = 1; // read at least 1 byte
  // term.c_cc[VTIME] = 0; // no timeout
  // term.c_cc[VSTOP] = _POSIX_VDISABLE; // disable Ctrl-S
  // term.c_cc[VSUSP] = _POSIX_VDISABLE; // disable Ctrl-Z
  // tcsetattr(STDIN_FILENO, TCSANOW, &term); // set terminal attributes

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

// void onSignal(int signal) {
//   if (app != nullptr) {
//     if (signal == SIGINT) {
//       app->Update(KEY_CTRL_C);
//     }
//   }
// }

void quit() {
  endwin();
}

#endif
