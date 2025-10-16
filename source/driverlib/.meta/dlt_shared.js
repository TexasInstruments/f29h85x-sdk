let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_dlt.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

/* Intro splash on GUI */
let longDescription = "The DLT module enhances real-time non-intrusive data-logging and system analysis " + 
                      "capabilities of the device. Filtering out what is data-logged, using generated " +
                      "ERAD start commands to initiate data-logging and stop commands, using DLT start " +
                      "and stop commands for data-logging, and time stamping when or where in the program " +
                      "code data is being logged are the main features of the DLT.";

let dma_instances = [];
for (var dma of device_driverlib_memmap.DMAMemoryMap) {
    dma_instances.push({
        name : dma.name,
        displayName : dma.displayName
    })
}

function onChangeEnableERADFilter(inst, ui)
{
    if (inst.enableERADFilter == true){
        ui.startEvent.hidden = false;
        ui.endEvent.hidden = false;
    }
    else {
        ui.startEvent.hidden = true;
        ui.endEvent.hidden = true;
    }
}

function onChangeEnableTagFilter(inst, ui)
{
    if (inst.enableTagFilter == true){
        ui.startTagReference.hidden = false;
        ui.startTagMask.hidden = false;
        ui.endTagReference.hidden = false;
        ui.endTagMask.hidden = false;
    }
    else {
        ui.startTagReference.hidden = true;
        ui.startTagMask.hidden = true;
        ui.endTagReference.hidden = true;
        ui.endTagMask.hidden = true;
    }
}

function onChangeEnableInterrupt(inst, ui)
{
    if (inst.enableInterrupt.length > 0){
        ui.registerInterrupts.hidden = false;
    }
    else {
        ui.registerInterrupts.hidden = true;
    }
}

function onChangeEnableDMA(inst, ui)
{
    if (inst.enableDMA)
    {
        ui.useDMA.hidden = false;
    }
    else 
    {
        ui.useDMA.hidden = true;
    }
}

function onChangeUseDMA(inst, ui)
{
    if (inst.useDMA)
    {
        ui.DMAInst.hidden = false;
    }
    else 
    {
        ui.DMAInst.hidden = true;
    }
}

/* Array of DLT configurables that are common across device families */
let globalConfig = [
    {
        name: "GROUP_SYS",
        displayName: "System Configuration",
        collapsed: true,
        config: []
    }
];

let config = [
    {
        name: "GROUP_PERCFG",
        displayName: "Peripheral Configuration",
        collapsed: false,
        config: [
            {
                name        : "dltBase",
                displayName : "DLT Base Address",
                description : 'DLT Base address',
                hidden      : true,
                readOnly    : true,
                default     : "CPUDLT_BASE",
            },
            {
                name        : "GROUP_ERAD_FILTERING",
                displayName : "ERAD Event based Filtering",
                collapsed   : false,
                config      : 
                [
                    {
                        name         : "enableERADFilter",
                        displayName  : "Enable ERAD event based Filtering",
                        description  : 'Enables ERAD event based START-END filtering',
                        hidden       : false,
                        default      : false,
                        onChange     : onChangeEnableERADFilter,
                    },
                    {
                        name         : "startEvent",
                        displayName  : "Start Events",
                        description  : 'Set the ERAD events that can start the DLT recording for the ERAD event based filtering',
                        hidden       : true,
                        default      : [],
                        minSelections: 0,
                        options      : device_driverlib_peripheral.DLT_EventSelect,
                    },
                    {
                        name         : "endEvent",
                        displayName  : "End Events",
                        description  : 'Set the ERAD events that can end the DLT recording for the ERAD event based filtering',
                        hidden       : true,
                        default      : [],
                        minSelections: 0,
                        options      : device_driverlib_peripheral.DLT_EventSelect,
                    },
                ],
            },
            {
                name        : "GROUP_TAG_FILTERING",
                displayName : "TAG based Filtering",
                collapsed   : false,
                config      : 
                [
                    {
                        name         : "enableTagFilter",
                        displayName  : "Enable Tag based Filtering",
                        description  : 'Enables the TAG based START-END filtering',
                        hidden       : false,
                        default      : false,
                        onChange     : onChangeEnableTagFilter,
                    },
                    {
                        name         : "startTagReference",
                        displayName  : "Start Tag Reference",
                        description  : 'Set the Reference for the Start event Tag',
                        hidden       : true,
                        displayFormat: "hex",
                        default      : 0,
                    },
                    {
                        name         : "startTagMask",
                        displayName  : "Start Tag Mask",
                        description  : 'Set the Mask for the Start event Tag',
                        hidden       : true,
                        displayFormat: "hex",
                        default      : 0,
                    },
                    {
                        name         : "endTagReference",
                        displayName  : "End Tag Reference",
                        description  : 'Set the Reference for the End event Tag',
                        hidden       : true,
                        displayFormat: "hex",
                        default      : 0,
                    },
                    {
                        name         : "endTagMask",
                        displayName  : "End Tag Mask",
                        description  : 'Set the Mask for the End event Tag',
                        hidden       : true,
                        displayFormat: "hex",
                        default      : 0,
                    },
                ],
            },
            {
                name        : "setCaptureMode",
                displayName : "Set Capture Mode",
                description : 'Sets the DLT Capture Mode',
                hidden      : false,
                default     : device_driverlib_peripheral.DLT_CaptureMode[0].name,
                options     : device_driverlib_peripheral.DLT_CaptureMode,
            },
            {
                name        : "setFIFOTriggerLevel",
                displayName : "Set FIFO Trigger Level",
                description : 'Sets the FIFO Trigger level',
                hidden      : false,
                default     : 0xFF
            },
            {
                name        : "enableDMA",
                displayName : "Enable DMA",
                description : 'Enables DMA request to be generated when FIFO reaches the Trigger level',
                hidden      : false,
                default     : false,
                onChange    : onChangeEnableDMA,
            },            
        ]
    },
    {
        name: "GROUP_DMA",
        displayName: "RTDMA Configuration",
        collapsed: true,
        config: [
            {
                name        : "useDMA",
                displayName : "Use RTDMA",
                description : 'Whether or not to use DMA.',
                hidden      : true,
                default     : false,
                onChange    : onChangeUseDMA,
            },
            {
                name        : "DMAInst",
                displayName : "RTDMA instance to be used",
                description : "Choose the RTDMA instance for the channel used",
                hidden      : true,
                default     : dma_instances[0].name,
                options     : dma_instances,
            },
        ]
    },
    {
        name: "GROUP_INTERRUPT",
        displayName: "Interrupt Configuration",
        collapsed: true,
        config: [ 
            {
                name         : "enableInterrupt",
                displayName  : "Enable Interrupt",
                description  : 'Enables the events to generate an interrupt .',
                hidden       : false,
                default      : [],
                minSelections: 0,
                options      : device_driverlib_peripheral.DLT_INT.slice(1,),
                onChange     : onChangeEnableInterrupt,
            },
            {
                name         : "registerInterrupts",
                displayName  : "Register Interrupt Handler",
                description  : 'Whether or not to register interrupt handlers in the interrupt module.',
                hidden       : true,
                default      : false
            },
        ]
    },
];

