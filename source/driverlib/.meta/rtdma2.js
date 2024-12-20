let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_rtdma.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

let rtdma_shared =
    system.getScript("/driverlib/rtdma.js");

var sharedModuleInstances = undefined;

var uiAddOption = "instanceOnly"
if (Common.isContextCPU1())
{
    uiAddOption = "staticAndInstance"
}

function staticModuleInstances(inst, ui)
{
    let components = []
    if(!Common.isContextCPU1()) {
        return components
    }
    var rtdmaInstance = inst.$module.name.toUpperCase().replace("GLOBAL", "")
    components.push(
        {
            name: "periphClock",
            group: "GROUP_SYS",
            displayName: "",
            moduleName: "/driverlib/perClock.js",
            collapsed: false,
            requiredArgs:{
                pinmuxPeripheralModule : "",
                peripheralInst: rtdmaInstance,
            }
        }
    )
    components.push(
        {
            name: "periphConfig",
            group: "GROUP_SYS",
            displayName: "",
            moduleName: "/driverlib/perConfig.js",
            collapsed: false,
            requiredArgs:{
                pinmuxPeripheralModule : "",
                peripheralInst: inst.$module.name.toUpperCase().replace("GLOBAL", "CH"),
                removeCpuSelStandbyDbgHalt: true,
            }
        }
    )

    if (inst.configureESMforLPERR){
        components.push(
            {
                name: "ESMConfigLPERR",
                group: "GROUP_ESM",
                displayName: "Error Signaling for LPERR",
                moduleName : "/driverlib/esm.js",
                collapsed: true,
                args: {
                    $name: rtdmaInstance + "_LPERR_ESM",
                },
                requiredArgs: {
                    eventSource: "ESM_EVENT_ErrorAggregator_" + rtdmaInstance + "_LPERR"
                },
            }
        )
    }

    if (inst.configureESMforHPERR){
        components.push(
            {
                name: "ESMConfigHPERR",
                group: "GROUP_ESM",
                displayName: "Error Signaling for HPERR",
                moduleName : "/driverlib/esm.js",
                collapsed: true,
                args: {
                    $name: rtdmaInstance + "_HPERR_ESM",
                },
                requiredArgs: {
                    eventSource: "ESM_EVENT_ErrorAggregator_" + rtdmaInstance + "_HPERR"
                },
            }
        )
    }

    return components
}

var rtdma2Module = {
    peripheralName: "RTDMA2",
    displayName: "RTDMA2",
    maxInstances: 10,
    defaultInstanceName: "myRTDMA2Ch",
    config: rtdma_shared.getRTDMAConfig("RTDMA2"),
    sharedModuleInstances: sharedModuleInstances,
    moduleInstances: (inst) => {
        var submodules = []
        if (inst.useInterrupts && inst.registerInterrupts)
        {
            submodules = submodules.concat([{
                name: "rtdma2Int",      
                group: "GROUP_INTERRUPT",
                displayName: "RTDMA Interrupt",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
            		$name : inst.$name + "_INT",
                    typeInterruptName : true,
                    pinmuxPeripheralModule :"",
                    driverlibInt: "INT_" + inst.chBase.split('_')[0],
                    interruptHandler : "INT_" + inst.$name + "_ISR",
                }
            }])
        }
        return submodules;
    },
    
    templates: {
        boardc : "/driverlib/rtdma2/rtdma2.board.c.xdt",
        boardh : "/driverlib/rtdma2/rtdma2.board.h.xdt"
    },
    moduleStatic: {
        name: "rtdma2Global",
        displayName: "RTDMA2 Global",
        config: rtdma_shared.getRTDMAGlobalConfig("RTDMA2"),
        moduleInstances: staticModuleInstances,
        validate: rtdma_shared.onValidateStatic,
    },

    validate: rtdma_shared.onValidate,
    uiAdd   : uiAddOption,
};


exports = rtdma2Module;