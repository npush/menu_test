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
    softState = initial;
    Serial.println("initil envent");
    switch (e) {
        default:
            break;
    }
}

void displayMenuF(enum events e)
{
    softState = displayMenu;
    Serial.println("Menu display envent");
    switch (e) {
        // Walk thrue menu
        case upKey:
            Serial.println("do UpKey event");
            Serial.println("do print menu event");
            break;
        case downKey:
            Serial.println("do DownpKey event");
            Serial.println("do print menu event");
            break;
        case menuKey:
            Serial.println("do menuDo event");
            // Enter in child menu
            
            // Edit param
            //softState = editParam;

            // Perform menuFunction
            //softState = runFunction;

            break;
        default:
            break;
    }
}

void editParamF(enum events e)
{
    softState = editParam;
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
    softState = runFunction;
    Serial.println("runFunctionF envent");
    switch (e) {
        default:
            break;
    }
}
