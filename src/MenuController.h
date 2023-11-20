/*
    Implementation of Menu controller.
*/


#include "NumericSelector.h"
#include "Action.h"
#include "Menu.h"

#include "SerialDrawer.h"

#ifndef MenuController_h
#define MenuController_h

typedef enum menu_event_t {NONE, MENU_PREV, MENU_NEXT, MENU_SELECT, MENU_BACK} menu_event_t;

class MenuController {
    private:
        MenuItem* currentItem;
        MenuItemDrawer* drawer;

        bool exiting;


    public:
        MenuController();
        MenuController(MenuItem* root, MenuItemDrawer* drawer);

        void next();
        void prev();

        void select();
        void back();

        void draw();

        int canExit();

        void takeControl(MenuItem* item);
};

#endif
