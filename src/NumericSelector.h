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
  typedef void (*SelectCallback)(bool);
  NumericSelector(MenuItem *parent, const FlashString *text,
                  SelectCallback callback = NULL);

  template <class T> bool activateT(T &val, T &oldVal) {
    oldVal = val;
    setEditingState(true);
    return 1;
  }

  template <class T> void deactivateT(T &val, T &oldVal) {
    val = oldVal;
    setEditingState(false);
    if (callback)
      callback(false);
  }

  template <class T> void doNextT(T &val, T upper, T incr) {
    if (val + incr > upper)
      val = upper;
    else
      val += incr;
    if (callback)
      callback(false);
  }

  template <class T> void doPrevT(T &val, T lower, T incr) {
    if (val - incr < lower)
      val = lower;
    else
      val -= incr;
    if (callback)
      callback(false);
  }

  MenuItem *action();

protected:
  SelectCallback callback;
  const FlashString *unit;
  char valueStr[18];
};

class NumericSelectorUint8 : public NumericSelector {
public:
  typedef void (*SelectCallback)(bool);

  NumericSelectorUint8(MenuItem *parent, const FlashString *text,
                       uint8_t &variable, uint8_t lower, uint8_t upper,
                       uint8_t stepSize = 1, const FlashString *unit = NULL,
                       SelectCallback callback = NULL);

  char getTypeId() { return 'b'; };

  const char *getSecondaryText();

  bool activate();
  void deactivate();

  void doNext();
  void doPrev();

private:
  uint8_t &variable;
  uint8_t oldValue, lower, upper, stepSize;
};

class NumericSelectorInt16 : public NumericSelector {
public:
  typedef void (*SelectCallback)(bool);

  NumericSelectorInt16(MenuItem *parent, const FlashString *text,
                       int16_t &variable, int16_t lower, int16_t upper,
                       int16_t stepSize = 1, const FlashString *unit = NULL,
                       SelectCallback callback = NULL);

  char getTypeId() { return 'i'; };

  const char *getSecondaryText();

  bool activate();
  void deactivate();

  void doNext();
  void doPrev();

private:
  int16_t &variable;
  int16_t oldValue, lower, upper, stepSize;
};

class NumericSelectorList : public NumericSelector {
public:
  typedef void (*SelectCallback)(bool);

  NumericSelectorList(MenuItem *parent, const FlashString *text,
                      uint8_t &variable, uint8_t upper, const char **arr = NULL,
                      SelectCallback callback = NULL);

  char getTypeId() { return 'l'; };

  const char *getSecondaryText();

  bool activate();
  void deactivate();

  void doNext();
  void doPrev();

private:
  uint8_t &variable;
  uint8_t oldValue, lower, upper, stepSize;
  const char **arr = NULL;
};

#endif
