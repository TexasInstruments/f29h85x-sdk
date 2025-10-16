let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_xbar.js");

let xbar_shared =
    system.getScript("/driverlib/xbarShared.js");

var globalConfig = _.clone(xbar_shared.globalConfig)   
   
var noPrefixOptions = device_driverlib_peripheral.XBAR_ClbXbarInputSource.map(element => {
    var elementName = element.name.replace(/XBAR_CLB_/g, "")
    return { name: elementName, displayName: element.displayName}
});

var config = [    
    {
        name: "GROUP_PERCFG",
        displayName: "Peripheral Configuration",
        collapsed: false,
        config: [
            {
                name        : "auxInput",
                displayName : "Aux Signal Input",
                description : 'Which Aux Signal is configured to be sourced from the inputs.',
                hidden      : false,
                default     : device_driverlib_peripheral.XBAR_AuxSigNum[0].name,
                options     : device_driverlib_peripheral.XBAR_AuxSigNum,
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

config[0].config = config[0].config.concat(xbar_shared.getXbarConfig("CLBXBAR"))


function onValidate(inst, validation) {
    var  usedInstances = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
         usedInstances.push(instance_obj.auxInput);
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
            "The Aux Signal input cannot be same for multiple modules. Duplicates: " + allDuplicates, 
            inst, "auxInput");
    }

    if(inst["sourceSignals"].length == 0)
    {
        validation.logError("Please select atleast one input for this Xbar", inst, "sourceSignals");
    }
}

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["CLBXBAR"]));
}


var clbxbarModule = {
    peripheralName        : "CLBXBAR",
    displayName           : "CLB XBAR",
    maxInstances          : 8, //Common.peripheralCount("CLBXBAR"), 
    defaultInstanceName   : "myCLBXBAR",
    description           : "CLB X-BAR",
    filterHardware        : filterHardware,
    config                : config,
    templates             : {
        boardc : "/driverlib/clbxbar/clbxbar.board.c.xdt",
        boardh : "/driverlib/clbxbar/clbxbar.board.h.xdt"
    },
    validate              : onValidate,
    moduleStatic: {
        name: "clbXbarGlobal",
        displayName: "CLBXBAR Global",
        config: globalConfig,
        shouldBeAllocatedAsResource : true,
    },
    shouldBeAllocatedAsResource : true,
    alwaysAllocateAsResource : true,
};


exports = clbxbarModule;