let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_xbar.js");

let xbar_shared =
    system.getScript("/driverlib/xbarShared.js");

var globalConfig = _.clone(xbar_shared.globalConfig)

var noPrefixOptions = device_driverlib_peripheral.XBAR_IclXbarInputSource.map(element => {
    var elementName = element.name.replace(/XBAR_ICL_/g, "")
    return { name: elementName, displayName: element.displayName}
});

var config = [
    {
        name: "GROUP_PERCFG",
        displayName: "Peripheral Configuration",
        collapsed: false,
        config: [
            {
                name        : "xbarOutput",
                displayName : "XBAR Output",
                description : 'Which XBAR output is configured to be sourced from the inputs.',
                hidden      : false,
                default     : device_driverlib_peripheral.XBAR_OutputNum[0].name,
                options     : device_driverlib_peripheral.XBAR_OutputNum,
                shouldBeAllocatedAsResource : true,
            },
            {
                name         : "sourceSignals",
                displayName  : "Input Source Signals",
                default      : [],
                minSelections: 0,
                options      : noPrefixOptions,
                description  : "This determines the output of the xbar",
                shouldBeAllocatedAsResource : true,
            }
        ]
    }
]

config[0].config = config[0].config.concat(xbar_shared.getXbarConfig("ICLXBAR"))


function onValidate(inst, validation) {
    var  usedInstances = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
         usedInstances.push(instance_obj.xbarOutput);
    }

    var duplicatesResult = Common.findDuplicates( usedInstances)
    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ") 
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The XBAR Instance cannot be same for multiple modules. Duplicates: " + allDuplicates, 
            inst, "xbarOutput");
    }

    if(inst["sourceSignals"].length == 0)
    {
        validation.logError("Please select atleast one input for this Xbar", inst, "sourceSignals");
    }
}

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["ICLXBAR"]));
}
 

var iclxbarModule = {
    peripheralName        : "ICLXBAR",
    displayName           : "ICL XBAR",
    maxInstances          : 16, //Common.peripheralCount("ICLXBAR"), 
    defaultInstanceName   : "myICLXBAR",
    description           : "ICL X-BAR",
    filterHardware        : filterHardware,
    config                : config,
    templates             : {
        boardc : "/driverlib/iclxbar/iclxbar.board.c.xdt",
        boardh : "/driverlib/iclxbar/iclxbar.board.h.xdt"
    },
    validate              : onValidate,
    moduleStatic: {
        name: "iclXbarGlobal",
        displayName: "ICLXBAR Global",
        config: globalConfig,
        shouldBeAllocatedAsResource : true,
    },
    shouldBeAllocatedAsResource : true,
    alwaysAllocateAsResource : true,
};


exports = iclxbarModule;