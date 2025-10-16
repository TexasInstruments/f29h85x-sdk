let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_rtdma.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

var DMA_INSTANCE = [];
for (var dma of device_driverlib_memmap.DMAMemoryMap) {
    DMA_INSTANCE.push({
        name : dma.name,
        displayName : dma.displayName
    })
}

var CHANNEL_INSTANCE = [];
for (var channel of device_driverlib_memmap.DMAChMemoryMap) {
    CHANNEL_INSTANCE.push({
        name : channel.name,
        displayName : channel.displayName
    })
}


device_driverlib_peripheral.DMA_Trigger.push({name: "DMA_TRIGGER_LINKED", displayName: "Trigger is linked to peripheral"})

let INPUT_MODE_MANUAL = "MANUAL"
let INPUT_MODE_VARIABLE = "VARIABLE"
let INPUT_MODE_LINKED = "LINKED"

let ADDRESS_INPUT_MODE = [
    {name: "MANUAL", displayName: "Manual"},
    {name: "VARIABLE", displayName: "Variable/Function Name"},
    {name: "LINKED", displayName: "Linked to Peripheral"},
]

let datasize_map = {
    "DMA_CFG_READ_SIZE_8BIT" : 8,
    "DMA_CFG_READ_SIZE_16BIT" : 16,
    "DMA_CFG_READ_SIZE_32BIT" : 32,
    "DMA_CFG_READ_SIZE_64BIT" : 64,
    "DMA_CFG_WRT_SIZE_8BIT" : 8,
    "DMA_CFG_WRT_SIZE_16BIT" : 16,
    "DMA_CFG_WRT_SIZE_32BIT" : 32,
    "DMA_CFG_WRT_SIZE_64BIT" : 64,
}

/* Intro splash on GUI */
let longDescription = "";


function onChangePeripheralTXLinked(inst,ui)
{
    if (inst.peripheralTXLinked) {
        inst.destBurstStep = 0;
        //ui.destBurstStep.readOnly = true;
        inst.destTransferStep = 0;
        //ui.destTransferStep.readOnly = true;
        inst.destWrapStep = 0;
        //ui.destWrapStep.readOnly = true;
        

        ui.destAddressManual.hidden = true;
        inst.destAddressInputMode = INPUT_MODE_LINKED
        ui.destAddressInputMode.readOnly = true
        ui.destAddressLinked.hidden = false
        ui.destAddressLinked.readOnly = true
        inst.destWrapSize = 65536;
    }
}

function onChangePeripheralRXLinked(inst,ui)
{
    if (inst.peripheralRXLinked) {
        inst.srcBurstStep = 0;
        //ui.srcBurstStep.readOnly = true;
        inst.srcTransferStep = 0;
        //ui.srcTransferStep.readOnly = true;
        inst.srcWrapStep = 0;
        //ui.srcWrapStep.readOnly = true;

        ui.srcAddressManual.hidden = true;
        inst.srcAddressInputMode = INPUT_MODE_LINKED
        ui.srcAddressInputMode.readOnly = true
        ui.srcAddressLinked.hidden = false
        ui.srcAddressLinked.readOnly = true
        inst.srcWrapSize = 65536;
        //ui.srcWrapSize.readOnly = true
    }
}

function onChangePriorityMode(inst, ui)
{
    if(inst.enableSoftwarePriority == true)
    {
        ui.channelPriority.hidden = false
    }
    else
    {
        ui.channelPriority.hidden = true
    }
}

// function onChangeLockAllChannelConfig(inst,ui)
// {
//     if (inst.lockAllChannelConfig){
//         ui.lockChannelConfig.hidden = true 
//     }
//     else{
//         ui.lockChannelConfig.hidden = false
//     }

// }

// function onChangeCommitAllChannelConfig(inst,ui)
// {
//     if (inst.commitAllChannelConfig){
//         ui.commitChannelConfig.hidden = true 
//     }
//     else{
//         ui.commitChannelConfig.hidden = false
//     }
// }

