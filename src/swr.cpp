#include <Arduino.h>

#include "Keypad.h"
#include "keyconfig.h"
#include "menu.h"
#include "fsm.h"
#include "display.h"

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup(void)
{
    Serial.begin(57600);
    initDisplay();
    Serial.println("OK:");
    //#define FPSTR(pstr_pointer) (reinterpret_cast<const __FlashStringHelper *>(pstr_pointer))
    //Serial.println(FPSTR(&getSelectedMenuItem()->name));
}

void loop(void)
{

    char key = kpd.getKey();

// 1 -> menu 2 -> up 3 -> down 4 -> exit

    if (key == '1'){
        doEvent(menuKey);
        Serial.println((const __FlashStringHelper*)GET_NAME(getSelectedMenu()));
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

    //draw_page();

    // u8g2.firstPage();
    // do {
    //     /* all graphics commands have to appear within the loop body. */    
    //     u8g2.setFont(u8g2_font_ncenB14_tr);
    //     u8g2.drawStr(0,20,"Hello World!");
    // } while ( u8g2.nextPage() );
}

void initialF(enum events e)
{
    setState(initial);
    Serial.println("initil envent");
    switch (e) {
        default:
            break;
    }
}

void displayMenuF(enum events e)
{
    setState(displayMenu);
    Serial.println("Menu display envent");
    switch (e) {
        // Walk thrue menu
        case upKey:
            //Serial.println("do UpKey event");
            //Serial.println("do print menu event");
            renderMenuItems(getSelectedMenu(), Serial::*println);
            break;
        case downKey:
            Serial.println("do DownpKey event");
            Serial.println("do print menu event");
            break;
        case menuKey:
            Serial.println("do menuDo event");
            // Enter in child menu
            
            // Edit param
            //softState = editParam;

            // Perform menuFunction
            //softState = runFunction;

            break;
        default:
            break;
    }
}

void editParamF(enum events e)
{
    setState(editParam);
    Serial.println("editParamF envent");
    switch (e) {
        case upKey:
            Serial.println("do UpKey event");
            break;
        case downKey:
            Serial.println("do DownpKey event");
            break;
        case menuKey:
            Serial.println("do save param event");
            break;
        default:
            break;
    }

}

void runFunctionF(enum events e)
{
    setState(runFunction);
    Serial.println("runFunctionF envent");
    switch (e) {
        default:
            break;
    }
}