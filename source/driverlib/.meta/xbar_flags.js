var config = [
    {
        name        : "$assignedContext",
        hidden      : true,
        default     : "CPU1",
        options     : [{name:"CPU1"}],
        readOnly    : true
    }
];

function moduleInstances(inst)
{
    let components = []
    components.push(
        {
            name: "inputFlagsPeriphConfig",
            displayName: "Input Flags System Configuration",
            moduleName: "/driverlib/perConfig.js",
            collapsed: false,
            requiredArgs:{
                cpuSel: inst.$assignedContext ?? system.context,
                pinmuxPeripheralModule : "",
                peripheralInst: "INPUTXBARFLAGS",
                removeCpuSelStandbyDbgHalt: true,
            },
            shouldBeAllocatedAsResource : true,
        }
    )

    components.push(
        {
            name: "outputFlagsPeriphConfig",
            displayName: "Output Flags System Configuration",
            moduleName: "/driverlib/perConfig.js",
            collapsed: false,
            requiredArgs:{
                cpuSel: inst.$assignedContext ?? system.context,
                pinmuxPeripheralModule : "",
                peripheralInst: "OUTPUTXBARFLAGS",
                removeCpuSelStandbyDbgHalt: true,
            },
            shouldBeAllocatedAsResource : true,
        }
    )

    return components;
}

var xbarFlagsModule = {
    peripheralName        : "XBARFLAGS",
    displayName           : "XBAR FLAGS",
    maxInstances          : 1,
    defaultInstanceName   : "myXBARFlags",
    description           : "XBAR Input/ Output Flags",
    moduleStatic          : {
        config          : config,
        moduleInstances : moduleInstances,
        shouldBeAllocatedAsResource : true,
        alwaysAllocateAsResource : true,
    },
};


exports = xbarFlagsModule;