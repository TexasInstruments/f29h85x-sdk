let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_dac.js");

/* Intro splash on GUI */
let longDescription = "DAC";

var DAC_INSTANCE = [
    { name: "DACA_BASE", displayName: "DACA"},
    { name: "DACB_BASE", displayName: "DACB"},
];

function onChangeDACVref(inst, ui)
{
    if (inst.referenceVoltage == device_driverlib_peripheral.DAC_ReferenceVoltage[0].name){
        ui.gainMode.hidden = true
        
    }
    else {
        ui.gainMode.hidden = false
    }
}

function onChangeLoadMode(inst, ui)
{
    if (inst.loadMode == device_driverlib_peripheral.DAC_LoadMode[0].name){
        ui.ePWMSyncSignal.hidden = true
        
    }
    else {
        ui.ePWMSyncSignal.hidden = false
    }   
}

var dacStatic = undefined;

/* determine ASYSCTL static module dependency */
dacStatic = {
    name: "dacGlobal",
    displayName: "DAC Global",
    modules: Common.autoForce("asysctl", "/driverlib/asysctl.js")
}

var numberOfDACs = 2;


DAC_INSTANCE = [
    { name: "DACA_BASE", displayName: "DACA"},
    { name: "DACB_BASE", displayName: "DACB"},
];


/* Array of possible ePWM sync signals */
var ePWMInstances = Common.peripheralCount("EPWM")
var ePWMArray = [];
for(var i = 0; i < ePWMInstances; i++) {
    ePWMArray.push()
    ePWMArray.push({ name: ""+(i+1), displayName: "EPWM"+(i+1)+"SYNCPER"})
}

// Default pin name
var defaultDacName = "DACA";
defaultDacName = Pinmux.getDeviceDACName(defaultDacName)


/* Array of DAC configurables that are common across device families */
let config = [
    {
        name        : "dacBase",
        displayName : "DAC Instance",
        description : 'Instance of the DAC used.',
        hidden      : false,
        default     : DAC_INSTANCE[0].name,
        options     : DAC_INSTANCE
    },
    {
        name        : "dacDevicePinName",
        displayName : "DAC Device Pin Name",
        description : 'The device pin name and the signal name for that pin',
        hidden      : false,
        getValue    : (inst) => {
            var dacOutName = Pinmux.getDeviceDACName(inst.dacBase.replace("_BASE", ""))
            var dacAnalogPins = Pinmux.findAllAnalogPin(dacOutName);
            return Pinmux.getDevicePinInfoDescription(dacAnalogPins);
        },
        default     : Pinmux.getDevicePinInfoDescription(defaultDacName)
    },
    {
        name        : "referenceVoltage",
        displayName : "Reference Voltage",
        description : 'Sets the DAC Reference Voltage',
        hidden      : false,
        onChange    : onChangeDACVref,
        default     : device_driverlib_peripheral.DAC_ReferenceVoltage[0].name,
        options     : device_driverlib_peripheral.DAC_ReferenceVoltage
    },
    {
        name        : "loadMode",
        displayName : "Load Mode",
        description : 'Sets the DAC Load Mode',
        hidden      : false,
        onChange    : onChangeLoadMode,
        default     : device_driverlib_peripheral.DAC_LoadMode[0].name,
        options     : device_driverlib_peripheral.DAC_LoadMode
    },
    {
        name        : "ePWMSyncSignal",
        displayName : "EPWMSYNCPER Signal",
        description : 'Sets the DAC ePWMSYNC Signal',
        hidden      : true,
        default     : ePWMArray[0].name,
        options     : ePWMArray
    },
    {
        name        : "shadowValue",
        displayName : "Shadow Value",
        description : 'Set the DAC Shadow Output Value.',
        hidden      : false,
        default     : 0
    },
    {
        name        : "enableOutput",
        displayName : "Enable Output",
        description : 'Whether or not to enable the DAC output.',
        hidden      : false,
        default     : false,
    },
    {
        name        : "lockedRegisters",
        displayName : "Lock DAC Registers",
        description : 'Which DAC Registers to enable.',
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : [
            {name: "DAC_LOCK_CONTROL", displayName: "Control Register"},
            {name: "DAC_LOCK_SHADOW", displayName: "Shadow Register"},
            {name: "DAC_LOCK_OUTPUT", displayName: "Output Register"},
        ],
        
    },
];

config.push(
    {
        name : "Group_Sys",
        displayName : "System Configuration",
        collapsed : true,
        config : []
    }
)



