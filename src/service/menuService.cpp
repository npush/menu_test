#include <Arduino.h>

#include "menu.h"
#include "fsm.h"

void menuNavigate(events e)
{
    switch (e) {
        // Walk thrue menu
        case upKey:
            //Serial.println("do UpKey event");
            //Serial.println("do print menu event");
            setMenu(GET_NEXT(getSelectedMenu()));
            renderMenuItems(getSelectedMenu(), 4);
            break;
        case downKey:
            //Serial.println("do DownpKey event");
            //Serial.println("do print menu event");
            setMenu(GET_PREVIOUS(getSelectedMenu()));
            renderMenuItems(getSelectedMenu(), 4);
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