function onChangeUseInterrupts(inst,ui)
{
    if (inst.useInterrupts) {
        ui.enableInterrupts.hidden = false
        ui.registerInterrupts.hidden = false
        ui.enableOverrunInterrupt.hidden = false
        ui.interruptMode.hidden = false
    }
    else {
        ui.enableInterrupts.hidden = true
        ui.registerInterrupts.hidden = true
        ui.enableOverrunInterrupt.hidden = true
        ui.interruptMode.hidden = true
    }
}

function onChangeSrcAddressInputMode(inst,ui)
{
    if (inst.srcAddressInputMode == INPUT_MODE_MANUAL) {
        ui.srcAddressManual.hidden = false
        ui.srcAddressVariable.hidden = true
        ui.srcAddressLinked.hidden = true
    }
    if (inst.srcAddressInputMode == INPUT_MODE_VARIABLE) {
        ui.srcAddressManual.hidden = true
        ui.srcAddressVariable.hidden = false
        ui.srcAddressLinked.hidden = true
    }
    if (inst.srcAddressInputMode == INPUT_MODE_LINKED) {
        ui.srcAddressManual.hidden = true
        ui.srcAddressVariable.hidden = true
        ui.srcAddressLinked.hidden = false
        ui.srcAddressLinked.readOnly = true
        ui.srcWrapSize.readOnly = true
    }
}

function onChangeDestAddressInputMode(inst,ui)
{
    if (inst.destAddressInputMode == INPUT_MODE_MANUAL) {
        ui.destAddressManual.hidden = false
        ui.destAddressVariable.hidden = true
        ui.destAddressLinked.hidden = true
    }
    if (inst.destAddressInputMode == INPUT_MODE_VARIABLE) {
        ui.destAddressManual.hidden = true
        ui.destAddressVariable.hidden = false
        ui.destAddressLinked.hidden = true
    }
    if (inst.destAddressInputMode == INPUT_MODE_LINKED) {
        ui.destAddressManual.hidden = true
        ui.destAddressVariable.hidden = true
        ui.destAddressLinked.hidden = false
        ui.destAddressLinked.readOnly = true
        ui.destWrapSize.readOnly = true
    }
}

function getRTDMAGlobalConfig(rtdma_instance)
{
    var globalConfig = []
    if((system.resourceAllocation.mode == "OFF") && !Common.isContextCPU1()) {
        return globalConfig
    }

    if(rtdma_instance == "RTDMA1"){
        globalConfig.push({
            name        : "dmaBase",
            displayName : "RTDMA Instance",
            description : 'RTDMA Instance used.',
            default     : DMA_INSTANCE[0].displayName,
            readOnly    : true,
            shouldBeAllocatedAsResource : true,
        })
    }
    else if(rtdma_instance == "RTDMA2"){
        globalConfig.push({
            name        : "dmaBase",
            displayName : "RTDMA Instance",
            description : 'RTDMA Instance used.',
            default     : DMA_INSTANCE[1].displayName,
            readOnly    : true,
            shouldBeAllocatedAsResource : true,
        })
    }

    globalConfig.push( 
        {
            name        : "emulationMode",
            displayName : "Emulation Mode",
            description : "Set emulation mode for the selected channel.",
            hidden      : false,
            default     : device_driverlib_peripheral.DMA_EmulationMode[0].name,
            options     : device_driverlib_peripheral.DMA_EmulationMode,
            shouldBeAllocatedAsResource : true,
        },
        {
            name        : "enableSoftwarePriority",
            displayName : "Enable Software priority",
            description : "Enable Software configurable priority",
            hidden      : false,
            default     : false,
            shouldBeAllocatedAsResource : true,
            // onChange    : onChangePriorityMode
        },
        {
            name        : "lockDMAConfig",
            displayName : "Lock DMA Configuration",
            description : "Lock the DMA Configuration registers.",
            hidden      : false,
            default     : false,
            shouldBeAllocatedAsResource : true,
        },
        {
            name        : "commitDMAConfig",
            displayName : "Commit DMA Configuration",
            description : "Commit the lock on the DMA Configuration registers.",
            hidden      : false,
            default     : false,
            shouldBeAllocatedAsResource : true,
        },
        {
            name        : "enableMPU",
            displayName : "Enable MPU",
            description : 'Enable MPU',
            hidden      : false,
            default     : false,
            shouldBeAllocatedAsResource : true,
        }, 
    );

    if(Common.isContextCPU1()) {
        globalConfig.push(
            {
                name: "GROUP_SYS",
                displayName: "System Configuration",
                collapsed: true,
                config: []
            },
            {
                name: "GROUP_ESM",
                displayName: "Error Signaling Configuration",
                collapsed: true,
                config: [
                {
                    name        : "configureESMforLPERR",
                    displayName : "Configure Error Signaling for LPERR",
                    description : 'Configure the handling of RTDMA Error aggregator LPERR',
                    hidden      : false,
                    default     : false
                },
                {
                    name        : "configureESMforHPERR",
                    displayName : "Configure Error Signaling for HPERR",
                    description : 'Configure the handling of RTDMA Error aggregator HPERR',
                    hidden      : false,
                    default     : false
                }]
            },
        )
    }

    return globalConfig
}

