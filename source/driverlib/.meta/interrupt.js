let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_interrupt.js");

var interruptOptions = device_driverlib_peripheral.interrupts.map(element => {
    return { name: element.int_define_name}
});

/* Intro splash on GUI */
let longDescription = "";

function onChangeIntList(inst, ui)
{
    inst["interruptHandler"] = inst["driverlibIntList"] + "_ISR"
}

function onChangeTypeInterruptName(inst, ui)
{
    if(inst.typeInterruptName)
    {
        ui.driverlibIntList.hidden = true
    }
    else
    {
        ui.driverlibIntList.hidden = false
    }
}

/* Array of configurables that are common across device families */
let config = [
    {
        name        : "pinmuxPeripheralModule",
        displayName : "PinMux Peripheral Module",
        description : 'The pinmux peripheral module name',
        hidden      : true,
        readOnly    : false,
        default     : ''
    },
    {
        name        : "typeInterruptName",
        displayName : "Type Interrupt Name",
        hidden      : true,
        readOnly    : false,
        default     : false,
        onChange    : onChangeTypeInterruptName,
    },
    {
        name        : "driverlibInt",
        displayName : "Driverlib Int",
        description : 'The interrupt name in driverlibs inc/hw_ints',
        hidden      : true,
        readOnly    : false,
        default     : ''
    },
    {
        name        : "driverlibIntList",
        displayName : "Interrupt Source",
        description : 'List of Interrupt sources',
        hidden      : false,
        default     : interruptOptions[0].name,
        options     : interruptOptions,
        onChange    : onChangeIntList
    },
    {
        name        : "interruptHandler",
        displayName : "Interrupt Handler",
        description : 'The interrupt handler function name',
        hidden      : false,
        readOnly    : false,
        default     : interruptOptions[0].name + "_ISR"
    },
    {
        name        : "enableInterrupt",
        displayName : "Enable Interrupt in PIPE",
        description : 'Enable the interrupt in the interrupt module',
        hidden      : false,
        readOnly    : false,
        default     : true
    },
    {
        name        : "interruptPriority",
        displayName : "Interrupt Priority",
        description : 'The interrupt priority (0-255). Lower the number, higher the priority',
        hidden      : false,
        readOnly    : false,
        default     : 255
    },
    {
        name        : "contextID",
        displayName : "Interrupt Context ID",
        description : 'The interrupt priority (0-255). Lower the number, higher the priority',
        hidden      : false,
        readOnly    : false,
        default     : "INTERRUPT_CONTEXTID_0",
        options     : [
            {name: "INTERRUPT_CONTEXTID_0",      displayName : " Context-ID 0"},
            {name: "INTERRUPT_CONTEXTID_1",      displayName : " Context-ID 1"},
            {name: "INTERRUPT_CONTEXTID_2",      displayName : " Context-ID 2"},
            {name: "INTERRUPT_CONTEXT_AGNOSTIC", displayName : " Context-ID Agnostic"},
        ]
    },
];

let globalConfig = [
    {
        name        : "RTINT_Threshold",
        displayName : "RTINT Threshold",
        default     : 0
    },
    {
        name        : "groupMask",
        displayName : "Interrupt Nesting groups",
        default     : '0xFF',
        options     : [
            {name:'0xFF', displayName:"All interrupts can nest in one another"},
            {name:'0xFE', displayName:"128 priority groups with 2 interrupt levels each"},
            {name:'0xFC', displayName:"64 priority groups with 4 interrupt levels each"},
            {name:'0xF8', displayName:"32 priority groups with 8 interrupt levels each"},
            {name:'0xF0', displayName:"16 priority groups with 16 interrupt levels each"},
            {name:'0xE0', displayName:"8 priority groups with 32 interrupt levels each"},
            {name:'0xC0', displayName:"4 priority groups with 64 interrupt levels each"},
            {name:'0x80', displayName:"2 priority groups with 128 interrupt levels each"},
            {name:'0x00', displayName:"No interrupts can nest in one another"},
        ]
    },
    {
        name            : "WARNRTISP",
        displayName     : "RTINT Stack Pointer Warning Level",
        longDescription : "When RTINT stack pointer crosses this level, only interrupts above the a certain priority (configured below) will be serviced.",
        default         : 15,
        options         : [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15].map(x=> { return {name:x}})
    },
    {
        name            : "WARNRTISP_PRIO_LEVEL",
        displayName     : "RTINT Stack Pointer Warning Priority level",
        longDescription : "When stack pointer crosses the warning level, only interrupts with priority than this level will be serviced.",
        default         : 0
    },
    {
        name            : "SUP_IGN_INTE_EN",
        displayName     : "Enable Supervisor ignore INTE",
        longDescription : "Supervisor interrupt is the interrupt configured with priority = RTINT Threshold level. This field enables supervisor interrupt to be used without regard to INTE enable within CPU",
        default         : false
    },
];

function onValidate(inst, validation) {
    var usedInterruptInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        if(instance_obj.typeInterruptName == true)
        {
            if(instance_obj.pinmuxPeripheralModule == "")
            {
                usedInterruptInsts.push(instance_obj.driverlibInt);
            }
        }
        else
        {
            usedInterruptInsts.push(instance_obj.driverlibIntList);
        }
    }

    var duplicatesResult = Common.findDuplicates(usedInterruptInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ") 
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        if (duplicatesResult.duplicates.includes(inst.driverlibInt))
        {
            validation.logError(
                "Duplicates: " + allDuplicates, 
                inst, "driverlibInt");
        }
        if (duplicatesResult.duplicates.includes(inst.driverlibIntList))
        {
            validation.logError(
                "Duplicates: " + allDuplicates, 
                inst, "driverlibIntList");
        }

    }

    if(inst.interruptPriority < 0 || inst.interruptPriority > 255)
    {
        validation.logError(
            "Interrupt priority must be in 0-255 range", 
            inst, "interruptPriority");
    }

    // Block INT_SW1 if FreeRTOS is used
    if(inst.driverlibIntList == 'INT_SW1'){
        let freertosModule = system.modules["/kernel/freertos_tool/FREERTOS"]
        if(freertosModule)
            validation.logError(
                "FreeRTOS uses this software interrupt as part of the device port",
                inst, "driverlibIntList"
            )
    }
}

function onValidateStatic(mod, validation){
    if((mod.RTINT_Threshold > 255) || (mod.RTINT_Threshold < 0)) {
        validation.logError("Invalid priority level", mod, "RTINT_Threshold")
    }

    if((mod.WARNRTISP_PRIO_LEVEL > 255) || (mod.WARNRTISP_PRIO_LEVEL < 0)) {
        validation.logError("Invalid priority level", mod, "WARNRTISP_PRIO_LEVEL")
    }

    if((mod.RTINT_Threshold & Number(mod.groupMask)) != mod.RTINT_Threshold) {
        validation.logError("Threshold value should be aligned with group mask", mod, "RTINT_Threshold")
    }
}

var intModule = {
    peripheralName: "INTERRUPT",
    displayName: "INTERRUPT",
    defaultInstanceName: "myInterrupt",
    description: "",
    config: config,
    templates: {
        boardc : "/driverlib/interrupt/interrupt.board.c.xdt",
        boardh : "/driverlib/interrupt/interrupt.board.h.xdt"
    },
    validate    : onValidate,
    moduleStatic : {
        name: "intGlobal",
        displayName: "Interrupt Global",
        config: globalConfig,
        validate : onValidateStatic
    },
    uiAdd : "staticAndInstance"
};

exports = intModule;