let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_xbar.js");

/* Intro splash on GUI */
let longDescription = "The Input X-BAR is used to route signals from a GPIO to many different IP blocks " +
                    "such as the ADC(s), eCAP(s), ePWM(s), EQEP(s), WADI and external interrupts";

// var inputXbarCount = 64;
if (["F29H85x"].includes(Common.getDeviceName()))
{
    var inputXbarCount = 64
}

var extraInputOptions = [
	{name: "0xFFFE", displayName : "LOGIC HIGH ('1' selected input)"},
	{name: "0xFFFF", displayName : "LOGIC LOW ('0' selected input)"}
];

var gpios = Common.getGPIOs();
var aios = Common.getAIOs();
var inputxbarGPIOOptions = extraInputOptions;
for (var gpioIndex = 0; gpioIndex < gpios.length; gpioIndex++)
{
    inputxbarGPIOOptions.push({name: gpios[gpioIndex]});
}
for (var aioIndex = 0; aioIndex < aios.length; aioIndex++)
{
    inputxbarGPIOOptions.push({name: aios[aioIndex]});
}


var inputNumOptions = []
var connectedPeripherals = new Map()
for (var inputNum of device_driverlib_peripheral.XBAR_InputNum)
{
    inputNumOptions.push({
        name: inputNum.name
    })
    connectedPeripherals.set(inputNum.name, inputNum.displayName)
}

function onChangeInputxbarInput(inst, ui)
{
    if(inst.inputxbarInput == "XBAR_INPUT63" || inst.inputxbarInput == "XBAR_INPUT64")
    {
        ui.configureESM.hidden = false
    }
    else
    {
        inst.configureESM = false
        ui.configureESM.hidden = true
    }
}

var config = [
    {
        name: "GROUP_PERCFG",
        displayName: "Peripheral Configuration",
        collapsed: false,
        config: [
            {
                name        : "inputxbarInput",
                displayName : "Input",
                description : 'The Input number for Input X-Bar',
                hidden      : false,
                default     : inputNumOptions[0].name,
                options     : inputNumOptions,
                onChange    : onChangeInputxbarInput,
            },
            {
                name        : "inputxbarGpio",
                displayName : "Input Source",
                description : 'GPIO for this Input X-Bar',
                hidden      : false,
                default     : inputxbarGPIOOptions[0].name,
                options     : inputxbarGPIOOptions
            },
            {
                name        : "inputxbarSelectedSource",
                displayName : "Selected Source Of GPIO",
                description : 'Selected GPIO is connected to this signal in the application',
                hidden      : false,
                default     : "",
                getValue    : (inst) => {
                    let modNames = Object.keys(system.modules).sort();
                    for (var modName of modNames)
                    {
                        var mod = system.modules[modName]
                        var pinmuxRequirementsFunc = mod.pinmuxRequirements;
                        if (pinmuxRequirementsFunc)
                        {
                            for (var modInstance of mod.$instances)
                            {
                                var pinmuxRequirements = pinmuxRequirementsFunc(modInstance);
                                //console.log(pinmuxRequirements)
                                for (var pinmuxReq of pinmuxRequirements)
                                {
                                    var pinmuxReqName = pinmuxReq.name;
                                    //console.log(pinmuxReqName)
                                    if (pinmuxReq.resources)
                                    {
                                        //
                                        // Normal Peripheral Other than GPIO
                                        //
                                        var peripheralName = modInstance[pinmuxReqName].$solution.peripheralName
                                        //console.log(peripheralName)
                                        for (var pinmuxReqInterface of pinmuxReq.resources)
                                        {
                                            var pinmuxReqInterfaceName = pinmuxReqInterface.name
                                            var devicePinName = modInstance[pinmuxReqName][pinmuxReqInterfaceName].$solution.devicePinName
                                            var peripheralPinName = modInstance[pinmuxReqName][pinmuxReqInterfaceName].$solution.peripheralPinName
                                            //console.log(peripheralPinName)
                                            //console.log(devicePinName)

                                            var gpioNames = Pinmux.getGPIOFromDevicePinName(devicePinName)
                                            //console.log(gpioNames)

                                            if (gpioNames.includes(inst.inputxbarGpio))
                                            {
                                                //console.log("Found: " + modInstance.$name + " = " + peripheralPinName)
                                                return (modInstance.$name + " = " + peripheralPinName)
                                            }
                                        }
                                    }
                                    else
                                    {
                                        //
                                        // GPIO
                                        //
                                        var peripheralName = modInstance[pinmuxReqName].$solution.peripheralName
                                        var devicePinName = modInstance[pinmuxReqName].$solution.devicePinName
                                        var peripheralPinName = modInstance[pinmuxReqName].$solution.peripheralPinName
                                        //console.log(peripheralName)
                                        //console.log(peripheralPinName)
                                        //console.log(devicePinName)
                                        if (devicePinName)
                                        {
                                            //
                                            // Normal GPIO, single bonded AGPIO
                                            //
                                            var gpioNames = Pinmux.getGPIOFromDevicePinName(devicePinName)
                                            //console.log(gpioNames)
                                            if (gpioNames.includes(inst.inputxbarGpio))
                                            {
                                                //console.log("Found: " + modInstance.$name + " = " + peripheralPinName)
                                                return (modInstance.$name + " = " + peripheralPinName)
                                            }
                                        }
                                        else
                                        {
                                            //
                                            // Double bonded AGPIO and AIOs
                                            //
                                            if (peripheralName == inst.inputxbarGpio)
                                            {
                                                //console.log("Found: " + modInstance.$name + " = " + peripheralName)
                                                return (modInstance.$name + " = " + peripheralName)
                                            }
                                        }
                                    }
                                }
                                //console.log(pinmuxRequirementsFunc(modInstance))
                            }
                        }
                    }
                    //console.log(system)
                    return "This source is not used by any module"
                }
            },
            {
                name        : "inputxbarLock",
                displayName : "Input Lock",
                description : 'Lock this Input X-Bar',
                hidden      : false,
                default     : false
            }
        ]
    },
    {
        name: "GROUP_ESM",
        displayName: "Error Signaling Configuration",
        collapsed: true,
        config: [
            {
                name        : "configureESM",
                displayName : "Configure Error Signaling",
                description : 'Configure the Error event handling',
                hidden      : true,
                default     : false
            }
        ]
    }
]


