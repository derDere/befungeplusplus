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
    curs_set(0);
    start_color();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, true);
    // mousemask(BUTTON1_CLICKED, NULL); //ALL_MOUSE_EVENTS, NULL);
    app->Init(win);

    app->Draw();

    getch();

    return 0;
}

void printHelp() {}

void quit() {
  endwin();
}

#endif
