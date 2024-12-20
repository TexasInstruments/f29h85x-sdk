let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_rtdma.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

var MPU_INSTANCE = [];
for (var mpu of device_driverlib_memmap.DMAMPUMemoryMap) {
    MPU_INSTANCE.push({
        name : mpu.name,
        displayName : mpu.displayName
    })
}

let INPUT_MODE_MANUAL = "MANUAL"
let INPUT_MODE_VARIABLE = "VARIABLE"

let ADDRESS_INPUT_MODE = [
    {name: "MANUAL", displayName: "Manual"},
    // {name: "VARIABLE", displayName: "Variable Name"},
]

/* Intro splash on GUI */
let longDescription = "";


function onChangeStartAddressInputMode(inst,ui)
{
    if (inst.startAddressInputMode == INPUT_MODE_MANUAL) {
        ui.startAddressManual.hidden = false
        ui.startAddressVariable.hidden = true
    }
    if (inst.startAddressInputMode == INPUT_MODE_VARIABLE) {
        ui.startAddressManual.hidden = true
        ui.startAddressVariable.hidden = false
    }
}

function onChangeEndAddressInputMode(inst,ui)
{
    if (inst.endAddressInputMode == INPUT_MODE_MANUAL) {
        ui.endAddressManual.hidden = false
        ui.endAddressVariable.hidden = true
    }
    if (inst.endAddressInputMode == INPUT_MODE_VARIABLE) {
        ui.endAddressManual.hidden = true
        ui.endAddressVariable.hidden = false
    }
}

function getRTDMAMPUGlobalConfig(rtdma_instance)
{
    var globalConfig = [];
    if(!Common.isContextCPU1()) {
        return globalConfig
    }

    if(rtdma_instance == "RTDMA1"){
        globalConfig.push({
            name        : "mpuBase",
            displayName : "RTDMA MPU Instance",
            description : 'RTDMA MPU Instance used.',
            hidden      : false,
            default     : MPU_INSTANCE[0].displayName,
            readOnly    : true,
        })
    }
    else if(rtdma_instance == "RTDMA2"){
        globalConfig.push({
            name        : "mpuBase",
            displayName : "RTDMA MPU Instance",
            description : 'RTDMA MPU Instance used.',
            hidden      : false,
            default     : MPU_INSTANCE[1].displayName,
            readOnly    : true,
        });
    }

    globalConfig.push(
        {
            name        : "enableMPU",
            displayName : "Enable MPU",
            description : 'Enable MPU',
            hidden      : false,
            default     : true,
            // onChange    : onChangeEnableMPU,
        }, 
        {
            name        : "lockMPUConfig",
            displayName : "Lock MPU Configuration",
            description : "Lock the MPU Configuration register.",
            hidden      : false,
            default     : false,
        },

        {
            name        : "commitMPUConfig",
            displayName : "Commit MPU Configuration",
            description : "Commit the lock on the MPU Configuration register.",
            hidden      : false,
            default     : false,
        },
    )
    return globalConfig
}

