#include <Arduino.h>
#include "U8g2lib.h"
#include "display.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R0, /* CS=*/ 10, /* reset=*/ 8);
U8G2_ST7920_128X64_2_HW_SPI u8g2(U8G2_R0, /* CS=*/ 10, /* reset=*/ 8);

uint8_t stringHeight = u8g2.getMaxCharHeight();
uint8_t displayHeight = u8g2.getDisplayHeight();
uint8_t displayWidth = u8g2.getDisplayWidth();
uint8_t maxStrings = displayHeight / stringHeight;

#define MAX_MENU_ITEMS 8

void initDisplay()
{
    //uint8_t menu_select_pin, 
    //uint8_t menu_next_pin, 
    //uint8_t menu_prev_pin, uint8_t 
    //menu_up_pin = U8X8_PIN_NONE, 
    //uint8_t menu_down_pin = U8X8_PIN_NONE, 
    //uint8_t menu_home_pin = U8X8_PIN_NONE
    u8g2.begin();
}

// this is the state machine, which will replace the do - while loop
void draw_page(void (*callBack)(void)) 
{
    static uint8_t is_next_page = 0;

    // call to first page, if required
    if (is_next_page == 0) {
        u8g2.firstPage();
        is_next_page = 1;
    }
    callBack();
    // draw our screen

    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.drawStr(0, 20, "Hello World!");

    // call to next page
    if (u8g2.nextPage() == 0) {
        is_next_page = 0;			// ensure, that first page is called
    }  
}