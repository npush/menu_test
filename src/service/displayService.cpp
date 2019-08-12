#include <Arduino.h>

#include "menu.h"

void renderMenuItems(menuItem* sellectedMenu, uint8_t itemsToRender = 4)
{
    menuItem* tmpMenu;
    if (isNullMenu(sellectedMenu)) {
        // init menu.
        Serial.println(F("Menu:"));
        tmpMenu = getMenuItem(Menu_1);
        //@ todo remove
        //setMenu(tmpMenu);
    } else {
        tmpMenu = GET_PREVIOUS(sellectedMenu);
        if (isNullMenu(tmpMenu)) {
            tmpMenu = sellectedMenu;
        }
            // Print Parent menu name
        if (!isNullMenu(GET_PARENT(tmpMenu))) {
            Serial.println((const __FlashStringHelper*)GET_NAME(GET_PARENT(tmpMenu)));
        }
    }
    while (!isNullMenu(tmpMenu) && itemsToRender > 0) {
        if(tmpMenu == sellectedMenu) {
            Serial.print(F("--->"));
            Serial.println((const __FlashStringHelper*)GET_NAME(tmpMenu));
        } else
        {
            Serial.println((const __FlashStringHelper*)GET_NAME(tmpMenu));
        }
        itemsToRender--;
        tmpMenu = GET_NEXT(tmpMenu);
    }
}