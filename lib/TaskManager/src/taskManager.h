#ifndef TaskManager_H
#define TaskManager_H

#include <Arduino.h>

#include "fsm.h"

typedef struct task { 
   void (*pTask)(enum event);
   uint8_t ready;
   uint8_t inProgress;
};

void deleteTask (void (*taskFunction)(enum event));
void addTask (void (*taskFunction)(enum event));
void dispatchTask();

#endif