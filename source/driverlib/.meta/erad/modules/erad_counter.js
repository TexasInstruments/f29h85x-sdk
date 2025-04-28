let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_erad.js");

let SEC_MODES = [
    {name: "0", displayName: "Counter Mode"},
    {name: "1", displayName: "Stopwatch Mode"},
    {name: "3", displayName: "Cumulative Mode"}
];

let CLOCK_SOURCE = [
    {name: "0", displayName: "CPU Cycles as source"},
    {name: "1", displayName: "External events as source"}
];

let COUNTER_MODES = [
    {name: "true", displayName: "Reset on match"},
    {name: "false", displayName: "Continuous Mode"}
];

function onChangeSECMode(inst, ui)
{   
    for (var config_i in stopwatchModeConfig)
    {
        ui[stopwatchModeConfig[config_i].name].hidden = (inst.secMode == SEC_MODES[0].name);
    }
    for (var config_i in counterModeConfig)
    {
        ui[counterModeConfig[config_i].name].hidden = !(inst.secMode == SEC_MODES[0].name);
    }
}

function onChangeClockSource(inst, ui)
{
    ui.externalClockSource.hidden = (inst.clockSource == CLOCK_SOURCE[0].name);
    ui.countMode.hidden = (inst.clockSource == CLOCK_SOURCE[0].name);
}

function onChangeUseExternalResetSource(inst, ui)
{
    ui.externalResetSource.hidden = !inst.useExternalResetSource;
}

var config = [
    {
        name        : "instance",
        displayName : "SEC Instance",
        description : 'System Event Counter (SEC) Instance used',
        hidden      : false,
        default     : device_driverlib_peripheral.ERAD_CounterInstance[0].name,
        options     : device_driverlib_peripheral.ERAD_CounterInstance,
    },
    {
        name        : "owner",
        displayName : "Owner",
        description : 'Owner of the ERAD module',
        hidden      : false,
		readOnly    : true,
        default     : "C29x",
        options     : [
            {name: "C29x"},
            {name: "Debugger"}
        ]
    },
    {
        name        : "secMode",
        displayName : "ERAD SEC Mode",
        description : 'Mode of the SEC Module',
        hidden      : false,
        default     : SEC_MODES[0].name,
        options     : SEC_MODES,
        onChange    : onChangeSECMode
    }
];

var counterModeConfig = [
    {
        name        : "counterPeriod",
        displayName : "Counter Reference Value",
        description : "The reference value for the counter to count up to!",
        default     : 0xFFFFFFFF,
        displayFormat: "hex",
    },
    {
        name        : "counterMode",
        displayName : "Reset Counter on Match",
        description : "Whether or not to reset the Counter when the COUNT matches the REF value",
        default     : false,
        hidden      : false
    }
]

var stopwatchModeConfig = [
    {
        name        : "swStart",
        displayName : "Start Event Signal",
        description : "The source to start the counter in order to increment on the clock source!",
        default     : device_driverlib_peripheral.ERAD_Counter_Input_Event[0].name,
        options     : device_driverlib_peripheral.ERAD_Counter_Input_Event,
        hidden      : true
    },
    {
        name        : "swStop",
        displayName : "Stop Event Signal",
        description : "The source to stop the counter.",
        default     : device_driverlib_peripheral.ERAD_Counter_Input_Event[0].name,
        options     : device_driverlib_peripheral.ERAD_Counter_Input_Event,
        hidden      : true
    },
    {
        name        : "swReferenceCount",
        displayName : "Reference Counter Value",
        description : "The reference value for the counter to generate a HALT or Interrupt!",
        default     : 0xFFFFFFFF,
        displayFormat: "hex",
        hidden      : true
    },
]

