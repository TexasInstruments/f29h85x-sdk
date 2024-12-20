let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_cputimer.js");

/* Intro splash on GUI */
let longDescription = "";

var CPUTIMER_INSTANCE = [
    { name: "CPUTIMER0_BASE", displayName: "CPUTIMER0"},
    { name: "CPUTIMER1_BASE", displayName: "CPUTIMER1"},
    { name: "CPUTIMER2_BASE", displayName: "CPUTIMER2"},
]

function onChangeCPUTIMERBase(inst, ui)
{
    if (inst.cputimerBase == "CPUTIMER2_BASE"){
        ui.clockSource.hidden = false;
        ui.clockPrescaler.hidden = false;
    }
    else {
        ui.clockSource.hidden = true;
        ui.clockPrescaler.hidden = true;
    }
}

function calcInputFreq(inst, ui)
{
    let timerClock = Common.getSYSCLK();
    let clocktree = Common.getClockTree()
   
    if(clocktree)
    {
        if (inst.cputimerBase == "CPUTIMER2_BASE")
        {
            timerClock = (clocktree["TIMER2CLK"].in)
        }
    }
    return timerClock;
}

function calcTimerFreq(inst, ui)
{
    return ((inst.timerInputFreq / (inst.timerPrescaler + 1)) / inst.timerPeriod) * Math.pow(10,6)
}

function calcTimerPeriod(inst, ui)
{
    return (1 / inst.timerFreq)
}

/* Array of CPUTIMER configurables that are common across device families */
let config = [
    {
        name : "GROUP_PERCFG",
        displayName: "Peripheral Configuration",
        collapsed: false,
        config: [
            {
                name        : "cputimerBase",
                displayName : "CPUTIMER Instance",
                description : 'Instance of the CPUTIMER used.',
                hidden      : false,
                onChange    : onChangeCPUTIMERBase,
                default     : CPUTIMER_INSTANCE[0].name,
                options     : CPUTIMER_INSTANCE
            },
            {
                name        : "clockSource",
                displayName : "Clock Source",
                description : 'Clock source for the Timer',
                hidden      : true,
                default     : "PLLSYSCLK",
                getValue    : () => {
                    var clockTree = Common.getClockTree();
                    if(clockTree){
                        return clockTree["TMR2CLKSRCSEL"].inputSelect
                    }
                    else{
                        return "PLLSYSCLK";
                    }
                },
                readOnly    : true,
            },
            {
                name        : "clockPrescaler",
                displayName : "Clock Prescaler",
                description : 'Sets the prescaler for the Clock source of the Timer.',
                hidden      : true,
                default     : 1,
                getValue    : () => {
                    var clockTree = Common.getClockTree();
                    if(clockTree){
                        return clockTree["TMR2CLKPRESCALE"].divideValue
                    }
                    else{
                        return 1;
                    }
                },
                readOnly    : true,
            },
            {
                name        : "timerInputFreq",
                displayName : "Timer Input Frequency (MHz)",
                description : 'CPUTIMER Input frequency in MHz.',
                hidden      : false,
                default     : 0,
                getValue    : calcInputFreq,
            },
            {
                name        : "emulationMode",
                displayName : "Emulation Mode",
                description : 'Emulation Mode',
                hidden      : false,
                default     : device_driverlib_peripheral.CPUTimer_EmulationMode[0].name,
                options     : device_driverlib_peripheral.CPUTimer_EmulationMode
            },
            {
                name        : "timerPrescaler",
                displayName : "Timer Prescaler",
                description : 'Sets the CPUTIMER timer prescaler.',
                hidden      : false,
                default     : 0
            },
            {
                name        : "timerPeriod",
                displayName : "Timer Period (cycles)",
                description : 'Sets the CPUTIMER period in terms of number of cycles.',
                hidden      : false,
                default     : 0,
            },
            {
                name        : "timerPeriodSec",
                displayName : "Timer Period (s)",
                description : 'Sets the CPUTIMER period in seconds.',
                hidden      : false,
                default     : 0,
                getValue    : calcTimerPeriod,
            },
            {
                name        : "timerFreq",
                displayName : "Timer Frequency (Hz)",
                description : 'The CPUTIMER Interrupt Frequency in Hz.',
                hidden      : false,
                default     : 0,
                getValue    : calcTimerFreq,
            },
            {
                name        : "startTimer",
                displayName : "Start Timer",
                description : 'Whether or not to start the timer.',
                hidden      : false,
                default     : false
            },
        ]
    },
    {
        name: "GROUP_ISR",
        displayName: "Interrupt Configuration",
        collapsed: true,
        config: [
            {
                name        : "enableInterrupt",
                displayName : "Enable Interrupt",
                description : 'Whether or not to enable interrupts.',
                hidden      : false,
                default     : false
            },
            {
                name        : "registerInterrupts",
                displayName : "Register Interrupt in PIPE",
                description : 'Whether or not to register interrupt in the PIPE module.',
                hidden      : false,
                default     : false
            },
        ]
    },
    {
        name: "GROUP_SYS",
        displayName: "System Configuration",
        collapsed: true,
        config: []
    }
];


