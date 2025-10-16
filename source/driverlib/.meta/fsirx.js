let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_fsi.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

let dma_instances = [];
for (var dma of device_driverlib_memmap.DMAMemoryMap) {
    dma_instances.push({
        name : dma.name,
        displayName : dma.displayName
    })
}

/* Intro splash on GUI */
let longDescription = "The Fast Serial Interface (FSI) module is a serial " +
                    "communication peripheral capable of reliable high-speed " +
                    "communication across isolation devices.";


function onChangeUseDMARX(inst, ui)
{
    if (inst.useDMARX)
    {
        ui.DMARXInstData.hidden = false;
        ui.DMARXInstInfo.hidden = false;
    }
    else
    {
        ui.DMARXInstData.hidden = true;
        ui.DMARXInstInfo.hidden = true;
    }
}

function onChangeEnableRxFrameWd(inst, ui)
{
    if (inst.enableRxFrameWd)
    {
        ui.rxFrameWdCounter.hidden = false;
    }
    else
    {
        ui.rxFrameWdCounter.hidden = true;
    }
}

function onChangeEnableInterrupt(inst, ui)
{
    if (inst.enableInterrupt) {
        ui.useInterrupts.hidden = false;
        if (inst.useInterrupts.indexOf(device_driverlib_peripheral.FSI_InterruptNum[0].name) != -1)
        {
            ui.enabledINT1Interrupts.hidden = false;
            ui.registerInterruptLine1.hidden = false;
        }
        else
        {
            ui.enabledINT1Interrupts.hidden = true;
            ui.registerInterruptLine1.hidden = true;
        }

        if (inst.useInterrupts.indexOf(device_driverlib_peripheral.FSI_InterruptNum[1].name) != -1)
        {
            ui.enabledINT2Interrupts.hidden = false;
            ui.registerInterruptLine2.hidden = false;
        }
        else
        {
            ui.enabledINT2Interrupts.hidden = true;
            ui.registerInterruptLine2.hidden = true;
        }
    }
    else {
        ui.useInterrupts.hidden = true;
        ui.enabledINT1Interrupts.hidden = true;
        ui.enabledINT2Interrupts.hidden = true;
        ui.registerInterruptLine1.hidden = true;
        ui.registerInterruptLine2.hidden = true;
    }
}

function onChangeEnableDelayTap(inst, ui)
{
    if (inst.enableDelayTap) {
        ui.tapValue1.hidden = false;
        ui.tapValue2.hidden = false;
        ui.tapValue3.hidden = false;
    }
    else {
        ui.tapValue1.hidden = true;
        ui.tapValue2.hidden = true;
        ui.tapValue3.hidden = true;
    }
}

function onChangeEnablePingTimeout(inst, ui)
{
    if (inst.pingTimeout) {
        ui.selectPingMode.hidden = false;
        ui.timeoutDelay.hidden = false;
    }
    else {
        ui.selectPingMode.hidden = true;
        ui.timeoutDelay.hidden = true;
    }
}

function onChangeEnableTagMatch(inst, ui)
{
    if (inst.enableTagMatching) {
        ui.frameTag.hidden = false;
        ui.frameType.hidden = false;
        ui.tagMask.hidden = false;
    }
    else {
        ui.frameTag.hidden = true;
        ui.frameType.hidden = true;
        ui.tagMask.hidden = true;
    }
}

