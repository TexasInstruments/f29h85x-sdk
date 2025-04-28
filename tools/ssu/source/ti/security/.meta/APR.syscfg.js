const Common = system.getScript('/ti/security/Common.js');
const Cmn    = system.getScript("/driverlib/Common.js");

const cpuData           = system.getScript('/ti/security/device_specific_information/cpu_data.js');
const memoryData        = system.getScript('/ti/security/device_specific_information/memory_data.js');
const ssuData           = system.getScript('/ti/security/device_specific_information/ssu_data.js');
const peripheralData    = system.getScript('/ti/security/device_specific_information/peripheral_data.js');


let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
    Cmn.getDeviceName().toLowerCase() + "_memmap.js");

let dmaMpu_instances = [];
for (let dmampu of device_driverlib_memmap.DMAMPUMemoryMap) {
    dmaMpu_instances.push({
        name : dmampu.name,
        displayName : dmampu.displayName
    })
}

function needExtAP(inst)
{
    if(inst.type == "Peripheral")
    {
        let selectedPeriphs = peripheralData.getPeriphsSortedbyFrame()
                                    .filter(x=> inst.peripherals.includes(x.name))
        if(selectedPeriphs.length > 1)
        {
            if((selectedPeriphs[0].start >> 28) != (selectedPeriphs[selectedPeriphs.length -1].start >> 28))
                return true
        }
    }
    else
    {
        if(inst.memType == "ExtMemory")
            return true
    }
    return false
}

let config_static = [
    {
        name             : 'cpuMarker',
        default          : 1,
        hidden           : true,
        getValue         : (inst, ui) => {
            if(Cmn.isContextCPU1()) return 1;
            if(Cmn.isContextCPU2()) return 2;
            if(Cmn.isContextCPU3()) return 3;
            return -1;
        }
    },
    /* {
        name            : "hsmRamSize",
        displayName     : "RAM memory reserved for HSM (in kB)",
        longDescription : "This memory is reserved for HSM functionality, and will not be available for application.\
                            Memory will be reserved in LDA RAM",
        default         : 0,
    }, */
   {
        name       : "bankMode",
        displayName: "Bank Mode",
        hidden     : !Cmn.isContextCPU1(),
        default    : 0,
        options    : [
            {name : 0, displayName : "MODE0 : Only CPU1, No FOTA"},
            {name : 1, displayName : "MODE1 : Only CPU1, FOTA Enabled"},
            {name : 2, displayName : "MODE2 : CPU1/CPU3 split, No FOTA"},
            {name : 3, displayName : "MODE3 : CPU1/CPU3 split, FOTA Enabled"}
        ],
    },
    {
        name       : "nmiVectorAddress",
        displayName: "NMI Vector Address",
        longDescription: `Use this field to place the ${system.context} NMI Vector at a specific address (This will override any auto-assigned address if present). To auto-assign the vector address, set this field to 0x0.`,
        hidden     : Cmn.isContextCPU1(),
        default    : 0x0,
        displayFormat: "hex"
    },
    {
        name       : "resetVectorAddress",
        displayName: "Reset Vector Address",
        longDescription: `Use this field to place the ${system.context} Reset Vector at a specific address (This will override any auto-assigned address if present). To auto-assign the vector address, set this field to 0x0.`,
        hidden     : Cmn.isContextCPU1(),
        default    : 0x0,
        displayFormat: "hex"
    },
]

