#include "NumericSelector.h"

NumericSelector::NumericSelector(MenuItem *parent, const FlashString *text,
                                 SelectCallback callback)
    : MenuItem(parent, text), callback(callback){};

MenuItem *NumericSelector::action() {
  setEditingState(false);
  if (callback)
    callback(true);
  return getParent();
}

NumericSelectorUint8::NumericSelectorUint8(MenuItem *parent,
                                           const FlashString *text,
                                           uint8_t &variable, uint8_t lower,
                                           uint8_t upper, uint8_t stepSize,
                                           uint8_t stepSizeFast,
                                           const FlashString *unit,
                                           SelectCallback callback)
    : NumericSelector(parent, text, callback), variable(variable),
      oldValue(variable), lower(lower), upper(upper), stepSize(stepSize), stepSizeFast(stepSizeFast) {
  this->unit = unit;
};

NumericSelectorInt16::NumericSelectorInt16(
    MenuItem *parent, const FlashString *text, int16_t &variable, int16_t lower,
    int16_t upper, int16_t stepSize, int16_t stepSizeFast, uint8_t decPlaces, const FlashString *unit,
    SelectCallback callback)
    : NumericSelector(parent, text, callback), variable(variable),
      oldValue(variable), lower(lower), upper(upper), stepSize(stepSize), stepSizeFast(stepSizeFast),
      decPlaces(decPlaces) {
  this->unit = unit;
};

NumericSelectorList::NumericSelectorList(MenuItem *parent,
                                         const FlashString *text,
                                         uint8_t &variable, uint8_t upper,
                                         const char **arr,
                                         SelectCallback callback)
    : NumericSelector(parent, text, callback), variable(variable),
      oldValue(variable), lower(0), upper(upper), stepSize(1), arr(arr){};

bool NumericSelectorUint8::activate() { return activateT(variable, oldValue); }
bool NumericSelectorInt16::activate() { return activateT(variable, oldValue); }
bool NumericSelectorList::activate() { return activateT(variable, oldValue); }

void NumericSelectorUint8::deactivate() { deactivateT(variable, oldValue); }
void NumericSelectorInt16::deactivate() { deactivateT(variable, oldValue); }
void NumericSelectorList::deactivate() { deactivateT(variable, oldValue); }

void NumericSelectorUint8::doIncr() { doIncrT(variable, upper, stepSize); }
void NumericSelectorInt16::doIncr() { doIncrT(variable, upper, stepSize); }
void NumericSelectorList::doIncr() { doIncrT(variable, upper, stepSize); }

void NumericSelectorUint8::doDecr() { doDecrT(variable, lower, stepSize); }
void NumericSelectorInt16::doDecr() { doDecrT(variable, lower, stepSize); }
void NumericSelectorList::doDecr() { doDecrT(variable, lower, stepSize); }

void NumericSelectorUint8::doIncrFast() { doIncrT(variable, upper, stepSizeFast); }
void NumericSelectorInt16::doIncrFast() { doIncrT(variable, upper, stepSizeFast); }
void NumericSelectorList::doIncrFast() { doIncrT(variable, upper, stepSize); }

void NumericSelectorUint8::doDecrFast() { doDecrT(variable, lower, stepSizeFast); }
void NumericSelectorInt16::doDecrFast() { doDecrT(variable, lower, stepSizeFast); }
void NumericSelectorList::doDecrFast() { doDecrT(variable, lower, stepSize); }


const char *NumericSelectorUint8::getSecondaryText() {
  snprintf_P(valueStr, 18, PSTR("%d %S"), variable, unit);
  return valueStr;
}

const char *NumericSelectorInt16::getSecondaryText() {
  snprintf_P(valueStr, 18, PSTR("%s %S"), intDecimal(variable, decPlaces), unit);
  return valueStr;
}

const char *NumericSelectorList::getSecondaryText() {
  snprintf_P(valueStr, 18, PSTR("%s"), arr[variable]);
  return valueStr;
}
