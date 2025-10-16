let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_gpio.js");


var xint_inputxbar_map = {
    "GPIO_INT_XINT1" : "XBAR_INPUT4",
    "GPIO_INT_XINT2" : "XBAR_INPUT5",
    "GPIO_INT_XINT3" : "XBAR_INPUT6",
    "GPIO_INT_XINT4" : "XBAR_INPUT13",
    "GPIO_INT_XINT5" : "XBAR_INPUT14",
}
//console.log(system.deviceData)

function onChangeAnalogMode(inst, ui)
{
    if (inst.analogMode == "GPIO_ANALOG_DISABLED")
    {
        ui.direction.hidden = false;
        ui.padConfig.hidden = false;
        ui.controllerCore.hidden = false;
        ui.qualMode.hidden = false;
    }
    else
    {
        ui.direction.hidden = true;
        ui.padConfig.hidden = true;
        ui.controllerCore.hidden = true;
        ui.qualMode.hidden = true;
    }

}
/* Intro splash on GUI */
let longDescription = "The GPIO module allows you to manage General Purpose I/O"
        + " resources via simple and portable APIs. GPIO pin behavior is"
        + " usually configured statically, but can also be configured or"
        + " reconfigured at runtime.";

function onChangeContext(inst)
{
    inst.controllerCore = "GPIO_CORE_" + inst.$assignedContext;
}

/* Array of SCI configurables that are common across device families */
let config = [
    {
        name        : "$assignedContext",
        hidden      : false,
        default     : "CPU1",
        options     : [{name:"CPU1"}, {name:"CPU2"}, {name:"CPU3"}],
        onChange    : onChangeContext,
    },
    {
        name        : "analogMode",
        displayName : "Analog Mode",
        description : 'Whether pin is in analog mode or not.',
        readOnly    : true,
        hidden      : false,
        onChange    : onChangeAnalogMode,
        default     : device_driverlib_peripheral.GPIO_AnalogMode[0].name,
        options     : device_driverlib_peripheral.GPIO_AnalogMode,
        shouldBeAllocatedAsResource: true,
    },

    {
        name        : "direction",
        displayName : "GPIO Direction",
        description : 'Whether pin is input or output.',
        hidden      : false,
        default     : device_driverlib_peripheral.GPIO_Direction[0].name,
        options     : device_driverlib_peripheral.GPIO_Direction
    },

    {
        name        : "padConfig",
        displayName : "Pin Type",
        description : 'Type of pin is driving the gpio.',
        hidden      : false,
        default     : 'STD',
        options     : [
            { name: "STD", displayName : "Push-pull output/floating input" },
            { name: "PULLUP", displayName : "Push-pull output/pull-up enabled on input"  },
            { name: "INVERT", displayName : "Push-pull output/floating INVERTED polarity on an input"  },
            { name: "PULLUP_INVERT", displayName : "Push-pull output/pull-up enabled on INVERTED input"  },
            { name: "OD", displayName : "Open-drain output/floating input" },
            { name: "OD_PULLUP", displayName : "Open-drain output with pull-up enabled output and input" },
            { name: "OD_INVERT", displayName : "Open-drain output/floating inverted input" },
            { name: "OD_PULLUP_INVERT", displayName : "Open-drain output with pull-up enabled output and INVERTED input" }
        ],
        shouldBeAllocatedAsResource: true,
    },

    {
        name        : "qualMode",
        displayName : "Qualification Mode",
        description : 'The type of qualification done on the pin.',
        hidden      : false,
        default     : device_driverlib_peripheral.GPIO_QualificationMode[0].name,
        options     : device_driverlib_peripheral.GPIO_QualificationMode,
        shouldBeAllocatedAsResource: true,
    },

    {
        name        : "GROUP_XINT",
        displayName : "External Interrupts",
        description : 'Connect to an XINT for interrupts',
        config     : [
            {
                name        : "useInterrupt",
                displayName : "Use Interrupts",
                description : 'Connect to an XINT for interrupts',
                hidden      : false,
                default     : false,
                shouldBeAllocatedAsResource: true,
            },
        ]
    },
];
function coreselec(){
    let opt = [];
    for(let i in device_driverlib_peripheral.GPIO_CoreSelect){
        let temp=(device_driverlib_peripheral.GPIO_CoreSelect[i].name).replace("GPIO_CORE_","")
        if(Common.is_instance_not_in_variant(temp))continue;
        else{
            opt.push({ name: device_driverlib_peripheral.GPIO_CoreSelect[i].name, displayName: device_driverlib_peripheral.GPIO_CoreSelect[i].displayName });
        }

    }
    return opt;
}
{
    var coreSelectConfig = {
        name        : "controllerCore",
        legacyNames : ["masterCore"],
        displayName : "Core Select",
        description : 'Who owns the GPIO.',
        hidden      : false,
        default     : device_driverlib_peripheral.GPIO_CoreSelect[0].name,
        options     : coreselec(),
        shouldBeAllocatedAsResource: true
    };
    config.push(coreSelectConfig)
}

