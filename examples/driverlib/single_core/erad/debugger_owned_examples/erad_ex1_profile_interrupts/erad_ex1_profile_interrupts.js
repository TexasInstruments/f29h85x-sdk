//#############################################################################
//
// erad_ex1_profile_interrupts.js
//
// This JavaScript file is used to configure ERAD registers for use with the
// -CCS example "erad_ex1_profile_interrupts".
//
// To run the ERAD script, use the following command in the scripting console:
// - require("<proj_workspace_path>\\erad_ex1_profile_interrupts\\erad_ex1_profile_interrupts.js")
//
// Note that the script must be run after loading the .out on the C29x core. 
//
// This JavaScript file uses CCS Scripting features. For information, please visit:
// https://software-dl.ti.com/ccs/esd/documents/users_guide_ccs_20.0.0/index_debug-scripting.html
//
//#############################################################################

const ERAD = require("./erad.js");

let { ERAD_EBC_BASE, ERAD_SEC_BASE, ERAD_Ebc_Regs_Offset, ERAD_Sec_Regs_Offset, ERAD_Owner, ERAD_Buscomp_Bus_Select, ERAD_Counter_Input_Event, ERAD_Misc } = ERAD;
let { SEC_STATUS_M, EBC_BUS_SEL_M, SEC_INP_SEL_ENABLE, SEC_STARTSTOP, SEC_MODE_RISING_EDGE, ENABLE } = ERAD_Misc

//
// Launch a scripting session
//
const { initScripting } = require(require.resolve("scripting",  {paths: [process.cwd()] }));
const ds = initScripting();
const debugSession = ds.openSession("C29xx_CPU1");

//
// Variables for data read/write sizes
//
let DATA_SIZE_16 = 16;
let DATA_SIZE_32 = 32;

//*****************************************************************************
// Example: Profile Interrupts
//*****************************************************************************

function profile(i, addr1, addr2)
{
    let Ebc1 = ERAD_EBC_BASE[i*2]
    let Ebc2 = ERAD_EBC_BASE[i*2 + 1]
    let Sec  = ERAD_SEC_BASE[i]
    let inputSel = ((i*2 + 1) << 16) | (i*2)

    //
    // Set owner as debugger
    //
    debugSession.memory.write(Ebc1 + ERAD_Ebc_Regs_Offset.EBC_OWNER, ERAD_Owner.ERAD_OWNER_DEBUGGER, DATA_SIZE_32)
    debugSession.memory.write(Ebc2 + ERAD_Ebc_Regs_Offset.EBC_OWNER, ERAD_Owner.ERAD_OWNER_DEBUGGER, DATA_SIZE_32)
    debugSession.memory.write(Sec  + ERAD_Sec_Regs_Offset.SEC_OWNER, ERAD_Owner.ERAD_OWNER_DEBUGGER, DATA_SIZE_32)

    debugSession.memory.write(Ebc1 + ERAD_Ebc_Regs_Offset.EBC_REFL, addr1, DATA_SIZE_32)
    debugSession.memory.write(Ebc2 + ERAD_Ebc_Regs_Offset.EBC_REFL, addr2, DATA_SIZE_32)

    debugSession.memory.write(Ebc1 + ERAD_Ebc_Regs_Offset.EBC_CNTL, ENABLE | (ERAD_Buscomp_Bus_Select.ERAD_BUS_VPC_I_ALIGNED << EBC_BUS_SEL_M), DATA_SIZE_32)
    debugSession.memory.write(Ebc2 + ERAD_Ebc_Regs_Offset.EBC_CNTL, ENABLE | (ERAD_Buscomp_Bus_Select.ERAD_BUS_VPC_I_ALIGNED << EBC_BUS_SEL_M), DATA_SIZE_32)

    // Clear regs
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_CNTL,      0,          DATA_SIZE_32)
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_REF,       0xFFFFFFFF, DATA_SIZE_32)
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_COUNT,     0,          DATA_SIZE_32)
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_MAX_COUNT, 0,          DATA_SIZE_32)
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_MIN_COUNT, 0xFFFFFFFF, DATA_SIZE_32)

    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_INPUT_SEL2, inputSel,         DATA_SIZE_32)
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_CNTL, ENABLE | SEC_STARTSTOP, DATA_SIZE_32)
}

function configCounterInCountingMode(i, counter_input)
{
    let Sec  = ERAD_SEC_BASE[i]

    //
    // Set owner as debugger
    //
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_OWNER, ERAD_Owner.ERAD_OWNER_DEBUGGER, DATA_SIZE_32)
    
    //
    // Clear regs
    //
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_CNTL,      0,          DATA_SIZE_32)
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_REF,       0xFFFFFFFF, DATA_SIZE_32)
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_COUNT,     0,          DATA_SIZE_32)
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_MAX_COUNT, 0,          DATA_SIZE_32)
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_MIN_COUNT, 0xFFFFFFFF, DATA_SIZE_32)

    if(counter_input != ERAD_Counter_Input_Event.ERAD_EVENT_NO_EVENT)
    {
        debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_INPUT_SEL1, counter_input, DATA_SIZE_32)
        debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_CNTL, ENABLE | SEC_MODE_RISING_EDGE | SEC_INP_SEL_ENABLE, DATA_SIZE_32)
    }
    else
    {
        debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_CNTL, ENABLE | SEC_MODE_RISING_EDGE, DATA_SIZE_32)
    }
}