var commonConfig = [
    {
        name        : "clockSource",
        displayName : "Clock Source",
        description : "The clock source used for incrementing the counter",
        default     : CLOCK_SOURCE[0].name,
        options     : CLOCK_SOURCE,
        onChange    : onChangeClockSource
    },
    {
        name        : "externalClockSource",
        displayName : "External Clock Source",
        description : "The clock source used for incrementing the counter from external signals rising edge",
        options     : device_driverlib_peripheral.ERAD_Counter_Input_Event,
        default     : device_driverlib_peripheral.ERAD_Counter_Input_Event[0].name,
        hidden      : true
    },
    {
        name        : "countMode",
        displayName : "Count Mode",
        description : "Choose to count Rising edges or Active duration",
        default     : device_driverlib_peripheral.ERAD_Counter_Event_Mode[1].name,
        options     : device_driverlib_peripheral.ERAD_Counter_Event_Mode,
        hidden      : true
    },
    {
        name        : "useExternalResetSource",
        displayName : "Use an External Reset Source",
        description : "Whether or not to use an external reset source for the counter",
        default     : false,
        onChange    : onChangeUseExternalResetSource,
        hidden      : false
    },
    {
        name        : "externalResetSource",
        displayName : "External Reset Source",
        description : "The reset source used to set the counter to 0, coming from external signals rising edge",
        default     : device_driverlib_peripheral.ERAD_Counter_Input_Event[0].name,
        options     : device_driverlib_peripheral.ERAD_Counter_Input_Event,
        hidden      : true
    },
    {
        name        : "haltCPU",
        displayName : "Halt CPU on Count Match",
        description : "Whether or not to halt the CPU when the COUNT matches the REF value",
        default     : false
    },
    {
        name        : "interrupt",
        displayName : "Generate Interrupt on Count Match",
        description : "Whether or not to generate Interrupt when the COUNT matches the REF value",
        default     : false
    },
    {
        name        : "NMI",
        displayName : "Generate NMI on Match",
        description : "Whether or not to generate NMI when the COUNT matches the REF value",
        default     : false
    }
]

config = config.concat(counterModeConfig);
config = config.concat(stopwatchModeConfig);
config = config.concat(commonConfig);

function onValidate(inst, validation)
{
    if (Common.isContextCPU1() && (inst.instance == "ERAD_COUNTER3"))
    {
        validation.logWarning("The SEC Instance is used for a workaround (Refer Device_errataWorkaroundNMIVectorFetch()). Select a different SEC instance.", inst, "instance");
    }

    var usedCounterInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedCounterInsts.push(instance_obj.instance);
    }

    var duplicatesResult = Common.findDuplicates(usedCounterInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ")
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The SEC Instance is already in use. Duplicates: " + allDuplicates,
            inst, "instance");
    }

    if(inst.interrupt && inst.NMI)
    {
        validation.logError("Cannot enable both interrupt and NMI for an event.", inst, "NMI")
    }
    if ((inst.swReferenceCount > 0xFFFFFFFF) || (inst.swReferenceCount < 0) || !Number.isInteger(inst.swReferenceCount))
    {
        validation.logError("The counter reference value must be an integer between 0 and 0xFFFFFFFF", inst, "swReferenceCount");
    }
    if ((inst.counterPeriod > 0xFFFFFFFF) || (inst.counterPeriod < 0) || !Number.isInteger(inst.counterPeriod))
    {
        validation.logError("The counter period reference value must be an integer between 0 and 0xFFFFFFFF", inst, "counterPeriod");
    }
    if(inst.NMI)
    {
        validation.logInfo("This NMI signal is routed to the ESM. Configure the " + system.context + "_ERAD_NMI event in the Error Signaling Configuration block.", inst, "NMI");
    }
}

var eradSECSubmodule = {
    displayName: "ERAD COUNTER",
    defaultInstanceName: "myERAD_COUNTER",
    description: "ERAD System Event Counter (SEC)",
    config: config,
    validate: onValidate,
    templates: {
        boardc : "",
        boardh : ""
    },
};


exports = eradSECSubmodule;