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

    Serial.println("do print menu event");
    
    softState = displayMenu;
    switch (e) {
        // Walk thrue menu
        case upKey:
            Serial.println("do UpKey event");
            break;
        case downKey:
            Serial.println("do DownpKey event");
            break;
        case exitKey:
            Serial.println("do ExitKey event");
            softState = initial;
            break;
        case menuKey:
            Serial.println("do menuDo event");
            // Enter in child menu
            
            // Edit param

            // Perform menuFunction
            break;
        default:
            break;
    }
}

void editParamF(enum events e)
{
    Serial.println("editParamF envent");
    softState = editParam;
    switch (e) {
        case upKey:
            Serial.println("do UpKey event");
            break;
        case downKey:
            Serial.println("do DownpKey event");
            break;
        case exitKey:
            Serial.println("do ExitKey event");
            softState = displayMenu;
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
    Serial.println("runFunctionF envent");
    softState = runFunction;
    switch (e) {
        case exitKey:
            Serial.println("Exit to main menu");
            softState = displayMenu;
            break;
        
        default:
            break;
    }
}
