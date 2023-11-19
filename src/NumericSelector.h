/*
    This item set a variable to a integer value in a range.

    support for text array by reaper7
*/

#include <Arduino.h>


#include "MenuItem.h"

#ifndef NumericSelector_h
#define NumericSelector_h

class NumericSelector : public MenuItem {
    public:
        typedef void(*NumberSelectedCallback)(bool);

        NumericSelector(MenuItem* parent, const FlashString* text, uint8_t& variable, uint8_t min, uint8_t max, NumberSelectedCallback callback = NULL, const char** arr = NULL);

        uint8_t getValue();
        uint8_t getMin();
        uint8_t getMax();

        char getTypeId() { return (arr?'t':'s'); }; //s - numeric selector; t - array selector

        const char* getSecondaryText();

        bool activate();
        void deactivate();

        void doNext();
        void doPrev();

        MenuItem* action();

    private:
        uint8_t& variable;
        uint8_t oldValue, min, max;

        const char** arr = NULL;

        char valueStr[18];

        NumberSelectedCallback callback;
};

#endif
