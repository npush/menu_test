#include <Arduino.h>

#include "Keypad.h"
#include "keyconfig.h"
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
}
