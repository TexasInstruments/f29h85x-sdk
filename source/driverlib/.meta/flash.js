let Common  = system.getScript("/driverlib/Common.js");
let Pinmux  = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_flash.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

/* Intro splash on GUI */
let longDescription = `Flash is an electrically erasable/programmable
 nonvolatile memory that can be programmed and erased many times to 
 ease code development. Flash memory can be used primarily as a program 
 memory for the core, and secondarily as static data memory
`;

longDescription += "*   [Device TRM](" + Common.getDeviceTRM() + ")";

var FLASH_INSTANCE = [];

FLASH_INSTANCE.push({ name: device_driverlib_memmap.FLASH0MemoryMap[0].name, displayName: device_driverlib_memmap.FLASH0MemoryMap[0].displayName });

var Flash_SysClk_MHz = 200;
Flash_SysClk_MHz = Common.getSYSCLK();

var Flash_FClk_MHz = 50;

var numberOfInstance = {
    "F29H85x"   : 1,
}

var deviceNumberOfInstances = numberOfInstance[Common.getDeviceName()];

function calcWaitState(inst, ui)
{
    Flash_SysClk_MHz = Common.getSYSCLK()
    if (["F29H85x"].includes(Common.getDeviceName()) && (0 < Flash_SysClk_MHz && Flash_SysClk_MHz <= 100)){
        return (1)
    }
    else if (["F29H85x"].includes(Common.getDeviceName()) && (100 < Flash_SysClk_MHz && Flash_SysClk_MHz <= 150)){
        return (2)
    }
    else if(["F29H85x"].includes(Common.getDeviceName()) && (150 < Flash_SysClk_MHz && Flash_SysClk_MHz <= 200)){
        return (3)
    }
    else{
        return Math.ceil((Flash_SysClk_MHz/Flash_FClk_MHz) - 1);
    }
}

