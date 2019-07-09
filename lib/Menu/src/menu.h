#include <Arduino.h>

typedef struct{
    void *previous;
    void *next;
    void *parent;
    void *child;
    const char name[10];
    uint8_t id;
}menuItem;

#define prepareMenuItem(name, previous, next, parent, child, id)\
       {(void*)previous, (void*)next, (void*)parent, (void*)child, {name}, id}

#define GET_PREVIOUS(_menuItem) (menuItem*)pgm_read_word(&(_menuItem->previous)))
#define GET_NEXT(_menuItem)     ((menuItem*)pgm_read_word(&(_menuItem->next)))
#define GET_PARENT(_menuItem)   ((menuItem*)pgm_read_word(&(_menuItem->parent)))
#define GET_CHILD(_menuItem)    ((menuItem*)pgm_read_word(&(_menuItem->child)))
#define GET_NAME(_menuItem)     (&(_menuItem->name))
#define GET_ID(_menuItem)       ((menuItemIndex)pgm_read_byte(&(_menuItem->id)))

enum menuItemIndex {Null_Menu = 0, Menu_1, Menu_2, Menu_3, Menu_4};

menuItem* getMenuItem(menuItemIndex);
bool isNullMenu(menuItem*);
menuItem* renderMenu(uint8_t, menuItem*);