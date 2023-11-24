#include "Menu.h"

Menu::Menu(MenuItem* parent, const FlashString* text, MenuSelectedCallback callback, MenuEnterCallback enter_cb, uint8_t drawerLines) : MenuItem(parent, text) {
    this->firstEntry = NULL;
    this->lastEntry = NULL;

    this->enter_cb = enter_cb;
    this->callback = callback;
    this->drawerLines = drawerLines;
};

MenuItem* Menu::addItem(MenuItem* item) {
    ListEntry* e = new ListEntry(item);

    if(firstEntry) {
        lastEntry->next = e;
        e->prev = lastEntry;
    } else
        firstEntry = e;

    lastEntry = e;

    selectedItem = firstEntry;
    prevSelectedItem = firstEntry;
    firstDrawerEntry = firstEntry;

    ListEntry* ee = this->firstDrawerEntry;
    for (int i = 0; i < drawerLines; i++) {
      if (!ee) break;
      lastDrawerEntry = ee;
      ee = ee->next;
    }
    selectedLine = 1;

    return item;
}

void Menu::clearItems() {
    ListEntry* e = this->firstEntry;
    ListEntry* next;

    while(e) {
        next = e->next;

        delete e;

        e = next;
    }

    this->firstEntry = NULL;
    this->lastEntry  = NULL;
}

bool Menu::activate() {
    if (this->enter_cb)
        this->enter_cb(this);

    if (this->callback)
        this->callback(true);

    // Select the previous selected item when entering the menu
    selectedItem = prevSelectedItem;

    // And jump to the next. If firstElement is enabled, it will stop there,
    // otherwise it will find the first enabled item.
    // doNext();
}

void Menu::deactivate() {
    prevSelectedItem = firstEntry;
    firstDrawerEntry = firstEntry;

    ListEntry* e = firstDrawerEntry;
    for (int i = 0; i < drawerLines; i++) {
      if (!e) break;
      lastDrawerEntry = e;
      e = e->next;
    }
    selectedLine = 1;

    if (this->callback)
        this->callback(true);
}

void Menu::doNext() {
  selectedItem = selectedItem->next;
  if (selectedItem) {
    selectedLine++;
    if (selectedLine > drawerLines) selectedLine = drawerLines;
    if (selectedItem->prev == lastDrawerEntry){
      lastDrawerEntry = selectedItem;
      firstDrawerEntry =  firstDrawerEntry->next;
    }
  }
  else {
      selectedItem = lastEntry;
  }
}

void Menu::doPrev() {
  selectedItem = selectedItem->prev;
  if (selectedItem){
    selectedLine--;
    if (selectedLine < 1) selectedLine = 1;
    if (selectedItem->next == firstDrawerEntry){
      firstDrawerEntry = selectedItem;
      lastDrawerEntry =  lastDrawerEntry->prev;
    }
  }
  else {
    selectedItem = firstEntry;
  }

    // // TODO: infinite loop if all entries are disabled??
    // do {
    //
    //     selectedItem = selectedItem->prev;
    //
    //     if(!selectedItem) selectedItem = firstEntry;
    //
    // } while(!selectedItem->item->isEnabled());
}

MenuItem* Menu::action() {
    prevSelectedItem = selectedItem;
    // Let's the Item do something to start
    int takeControl = selectedItem->item->activate();

    // Then let it take control, or maintain it.
    if(takeControl)
        return selectedItem->item;
    else
        return NULL;
}
