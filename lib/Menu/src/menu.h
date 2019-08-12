#ifndef Menu_h
#define Menu_h

#include <Arduino.h>

enum menuItemType {MenuItem, FunctionItem};

typedef struct{
    void *previous;
    void *next;
    void *parent;
    void *child;
    const char name[10];
    uint8_t id;
    menuItemType type;
}menuItem;

#define prepareMenuItem(name, previous, next, parent, child, id, type)\
       {(void*)previous, (void*)next, (void*)parent, (void*)child, {name}, id, type}

#define GET_PREVIOUS(_menuItem) ((menuItem*)pgm_read_word(&(_menuItem->previous)))
#define GET_NEXT(_menuItem)     ((menuItem*)pgm_read_word(&(_menuItem->next)))
#define GET_PARENT(_menuItem)   ((menuItem*)pgm_read_word(&(_menuItem->parent)))
#define GET_CHILD(_menuItem)    ((menuItem*)pgm_read_word(&(_menuItem->child)))
#define GET_NAME(_menuItem)     (&(_menuItem->name))
#define GET_ID(_menuItem)       ((menuItemIndex)pgm_read_byte(&(_menuItem->id)))
#define GET_TYPE(_menuItem)     ((menuItemType)pgm_read_word(&(_menuItem->type)))

enum menuItemIndex {Null_Menu = 0, Menu_1, Menu_2, Menu_3, Menu_4};

menuItem* getSelectedMenu();
menuItem* getMenuItem(menuItemIndex);
bool isNullMenu(menuItem*);
void renderMenuItems(menuItem*, uint8_t);
void setMenu(menuItem*);
uint8_t performMenuAction(menuItem*);

#endif // !Menu_h