let config = [
    {
        name             : 'specialAprStatus',
        default          : "none",
        hidden           : true,
        options          : Common.getSpecialAprList()
    },
    {
        name             : 'diffContext',
        default          : false,
        hidden           : true,
    },
    {
        name             : 'diffContextName',
        default          : "",
        hidden           : true,
    },
    {
        displayName: "Type",
        name       : 'type',
        default    : "Code",
        options          : () => {
            let typeOptions = [
                { name: "Code"},
                { name: "Data"},
                { name: "Peripheral"},
            ]
            let sysSec = Common.modStaticByCPU('/ti/security/System_Security', "CPU1");
            if(sysSec){
                return typeOptions;
            }
            return typeOptions.filter(m => m.name != "Peripheral")
        },
        onChange   : (inst,ui) => {
            ui.peripherals.hidden   = !(inst.type == "Peripheral");
            ui.memType.hidden       = (inst.type == "Peripheral");
            ui.memSize.hidden       = (inst.type == "Peripheral");
            ui.share.hidden    = (inst.memType != "RAM") || (inst.type == "Peripheral")
            if(inst.type != "Peripheral" && inst.memType == "RAM")
                ui.zeroWS.hidden = false;
            else
                ui.zeroWS.hidden = true;
        }
    },
    {
        name          : 'useExtAP',
        default       : false,
        hidden        : true,
        readOnly      : true,
        getValue      : (inst)=> { return needExtAP(inst)}
    },
    {
        displayName   : "Peripherals",
        name          : 'peripherals',
        hidden        : true,
        default       : [],
        minSelections : 0,
        options       : () => {return peripheralData.getPeriphsSortedbyFrame().map(x=> { return {name: x.name}})},
    },
    {
        displayName   : "Memory Placement",
        name          : 'placement',
        collapsed     : false,
        config        : [
            {
                name             : 'memType',
                displayName      : 'Memory Type',
                default          : memoryData.memTypes[0].name,
                options          : () => {
                    let sysSec = Common.modStaticByCPU('/ti/security/System_Security', "CPU1");
                    if(sysSec && sysSec.ssumode != 1){
                        return memoryData.memTypes;
                    }
                    return memoryData.memTypes.filter(m => m.name != "ExtMemory")
                },
                onChange         : (inst, ui) => {
                    ui.zeroWS.hidden   = inst.memType != "RAM";
                    ui.share.hidden    = (inst.memType != "RAM") || (inst.type == "Peripheral");
                    if(inst.memType == "Flash")
                        inst.dmaMpuInst = dmaMpu_instances[0].name
                }
            },
            {
                name             : 'memSize',
                displayName      : 'Memory Size (in kB)',
                default          : 4,
            },
            {
                name             : 'zeroWS',
                displayName      : 'Use 0 WS Memory only',
                default          : true,
            },
            {
                name             : 'weprot',
                displayName      : 'weprot',
                default           : 0,
                hidden          : true,
                getValue        : (inst, ui) => {
                    if(inst.memType != "Flash") return 0
                    return Common.getAprWeprotVal(inst.$name, inst.type, inst.$module.$static.cpuMarker)    //!! Calc in backend
                }
            },
            {
                name             : 'startAddr',
                displayName      : 'Start Address',
                default          : 0x0,
                displayFormat    : "hex",
                getValue         : (inst, vo) => {
                    if((inst.type != "Peripheral") && inst.memSize <= 0 )
                        return 0;
                    if((inst.type != "Peripheral") && (inst.memSize % 4 != 0) )
                        return 0;
                    if(inst.type == "Peripheral") {
                        let periphList = peripheralData.peripheralList.filter(p => inst.peripherals.includes(p.name))
                        return (periphList.length > 0) ? periphList[0].start : 0
                    }
                    else {
                        let aprList = Common.allocateAllMemoryRegions()
                        let addedContext = inst.diffContext ? inst.diffContextName : system.context
                        if(!aprList || !aprList[addedContext]) return 0;
                        let aprInfo = aprList[addedContext].filter(apr =>(apr.memRegion && (apr.memRegion.$name == inst.$name))) //!! replace with direct instance comparison
                        if(aprInfo.length && aprInfo[0].startAddr > 0)
                            return aprInfo[0].startAddr
                        return 0;
                    }

                }
            },
            {
                name             : 'endAddr',
                displayName      : 'End Address',
                default          : 0x0,
                displayFormat    : "hex",
                getValue         : (inst, vo) => {
                    if((inst.type != "Peripheral") && inst.memSize <= 0 )
                        return 0;
                    if((inst.type != "Peripheral") && (inst.memSize % 4 != 0) )
                        return 0;
                    if(inst.type == "Peripheral") {
                        let periphList = peripheralData.peripheralList.filter(p => inst.peripherals.includes(p.name))
                        return (periphList.length > 0) ? periphList[periphList.length -1].end - 1 : 0
                    }
                    else {
                        let aprList = Common.allocateAllMemoryRegions()
                        let addedContext = inst.diffContext ? inst.diffContextName : system.context
                        if(!aprList || !aprList[addedContext]) return 0;
                        let aprInfo = aprList[addedContext].filter(apr =>(apr.memRegion && (apr.memRegion.$name == inst.$name))) //!! replace with direct instance comparison
                        if(aprInfo.length && (aprInfo[0].endAddr > 0))
                            return aprInfo[0].endAddr - 1
                        return 0;
                    }

                }
            },
            {
                name             : 'share',
                displayName      : 'Share with other cores',
                options          : () => Common.getCoreList(1).map(x=> { return {name:x.name}}).filter(x => x.name!=system.context),
                default          : [],
                hidden           : false,
                minSelections    : 0,
            },
            {
                name          : "isAutoSharedRegion",
                description   : "Internal use. If true, certain configs are hidden/locked",
                //onChange      : onChangeIsAutoSharedRegion,
                default       : false,
                hidden        : true
            },
        ]
    },
    {
        displayName      : "Other Configurations",
        name             : "other",
        collapsed        : false,
        config           : [
            {
                name             : 'dmampu',
                displayName      : 'Create equivalent RTDMA MPU region',
                hidden           : true,
                default          : false,
                onChange         : (inst, ui) => {
                    if(inst.dmampu)
                        ui.dmaMpuInst.hidden = false;
                    else
                        ui.dmaMpuInst.hidden = true;
                }
            },
            {
                name        : "dmaMpuInst",
                displayName : "RTDMA MPU instance to be used",
                description : "Choose the RTDMA MPU instance to be configured",
                hidden      : true,
                default     : dmaMpu_instances[0].name,
                options     : (inst, ui) => {
                    if(inst.memType == "Flash") return dmaMpu_instances.slice(0,1)
                    return dmaMpu_instances
                },
            },
            {
                name          : "isShared",
                displayName   : "Shared region",
                description   : "Is this memory region shared between multiple cores",
                //onChange      : onChangeIsShared,
                default       : false,
                hidden        : true
            },
        ]
    },
];

