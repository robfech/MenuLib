/*
    This item contains other items.
*/

#include "MenuItem.h"

#include "Action.h"
#include "CheckBox.h"
#include "NumericSelector.h"

#ifndef Menu_h
#define Menu_h

struct ListEntry {
  ListEntry(MenuItem *i) : item(i) {
    nextEntry = NULL;
    prevEntry = NULL;
  }

  ListEntry *nextEntry;
  ListEntry *prevEntry;

  MenuItem *item;
};

class Menu : public MenuItem {
public:
  typedef void (*MenuEnterCallback)(Menu *);
  uint8_t drawerLines;

  Menu(MenuItem *parent, const FlashString *text,
       MenuEnterCallback enter_cb = NULL, uint8_t drawerLines = 3);

  char getTypeId() { return 'm'; }

  MenuItem *addItem(MenuItem *item);
  void clearItems();

  ListEntry *getCollection() { return firstEntry; }
  MenuItem *getSelectedItem() { return selectedItem->item; }

  ListEntry *getSelectedListEntry() { return selectedItem; }
  ListEntry *getFirstDrawerEntry() { return firstDrawerEntry; }
  ListEntry *getLastDrawerEntry() { return lastDrawerEntry; }
  uint8_t getSelectedLine() { return selectedLine; }

  // MenuItem fields

  bool activate();
  void deactivate();

  // Selects the next item in the list
  void doIncr();
  void doIncrFast();
  // Selects the prev item in the list
  void doDecr();
  void doDecrFast();

  MenuItem *action();

private:
  ListEntry *firstEntry, *lastEntry, *selectedItem, *prevSelectedItem,
      *firstDrawerEntry, *lastDrawerEntry;

  MenuEnterCallback enter_cb;
  uint8_t selectedLine;
};

#endif
