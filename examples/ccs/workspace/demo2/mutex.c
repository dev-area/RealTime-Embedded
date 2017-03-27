/* 
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */

/*
 *  ======== mutex.c ========
 *  This example shows the use of two tasks and one semaphore to perform
 *  mutual exclusive data access.
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>

#include <xdc/cfg/global.h>

Void task1(UArg arg0, UArg arg1);
Void task2(UArg arg0, UArg arg1);

Int resource = 0;
Semaphore_Handle sem;
Task_Handle tsk1;
Task_Handle tsk2;

Int finishCount = 0;

/*
 *  ======== main ========
 */
Void main()
{ 
    Task_Params taskParams;
        
    /* Create a Semaphore object to be use as a resource lock */
    sem = Semaphore_create(1, NULL, NULL);

    /* Create two tasks that share a resource*/
    Task_Params_init(&taskParams);
    taskParams.priority = 1;
    tsk1 = Task_create (task1, &taskParams, NULL);
    
    Task_Params_init(&taskParams);
    taskParams.priority = 2;
    tsk2 = Task_create (task2, &taskParams, NULL);

    BIOS_start();
}

/*
 *  ======== task1 ========
 */
Void task1(UArg arg0, UArg arg1)
{
    UInt32 time;

    for (;;) {
        System_printf("Running task1 function\n");

        if (Semaphore_getCount(sem) == 0) {
            System_printf("Sem blocked in task1\n");
        }

        /* Get access to resource */
        Semaphore_pend(sem, BIOS_WAIT_FOREVER); 

        /* do work by waiting for 2 system ticks to pass */
        time = Clock_getTicks();
        while (Clock_getTicks() <= (time + 1)) {
            ;
        }

        /* do work on locked resource */
        resource += 1;
        /* unlock resource */

        Semaphore_post(sem);

        Task_sleep(5);
    }
}

/*
 *  ======== task2 ========
 */
Void task2(UArg arg0, UArg arg1)
{
    for (;;) {
        System_printf("Running task2 function\n");

        if (Semaphore_getCount(sem) == 0) {
            System_printf("Sem blocked in task2\n");
        }

        /* Get access to resource */
        Semaphore_pend(sem, BIOS_WAIT_FOREVER);

        /* do work on locked resource */
        resource += 1;
        /* unlock resource */
        
        Semaphore_post(sem);
        
        Task_sleep(5);
        
        finishCount++;
        if (finishCount == 5) {
            System_printf("Calling System_exit from task2\n");
            System_exit(0);
        }
    }
}
/*
 *  @(#) ti.sysbios.examples; 2, 0, 0, 0,45; 8-9-2010 11:59:53; /db/vtree/library/trees/avala/avala-n44x/src/
 */

