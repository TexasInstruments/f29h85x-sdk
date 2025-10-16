let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_xbar.js");

let xbar_shared =
    system.getScript("/driverlib/xbarShared.js");

var globalConfig = _.clone(xbar_shared.globalConfig)

var noPrefixOptions = device_driverlib_peripheral.XBAR_OutputXbarInputSource.map(element => {
    var elementName = element.name.replace(/XBAR_OUT_/g, "")
    return { name: elementName, displayName: element.displayName}
});

var config = [
    {
        name: "GROUP_PERCFG",
        displayName: "Peripheral Configuration",
        collapsed: false,
        config: [
            {
                name         : "sourceSignals",
                displayName  : "Input Source Signals",
                default      : [],
                minSelections: 0,
                options      : noPrefixOptions,
                description  : "This determines the output of the xbar",
                shouldBeAllocatedAsResource : true,
            }]
    }
];

config[0].config = config[0].config.concat(xbar_shared.getXbarConfig("OUTPUTXBAR"))

config.push(
    {
        name: "GROUP_ESM",
        displayName: "Error Signaling Configuration",
        collapsed: true,
        config: [ 
            {
                name        : "configureESM",
                displayName : "Configure Error Signaling",
                description : 'Configure the Error event handling',
                hidden      : false,
                default     : false
            } 
        ]
    }
)

function onValidate(inst, validation) {
    // If no instance is selected
    if(inst["sourceSignals"].length == 0)
    {
        validation.logError("Please select atleast one input for this Xbar", inst, "sourceSignals");
    }
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
                typeEventSource   : true,
                eventSourceTyped  : "ESM_EVENT_" + inst.$name
            },
        }])
    }

    return components;
}

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["OUTPUTXBAR"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}    

var outputxbarModule = {
    peripheralName        : "OUTPUTXBAR",
    displayName           : "OUTPUT XBAR",
    maxInstances          : Common.peripheralCount("OUTPUTXBAR"), 
    defaultInstanceName   : "myOUTPUTXBAR",
    description           : "Output X-bar",
    filterHardware        : filterHardware,
    config                : Common.filterConfigsIfInSetupMode(config),
    moduleInstances       : moduleInstances,
    templates             : {
        boardc : "/driverlib/outputxbar/outputxbar.board.c.xdt",
        boardh : "/driverlib/outputxbar/outputxbar.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.outputxbarPinmuxRequirements,
    validate: onValidate,
    moduleStatic: {
        name: "outputXbarGlobal",
        displayName: "OUTPUTXBAR Global",
        config: globalConfig,
        shouldBeAllocatedAsResource : true,
    },
    shouldBeAllocatedAsResource : true,
    alwaysAllocateAsResource : true,
};

if (outputxbarModule.maxInstances <= 0)
{
    delete outputxbarModule.pinmuxRequirements;
}

exports = outputxbarModule;