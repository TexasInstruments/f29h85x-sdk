//#############################################################################
//
// erad_ex2_stack_overflow.js
//
// This JavaScript file is used to configure ERAD registers for use with the
// CCS example "erad_ex2_stack_overflow".
//
// Run this ERAD script in the scripting console using the following command
//
// - require("<proj_workspace_path>\\erad_ex2_stack_overflow\\erad_ex2_stack_overflow.js")
//
// This JavaScript file uses CCS Scripting features. For information, please visit:
// https://software-dl.ti.com/ccs/esd/documents/users_guide_ccs_20.0.0/index_debug-scripting.html
//
//#############################################################################

const ERAD = require("./erad.js");

let { ERAD_EBC_BASE, ERAD_Ebc_Regs_Offset, ERAD_Owner, ERAD_Misc } = ERAD;
let { ENABLE } = ERAD_Misc

//
// Launch a scripting session
//
const { initScripting } = require(require.resolve("scripting", { paths: [process.cwd()] }));
const ds = initScripting();
const debugSession = ds.openSession("C29xx_CPU1");

//
// Variables for data read/write sizes
//
var DATA_SIZE_16 = 16;
var DATA_SIZE_32 = 32;

//*****************************************************************************
// Example: Stack Overflow
//*****************************************************************************

var Ebc = ERAD_EBC_BASE[6]

//
// Set owner as debugger
//
debugSession.memory.write(Ebc + ERAD_Ebc_Regs_Offset.EBC_OWNER, ERAD_Owner.ERAD_OWNER_DEBUGGER, DATA_SIZE_32)

//
// Ensure that EBC is in idle mode
//
var ebcStatus = Number(debugSession.memory.readOne(Ebc + ERAD_Ebc_Regs_Offset.EBC_STATUS, DATA_SIZE_32))

if(0 == (ebcStatus &  0x300))
{
    console.log("\nProfile Setup\n");

    //
    // Reset EBC
    //
    debugSession.memory.write(Ebc + ERAD_Ebc_Regs_Offset.EBC_STATUSCLEAR, 0x1, DATA_SIZE_32);
    debugSession.memory.write(Ebc + ERAD_Ebc_Regs_Offset.EBC_CNTL, 0x0, DATA_SIZE_32);
    debugSession.memory.write(Ebc + ERAD_Ebc_Regs_Offset.EBC_REFL, 0x0, DATA_SIZE_32);
    debugSession.memory.write(Ebc + ERAD_Ebc_Regs_Offset.EBC_REFH, 0x0, DATA_SIZE_32);

    //
    // Grab maximum value for stack
    //
  	var stackEnd = Number(debugSession.expressions.evaluate("__TI_STACK_END"))
    console.log("\nSP END: " + stackEnd.toString(16) + "\n");

    //
    // Set EBC_REF to be stackEnd - threshold (0x10) for EBC
    //
    debugSession.memory.write(Ebc + ERAD_Ebc_Regs_Offset.EBC_REFL, stackEnd - 0x10, DATA_SIZE_32);

    //
    // Clear mask value
    //
    debugSession.memory.write(Ebc + ERAD_Ebc_Regs_Offset.EBC_MASKL, 0x0, DATA_SIZE_32);
    debugSession.memory.write(Ebc + ERAD_Ebc_Regs_Offset.EBC_MASKH, 0x0, DATA_SIZE_32);

    //
    // Set CPU to halt when write to address greater than value in EBC_REF
    // occurs
    // ENABLE         = (1  <<  0) | -> Enable the EBC instance
    // BUS_SEL        = (1  <<  1) | -> DWAB for write data accesses
    // HALT           = (1  <<  6) | -> Halt CPU on match
    // INTERRUPT      = (0  <<  7) | -> Do not generate interrupt
    // NMI_EN         = (0  <<  8) | -> Do not generate NMI
    // COMP_MODE      = (0  <<  9) | -> Generate match when address matches EBC_REF
    // STACK_QUAL     = (1  << 12) | -> Enable Stack access qualifier
    // SPSEL_MATCH_EN = (0  << 13) | -> SPSEL match disabled
    // SPSEL          = (0  << 14)
    // EBC_CNTL = 0x1043
    //
    debugSession.memory.write(Ebc + ERAD_Ebc_Regs_Offset.EBC_CNTL, 0x1043, DATA_SIZE_32);

    //
    // Loop until Stack Overflow occurs
    //
    console.log("\nProfile Started. CPU will halt on stack overflow.\n");

    var coreRan = 0;

    while(1)
    {
        //
        // Read status and check for event fired bit to be set active. This
        // signals that a "match" has occured, as defined by the values set in
        // EBC_CNTL and EBC_REF for EBC. In this case, the event fired bit
        // represents whether or not a write has occurred to the address in
        // EBC_REF, which is set to just before __TI_STACK_END value
        //
        var bp_status = Number(debugSession.memory.readOne(Ebc + ERAD_Ebc_Regs_Offset.EBC_STATUS, DATA_SIZE_32))

        if(bp_status & 0x1 == 1)
        {
            console.log("\nSTACK OVERFLOW detected. Halting CPU.\n");
            break;
        }

        //
        // Halt script if CPU is halted
        //
        var halted = debugSession.target.isHalted();

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
    // Disable EBC
    //
    EBC_CNTL_RD = Number(debugSession.memory.readOne((Ebc + ERAD_Ebc_Regs_Offset.EBC_CNTL) & ENABLE, DATA_SIZE_32))
    disableEBC = EBC_CNTL_RD & (~ENABLE);
    debugSession.memory.write(Ebc + ERAD_Ebc_Regs_Offset.EBC_CNTL, disableEBC, DATA_SIZE_32);

    console.log("\nProfile stopped\n");
}
else
{
    console.log("\nFAILED. EBC is not in idle state\n");
}

//
// End of File
//