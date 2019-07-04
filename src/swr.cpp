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

menuItem* selectedMenuItem;

enum {Null_Menu = 0, Menu_1, Menu_2, Menu_3, Menu_4};

#define prepareMenuItem(name, previous, next, parent, child)\
        {(void*)next, (void*)previous, (void*)parent, (void*)child, {name}}

const menuItem PROGMEM menu[] = {
    prepareMenuItem(0x00, 0, 0, 0, 0),
    prepareMenuItem("Menu_1", &menu[Null_Menu], &menu[Menu_2],0 ,0),
    prepareMenuItem("Menu_2", &menu[Menu_1], &menu[Menu_3], 0 ,0),
    prepareMenuItem("Menu_3", &menu[Menu_2], &menu[Null_Menu], 0 ,0)
};

#define PREVIOUS   ((menuItem*)pgm_read_word(&selectedMenuItem->Previous))
#define NEXT       ((menuItem*)pgm_read_word(&selectedMenuItem->Next))
#define PARENT     ((menuItem*)pgm_read_word(&selectedMenuItem->Parent))
#define CHILD      ((menuItem*)pgm_read_word(&selectedMenuItem->Child))
//&(string_table[i]))

void menuChange(menuItem* NewMenu)
{
	if ((void*)NewMenu == (void*)&menu[Null_Menu])
	  return;
 
	selectedMenuItem = NewMenu;
}

void initMenu(void) {
	selectedMenuItem = (menuItem*)&menu[Menu_1];
}

void renderMenu(void) {
	menuItem* tempMenu;
	tempMenu = (menuItem*)pgm_read_word(&selectedMenuItem->parent);
	if ((void*)tempMenu == (void*)&menu[Null_Menu]) {
		Serial.println((const char *)PSTR("MENU:"));
	} else {
		Serial.println((const char *)tempMenu->name);
	}
	Serial.println((const char *)selectedMenuItem->name);
}

void setup(void) {
    Serial.begin(5760);
    u8g2.begin();
    initMenu();
    Serial.println((const char *)selectedMenuItem->name);
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
