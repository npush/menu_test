#ifndef Keyconfig_h
#define Keyconfig_h

#include <Arduino.h>

const byte ROWS = 4;
const byte COLS = 1;

char keys[ROWS][COLS] = {
    {'1'},
    {'2'},
    {'3'},
    {'4'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {3}; //connect to the column pinouts of the kpd

#endif