function getRTDMAConfig(rtdma_instance){
    // if(rtdma_instance != "RTDMA1" && rtdma_instance != "RTDMA2"){
    //     throw new Error("INVALID RTDMA INSTANCE")
    // }

    var chOptions;

    if(rtdma_instance == "RTDMA1"){
        chOptions = CHANNEL_INSTANCE.slice(0,10)
    }
    else {
        chOptions = CHANNEL_INSTANCE.slice(10,20)
    }

    let config = [
        {
            name: "GROUP_PERCFG",
            displayName: "Peripheral Configuration",
            collapsed: false,
            config: [
                {
                    name        : "chBase",
                    displayName : "DMA Channel",
                    description : 'DMA Channel used.',
                    hidden      : false,
                    default     : chOptions[0].name,
                    options     : chOptions,
                    shouldBeAllocatedAsResource: true,
                },  
                {
                    name        : "peripheralRXLinked",
                    displayName : "Channel is linked to a peripheral for receive from DMA.",
                    description : '',
                    hidden      : true,
                    default     : false,
                    onChange    : onChangePeripheralRXLinked
                },

                {
                    name        : "peripheralTXLinked",
                    displayName : "Channel is linked to a peripheral for transmit to DMA.",
                    description : '',
                    hidden      : true,
                    default     : false,
                    onChange    : onChangePeripheralTXLinked
                },

                {
                    name        : "channelPriority",
                    displayName : "Channel Priority",
                    description : "Software configurable priority of the channel",
                    hidden      : false, 
                    default     : device_driverlib_peripheral.DMA_ChannelPriority[1].name,
                    options     : device_driverlib_peripheral.DMA_ChannelPriority,
                    shouldBeAllocatedAsResource : true,
                },

                {
                    name        : "enableTriggers",
                    displayName : "Enable Triggers",
                    description : "Enable triggers for the selected channel.",
                    hidden      : false,
                    default     : false,
                },

                {
                    name        : "triggerSource",
                    displayName : "Trigger Source",
                    description : "Set trigger source for the selected channel.",
                    hidden      : false,
                    default     : device_driverlib_peripheral.DMA_Trigger[0].name,
                    options     : device_driverlib_peripheral.DMA_Trigger
                },

                {
                    name        : "oneShotConfig",
                    displayName : "One-Shot Configuration",
                    description : "Configuration options for the selected channel.",
                    hidden      : false,
                    default     : device_driverlib_peripheral.DMA_CFG_ONESHOT[0].name,
                    options     : device_driverlib_peripheral.DMA_CFG_ONESHOT
                },

                {
                    name        : "continuousModeConfig",
                    displayName : "Continuous Mode Configuration",
                    description : "Configuration options for the selected channel.",
                    hidden      : false,
                    default     : device_driverlib_peripheral.DMA_CFG_CONTINUOUS[0].name,
                    options     : device_driverlib_peripheral.DMA_CFG_CONTINUOUS
                },

                {
                    name        : "burstSignalingModeConfig",
                    displayName : "Burst Signaling Mode Configuration",
                    description : "Configuration options for the selected channel.",
                    hidden      : false,
                    default     : device_driverlib_peripheral.DMA_BurstSignalingMode[0].name,
                    options     : device_driverlib_peripheral.DMA_BurstSignalingMode
                },

                {
                    name        : "databusWidthConfig",
                    displayName : "Read Datasize",
                    description : "Read datasize configuration options for the selected channel.",
                    hidden      : false,
                    default     : device_driverlib_peripheral.DMA_CFG_READ_SIZE[0].name,
                    options     : device_driverlib_peripheral.DMA_CFG_READ_SIZE
                },

                {
                    name        : "writeDatasizeConfig",
                    displayName : "Write Datasize",
                    description : "Write datasize configuration options for the selected channel.",
                    hidden      : false,
                    default     : device_driverlib_peripheral.DMA_CFG_WRT_SIZE[0].name,
                    options     : device_driverlib_peripheral.DMA_CFG_WRT_SIZE
                },

                {
                    name        : "burstSize",
                    displayName : "Burst Size (number of bytes per burst)",
                    description : "Set number of bytes to transfer with each burst.",
                    hidden      : false,
                    default     : 1,
                },

                {
                    name        : "transferSize",
                    displayName : "Transfer Size (number of bursts per transfer)",
                    description : "Set number of bursts per transfer.",
                    hidden      : false,
                    default     : 1,
                },

                {
                    name        : "numberBytesToTransfer",
                    displayName : "Number of bytes of data to be transferred",
                    hidden      : false,
                    readOnly    : true,
                    default     : 1,
                    getValue    : calculateBytesToTransfer,
                },

                {
                    name        : "startChannel",
                    displayName : "Start Channel",
                    description : "Start channel immediately at runtime.",
                    hidden      : false,
                    default     : false,
                }, 

                {
                    name: "GROUP_SRC_ADDRESS",
                    displayName: "Source Address Setup",
                    description: "Source address setup options",
                    longDescription: "",
                    config: [
                        {
                            name        : "srcAddressInputMode",
                            displayName : "Source Address Input Type",
                            description : 'Type of source address input.',
                            hidden      : false,
                            default     : ADDRESS_INPUT_MODE[0].name,
                            options     : ADDRESS_INPUT_MODE,
                            onChange    : onChangeSrcAddressInputMode
                        },
                
                        {
                            name        : "srcAddressManual",
                            displayName : "Source Address",
                            description : 'The source address (hexadecimal if using "0x" prefix)',
                            hidden      : false,
                            displayFormat: "hex",
                            default     : 0x00
                        },
                    
                        {
                            name        : "srcAddressVariable",
                            displayName : "Source Address Variable",
                            description : "Void pointer to function/variable of source address.",
                            hidden      : true,
                            default     : "",
                        },
                    
                        {
                            name        : "srcAddressLinked",
                            displayName : "Source Address Of Linked Peripheral",
                            description : "Static source address of linked peripheral",
                            hidden      : true,
                            default     : "",
                        },
                    
                        {
                            name        : "srcBurstStep",
                            displayName : "Source Address Burst Step",
                            description : "Amount to increment (positive) or decrement (negative) source address after each word of burst. Note: step size will occur in 8-bit increments regardless of databus width.",
                            hidden      : false,
                            default     : 0,
                        },
                    
                        {
                            name        : "srcTransferStep",
                            displayName : "Source Address Transfer Step",
                            description : "Amount to increment (positive) or decrement (negative) source address after completing the current burst transfer. Note: step size will occur in 8-bit increments regardless of databus width.",
                            hidden      : false,
                            default     : 0,
                        },
                    
                        {
                            name        : "srcWrapSize",
                            displayName : "Source Wrap Size",
                            description : "Set number of bursts before wrap on source address occurs.",
                            hidden      : false,
                            default     : 65536,
                        },
                    
                        {
                            name        : "srcWrapStep",
                            displayName : "Source Address Wrap Step",
                            description : "Amount to increment (positive) or decrement (negative) source address after wrap counter reaches 0. Note: step size will occur in 8-bit increments regardless of databus width.",
                            hidden      : false,
                            default     : 0,
                        },
                    ]
                },
            
                {
                    name: "GROUP_DEST_ADDRESS",
                    displayName: "Destination Address Setup",
                    description: "Destination address setup options",
                    longDescription: "",
                    config: [
                        {
                            name        : "destAddressInputMode",
                            displayName : "Destination Address Input Type",
                            description : 'Type of destination address input.',
                            hidden      : false,
                            default     : ADDRESS_INPUT_MODE[0].name,
                            options     : ADDRESS_INPUT_MODE,
                            onChange    : onChangeDestAddressInputMode
                        },
                    
                        {
                            name        : "destAddressManual",
                            displayName : "Destination Address",
                            description : 'The source address (hexadecimal if using "0x" prefix)',
                            hidden      : false,
                            displayFormat: "hex",
                            default     : 0x00
                        },
                    
                        {
                            name        : "destAddressVariable",
                            displayName : "Destination Address Variable",
                            description : "Void pointer to function/variable of destination address.",
                            hidden      : true,
                            default     : "",
                        },
                    
                        {
                            name        : "destAddressLinked",
                            displayName : "Destination Address Of Linked Peripheral",
                            description : "Static destination address of linked peripheral",
                            hidden      : true,
                            default     : "",
                        },
                    
                        {
                            name        : "destBurstStep",
                            displayName : "Destination Address Burst Step",
                            description : "Amount to increment (positive) or decrement (negative) destination address after each word of burst. Note: step size will occur in 8-bit increments regardless of databus width.",
                            hidden      : false,
                            default     : 0,
                        },
                    
                        {
                            name        : "destTransferStep",
                            displayName : "Destination Address Transfer Step",
                            description : "Amount to increment (positive) or decrement (negative) destination address after completing the current burst transfer. Note: step size will occur in 8-bit increments regardless of databus width.",
                            hidden      : false,
                            default     : 0,
                        },
                    
                        {
                            name        : "destWrapSize",
                            displayName : "Destination Wrap Size",
                            description : "Set number of bursts before wrap on destination address occurs.",
                            hidden      : false,
                            default     : 65536,
                        },
                    
                        {
                            name        : "destWrapStep",
                            displayName : "Destination Address Wrap Step",
                            description : "Amount to increment (positive) or decrement (negative) destination address after wrap counter reaches 0. Note: step size will occur in 8-bit increments regardless of databus width.",
                            hidden      : false,
                            default     : 0,
                        },
                    ]
                },
            
                {
                    name        : "lockChannelConfig",
                    displayName : "Lock Channel Configuration",
                    description : "Lock the current DMA channel Configuration registers.",
                    hidden      : false,
                    default     : false,
                },
                
                {
                    name        : "commitChannelConfig",
                    displayName : "Commit Channel Configuration",
                    description : "Commit the lock on the current DMA channel Configuration registers.",
                    hidden      : false,
                    default     : false,
                },
            ]
        },

        {
            name: "GROUP_INTERRUPT",
            displayName: "Interrupt Configuration",
            collapsed: true,
            config: [
                {
                    name        : "useInterrupts",
                    displayName : "Use Interrupt",
                    onChange    : onChangeUseInterrupts,
                    description : 'Whether or not to use Interrupt mode.',
                    hidden      : false,
                    default     : false,
                },
        
                {
                    name        : "registerInterrupts",
                    displayName : "Register Interrupt Handler",
                    description : 'Whether or not to register interrupt handlers in the interrupt module.',
                    hidden      : true,
                    default     : false,
                },
                {
                    name        : "enableInterrupts",
                    displayName : "Enable Interrupts",
                    description : "Enable the DMA channel's CPU interrupt.",
                    hidden      : true,
                    default     : false,
                },

                {
                    name        : "enableOverrunInterrupt",
                    displayName : "Enable Overrun Interrupt",
                    description : "Determines whether the DMA module generates a CPU interrupt when it detects an overflow event.",
                    hidden      : true,
                    default     : false,
                },

                {
                    name        : "interruptMode",
                    displayName : "Interrupt Mode",
                    description : "Set interrupt mode for the selected channel.",
                    hidden      : true,
                    default     : device_driverlib_peripheral.DMA_InterruptMode[0].name,
                    options     : device_driverlib_peripheral.DMA_InterruptMode
                }
            ]
        }];
    
    return config
}


