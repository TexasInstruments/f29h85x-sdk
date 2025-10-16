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

/* Intro splash on GUI */
let longDescription = "The external interrupt module (XINT).";

/* Array of configurables that are common across device families */
let config = [
    {
        name: "xintNum",
        displayName: "XINT Instance",
        options: device_driverlib_peripheral.GPIO_ExternalIntNum,
        default: device_driverlib_peripheral.GPIO_ExternalIntNum[0].name,
        shouldBeAllocatedAsResource: true,
    },
    {
        name: "intType",
        displayName: "Interrupt Edge",
        options: device_driverlib_peripheral.GPIO_IntType,
        default: device_driverlib_peripheral.GPIO_IntType[0].name
    },
    {
        name: "enableInt",
        displayName: "Enable Interrupt",
        default: false,
    },
    {
        name: "registerInterrupts",
        displayName: "Register Interrupt Handler",
        default: false,
    }
];

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
    return (Common.typeMatches(component.type, ["XINT"]));
}

function sharedModuleInstances(inst)
{
    var sharedMods = []
    let requiredArgs = {}
    if(Common.isAllocationSetupMode())
    {
        requiredArgs = {
            $assignedContext: "CPU1",
            inputxbarInput : xint_inputxbar_map[inst.xintNum],
        }
    }
    else
    {
        requiredArgs = {
            inputxbarInput : xint_inputxbar_map[inst.xintNum],
        }
    }

    //GROUP_XINT
    sharedMods.push({
        name: "inputxbar",      
        displayName: "INPUTXBAR",
        moduleName: "/driverlib/inputxbar_input.js",
        collapsed: true,
        requiredArgs : requiredArgs,
        shouldBeAllocatedAsResource: true,
    })
    return sharedMods
}

function moduleInstances(inst)
{
    var mods = []

    if (inst.registerInterrupts)
    {
        mods.push({
            name: "xInt",      
            displayName: "XINT PIPE Interrupt Configuration",
            moduleName: "/driverlib/interrupt.js",
            collapsed: true,
            args: {
                $name : inst.$name + "_INT",
                typeInterruptName : true,
                pinmuxPeripheralModule : "",
                driverlibInt: "INT_" + inst.xintNum.replace("GPIO_INT_", ""),
                interruptHandler : "INT_" + inst.$name + "_ISR",
            }
        })
    }
    
    return mods
}

function onValidate(inst, validation)
{
    var baseName = "xintNum"
    var usedInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedInsts.push(instance_obj[baseName]);
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
            "The module instance used is duplicated and it must be unique. Duplicates: " + allDuplicates, 
            inst, baseName);
    }
}

if (Common.onlyPinmux())
{
    config = [];
}

var xintModule = {
    peripheralName: "XINT",
    displayName: "XINT",
    maxInstances: device_driverlib_peripheral.GPIO_ExternalIntNum.length,
    defaultInstanceName: "myXINT",
    sharedModuleInstances: sharedModuleInstances,
    moduleInstances: moduleInstances,
    description: "External Interrupt (XINT)",
    longDescription: longDescription,
    filterHardware : filterHardware,
    validate: onValidate,
    config: Common.filterConfigsIfInSetupMode(config),
    templates: {
        boardc : "/driverlib/gpio/xint.board.c.xdt",
        boardh : "/driverlib/gpio/xint.board.h.xdt"
    },
    shouldBeAllocatedAsResource: true,
};


exports = xintModule;