config = config.concat([
    {
        name        : "writeInitialValue",
        displayName : "Write Initial Value",
        description : "Determines whether or not to write an initial value for the GPIO output",
        default     : false,
        onChange    : (inst, ui) => {
            ui.initialValue.hidden = !inst.writeInitialValue;
        }
    },
    {
        name        : "initialValue",
        displayName : "Initial Value",
        description : "Determines whether or not to write an initial value for the GPIO output",
        hidden      : true,
        default     : 0,
        options     : [
            { name: 0, displayName: "0: GPIO state is LOW"},
            { name: 1, displayName: "1: GPIO state is HIGH"}
        ]
    }
])

//TODO: What is this if condition?
var pinMuxReq = Pinmux.gpioPinmuxRequirements;
// if (["F280013x","F280015x"].includes(Common.getDeviceName())){
//     if (!["64PM","64VPM","80PN"].includes(Common.getDevicePackage()))
//     pinMuxReq = Pinmux.gpioWithPeripheralPinmuxRequirements;
// }

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
    return (Common.typeMatches(component.type, ["GPIO"]));
}


function moduleInstances(inst)
{
    var ownedMods = []

    let reqArgs = {}
    if(Common.isAllocationSetupMode())
    {
        reqArgs = {
            $assignedContext: inst.$assignedContext,
            $name : inst.$name + "_XINT",
        }
    }
    else
    {
        reqArgs = {
            $name : inst.$name + "_XINT",
        }
    }

    if (inst.useInterrupt)
    {
        //GROUP_XINT
        ownedMods.push({
            name: "xint",      
            displayName: "XINT",
            moduleName: "/driverlib/xint.js",
            collapsed: true,
            group: "GROUP_XINT",
            requiredArgs: reqArgs,
            shouldBeAllocatedAsResource: true,
        })
    }
    return ownedMods
}

function onValidatePinmux(inst, validation) {
    if (inst.useInterrupt){
        var xint = inst.xint;
        var xintNum = xint.xintNum;
        var inputxbar = xint.inputxbar;

        if (inst.gpioPin.$solution)
        {
            var selectedGPIOPeripheral = inst.gpioPin.$solution.peripheralPinName;
            if (!selectedGPIOPeripheral)
            {
                selectedGPIOPeripheral = inst.gpioPin.$solution.peripheralName
            }
            if (selectedGPIOPeripheral != inputxbar["inputxbarGpio"])
            {
                validation.logWarning(
                    "Select " + selectedGPIOPeripheral + " which is the selection in your GPIO PinMux entry.", 
                    inputxbar, "inputxbarGpio");
            }
        }
        else
        {
            validation.logInfo(
                "Select " + "the same GPIO" + " as the one in your GPIO PinMux entry.", 
                inputxbar, "inputxbarGpio");
        }
    }
}

if (Common.onlyPinmux())
{
    config = [];
}
var gpioModule = {
    peripheralName: "GPIO",
    displayName: "GPIO",
    totalMaxInstances: Common.peripheralCount("GPIO"),
    defaultInstanceName: "myGPIO",
    description: "General Purpose IO Interface Peripheral",
    //longDescription: (Common.getCollateralFindabilityList("GPIO")),
    filterHardware : filterHardware,
    moduleInstances: moduleInstances,
    shouldBeAllocatedAsResource: true,
    config: Common.filterConfigsIfInSetupMode(config),
    templates: {
        boardc : "/driverlib/gpio/gpio.board.c.xdt",
        boardh : "/driverlib/gpio/gpio.board.h.xdt"
    },
    pinmuxRequirements    : pinMuxReq,
    validatePinmux: onValidatePinmux
};


if (gpioModule.maxInstances <= 0)
{
    delete gpioModule.pinmuxRequirements;
}


exports = gpioModule;
