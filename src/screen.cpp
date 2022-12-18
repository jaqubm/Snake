/* screen.cpp */
#include "screen.h"
#include "cpoint.h"

#define LINE_MAX 255

static CPoint TopLeft;
static CPoint BottomRight;
static int cury, curx;

void init_screen()
{
  initscr();
  cbreak();
  noecho();
  timeout(20);
  nonl();
  leaveok(stdscr,TRUE);
  intrflush(stdscr, FALSE);
  keypad(stdscr, TRUE);
  curs_set(0);
}

void done_screen()
{
  endwin();
}

void update_screen()
{
  getscreenanchor(TopLeft.y, TopLeft.x);
  getscreensize(BottomRight.y, BottomRight.x);
  BottomRight += TopLeft;
}

int ngetch()
{
  return wgetch(stdscr);
}

void getscreenanchor(int &y, int &x)
{
  getbegyx(stdscr, y, x);
}

void getscreensize(int &y, int &x)
{
  getmaxyx(stdscr, y, x);
}

int gotoyx(int y, int x)
{
  cury=y;
  curx=x;
  return (cury >= TopLeft.y && cury < BottomRight.y && curx >= TopLeft.x && curx < BottomRight.x);
}

void getcursor(int& y, int& x)
{
  y = cury;
  x = curx;
}

void printc(char c)
{
  if(c != '\n' && c != '\r')
  {
    if(cury >= TopLeft.y && cury < BottomRight.y && curx >= TopLeft.x && curx < BottomRight.x)
    {
      wmove(stdscr, cury, curx);
      addch(c);
    }
    curx++;
  }
}

int printl(const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);

  char dest[LINE_MAX];
  vsnprintf(dest, LINE_MAX, fmt, ap);

  int i = 0;
  while(dest[i])
    printc(dest[i++]);

  va_end(ap);
  return !ERR;
}
