#include <Arduino.h>

#ifndef IntDecimal_h
#define IntDecimal_h

void insertAndShift(char *cArray, int16_t size, int16_t index, char value);
char *intDecimal(int16_t val, uint8_t decPlaces = 0);

#endif
