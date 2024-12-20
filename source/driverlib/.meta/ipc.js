let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");
let device_driverlib_int_names =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_interrupt.js");

/* Intro splash on GUI */
let longDescription = `The Inter-Processor Communication (IPC) allows to setup a communication channel 
between various cores.`;
var sharedModuleInstances = undefined;

var driverlibIntNames = [];

device_driverlib_int_names.interrupts.
    forEach((element, index) =>
        {
            if (element.int_define_name.includes("INT_IPC_"))
                {
                    driverlibIntNames.push(element.int_define_name);
                }
        }
);

let IntNumber = [
{name: "0", displayName: "IPC_1_1"},    
{name: "1", displayName: "IPC_1_2"},
{name: "2", displayName: "IPC_1_3"},
{name: "3", displayName: "IPC_1_4"},
{name: "4", displayName: "IPC_2_1"},    
{name: "5", displayName: "IPC_2_2"},
{name: "6", displayName: "IPC_2_3"},
{name: "7", displayName: "IPC_2_4"},
]

let staticConfig = []
let otherContexts = Common.getOtherContextNames()
if (Common.isMultiCoreSysConfig())
{
    for(var i in otherContexts){
        var cntx = otherContexts[i]
        staticConfig = staticConfig.concat([
            {
                name        : "registerInterrupts" + i,
                displayName : "Register Interrupts to Receive signal from " + cntx,
                description : 'Whether or not to register interrupt handlers in the interrupt module.',
                hidden      : false,
                default     : [],
                minSelections: 0,
                options     : IntNumber.slice((4*i), 4*(i+1))
            }
        ]);
    }
}
else
{
    staticConfig = staticConfig.concat([
        {
            name        : "registerInterrupts0",
            displayName : "Register Interrupts to Receive signal from other Cores",
            description : 'Whether or not to register interrupt handlers in the interrupt module.',
            hidden      : false,
            default     : [],
            minSelections: 0,
            options     : IntNumber.slice(0,8)
        },
    ]);
}


function onValidate(inst, validation)
{
    // if (Common.isMultiCoreSysConfig())
    // {
    //     if (Common.isModuleOnOtherContext("/driverlib/ipc.js") == false)
    //     {
    //         validation.logError("The IPC module needs to be added on two CPUs",
    //         inst, "registerInterrupts");
    //     }
    // }
    if (!Common.isMultiCoreSysConfig())
    {
        validation.logWarning("The IPC module is intended for use in a multi-core system. Error checking is limited in single-core mode.", 
        inst);
    }
}


function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["IPC"]));
}

function moduleInstances(inst)
{
    let intReturn =  []

    if ((inst.registerInterrupts0.length > 0))
    {
        for (var i in inst.registerInterrupts0)
        {
            var int = inst.registerInterrupts0[i]
            intReturn.push ({
                name: "ipcInt1" + (+int+1),
                displayName: "IPC " + driverlibIntNames[int].replace("INT_IPC_", "") + " INTERRUPT",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
                    $name : driverlibIntNames[int].replace("INT_", "INT_my"),
                    typeInterruptName : true,
                    pinmuxPeripheralModule :"",
                    driverlibInt: driverlibIntNames[int],
                    interruptHandler : driverlibIntNames[int] + "_ISR",
                }
            })
        }
    }

    if(Common.isMultiCoreSysConfig() & otherContexts.length > 1)
    {
        console.log("inside if")
        if ((inst.registerInterrupts1.length > 0))
        {
            for (var i in inst.registerInterrupts1)
            {
                var int = inst.registerInterrupts1[i]
                intReturn.push ({
                    name: "ipcInt2" + (+int-3),
                    displayName: "IPC 2-" + (+int-3) + " INTERRUPT",
                    moduleName: "/driverlib/interrupt.js",
                    collapsed: true,
                    args: {
                        $name : driverlibIntNames[int].replace("INT_", "INT_my"),
                        typeInterruptName : true,
                        pinmuxPeripheralModule :"",
                        driverlibInt: driverlibIntNames[int],
                        interruptHandler : driverlibIntNames[int] + "_ISR",
                    }
                })
            }
        }
    }

    return intReturn;
}


var ipcModule = {
    peripheralName: "IPC",
    displayName: "IPC",
    maxInstances: Common.peripheralCount("IPC"),
    defaultInstanceName: "myIPC",
    description: "Interprocessor Communication between C29 Cores",
    filterHardware : filterHardware,
    moduleStatic : {
        config: staticConfig,
        moduleInstances: moduleInstances,
        validate: onValidate,
    },
    templates: {
        boardc : "/driverlib/ipc/ipc.board.c.xdt",
        boardh : "/driverlib/ipc/ipc.board.h.xdt"
    },
};


exports = ipcModule;

