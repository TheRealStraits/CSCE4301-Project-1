# CSCE4301 Project 1

This project is that of a task scheduler that operates as an RTOS on the STM32. The aim of the project is to be able to queue and dispatch tasks using the implemented Task Scheduler. The designed scheduler uses a combination of struct datatypes and C functions in order to accomplish its objective of queuing different tasks that perform different functionalities on the STM32 Microcontroller. 

## Task Scheduler

### How does it work?

The different tasks are initialsed at the beginning of the project with all the necessary implementations. The user can then use then start queuing the different tasks and include their priority along with them using the ***QueTask()*** function. Once the tasks have been queued accordingly. The ***Dispatch()*** function can be run in order to start popping tasks from the queue and start the program. There are other functions that can be used in the API such as the ReRunMe() & Init() functions which you can see the description for in the functions section. 

### Functions

#### Init()

#### QueTask(taskPointer, taskPriority)

#### ReRunMe(tickDelay)

#### Dispatch()



## Scheduler Implementations

### Temprature Sensor

### Parking Sensor
