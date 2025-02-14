/*
    This item represent a "Yes\No" or "On\Off" option.
*/

#include <Arduino.h>

#include "MenuItem.h"

#ifndef CheckBox_h
#define CheckBox_h

class CheckBox : public MenuItem {
public:
  typedef void (*SelectedCallback)(bool);

  CheckBox(MenuItem *parent, const FlashString *text, bool &variable,
           SelectedCallback callback = NULL);

  char getTypeId() { return 'c'; }

  const char *getSecondaryText();

  // MenuItem fields

  // When activated from parent menu, trigger the callback and don't take
  // control.
  bool activate();
  void deactivate(){};

  // These three methods do nothing. Since CheckBox doesn't take control, they
  // are never called.
  void doIncr() {}
  void doDecr() {}
  void doIncrFast() {}
  void doDecrFast() {}
  MenuItem *action() { return NULL; }

private:
  bool &value;
  // callback pointer
  SelectedCallback callback;
};

#endif
