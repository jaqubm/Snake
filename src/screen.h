#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <ncurses.h>

void init_screen();
void done_screen();
void update_screen();

int ngetch();

void getscreenanchor(int &y, int &x);
void getscreensize(int &y, int &x);

int gotoyx(int y, int x);
void getcursor(int& y, int& x);

void printc(char c);
int printl(const char* fmt, ...);

#endif
