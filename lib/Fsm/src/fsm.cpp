#include <Arduino.h>
#include "fsm.h"

typedef void (*MKA)(enum events);

const MKA PROGMEM FSM_table[4][4] = {
    //menuKey  upKey downKey exitKey
    {&displayMenuF, NULL, NULL, NULL},   // initial
    {&displayMenuF, &displayMenuF, &displayMenuF, &initialF},//displayMenu
    {&editParamF, &editParamF, &editParamF, &displayMenuF},  //editParam
    {NULL, NULL, NULL, &initialF} //runFunction
};

volatile states softState = initial;

void doEvent(enum events e)
{
    if (pgm_read_word(&FSM_table[softState][e]) == NULL) {
  
        return;
    }
    (*(MKA)pgm_read_word(&FSM_table[softState][e]))(e);
}

void initialF(enum events e)
{
    Serial.println("initil envent");
}

void displayMenuF(enum events e)
{
    Serial.println("Menu display envent");
}

void editParamF(enum events e)
{
    Serial.println("editParamF envent");

}

void runFunctionF(enum events e)
{
    Serial.println("runFunctionF envent");

}

// 1 -> menu 2 -> up 3 -> down 4 -> exit
events remap(char key)
{
    if (key == '1')
        return menuKey;
    if (key == '2')
        return upKey;
    if (key == '3')
        return downKey;
    if (key == '4')
        return exitKey;
}
