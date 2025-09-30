// G8RTOS_Scheduler.h
// Date Created: 2023-07-26
// Date Updated: 2023-07-26
// Scheduler / initialization code for G8RTOS

#ifndef G8RTOS_SCHEDULER_H_
#define G8RTOS_SCHEDULER_H_

/************************************Includes***************************************/

#include <stdint.h>

#include "G8RTOS_Structures.h"
#include "../MultimodDrivers/multimod.h"

/************************************Includes***************************************/

/*************************************Defines***************************************/

/* Status Register with the Thumb-bit Set */
#define THUMBBIT            0x01000000

#define MAX_THREADS         6
#define STACKSIZE           1024
#define OSINT_PRIORITY      7

/*************************************Defines***************************************/

/******************************Data Type Definitions********************************/

// Scheduler error typedef
// stuff goes here (if you want)



/******************************Data Type Definitions********************************/

/****************************Data Structure Definitions*****************************/
/****************************Data Structure Definitions*****************************/

/********************************Public Variables***********************************/

// stuff goes here (if you want)

/********************************Public Variables***********************************/

/********************************Public Functions***********************************/

extern void G8RTOS_Start();
extern void PendSV_Handler();

void G8RTOS_Init();
int32_t G8RTOS_Launch();
void G8RTOS_Scheduler();
sched_ErrCode_t G8RTOS_AddThread(void (*threadToAdd)(void));
void SysTick_Handler();

/********************************Public Functions***********************************/


#endif /* G8RTOS_SCHEDULER_H_ */

