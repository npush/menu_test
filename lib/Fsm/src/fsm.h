#ifndef Fsm_h
#define Fsm_h

enum states{
    initial,
    displayMenu,
    editParam,
    runFunction
};

enum events{
    menuKey,
    upKey,
    downKey,
    exitKey
};

void setState(states);
void doEvent(enum events);

void initialF(enum events, void (*f)());
void displayMenuF(enum events, void (*f)());
void editParamF(enum events, void (*f)());
void runFunctionF(enum events, void (*f)());

#endif // !Fsm_h