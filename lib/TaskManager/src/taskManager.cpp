// http://robocraft.ru/blog/3636.html
#include <Arduino.h>

#include "taskManager.h"

#define MAX_TASKS 16
volatile static task TaskQueue[MAX_TASKS];

volatile static byte queueTail;

void deleteTask (void (*taskFunc)(void))
{
      for (byte i=0; i<queueTail; i++)           // проходим по списку задач
   {
      if(TaskQueue[i].pTask == taskFunc)   // если задача в списке найдена
      {
       if(i != (queueTail - 1))                     //  и она не последняя, то переносим последнюю задачу
         {                                                   // на место удаляемой
          TaskQueue[i].pTask = TaskQueue[queueTail - 1].pTask;
          TaskQueue[i].start_delay =TaskQueue[queueTail - 1].start_delay;
          TaskQueue[i].period = TaskQueue[queueTail - 1].period;
          TaskQueue[i].ready_run = TaskQueue[queueTail - 1].ready_run;
         }
         queueTail--;                                 // уменьшаем указатель "хвоста"
         return;
      }
   }

}

void addTask (void (*taskFunc)(void))
{
      for(byte i = 0; i < queueTail; i++)             // поиск задачи в текущем списке
   {
      if(TaskQueue[i].pTask == taskFunc)        // если нашли, то обновляем переменные
      {
         TaskQueue[i].start_delay = taskDelay;
         TaskQueue[i].period = taskPeriod;
         TaskQueue[i].ready_run = 0;   
         return;                                      // обновив, выходим
      }
   }
   if (queueTail < MAX_TASKS)          // если такой задачи в списке нет 
   {                                                  // и есть место,то добавляем
      TaskQueue[queueTail].pTask = taskFunc;
      TaskQueue[queueTail].start_delay = taskDelay;
      TaskQueue[queueTail].period = taskPeriod;
      TaskQueue[queueTail].ready_run = 0;   
      queueTail++;                                    // увеличиваем "хвост"
    }

}

void dispatchTask()
{
   void (*function) (void);                 // указатель на функцию, которую если-что, нужно запускать
   for (byte i=0; i<queueTail;)              // сканируем список задач
   {
      if (TaskQueue[i].ready_run == 1)                // если флаг на выполнение взведен,
      {                                                
         function = TaskQueue[i].pTask;               // запоминаем задачу
                                                      
         if(TaskQueue[i].period == 0)                 
           {                                       // если у задачи период равен 0
              DeleteTask(TaskQueue[i].pTask);      // удаляем задачу из списка
           } //end if (TaskQueue[i].period == 0)
         else
         {
            TaskQueue[i].start_delay = TaskQueue[i].period; // и копируем значение периодичности в задержку
            TaskQueue[i].ready_run = 0;                     // иначе снимаем флаг запуска
            i++;   // переходим к следующей задаче
         } //end else
         (*function)();                               // выполняем задачу
      } // end if (TaskQueue[i].ready_run == 1)
      else   // флаг запуска не взведен
         i++;    // переходим к следующей задаче в списке
   }// end for.
 }
 // @todo
 //https://kaimi.io/2017/09/atmos-atmel-avr-operational-system-timers/