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
 *  ======== sizingConfig ========
 *  This function takes size as input parameter. Size is a string and can be 
 *  either "BASIC" or "MINIMAL". Based on size this function will configure 
 *  xdc runtime. 
 *  "BASIC" will configure some xdc.runtime parameters which are not used by the *  examples.
 *  "MINIMAL" goes a step further and configures xdc runtime to minimize code 
 *  and data footprint. 
 */
 
function sizingConfig(size)
{
    /* xdc.runtime modules */
    var Defaults = xdc.useModule('xdc.runtime.Defaults');
    var Diags = xdc.useModule('xdc.runtime.Diags');
    var Log = xdc.useModule('xdc.runtime.Log');
    var LoggerBuf = xdc.useModule('xdc.runtime.LoggerBuf');
    var Main = xdc.useModule('xdc.runtime.Main');
    var SysMin = xdc.useModule('xdc.runtime.SysMin');
    var System = xdc.useModule('xdc.runtime.System');
    var Memory = xdc.useModule('xdc.runtime.Memory');

    /* set various Program parameters to some minimum values */

    /* 
     * Program.argSize sets size of .args section. 
     * Set to zero because main does not
     * take arguments in this example 
     */
    Program.argSize = 0x0;

    /* 
     * By default Memory module creates a default heap for the system. 
     * The following line sets the default heap size to a minimum. The 
     * application will create a default heap.
     */
    Memory.defaultHeapSize = 0x8;

    /* Turn off Asserts which are ON by default */
    Defaults.common$.diags_ASSERT = Diags.ALWAYS_OFF;

    /* Minimize exit handler array in System */
    System.maxAtexitHandlers = 0;       

    if (size == "MINIMAL") {
        /* 
         * All HeapStd functions brought in by Memory, but not used because 
         * the application uses HeapMem to create the default system heap. 
         * Setting fxntab to false removes these functions
         */
        var HeapStd = xdc.useModule('xdc.runtime.HeapStd');
        HeapStd.common$.fxntab = false;

        /* 
         * Remove Error print function. We lose error information when it occurs. 
         * Program will terminate without a message.
         */
        var Error = xdc.useModule('xdc.runtime.Error');
        Error.raiseHook = null;

        /* 
         * Module functions not accessed through instance handle. 
         * fxntab can be set to false for all modules 
         */
        var Defaults = xdc.useModule('xdc.runtime.Defaults');
        Defaults.common$.fxntab = false;    
    
        /* Modules names are not loaded on the target */
        Defaults.common$.namedModule = false;

        /* Error, Assert, Log  strings are not loaded on the target */
        var Text = xdc.useModule('xdc.runtime.Text');
        Text.isLoaded = false;
    }
}
/*
 *  @(#) ti.sysbios.examples; 2, 0, 0, 0,45; 8-9-2010 11:59:53; /db/vtree/library/trees/avala/avala-n44x/src/
 */

