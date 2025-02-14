/*
    Implementation of Menu controller.
*/

#include "Action.h"
#include "Menu.h"
#include "NumericSelector.h"

#include "SerialDrawer.h"

#ifndef MenuController_h
#define MenuController_h

class MenuController {
private:
  MenuItem *currentItem;
  MenuItemDrawer *drawer;

  bool exiting;

public:
  MenuController();
  MenuController(MenuItem *root, MenuItemDrawer *drawer);

  void incr();
  void incrFast();
  void decr();
  void decrFast();

  void select();
  void esc();

  void draw();

  int canExit();

  void takeControl(MenuItem *item);
};

#endif
