#include "Menu.h"

Menu::Menu(MenuItem *parent, const FlashString *text,
           MenuEnterCallback enter_cb, uint8_t drawerLines)
    : MenuItem(parent, text) {
  this->firstEntry = NULL;
  this->lastEntry = NULL;

  this->enter_cb = enter_cb;
  this->drawerLines = drawerLines;
};

MenuItem *Menu::addItem(MenuItem *item) {
  ListEntry *e = new ListEntry(item);

  if (firstEntry) {
    lastEntry->nextEntry = e;
    e->prevEntry = lastEntry;
  } else
    firstEntry = e;

  lastEntry = e;

  selectedItem = firstEntry;
  prevSelectedItem = firstEntry;
  firstDrawerEntry = firstEntry;

  ListEntry *ee = this->firstDrawerEntry;
  for (int i = 0; i < drawerLines; i++) {
    if (!ee)
      break;
    lastDrawerEntry = ee;
    ee = ee->nextEntry;
  }
  selectedLine = 1;

  return item;
}

void Menu::clearItems() {
  ListEntry *e = this->firstEntry;
  ListEntry *nextEntry;

  while (e) {
    nextEntry = e->nextEntry;

    delete e;

    e = nextEntry;
  }

  this->firstEntry = NULL;
  this->lastEntry = NULL;
}

bool Menu::activate() {
  if (this->enter_cb)
    this->enter_cb(this);

  // Select the previous selected item when entering the menu
  selectedItem = prevSelectedItem;

  // And jump to the nextEntry. If firstElement is enabled, it will stop there,
  // otherwise it will find the first enabled item.
  // doIncr();
  return 1;
}

void Menu::deactivate() {
  prevSelectedItem = firstEntry;
  firstDrawerEntry = firstEntry;

  ListEntry *e = firstDrawerEntry;
  for (int i = 0; i < drawerLines; i++) {
    if (!e)
      break;
    lastDrawerEntry = e;
    e = e->nextEntry;
  }
  selectedLine = 1;
}

void Menu::doIncr() {
  selectedItem = selectedItem->nextEntry;
  if (selectedItem) {
    selectedLine++;
    if (selectedLine > drawerLines)
      selectedLine = drawerLines;
    if (selectedItem->prevEntry == lastDrawerEntry) {
      lastDrawerEntry = selectedItem;
      firstDrawerEntry = firstDrawerEntry->nextEntry;
    }
  } else {
    selectedItem = lastEntry;
  }
}

void Menu::doIncrFast() { doIncr(); }

void Menu::doDecr() {
  selectedItem = selectedItem->prevEntry;
  if (selectedItem) {
    selectedLine--;
    if (selectedLine < 1)
      selectedLine = 1;
    if (selectedItem->nextEntry == firstDrawerEntry) {
      firstDrawerEntry = selectedItem;
      lastDrawerEntry = lastDrawerEntry->prevEntry;
    }
  } else {
    selectedItem = firstEntry;
  }
}

void Menu::doDecrFast() { doDecr(); }

MenuItem *Menu::action() {
  prevSelectedItem = selectedItem;
  // Let's the Item do something to start
  int takeControl = selectedItem->item->activate();

  // Then let it take control, or maintain it.
  if (takeControl)
    return selectedItem->item;
  else
    return NULL;
}
