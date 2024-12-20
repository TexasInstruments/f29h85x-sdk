let Common  = system.getScript("/driverlib/Common.js");
let Pinmux  = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_esm.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

/* Intro splash on GUI */
// longDescription += "*   [Device TRM](" + Common.getDeviceTRM() + ")";

function onChangeTypeEventSource(inst, ui)
{
    if(inst.typeEventSource)
    {
        ui.eventSourceTyped.hidden = false
        ui.eventSource.hidden  = true
    }
    else
    {
        ui.eventSourceTyped.hidden = true
        ui.eventSource.hidden  = false
    }
}

let config = [
    {
        name        : "eventSource",
        displayName : "Event Source",
        description : 'The error event source name in driverlib',
        hidden      : false,
        readOnly    : false,
        default     : '',
    },
    {
        name        : "typeEventSource",
        displayName : "Type the Event Source Name",
        description : "Enable to type the error event name or else drop down is provided.",
        hidden      : true,
        default     : false,
        onChange    : onChangeTypeEventSource,
    },
    {
        name        : "eventSourceTyped",
        displayName : "Event Source",
        description : 'The error event source name.',
        hidden      : true,
        readOnly    : false,
        default     : '',
    },
    {
        name        : "inSysEsm",
        displayName : "Configure event in SYSTEM ESM",
        description : 'Configure the error event in SYSTEM ESM',
        default     : false,
    },
]
if (Common.isContextCPU1())
{
    config = config.concat([
        {
            name        : "inCpu1Esm",
            displayName : "Configure event in CPU1",
            description : 'Configure the error event in CPU1',
            default     : false,
        },
    ])
}
if (Common.isContextCPU2())
{
    config = config.concat([
        {
            name        : "inCpu2Esm",
            displayName : "Configure event in CPU2",
            description : 'Configure the error event in CPU2',
            default     : false,
        },
    ])
}
if (Common.isContextCPU3())
{ 
    config = config.concat([
        {
            name        : "inCpu3Esm",
            displayName : "Configure event in CPU3",
            description : 'Configure the error event in CPU3',
            default     : false,
        },
    ])
}

var sharedModuleInstances = undefined;

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["ESM"]));
}

function moduleInstances(inst)
{
    let submodules = []
    if(inst.typeEventSource)
    {
        var reqArgs = {
            typeEventSource  : inst.typeEventSource,
            eventSourceTyped : inst.eventSourceTyped,
        }
    }
    else
    {
        var reqArgs = {
            eventSource      : inst.eventSource
        }
    }

    if (inst.inSysEsm)
    {
        submodules = submodules.concat([{
            name: "esmSys",
            displayName: "SYSTEM ESM",
            moduleName: "/driverlib/esm_system.js",
            collapsed: true,
            args: {
                $name       : inst.$name + "SYSTEM",
            },
            requiredArgs: reqArgs
        }])
    }
    if (Common.isContextCPU1())
    {
        if (inst.inCpu1Esm)
        {
            submodules = submodules.concat([{
                name: "esm" + system.context,
                displayName: system.context + " ESM",
                moduleName: "/driverlib/esm_cpu.js",
                collapsed: true,
                args: {
                    $name       : inst.$name + system.context,
                },
                requiredArgs: reqArgs
            }])
        }
    }
    if (Common.isContextCPU2()) 
    {
        if (inst.inCpu2Esm)
        {
            submodules = submodules.concat([{
                name: "esm" + system.context,
                displayName: system.context + " ESM",
                moduleName: "/driverlib/esm_cpu.js",
                collapsed: true,
                args: {
                    $name       : inst.$name + system.context,
                },
                requiredArgs: reqArgs
            }])
        }
    }
    if (Common.isContextCPU3()) 
    {
        if (inst.inCpu3Esm)
        {
            submodules = submodules.concat([{
                name: "esm" + system.context,
                displayName: system.context + " ESM",
                moduleName: "/driverlib/esm_cpu.js",
                collapsed: true,
                args: {
                    $name       : inst.$name + system.context,
                },
                requiredArgs: reqArgs
            }])
        }
    }

    return submodules;
}


var ESMModule = {
    peripheralName: "ESM",
    displayName: "ERROR SIGNALING",
    defaultInstanceName: "myErrorSignaling",
    description: "Error Signaling module configuration",
    // longDescription : longDescription,
    filterHardware: filterHardware,
    config          : config,
    moduleInstances : moduleInstances,
    sharedModuleInstances : sharedModuleInstances,
};


exports = ESMModule;