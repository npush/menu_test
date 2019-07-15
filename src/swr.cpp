#include <Arduino.h>
#include "U8g2lib.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include "Keypad.h"
#include "menu.h"
#include "fsm.h"

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

menuItem* selectedMenuItem;

//U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R0, /* CS=*/ 10, /* reset=*/ 8);
U8G2_ST7920_128X64_2_HW_SPI u8g2(U8G2_R0, /* CS=*/ 10, /* reset=*/ 8);

uint8_t stringHeight = u8g2.getMaxCharHeight();
uint8_t displayHeight = u8g2.getDisplayHeight();
uint8_t displayWidth = u8g2.getDisplayWidth();
uint8_t maxStrings = displayHeight / stringHeight;

#define MAX_MENU_ITEMS 8

// this is the state machine, which will replace the do - while loop
void draw_page(void) 
{
    static uint8_t is_next_page = 0;

    // call to first page, if required
    if (is_next_page == 0) {
        u8g2.firstPage();
        is_next_page = 1;
    }

    // draw our screen
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(0,20,"Hello World!");

    // call to next page
    if (u8g2.nextPage() == 0) {
        is_next_page = 0;			// ensure, that first page is called
    }  
}

void setup(void)
{
    Serial.begin(57600);
    //uint8_t menu_select_pin, 
    //uint8_t menu_next_pin, 
    //uint8_t menu_prev_pin, uint8_t 
    //menu_up_pin = U8X8_PIN_NONE, 
    //uint8_t menu_down_pin = U8X8_PIN_NONE, 
    //uint8_t menu_home_pin = U8X8_PIN_NONE
    u8g2.begin();
    Serial.println("OK:");

    selectedMenuItem = getMenuItem(Null_Menu);

    //#define FPSTR(pstr_pointer) (reinterpret_cast<const __FlashStringHelper *>(pstr_pointer))
    //Serial.println(FPSTR(&getSelectedMenuItem()->name));
}

void loop(void)
{

    char key = kpd.getKey();

// 1 -> menu 2 -> up 3 -> down 4 -> exit

    if (key == '1'){
        doEvent(menuKey);
        Serial.println((const __FlashStringHelper*)GET_NAME(selectedMenuItem));
    }

    if (key == '2'){
        doEvent(upKey);
    }

    if (key == '3'){
        doEvent(downKey);
    }
    if (key == '4'){
        doEvent(exitKey);
    }

    //u8g2.clearBuffer();
    // //code
    //u8g2.setFontDirection(0);
    //u8g2.setFont(u8g2_font_inb16_mf);
    //u8g2.drawStr(1,54, "U+0089");
    //u8g2.sendBuffer();
    //delay(1000);

    draw_page();

    // u8g2.firstPage();
    // do {
    //     /* all graphics commands have to appear within the loop body. */    
    //     u8g2.setFont(u8g2_font_ncenB14_tr);
    //     u8g2.drawStr(0,20,"Hello World!");
    // } while ( u8g2.nextPage() );
}
