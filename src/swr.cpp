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

U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R0, /* CS=*/ 10, /* reset=*/ 8);

void renderMenu(uint8_t itemsToRender)
{
	menuItem* tempMenu = GET_PARENT;
	if (isNullMenu(tempMenu)) {
		Serial.println(F("MENU:"));
	} else {
		Serial.println((const __FlashStringHelper*)tempMenu->name);
	}
	Serial.println((const __FlashStringHelper*)GET_NAME);
}

void setup(void)
{
    Serial.begin(57600);
    u8g2.begin();
    initMenu();
    // point to first array element in flash
    const char *name = (const char *)&getSelectedMenuItem()->name;
    // potin to itemMenu address in flash
    menuItem *next = (menuItem*)pgm_read_word(&getSelectedMenuItem()->next);
    menuItem *prev = GET_PREVIOUS;
    Serial.println("OK:");
    Serial.println((const __FlashStringHelper*)GET_NAME);

    //#define FPSTR(pstr_pointer) (reinterpret_cast<const __FlashStringHelper *>(pstr_pointer))
    //Serial.println(FPSTR(&getSelectedMenuItem()->name));
}

void loop(void)
{

    char key = kpd.getKey();

// 1 -> menu 2 -> up 3 -> down 4 -> exit

    if (key == '1'){
        doEvent(remap(key));
        Serial.println((const __FlashStringHelper*)GET_NAME);
    }

    if (key == '2'){
        doEvent(remap(key));
        setMenu(GET_NEXT);
        Serial.println((const __FlashStringHelper*)GET_NAME);
    }

    if (key == '3'){
        doEvent(remap(key));
        setMenu(GET_PREVIOUS);
        Serial.println((const __FlashStringHelper*)GET_NAME);
    }
    if (key == '4'){
        doEvent(remap(key));
        initMenu();
    }

    u8g2.clearBuffer();
    // code
    u8g2.setFontDirection(0);
    u8g2.setFont(u8g2_font_inb16_mf);
    u8g2.drawStr(1,54, "U+0089");
    u8g2.sendBuffer();
    //delay(1000);
}
