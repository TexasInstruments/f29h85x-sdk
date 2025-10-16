let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_xbar.js");

let xbar_shared =
    system.getScript("/driverlib/xbarShared.js");

var globalConfig = _.clone(xbar_shared.globalConfig)  

var noPrefixOptions = device_driverlib_peripheral.XBAR_EpwmXbarInputSource.map(element => {
    var elementName = element.name.replace(/XBAR_EPWM_/g, "")
    return { name: elementName, displayName: element.displayName}
});

var config = [
    {
        name: "GROUP_PERCFG",
        displayName: "Peripheral Configuration",
        collapsed: false,
        config: [
            {
                name        : "tripInput",
                displayName : "Trip Input",
                description : 'Which Trip input is configured to be sourced from the muxes.',
                hidden      : false,
                default     : device_driverlib_peripheral.XBAR_TripNum[0].name,
                options     : device_driverlib_peripheral.XBAR_TripNum,
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

config[0].config = config[0].config.concat(xbar_shared.getXbarConfig("EPWMXBAR"))

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
    var usedTrips = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedTrips.push(instance_obj.tripInput);
    }

    var duplicatesResult = Common.findDuplicates(usedTrips)
    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ") 
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The Trip Inputs cannot be same for multiple modules. Duplicates: " + allDuplicates, 
            inst, "tripInput");
    }

    if (inst.tripInput == "XBAR_TRIP1")
    {
        validation.logWarning("TRIP1 instance is used for a workaround (Refer Device_errataWorkaroundNMIVectorFetch()). Select a different Trip input.", inst, "tripInput");
    }

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
                eventSource  : "ESM_EVENT_EPWMXBAR" + inst.tripInput.replace("XBAR_TRIP", "")
            },
        }])
    }

    return components;
}

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["EPWMXBAR"]));
}
  

var epwmxbarModule = {
    peripheralName        : "EPWMXBAR",
    displayName           : "EPWM XBAR",
    maxInstances          : 16, //Common.peripheralCount("EPWMXBAR"), 
    defaultInstanceName   : "myEPWMXBAR",
    description           : "EPWM X-BAR",
    filterHardware        : filterHardware,
    config                : Common.filterConfigsIfInSetupMode(config),
    moduleInstances       : moduleInstances,
    templates             : {
        boardc : "/driverlib/epwmxbar/epwmxbar.board.c.xdt",
        boardh : "/driverlib/epwmxbar/epwmxbar.board.h.xdt"
    },
    validate              : onValidate,
    moduleStatic: {
        name: "epwmXbarGlobal",
        displayName: "EPWMXBAR Global",
        config: globalConfig,
        shouldBeAllocatedAsResource : true,
    },
    shouldBeAllocatedAsResource : true,
    alwaysAllocateAsResource : true,
};


exports = epwmxbarModule;