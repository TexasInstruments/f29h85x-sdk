let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

var numberOfBusCompInstance = {
    "F29H85x"   : 8
}
var numberOfCounterInstance = {
    "F29H85x"   : 4
}
var numberOfANDMaskInstance = {
    "F29H85x"   : 4
}
var numberOfORMaskInstance = {
    "F29H85x"   : 4
}

let config = [
    {
        name: "GROUP_PERCFG",
        displayName: "Peripheral Configuration",
        collapsed: false,
        config: []
    },
    {
        name: "GROUP_INTERRUPT",
        displayName: "Interrupt Configuration",
        collapsed: true,
        config: [
            {
                name        : "registerInterrupts",
                displayName : "Register Interrupt Handler",
                description : 'Whether or not to register interrupt handlers in the interrupt module.',
                hidden      : false,
                default     : false,
            },
        ]
    },
    {
        name: "GROUP_ESM",
        displayName: "Error Signaling Configuration",
        collapsed: true,
        config: [
            {
                name        : "configureESMforERADINT",
                displayName : "Configure Error Signaling for ERAD Interrupt",
                description : 'Configure the handling of ERAD Interrupt',
                hidden      : false,
                default     : false
            },
            {
                name        : "configureESMforERADNMI",
                displayName : "Configure Error Signaling for ERAD NMI",
                description : 'Configure the handling of ERAD NMI',
                hidden      : false,
                default     : false
            }
        ]
    },
    {
        name: "GROUP_SYS",
        displayName: "System Configuration",
        collapsed: true,
        config: []
    },
];

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["ERAD"]));
}

function moduleInstances(inst)
{
    let components = new Array();

    components.push(
        {
            name: "periphClock",
            group: "GROUP_SYS",
            displayName: "",
            moduleName: "/driverlib/perClock.js",
            collapsed: false,
            requiredArgs:{
                pinmuxPeripheralModule : "",
                peripheralInst: "CPUXERAD"
            }
        }
    )
    if (inst.registerInterrupts)
    {
        var interruptName = "ERAD"
        components.push(
            {
                name: "eradInt",
                group: "GROUP_INTERRUPT",  
                displayName: "ERAD Interrupt",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
                    $name : interruptName + "_INT",
                    typeInterruptName : true,
                    pinmuxPeripheralModule : "",
                    driverlibInt: "INT_" + interruptName,
                    interruptHandler : "INT_my" + interruptName + "_ISR",
                }   
            }
        )
    }
    if (inst.configureESMforERADINT)
    {
        components.push(
            {
                name: "ESMConfigINT",
                group: "GROUP_ESM",
                displayName: "Error Signaling for ERAD Interrupt",
                moduleName : "/driverlib/esm.js",
                collapsed: true,
                args: {
                    $name: system.context + "_ERAD_INT_ESM",
                },
                requiredArgs: {
                    eventSource: "ESM_EVENT_" + system.context + "_ERAD_INT"
                },
            }
        )
    }
    if (inst.configureESMforERADNMI)
    {
        components.push(
            {
                name: "ESMConfigNMI",
                group: "GROUP_ESM",
                displayName: "Error Signaling for ERAD NMI",
                moduleName : "/driverlib/esm.js",
                collapsed: true,
                args: {
                    $name: system.context + "_ERAD_NMI_ESM",
                },
                requiredArgs: {
                    eventSource: "ESM_EVENT_" + system.context + "_ERAD_NMI"
                },
            }
        )
    }
    components.push(
        {
            name: "erad_buscomp",
            group: "GROUP_PERCFG",
            displayName: "ERAD BUSCOMP",
            moduleName: "/driverlib/erad/modules/erad_buscomp.js",
            description:"ERAD Enhanced Bus Comparator (EBC)",
            useArray: true,
            collapsed: false,
            maxInstanceCount: numberOfBusCompInstance[Common.getDeviceName()],
        }
    )

    components.push(
        {
            name: "erad_counter",
            group: "GROUP_PERCFG",
            displayName: "ERAD COUNTER",
            moduleName: "/driverlib/erad/modules/erad_counter.js",
            description:"ERAD System Event Counter (SEC)",
            useArray: true,
            collapsed: false,
            maxInstanceCount: numberOfCounterInstance[Common.getDeviceName()],
        }
    )

    components.push(
        {
            name: "erad_and_mask",
            group: "GROUP_PERCFG",
            displayName: "ERAD AND MASK",
            moduleName: "/driverlib/erad/modules/erad_and_mask.js",
            description:"ERAD AND MASK",
            useArray: true,
            collapsed: false,
            maxInstanceCount: numberOfANDMaskInstance[Common.getDeviceName()],
        }
    )
    
    components.push(
        {
            name: "erad_or_mask",
            group: "GROUP_PERCFG",
            displayName: "ERAD OR MASK",
            moduleName: "/driverlib/erad/modules/erad_or_mask.js",
            description:"ERAD OR MASK",
            useArray: true,
            collapsed: false,
            maxInstanceCount: numberOfORMaskInstance[Common.getDeviceName()],
        }
    )

    return components;
}

var eradModule = {
    peripheralName: "ERAD",
    displayName: "ERAD",
    defaultInstanceName: "myERAD",
    description: "Embedded Real-Time Analysis And Diagnostic",
    // longDescription: (Common.getCollateralFindabilityList("ERAD")),
    filterHardware : filterHardware,
    moduleStatic          : {
        config          : config,
        moduleInstances : moduleInstances,
    },
    templates: {
        boardc : "/driverlib/erad/erad.board.c.xdt",
        boardh : "/driverlib/erad/erad.board.h.xdt"
    },
};


exports = eradModule;