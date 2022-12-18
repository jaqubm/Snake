#ifndef __WINSYS_H__
#define __WINSYS_H__

#include "cpoint.h"
#include <list>

#include <string>
//#include <ctype.h>
//#include <stdarg.h>
using namespace std;

class CView
{
  protected:
    CRect geom;

  public:
    CView(CRect g) : geom(g) {}
    virtual ~CView() {}

    virtual void paint () = 0;
    virtual bool handleEvent (int key) = 0;
    virtual void move (const CPoint & delta);
};

class CWindow:public CView
{
  protected:
    char c;
  public:
    CWindow(CRect r, char _c = '*') : CView(r), c(_c) {}

    void paint();
    bool handleEvent(int key);
};

class CFramedWindow:public CWindow
{
  public:
    CFramedWindow(CRect r, char _c = '\'') : CWindow(r, _c) {}

    void paint();
};

class CInputLine:public CFramedWindow
{
    string text;
  public:
    CInputLine(CRect r, char _c = ',') : CFramedWindow(r, _c) {}

    void paint();
    bool handleEvent(int c);
};

class CGroup:public CView
{
    list< CView * > children;
  public:
    CGroup(CRect g) : CView(g) {}
    ~CGroup();

    void paint();
    bool handleEvent(int key);
    void insert(CView * v);
};

class CDesktop:public CGroup
{
  public:
    CDesktop();
    ~CDesktop();

    void paint();
    int getEvent();
    void run();
};

#endif
