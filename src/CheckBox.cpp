#include "CheckBox.h"

CheckBox::CheckBox(MenuItem *parent, const FlashString *text, bool &variable,
                   SelectedCallback callback)
    : MenuItem(parent, text), value(variable) {
  this->callback = callback;
}

bool CheckBox::activate() {
  // Don't use the xor or the not method to avoid strange things if
  // the variable changes outside the menu.
  value = value ? 0 : 1;

  if (this->callback)
    this->callback(true);

  return 0;
}

const char *CheckBox::getSecondaryText() { return value ? "On" : "Off"; }
