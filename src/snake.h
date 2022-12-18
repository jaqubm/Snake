#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <vector>
#include <cstdlib>
#include <ctime>

#include "winsys.h"
#include "cpoint.h"
#include "screen.h"

class CSnake : public CFramedWindow
{
  private:
    bool game_pause = true;
    bool game_help = true;
    bool game_end = false;

    int direction = KEY_RIGHT;

    int lvl = 0;
    int clock = 0;
    int game_speed = 20;

    vector <CPoint> snake_parts;

    CPoint food;

  public:
    CSnake(CRect r, char _c = ' ');

    bool handleEvent(int key);

    void paint();

    bool gameMove();

    void gameReset();

    void foodSpawner();
};

#endif
