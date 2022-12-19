#include "snake.h"

CSnake::CSnake(CRect r, char _c /*=' '*/) : CFramedWindow(r, _c)
{
  srand(time(NULL));
  gameReset();
  game_pause = true;
}

bool CSnake::handleEvent(int key)
{
  //Clocker if there is no button pressed down
  if(!game_pause && key == ERR)
  {
    clock++;
    if(game_speed <= clock) 
    {
      gameMove();
      clock = 0;
      return true;
    }
  }

  //Pause menu turning on/off
  if(tolower(key) == 'p') 
  {
    game_pause = !game_pause;
    if(game_help) game_help = false;
    clock = 0;
    return true;
  }

  //Help menu turning on/off if game is paused
  if(tolower(key) == 'h' && game_pause) 
  {
    game_help = !game_help;
    clock = 0;
    return true;
  }

  //Game reset
  if(tolower(key) == 'r') 
  {
    gameReset();
    clock = 0;
    return true;
  }

  //Changing move diroection for Snake
  if(!game_pause && !game_end)
  {
    if(key == KEY_UP)
    {
      if(direction != KEY_DOWN) direction = key;
      gameMove();
      clock = 0;
      return true;
    }
    else if(key == KEY_LEFT)
    {
      if(direction != KEY_RIGHT) direction = key;
      gameMove();
      clock = 0;
      return true;
    }
    else if(key == KEY_DOWN)
    {
      if(direction != KEY_UP) direction = key;
      gameMove();
      clock = 0;
      return true;
    }
    else if(key == KEY_RIGHT)
    {
      if(direction != KEY_LEFT) direction = key;
      gameMove();
      clock = 0;
      return true;
    }
  }

  return CFramedWindow::handleEvent(key);
}

void CSnake::paint()
{
  CFramedWindow::paint();

  //Food
  gotoyx(food.y + geom.topleft.y, food.x + geom.topleft.x);
  printc('O');

  //Sneak head
  gotoyx(snake_parts[0].y + geom.topleft.y, snake_parts[0].x + geom.topleft.x);
  printc('+');

  //Snake body
  for(unsigned int i=1; i<snake_parts.size(); i++)
  {
    gotoyx(snake_parts[i].y + geom.topleft.y, snake_parts[i].x + geom.topleft.x);
    printc('*');
  }

  int x = geom.topleft.x;
  int y = geom.topleft.y;

  if(!game_end)
  {
    gotoyx(y - 1, x);
    printl("| LEVEL: %d |", lvl);

    if(game_pause && !game_help && !game_end)
    {
      gotoyx(y + 2, x + 3);
      printl("h - toggle help information");
      gotoyx(y + 3, x + 3);
      printl("p - toggle play/pause mode");
      gotoyx(y + 4, x + 3);
      printl("r - restart game");
      gotoyx(y + 5, x + 3);
      printl("q - quit");
      gotoyx(y + 6, x + 3);
      printl("arrows - move snake (in play mode) or");
      gotoyx(y + 7, x + 12);
      printl("move window (in pause mode)");
    }
    else if(game_pause && game_help && !game_end)
    {
      gotoyx(y + 2, x + 2);
      printl("Use arrows to move snake");
      gotoyx(y + 4, x + 2);
      printl("Eat as much food as you can.");
      gotoyx(y + 5, x + 2);
      printl("Also, dont die.");
      gotoyx(y + 7, x + 2);
      printl("press 'p' or 'r' to play or 'h' for help");
    }
  }
  else
  {
    gotoyx(y + 1, x + 1);
    printl("GAME OVER, result: %d", lvl);
  }
}

bool CSnake::gameMove()
{
  if(!game_pause)
  {
    //Remembering the oldest tail position
    CPoint oldTail = snake_parts[snake_parts.size()-1];

    //Moving tail to next position
    for(unsigned int i=snake_parts.size()-1; i>0; i--) snake_parts[i] = snake_parts[i-1];

    //Snake head move
    if(direction == KEY_UP) snake_parts[0] += CPoint(0, -1);
    else if(direction == KEY_LEFT) snake_parts[0] += CPoint(-1, 0);
    else if(direction == KEY_DOWN) snake_parts[0] += CPoint(0, 1);
    else if(direction == KEY_RIGHT) snake_parts[0] += CPoint(1, 0);

    //Going out of map border
    if(snake_parts[0].x == 0) snake_parts[0].x = geom.size.x-2;
    if(snake_parts[0].x == geom.size.x-1) snake_parts[0].x = 1;

    if(snake_parts[0].y == 0) snake_parts[0].y = geom.size.y-2;
    if(snake_parts[0].y == geom.size.y-1) snake_parts[0].y = 1;

    //Collision detection
    for(unsigned int i=1; i<snake_parts.size(); i++)
    {
      if(snake_parts[0].x == snake_parts[i].x && snake_parts[0].y == snake_parts[i].y) 
      {
        game_pause = true;
        game_end = true;
        return true;
      }
    }

    if(snake_parts[0].x == food.x && snake_parts[0].y == food.y)
    {
      if(game_speed > 1) game_speed--;
      lvl++;

      snake_parts.push_back(oldTail);

      foodSpawner();
    }
  }

  return false;
}

void CSnake::gameReset()
{
  game_pause = false;
  game_help = false;
  game_end = false;

  direction = KEY_RIGHT;

  game_speed = 20;
  lvl = 0;

  snake_parts.clear();

  int snakeHeadX = rand() % (geom.size.x - 5) + 1;
  int sneakHeadY = rand() % (geom.size.y - 5) + 1;

  snake_parts.push_back(CPoint(snakeHeadX, sneakHeadY));
  snake_parts.push_back(CPoint(snakeHeadX - 1, sneakHeadY));
  snake_parts.push_back(CPoint(snakeHeadX - 2, sneakHeadY));

  foodSpawner();

  paint();
}

void CSnake::foodSpawner()
{
  int x, y;

  while(1)
  {
    bool onSnake = false;

    x = (rand() % (geom.size.x - 2)) + 1;
    y = (rand() % (geom.size.y - 2)) + 1;

    for(unsigned int i=0; i<snake_parts.size(); i++)
    {
      if(snake_parts[i].x == x && snake_parts[i].y == y)
      {
        onSnake = true;

        break;
      }
    }

    if(!onSnake) break;
  }

  food = CPoint(x, y);
}
