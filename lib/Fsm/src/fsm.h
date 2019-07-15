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

void doEvent(enum events e);

void initialF(enum events e);
void displayMenuF(enum events e);
void editParamF(enum events e);
void runFunctionF(enum events e);

#endif // !Fsm_h