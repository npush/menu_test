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

void initialF(enum events);
void displayMenuF(enum events);
void editParamF(enum events);
void runFunctionF(enum events);

#endif // !Fsm_h