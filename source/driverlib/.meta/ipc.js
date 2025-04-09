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

let contextNames = ["CPU1","CPU2","CPU3"]
let otherContexts = contextNames.filter(e => e !== system.context);
let staticConfig = []
for(var i in otherContexts){
    let cntx = otherContexts[i]
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

function onValidate(inst, validation)
{
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

    for (var i in inst.registerInterrupts0)
    {
        var int = inst.registerInterrupts0[i]
        intReturn.push ({
            name: "ipcInt1" + (+int+1),
            displayName: "IPC 1-" + (+int+1) + " INTERRUPT",
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

