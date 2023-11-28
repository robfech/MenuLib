#include <Arduino.h>

#include "SerialDrawer.h"

void SerialDrawer::drawMenu(Menu* menu) {
    Serial.print(F("Menu: "));
    const FlashString* text = reinterpret_cast<const FlashString*>(menu->getText());
    Serial.println(text);

    ListEntry* e = menu->getFirstDrawerEntry();

    if(!e)
        Serial.println(F("  No sub-items"));
    else
        while(e) {
            if(e->item == menu->getSelectedItem())
                Serial.print(F("   ->"));
            else
                Serial.print(F("     "));

            const FlashString* text = reinterpret_cast<const FlashString*>(e->item->getText());
            Serial.print(text);

            if(e->item->getSecondaryText()) {
                Serial.print(F(" | "));
                Serial.print(e->item->getSecondaryText());
            }

            Serial.println();

            if ( e == menu->getLastDrawerEntry()) break;
            e = e->next;
        }
}

/*void SerialDrawer::drawAction(Action* action) {
    Serial.print(F("Action: "));
    Serial.println(action->getText());
}*/

void SerialDrawer::drawSelector(NumericSelector* selector) {
    Serial.print(F("Selector: "));

    const FlashString* text = reinterpret_cast<const FlashString*>(selector->getText());
    Serial.print(text);

    Serial.print(F(" <"));
    Serial.print(selector->getSecondaryText());
    Serial.println(F(">"));
}

void SerialDrawer::draw(MenuItem* item) {
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