function configCounterInStartStopMode(i, counter_input, start_event, stop_event)
{
    let Sec  = ERAD_SEC_BASE[i]

    //
    // Set owner as debugger
    //
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_OWNER, ERAD_Owner.ERAD_OWNER_DEBUGGER, DATA_SIZE_32)

    //
    // Clear regs
    //
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_CNTL,      0,          DATA_SIZE_32)
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_REF,       0xFFFFFFFF, DATA_SIZE_32)
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_COUNT,     0,          DATA_SIZE_32)
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_MAX_COUNT, 0,          DATA_SIZE_32)
    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_MIN_COUNT, 0xFFFFFFFF, DATA_SIZE_32)

    debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_INPUT_SEL2, start_event | (stop_event << 16), DATA_SIZE_32)

    if(counter_input != ERAD_Counter_Input_Event.ERAD_EVENT_NO_EVENT)
    {
        debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_INPUT_SEL1, counter_input, DATA_SIZE_32)
        debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_CNTL, ENABLE | SEC_STARTSTOP | SEC_INP_SEL_ENABLE, DATA_SIZE_32)
    }
    else
    {
        debugSession.memory.write(Sec + ERAD_Sec_Regs_Offset.SEC_CNTL, ENABLE | SEC_STARTSTOP, DATA_SIZE_32)
    }
}


//
// Ensure that Counters 1-3 are in idle mode (bits 15:12 are set to 0)
//
let counter1Status = Number(debugSession.memory.readOne(ERAD_SEC_BASE[0] + ERAD_Sec_Regs_Offset.SEC_STATUS, DATA_SIZE_32));
let counter2Status = Number(debugSession.memory.readOne(ERAD_SEC_BASE[1] + ERAD_Sec_Regs_Offset.SEC_STATUS, DATA_SIZE_32));
let counter3Status = Number(debugSession.memory.readOne(ERAD_SEC_BASE[2] + ERAD_Sec_Regs_Offset.SEC_STATUS, DATA_SIZE_32));

