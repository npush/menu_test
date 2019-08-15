#include <Arduino.h>
#include "fsm.h"
#include "menu.h"
#include "taskManager.h"

typedef void (*MKA)(enum events, bool keyState);

const MKA PROGMEM FSM_table[5][4] = {
    //menuKey  upKey downKey exitKey
    {&showMenuF, NULL, NULL, NULL},   // initial
    {&showMenuF, NULL, NULL, NULL},   // idle
    {&showMenuF, &showMenuF, &showMenuF, &initialF},//displayMenu
    {&editParamF, &editParamF, &editParamF, &showMenuF},  //editParam
    {NULL, NULL, NULL, &initialF} //runFunction
};

volatile states softState = initial;

void setState(states newState)
{
    softState = newState;
}

bool isNewState(states newState)
{
    if (softState != newState) {
        return true;
    }

    return false;
}

void doEvent(enum events e, bool keyState)
{
    if (pgm_read_word(&FSM_table[softState][e]) == NULL) {
  
        return;
    }
    (*(MKA)pgm_read_word(&FSM_table[softState][e]))(e, keyState);
}
// Call initilization fuictions
void initialF(enum events e, bool keyState)
{
    Serial.println("initil envent");
    switch (e) {
        default:
            break;
    }
    setState(idle);
}

void idleF(enum events e, bool keyState)
{
    setState(idle);
    Serial.println("idel envent");
}

void showMenuF(enum events e, bool keyState)
{
    char itemType;
    // if first time in state
    if (softState != displayMenu) {
        setState(displayMenu);
        addTask(renderMenuItems(getSelectedMenu(), 4));
        //renderMenuItems(getSelectedMenu(), 4);
        return;
    }
    
    itemType = resolveMenuItem(e, keyState);
    switch (itemType) {
        case MenuItem:
            /* code */
            //setNext();
            break;
        case PropertyItem:
            setState(editParam);
            // emmit event Edit Params (e)
            /* code */
            break;
        case FunctionItem:
            setState(runFunction);
            // emmit event Run Function (e, parametr)
            /* code */
            break;
        default:
            break;
    }

    //refresh display
    renderMenuItems(getSelectedMenu(), 4);
}

void editParamF(enum events e, bool keyState)
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

void runFunctionF(enum events e, bool keyState)
{
    setState(runFunction);
    Serial.println("runFunctionF envent");
    switch (e) {
        default:
            break;
    }
}

// private function
menuItemType resolveMenuItem(enum events e, bool keyState)
{
        // call menu navigation rounine
    switch (e) {
        // Walk thrue menu
        case upKey:
            //Serial.println("do UpKey event");
            //Serial.println("do print menu event");
            setMenu(GET_NEXT(getSelectedMenu()));
            break;
        case downKey:
            //Serial.println("do DownpKey event");
            //Serial.println("do print menu event");
            setMenu(GET_PREVIOUS(getSelectedMenu()));
            break;
        case menuKey:
            Serial.println("do menuDo event");
            /* here you must call service */
            performMenuAction(getSelectedMenu());
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
