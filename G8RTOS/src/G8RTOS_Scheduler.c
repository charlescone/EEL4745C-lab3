// G8RTOS_Scheduler.c
// Date Created: 2023-07-25
// Date Updated: 2023-07-27
// Defines for scheduler functions

#include "../G8RTOS_Scheduler.h"

/************************************Includes***************************************/

#include <stdint.h>

#include "../G8RTOS_CriticalSection.h"

#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "inc/hw_nvic.h"
#include "driverlib/systick.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"

/************************************Includes***************************************/

/********************************Private Variables**********************************/

// Thread Control Blocks - array to hold information for each thread
// stuff goes here

// Thread Stacks - array of arrays for individual stacks of each thread
// stuff goes here

// Current Number of Threads currently in the scheduler
// stuff goes here

/********************************Private Variables**********************************/

/*******************************Private Functions***********************************/

static void InitSysTick(void) {
    // hint: use SysCtlClockGet() to get the clock speed without having to hardcode it!

    // use timer interrupt to overflow every 1 ms (aka context switch ever 1 ms)
}

/*******************************Private Functions***********************************/


/********************************Public Variables***********************************/

uint32_t SystemTime;

// reference currently running thread
// stuff goes here

/********************************Public Variables***********************************/



/********************************Public Functions***********************************/



// G8RTOS_Init
// Initializes the RTOS by initializing system time.
// Return: void
void G8RTOS_Init() {
    // stuff goes here
}

// G8RTOS_Launch
// Launches the RTOS.
// Return: error codes, 0 if none
uint8_t G8RTOS_Launch() {
    // stuff goes here

    // Call G8RTOS_Start()
    return 0;
}

// G8RTOS_Scheduler
// Chooses next thread in the TCB. Round-robin scheduling.
// Return: void
void G8RTOS_Scheduler() {
    // stuff goes here (alot of stuff)
}

// G8RTOS_AddThread
// - Adds threads to G8RTOS Scheduler
// - Checks if there are still available threads to insert to scheduler
// - Initializes the thread control block for the provided thread
// - Initializes the stack for the provided thread to hold a "fake context"
// - Sets stack thread control block stack pointer to top of thread stack
// - Sets up the next and previous thread control block pointers in a round robin fashion
// Param void* "threadToAdd": pointer to thread function address
// Return: scheduler error code
uint8_t G8RTOS_AddThread(void (*threadToAdd)(void)) {
    // stuff goes here
    return 0;
}

// SysTick_Handler
// Increments system time, sets PendSV flag to start scheduler.
// Return: void
void SysTick_Handler() {
// stuff goes here
}