/* Array of FSI configurables that are common across device families */
let config = [

    {
        name: "GROUP_PERCFG",
        displayName: "Peripheral Configuration",
        collapsed: false,
        config: [
            {
                name        : "enableLoopback",
                displayName : "Loopback Mode",
                description : 'Whether or not to use internal loopback mode',
                longDescription: "The option to enable the loopback is provided in" +
                                "just the RX module. Additional steps to initialize " +
                                "RX core are to be done in the main source code.",
                hidden      : false,
                default     : false
            },
            {
                name: "GROUP_FRAMECFG",
                displayName: "Frame Configuration",
                longDescription: "This section is used for frame configuration " +
                                "for the RX module.",
                collapsed: false,
                config: [
                {
                    name        : "dataWidth",
                    displayName : "Number of Data Lines",
                    description : 'Number of lanes for communication',
                    hidden      : false,
                    default     : device_driverlib_peripheral.FSI_DataWidth[0].name,
                    options     : device_driverlib_peripheral.FSI_DataWidth,
                },

                {
                    name        : "softwareFrameSize",
                    displayName : "Software Frame Size",
                    description : 'When selecting N-WORD frame type, this determines number of words (N)',
                    hidden      : false,
                    default     : '8',
                    options     : [
                        { name: "1" , displayName : "1-Word"},
                        { name: "2" , displayName : "2-Word"},
                        { name: "3" , displayName : "3-Word"},
                        { name: "4" , displayName : "4-Word"},
                        { name: "5" , displayName : "5-Word"},
                        { name: "6" , displayName : "6-Word"},
                        { name: "7" , displayName : "7-Word"},
                        { name: "8" , displayName : "8-Word"},
                        { name: "9" , displayName : "9-Word"},
                        { name: "10" , displayName : "10-Word"},
                        { name: "11" , displayName : "11-Word"},
                        { name: "12" , displayName : "12-Word"},
                        { name: "13" , displayName : "13-Word"},
                        { name: "14" , displayName : "14-Word"},
                        { name: "15" , displayName : "15-Word"},
                        { name: "16" , displayName : "16-Word" }
                    ]
                },
                {
                    name        : "enableRxFrameWd",
                    displayName : "Enable Frame Watchdog",
                    longDescription: "This options sets the Rx Frame watchdog counter" +
                    "Interrupt event for the same will have to be configured manually",
                    description : 'Whether or not to enable Rx Frame watchdog',
                    hidden      : false,
                    default     : false,
                    onChange    : onChangeEnableRxFrameWd
                },
                {
                    name        : "rxFrameWdCounter",
                    displayName : "Set Frame Watchdog Counter",
                    description : 'Enter the frame watchdog counter value (32-bit hexadecimal)',
                    hidden      : true,
                    default     : 1000000
                },
            ]
            },
            {
                name: "GROUP_TAGMATCH",
                displayName: "Tag Matching",
                longDescription: "This section is used to configure the " +
                                "frame type and frame tag which will be matched " +
                                "with the incoming frame type and frame tag. The user " +
                                "can configure interrupts corresponding to tag match " +
                                "event for ping or frame under the interrupts tab.",
                collapsed: false,
                config: [
                {
                    name        : "enableTagMatching",
                    displayName : "Enable Tag Matching",
                    description : 'To Enable Tag matching for receieved frame tag.',
                    hidden      : false,
                    onChange    : onChangeEnableTagMatch,
                    default     : false,
                },

                {
                    name        : "frameType",
                    displayName : "Reference frame type",
                    description : 'Sets the Rx Frame Reference Type Value',
                    longDescription: "The reference type is used to check against " +
                                    "when comparing the TAG_MASK and " +
                                    "the incoming frame tag.",
                    hidden      : true,
                    default     : device_driverlib_peripheral.FSI_FrameType[0].name,
                    options     : device_driverlib_peripheral.FSI_FrameType,
                },

                {
                    name        : "frameTag",
                    displayName : "Reference frame tag",
                    description : 'Sets the Rx Frame Reference Tag Value',
                    longDescription: "The reference tag is used to check against " +
                                    "when comparing the TAG_MASK and " +
                                    "the incoming frame tag.",
                    hidden      : true,
                    default     : device_driverlib_peripheral.FSI_FrameTag[0].name,
                    options     : device_driverlib_peripheral.FSI_FrameTag,
                },

                {
                    name        : "tagMask",
                    displayName : "Tag Mask",
                    description : 'Sets the Rx Frame Tag Mask',
                    longDescription: "The tag mask is used ignore the specified " +
                                    "bits in the frame tag during comparison.",
                    hidden      : true,
                    default     : 0,
                },
            ]},
            {
                name: "GROUP_PING",
                displayName: "Ping Timeout",
                longDescription: "This function is meant to set up ping watchdog " +
                                "for the RX module. The delay value will be time after " +
                                "which the received ping frame will be checked.",
                collapsed: false,
                config: [
                {
                    name        : "pingTimeout",
                    displayName : "Enable PING Timeout",
                    description : 'Enables the timeout for Ping.',
                    hidden      : false,
                    onChange    : onChangeEnablePingTimeout,
                    default     : false,
                },

                {
                    name        : "selectPingMode",
                    displayName : "Select PING Timeout Mode",
                    description : 'Select the timeout mode for Ping.',
                    hidden      : true,
                    default     : device_driverlib_peripheral.FSI_PingTimeoutMode[0].name,
                    options     : device_driverlib_peripheral.FSI_PingTimeoutMode
                },

                {
                    name        : "timeoutDelay",
                    displayName : "Select PING Timeout Delay",
                    description : 'Enter the timeout value for ping watchdog in integer.',
                    hidden      : true,
                    default     : 0
                },
            ]
            },

            {
                name: "GROUP_DELAY",
                displayName: "Delay Tap Selection",
                longDescription: "This section enables the user to " +
                                "decide the delay for RXCLK line, RXD0 and " +
                                "RXD1 line. It is to be noted that these " +
                                "configurations do not enable the delay line functioning fully." +
                                " The user will need to perform additional steps mentioned in the " +
                                "device reference manual. The function defined in board.c file can " +
                                "be used as a starting point for the functionality.",
                collapsed: false,
                config: [
                {
                    name        : "enableDelayTap",
                    displayName : "Enable Delay Tapping",
                    description : 'To Enable Rx lines for delay tap selection.',
                    hidden      : false,
                    onChange    : onChangeEnableDelayTap,
                    default     : false,
                },

                {
                    name        : "tapValue1",
                    displayName : "Enter Delay Tap Value for CLK",
                    description : '5 bit value of the amount of delay to be added',
                    hidden      : true,
                    default     : 0
                },

                {
                    name        : "tapValue2",
                    displayName : "Enter Delay Tap Value for D0",
                    description : '5 bit value of the amount of delay to be added',
                    hidden      : true,
                    default     : 0
                },

                {
                    name        : "tapValue3",
                    displayName : "Enter Delay Tap Value for D1",
                    description : '5 bit value of the amount of delay to be added',
                    hidden      : true,
                    default     : 0
                },
            ]
            },
            {
                name: "useCase",
                displayName : "PinMux Use Case",
                description : 'Peripheral use case',
                hidden      : false,
                default     : 'ALL',
                options     : Pinmux.getPeripheralUseCaseNames("FSIRX"),
                onChange    : Pinmux.useCaseChanged,
            },
        ]
    },
    {
        name: "GROUP_ISR",
        displayName: "Interrupt Configuration",
        collapsed: false,
        config: [
            {
                name        : "enableInterrupt",
                displayName : "Enable Interrupt",
                description : 'To Enable FSI Interrupts.',
                hidden      : false,
                onChange    : onChangeEnableInterrupt,
                default     : false,
            },

            {
                name        : "useInterrupts",
                displayName : "Use Interrupt Lines",
                description : 'Selection of FSI Interrupt Lines.',
                onChange    : onChangeEnableInterrupt,
                hidden      : true,
                default     : [],
                minSelections: 0,
                options     : device_driverlib_peripheral.FSI_InterruptNum

            },

            {
                name        : "enabledINT1Interrupts",
                displayName : "Enabled INT1 Line Interrupts",
                description : 'Interrupts to be enabled for INT1.',
                hidden      : true,
                default     : [],
                minSelections: 0,
                options     : device_driverlib_peripheral.FSI_RX_EVT,

            },

            {
                name        : "enabledINT2Interrupts",
                displayName : "Enabled INT2 Line Interrupts",
                description : 'Interrupts to be enabled for INT2.',
                hidden      : true,
                default     : [],
                minSelections: 0,
                options     : device_driverlib_peripheral.FSI_RX_EVT,

            },

            {
                name        : "registerInterruptLine1",
                displayName : "Register INT1 Line Handler",
                description : 'Whether or not to register interrupt Line1 handlers in the interrupt module.',
                hidden      : true,
                default     : false
            },
            {
                name        : "registerInterruptLine2",
                displayName : "Register INT2 Line Handler",
                description : 'Whether or not to register interrupt Line2 handlers in the interrupt module.',
                hidden      : true,
                default     : false
            },
        ]
    },
    {
        name: "GROUP_DMA",
        displayName: "RTDMA Configuration",
        collapsed: true,
        config: [
            {
                name        : "useDMARX",
                displayName : "Use RTDMA for Receive",
                description : 'Whether or not to use DMA mode for RX.',
                hidden      : false,
                default     : false,
                onChange    : onChangeUseDMARX,
                shouldBeAllocatedAsResource : true
            },
            {
                name        : "DMARXInstData",
                displayName : "RTDMA instance to be used for Received Data",
                description : "Choose the RTDMA instance for the channel used for Receive",
                hidden      : true,
                default     : dma_instances[0].name,
                options     : dma_instances,
                shouldBeAllocatedAsResource : true
            },
            {
                name        : "DMARXInstInfo",
                displayName : "RTDMA instance to be used for Tag and User Data",
                description : "Choose the RTDMA instance for the channel used for Receive",
                hidden      : true,
                default     : dma_instances[0].name,
                options     : dma_instances,
                shouldBeAllocatedAsResource : true
            }
        ]
    },
    {
        name: "GROUP_SYS",
        displayName: "System Configuration",
        collapsed: true,
        config: []
    },
]
function validatePinmux(inst,validation){
    if (inst.fsirx && inst.fsirx.$solution) {
        let selectedPeripheral = inst.fsirx.$solution.peripheralName; // e.g., "UARTA"
        if (Common.is_instance_not_in_variant(selectedPeripheral)) {
            validation.logError(
                `${selectedPeripheral} is not supported for ${Common.getVariant().replace(/^TMS320/, '')}.`,
                inst,
                "fsirx"
            );
        }
    }
}

