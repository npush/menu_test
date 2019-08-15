#include <Arduino.h>

#include "Keypad.h"
#include "keyconfig.h"
#include "fsm.h"
#include "display.h"
#include "timer-api.h"
#include "taskManager.h"

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup(void)
{
    Serial.begin(57600);
    initDisplay();
    Serial.println("OK:");
    /**
    * freq: 20Hz
    * period: 50ms
    */
    timer_init_ISR_20Hz(TIMER_DEFAULT);
    //#define FPSTR(pstr_pointer) (reinterpret_cast<const __FlashStringHelper *>(pstr_pointer))
    //Serial.println(FPSTR(&getSelectedMenuItem()->name));
}

void loop(void)
{
        // 1 -> menu 2 -> up 3 -> down 4 -> exit
    char key = kpd.getKey();
    switch (key) {
    case '1':
        doEvent(menuKey, kpd.isPressed(key));
        //Serial.println((const __FlashStringHelper*)GET_NAME(getSelectedMenu()));
        break;
    case '2':
        doEvent(upKey, kpd.isPressed(key));
        break;
    case '3':
        doEvent(downKey, kpd.isPressed(key));
        break;
    case '4':
        doEvent(exitKey, kpd.isPressed(key));
        break;
    }
}

/**
 * Timer interrupt service routine, called with chosen period
 * @param timer - timer id
 */
void timer_handle_interrupts(int timer) 
{
    dispatchTask();
}
