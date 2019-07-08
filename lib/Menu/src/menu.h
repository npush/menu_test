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

#define GET_PREVIOUS   ((menuItem*)pgm_read_word(&(getSelectedMenuItem()->previous)))
#define GET_NEXT       ((menuItem*)pgm_read_word(&(getSelectedMenuItem()->next)))
#define GET_PARENT     ((menuItem*)pgm_read_word(&(getSelectedMenuItem()->parent)))
#define GET_CHILD      ((menuItem*)pgm_read_word(&(getSelectedMenuItem()->child)))
#define GET_NAME        ((const char *)&(getSelectedMenuItem()->name))
#define GET_ID          ((menuItemIndex)pgm_read_byte(&(getSelectedMenuItem()->id)))

void setMenu(menuItem* NewMenu);
void initMenu(void);
menuItem* getSelectedMenuItem(void);
menuItem* getMenuItem(char index);
bool isNullMenu(menuItem* menuItem);
