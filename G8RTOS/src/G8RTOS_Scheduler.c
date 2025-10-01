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
#include <driverlib/systick.h>
#include <driverlib/sysctl.h>
#include <driverlib/interrupt.h>

/************************************Includes***************************************/

/********************************Private Variables**********************************/

// Thread Control Blocks - array to hold information for each thread
// stuff goes here
static tcb_t threadControlBlocks[MAX_THREADS];

// Thread Stacks - array of arrays for individual stacks of each thread
// stuff goes here
static uint32_t threadStacks[MAX_THREADS][STACKSIZE];

// Current Number of Threads currently in the scheduler
// stuff goes here
static uint32_t currNumThreads;

/********************************Private Variables**********************************/

/*******************************Private Functions***********************************/

static void InitSysTick(void) {
    // hint: use SysCtlClockGet() to get the clock speed without having to hardcode it!
    // use timer interrupt to overflow every 1 ms (aka context switch ever 1 ms)
    SysTickPeriodSet(SysCtlClockGet() / 1000);
    SysTickIntRegister(SysTick_Handler);
    IntRegister(FAULT_PENDSV, PendSV_Handler);
    SysTickIntEnable();
    SysTickEnable();
}

/*******************************Private Functions***********************************/


/********************************Public Variables***********************************/

uint32_t SystemTime;

// reference currently running thread
tcb_t *CurrentlyRunningThread;
// stuff goes here

/********************************Public Variables***********************************/



/********************************Public Functions***********************************/



// G8RTOS_Init
// Initializes the RTOS by initializing system time.
// Return: void
void G8RTOS_Init() {
    // stuff goes here
    SystemTime = 0;
    currNumThreads = 0;

}

// G8RTOS_Launch
// Launches the RTOS.
// Return: error codes, 0 if none
uint8_t G8RTOS_Launch() {
    // stuff goes here
    InitSysTick();

    CurrentlyRunningThread = &threadControlBlocks[0];

    IntPrioritySet(FAULT_PENDSV, 0xFF);
    IntPrioritySet(FAULT_SYSTICK, 0xFF);

    // Call G8RTOS_Start()
    G8RTOS_Start();
    return 0;
}

// G8RTOS_Scheduler
// Chooses next thread in the TCB. Round-robin scheduling.
// Return: void
void G8RTOS_Scheduler() {
    CurrentlyRunningThread = CurrentlyRunningThread->next;
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

    uint32_t status = StartCriticalSection();

    if (currNumThreads >= MAX_THREADS)
        return 1;


    tcb_t *newTCB = &threadControlBlocks[currNumThreads];

    newTCB->sp = &threadStacks[currNumThreads][STACKSIZE - 16];

    newTCB->sp[15] = THUMBBIT;
    newTCB->sp[14] = (uint32_t)threadToAdd;
    newTCB->sp[13] = 0x00000000; // LR
    newTCB->sp[12] = 0x12121212; // R12
    newTCB->sp[11] = 0x03030303; // R3
    newTCB->sp[10] = 0x02020202; // R2
    newTCB->sp[9]  = 0x01010101; // R1
    newTCB->sp[8]  = 0x00000000; // R0
    newTCB->sp[7]  = 0x11111111; // R11
    newTCB->sp[6]  = 0x10101010; // R10
    newTCB->sp[5]  = 0x09090909; // R9
    newTCB->sp[4]  = 0x08080808; // R8
    newTCB->sp[3]  = 0x07070707; // R7
    newTCB->sp[2]  = 0x06060606; // R6
    newTCB->sp[1]  = 0x05050505; // R5
    newTCB->sp[0]  = 0x04040404; // R4

    if (currNumThreads == 0) {
        newTCB->next = newTCB;
        newTCB->prev = newTCB;
    } else {
        tcb_t *firstTCB = &threadControlBlocks[0];
        tcb_t *lastTCB = &threadControlBlocks[currNumThreads - 1];

        firstTCB->prev = newTCB;
        newTCB->next = firstTCB;
        lastTCB->next = newTCB;
        newTCB->prev = lastTCB;
    }

    currNumThreads++;

    EndCriticalSection(status);

    return 0;
}

// SysTick_Handler
// Increments system time, sets PendSV flag to start scheduler.
// Return: void
void SysTick_Handler() {
    SystemTime++;
    HWREG(NVIC_INT_CTRL) |= NVIC_INT_CTRL_PEND_SV;
}

