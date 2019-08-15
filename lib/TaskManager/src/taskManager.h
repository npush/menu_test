#ifndef TaskManager_H
#define TaskManager_H

#include <Arduino.h>

typedef struct task
{ 
   void (*pTask)(void); // указатель на функцию
   uint8_t ready; // флаг готовности задачи к запуску
};

void deleteTask (void (*taskFunc)(void));
void addTask (void (*taskFunc)(void));
void dispatchTask();


#endif