#include "menu.h"

enum menuItemIndex {Null_Menu = 0, Menu_1, Menu_2, Menu_3, Menu_4};
// name, previous, next, parent, child
const menuItem PROGMEM menu[] = {
   prepareMenuItem("root", 0, 0, 0, 0, Null_Menu),
   prepareMenuItem("Menu_1", &menu[Null_Menu], &menu[Menu_2], &menu[Null_Menu], &menu[Null_Menu], Menu_1),
   prepareMenuItem("Menu_2", &menu[Menu_1], &menu[Menu_3], &menu[Null_Menu], &menu[Null_Menu], Menu_2),
   prepareMenuItem("Menu_3", &menu[Menu_2], &menu[Menu_4], &menu[Null_Menu], &menu[Null_Menu], Menu_3),
   prepareMenuItem("Menu_4", &menu[Menu_3], &menu[Null_Menu], &menu[Null_Menu], &menu[Null_Menu], Menu_4)
};

volatile menuItem* selectedMenuItem;

void initMenu(void)
{
    selectedMenuItem = (menuItem*)pgm_read_word(&menu[Menu_2]);
}

volatile menuItem* getSelectedMenuItem(void)
{
    return selectedMenuItem;
}

menuItemIndex getSelectedMenuIndex(void)
{
    return (menuItemIndex)pgm_read_byte(&selectedMenuItem->id);
}

menuItem* getMenuItem(menuItemIndex index)
{
    return (menuItem*)pgm_read_word(&menu[index]);
}

void setMenu(menuItem* NewMenu)
{
    if (isNullMenu(NewMenu)) {
     
      return;
    }
    selectedMenuItem = NewMenu;
}

/*
* @param
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