let staticModuleInstances = (inst) => {
    let modules = []

    if(system.context == "CPU1"){
        modules.push({
            name        : "APR_RESERVED_sign_CPU1",
            moduleName  : "/ti/security/APR",
            collapsed   : true,
            hidden      : false,
            requiredArgs: {
                $name           : "APR_RESERVED_sign_CPU1",
                type            : "Data",
                memType         : "Flash",
                memSize         : 4,
                specialAprStatus: "signature_CPU1"
            }
        })
    }

    return modules;
}

let moduleInstances = (inst) => {
    let mods = []

    if(inst.dmampu) {
        let inst_file = inst.dmaMpuInst.split("_")[0].toLowerCase()
        mods.push({
            name: inst.$name + "_mpu",
            displayName: "RTDMA MPU Region",
            moduleName: `/driverlib/${inst_file}_mpu.js`,
            requiredArgs: {
                $name : inst.$name + "_MPU_REGION",
                startAddressInputMode: "MANUAL",
                endAddressInputMode: "MANUAL",
                memoryTiedRegion: true,
                memoryTiedRegionTag: inst.$name
            },
            collapsed: false,
        })
    }
    return mods
}

function validateStatic(inst, vo){
    // Validate user-configured address ranges
    if(inst.nmiVectorAddr < 0){
        vo.logError("NMI Vector Address cannot be negative" , inst, 'nmiVectorAddr');
    }
    if(inst.resetVectorAddress < 0){
        vo.logError("Reset Vector Address cannot be negative" , inst, 'resetVectorAddress');
    }

    // validate peripheral overlap
}

