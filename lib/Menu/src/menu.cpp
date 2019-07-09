#include "menu.h"

// name, previous, next, parent, child, id
const menuItem PROGMEM menu[] = {
   prepareMenuItem("root", 0, 0, 0, 0, Null_Menu),
   prepareMenuItem("Menu_1", &menu[Null_Menu], &menu[Menu_2], &menu[Null_Menu], &menu[Null_Menu], Menu_1),
   prepareMenuItem("Menu_2", &menu[Menu_1], &menu[Menu_3], &menu[Null_Menu], &menu[Null_Menu], Menu_2),
   prepareMenuItem("Menu_3", &menu[Menu_2], &menu[Menu_4], &menu[Null_Menu], &menu[Null_Menu], Menu_3),
   prepareMenuItem("Menu_4", &menu[Menu_3], &menu[Null_Menu], &menu[Null_Menu], &menu[Null_Menu], Menu_4)
};

/*
* Return pointer to menuItem
*
* @param menuItemIndex index
*/
menuItem* getMenuItem(menuItemIndex index)
{
    return (menuItem*)&menu[index];
}

/*
* @param menuItem menuItem
* @return bool
*/
bool isNullMenu(menuItem* menuItem)
{
    Serial.println((int) menuItem, HEX);
    if (menuItem == getMenuItem(Null_Menu)) {
        Serial.println("true");
 		return true;
 	}
Serial.println("false");
     return false;
}

menuItem* renderMenu(uint8_t itemsToRender = 8, menuItem* lastMenu = NULL)
{
    menuItem* tempMenu;
    int8_t idx = 0;
    if (lastMenu == NULL) {
        tempMenu = getMenuItem(Menu_1);
    } else {
        tempMenu = lastMenu;
    }
    while (itemsToRender > 1) {
        if (isNullMenu(tempMenu)) {
		    return tempMenu;
	    }
        Serial.println((const __FlashStringHelper*)GET_NAME(tempMenu));
        tempMenu = GET_NEXT(tempMenu);
        itemsToRender--;
    }
    return tempMenu;
}
