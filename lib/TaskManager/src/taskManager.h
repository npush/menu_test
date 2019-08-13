#ifndef TaskManager_H
#define TaskManager_H

#include <Arduino.h>

typedef struct task
{ 
   void (*pFunc) (void); // указатель на функцию
   uint8_t run; // флаг готовности задачи к запуску
};

#endif