function calculateBytesToTransfer(inst, ui)
{
    var nBytes = 0
    nBytes = Math.ceil(inst.burstSize / (datasize_map[inst.databusWidthConfig]/8)) * (datasize_map[inst.databusWidthConfig]/8) * inst.transferSize        
    return nBytes
}

function onValidate(inst, validation)
{
    var usedDMAChInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedDMAChInsts.push(instance_obj.chBase);
    }

    var otherContexts = Common.getOtherContextNames()
    for (var cntx of otherContexts)
    {
        var onOtherCntx = Common.getModuleForCore(inst.$module.$name, cntx);
        if (onOtherCntx)
        {
            for (var instance_index in onOtherCntx.$instances)
            {
                var instance_obj = onOtherCntx.$instances[instance_index];
                usedDMAChInsts.push(instance_obj.chBase);
            }
        }
    }
    
    var duplicatesResult = Common.findDuplicates(usedDMAChInsts)
    
    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ")
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "This DMA channel is already in use! Duplicates: " + allDuplicates,
            inst, "chBase");
    }
    
    if (datasize_map[inst.writeDatasizeConfig] > datasize_map[inst.databusWidthConfig] ){
        validation.logError("Write data size must be less than or equal to the read data size and the read data size must be an integral multiple of write data size!", inst, "writeDatasizeConfig");
    }

    if (inst.numberBytesToTransfer != inst.transferSize*inst.burstSize){
        validation.logError("The burst size must be aligned with the read data size!", inst, "burstSize");
    }

    if (inst.burstSize > 256 || inst.burstSize < 1 || !Number.isInteger(inst.burstSize)) {
        validation.logError("Burst size must be an integer between 1 and 256!", inst, "burstSize");
    }

    if (inst.srcBurstStep > 4095 || inst.srcBurstStep < -4096 || !Number.isInteger(inst.srcBurstStep)) {
        validation.logError("Source address step size must be an integer between -4096 and 4095!", inst, "srcBurstStep");
    }

    if (inst.destBurstStep > 4095 || inst.destBurstStep < -4096 || !Number.isInteger(inst.destBurstStep)) {
        validation.logError("Destination address step size must be an integer between -4096 and 4095!", inst, "destBurstStep");
    }

    if (inst.srcTransferStep > 4095 || inst.srcTransferStep < -4096 || !Number.isInteger(inst.srcTransferStep)) {
        validation.logError("Source address step size must be an integer between -4096 and 4095!", inst, "srcTransferStep");
    }

    if (inst.destTransferStep > 4095 || inst.destTransferStep < -4096 || !Number.isInteger(inst.destTransferStep)) {
        validation.logError("Destination address step size must be an integer between -4096 and 4095!", inst, "destTransferStep");
    }

    if (inst.srcWrapStep > 4095 || inst.srcWrapStep < -4096 || !Number.isInteger(inst.srcWrapStep)) {
        validation.logError("Source address step size must be an integer between -4096 and 4095!", inst, "srcWrapStep");
    }

    if (inst.destWrapStep > 4095 || inst.destWrapStep < -4096 || !Number.isInteger(inst.destWrapStep)) {
        validation.logError("Destination address step size must be an integer between -4096 and 4095!", inst, "destWrapStep");
    }

    if (inst.transferSize > 65536 || inst.transferSize < 1 || !Number.isInteger(inst.transferSize)) {
        validation.logError("Transfer size must be an integer between 1 and 65,536!", inst, "transferSize");
    }

    if (inst.srcWrapSize > 65536 || inst.srcWrapSize < 1 || !Number.isInteger(inst.srcWrapSize)) {
        validation.logError("Source address wrap size must be an integer between 1 and 65,536!", inst, "srcWrapSize");
    }

    if (inst.destWrapSize > 65536 || inst.destWrapSize < 1 || !Number.isInteger(inst.destWrapSize)) {
        validation.logError("Destination address wrap size must be an integer between 1 and 65,536!", inst, "destWrapSize");
    }

    if (inst.oneShotConfig == device_driverlib_peripheral.DMA_CFG_ONESHOT[1].name && inst.channelPriority == 0) {
        validation.logError("One-Shot mode and High-priority mode must not be used at the same time on channel 1!", inst, "enablePriority");   
    }

    if (inst.peripheralTXLinked == 0 && inst.destAddressInputMode == INPUT_MODE_LINKED) {
        validation.logError("Linking to a peripheral must be configured as a submodule of that peripheral!", inst, "destAddressInputMode");   
    }

    if (inst.peripheralRXLinked == 0 && inst.srcAddressInputMode == INPUT_MODE_LINKED) {
        validation.logError("Linking to a peripheral must be configured as a submodule of that peripheral!", inst, "srcAddressInputMode");   
    }

    if (inst.peripheralTXLinked == 0 && inst.peripheralRXLinked == 0 && inst.triggerSource == "DMA_TRIGGER_LINKED") {
        validation.logError("Linking to a peripheral must be configured as a submodule of that peripheral!", inst, "triggerSource");   
    }
}