if((0 == (counter1Status & SEC_STATUS_M)) &&
   (0 == (counter2Status & SEC_STATUS_M)) &&
   (0 == (counter3Status & SEC_STATUS_M)))
{
    let startTimer2ISR = Number(debugSession.expressions.evaluate("funcStart"));
    let endTimer2ISR   = Number(debugSession.expressions.evaluate("funcEnd")) - 2;
    profile(2, startTimer2ISR, endTimer2ISR)
    
    configCounterInCountingMode(0, ERAD_Counter_Input_Event.ERAD_EVENT_CPU1_TIMER2_INT)
    configCounterInStartStopMode(1, ERAD_Counter_Input_Event.ERAD_EVENT_NO_EVENT, ERAD_Counter_Input_Event.ERAD_EVENT_CPU1_TIMER2_INT, ERAD_Counter_Input_Event.ERAD_EVENT_EBC4)

    let coreRan = 0;

    while(1)
    {
        let cycleCount       = debugSession.memory.readOne(ERAD_SEC_BASE[2] + ERAD_Sec_Regs_Offset.SEC_COUNT,     DATA_SIZE_32);
        let cycleCountMax    = debugSession.memory.readOne(ERAD_SEC_BASE[2] + ERAD_Sec_Regs_Offset.SEC_MAX_COUNT, DATA_SIZE_32);
        let intEventCount    = debugSession.memory.readOne(ERAD_SEC_BASE[0] + ERAD_Sec_Regs_Offset.SEC_COUNT,     DATA_SIZE_32);
        let isrDelayCycleMax = debugSession.memory.readOne(ERAD_SEC_BASE[1] + ERAD_Sec_Regs_Offset.SEC_MAX_COUNT, DATA_SIZE_32);

        console.log("\n Current ISR Cycle Count   = " + cycleCount.toString() +
                    "\n Max ISR Cycle Count       = " + cycleCountMax.toString() +
                    "\n Interrupt Occurence Count = " + intEventCount.toString() +
                    "\n Max ISR Delay Cycle Count = " + isrDelayCycleMax.toString());

        //
        // Halt script if CPU is halted
        //
        let halted = debugSession.target.isHalted();

        if(!halted)
        {
            coreRan = 1;
        }

        if(coreRan && halted)
        {
            break;
        }
    }

    //
    // Disable  EBC_4-5 and SEC_1-3
    //
    let enabled;
    let enableBits = 1
    enabled = Number(debugSession.memory.readOne(ERAD_EBC_BASE[4] + ERAD_Ebc_Regs_Offset.EBC_CNTL, DATA_SIZE_32))
    enabled = enabled & (~enableBits);
    debugSession.memory.write(ERAD_EBC_BASE[4] + ERAD_Ebc_Regs_Offset.EBC_CNTL, enabled, DATA_SIZE_32)

    enabled = Number(debugSession.memory.readOne(ERAD_EBC_BASE[5] + ERAD_Ebc_Regs_Offset.EBC_CNTL, DATA_SIZE_32))
    enabled = enabled & (~enableBits);
    debugSession.memory.write(ERAD_EBC_BASE[5] + ERAD_Ebc_Regs_Offset.EBC_CNTL, enabled, DATA_SIZE_32)

    enabled = Number(debugSession.memory.readOne(ERAD_SEC_BASE[0] + ERAD_Sec_Regs_Offset.SEC_CNTL, DATA_SIZE_32))
    enabled = enabled & (~enableBits);
    debugSession.memory.write(ERAD_SEC_BASE[0] + ERAD_Sec_Regs_Offset.SEC_CNTL, enabled, DATA_SIZE_32)

    enabled = Number(debugSession.memory.readOne(ERAD_SEC_BASE[1] + ERAD_Sec_Regs_Offset.SEC_CNTL, DATA_SIZE_32))
    enabled = enabled & (~enableBits);
    debugSession.memory.write(ERAD_SEC_BASE[1] + ERAD_Sec_Regs_Offset.SEC_CNTL, enabled, DATA_SIZE_32)

    enabled = Number(debugSession.memory.readOne(ERAD_SEC_BASE[2] + ERAD_Sec_Regs_Offset.SEC_CNTL, DATA_SIZE_32))
    enabled = enabled & (~enableBits);
    debugSession.memory.write(ERAD_SEC_BASE[2] + ERAD_Sec_Regs_Offset.SEC_CNTL, enabled, DATA_SIZE_32)

    //
    // Reset SEC_1-3 values
    //
    debugSession.memory.write(ERAD_SEC_BASE[0] + ERAD_Sec_Regs_Offset.SEC_COUNT,       0x0,        DATA_SIZE_32)
    debugSession.memory.write(ERAD_SEC_BASE[0] + ERAD_Sec_Regs_Offset.SEC_MAX_COUNT,   0x0,        DATA_SIZE_32)
    debugSession.memory.write(ERAD_SEC_BASE[0] + ERAD_Sec_Regs_Offset.SEC_MIN_COUNT,   0xFFFFFFFF, DATA_SIZE_32)
    debugSession.memory.write(ERAD_SEC_BASE[0] + ERAD_Sec_Regs_Offset.SEC_STATUSCLEAR, 0x1,        DATA_SIZE_32)

    debugSession.memory.write(ERAD_SEC_BASE[1] + ERAD_Sec_Regs_Offset.SEC_COUNT,       0x0,        DATA_SIZE_32)
    debugSession.memory.write(ERAD_SEC_BASE[1] + ERAD_Sec_Regs_Offset.SEC_MAX_COUNT,   0x0,        DATA_SIZE_32)
    debugSession.memory.write(ERAD_SEC_BASE[1] + ERAD_Sec_Regs_Offset.SEC_MIN_COUNT,   0xFFFFFFFF, DATA_SIZE_32)
    debugSession.memory.write(ERAD_SEC_BASE[1] + ERAD_Sec_Regs_Offset.SEC_STATUSCLEAR, 0x1,        DATA_SIZE_32)

    debugSession.memory.write(ERAD_SEC_BASE[2] + ERAD_Sec_Regs_Offset.SEC_COUNT,       0x0,        DATA_SIZE_32)
    debugSession.memory.write(ERAD_SEC_BASE[2] + ERAD_Sec_Regs_Offset.SEC_MAX_COUNT,   0x0,        DATA_SIZE_32)
    debugSession.memory.write(ERAD_SEC_BASE[2] + ERAD_Sec_Regs_Offset.SEC_MIN_COUNT,   0xFFFFFFFF, DATA_SIZE_32)
    debugSession.memory.write(ERAD_SEC_BASE[2] + ERAD_Sec_Regs_Offset.SEC_STATUSCLEAR, 0x1,        DATA_SIZE_32)

    //
    // Reset EBC_4-5
    //
    debugSession.memory.write(ERAD_EBC_BASE[4] + ERAD_Ebc_Regs_Offset.EBC_STATUSCLEAR, 0x1, DATA_SIZE_16);
    debugSession.memory.write(ERAD_EBC_BASE[5] + ERAD_Ebc_Regs_Offset.EBC_STATUSCLEAR, 0x1, DATA_SIZE_16);

    console.log("\nCounter Stopped\n");
}
else
{
    console.log("Failed\n");
}

//
// End of File
//