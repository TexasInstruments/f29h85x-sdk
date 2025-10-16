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
    if((system.resourceAllocation.mode == "OFF") && !Common.isContextCPU1()) {
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
                cpuSel: inst.$assignedContext ?? system.context,
                pinmuxPeripheralModule : "",
                peripheralInst: inst.$module.name.toUpperCase().replace("GLOBAL", "CH"),
                removeCpuSelStandbyDbgHalt: true,
            },
            shouldBeAllocatedAsResource: true,
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


var rtdma1Module = {
    peripheralName: "RTDMA1",
    displayName: "RTDMA1",
    totalMaxInstances: 10,
    defaultInstanceName: "myRTDMA1Ch",
    config: Common.filterConfigsIfInSetupMode(rtdma_shared.getRTDMAConfig("RTDMA1")),
    sharedModuleInstances: sharedModuleInstances,
    moduleInstances: (inst) => {
        var submodules = []
        if (inst.useInterrupts && inst.registerInterrupts)
        {
            submodules = submodules.concat([{
                name: "rtdma1Int", 
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
        boardc : "/driverlib/rtdma1/rtdma1.board.c.xdt",
        boardh : "/driverlib/rtdma1/rtdma1.board.h.xdt"
    },

    moduleStatic: {
        name: "rtdma1Global",
        displayName: "RTDMA1 Global",
        config: Common.filterConfigsIfInSetupMode(rtdma_shared.getRTDMAGlobalConfig("RTDMA1")),
        moduleInstances: staticModuleInstances,
        validate: rtdma_shared.onValidateStatic,
        shouldBeAllocatedAsResource: true,
        alwaysAllocateAsResource: true,
    },
    
    shouldBeAllocatedAsResource: true,
    validate: rtdma_shared.onValidate,
    uiAdd   : uiAddOption,
};


exports = rtdma1Module;