// Gain Mode 
config.splice(2, 0, 
    {
        name        : "gainMode",
        displayName : "Gain Mode",
        description : 'Sets the DAC Gain Mode',
        hidden      : true,
        default     : device_driverlib_peripheral.DAC_GainMode[0].name,
        options     : device_driverlib_peripheral.DAC_GainMode
    }
);

function onValidate(inst, validation) {

    //
    // Check Multicontext
    //
    if (Common.isContextCPU2()) {
        if (Common.isMultiCoreSysConfig()) {
            //
            // Check if the analog module is added on CPU1 if the current context is CPU2
            //
            if (Common.isModuleOnOtherContext("/driverlib/analog.js") == false) {
                validation.logError(
                    "The ANALOG PinMux module needs to be added on CPU1 when a DAC instance is added on CPU2",inst,"dacBase");
            }
        } 
        else {
            validation.logWarning(
                "The ANALOG PinMux module needs to be added on CPU1 when a DAC instance is added on CPU2",inst,"dacBase");
        } 
    }

    var usedDACInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedDACInsts.push(instance_obj.dacBase);
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
                usedDACInsts.push(instance_obj.dacBase);
            }
        }
    }

    var duplicatesResult = Common.findDuplicates(usedDACInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ") 
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The DAC Instance used. Duplicates: " + allDuplicates, 
            inst, "dacBase");
    }

    if (inst.shadowValue < 0 || inst.shadowValue > 4095)
    {
        validation.logError(
            "Enter an integer for Shadow Value between 0 and 4095!", 
            inst, "shadowValue");
    }
    if (!Number.isInteger(inst.shadowValue))
    {
        validation.logError(
            "Shadow Value must be an integer", 
            inst, "shadowValue");
    }
    var asysctlMod = system.modules['/driverlib/asysctl.js'];
    if (asysctlMod){
        var stat = asysctlMod.$static
        //validation.logError("An example error in gainMode", inst, "gainMode");
        if(inst.referenceVoltage == "DAC_REF_VDAC" && inst.gainMode == "DAC_GAIN_TWO"){
            validation.logError(
                "Selected gain mode not supported for configured reference voltage.",
                inst, "gainMode");
            validation.logError(
                "Selected reference voltage not supported for configured gain mode.",
                inst, "referenceVoltage");
        } // the case of VDAC, no gain mode select! the case of [vdac,   x,        x,    gain 2x]
        if(inst.referenceVoltage == "DAC_REF_ADC_VREFHI" && stat.analogReference == "INTERNAL" 
                && stat.analogReferenceVoltage == "1P65" && inst.gainMode == "DAC_GAIN_ONE"){
            validation.logError(
                "Selected gain mode not supported for configured analog reference voltage.", 
                inst, "gainMode");
            validation.logError(
                "Selected analog reference voltage not supported for configured gain mode.", 
                stat, "analogReferenceVoltage");
        } // the case of [vrefhi, internal, 1.65, gain 1x]
        if(inst.referenceVoltage == "DAC_REF_ADC_VREFHI" && stat.analogReference == "INTERNAL"
                && stat.analogReferenceVoltage == "2P5" && inst.gainMode == "DAC_GAIN_TWO"){
            validation.logError(
                "Selected gain mode not supported for configured analog reference voltage.", 
                inst, "gainMode");
            validation.logError(
                "Selected analog reference voltage not supported for configured gain mode.", 
                stat, "analogReferenceVoltage");               
        } // the case of [vrefhi, internal, 2.5,  gain 2x]
        if(inst.referenceVoltage == "DAC_REF_ADC_VREFHI" && stat.analogReference == "EXTERNAL" && inst.gainMode == "DAC_GAIN_TWO"){
            validation.logError(
                "Selected gain mode not supported for configured analog reference.", 
                inst, "gainMode");
            validation.logError(
                "Selected analog reference not supported for configured gain mode.", 
                stat, "analogReference");
        } // the case of [vrefhi, external, x,    gain 2x]
    }


    //
    // Check for Pin Usage in analog
    //
    if (Common.isContextCPU1()) {
        if (Common.peripheralCount("ANALOG") > 0)
        {
            if(inst.enableOutput){
                var devicePinNameInfo = inst["dacDevicePinName"]
                if (devicePinNameInfo == Pinmux.NO_DEVICE_PIN_FOUND)
                {
                    validation.logWarning(
                        "DAC output selected has no device pin found.",
                        inst, "dacDevicePinName");
                }
                else
                {
                    var dacOutName = Pinmux.getDeviceDACName(inst.dacBase.replace("_BASE", ""))
                    var dacAnalogPins = Pinmux.findAllAnalogPin(dacOutName);
                    var selectedInterfaces = Pinmux.getPeripheralUseCaseInterfaces(inst.analog, "ANALOG", inst.analog.useCase);
                    var allInterfaces = Pinmux.getPeripheralUseCaseInterfaces(inst.analog, "ANALOG", "ALL");


                    for (var dacPin of dacAnalogPins)
                    {
                        var pinSelected = dacPin.PinDesignSignalName;
                        if (!selectedInterfaces.includes(pinSelected) && allInterfaces.includes(pinSelected))
                        {
                            validation.logError(
                                "The pin " + pinSelected + " is not selected in the ANALOG PinMux module." +
                                " Add this pin to the 'Pins Used' or change the 'Use Case'",
                                inst,"dacDevicePinName");
                        }

                    }

                }
            }
        }
    }

    //
    // Check against ADC and CMPSS
    //
    if (inst["dacDevicePinName"])
    {
        if(inst.enableOutput){
            var devicePinNameInfo = inst["dacDevicePinName"]
            if (devicePinNameInfo != Pinmux.NO_DEVICE_PIN_FOUND)
            {
                var dacOutName = Pinmux.getDeviceDACName(inst.dacBase.replace("_BASE", ""))
                var dacAnalogPins = Pinmux.findAllAnalogPin(dacOutName);
                var adcPinsUsed = Pinmux.getADCPinsUsed();
                var cmpssPinsUsed = Pinmux.getCMPSSPinsUsed();
				//var cmpssLitePinsUsed = Pinmux.getCMPSSLitePinsUsed();

                for (var dacPin of dacAnalogPins)
                {
                    var pinSelected = dacPin.PinDesignSignalName;
                    if (adcPinsUsed.includes(pinSelected))
                    {
                        validation.logWarning(
                            "The pin " + pinSelected + " is also selected by the ADC module." +
                            " The DAC output will be driving the ADC pin input. This is an acceptable " + 
                            "use-case.",
                            inst, "dacDevicePinName");
                    }

                    if (cmpssPinsUsed.includes(pinSelected))
                    {
                        validation.logWarning(
                            "The pin " + pinSelected + " is also selected by the CMPSS module." +
                            " The DAC output will be driving the CMPSS pin input. This is an acceptable " + 
                            "use-case.",
                            inst, "dacDevicePinName");
                    }
					// if (cmpssLitePinsUsed.includes(pinSelected))
                    // {
                    //     validation.logWavrning(
                    //         "The pin " + pinSelected + " is also selected by the CMPSSLite module." +
                    //         " The DAC output will be driving the CMPSSLite pin input. This is an acceptable " + 
                    //         "use-case.",
                    //         inst, "dacDevicePinName");
                    // }
                }
            }
        }
    }
}


