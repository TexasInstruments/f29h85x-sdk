let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_dcc.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

/* Intro splash on GUI */
let longDescription = "The dual-clock comparator module is used for evaluating and monitoring the clock" +
                      " input based on a secondclock, which can be a more accurate and reliable version." +
                      " This instrumentation is used to detect faults in clocksource or clock structures,"+
                      " thereby enhancing the system's safety metrics.";



var DCC_INSTANCE = [];
for (var dcc of device_driverlib_memmap.DCCMemoryMap) {
    DCC_INSTANCE.push({
        name : dcc.name,
        displayName : dcc.displayName
    })
}

var fclk0_clocktree_mapping = {
    "DCC_COUNT0SRC_XTAL" : ["XTAL_OR_X1", "External_Clock"] ,
    "DCC_COUNT0SRC_INTOSC1" : ["INTOSC1", "out"] ,
    "DCC_COUNT0SRC_INTOSC2" : ["INTOSC2", "out"] ,
    "DCC_COUNT0SRC_TCK" : ["PLLSYSCLK", "in"] ,
    "DCC_COUNT0SRC_CPU1_CLOCK" : ["CPU1_CPUCLK", "in"] ,
    "DCC_COUNT0SRC_AUXCLKIN" : ["AUXCLKIN", "in"] ,
    "DCC_COUNT0SRC_INPUTXBAR1_INPUT16" : ["PLLSYSCLK", "in"] ,
}

var fclk1_clocktree_mapping = {
    "DCC_COUNT1SRC_PLL" : ["PLLSYSCLK", "in"] ,
    "DCC_COUNT1SRC_FLC1_FCLK" : ["PLLSYSCLK", "in"] ,
    "DCC_COUNT1SRC_INTOSC1" : ["INTOSC1", "out"] ,
    "DCC_COUNT1SRC_INTOSC2" : ["INTOSC2", "out"] ,
    "DCC_COUNT1SRC_ECATPHYCLK" : ["ECATDIV", "out"] ,
    "DCC_COUNT1SRC_CPU1_CLOCK" : ["CPU1_CPUCLK", "in"] ,
    "DCC_COUNT1SRC_CPU2_CLOCK" : ["CPU2_CPUCLK", "in"] ,
    "DCC_COUNT1SRC_RTDMA_CLOCK" : ["PLLSYSCLK", "in"] ,
    "DCC_COUNT1SRC_INPUTXBAR1_INPUT15" : ["PLLSYSCLK", "in"] ,
    "DCC_COUNT1SRC_AUXCLKIN" : ["AUXCLKIN", "in"] ,
    "DCC_COUNT1SRC_EPWMCLK" : ["EPWMCLK", "in"] ,
    "DCC_COUNT1SRC_ADCCLK" : ["PERx_CPU_PLLSYSCLK_GATE", "out"] ,
    "DCC_COUNT1SRC_WDCLK" : ["Watchdog_domain", "in"] ,
    "DCC_COUNT1SRC_FLC2_FCLK" : ["PLLSYSCLK", "in"] ,
    "DCC_COUNT1SRC_CPU3_CLOCK" : ["CPU3_CPUCLK", "in"] ,
    "DCC_COUNT1SRC_INPUTXBAR1_INPUT11" : ["PLLSYSCLK", "in"] ,
    "DCC_COUNT1SRC_INPUTXBAR1_INPUT12" : ["PLLSYSCLK", "in"] ,
    "DCC_COUNT1SRC_MCANA" : ["MCANABITCLK", "in"] ,
    "DCC_COUNT1SRC_MCANB" : ["MCANBBITCLK", "in"] ,
    "DCC_COUNT1SRC_MCANC" : ["MCANCBITCLK", "in"] ,
    "DCC_COUNT1SRC_MCAND" : ["MCANDBITCLK", "in"] ,
    "DCC_COUNT1SRC_MCANE" : ["MCANEBITCLK", "in"] ,
    "DCC_COUNT1SRC_MCANF" : ["MCANFBITCLK", "in"] ,
    "DCC_COUNT1SRC_ESMCLK" : ["PLLSYSCLK", "in"] ,
}

function onChangeEnableDoneSignalInterrupt(inst, ui)
{
    if (inst.enableDoneSignalInterrupt == true){
        ui.registerInterrupts.hidden = false;
    }
    else {
        ui.registerInterrupts.hidden = true;
    }
}

