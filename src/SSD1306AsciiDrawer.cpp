#include <Arduino.h>

#include "SSD1306AsciiDrawer.h"

void SSD1306AsciiDrawer::drawMenu(Menu* menu) {
    oled.setFont(HEADER_FONT);
    oled.setCursor(0, 0);
    oled.print(F("Menu: "));
    const FlashString* text = reinterpret_cast<const FlashString*>(menu->getText());
    oled.print(text);
    oled.clearToEOL();
    oled.println();
    oled.setFont(NORMAL_FONT);

    ListEntry* e = menu->getFirstDrawerEntry();

    if(!e) return;

    while(e) {
      if (e->item == menu->getSelectedItem() && !e->item->isEdited())
          oled.setInvertMode(true);
      else
          oled.setInvertMode(false);

      const FlashString* text = reinterpret_cast<const FlashString*>(e->item->getText());
      oled.print(text);
      oled.clear(oled.col(), colSecondary, oled.row(), oled.row()+1);
      oled.setInvertMode(false);
      if(e->item->getSecondaryText()) {
        oled.setCursor(colSecondary, oled.row());
        if (e->item->isEdited()) oled.setInvertMode(true);
        oled.print(e->item->getSecondaryText());
        oled.setInvertMode(false);
      }
      oled.clearToEOL();

      if ( e == menu->getLastDrawerEntry()) {
        oled.clear(0, oled.displayWidth() - 1, oled.row() + oled.fontRows(), oled.displayRows());
        break;
      }

      oled.println();


      e = e->next;
  }
  selectedLine = menu->getSelectedLine();
}

/*void SerialDrawer::drawAction(Action* action) {
    Serial.print(F("Action: "));
    Serial.println(action->getText());
}*/

void SSD1306AsciiDrawer::drawSelector(NumericSelectorUint8* selector) {
    MenuItem *prev = selector->getParent();
    drawMenu((Menu*)prev);
}

void SSD1306AsciiDrawer::drawSelector(NumericSelectorInt16* selector) {
    MenuItem *prev = selector->getParent();
    drawMenu((Menu*)prev);
}

void SSD1306AsciiDrawer::drawSelector(NumericSelectorList* selector) {
    MenuItem *prev = selector->getParent();
    drawMenu((Menu*)prev);
}

void SSD1306AsciiDrawer::draw(MenuItem* item) {
  if(!item) return;

  switch(item->getTypeId()) {
    case 'm':
      drawMenu((Menu*)item);
      break;

    /*case 'a':
        drawAction((Action*)item);
        break;
    */
    case 'b':
      drawSelector((NumericSelectorUint8*)item);
      break;
    case 'i':
        drawSelector((NumericSelectorInt16*)item);
        break;
    case 'l':
      drawSelector((NumericSelectorList*)item);
      break;
  }
}
