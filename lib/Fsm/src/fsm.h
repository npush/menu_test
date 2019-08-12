#ifndef Fsm_h
#define Fsm_h

enum states{
    initial,
    idle,
    displayMenu,
    editParam,
    runFunction,
    resolveMenuItem
};

enum events{
    menuKey,
    upKey,
    downKey,
    exitKey
};

void setState(states);
void doEvent(enum events, bool keyState);

void initialF(enum events, bool keyState);
void idleF(enum events, bool keyState);
void showMenuF(enum events, bool keyState);
void editParamF(enum events, bool keyState);
void runFunctionF(enum events, bool keyState);

#endif // !Fsm_h