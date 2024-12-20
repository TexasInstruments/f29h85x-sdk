let Common   = system.getScript("/driverlib/Common.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_sysctl.js");

/* Intro splash on GUI */
let longDescription = "";


var standbyOptions = []
for (var prd = 0; prd <= 63; prd++)
{
    standbyOptions.push({
        name: prd + 2,
        displayName: (prd + 2).toString() + " OSCCLKs"
    })
}

/* Array of Clock configurables */
let config = [
    {
        name        : "LSConfig_group",
        displayName : "LockStep/SplitLock Configuration",
        collapsed   : false,
        config      : [
            {
                name: "LSConfig",
                displayName: "CPU1-CPU2 Configuration",
                hidden  : !Common.isContextCPU1(),
                default : "LockStep",
                options : [
                    {name:"LockStep"},
                    {name:"SplitLock"}
                ]
            },
        ]
    },
    {
        name        : "XRSnConfig",
        displayName : "XRSn Configuration",
        collapsed   : false,
        config      : [
            {
                name        : "ESM_CPU1CRITICAL",
                displayName : "Enable XRSn on CPU1 ESM Critical Priority Event",
                hidden      : !Common.isContextCPU1(),
                default     : true,
            },
            {
                name        : "ESM_CPU1HIPRIWD",
                displayName : "Enable XRSn on CPU1 ESM NMI Watchdog Event",
                hidden      : !Common.isContextCPU1(),
                default     : true,
                readOnly    : true
            },
            {
                name        : "ESM_CPU2CRITICAL",
                displayName : "Enable XRSn on CPU2 ESM Critical Priority Event",
                hidden      : !Common.isContextCPU1(),
                default     : false,
            },
            {
                name        : "ESM_CPU2HIPRIWD",
                displayName : "Enable XRSn on CPU2 ESM NMI Watchdog Event",
                hidden      : !Common.isContextCPU1(),
                default     : false,
            },
            {
                name        : "ESM_CPU3CRITICAL",
                displayName : "Enable XRSn on CPU3 ESM Critical Priority Event",
                hidden      : !Common.isContextCPU1(),
                default     : false,
            },
            {
                name        : "ESM_CPU3HIPRIWD",
                displayName : "Enable XRSn on CPU3 ESM NMI Watchdog Event",
                hidden      : !Common.isContextCPU1(),
                default     : false,
            },
            {
                name        : "ESM_RESET",
                displayName : "Enable XRSn on ESM.SYS Critical Priority Event",
                hidden      : !Common.isContextCPU1(),
                default     : false,
            },
        ]
    },
    {
        name        : "LPMConfig",
        displayName : "LPM Configuration",
        collapsed   : false,
        config      : [
            {
                name: "lpmWakeUpPin",
                displayName: "LPM Wake Up Pin",
                hidden      : !Common.isContextCPU1(),
                default : [],
                minSelections : 0,
                options : device_driverlib_peripheral.SysCtl_LPMWakeupPin,
            },
            {
                name: "standbyQualificationPeriod",
                displayName: "Standby Qualification Period",
                hidden      : !Common.isContextCPU1(),
                options : standbyOptions,
                default: standbyOptions[0].name
            }
        ]
    },
    {
        name        : "interrupt",
        displayName : "Interrupt Configuration",
        collapsed   : false,
        config      : [
            {
                name        : "registerWakeupInterrupt",
                displayName : "Register LPM Wakeup Interrupt in PIPE",
                description : 'Whether or not to register LPM wakeup interrupt in the PIPE module.',
                hidden      : false,
                default     : false
            },
        ]
    },
    {
        name        : "GROUP_ESM",
        displayName : "Error Signaling Configuration",
        collapsed   : false,
        config      : [
            {
                name        : "clockFail",
                displayName : "Enable CLOCKFAIL Signal",
                description : 'Enable CLOCKFAIL to ESM',
                default     : false
            },
            {
                name        : "pllSlip",
                displayName : "Enable PLLSLIP Signal",
                description : 'Enable PLLSLIP to ESM',
                default     : false
            },
        ]
    },
];

function moduleInstances(inst)
{
    let components = []
    if (inst.registerWakeupInterrupt)
    {
        var interruptName = "LPM_WAKE";
        components.push({
            name: "wakeupInt",
            displayName: "LPM Wakeup Interrupt",
            moduleName: "/driverlib/interrupt.js",
            collapsed: false,
            group : "interrupt",
            args: {
                $name : interruptName + "_INT",
                typeInterruptName : true,
                pinmuxPeripheralModule : "",
                driverlibInt: "INT_" + interruptName,
                interruptHandler : "INT_" + interruptName + "_ISR",
            }
        })
    }

    if (inst.clockFail)
    {
        components = components.concat([{
            name        : "ESMConfig_clockfail",
            group       : "GROUP_ESM",
            displayName : "CLOCKFAIL",
            moduleName  : "/driverlib/esm.js",
            collapsed   : true,
            args        : {
                $name        : "CLOCKFAIL_ESM",
                eventSource  : "ESM_EVENT_CLOCKFAIL"
            },
        }])
    }
    if (inst.pllSlip)
    {
        components = components.concat([{
            name        : "ESMConfig_pllSlip",
            group       : "GROUP_ESM",
            displayName : "PLLSLIP",
            moduleName  : "/driverlib/esm.js",
            collapsed   : true,
            args        : {
                $name        : "PLLSLIP_ESM",
                eventSource  : "ESM_EVENT_SYS_PLL_SLIP"
            },
        }])
    }
    return components;
}

function onValidate(inst, validation) 
{

    
}


function filterHardware(component)
{
}

var clockModule = {
    peripheralName: "SYSCTL",
    displayName: "SYSCTL",
    maxInstances: 1,
    description: "SYSCTL",
    filterHardware : filterHardware,
    templates: {
        boardc : "/driverlib/sysctl/sysctl.board.c.xdt",
        boardh : "/driverlib/sysctl/sysctl.board.h.xdt"
    },
    moduleStatic : {
        config: config,
        validate    : onValidate,
        moduleInstances : moduleInstances,
    },

};




exports = clockModule;