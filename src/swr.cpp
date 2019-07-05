#include <Arduino.h>
#include "U8g2lib.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include "Keypad.h"

const byte ROWS = 4;
const byte COLS = 1;
char keys[ROWS][COLS] = {
    {'1'},
    {'2'},
    {'3'},
    {'4'}
};
byte rowPins[ROWS] = {7, 6, 5, 4}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {3}; //connect to the column pinouts of the kpd
Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


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
       {(void*)previous, (void*)next, (void*)parent, (void*)child, {name}}

const menuItem PROGMEM menu[] = {
   prepareMenuItem(0x00, 0, 0, 0, 0),
   prepareMenuItem("Menu_1", &menu[Null_Menu], &menu[Menu_2],0 ,0),
   prepareMenuItem("Menu_2", &menu[Menu_1], &menu[Menu_3], 0 ,0),
   prepareMenuItem("Menu_3", &menu[Menu_2], &menu[Menu_4], 0 ,0),
   prepareMenuItem("Menu_4", &menu[Menu_3], &menu[Null_Menu], 0 ,0)
};

#define PREVIOUS   ((menuItem*)pgm_read_word(&selectedMenuItem->previous))
#define NEXT       ((menuItem*)pgm_read_word(&selectedMenuItem->next))
#define PARENT     ((menuItem*)pgm_read_word(&selectedMenuItem->parent))
#define CHILD      ((menuItem*)pgm_read_word(&selectedMenuItem->child))
//&(string_table[i]))

void menuChange(menuItem* NewMenu)
{
    if ((void*)NewMenu == (void*)pgm_read_word(&menu[Null_Menu]))
      return;

    selectedMenuItem = NewMenu;
}

void initMenu(void) {
    selectedMenuItem = (menuItem*)pgm_read_word(&menu[Menu_2]);
}

void renderMenu(void) {
	menuItem* tempMenu;
	tempMenu = (menuItem*)pgm_read_word(&selectedMenuItem->parent);
	if ((void*)tempMenu == (void*)&menu[Null_Menu]) {
		Serial.println(F("MENU:"));
	} else {
		Serial.println((const char *)tempMenu->name);
	}
	Serial.println((const __FlashStringHelper*)&selectedMenuItem->name);
}

void setup(void) {
    Serial.begin(57600);
    u8g2.begin();
    initMenu();
    // point to first array element in flash
    const char *name = (const char *)&selectedMenuItem->name;
    // potin to itemMenu address in flash
    menuItem *next = (menuItem*)pgm_read_word(&selectedMenuItem->next);
    menuItem *prev = PREVIOUS;
    Serial.println("OK:");
    Serial.println((const __FlashStringHelper*)&selectedMenuItem->name);

    menuChange((menuItem*)pgm_read_word(&selectedMenuItem->next));
    Serial.println("chage menu:");
    #define FPSTR(pstr_pointer) (reinterpret_cast<const __FlashStringHelper *>(pstr_pointer))
    Serial.println(FPSTR(&selectedMenuItem->name));
}

void loop(void) {

    char key = kpd.getKey();
    
    if (key){
        Serial.println(key);
    }

    u8g2.clearBuffer();
    // code
    u8g2.setFontDirection(0);
    u8g2.setFont(u8g2_font_inb16_mf);
    u8g2.drawStr(1,54, "U+0089");
    u8g2.sendBuffer();
    delay(1000);
}
