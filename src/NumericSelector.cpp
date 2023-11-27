#include "NumericSelector.h"

NumericSelector::NumericSelector(MenuItem* parent, const FlashString* text, uint8_t& variable, uint8_t min, uint8_t max, NumberSelectedCallback callback, const char** arr) : MenuItem(parent, text), variable(variable) {
    this->min = min;
    this->max = max;

    this->callback = callback;

    oldValue = variable;

    if (arr)
      this->arr = arr;
};

uint8_t NumericSelector::getValue() { return variable; }
uint8_t NumericSelector::getMin()   { return min; }
uint8_t NumericSelector::getMax()   { return max; }

const char* NumericSelector::getSecondaryText() {
    if (!arr) {
      snprintf_P(valueStr, 18, PSTR("%d"), variable);
    } else {
      snprintf_P(valueStr, 18, PSTR("%s"), arr[variable]);
    }

    return valueStr;
}

bool NumericSelector::activate() {
    oldValue = variable;

    return 1;
}

void NumericSelector::deactivate() {
    variable = oldValue;

    // On cancel restore the value
    if (this->callback)
        this->callback(false);
}

void NumericSelector::doNext() {
    if(variable >= this->max)
        variable = this->max;
    else
        variable++;

    if (this->callback)
        this->callback(false);

}
void NumericSelector::doPrev() {
    if(variable <= this->min)
        variable = this->min;
    else
        variable--;

    if (this->callback)
        this->callback(false);
}

MenuItem* NumericSelector::action() {
    if (this->callback)
        this->callback(true);

    return this->getParent();
}