var sharedModuleInstances = undefined;
if (Common.isContextCPU1()) {
    if (Common.peripheralCount("ANALOG") > 0) {
        sharedModuleInstances = function () {
                return (
                    [
                        {
                            name: "analog",
                            displayName: "Analog PinMux",
                            moduleName: "/driverlib/analog.js"
                        },
                    ]
                );
            }
    }
}

var dacModule = {
    peripheralName: "DAC",
    displayName: "DAC",
    maxInstances: numberOfDACs,
    defaultInstanceName: "myDAC",
    description: "Digital Analog Converter",
    //longDescription: (Common.getCollateralFindabilityList("DAC")),
    config: config,
    moduleStatic: dacStatic,
    sharedModuleInstances: sharedModuleInstances,
    moduleInstances: (inst) => {
        var clkReturn = [];
        clkReturn = clkReturn.concat([
            {
                name: "periphClock",
                group: "Group_Sys",
                displayName: "",
                moduleName: "/driverlib/perClock.js",
                collapsed: false,
                requiredArgs:{
                    pinmuxPeripheralModule : "",
                    peripheralInst: inst.dacBase.replace("_BASE", "")
                }
            },
            {
                name: "periphConfig",
                group: "Group_Sys",
                displayName: "",
                moduleName: "/driverlib/perConfig.js",
                collapsed: false,
                requiredArgs:{
                    pinmuxPeripheralModule : "",
                    peripheralInst: inst.dacBase.replace("_BASE", "")
                }
            },
        ])
        
        return clkReturn;
    },
    templates: {
        boardc : "/driverlib/dac/dac.board.c.xdt",
        boardh : "/driverlib/dac/dac.board.h.xdt"
    },
    validate    : onValidate,
};

exports = dacModule;