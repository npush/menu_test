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
        //Serial.println((const __FlashStringHelper*)GET_NAME(getSelectedMenu()));
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
    switch (e) {
        // Walk thrue menu
        case upKey:
            //Serial.println("do UpKey event");
            //Serial.println("do print menu event");
            setMenu(GET_NEXT(getSelectedMenu()));
            renderMenuItems(getSelectedMenu(), 4);
            break;
        case downKey:
            //Serial.println("do DownpKey event");
            //Serial.println("do print menu event");
            setMenu(GET_PREVIOUS(getSelectedMenu()));
            renderMenuItems(getSelectedMenu(), 4);
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

void renderMenuItems(const menuItem* sellectedMenu, uint8_t itemsToRender = 4)
{
    menuItem* tmpMenu;
    if (isNullMenu(sellectedMenu)) {
        // init menu.
        Serial.println(F("Menu:"));
        tmpMenu = getMenuItem(Menu_1);
        //@ todo remove
        //setMenu(tmpMenu);
    } else {
        tmpMenu = GET_PREVIOUS(sellectedMenu);
        if (isNullMenu(tmpMenu)) {
            tmpMenu = sellectedMenu;
        }
            // Print Parent menu name
        if (!isNullMenu(GET_PARENT(tmpMenu))) {
            Serial.println((const __FlashStringHelper*)GET_NAME(GET_PARENT(tmpMenu)));
        }
    }
    while (!isNullMenu(tmpMenu) && itemsToRender > 0) {
        if(tmpMenu == sellectedMenu) {
            Serial.print(F("--->"));
            Serial.println((const __FlashStringHelper*)GET_NAME(tmpMenu));
        } else
        {
            Serial.println((const __FlashStringHelper*)GET_NAME(tmpMenu));
        }
        itemsToRender--;
        tmpMenu = GET_NEXT(tmpMenu);
    }
}

void callMenu(*menuItem tmpMenu)
{

}