function onValidateStatic(mod, validation)
{
    validation.logInfo("The RTDMA global configurations are done in CPU1 only. The individual channels can be added and configured in any CPU context.", mod);

    if (Common.isContextCPU1()) {
        validation.logInfo("High Priority Error types: Security violation (DW/ DR), Access timeout error (DW/ DR), Access ACK error (DW/ DR), Uncorrectable error (DR).", mod, "configureESMforHPERR");
        validation.logInfo("Low Priority Error types: Correctable error (DR).", mod, "configureESMforLPERR");
    }

    if (mod.enableMPU == false)
    {
        validation.logInfo("The RTDMA MPU is enabled at reset in hardware. To disable MPU, the checkbox here is used.", mod, "enableMPU");
    }

    if ((mod.enableMPU == true) && (Common.isModuleOnAnyContext(mod.$name.replace(".js", "_mpu.js")) == false))
    {
        validation.logWarning("RTDMA MPU is enabled here. The RTDMA MPU module is to be added in CPU1 for configurations.", mod, "enableMPU");
    }
}

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["RTDMA"]));
}


var sharedModuleInstances = undefined;

var rtdma_shared = {
    getRTDMAConfig        : getRTDMAConfig,
    getRTDMAGlobalConfig  : getRTDMAGlobalConfig,
    onValidate            : onValidate,
    onValidateStatic      : onValidateStatic,
};

exports = rtdma_shared;