function onValidate(inst, validation)
{
    if (inst.setFIFOTriggerLevel < 0 || inst.setFIFOTriggerLevel > 0xFF || (!Number.isInteger(inst.setFIFOTriggerLevel)))
    {
        validation.logError("FIFO Trigger level must be an integer between 0 and 0xFF", inst, "setFIFOTriggerLevel");
    }
    if (inst.startTagReference < 0 || inst.startTagReference > 0xFFFF || (!Number.isInteger(inst.startTagReference)))
    {
        validation.logError("The Start tag Reference value must be an integer between 0 and 0xFFFF", inst, "startTagReference");
    }
    if (inst.startTagMask < 0 || inst.startTagMask > 0xFFFF || (!Number.isInteger(inst.startTagMask)))
    {
        validation.logError("The Start tag Mask value must be an integer between 0 and 0xFFFF", inst, "startTagMask");
    }
    if (inst.endTagReference < 0 || inst.endTagReference > 0xFFFF || (!Number.isInteger(inst.endTagReference)))
    {
        validation.logError("The End tag Reference value be an integer between 0 and 0xFFFF", inst, "endTagReference");
    }
    if (inst.endTagMask < 0 || inst.endTagMask > 0xFFFF || (!Number.isInteger(inst.endTagMask)))
    {
        validation.logError("The End tag Mask value must be an integer between 0 and 0xFFFF", inst, "endTagMask");
    }
}


function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["DLT"]));
}

function moduleInstances(inst, isInst, isInstGlobal)
{
    let components = []
    if (inst.registerInterrupts)
    {
        components.push(
            {
                name: "dltInt",
                group: "GROUP_INTERRUPT",
                displayName: "DLT Interrupt",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: 
                    {
                        $name                  : "myDLT_INT",
                        typeInterruptName      : true,
                        pinmuxPeripheralModule : "",
                        driverlibInt           : "INT_DLT",
                        interruptHandler       : "INT_myDLT_ISR",
                    }
            }
        )
    }

    if (inst.useDMA)
    {
        let dmaInst = inst.DMAInst.split('_')[0].toLowerCase()
        components.push(
            {
                name: "dltDMA",
                group: "GROUP_DMA",    
                displayName: "RTDMA",
                moduleName: "/driverlib/" + dmaInst + ".js",
                collapsed: true,
                args: {
                    $name : "myDLT_" + system.context + "FIFO_DMA",
                    databusWidthConfig: "DMA_CFG_READ_SIZE_32BIT",
                    burstSize : 4,
                },
                requiredArgs: {
                    srcAddressLinked: "DLT_" + system.context + "FIFO_DMA_ADDRESS",
                    peripheralRXLinked: true,
                    triggerSource: "DMA_TRIGGER_" + system.context + "_DLT"
                }
            },
        )
    }

    if (isInst && !isInstGlobal)
    {
        return components
    }

    let staticComponents = []
    staticComponents.push(
        {
            name: "periphClock",
            group: "GROUP_SYS",
            displayName: "",
            moduleName: "/driverlib/perClock.js",
            collapsed: false,
            requiredArgs:{
                pinmuxPeripheralModule : "",
                peripheralInst: "CPUXDLT"
            }
        }
    )

    staticComponents.push(
        {
            name: "periphConfig",
            group: "GROUP_SYS",
            displayName: "",
            moduleName: "/driverlib/perConfig.js",
            collapsed: false,
            requiredArgs:{
                pinmuxPeripheralModule : "",
                peripheralInst: "DLTFIFOREGS",
                removeCpuSelStandbyDbgHalt: true,
            },
            shouldBeAllocatedAsResource: true,
        }
    )

    if(isInst && isInstGlobal)
    {
        return staticComponents
    }
    else
    {
        return components.concat(staticComponents)
    }
}



var dlt_shared = {
    globalConfig          : globalConfig,
    config                : config,
    moduleInstances       : moduleInstances,
    filterHardware        : filterHardware,
    onValidate            : onValidate,
    longDescription       : longDescription,
};

exports = dlt_shared;