function getRTDMAMPUConfig(rtdma_instance){
    // if(rtdma_instance != "RTDMA1" && rtdma_instance != "RTDMA2"){
    //     throw new Error("INVALID RTDMA INSTANCE")
    // }

    let config = [
        {
            name        : "mpuRegion",
            displayName : "MPU Region",
            description : 'MPU Region used.',
            hidden      : false,
            default     : device_driverlib_peripheral.DMA_MPURegion[0].name,
            options     : device_driverlib_peripheral.DMA_MPURegion,
        },  
        {
            name        : "startAddressInputMode",
            displayName : "Start Address Input Type",
            description : "Type of Start address input.",
            hidden      : false,
            default     : ADDRESS_INPUT_MODE[0].name,
            options     : ADDRESS_INPUT_MODE,
            onChange    : onChangeStartAddressInputMode
        },
        {
            name        : "startAddressManual",
            displayName : "Start Address (4 KB granularity)",
            description : 'The start address (hexadecimal if using "0x" prefix)',
            hidden      : false,
            displayFormat: "hex",
            default     : 0x00
        },
        {
            name        : "startAddressVariable",
            displayName : "Start Address Variable",
            description : "Void pointer to variable of start address.",
            hidden      : true,
            default     : "",
        },
        {
            name        : "endAddressInputMode",
            displayName : "End Address Input Type",
            description : "Type of End address input.",
            hidden      : false,
            default     : ADDRESS_INPUT_MODE[0].name,
            options     : ADDRESS_INPUT_MODE,
            onChange    : onChangeEndAddressInputMode
        },
        {
            name        : "endAddressManual",
            displayName : "End Address (4 KB granularity)",
            description : 'The end address (hexadecimal if using "0x" prefix)',
            hidden      : false,
            displayFormat: "hex",
            default     : 0xFFF
        },   
        {
            name        : "endAddressVariable",
            displayName : "End Address Variable",
            description : "Void pointer to variable of end address.",
            hidden      : true,
            default     : "",
        },
        {
            name        : "accessPermission",
            displayName : "Access Permission",
            hidden      : false,
            default     : device_driverlib_peripheral.DMA_MPUAccessPermission[0].name,
            options     : device_driverlib_peripheral.DMA_MPUAccessPermission,
        },
        {
            name        : "channelMask",
            displayName : "Channel Enable",
            description : "Maps the DMA channels that has access to particular MPU regions.",
            hidden      : false,
            default     : [],
            minSelections: 0,
            options     : device_driverlib_peripheral.DMA_MPU_CH,
        },
        {
            name        : "lockMPURegion",
            displayName : "Lock MPU Region Configuration",
            description : "Lock the current MPU Region Configuration registers.",
            hidden      : false,
            default     : false,
        },
        {
            name        : "commitMPURegion",
            displayName : "Commit MPU Region Configuration",
            description : "Commit the lock on the MPU Region Configuration registers.",
            hidden      : false,
            default     : false,
        },

        {
            name        : "memoryTiedRegion",
            hidden      : true,
            default     : false,
            onChange    : (inst, ui) => {
                if(inst.memoryTiedRegion){
                    ui.startAddressInputMode.hidden     = true;
                    ui.startAddressManual.hidden        = true;
                    ui.endAddressInputMode.hidden       = true;
                    ui.endAddressManual.hidden          = true;
                }
                else{
                    ui.startAddressInputMode.hidden     = false;
                    ui.startAddressManual.hidden        = false;
                    ui.endAddressInputMode.hidden       = false;
                    ui.endAddressManual.hidden          = false;
                }
            }
        },
        {
            name        : "memoryTiedRegionTag",
            hidden      : true,
            default     : "",
        },

    ]
    
    return config
}


function onValidate(inst, validation)
{
    if(!Common.isContextCPU1())
    {
        validation.logInfo("For all the MPU regions configured here, the code is generated in CPU1.", inst);
    }
    var usedMPUInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedMPUInsts.push(instance_obj.mpuRegion);
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
                usedMPUInsts.push(instance_obj.mpuRegion);
            }
        }
    }

    var duplicatesResult = Common.findDuplicates(usedMPUInsts)
    
    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ")
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "This MPU region is already in use! Duplicates: " + allDuplicates,
            inst, "mpuRegion");
    }

    if (((inst.startAddressManual & 0xFFF) != 0) || (inst.startAddressManual > 0xFFFFFFFF) || !Number.isInteger(inst.startAddressManual)) {
        validation.logError("Start address must be a 32-bit integer and follow the 4 KB granularity!", inst, "startAddressManual");
    }

    if (((inst.endAddressManual & 0xFFF) != 0xFFF) || (inst.endAddressManual > 0xFFFFFFFF) || !Number.isInteger(inst.endAddressManual)) {
        validation.logError("End address must be a 32-bit integer and should be the end of the 4 KB granular block!", inst, "endAddressManual");
    }
}

function onValidateStatic(mod, validation)
{
    validation.logInfo("RTDMA MPU global configurations are done in CPU1 only.", mod);

    let rtdmaSetting = false
    if (system.modules[mod.$name.replace("_mpu", "")])
    {
        rtdmaSetting = system.modules[mod.$name.replace("_mpu", "")].$static.enableMPU
    }

    if ((mod.enableMPU == true) && (rtdmaSetting == false)) {
        validation.logWarning("MPU is not enabled in the RTDMA module tab.", mod, "enableMPU");
    }

    if ((mod.enableMPU == false) && (rtdmaSetting == true)) {
        validation.logWarning("MPU is enabled in the RTDMA module tab but not here. Enable MPU to configure the individual MPU Regions.", mod, "enableMPU");
    }
}



var sharedModuleInstances = undefined;

var rtdma_mpu_shared = {
    getRTDMAMPUConfig       : getRTDMAMPUConfig,
    getRTDMAMPUGlobalConfig : getRTDMAMPUGlobalConfig,
    onValidate              : onValidate,
    onValidateStatic        : onValidateStatic,
};

exports = rtdma_mpu_shared;





