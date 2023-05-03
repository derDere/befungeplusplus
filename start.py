#!/usr/bin/env python3

"""
This is a wrapper script for the Befunge++ interpreter. It is intended to be
used as a launcher for the interpreter, and to reset the terminal to a sane
state if the interpreter crashes. It is not intended to be used as a library.
If you know how to reset the terminal to a sane state, you could just run the
interpreter directly.
"""

import sys
import curses
import subprocess


CMD = './befunge++'


class CursesGuard:
  def __enter__(self):
    curses.initscr()
    curses.noecho()
    curses.raw()
    curses.curs_set(0)
    curses.start_color()
    curses.use_default_colors()
    curses.mousemask(curses.ALL_MOUSE_EVENTS)

  def __exit__(self, exc_type, exc_value, traceback):
    curses.endwin()


def main(args):
  r = None
  with CursesGuard() as c:
    r = subprocess.run([CMD] + args)
  if r != None:
    if r.returncode != 0:
      print(CMD + " exited with code " + str(r.returncode) + ".", file=sys.stderr)
    return r.returncode
  else:
    print("Error: " + CMD + " did not run.", file=sys.stderr)
    return 1


if __name__=="__main__":
  exc = 0
  if len(sys.argv) > 1:
    exc = main(sys.argv[1:])
  else:
    exc = main([])
  sys.exit(exc)
