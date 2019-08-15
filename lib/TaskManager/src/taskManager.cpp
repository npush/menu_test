// http://robocraft.ru/blog/3636.html
#include <Arduino.h>

#include "taskManager.h"

#define MAX_TASKS 8
volatile static task TaskQueue[MAX_TASKS];

volatile static byte queueTail;

volatile static uint8_t itemsInBuffer[MAX_TASKS];
volatile static uint8_t head;
volatile static uint8_t tail;

void _addTask(void (*taskFunc)(void))
{

}


void deleteTask (void (*taskFunc)(void))
{
    for (byte i=0; i < queueTail; i++) {
        if(TaskQueue[i].pTask == taskFunc) {
            if(i != (queueTail - 1)) {
                TaskQueue[i].pTask = TaskQueue[queueTail - 1].pTask;
                TaskQueue[i].ready = TaskQueue[queueTail - 1].ready;
         }
         queueTail--;
         return;
      }
   }
}

void addTask (void (*taskFunc)(void))
{
    // for(byte i = 0; i < queueTail; i++) {
    //     // update task
    //     if(TaskQueue[i].pTask == taskFunc) {
    //         TaskQueue[i].ready = 0;
    //         return;
    //     }
    // }
   if (queueTail < MAX_TASKS) {
      TaskQueue[queueTail].pTask = taskFunc;
      TaskQueue[queueTail].ready = 1;   
      queueTail++;
    }
}

void dispatchTask()
{
   void (*function) (void);
   for (byte i=0; i < queueTail;) {
        if (TaskQueue[i].ready == 1) {
            function = TaskQueue[i].pTask;
        (*function)();
        deleteTask(TaskQueue[i].pTask);
        } else {
           // флаг запуска не взведен
            i++;    // переходим к следующей задаче в списке
        }
   }
 }
 // @todo
 //https://kaimi.io/2017/09/atmos-atmel-avr-operational-system-timers/

 #ifdef __cplusplus
extern "C" {
#endif

// all of your legacy C code here

#ifdef __cplusplus
}
#endif