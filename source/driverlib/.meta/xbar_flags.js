var config = [];

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
                pinmuxPeripheralModule : "",
                peripheralInst: "INPUTXBARFLAGS",
                removeCpuSelStandbyDbgHalt: true,
            }
        }
    )

    components.push(
        {
            name: "outputFlagsPeriphConfig",
            displayName: "Output Flags System Configuration",
            moduleName: "/driverlib/perConfig.js",
            collapsed: false,
            requiredArgs:{
                pinmuxPeripheralModule : "",
                peripheralInst: "OUTPUTXBARFLAGS",
                removeCpuSelStandbyDbgHalt: true,
            }
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
    },
};


exports = xbarFlagsModule;