let config = [
    {
        name        : "flashBase",
        displayName : "FLASH Instance",
        description : 'Instance of the FLASH used.',
        hidden      : false,
        default     : FLASH_INSTANCE[0].name,
        options     : FLASH_INSTANCE
    },
    {
        name        : "calcWaitStates",
        displayName : "Calculate Wait State [RWAIT]",
        description : '',
        hidden      : false,
        default     : true,
        onChange    : (inst, ui) => {
            ui.waitStates.hidden = inst.calcWaitStates;
            ui.calculatedWaitStates.hidden = !inst.calcWaitStates
        }
    },    
    {
        name        : "calculatedWaitStates",
        displayName : "Wait State [RWAIT]",
        description : 'Sets the number of wait states for a flash read access. The waitstates parameter is a number between 0x1 and 0xF.',
        hidden      : true,
        default     : 0xF, 
        displayFormat: {
            radix: 'hex',
            bitSize: 4
        },
        getValue : (inst, ui) => {
            return calcWaitState(inst, ui)
        }
    },
    //Flash_setWaitstates(uint32_t ctrlBase, uint16_t waitstates), set to max 0xF by default
    {
        name        : "waitStates",
        displayName : "Wait State [RWAIT]",
        description : 'Sets the number of wait states for a flash read access. The waitstates parameter is a number between 0x1 and 0xF.',
        hidden      : true,
        default     : 0xF, 
        displayFormat: {
            radix: 'hex',
            bitSize: 4
        }
    },
    //Flash_enableAllFRIsPrefetch(uint32_t ctrlBase), disabled by default
    {
        name        : "enablePrefetch",
        displayName : "Enable All FRIs Prefetch",
        description : '',
        hidden      : false,
        default     : true
    },
    //Flash_enableAllFRIsDataPreread(uint32_t ctrlBase), disabled by default
    {
        name        : "enableDataPreread",
        displayName : "Enable All FRIs Data Preread",
        description : '',
        hidden      : false,
        default     : true
    },
    //Flash_enableAllFRIsDataCache(uint32_t ctrlBase), disabled by default
    {
        name        : "enableDataCache",
        displayName : "Enable All FRIs Data Cache",
        description : '',
        hidden      : false,
        default     : true
    },
    //Flash_enableAllFRIsCodeCache(uint32_t ctrlBase), disabled by default
    {
        name        : "enableCodeCache",
        displayName : "Enable All FRIs Code Cache",
        description : '',
        hidden      : false,
        default     : true
    },
    {
        name : "FRI1_CONFIG",
        displayName: "FRI1 Configuration",
        collapsed: true,
        config: [
                    //Flash_enableFRI1Prefetch(uint32_t ctrlBase), disabled by default
                    {
                        name        : "enableFRI1Prefetch",
                        displayName : "Enable FRI1 Prefetch",
                        description : '',
                        hidden      : false,
                        default     : true
                    },
                    //Flash_enableFRI1DataPreread(uint32_t ctrlBase), disabled by default
                    {
                        name        : "enableFRI1DataPreread",
                        displayName : "Enable FRI1 Data Preread",
                        description : '',
                        hidden      : false,
                        default     : true
                    },
                    //Flash_enableFRI1DataCache(uint32_t ctrlBase), disabled by default
                    {
                        name        : "enableFRI1DataCache",
                        displayName : "Enable FRI1 Data Cache",
                        description : '',
                        hidden      : false,
                        default     : true
                    },
                    //Flash_enableFRI1CodeCache(uint32_t ctrlBase), disabled by default
                    {
                        name        : "enableFRI1CodeCache",
                        displayName : "Enable FRI1 Code Cache",
                        description : '',
                        hidden      : false,
                        default     : true
                    }
        ]
    },
    {
        name : "FRI2_CONFIG",
        displayName: "FRI2 Configuration",
        collapsed: true,
        config: [
                    //Flash_enableFRI2Prefetch(uint32_t ctrlBase), disabled by default
                    {
                        name        : "enableFRI2Prefetch",
                        displayName : "Enable FRI2 Prefetch",
                        description : '',
                        hidden      : false,
                        default     : true
                    },
                    //Flash_enableFRI2DataPreread(uint32_t ctrlBase), disabled by default
                    {
                        name        : "enableFRI2DataPreread",
                        displayName : "Enable FRI2 Data Preread",
                        description : '',
                        hidden      : false,
                        default     : true
                    },
                    //Flash_enableFRI2DataCache(uint32_t ctrlBase), disabled by default
                    {
                        name        : "enableFRI2DataCache",
                        displayName : "Enable FRI2 Data Cache",
                        description : '',
                        hidden      : false,
                        default     : true
                    },
                    //Flash_enableFRI2CodeCache(uint32_t ctrlBase), disabled by default
                    {
                        name        : "enableFRI2CodeCache",
                        displayName : "Enable FRI2 Code Cache",
                        description : '',
                        hidden      : false,
                        default     : true
                    }
        ]
    },
    {
        name : "FRI3_CONFIG",
        displayName: "FRI3 Configuration",
        collapsed: true,
        config: [
                    //Flash_enableFRI3Prefetch(uint32_t ctrlBase), disabled by default
                    {
                        name        : "enableFRI3Prefetch",
                        displayName : "Enable FRI3 Prefetch",
                        description : '',
                        hidden      : false,
                        default     : true
                    },
                    //Flash_enableFRI3DataPreread(uint32_t ctrlBase), disabled by default
                    {
                        name        : "enableFRI3DataPreread",
                        displayName : "Enable FRI3 Data Preread",
                        description : '',
                        hidden      : false,
                        default     : true
                    },
                    //Flash_enableFRI3DataCache(uint32_t ctrlBase), disabled by default
                    {
                        name        : "enableFRI3DataCache",
                        displayName : "Enable FRI3 Data Cache",
                        description : '',
                        hidden      : false,
                        default     : true
                    },
                    //Flash_enableFRI3CodeCache(uint32_t ctrlBase), disabled by default
                    {
                        name        : "enableFRI3CodeCache",
                        displayName : "Enable FRI3 Code Cache",
                        description : '',
                        hidden      : false,
                        default     : true
                    }
        ]
    },
    {
        name : "FRI4_CONFIG",
        displayName: "FRI4 Configuration",
        collapsed: true,
        config: [
                    //Flash_enableFRI4Prefetch(uint32_t ctrlBase), disabled by default
                    {
                        name        : "enableFRI4Prefetch",
                        displayName : "Enable FRI4 Prefetch",
                        description : '',
                        hidden      : false,
                        default     : true
                    },
                    //Flash_enableFRI4DataPreread(uint32_t ctrlBase), disabled by default
                    {
                        name        : "enableFRI4DataPreread",
                        displayName : "Enable FRI4 Data Preread",
                        description : '',
                        hidden      : false,
                        default     : true
                    },
                    //Flash_enableFRI4DataCache(uint32_t ctrlBase), disabled by default
                    {
                        name        : "enableFRI4DataCache",
                        displayName : "Enable FRI4 Data Cache",
                        description : '',
                        hidden      : false,
                        default     : true
                    },
                    //Flash_enableFRI4CodeCache(uint32_t ctrlBase), disabled by default
                    {
                        name        : "enableFRI4CodeCache",
                        displayName : "Enable FRI4 Code Cache",
                        description : '',
                        hidden      : false,
                        default     : true
                    }
        ]
    },
    {
        name: "GROUP_ESM",
        displayName: "Error Signaling Configuration",
        collapsed: true,
        config: [
            {
                name        : "enableErrorSignal",
                displayName : "Enable Error Signal",
                description : 'Enable Error Signal to ESM',
                hidden      : false,
                default     : false
            },
        ]
    }
];


