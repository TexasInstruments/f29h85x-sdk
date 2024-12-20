let Common  = system.getScript("/driverlib/Common.js");
let Pinmux  = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_esm.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

/* Intro splash on GUI */
// longDescription += "*   [Device TRM](" + Common.getDeviceTRM() + ")";

function onChangeEnableHighPriorityWatchdog(inst,ui)
{
    if(inst.enableHighPriorityWatchdog)
    {
        ui.watchdogCounterValue.hidden = false
    }
    else
    {
        ui.watchdogCounterValue.hidden = true
    }
}

function onChangeRegisterNMI(inst,ui)
{
    if(inst.registerNMI)
    {
        ui.NMIHandler.hidden = false
    }
    else
    {
        ui.NMIHandler.hidden = true
    }
}

function onChangeTypeEventSource(inst, ui)
{
    if(inst.typeEventSource)
    {
        ui.eventSourceTyped.hidden = false
        ui.eventSource.hidden  = true
    }
    else
    {
        ui.eventSourceTyped.hidden = true
        ui.eventSource.hidden  = false
    }
}


let globalConfig = [
    {
        name        : "esmBase",
        displayName : "ESM Instance",
        description : 'Instance of the ESM used.',
        hidden      : false,
        default     : "ESM" + system.context,
        readOnly    : true,
    },
    {
        name        : "registerInterrupts",
        displayName : "Register Low Priority Interrupt Handler",
        description : 'Whether or not to register interrupt handlers in the interrupt module.',
        hidden      : false,
        default     : false,
    },
    {
        name        : "registerNMI",
        displayName : "Register High Priority NMI Handler",
        description : 'Whether or not to register NMI handler in the interrupt module.',
        hidden      : false,
        default     : false,
        onChange    : onChangeRegisterNMI,
    },
    {
        name        : "NMIHandler",
        displayName : "NMI Handler",
        description : 'The NMI handler function name.',
        hidden      : true,
        default     : 'myNMI_ISR',
    },
    {
        name        : "enableHighPriorityWatchdog",
        displayName : "Enable High Priority Watchdog",
        description : 'Enable the High Priority Watchdog',
        hidden      : false,
        default     : false, 
        onChange    : onChangeEnableHighPriorityWatchdog,
    },
    {
        name        : "watchdogCounterValue",
        displayName : "High Priority Watchdog Counter Pre-load Value",
        description : 'High priority Watchdog counter pre-load value',
        hidden      : true,
        displayFormat: "hex",
        default     : 0xFFFF,
    },
];


let config = [
    {
        name        : "eventSource",
        displayName : "Event Source",
        description : 'The error event source name in driverlib',
        hidden      : false,
        readOnly    : false,
        default     : device_driverlib_peripheral.ESM_EventMap[0].name,
        options     : device_driverlib_peripheral.ESM_EventMap
    },
    {
        name        : "typeEventSource",
        displayName : "Type the Event Source Name",
        description : "Enable to type the error event name or else drop down is provided.",
        hidden      : true,
        default     : false,
        onChange    : onChangeTypeEventSource,
    },
    {
        name        : "eventSourceTyped",
        displayName : "Event Source",
        description : 'The error event source name',
        hidden      : true,
        default     : '',
    },
    {
        name        : "enableInterrupt",
        displayName : "Enable Low Priority Interrupt",
        description : "Enable low priority interrupt for the error event",
        hidden      : false,
        default     : false,
    },
    {
        name        : "enableNMI",
        displayName : "Enable High Priority NMI",
        description : "Enable High Priority NMI for the error event",
        hidden      : false,
        default     : false,
    },
    {
        name        : "enableCriticalEvent",
        displayName : "Enable Critical Priority Event",
        description : "Enable the error event to cause a critical priority event. This can be configured to cause an XRSn in SYSCTL.",
        hidden      : false,
        default     : false,
    },
];

var sharedModuleInstances = undefined;

function onValidate(inst, validation) 
{
    var usedESMInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        if(instance_obj.typeEventSource == false)
        {
            usedESMInsts.push(instance_obj.eventSource);
        }
    }

    var duplicatesResult = Common.findDuplicates(usedESMInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ") 
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        if (duplicatesResult.duplicates.includes(inst.eventSource))
        {
            validation.logError(
                "Duplicates: " + allDuplicates, 
                inst, "eventSource");
        }
    }
    if(inst.enableInterrupt && inst.enableNMI)
    {
        validation.logError("Cannot enable both low priority interrupt and high priority NMI for an event.", inst, "enableInterrupt")
    }
    if(inst.enableInterrupt && !inst.$module.$static.registerInterrupts)
    {
        validation.logWarning("Low priority interrupt is enabled for one or more error events. Register the Interrupt handler in the Global parameters section.", inst, "enableInterrupt");
    }
    if(inst.enableNMI && !inst.$module.$static.registerNMI)
    {
        validation.logWarning("High priority NMI is enabled for one or more error events. Register the NMI handler in the Global parameters section.", inst, "enableNMI");
    }
}

function onValidateStatic(mod, validation){
    if ((mod.watchdogCounterValue > 0xFFFFFFFF) || (mod.watchdogCounterValue < 0) || !Number.isInteger(mod.watchdogCounterValue)) {
        validation.logError("Watchdog Counter Pre-load value must be an integer between 0 and 0xFFFFFFFF", mod, "watchdogCounterValue");
    }
}

var ESMCpuModule = {
    peripheralName: "ESMCPU",
    displayName: "ERROR SIGNALING CPU",
    defaultInstanceName: "myErrorSignaling",
    description: "Error Signaling module configuration",
    // longDescription : longDescription,
    config: config,
    sharedModuleInstances : sharedModuleInstances,
    templates: {
        boardc : "/driverlib/esm/esmcpu.board.c.xdt",
        boardh : "/driverlib/esm/esmcpu.board.h.xdt"
    },
    validate    : onValidate,
    moduleStatic : {
        name: "esmCpuGlobal",
        displayName: "Error Signaling Global",
        config: globalConfig,
        moduleInstances: (inst) => {
            var submodules = []
            if (inst.registerInterrupts)
            {
                var interruptName = "ESM_LOWPRI"
                submodules = submodules.concat([{
                    name: "esmInt",      
                    displayName: "ESM Low priority Interrupt",
                    moduleName: "/driverlib/interrupt.js",
                    collapsed: true,
                    args: {
                        $name : interruptName + "_INT",
                        typeInterruptName : true,
                        pinmuxPeripheralModule : "",
                        driverlibInt: "INT_" + interruptName,
                        interruptHandler : "INT_my" + interruptName+ "_ISR",
                    }
                }])
            }
            return submodules;
        },
        validate : onValidateStatic
    },
    uiAdd : "staticAndInstance"
    // uiAdd : "summary"
};


exports = ESMCpuModule;