function AutoCalculate(localDCCerrtol, localFclk1, localFclk0, localFsysclk, localMeasureFclk1, localFreqerrtol)
{
    var localcounter0seed;
    var localvalidcounter0seed;
    var localcounter1seed;
    var totalErr;
    var allowedFreqErr;
    var dccWindow;
    var asyncErr;
    var dccErr;

    if(localFclk1<localFclk0)
    {
        asyncErr = (2*(localFclk0/localFclk1))+(2*(localFsysclk/localFclk0));
    }
    else
    {
        asyncErr = (2+(2*(localFsysclk/localFclk0)));
    }

    dccErr = asyncErr + 8;
    dccWindow = dccErr/(localDCCerrtol*0.01);
    allowedFreqErr = Math.ceil(dccWindow*localFreqerrtol*0.01);
    totalErr = allowedFreqErr+dccErr;

    localcounter0seed = Math.ceil(dccWindow - totalErr);
    localvalidcounter0seed = Math.ceil(2 * totalErr);
    if(localMeasureFclk1 == false)
    {
        localcounter1seed = Math.ceil((localFclk1/localFclk0)*dccWindow);
    }
    else
    {
        localcounter1seed = 1048575;
    }
    //console.log(localcounter0seed)
    return {
        counter0seed: localcounter0seed,
        validcounter0seed : localvalidcounter0seed,
        counter1seed : localcounter1seed
    }
}

function autoCalculateResult(inst, seed)
{
    if(inst.freqAutofill == true)
        return AutoCalculate(inst.dccerrtol, inst.fclk1_autofill, inst.fclk0_autofill, inst.fsysclk, inst.measureFclk1, inst.freqerrtol)
    else
        return AutoCalculate(inst.dccerrtol, inst.fclk1, inst.fclk0, inst.fsysclk, inst.measureFclk1, inst.freqerrtol)
}

var SysClk_MHz = Common.SYSCLK_getMaxMHz();
var dccerrtol_default = 0.25;
var freqerrtol_default = 1.0;
var clockTree = Common.getClockTree();

if(clockTree){
    var fclk0_default = clockTree[fclk0_clocktree_mapping[device_driverlib_peripheral.DCC_Count0ClockSource[0].name][0]][fclk0_clocktree_mapping[device_driverlib_peripheral.DCC_Count0ClockSource[0].name][1]];    
    var fclk1_default = clockTree[fclk1_clocktree_mapping[device_driverlib_peripheral.DCC_Count1ClockSource[0].name][0]][fclk1_clocktree_mapping[device_driverlib_peripheral.DCC_Count1ClockSource[0].name][1]];
}
else{
    var fclk0_default = 25;    
    var fclk1_default = 200;
}

var autoCal_defaults = AutoCalculate(dccerrtol_default, fclk1_default, fclk0_default, SysClk_MHz, false, freqerrtol_default)

function onChangeAutoCalc(inst, ui)
{

    if(inst.counterAutoCalc)
    {
        ui.counter0seed.hidden = true;
        ui.validCounter0seed.hidden = true;
        ui.counter1seed.hidden = true;
        ui.counter0seed_autoCalc.hidden = false;
        ui.validCounter0seed_autoCalc.hidden = false;
        ui.counter1seed_autoCalc.hidden = false;
        ui.dccerrtol.hidden = false;
        ui.freqerrtol.hidden = false;
        ui.measureFclk1.hidden = false;
    }
    else
    {
        ui.counter0seed.hidden = false;
        ui.validCounter0seed.hidden = false;
        ui.counter1seed.hidden = false;
        ui.counter0seed_autoCalc.hidden = true;
        ui.validCounter0seed_autoCalc.hidden = true;
        ui.counter1seed_autoCalc.hidden = true;
        ui.dccerrtol.hidden = true;
        ui.freqerrtol.hidden = true;
        ui.measureFclk1.hidden = true;
    }
}

function onChangeFreqAutofill(inst, ui)
{
    if(inst.freqAutofill)
    {
        ui.fclk0_autofill.hidden = false;
        ui.fclk1_autofill.hidden = false;
        ui.fclk0.hidden = true;
        ui.fclk1.hidden = true;
    }
    else
    {
        ui.fclk0_autofill.hidden = true;
        ui.fclk1_autofill.hidden = true;
        ui.fclk0.hidden = false;
        ui.fclk1.hidden = false;
    }
}