function onValidate(inst, validation)
{
    if (inst.timeoutDelay < 0 || inst.timeoutDelay > 0xFFFFFFFF)
    {
        validation.logError(
            "Enter an integer value for Ping Timeout within 32 bits!",
            inst, "timeoutDelay");
    }
    if (inst.tapValue1 < 0 || inst.tapValue1 > 0x1F)
    {
        validation.logError(
            "Enter an integer for Delay Tapping between 0 and 31!",
            inst, "tapValue1");
    }
    if (inst.tapValue2 < 0 || inst.tapValue2 > 0x1F)
    {
        validation.logError(
            "Enter an integer for Delay Tapping between 0 and 31!",
            inst, "tapValue2");
    }
    if (inst.tapValue3 < 0 || inst.tapValue3 > 0x1F)
    {
        validation.logError(
            "Enter an integer for Delay Tapping between 0 and 31!",
            inst, "tapValue3");
    }
    if (inst.tagMask < 0 || inst.tagMask > 0xF)
    {
        validation.logError(
            "Enter an integer for Tag Mask within 4 bits!",
            inst, "tagMask");
    }

}

/*
 *  ======== filterHardware ========
 *  Control RX, TX Pin usage by the user specified dataDirection.
 *
 *  param component - hardware object describing signals and
 *                     resources they're attached to
 *
 *  returns Boolean indicating whether or not to allow the component to
 *           be assigned to an instance's $hardware config
 */