function onValidate(inst, validation)
{
    var usedInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedInsts.push(instance_obj.inputxbarInput);
    }
    
    var duplicatesResult = Common.findDuplicates(usedInsts)
    
    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ")
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "This instance is already in use! Duplicates: " + allDuplicates,
            inst, "inputxbarInput");
    }

    validation.logInfo(inst.inputxbarInput + " is connected to " + connectedPeripherals.get(inst.inputxbarInput), inst, "inputxbarInput");
}


function moduleInstances(inst)
{
    let components = []
    if (inst.configureESM)
    {
        components = components.concat([{
            name: "ESMConfig",
            group: "GROUP_ESM",
            displayName: "Error Signaling",
            moduleName : "/driverlib/esm.js",
            collapsed: true,
            args: {
                $name        : inst.$name + "_ESM",
            },
            requiredArgs:{
                eventSource  : "ESM_EVENT_INPUTXBAR" + inst.inputxbarInput.replace("XBAR_INPUT", "")
            },
        }])
    }

    return components;
}

/*
 *  ======== filterHardware ========
 *  Control RX, TX Pin usage by the user specified dataDirection.
 *
 *  param component - hardware object describing signals and
 *                     resources they're attached to
 *
 *  returns Boolean indicating whether or not to allow the component to
 *           be assigned to an instance's $hardware config
 */
function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["INPUTXBAR"]));
}

var inputxbarModule = {
    peripheralName: "INPUTXBAR",
    displayName: "INPUTXBAR INPUT",
    maxInstances: inputXbarCount,
    defaultInstanceName: "myINPUTXBARINPUT",
    description: "Input X-bar",
    longDescription: longDescription,
    filterHardware : filterHardware,
    config: config,
    moduleInstances: moduleInstances,
    validate  :  onValidate,
    templates: {
        boardc : "/driverlib/inputxbar/inputxbar_input.board.c.xdt",
        boardh : "/driverlib/inputxbar/inputxbar_input.board.h.xdt"
    },
    // pinmuxRequirements    : Pinmux.inputxbarPinmuxRequirements
};

if (inputxbarModule.maxInstances <= 0)
{
    delete inputxbarModule.pinmuxRequirements;
}


exports = inputxbarModule;
