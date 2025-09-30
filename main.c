// Lab 3, uP2 Fall 2025
// Created: 2023-07-31
// Updated: 2025-07-09
// Lab 3 is intended to introduce you to RTOS concepts. In this, you will
// - configure the systick function
// - write asm functions for context switching
// - write semaphore functions
// - write scheduler functions to add threads / run scheduling algorithms
// - write critical section assembly functions

/************************************Includes***************************************/

#include "G8RTOS/G8RTOS.h"
#include "./MultimodDrivers/multimod.h"

#include "./threads.h"

/************************************Includes***************************************/

/*************************************Defines***************************************/
/*************************************Defines***************************************/

/********************************Public Variables***********************************/
//extern uint32_t SystemTime;

uint32_t task0Count = 0;
uint32_t task1Count = 0;
uint32_t task2Count = 0;

/********************************Public Variables***********************************/

/********************************Public Functions***********************************/


// Complete the functions below as test threads.
void task0(void) {

}

void task1(void) {

}

void task2(void) {

}

/********************************Public Functions***********************************/

/************************************MAIN*******************************************/

// Be sure to add in your source files from previous labs into "MultimodDrivers/src/"!
// If you made any modifications to the corresponding header files, be sure to update
// those, too.
int main(void) {

    // sysclock
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    // Initializes the necessary peripherals.
    Multimod_Init();

    // Add threads, initialize semaphores here!
        // your code here

    // launch your RTOS!
        // your code here

    // spin - the RTOS will take over now
    while (1);
}

/************************************MAIN*******************************************/
