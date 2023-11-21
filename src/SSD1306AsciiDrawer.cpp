#include <Arduino.h>

#include "SSD1306AsciiDrawer.h"

void SSD1306AsciiDrawer::drawMenu(Menu* menu) {
    oled.clear();
    oled.setFont(HEADER_FONT);
    oled.print(F("Menu: "));
    if (menu->isTextFlash()) {
        const FlashString* text = reinterpret_cast<const FlashString*>(menu->getText());
        oled.println(text);
    } else {
        oled.println(menu->getText());
    }
    oled.setFont(NORMAL_FONT);

    ListEntry* e = menu->getCollection();

    if(!e)
        oled.println(F("  No sub-items"));
    else
        while(e) {
            if(e->item == menu->getSelectedItem())
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

            if(e->item->getSecondaryText()) {
                oled.print(F("|"));
                oled.print(e->item->getSecondaryText());
            }
            oled.clearToEOL();
            oled.setInvertMode(false);
            oled.println();

            e = e->next;
        }
}

/*void SerialDrawer::drawAction(Action* action) {
    Serial.print(F("Action: "));
    Serial.println(action->getText());
}*/

void SSD1306AsciiDrawer::drawSelector(NumericSelector* selector) {
    oled.clear();
    oled.println(F("Selector:"));

    const FlashString* text = reinterpret_cast<const FlashString*>(selector->getText());
    oled.print(text);

    oled.print(F(" <"));
    oled.print(selector->getSecondaryText());
    oled.print(F(">"));
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
