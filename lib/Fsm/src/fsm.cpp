#include <Arduino.h>
#include "fsm.h"

typedef void (*MKA)(enum events, void (*f)());

const MKA PROGMEM FSM_table[4][4] = {
    //menuKey  upKey downKey exitKey
    {&displayMenuF, NULL, NULL, NULL},   // initial
    {&displayMenuF, &displayMenuF, &displayMenuF, &initialF},//displayMenu
    {&editParamF, &editParamF, &editParamF, &displayMenuF},  //editParam
    {NULL, NULL, NULL, &initialF} //runFunction
};

volatile states softState = initial;

void setState(states newState)
{
    softState = newState;
}

void doEvent(enum events e)
{
    if (pgm_read_word(&FSM_table[softState][e]) == NULL) {
  
        return;
    }
    (*(MKA)pgm_read_word(&FSM_table[softState][e]))(e);
}

void initialF(enum events e, void (*f)())
{
    setState(initial);
    Serial.println("initil envent");
    switch (e) {
        default:
            break;
    }
}

void displayMenuF(enum events e)
{
    setState(displayMenu);
    // call menu navigation rounine
    switch (e)
    {
    case menuKey:
        /* code */
        editParamF(e);
        break;
    
    default:
        break;
    }
    
}

void editParamF(enum events e)
{
    setState(editParam);
    Serial.println("editParamF envent");
    switch (e) {
        case upKey:
            Serial.println("do UpKey event");
            break;
        case downKey:
            Serial.println("do DownpKey event");
            break;
        case menuKey:
            Serial.println("do save param event");
            break;
        default:
            break;
    }

}

void runFunctionF(enum events e)
{
    setState(runFunction);
    Serial.println("runFunctionF envent");
    switch (e) {
        default:
            break;
    }
}