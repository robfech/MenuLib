#include "MenuController.h"

void MenuController::takeControl(MenuItem *item) {
  if (!item) {
    return;
  }

  currentItem = item;

  currentItem->activate();

  exiting = 0;
}

MenuController::MenuController() {}
MenuController::MenuController(MenuItem *root, MenuItemDrawer *drawer) {
  // TODO: check if root is NULL and throw an error
  currentItem = root;
  this->drawer = drawer;
};

void MenuController::incr() {
  if (exiting)
    exiting = 0;

  if (currentItem)
    currentItem->doIncr();
}

void MenuController::incrFast() {
  if (exiting)
    exiting = 0;

  if (currentItem)
    currentItem->doIncrFast();
}

void MenuController::decr() {
  if (exiting)
    exiting = 0;

  if (currentItem)
    currentItem->doDecr();
}

void MenuController::decrFast() {
  if (exiting)
    exiting = 0;

  if (currentItem)
    currentItem->doDecrFast();
}

void MenuController::select() {
  if (!currentItem)
    return;

  MenuItem *ret = currentItem->action();

  if (ret)
    takeControl(ret);
}

void MenuController::esc() {
  if (!currentItem)
    return;

  if (!currentItem->esc())
    return;

  currentItem->deactivate();

  if (currentItem->getParent())
    takeControl(currentItem->getParent());
  else
    exiting = 1;
}

void MenuController::draw() { drawer->draw(currentItem); }

int MenuController::canExit() { return exiting; }