var globalConfig = [
    
    // {
    //     name: "flashSYSCLK",
    //     displayName: "CPUCLK [MHz] for Flash Wait State Calculation",
    //     description: "This is the CPUCLK/SYSCLK value assumed for flash wait state calculation",
    //     default: Flash_SysClk_MHz,
    //     onChange : (inst, ui)=>{
    //         Flash_SysClk_MHz = inst.flashSYSCLK
    //     }
    // },
    
]

var sharedModuleInstances = undefined;

function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["FLASH"]));
}

function onValidate(inst, validation) {

    var usedFLASHInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedFLASHInsts.push(instance_obj.flashBase);
    }

    var duplicatesResult = Common.findDuplicates(usedFLASHInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ") 
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The FLASH Instance used. Duplicates: " + allDuplicates, 
            inst, "flashBase");
    }


    var waitstateConfig = inst.waitStates
    var waitstateConfigName = "waitStates"
    if (inst.calcWaitStates)
    {
        waitstateConfig = inst.calculatedWaitStates
        waitstateConfigName = "calculatedWaitStates"
    }

    if (waitstateConfig < 0x1 || waitstateConfig > 0xF ){
        validation.logError(
            "Enter a value from 0x1 to 0xF", 
            inst, waitstateConfigName);
    }

    if (waitstateConfig < Math.ceil((inst.$module.$static["flashSYSCLK"]/inst.$module.$static["flashFCLK"])) - 1){
        validation.logError(
            "Please enter a wait state value greater than or equal to the minimum required for your selected SYSCLK and FCLK", 
            inst, waitstateConfigName);
    }

    validation.logInfo(
        `It is important to look at your device's datasheet for information about what
        the required minimum flash wait state is for your selected SYSCLK frequency.
        See Flash section of TRM for more info.`, 
        inst, waitstateConfigName);
}

function onValidateStatic(inst, validation){

    if (inst.flashSYSCLK < 1 || inst.flashSYSCLK > 200 ){
        validation.logError(
            "Enter a value from 1 to 200 MHz", 
            inst, "flashSYSCLK");
    }

}

function moduleInstances(inst) {
    let components = []

    if (inst.enableErrorSignal)
    {
        components = components.concat([{
            name: "ESMConfig",
            group: "GROUP_ESM",
            displayName: "FRI Error Signaling",
            moduleName : "/driverlib/esm.js",
            collapsed: true,
            args: {
                $name        : inst.$name + "_ESM",
            },
            requiredArgs:{
                eventSource  : "ESM_EVENT_FRI_REG_PAR_ERR"
            },
        }])
    }
    return components
}

var flashModule = {

    peripheralName: "FLASH",
    displayName: "FLASH",
    maxInstances: deviceNumberOfInstances,
    defaultInstanceName: "myFMC",
    description: "FLASH",
    longDescription : longDescription,
    filterHardware: filterHardware,
    config: config,
    moduleInstances: moduleInstances,
    sharedModuleInstances : sharedModuleInstances,
    templates: {
        boardc : "/driverlib/flash/flash.board.c.xdt",
        boardh : "/driverlib/flash/flash.board.h.xdt"
    },
    moduleStatic: {
        name: "flashGlobal",
        displayName: "Flash Global",
        config: globalConfig,
        collapsed: false,
        //modules: moduleStaticModules,
        validate : onValidateStatic
    },
    validate    : onValidate
};

if (flashModule.maxInstances <= 0){
    delete flashModule.pinmuxRequirements;
}

exports = flashModule;