/* Array of DCC configurables that are common across device families */
let config = [
    {
        name: "GROUP_PERCFG",
        displayName: "Peripheral Configuration",
        collapsed: false,
        config: [
            {
                name        : "dccBase",
                displayName : "DCC Instance",
                description : 'Instance of the DCC used.',
                hidden      : false,
                default     : DCC_INSTANCE[0].name,
                options     : DCC_INSTANCE
            },
            {
                 name        : "freqAutofill",
                 displayName : "Autofill Clock Sources Frequency from Clocktree",
                 description : 'Use the Frequency calculated in Clocktree for the selected Clock sources',
                 hidden      : false,
                 onChange    : onChangeFreqAutofill,
                 default     : true,
            },
            {
                name        : "fsysclk",
                displayName : "SysClk Frequency/ Fsysclk (MHz)",
                description : 'SysClk Frequency in MegaHertz used when DCC is running',
                hidden      : false,
                default     : Common.SYSCLK_getMaxMHz(),
                getValue    : () => Common.getSYSCLK()
            },
            {
                name        : "setCounter0ClkSource",
                displayName : "Counter 0 Clock Source",
                description : 'Set Counter 0 Clock Source',
                hidden      : false,
                default     : device_driverlib_peripheral.DCC_Count0ClockSource[0].name,
                options     : device_driverlib_peripheral.DCC_Count0ClockSource,
            },
            {
                name        : "fclk0_autofill",
                displayName : "Counter 0 Clock/ Fclk0 Frequency (MHz)",
                description : 'DCC Clk0 (Reference clock) If Fclk0 is unknown or to be measured, put some ball park/expected value, DO NOT LEAVE this field blank',
                hidden      : false,
                default     : fclk0_default,
                getValue    : (inst) => {
                    var clockTree = Common.getClockTree();
                    if(clockTree){
                        return clockTree[fclk0_clocktree_mapping[inst.setCounter0ClkSource][0]][fclk0_clocktree_mapping[inst.setCounter0ClkSource][1]]
                    }
                    else{
                        return fclk0_default;
                    }
                },
            },
            {
                name        : "fclk0",
                displayName : "Counter 0 Clock/ Fclk0 Frequency (MHz)",
                description : 'DCC Clk0 (Reference clock) If Fclk0 is unknown or to be measured, put some ball park/expected value, DO NOT LEAVE this field blank',
                hidden      : true,
                default     : fclk0_default,
            },
            {
                name        : "setCounter1ClkSource",
                displayName : "Counter 1 Clock Source",
                description : 'Set Counter 1 Clock Source',
                hidden      : false,
                default     : device_driverlib_peripheral.DCC_Count1ClockSource[0].name,
                options     : device_driverlib_peripheral.DCC_Count1ClockSource,
            },
            {
                name        : "fclk1_autofill",
                displayName : "Counter 1 Clock/ Fclk1 Frequency  (MHz)",
                description : 'DCC Clk1 (Reference clock) If Fclk0 is unknown or to be measured, put some ball park/expected value, DO NOT LEAVE this field blank',
                hidden      : false,
                default     : fclk1_default,
                getValue    : (inst) => {
                    var clockTree = Common.getClockTree();
                    if(clockTree){
                        return clockTree[fclk1_clocktree_mapping[inst.setCounter1ClkSource][0]][fclk1_clocktree_mapping[inst.setCounter1ClkSource][1]]
                    }
                    else{
                        return fclk1_default;
                    }
                },
            },
            {
                name        : "fclk1",
                displayName : "Counter 1 Clock/ Fclk1 Frequency  (MHz)",
                description : 'DCC Clk1 (Reference clock) If Fclk0 is unknown or to be measured, put some ball park/expected value, DO NOT LEAVE this field blank',
                hidden      : true,
                default     : fclk1_default,
            },
            {
                name        : "counterAutoCalc",
                displayName : "Auto Calculate Counter Seeds",
                description : 'Use Calculated Values for Counter Seed',
                hidden      : false,
                onChange    : onChangeAutoCalc,
                default     : true,
            },
            {
                name        : "counter0seed",
                displayName : "Counter 0 seed value",
                description : 'Sets the value for counter 0 seed',
                hidden      : true,
                default     : autoCal_defaults.counter0seed,
            },
            {
                name        : "validCounter0seed",
                displayName : "Valid duration Counter 0 seed value",
                description : 'Sets the value for the valid duration counter 0 seed',
                hidden      : true,
                default     : autoCal_defaults.validcounter0seed,
            },
            {
                name        : "counter1seed",
                displayName : "Counter 1 seed value",
                description : 'Sets the value for counter 1 seed',
                hidden      : true,
                default     : autoCal_defaults.counter1seed,
            },
            {
                name        : "dccerrtol",
                displayName : "DCC Error Tolerance (%)",
                description : 'Tolerance allowed due to error in DCC measurement',
                longDescription: "This is the allowed error tolerance due to the DCC itself.  A smaller value" +
                                " will be more accurate but take longer to converge.  If the entered value is too" +
                                " small, the counter values will be too large and an error will be auto generated",
                hidden      : false,
                onChange    : onChangeAutoCalc,
                default     : dccerrtol_default,
            },
            {
                name        : "freqerrtol",
                displayName : "Frequency Error Tolerance (%)",
                description : 'If Fclk1 is unknown or to be measured, leave this field blank',
                longDescription: "This is the expected tolerance of the clock under measurement",
                hidden      : false,
                onChange    : onChangeAutoCalc,
                default     : freqerrtol_default,
            },
            {
                name        : "counter0seed_autoCalc",
                displayName : "Counter 0 seed value",
                description : 'Sets the value for counter 0 seed',
                hidden      : false,
                default     : autoCal_defaults.counter0seed,
                readOnly    : true,
                getValue    : (inst) => autoCalculateResult(inst).counter0seed
            },
            {
                name        : "validCounter0seed_autoCalc",
                displayName : "Valid duration Counter 0 seed value",
                description : 'Sets the value for the valid duration counter 0 seed',
                hidden      : false,
                default     : autoCal_defaults.validcounter0seed,
                readOnly    : true,
                getValue    : (inst) => autoCalculateResult(inst).validcounter0seed
            },
            {
                name        : "counter1seed_autoCalc",
                displayName : "Counter 1 seed value",
                description : 'Sets the value for counter 1 seed',
                hidden      : false,
                default     : autoCal_defaults.counter1seed,
                readOnly    : true,
                getValue    : (inst) => autoCalculateResult(inst).counter1seed
            },
            {
                name        : "measureFclk1",
                displayName : "Measure System Clock Frequency (MHz)",
                description : 'If Fclk1/Fclk0 value is being measured, meaning instead of checking the validity of the ratio, want to measure exact clock frequency value, then check this box.',
                hidden      : false,
                onChange    : onChangeAutoCalc,
                default     : false,
            },
            {
                name        : "enableSingleShotMode",
                displayName : "Enable Single Shot Mode",
                description : 'Enable Single Shot Mode',
                hidden      : false,
                default     : false
            },
            {
                name        : "enableModule",
                displayName : "Start DCC in DCC_init function",
                description : 'Starts the DCC counters',
                hidden      : false,
                default     : false
            },
        ]
    },
    {
        name: "GROUP_INTERRUPT",
        displayName: "Interrupt Configuration",
        collapsed: true,
        config: [
            {
                name        : "enableDoneSignalInterrupt",
                displayName : "Enable Done Signal Interrupt",
                description : 'Enable Done Signal',
                hidden      : false,
                onChange    : onChangeEnableDoneSignalInterrupt,
                default     : false
            },
            {
                name        : "registerInterrupts",
                displayName : "Register Interrupt Handler",
                description : 'Whether or not to register interrupt handlers in the interrupt module.',
                hidden      : true,
                default     : false
            },
        ]
    },
    {
        name: "GROUP_ESM",
        displayName: "Error Signaling Configuration",
        collapsed: true,
        config: [
            {
                name        : "enableErrorSignal",
                displayName : "Enable Error Signal",
                description : 'Enable Error Signal to ESM',
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
    },
];

function onValidate(inst, validation)
{
    var usedDCCInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedDCCInsts.push(instance_obj.dccBase);
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
                usedDCCInsts.push(instance_obj.dccBase);
            }
        }
    }

    var duplicatesResult = Common.findDuplicates(usedDCCInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ")
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "This DCC Instance is already in use. Duplicates: " + allDuplicates,
            inst, "dccBase");
    }
    if (inst.counterAutoCalc)
    {
        if (inst.counter1seed_autoCalc < 0 || inst.counter1seed_autoCalc > 4294967295)
        {
            validation.logError(
                "Enter an integer for counter1 seed between 0 and 4294967295!",
                inst, "counter1seed_autoCalc");
        }
        if (!Number.isInteger(inst.counter1seed_autoCalc))
        {
            validation.logError(
                "counter 1 seed must be an integer",
                inst, "counter1seed_autoCalc");
        }
        if (inst.counter0seed_autoCalc < 0 || inst.counter0seed_autoCalc > 4294967295)
        {
            validation.logError(
                "Enter an integer for counter0 seed between 0 and 4294967295!",
                inst, "counter0seed_autoCalc");
        }
        if (!Number.isInteger(inst.counter0seed_autoCalc))
        {
            validation.logError(
                "counter 0 seed must be an integer",
                inst, "counter0seed_autoCalc");
        }
        if (inst.validCounter0seed_autoCalc < 0 || inst.validCounter0seed_autoCalc > 4294967295)
        {
            validation.logError(
                "Enter an integer for valid counter0 seed between 0 and 4294967295!",
                inst, "validCounter0seed_autoCalc");
        }
        if (!Number.isInteger(inst.validCounter0seed_autoCalc))
        {
            validation.logError(
                "valid counter 0 seed must be an integer",
                inst, "validCounter0seed_autoCalc");
        }
    }
    else
    {
        if (inst.counter1seed < 0 || inst.counter1seed > 4294967295)
        {
            validation.logError(
                "Enter an integer for counter1 seed between 0 and 4294967295!",
                inst, "counter1seed");
        }
        if (!Number.isInteger(inst.counter1seed))
        {
            validation.logError(
                "counter 1 seed must be an integer",
                inst, "counter1seed");
        }
        if (inst.counter0seed < 0 || inst.counter0seed > 4294967295)
        {
            validation.logError(
                "Enter an integer for counter0 seed between 0 and 4294967295!",
                inst, "counter0seed");
        }
        if (!Number.isInteger(inst.counter0seed))
        {
            validation.logError(
                "counter 0 seed must be an integer",
                inst, "counter0seed");
        }
        if (inst.validCounter0seed < 0 || inst.validCounter0seed > 4294967295)
        {
            validation.logError(
                "Enter an integer for valid counter0 seed between 0 and 4294967295!",
                inst, "validCounter0seed");
        }
        if (!Number.isInteger(inst.validCounter0seed))
        {
            validation.logError(
                "valid counter 0 seed must be an integer",
                inst, "validCounter0seed");
        }
    }
    if (inst.fsysclk >  SysClk_MHz)
    {
        validation.logError(
            "SysClk cannot be greater than " + SysClk_MHz + " MHz for this device",
            inst, "fsysclk");
    }
}

