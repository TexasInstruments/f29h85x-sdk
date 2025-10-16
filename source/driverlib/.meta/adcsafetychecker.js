let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_adc.js");
let device_driverlib_memmap =
system.getScript("/driverlib/device_driverlib_peripherals/" +
    Common.getDeviceName().toLowerCase() + "_memmap.js");

//var numberOfBusCompInstance = {
//    "F29H85x"   : 8
//}
var CPU1 = Common.isContextCPU1()
var CPU2 = Common.isContextCPU2()
var CPU3 = Common.isContextCPU3()
var CPU = ""

if(!CPU1 && !CPU2)
{
    CPU = "3"
}
else if(!CPU2 && !CPU3)
{
    CPU = "1"
}
else
{
    CPU = "2"
}
let config = [
    {
        name: "GROUP_SAFECHECKCFG",
        displayName: "ADC Safety Checker Configuration",
        collapsed: false,
        config: []
    },

    {
        name: "GROUP_ESM",
        displayName: "Error Signaling Configuration",
        collapsed: true,
        config: [
            {
                name        : "enableErrorSignal",
                displayName : "Enable Error Signal",
                description : 'Enable Error Signal to ESM',
                hidden      : false,
                default     : false
            },
        ]
    },
];

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["ADC"]));
}

function moduleInstances(inst)
{
    let components = new Array();

    components.push(
        {
            name: "adc_safetycheckertile",
            group: "GROUP_SAFECHECKCFG",
            displayName: "Safety Checker Tile",
            moduleName: "/driverlib/adc/modules/adcsafetycheckertile.js",
            useArray: true,
            collapsed: true,
            //maxInstances: maxInstances,
        }
    )

    components.push(
        {
            name: "adc_safetycheckeraggr",
            group: "GROUP_SAFECHECKCFG",
            displayName: "Safety Checker Interrupt/Event Configuration",
            moduleName: "/driverlib/adc/modules/adcsafetycheckeraggr.js",
            useArray: true,
            collapsed: true,
            //maxInstances: maxInstances,
        }
    )
    if(inst.enableErrorSignal){
        components.push(
            {
                name: "ESMConfig",
                group: "GROUP_ESM",
                displayName: "ADC Event Signaling",
                moduleName : "/driverlib/esm.js",
                useArray: false,
                collapsed:true,
                requiredArgs: {
                    eventSource: "ESM_EVENT_ADC_SAFETY_CHECK_INT_CPU" + CPU
                }
               
            },

        )
    }

    return components;
}

var adcSCModule = {
    peripheralName: "ADCSafetyChecker",
    displayName: "ADC SAFETY CHECKER",
    defaultInstanceName: "myADCSAFETYCHECK",
    description: "ADC Safety Checker Module",
    maxInstances: 1,
    // longDescription: (Common.getCollateralFindabilityList("ERAD")),
    filterHardware : filterHardware,
    moduleStatic          : {
        config          : config,
        moduleInstances : moduleInstances,
    },
    templates: {
        boardc : "/driverlib/adc/adcsc.board.c.xdt",
        boardh : "/driverlib/adc/adcsc.board.h.xdt"
    },
};


exports = adcSCModule;