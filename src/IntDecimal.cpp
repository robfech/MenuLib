#include "IntDecimal.h"

void insertAndShift(char *cArray, int16_t size, int16_t index, char value) {
  // insert a char value into array at given position and shift the remaining
  // elements to the right
  for (int i = size - 1; i > index; i--) {
    cArray[i] = cArray[i - 1];
  }
  cArray[index] = value;
}

char *intDecimal(int16_t val, uint8_t decPlaces) {
  // converts an integer into an char array and adds a decimal point
  static char cArray[8];
  snprintf_P(cArray, sizeof(cArray), PSTR("%d"), val);
  if (decPlaces < 1 || decPlaces > 4)
    return cArray;

  bool isNegativ = val < 0 ? true : false;
  int prependZeros = decPlaces + 1 + isNegativ - strlen(cArray);

  // add leading zeros if needed
  if (prependZeros > 0) {
    uint8_t i = isNegativ ? 1 : 0;
    int16_t zeros = prependZeros + isNegativ;
    for (; i < zeros; i++) {
      insertAndShift(cArray, sizeof(cArray), i, '0');
    }
  }
  // add decimal point
  const char decPoint = '.';
  int16_t index = strlen(cArray) - decPlaces;
  insertAndShift(cArray, sizeof(cArray), index, decPoint);

  return cArray;
}
