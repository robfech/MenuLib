/*
    Implementation of a Drawer over Serial.
*/

#include "NumericSelector.h"
#include "Action.h"
#include "Menu.h"

#include "MenuItemDrawer.h"

#ifndef SerialDrawer_h
#define SerialDrawer_h

class SerialDrawer : public MenuItemDrawer {

    private:

        void drawMenu(Menu* menu);
        // void drawAction(Action<T>* action);
        void drawSelector(NumericSelectorUint8* selector);
        void drawSelector(NumericSelectorInt16* selector);
        void drawSelector(NumericSelectorList* selector);


    public:

        void draw(MenuItem* item);
};

#endif
