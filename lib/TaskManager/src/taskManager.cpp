#include <Arduino.h>

#include "taskManager.h"


void deleteTask (void (*taskFunc)(void))
{
}

void addTask (void (*taskFunc)(void))
{
}

void dispatchTask()
{
   uint8_t i;
   void (*function) (void);
   
   for (i=0; i<arrayTail; i++) // проходим по списку задач
   {
      if (TaskArray[i].run == 1) // если флаг на выполнение взведен,
      { // запоминаем задачу, т.к. во
         function = TaskArray[i].pFunc; // время выполнения может 
         // измениться индекс
        if(TaskArray[i].period == 0) 
        { // если период равен 0
           deleteTask(TaskArray[i].pFunc); // удаляем задачу из списка,
        }
        else
        {
           TaskArray[i].run = 0; // иначе снимаем флаг запуска
            if(!TaskArray[i].delay) // если задача не изменила задержку
            { // задаем ее
               TaskArray[i].delay = TaskArray[i].period-1; 
           } // задача для себя может сделать паузу 
        }
        
        (*function)(); // выполняем задачу
   }
 }