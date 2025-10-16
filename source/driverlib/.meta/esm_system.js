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

function onChangeOutputPinMode(inst, ui) {
    if(inst.outputPinMode == "ESM_OUTPUT_LEVEL_MODE")
    {
        ui.levelModePolarity.hidden = false
        ui.pwmHighCounterValue.hidden = true
        ui.pwmLowCounterValue.hidden = true
    }
    else if (inst.outputPinMode == "ESM_OUTPUT_PWM_MODE")
    {
        ui.levelModePolarity.hidden = true
        ui.pwmHighCounterValue.hidden = false
        ui.pwmLowCounterValue.hidden = false
    }
}

function onChangeUseErrorPin(inst, ui) {
    if(inst.useErrorPin)
    {
        ui.errorPinCounterValue.hidden = false
        ui.outputPinMode.hidden = false
        ui.levelModePolarity.hidden = false
        ui.errorPinMonitoring.hidden = false
    }
    else
    {
        ui.errorPinCounterValue.hidden = true
        ui.outputPinMode.hidden = true
        ui.levelModePolarity.hidden = true
        ui.errorPinMonitoring.hidden = true
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
        readOnly    : true,
        default     : "ESMSYSTEM",
        shouldBeAllocatedAsResource: true
    }
]

if (Common.isContextCPU1() || (system.resourceAllocation.mode != "OFF"))
{
    globalConfig = globalConfig.concat([
        {
            name        : "useErrorPin",
            displayName : "Use Error Pin",
            description : 'Select to configure Error pin for use.',
            default     : true,
            onChange    : onChangeUseErrorPin,
            shouldBeAllocatedAsResource: true
        },
        {
            name        : "errorPinCounterValue",
            displayName : "Error Pin Counter Pre-load Value",
            description : 'Error Pin counter Pre-load value',
            hidden      : false,
            displayFormat: "hex",
            default     : 0xFFFFFF,
            shouldBeAllocatedAsResource: true
        },
        {
            name        : "outputPinMode",
            displayName : "Output Pin Mode",
            description : "Configure the mode of the ESM Error output pin",
            hidden      : false,
            default     : device_driverlib_peripheral.ESM_OutputPinMode[0].name,
            options     : device_driverlib_peripheral.ESM_OutputPinMode,
            onChange    : onChangeOutputPinMode,
            shouldBeAllocatedAsResource: true
        },
        {
            name        : "levelModePolarity",
            displayName : "Error pin Polarity in Level mode",
            description : 'Set the polarity of the Error pin in Level mode.',
            hidden      : false,
            default     : device_driverlib_peripheral.ESM_LevelModePolarity[0].name,
            options     : device_driverlib_peripheral.ESM_LevelModePolarity,
            shouldBeAllocatedAsResource: true
        },
        {
            name        : "pwmHighCounterValue",
            displayName : "PWM High Counter Pre-load Value",
            description : 'PWM mode High Counter Pre-load value',
            hidden      : true,
            displayFormat: "hex",
            default     : 0xFFFFFF,
            shouldBeAllocatedAsResource: true
        },
        {
            name        : "pwmLowCounterValue",
            displayName : "PWM Low Counter Pre-load Value",
            description : 'PWM mode Low Counter Pre-load value',
            hidden      : true,
            displayFormat: "hex",
            default     : 0xFFFFFF,
            shouldBeAllocatedAsResource: true
        },
        {
            name        : "errorPinMonitoring",
            displayName : "Error Pin Monitoring",
            description : 'Enable Error pin monitoring',
            default     : false,
            shouldBeAllocatedAsResource: true
        },
    ])
}


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
        name        : "enableGenEvent",
        displayName : "Enable Event to XBAR",
        description : "Enable the error event to influence the ESM_GEN_EVENT to XBAR.",
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
    {
        name        : "enableInfluenceOnErrorPin",
        displayName : "Enable Influence on Error pin",
        description : "Configurable output generation on ERROR pin",
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

    var otherContexts = Common.getOtherContextNames()
    for (var cntx of otherContexts)
    {
        var onOtherCntx = Common.getModuleForCore(inst.$module.$name, cntx);
        if (onOtherCntx)
        {
            for (var instance_index in onOtherCntx.$instances)
            {
                var instance_obj = onOtherCntx.$instances[instance_index];
                if(instance_obj.typeEventSource == false)
                {
                    usedESMInsts.push(instance_obj.eventSource);
                }
            }
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

    if(inst.enableInfluenceOnErrorPin && !inst.$module.$static.useErrorPin)
    {
        validation.logWarning("One or more error events is configured to influence the Error Pin. Enable the use of Error Pin in the Global parameters section and configure.", inst, "enableInfluenceOnErrorPin");
    }
}

function onValidateStatic(mod, validation){
    if (!Common.isContextCPU1())
    {
        return
    }
    if((mod.errorPinCounterValue > 0xFFFFFF) || (mod.errorPinCounterValue < 0) || !Number.isInteger(mod.errorPinCounterValue)) {
        validation.logError("Error Pin Counter Pre-load value must be an integer between 0 and 0xFFFFFF", mod, "errorPinCounterValue")
    }
    if((mod.pwmHighCounterValue > 0xFFFFFF) || (mod.pwmHighCounterValue < 0) || !Number.isInteger(mod.pwmHighCounterValue)) {
        validation.logError("PWM High Counter Pre-load value must be an integer between 0 and 0xFFFFFF", mod, "pwmHighCounterValue")
    }
    if((mod.pwmLowCounterValue > 0xFFFFFF) || (mod.pwmLowCounterValue < 0) || !Number.isInteger(mod.pwmLowCounterValue)) {
        validation.logError("PWM Low Counter Pre-load value must be an integer between 0 and 0xFFFFFF", mod, "pwmLowCounterValue")
    }
}


var esmSysModule = {
    peripheralName: "ESMSYSTEM",
    displayName: "ERROR SIGNALING SYSTEM",
    defaultInstanceName: "myErrorSignalingSys",
    description: "Error Signaling module configuration",
    // longDescription : longDescription,
    templates: {
        boardh : "/driverlib/esm/esmsystem.board.h.xdt",
        boardc : "/driverlib/esm/esmsystem.board.c.xdt",
    },
    moduleStatic : {
        name: "esmSysGlobal",
        displayName: "Error Signaling Global",
        config: globalConfig,
        validate : onValidateStatic,
        pinmuxRequirements : Pinmux.esmPinmuxRequirements,
        shouldBeAllocatedAsResource: true,
        alwaysAllocateAsResource: true
    },
};

if(!Common.isAllocationSetupMode())
{
    esmSysModule.validate = onValidate;
    esmSysModule.config   = Common.filterConfigsIfInSetupMode(config);
    esmSysModule.uiAdd    = "staticAndInstance";
}

if (esmSysModule.maxInstances <= 0){
    delete esmSysModule.pinmuxRequirements;
}


exports = esmSysModule;