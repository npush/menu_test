#include <Arduino.h>
#include "U8g2lib.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R0, /* CS=*/ 10, /* reset=*/ 8);

typedef struct{
    void *previous;
    void *next;
    void *parent;
    void *child;
    const char name[10];
}menuItem;

#define NULL_ENTRY Null_Menu

menuItem* selectedMenuItem;

enum {Menu_1 = 1, Menu_2, Menu_3, Menu_4};

#define prepareMenuItem(menuName, name)\
        menuItem menuName PROGMEM = {(void*)0, (void*)0, (void*)0, (void*)0, {name}};

#define setMenuItem(menuName, _previous, _next, _parent, _child)\
        menuName.previous = &_previous;\
        menuName.next = &_next;\
        menuName.parent = &_parent;\
        menuName.child = &_child;\

#define PREVIOUS   ((menuItem*)pgm_read_word(&selectedMenuItem->Previous))
#define NEXT       ((menuItem*)pgm_read_word(&selectedMenuItem->Next))
#define PARENT     ((menuItem*)pgm_read_word(&selectedMenuItem->Parent))
#define CHILD      ((menuItem*)pgm_read_word(&selectedMenuItem->Child))

prepareMenuItem(Null_Menu, 0x00);

    prepareMenuItem(setup11, "menu1");
    prepareMenuItem(setup12, "menu2");
    prepareMenuItem(setup13, "menu3");
    prepareMenuItem(setup21, "menu4");


void menuChange(menuItem* NewMenu)
{
	if ((void*)NewMenu == (void*)&NULL_ENTRY)
	  return;
 
	selectedMenuItem = NewMenu;
}

void initMenu(void) {
	selectedMenuItem = (menuItem*)&setup11;
}

void setup(void) {
    u8g2.begin();

    setMenuItem(setup11, NULL_ENTRY, setup12, NULL_ENTRY, setup21);
    setMenuItem(setup12, setup11, setup13, NULL_ENTRY, NULL_ENTRY);
    setMenuItem(setup13, setup12, NULL_ENTRY, NULL_ENTRY, NULL_ENTRY);
    setMenuItem(setup21, NULL_ENTRY, NULL_ENTRY, setup11, NULL_ENTRY);

    initMenu();
}

void loop(void) {
    u8g2.clearBuffer();
    // code
    u8g2.setFontDirection(0);
    u8g2.setFont(u8g2_font_inb16_mf);
    u8g2.drawStr(1,54, "U+0089");
    u8g2.sendBuffer();
    delay(1000);
}
