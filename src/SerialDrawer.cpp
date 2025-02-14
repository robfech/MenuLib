#include <Arduino.h>

#include "SerialDrawer.h"

void SerialDrawer::drawMenu(Menu *menu) {
  Serial.print(F("Menu: "));
  const FlashString *text =
      reinterpret_cast<const FlashString *>(menu->getText());
  Serial.println(text);

  ListEntry *e = menu->getFirstDrawerEntry();

  if (!e)
    Serial.println(F("  No sub-items"));
  else
    while (e) {
      if (e->item == menu->getSelectedItem())
        Serial.print(F("  -> "));
      else
        Serial.print(F("     "));

      const FlashString *text =
          reinterpret_cast<const FlashString *>(e->item->getText());
      Serial.print(text);

      if (e->item->getSecondaryText()) {
        Serial.print(F(" | "));
        if (e->item->isEdited())
          Serial.print(">");
        Serial.print(e->item->getSecondaryText());
        if (e->item->isEdited())
          Serial.print("<");
      }

      Serial.println();

      if (e == menu->getLastDrawerEntry())
        break;
      e = e->nextEntry;
    }
}

/*void SerialDrawer::drawAction(Action* action) {
    Serial.print(F("Action: "));
    Serial.println(action->getText());
}*/

void SerialDrawer::drawSelector(NumericSelectorUint8 *selector) {
  MenuItem *prev = selector->getParent();
  drawMenu((Menu *)prev);
}

void SerialDrawer::drawSelector(NumericSelectorInt16 *selector) {
  MenuItem *prev = selector->getParent();
  drawMenu((Menu *)prev);
}

void SerialDrawer::drawSelector(NumericSelectorList *selector) {
  MenuItem *prev = selector->getParent();
  drawMenu((Menu *)prev);
}

void SerialDrawer::draw(MenuItem *item) {
  if (!item)
    return;

  switch (item->getTypeId()) {
  case 'm':
    drawMenu((Menu *)item);
    break;

  /*case 'a':
      drawAction((Action*)item);
      break;
  */
  case 'b':
    drawSelector((NumericSelectorUint8 *)item);
    break;
  case 'i':
    drawSelector((NumericSelectorInt16 *)item);
    break;
  case 'l':
    drawSelector((NumericSelectorList *)item);
    break;
  }
}