var sharedModuleInstances = undefined;

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["DCC"]));
}

function moduleInstances(inst)
{
    let components = []
    if (inst.enableDoneSignalInterrupt && inst.registerInterrupts)
    {
        components = components.concat([{
            name: "dccInt",
            group: "GROUP_INTERRUPT",
            displayName: "DCC Interrupt",
            moduleName: "/driverlib/interrupt.js",
            collapsed: true,
            args: {
                $name                  : inst.$name + "_INT",
                typeInterruptName      : true,
                pinmuxPeripheralModule : "",
                driverlibInt           : "INT_" + inst.dccBase.replace("_BASE", ""),
                interruptHandler       : "INT_" + inst.$name + "_ISR",
            },
        }])
    }
    
    if (inst.enableErrorSignal)
    {
        components = components.concat([{
            name: "ESMConfig",
            group: "GROUP_ESM",
            displayName: "DCC Error Signaling",
            moduleName : "/driverlib/esm.js",
            collapsed: true,
            args: {
                $name        : inst.$name + "_ESM",
            },
            requiredArgs:{
                eventSource  : "ESM_EVENT_" + inst.dccBase.replace("_BASE", "") + "_ERR"
            },
        }])
    }

    components.push(
        {
            name: "periphClock",
            group: "GROUP_SYS",
            displayName: "",
            moduleName: "/driverlib/perClock.js",
            collapsed: false,
            requiredArgs:{
                pinmuxPeripheralModule : "",
                peripheralInst: inst.dccBase.replace("_BASE", "")
            }
        }
    )

    components.push(
        {
            name: "periphConfig",
            group: "GROUP_SYS",
            displayName: "",
            moduleName: "/driverlib/perConfig.js",
            collapsed: false,
            requiredArgs:{
                pinmuxPeripheralModule : "",
                peripheralInst: inst.dccBase.replace("_BASE", "")
            }
        }
    )

    return components;
}

var dccModule = {
    peripheralName        : "DCC",
    displayName           : "DCC",
    maxInstances          : DCC_INSTANCE.length,
    defaultInstanceName   : "myDCC",
    description           : "DCC Peripheral",
    longDescription       : longDescription,
    filterHardware        : filterHardware,
    config                : config,
    moduleInstances       : moduleInstances,
    sharedModuleInstances : sharedModuleInstances,
    templates: {
     boardc : "/driverlib/dcc/dcc.board.c.xdt",
     boardh : "/driverlib/dcc/dcc.board.h.xdt"
    },
    validate   : onValidate
};


exports = dccModule;