function onValidate(inst, validation) 
{   
    var usedCPUTIMERInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedCPUTIMERInsts.push(instance_obj.cputimerBase);
    }

    var duplicatesResult = Common.findDuplicates(usedCPUTIMERInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ") 
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The CPUTIMER Instance used. Duplicates: " + allDuplicates, 
            inst, "cputimerBase");
    }


    if (inst.timerPrescaler < 0 || inst.timerPrescaler > 65535)
    {
        validation.logError(
            "Enter an integer for Timer Prescaler between 0 and 65535!", 
            inst, "timerPrescaler");
    }
    if (!Number.isInteger(inst.timerPrescaler))
    {
        validation.logError(
            "Timer Prescaler must be an integer", 
            inst, "timerPrescaler");
    }
    if (inst.timerPeriod < 0 || inst.timerPeriod > 4294967295)
    {
        validation.logError(
            "Enter an integer for Timer Period between 0 and 4294967295!", 
            inst, "timerPeriod");
    }
    if (!Number.isInteger(inst.timerPeriod))
    {
        validation.logError(
            "Timer Period must be an integer", 
            inst, "timerPeriod");
    }
    if (inst.timerPeriod == 0)
    {
        validation.logWarning(
            "Timer Period is currently set to 0", 
            inst, "timerPeriod");
    }
    
}

function moduleInstances(inst)
{
    let components = []
    if (inst.registerInterrupts)
    {
        var interruptName = inst.cputimerBase.replace("CPU", "").replace("_BASE", "");
        components.push({
            name: "timerInt",
            group: "GROUP_ISR",
            displayName: "Timer Interrupt",
            moduleName: "/driverlib/interrupt.js",
            collapsed: false,
            args: {
                $name : inst.$name + "_INT",
                typeInterruptName : true,
                pinmuxPeripheralModule : "",
                driverlibInt: "INT_" + interruptName,
                interruptHandler : "INT_" + inst.$name + "_ISR",
            }
        })
    }

    components.push(
        {
            name: "periphClock",
            displayName: "",
            group: "GROUP_SYS",
            moduleName: "/driverlib/perClock.js",
            collapsed: false,
            requiredArgs:{
                pinmuxPeripheralModule : "",
                peripheralInst: inst.cputimerBase.replace("_BASE", "")
            }
        }
    )
    return components;
}

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["CPUTIMER"]));
}

var cputimerModule = {
    peripheralName: "CPUTIMER",
    displayName: "CPUTIMER",
    maxInstances: 3,
    defaultInstanceName: "myCPUTIMER",
    description: "CPUTIMER Peripheral",
    filterHardware : filterHardware,
    config: config,
    moduleInstances : moduleInstances,
    templates: {
        boardc : "/driverlib/cputimer/cputimer.board.c.xdt",
        boardh : "/driverlib/cputimer/cputimer.board.h.xdt"
    },
    validate    : onValidate
};


if (cputimerModule.maxInstances <= 0)
{
    delete cputimerModule.pinmuxRequirements;
}

exports = cputimerModule;