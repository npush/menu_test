#include <Arduino.h>
#include "U8g2lib.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R0, /* CS=*/ 10, /* reset=*/ 8);

typedef struct PROGMEM{
    void *previous;
    void *next;
    void *parent;
    void *child;
    const char name[10];
}menuItem;

#define NULL_ENTRY Null_Menu
menuItem Null_Menu = {(void*)0, (void*)0, (void*)0, (void*)0, {0x00}};

menuItem* selectedMenuItem;

enum {Menu_1 = 1, Menu_2, Menu_3, Menu_4};

#define makeMenuItem(menuName, previous, next, parent, child, name)\
        menuItem menuName = {(void*)&previous, (void*)&next, (void*)&parent, (void*)&child, {name}}

#define PREVIOUS   ((menuItem*)pgm_read_word(&selectedMenuItem->Previous))
#define NEXT       ((menuItem*)pgm_read_word(&selectedMenuItem->Next))
#define PARENT     ((menuItem*)pgm_read_word(&selectedMenuItem->Parent))
#define CHILD      ((menuItem*)pgm_read_word(&selectedMenuItem->Child))
#define SELECT		(pgm_read_byte(&selectedMenuItem->Select))

void setup(void) {
    u8g2.begin();
    makeMenuItem(setup11, NULL_ENTRY, setup12, NULL_ENTRY, NULL_ENTRY,"setup");
    makeMenuItem(setup12, NULL_ENTRY, NULL_ENTRY, NULL_ENTRY, NULL_ENTRY,"setup");
    makeMenuItem(setup13, NULL_ENTRY, NULL_ENTRY, NULL_ENTRY, NULL_ENTRY,"setup");
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
