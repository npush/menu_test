#include "menu.h"

//                  name,       previous,       next,               parent,             child,      id
const menuItem PROGMEM menu[] = {
   prepareMenuItem("root", 0, 0, 0, 0, Null_Menu, MenuItem),
   prepareMenuItem("Menu_1", &menu[Null_Menu], &menu[Menu_2], &menu[Null_Menu], &menu[Null_Menu], Menu_1, MenuItem),
   prepareMenuItem("Menu_2", &menu[Menu_1], &menu[Menu_3], &menu[Null_Menu], &menu[Null_Menu], Menu_2, MenuItem),
   prepareMenuItem("Menu_3", &menu[Menu_2], &menu[Menu_4], &menu[Null_Menu], &menu[Null_Menu], Menu_3, MenuItem),
   prepareMenuItem("Menu_4", &menu[Menu_3], &menu[Null_Menu], &menu[Null_Menu], &menu[Null_Menu], Menu_4, MenuItem)
};

menuItem* selectedMenuItem = (menuItem*)&menu[Null_Menu];

menuItem* getSelectedMenu()
{
    return selectedMenuItem;
}

void setMenu(menuItem* tempMenu)
{
    if (isNullMenu(tempMenu)) {
        return;
    }
    selectedMenuItem = tempMenu;
}

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
    if (menuItem == getMenuItem(Null_Menu)) {
 		return true;
 	}
     return false;
}



menuItemType performMenuAction(menuItem* selectedItem)
{
    switch (GET_TYPE(selectedItem)) {
        case MenuItem:
            if (!isNullMenu(GET_CHILD(selectedItem))) {
                selectedItem = GET_CHILD(selectedItem);
            }
            break;
        case FunctionItem:
            //return GET_ID(selectedItem);
            break;
        default:
            break;
    }
}