function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["FSIRX", "FSI"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var fsirxModule = {
    peripheralName: "FSIRX",
    displayName: "FSIRX",
    totalMaxInstances: Common.peripheralCount("FSIRX"),
    defaultInstanceName: "myFSIRX",
    description: "Fast Serial Interface Receiver Peripheral",
    filterHardware : filterHardware,
    config: Common.filterConfigsIfInSetupMode(config),
    moduleInstances: (inst) => {
        var ownedInstances = [];

        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("FSIRX", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
            pinmuxQualMod.args = {
                qualMode : "GPIO_QUAL_ASYNC",
            }
        }

        ownedInstances = ownedInstances.concat(pinmuxQualMods)

        if (inst.enableInterrupt && inst.registerInterruptLine1)
        {
            ownedInstances.push(
                {
                    name: "fsiRxInt1",
                    group: "GROUP_ISR",
                    displayName: "INT1 Interrupt",
                    moduleName: "/driverlib/interrupt.js",
                    collapsed: true,
                    args: {
                        $name : inst.$name + "_INT1",
                        typeInterruptName : true,
                        pinmuxPeripheralModule : "fsirx",
                        driverlibInt: "INT_#1",
                        interruptHandler : "INT_" + inst.$name + "_1_ISR",
                    }
                }
            )
        }
        if (inst.enableInterrupt && inst.registerInterruptLine2)
        {
            ownedInstances.push(
                {
                    name: "fsiRxInt2",
                    group: "GROUP_ISR",
                    displayName: "INT2 Interrupt",
                    moduleName: "/driverlib/interrupt.js",
                    collapsed: true,
                    args: {
                        $name : inst.$name + "_INT2",
                        typeInterruptName : true,
                        pinmuxPeripheralModule : "fsirx",
                        driverlibInt: "INT_#2",
                        interruptHandler : "INT_" + inst.$name + "_2_ISR",
                    }
                }
            )
        }

        if (inst.useDMARX)
        {
            let dmaInstData = inst.DMARXInstData.split('_')[0].toLowerCase()
            let dmaInstInfo = inst.DMARXInstInfo.split('_')[0].toLowerCase()

            ownedInstances = ownedInstances.concat([
                {
                    name: "fsiRXDMAData",
                    group: "GROUP_DMA",
                    displayName: "FSIRX DMA - Received Data",
                    moduleName: "/driverlib/" + dmaInstData + ".js",
                    collapsed: true,
                    args: {
                        $name : inst.$name + "_RX_DMA_DATA",
                        burstSize : 2,
                        srcBurstStep : 2,
                        srcTransferStep : 2,
                        srcWrapSize : 32,
                        //srcWrapStep: -32
                    },
                    requiredArgs: {
                        srcAddressLinked: inst.$name + "_RX_DMA_DATA_ADDRESS",
                        peripheralRXLinked: true,
                        databusWidthConfig: "DMA_CFG_READ_SIZE_16BIT",
                        writeDatasizeConfig: "DMA_CFG_WRT_SIZE_16BIT",
                        triggerSource: "DMA_TRIGGER_LINKED"
                    },
                    shouldBeAllocatedAsResource : true
                },
                {
                    name: "fsiRXDMAInfo",
                    group: "GROUP_DMA",
                    displayName: "FSIRX DMA - Tag and User Data",
                    moduleName: "/driverlib/" + dmaInstInfo + ".js",
                    collapsed: true,
                    args: {
                        $name : inst.$name + "_RX_DMA_INFO",
                        burstSize : 2,
                    },
                    requiredArgs: {
                        srcAddressLinked: inst.$name + "_RX_DMA_INFO_ADDRESS",
                        peripheralRXLinked: true,
                        databusWidthConfig: "DMA_CFG_READ_SIZE_16BIT",
                        writeDatasizeConfig: "DMA_CFG_WRT_SIZE_16BIT",
                        triggerSource: "DMA_TRIGGER_LINKED"
                    },
                    shouldBeAllocatedAsResource : true
                },
            ])
        }

        ownedInstances = ownedInstances.concat([
            {
                name: "periphClock",
                group: "GROUP_SYS",
                displayName: "",
                moduleName: "/driverlib/perClock.js",
                collapsed: false,
                requiredArgs:{
                    pinmuxPeripheralModule : "fsirx",
                    peripheralInst: "",
                }
            },
            {
                name: "periphConfig",
                group: "GROUP_SYS",
                displayName: "",
                moduleName: "/driverlib/perConfig.js",
                collapsed: false,
                requiredArgs:{
                    cpuSel: inst.$assignedContext ?? system.context,
                    pinmuxPeripheralModule : "fsirx",
                    peripheralInst: ""
                },
                shouldBeAllocatedAsResource: true
            },
        ])

        return ownedInstances;
    },
    validate    : onValidate,
    validatePinmux: validatePinmux,
    templates: {
        boardc : "/driverlib/fsirx/fsirx.board.c.xdt",
        boardh : "/driverlib/fsirx/fsirx.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.fsirxPinmuxRequirements,
    shouldBeAllocatedAsResource: true
};

if (fsirxModule.maxInstances <= 0)
{
    delete fsirxModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(fsirxModule)
    Pinmux.addPinMuxQualGroupToConfig(fsirxModule)
}

exports = fsirxModule;