#include "NumericSelector.h"

NumericSelector::NumericSelector(MenuItem* parent, const FlashString* text, uint8_t& variable, uint8_t min, uint8_t max, uint8_t stepSize, NumberSelectedCallback callback, const char** arr) : MenuItem(parent, text), variable(variable) {
    this->min = min;
    this->max = max;
    this->stepSize = stepSize;

    this->callback = callback;

    oldValue = variable;

    if (arr)
      this->arr = arr;
};

uint8_t NumericSelector::getValue() { return variable; }
uint8_t NumericSelector::getMin()   { return min; }
uint8_t NumericSelector::getMax()   { return max; }
uint8_t NumericSelector::getStepSize() { return stepSize; }

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
    setEditingState(true);

    return 1;
}

void NumericSelector::deactivate() {
    variable = oldValue;
    setEditingState(false);

    // On cancel restore the value
    if (this->callback)
        this->callback(false);
}

void NumericSelector::doNext() {
    if(variable + stepSize >= this->max)
        variable = this->max;
    else
        variable = variable + stepSize;

    if (this->callback)
        this->callback(false);

}

void NumericSelector::doPrev() {
    if(variable - stepSize <= this->min)
        variable = this->min;
    else
        variable = variable - stepSize;

    if (this->callback)
        this->callback(false);
}

MenuItem* NumericSelector::action() {
    setEditingState(false);
    if (this->callback)
        this->callback(true);

    return this->getParent();
}