function validate(inst, vo)
{
    let APRList = Common.allocateAllMemoryRegions()[system.context]
    const sysSec    = Common.modStaticByCPU('/ti/security/System_Security', "CPU1");
    let bankMode = Common.getBankModeConfig();

    // CERT name is reserved
    if(inst.$name == "CERT"){
        vo.logError("Cannot use name 'CERT' as it is a reserved memory region indicator" , inst, '$name');
    }

    if(inst.type != "Peripheral"){
        // Check if the size is 0
        if(inst.memSize == 0)
            vo.logError("Memory Size cannot be 0" , inst, 'memSize');

        // Check if the size if multiple of 4kB
        if(inst.memSize % 4 != 0)
            vo.logError("Memory Size should be multiple of 4kB" , inst, 'memSize');

        if(inst.startAddr == 0 || inst.endAddr == 0){
            if(inst.zeroWS && inst.memType != "Flash")
                vo.logError("Zero state memory not available" , inst, 'memSize');
            else
                vo.logError("Memory not available" , inst, 'memSize');
        }
    }
    else{
        // Check if the peripherals selected are contiguous
        let sorted_periphs = peripheralData.peripheralList.map(x=>x.name)   //?? check
        if(!Common.isContiguous(sorted_periphs, inst.peripherals))
            vo.logError("Peripherals selected should be contiguous" , inst, 'peripherals');


        // Check if same Peripheral is used in multiple APRs
        if(APRList){
            APRList
                .filter(apr => (apr.type == "Peripheral" && apr.name != inst.$name))
                .forEach(apr => {
                inst.peripherals.forEach(p => {
                    if(apr.peripheralList.includes(p))
                        vo.logError(`Peripheral ${p} already used in ${apr.name}` , inst, 'peripherals');
                })
            })
        }
    }

    // Flash DMA MPU instance validation
    if((inst.dmampu) && (inst.memType == "Flash") && (inst.dmaMpuInst != dmaMpu_instances[0].name))
        vo.logError(`Flash APR can only use ${dmaMpu_instances[0].name}` , inst, 'dmaMpuInst');

    // APR belonging to different context
    if((inst.diffContext) && (inst.diffContextName != system.context)){
        vo.logInfo(`Memory Region will be added on ${inst.diffContextName}`, inst) 
    }

    if(sysSec){
        if(sysSec.ssumode != 1){
            // Check if the numbers of APRs that needs AP_EXT is more than available ones
            let ext_apr = Common.modInstances('/ti/security/APR').filter(apr => apr.useExtAP)   //!! Move to sysec
            if(ext_apr.length > ssuData.instanceCount.EXT_APR)
            {
                if(inst.useExtAP) {
                    if(inst.type == "Peripheral")
                        vo.logError("This requires extended APR and the device only supports " + ssuData.instanceCount.EXT_APR + " extended APRs. Consider splitting this into 2 APRs"  , inst, 'peripherals');
                    else
                        vo.logError("This requires extended APR and the device only supports " + ssuData.instanceCount.EXT_APR + " extended APRs."  , inst, 'memType');
                }
            }

            // Check for total count of APRs is done in System Security module
        }
    }
    else{
        if(inst.type == "Peripheral"){
            vo.logError("Current configuration does not require peripheral memory regions", inst, 'type');
        }
    }

    // Flash access availability checks
    if(inst.memType == "Flash" && system.context == Common.CONTEXT_CPU2 && inst.$name != "APR_FlashLoad_CPU2")
    {
        vo.logError("Cannot create flash regions on current core", inst, 'memType')
    }
    if(inst.memType == "Flash" && system.context == Common.CONTEXT_CPU3 && inst.$name != "APR_FlashLoad_CPU3" && bankMode < 2 )
    {
        vo.logError("Cannot create flash regions on current core", inst, 'memType')
    }
    
}

exports = {
    displayName        : 'Memory Region',
    defaultInstanceName: 'Mem_',
    moduleStatic : {
        validateStatic,
        config : config_static,
        //moduleInstances : staticModuleInstances
    },
    moduleInstances: moduleInstances,
    templates: {
        '/ti/security/templates/linker.security.cmd.xdt': true,
    },
    validate,
    config,

};
