#include <Arduino.h>

#include "SSD1306AsciiDrawer.h"

void SSD1306AsciiDrawer::drawMenu(Menu* menu) {
    int itemCounter= 0;
    oled.setFont(HEADER_FONT);
    oled.setCursor(0, 0);
    oled.print(F("Menu: "));
    if (menu->isTextFlash()) {
        const FlashString* text = reinterpret_cast<const FlashString*>(menu->getText());
        oled.print(text);
    } else {
        oled.print(menu->getText());
    }
    oled.setFont(NORMAL_FONT);
    oled.clearToEOL();
    oled.println();

    ListEntry* e = menu->getCollection();

    if(!e) return;

    do {
      if (itemCounter == 0 && e == menu->getSelectedListEntry()){
        firstScreenItem = e;
        lastScreenItem = e;
        for (int i = 1; i < ITEMS_PER_SCREEN; i++) {
          lastScreenItem = lastScreenItem->next;
        }
      }

      if (menu->getSelectedListEntry() == lastScreenItem->next) {
        firstScreenItem = firstScreenItem->next;
        lastScreenItem = lastScreenItem->next;
      }

      if (menu->getSelectedListEntry() == firstScreenItem->prev) {
        firstScreenItem = firstScreenItem->prev;
        lastScreenItem = lastScreenItem->prev;
      }

      if (e == menu->getSelectedListEntry())
        break;

      e = e->next;
      itemCounter++;
    } while(e);


    e = firstScreenItem;
    onScreenSelectedItem = 1;
    do{
      if(menu->getSelectedListEntry() == e){
        break;
      }
      onScreenSelectedItem++;
      e = e->next;
    } while(e);


    e = firstScreenItem;
    itemCounter = 0;

    while(e && itemCounter < ITEMS_PER_SCREEN) {
      if (e->item == menu->getSelectedItem())
          oled.setInvertMode(true);
      else
          oled.setInvertMode(false);

      if (e->item->isTextFlash()) {
          const FlashString* text = reinterpret_cast<const FlashString*>(e->item->getText());
          oled.print(text);
      } else {
          const char* text = e->item->getText();
          oled.print(text);
      }
      oled.clear(oled.col(), colSecondary, oled.row(), oled.row()+1);
      oled.setInvertMode(false);
      if(e->item->getSecondaryText()) {
        oled.setCursor(colSecondary, oled.row());
        oled.print(e->item->getSecondaryText());
      }
      oled.clearToEOL();
      oled.println();

      itemCounter++;
      e = e->next;
  }
}

/*void SerialDrawer::drawAction(Action* action) {
    Serial.print(F("Action: "));
    Serial.println(action->getText());
}*/

void SSD1306AsciiDrawer::drawSelector(NumericSelector* selector) {
    oled.setCursor(colSecondary, oled.fontRows() * onScreenSelectedItem);
    oled.setInvertMode(true);
    oled.print(selector->getSecondaryText());
    oled.setInvertMode(false);
    oled.clearToEOL();
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
        case 't':
        case 's':
            drawSelector((NumericSelector*)item);
            break;
    }
}
