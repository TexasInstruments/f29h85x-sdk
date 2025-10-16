const Common            = system.getScript('/ti/security/Common.js');
const peripheralData    = system.getScript('/ti/security/device_specific_information/peripheral_data.js');
const ssuData           = system.getScript('/ti/security/device_specific_information/ssu_data.js');
const currentContext    = system.context;

let check = Common.isAllocationSetupMode() ? true : false
let config_Global =
{
    name        : "globalInfo",
    displayName : "Global Settings",
    collapsed   : false,
    config      :
    [
        {
            name        : "ssumode",
            displayName : "SSU Mode",
            default     : 1,
            hidden      : check ? false : !Common.isContextCPU1(),
            options     : [1,2,3].map(x => {return {name:x, displayName:"SSUMODE"+x.toString()};}),
            onChange    : (inst, ui) =>
            {
                // ui.inter_security_context_behavior.hidden = inst.ssumode != 3;
                config_debugAccess.config.forEach(x => { x.config.forEach(y => {ui[y.name].hidden = inst.ssumode != 3})})

                ui.dltLinks.hidden = (inst.ssumode>1) ? false : true
            },
            shouldBeAllocatedAsResource: true,
        },
        {
            name             : 'cpuList',
            displayName      : "Cores enabled",
            default          : [],
            hidden           : check ? false : !Common.isContextCPU1(),
            options          : () =>
            {
                return Common.getCoreList(1).filter(x => { return x.name != Common.CONTEXT_CPU1 })
            },
            minSelections    : 0,
            shouldBeAllocatedAsResource: true,
        },
        {
            name        : "uppRev",
            displayName : "UPP Revision",
            hidden      : check ? false : !Common.isContextCPU1(),
            default     : 0,
            shouldBeAllocatedAsResource: true,
        },
        {
            name        : 'cpuMarker',
            default     : 1,
            hidden      : true,
            getValue    : (inst, ui) =>
            {
                if(Common.isContextCPU1(inst)) return 1;
                if(Common.isContextCPU2(inst)) return 2;
                if(Common.isContextCPU3(inst)) return 3;
                return 0;
            },
            shouldBeAllocatedAsResource: true,
        },
    ]
}

let config_SecurityMode =
{
    name        : "mode",
    displayName : "Security Mode",
    collapsed   : false,
    config      :
    [
        {
            name        : "inter_security_context_behavior",
            displayName : "Cross Security Context Call Behavior",
            default     : 'error',
            hidden      : true,
            options     :
            [
                { name : 'error',   displayName : 'Generate an Error'},
                { name : 'autofix', displayName : 'Auto Convert To Protected Call'},
            ],
            shouldBeAllocatedAsResource: true,
        },
        {
            name        : "updateCtr",
            displayName : "SECCFG Update Counter",
            hidden      : true,
            default     : "FFFFFFFFFFFFFFFF",
            shouldBeAllocatedAsResource: true,
        },
    ]
}

let config_WEPROT =
{
    name        : "flashWEPROT",
    displayName : "Flash Write/Erase Protections",
    collapsed   : true,
    config      :
    [
        {
            name        : 'WEPROT_CODE_BANKS',
            displayName : 'Write/Erase Protection for Code Banks',
            default     : false,
            hidden      : check ? false : !Common.isContextCPU1(),
            shouldBeAllocatedAsResource: true,
        },
        {
            name        : 'WEPROT_DATA_BANKS',
            displayName : 'Write/Erase Protection for Data Banks',
            default     : false,
            hidden      : check ? false : !Common.isContextCPU1(),
            shouldBeAllocatedAsResource: true,
        },
        {
            name        : 'WEPROT_APRs',
            displayName : 'Write/Erase Protection for Memory Regions (selected sectors)',
            default     : [],
            options     : (inst, ui) =>
            {
                let corePrefix = Common.getCurrentCorePrefix(inst)
                let reqdContext = check ? corePrefix.slice(0,-1) : currentContext;
                let aprs =  Common
                            .allocateAllMemoryRegions()[reqdContext].filter(x => x.memType == "Flash")
                            .map(x => {return {name: x.name}})
                            .sort((a,b) => a.name - b.name)

                if(Common.isContextCPU1(inst))
                {
                    if(inst.WEPROT_CODE_BANKS && inst.WEPROT_DATA_BANKS)
                        return []
                    else if(inst.WEPROT_CODE_BANKS)
                        return aprs.filter(x => x.type == "Data")
                    else
                        return aprs
                }
                else{
                    let ss = Common.modStaticByCPU(`/ti/security/${corePrefix}System_Security`, "CPU1");
                    if(!ss) return []
                    if(ss.WEPROT_CODE_BANKS && ss.WEPROT_DATA_BANKS)
                        return []
                    else if(ss.WEPROT_CODE_BANKS)
                        return aprs.filter(x => x.type == "Data")
                    else
                        return aprs
                }
            },
            shouldBeAllocatedAsResource: true,
        },
    ]
}

let config_debugAccess =
{
    name        : 'DebugAccess',
    displayName : "Debug Access (SSU MODE 3 Only)",
    collapsed   : true,
    config      :
    [
        {
            name        : 'C29DebugLock',
            displayName : "C29 Debug Lock",
            collapsed   : false,
            config      :
            [
                {
                    name        : 'C29DBGEN_CFG',
                    displayName : 'C29 Debug Unlock Configuration',
                    hidden      : true,
                    default     : 2,
                    options     :
                    [
                        { name: 1, displayName : "CPU based"},
                        { name: 2, displayName : "Password based"},
                        { name: 4, displayName : "Disable C29 Debug"},
                    ],
                    onChange    : (inst, ui) =>
                    {
                        ui.C29DBGEN_PSWD.hidden = inst.C29DBGEN_CFG != 2;
                    },
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'C29DBGEN_PSWD',
                    hidden      : true,
                    displayName : 'Password',
                    default     : "55555555555555555555555555555555",
                    shouldBeAllocatedAsResource: true,
                },
            ]
        },
    ]
};

["ZONE1", "ZONE2", "ZONE3"].forEach (x =>
{
    config_debugAccess.config.push
    ({
        name        : 'Zone' + x + "Debug",
        displayName :  x + " Debug Lock",
        collapsed   : false,
        config      :
        [
            {
                name        : x + '_DEBUG_CFG',
                displayName : 'ZONE Debug Unlock Configuration',
                hidden      : true,
                default     : 2,
                options     :
                [
                    { name: 1, displayName: "CPU based"},
                    { name: 2, displayName: "Password based"},
                    { name: 4, displayName: "Disable debug"},
                ],
                onChange    : (inst, ui) =>
                {
                    ui[x + "_FDBGPSWD"].hidden = inst[x + '_DEBUG_CFG'] != 2;
                    ui[x + "_PDBGPSWD"].hidden = inst[x + '_DEBUG_CFG'] != 2;
                },
                shouldBeAllocatedAsResource: true,
            },
            {
                name        : x + '_PDBGPSWD',
                hidden      : true,
                displayName : 'Partial debug password',
                default     : "55555555555555555555555555555555",
                shouldBeAllocatedAsResource: true,
            },
            {
                name        : x + '_FDBGPSWD',
                hidden      : true,
                displayName : 'Full debug password',
                default     : "55555555555555555555555555555555",
                shouldBeAllocatedAsResource: true,
            },
        ]
    })
})

let config_flashUpdateOwner =
{
    name        : 'FlashUpdateOwner',
    displayName : "Flash Update Owner",
    collapsed   : true,
    config      : []
};

["SECCFG", "ZONE1", "ZONE2", "ZONE3"].forEach ((x) =>
{
    config_flashUpdateOwner.config.push
    ({
        name        : x + "UpdateOwner" ,
        displayName : x + " Update Owner",
        collapsed   : false,
        config      :
        [
            {
                name        : x + '_UPDATE_EN',
                displayName : 'Enable update',
                hidden      : check ? false : !Common.isContextCPU1(),
                default     : true,
                shouldBeAllocatedAsResource: true,
            },
            {
                name        : x + '_UPDATE_CPU',
                displayName : 'Update Owner CPU',
                hidden      : check ? false : !Common.isContextCPU1(),
                default     : 1,
                options     :
                [
                    { name: 0, displayName :"CPU-HSM"},
                    { name: 1, displayName :"CPU1"},
                    { name: 2, displayName :"CPU2"},
                    { name: 3, displayName :"CPU3"},
                ],
                shouldBeAllocatedAsResource: true,
            },
            {
                name            :  x + '_UPDATE_LINK',
                displayName     : 'Update Owner LINK',
                hidden          : check ? false : !Common.isContextCPU1(),
                options         : (inst) => {let corePrefix = Common.getCurrentCorePrefix(inst); return Common.modInstances(`/ti/security/${corePrefix}Link`, inst)},
                hideNoneOption  : true,
                //shouldBeAllocatedAsResource: true,
            },
        ]
    })
})

let config_bootSettings =
{
    name        : 'BootSetting',
    displayName : "Boot Settings",
    collapsed   : true,
    config      :
    [
        {
            name        : 'BootConfig',
            displayName : "Boot configuration",
            collapsed   : false,
            config      :
            [
                {
                    name        : 'EMU_BOOTEN',
                    displayName : 'Enable emulation boot',
                    hidden      : check ? false : !Common.isContextCPU1(),
                    default     : false,
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'LPOST_EN',
                    displayName : 'LPOST Enable',
                    hidden      : check ? false : !Common.isContextCPU1(),
                    default     : "00",
                    options     :
                    [
                        {name : "00", displayName : "Run LPOST with PLL disabled (10MHz INTOSC)"},
                        {name : "01", displayName : "Run LPOST with high shift frequency"},
                        {name : "10", displayName : "Run LPOST with medium shift frequency"},
                        {name : "11", displayName : "Do not run LPOST"}
                    ],
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'LPOST_COVER',
                    displayName : 'LPOST Coverage',
                    hidden      : check ? false : !Common.isContextCPU1(),
                    default     : "01",
                    options     :
                    [
                        {name : "01", displayName : "≥ 60% coverage (ASIL-B configuration)"},
                        {name : "10", displayName : "≥ 80% coverage (ASIL-C configuration)"},
                        {name : "11", displayName : "≥ 90% coverage (ASIL-D configuration)"},
                    ],
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'MPOST_EN',
                    displayName : 'MPOST Enable',
                    hidden      : check ? false : !Common.isContextCPU1(),
                    default     : "00",
                    options     :
                    [
                        {name : "00", displayName : "Run MPOST with PLL disabled (10MHz INTOSC)"},
                        {name : "01", displayName : "Run MPOST at PLLCLK"},
                        {name : "10", displayName : "Run MPOST at PLLCLK/2"},
                        {name : "11", displayName : "Do not run MPOST"},
                    ],
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'ERROR_STS_PIN',
                    displayName : 'Error Status Pin',
                    hidden      : check ? false : !Common.isContextCPU1(),
                    default     : 219,
                    options     :
                    [
                        {name:255,  displayName: "None"},
                        {name:4,    displayName: "GPIO4"},
                        {name:79,   displayName: "GPIO79"},
                        {name:80,   displayName: "GPIO80"},
                        {name:219,  displayName: "GPIO219"},
                        {name:247,  displayName: "GPIO247"},
                    ],
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'BOOT_LOADER_LOCK',
                    displayName : 'Lock the ROM Boot loaders',
                    hidden      : check ? false : !Common.isContextCPU1(),
                    default     : false
                },
                {
                    name        : 'ENABLE_XTAL',
                    displayName : 'Enable XTAL during boot time',
                    hidden      : check ? false : !Common.isContextCPU1(),
                    default     : '0xFF',
                    options     :
                    [
                        {name:"0xC9", displayName: "Enable Crystal Mode"},
                        {name:"0x9C", displayName: "Enable Single ended Mode"},
                        {name:"0xFF", displayName: "Disable XTAL"},
                    ],
                    shouldBeAllocatedAsResource: true,
                },
            ]
        },
        {
            name        : 'BootPinConfig',
            displayName : "Boot pin configuration",
            collapsed   : false,
            config      :
            [
                {
                    name        : 'defaultBootmode',
                    displayName : 'Use default boot modes',
                    hidden      : check ? false : !Common.isContextCPU1(),
                    default     : true,
                    onChange    : (inst, ui) =>
                    {
                        let defBM = inst.defaultBootmode

                        if(defBM)
                        {
                            inst.bootPinCount   = 2
                            ui.BMSP0.hidden     = false
                            ui.BMSP1.hidden     = false
                            ui.BMSP2.hidden     = true
                            inst.BMSP0          = 84
                            inst.BMSP1          = 72
                            ui.BOOTDEF0.hidden  = false
                            ui.BOOTDEF1.hidden  = false
                            ui.BOOTDEF2.hidden  = false
                            ui.BOOTDEF3.hidden  = false
                            ui.BOOTDEF4.hidden  = true
                            ui.BOOTDEF5.hidden  = true
                            ui.BOOTDEF6.hidden  = true
                            ui.BOOTDEF7.hidden  = true
                            inst.BOOTDEF0       = '00'
                            inst.BOOTDEF1       = '01'
                            inst.BOOTDEF2       = '02'
                            inst.BOOTDEF3       = '03'
                        }

                        ui.bootPinCount.readOnly= defBM
                        ui.BMSP0.readOnly       = defBM
                        ui.BMSP1.readOnly       = defBM
                        ui.BMSP2.readOnly       = defBM
                        ui.BOOTDEF0.readOnly    = defBM
                        ui.BOOTDEF1.readOnly    = defBM
                        ui.BOOTDEF2.readOnly    = defBM
                        ui.BOOTDEF3.readOnly    = defBM
                        ui.BOOTDEF4.readOnly    = defBM
                        ui.BOOTDEF5.readOnly    = defBM
                        ui.BOOTDEF6.readOnly    = defBM
                        ui.BOOTDEF7.readOnly    = defBM
                    },
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'bootPinCount',
                    displayName : 'Number of Boot Pins',
                    hidden      : check ? false : !Common.isContextCPU1(),
                    default     : 2,
                    readOnly    : true,
                    options     :
                    [
                        {name: 0},
                        {name: 1},
                        {name: 2},
                        {name: 3}
                    ],
                    onChange    : (inst, ui) =>
                    {
                        let pinCount = inst.bootPinCount

                        ui.BMSP0.hidden     = pinCount == 0;
                        ui.BMSP1.hidden     = pinCount <= 1;
                        ui.BMSP2.hidden     = pinCount <= 2;
                        ui.BOOTDEF1.hidden  = pinCount == 0;
                        ui.BOOTDEF2.hidden  = pinCount <= 1;
                        ui.BOOTDEF3.hidden  = pinCount <= 1;
                        ui.BOOTDEF4.hidden  = pinCount <= 2;
                        ui.BOOTDEF5.hidden  = pinCount <= 2;
                        ui.BOOTDEF6.hidden  = pinCount <= 2;
                        ui.BOOTDEF7.hidden  = pinCount <= 2;
                    },
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'BMSP0',
                    displayName : 'Boot Pin 0 (BMSP0)',
                    hidden      : check ? false : !Common.isContextCPU1(),
                    readOnly    : true,
                    default     : 84,
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'BMSP1',
                    displayName : 'Boot Pin 1 (BMSP1)',
                    hidden      : check ? false : !Common.isContextCPU1(),
                    readOnly    : true,
                    default     : 72,
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'BMSP2',
                    displayName : 'Boot Pin 2 (BMSP2)',
                    hidden      : true,
                    readOnly    : true,
                    default     : 0xFF,
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'BOOTDEF0',
                    description : "Boot mode when the value of the GPIOs used for valid BSMP2-BSMP1-BSMP0 are 0b000",
                    hidden      : check ? false : !Common.isContextCPU1(),
                    readOnly    : true,
                    default     : "00",
                    options     : peripheralData.bootmodes,
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'BOOTDEF1',
                    description : "Boot mode when the value of the GPIOs used for valid BSMP2-BSMP1-BSMP0 are 0b001",
                    hidden      : check ? false : !Common.isContextCPU1(),
                    readOnly    : true,
                    default     : "01",
                    options     : peripheralData.bootmodes,
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'BOOTDEF2',
                    description : "Boot mode when the value of the GPIOs used for valid BSMP2-BSMP1-BSMP0 are 0b010",
                    hidden      : check ? false : !Common.isContextCPU1(),
                    readOnly    : true,
                    default     : "02",
                    options     : peripheralData.bootmodes,
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'BOOTDEF3',
                    description : "Boot mode when the value of the GPIOs used for valid BSMP2-BSMP1-BSMP0 are 0b011",
                    hidden      : check ? false : !Common.isContextCPU1(),
                    readOnly    : true,
                    default     : "03",
                    options     : peripheralData.bootmodes,
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'BOOTDEF4',
                    description : "Boot mode when the value of the GPIOs used for valid BSMP2-BSMP1-BSMP0 are 0b100",
                    hidden      : true,
                    readOnly    : true,
                    default     : "00",
                    options     : peripheralData.bootmodes,
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'BOOTDEF5',
                    description : "Boot mode when the value of the GPIOs used for valid BSMP2-BSMP1-BSMP0 are 0b101",
                    hidden      : true,
                    readOnly    : true,
                    default     : "00",
                    options     : peripheralData.bootmodes,
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'BOOTDEF6',
                    description : "Boot mode when the value of the GPIOs used for valid BSMP2-BSMP1-BSMP0 are 0b110",
                    hidden      : true,
                    readOnly    : true,
                    default     : "00",
                    options     : peripheralData.bootmodes,
                    shouldBeAllocatedAsResource: true,
                },
                {
                    name        : 'BOOTDEF7',
                    description : "Boot mode when the value of the GPIOs used for valid BSMP2-BSMP1-BSMP0 are 0b111",
                    hidden      : true,
                    readOnly    : true,
                    default     : "00",
                    options     : peripheralData.bootmodes,
                    shouldBeAllocatedAsResource: true,
                },
            ]
        },
    ]
}

let config_registerLocks =
{
    name        : 'registerLocks',
    displayName : "Register Lock & Commit",
    collapsed   : true,
    config      :
    [
        {
            name                : 'disableAPR',
            displayName         : 'Disable APR registers',
            default             : [],
            options             : (inst) =>
            {
                let reqdContext = check ? Common.getCurrentCorePrefix(inst).slice(0,-1) : currentContext;
                return Common.allocateAllMemoryRegions()[reqdContext].map(x => {return {name: x.name}})
            },
            disableSelectAll    : true,
            shouldBeAllocatedAsResource: true,
        },
        {
            name                : 'lockAPR',
            displayName         : 'Lock APR registers',
            default             : [],
            options             : (inst) =>
            {
                let reqdContext = check ? Common.getCurrentCorePrefix(inst).slice(0,-1) : currentContext;
                return Common.allocateAllMemoryRegions()[reqdContext].map(x => {return {name: x.name}})
            },
            disableSelectAll    : true,
            shouldBeAllocatedAsResource: true,
        },
        {
            name                : 'commitAPR',
            displayName         : 'Commit APR registers',
            default             : [],
            options             : (inst) =>
            {
                let reqdContext = check ? Common.getCurrentCorePrefix(inst).slice(0,-1) : currentContext;
                return Common.allocateAllMemoryRegions()[reqdContext].map(x => {return {name: x.name}})
            },
            disableSelectAll    : true,
            shouldBeAllocatedAsResource: true,
        },
        {
            name        : 'LockUnusedAPRs',
            displayName : 'Lock the unused APR registers',
            default     : false,
            shouldBeAllocatedAsResource: true,
        },
        {
            name        : 'CommitUnusedAPRs',
            displayName : 'Commit the unused APR registers',
            default     : false,
            shouldBeAllocatedAsResource: true,
        },
        {
            name        : 'DEBUG_CFG_LOCK',
            displayName : 'Lock DEBUG_CFG register',
            hidden      : check ? false : !Common.isContextCPU1(),
            default     : false,
            shouldBeAllocatedAsResource: true,
        },
        {
            name        : 'DEBUG_CFG_COMMIT',
            displayName : 'Commit DEBUG_CFG register',
            hidden      : check ? false : !Common.isContextCPU1(),
            default     : false,
            shouldBeAllocatedAsResource: true,
        },
        {
            name            : 'lockWEPROTRegs',
            displayName     : 'Lock WEPROT registers',
            hidden          : check ? false : !Common.isContextCPU1(),
            default         : [],
            minSelections   : 0,
            options         :
            [
                {name: "WEPROT_CODE_BANKS"},
                {name: "WEPROT_DATA_BANKS"},
                {name: "WEPROT_FLC1_B0"},
                {name: "WEPROT_FLC1_B2"},
                {name: "WEPROT_FLC2_B0"},
                {name: "WEPROT_FLC2_B2"},
            ],
            shouldBeAllocatedAsResource: true,
        },
        {
            name            : 'commitWEPROTRegs',
            displayName     : 'Commit WEPROT registers',
            hidden          : check ? false : !Common.isContextCPU1(),
            default         : [],
            minSelections   : 0,
            options         :
            [
                {name: "WEPROT_CODE_BANKS"},
                {name: "WEPROT_DATA_BANKS"},
                {name: "WEPROT_FLC1_B0"},
                {name: "WEPROT_FLC1_B2"},
                {name: "WEPROT_FLC2_B0"},
                {name: "WEPROT_FLC2_B2"},
            ],
            shouldBeAllocatedAsResource: true,
        },
        {
            name        : 'RAMOPEN_LOCK',
            displayName : 'Lock RAMOPEN register',
            hidden      : check ? false : !Common.isContextCPU1(),
            default     : false,
            shouldBeAllocatedAsResource: true,
        },
        {
            name        : 'RAMOPEN_COMMIT',
            displayName : 'Commit RAMOPEN register',
            hidden      : check ? false : !Common.isContextCPU1(),
            default     : false,
            shouldBeAllocatedAsResource: true,
        },
    ]
}

let config_misc =
{
    name        : 'miscSettings',
    displayName : "Other Settings",
    collapsed   : true,
    config      :
    [
        {
            name        : 'dltLinks',
            displayName : 'Links with DLT write permission',
            hidden      : true,
            options     : (inst) => {let corePrefix = Common.getCurrentCorePrefix(inst); return Common.modInstances(`/ti/security/${corePrefix}Link`, inst)},
            isArray     : true,
            //shouldBeAllocatedAsResource: true,
        },
    ]
}

let config_ssu =
{
    name        : "SSUSettings",
    displayName : 'SSU Setup',
    collapsed   : false,
    style       : "tab",
    config      :
    [
        {
            name            : "flashLoadSize",
            displayName     : "Flash size used as Load memory (in kB)",
            longDescription : "This is used for as Load memory for functions and RO sections in RAM and for storing cinit section copy tables",
            default         : !Common.isContextCPU2() ? 4 : 0,
            shouldBeAllocatedAsResource: true,
        },
        {
            name            : "addStack1",
            displayName     : "Add Custom Bootloader Sandbox",
            longDescription : "Enables STACK1 (Bootloader STACK) for application usage",
            default         : true,
            shouldBeAllocatedAsResource: true,
        },
        {
            name            : "addStack2",
            displayName     : "Add Secure Root Sandbox",
            longDescription : "Enables STACK2 (Secure Root STACK) in application",
            default         : true,
            getValue        : () => true
        },
        {
            name            : "addLink1",
            displayName     : "Auto-configure Bootloader Module",
            longDescription : "Boot ROM requires certain peripheral APRs to be pre-configured for LINK1 access. Unchecking will force manual creation of LINK1 & peripheral APRs. If this Module has been modified, toggling/re-checking causes the selected peripherals to reset to the default configuration. LINK can also be used in application if required",
            default         : true,
            shouldBeAllocatedAsResource: true,
        },
        {
            name            : "addLink2",
            displayName     : "Add Secure Root Module",
            longDescription : "Add LINK2 (Most secure LINK) with code and data APRs",
            default         : true,
            shouldBeAllocatedAsResource: true,
        },
        {
            name            : "addCommonCodeModule",
            displayName     : "Add Common Code Module",
            longDescription : "Libraries or functions which are called across modules can be placed in this module. This modules inherits the caller module's accesses to memory regions and peripherals",
            default         : true,
            shouldBeAllocatedAsResource: true,
        },
        {
            name            : "specialModules",
            displayName     : "Special Modules",
            style           : "tab",
            config          : [],
        },
        {
            name            : "specialSandboxes",
            displayName     : "Special Sandboxes",
            style           : "tab",
            config          : [],
        }
    ],
}

let config_ssu_setup_main_core =
{
    name        : "SSUSettings",
    displayName : 'SSU Setup',
    collapsed   : false,
    style       : "tab",
    config      :
    [
        {
            name            : "flashLoadSize",
            displayName     : "Flash size used as Load memory (in kB)",
            longDescription : "This is used for as Load memory for functions and RO sections in RAM and for storing cinit section copy tables",
            default         : 4,
            shouldBeAllocatedAsResource: true,
        },
        {
            name            : "addStack1",
            displayName     : "Add Custom Bootloader Sandbox",
            longDescription : "Enables STACK1 (Bootloader STACK) for application usage",
            default         : true,
            shouldBeAllocatedAsResource: true,
        },
        {
            name            : "addStack2",
            displayName     : "Add Secure Root Sandbox",
            longDescription : "Enables STACK2 (Secure Root STACK) in application",
            default         : true,
            getValue        : () => true
        },
        {
            name            : "addLink1",
            displayName     : "Auto-configure Bootloader Module",
            longDescription : "Boot ROM requires certain peripheral APRs to be pre-configured for LINK1 access. Unchecking will force manual creation of LINK1 & peripheral APRs. If this Module has been modified, toggling/re-checking causes the selected peripherals to reset to the default configuration. LINK can also be used in application if required",
            default         : true,
            shouldBeAllocatedAsResource: true,
        },
        {
            name            : "addLink2",
            displayName     : "Add Secure Root Module",
            longDescription : "Add LINK2 (Most secure LINK) with code and data APRs",
            default         : true,
            shouldBeAllocatedAsResource: true,
        },
        {
            name            : "addCommonCodeModule",
            displayName     : "Add Common Code Module",
            longDescription : "Libraries or functions which are called across modules can be placed in this module. This modules inherits the caller module's accesses to memory regions and peripherals",
            default         : true,
            shouldBeAllocatedAsResource: true,
        },
        {
            name            : "specialModules",
            displayName     : "Special Modules",
            style           : "tab",
            config          : [],
        },
        {
            name            : "specialSandboxes",
            displayName     : "Special Sandboxes",
            style           : "tab",
            config          : [],
        }
    ],
}

let config_additional_aprs =
{
    name        : "addlAprs",
    displayName : 'Auto-Generated Regions',
    collapsed   : true,
    config      : []
}

let config_coreAssignment =
[
    {
        name        : "$assignedContext",
        description : 'Override the assigned context to have only in CPU1',
        hidden      : true,
        default     : "CPU1",
        options     : [{name:"CPU1"}],
		readOnly    : true
    },
]

let configStatic =
[
    {
        name        : "generalSettings",
        displayName : "General settings",
        collapsed   : false,
        config      :
        [
            config_Global,
            config_SecurityMode,
            config_bootSettings,
            config_debugAccess,
            config_flashUpdateOwner,
            config_WEPROT,
            config_registerLocks,
            config_misc
        ],
    },
    config_ssu,
    config_additional_aprs
]

let config_main_core =
[   ...config_coreAssignment,
    {
        name        : "generalSettings",
        displayName : "General settings",
        collapsed   : false,
        config      :
        [
            config_Global,
            config_SecurityMode,
            config_bootSettings,
            config_debugAccess,
            config_flashUpdateOwner,
            config_WEPROT,
            config_registerLocks,
            config_misc
        ],
    },
    config_ssu_setup_main_core,
    config_additional_aprs
]



function moduleInstances(inst)
{
    let corePrefix  = Common.getCurrentCorePrefix(inst)
    let corePermaPrefix = check ? corePrefix : currentContext + "_"
    let modules     = []

    // Reserved Flash APR for signature
    if(Common.isContextCPU1(inst))
    {
        modules.push
        ({
            name        : "APR_RESERVED_sign_CPU1",
            displayName : "Flash Certificate APR",
            moduleName  : `/ti/security/${corePrefix}APR`,
            collapsed   : true,
            hidden      : false,
            group       : "addlAprs",
            requiredArgs:
            {
                $name           : "APR_RESERVED_sign_CPU1",
                type            : "Data",
                memType         : "Flash",
                memSize         : 4,
                specialAprStatus: "signature_CPU1"
            }
        })
    }

    if(Common.isContextCPU3(inst))
    {
        modules.push
        ({
            name        : "APR_RESERVED_sign_CPU3",
            displayName : "Flash Certificate APR",
            moduleName  : `/ti/security/${corePrefix}APR`,
            collapsed   : true,
            hidden      : false,
            group       : "addlAprs",
            requiredArgs:
            {
                $name           : "APR_RESERVED_sign_CPU3",
                type            : "Data",
                memType         : "Flash",
                memSize         : 4,
                specialAprStatus: "signature_CPU3"
            }
        })
    }

    // Default APR for flashload
    if(inst.flashLoadSize != 0)
    {
        modules.push
        ({
            name        : "APR_FlashLoad",
            displayName : "CPU" + String(inst.cpuMarker) + " Flash Load APR",
            moduleName  : `/ti/security/${corePrefix}APR`,
            collapsed   : true,
            hidden      : false,
            group       : "addlAprs",
            requiredArgs:
            {
                $name           : "APR_FlashLoad_CPU"+String(inst.cpuMarker),
                type            : "Data",
                memType         : "Flash",
                memSize         : inst.flashLoadSize,
                /* diffContext     : true,
                diffContextName : "CPU1", */
                specialAprStatus: "flash_load_CPU"+String(inst.cpuMarker)
            }
        })
    }

    // Modules with no Instances
    modules.push
    ({
        name        : "module",
        displayName : "Application Module",
        moduleName  : `/ti/security/${corePrefix}EasyMode_link`,
        useArray    : true,
        style       : "tab",
        group       : "SSUSettings",
    })

    // Add LINK2 module to special modules
    if(inst.addLink2)
    {
        modules.push
        ({
            name        : "LINK2",
            displayName : "Secure Root Module",
            moduleName  : `/ti/security/${corePrefix}EasyMode_link`,
            group       : "specialModules",
            collapsed   : true,
            requiredArgs:
            {
                $name   : corePermaPrefix + "LINK2",
                isLink2 : true
            },
            args        :
            {
                periphs_rw  : Common.getLink2RequiredAprs()
            }
        })
    }

    // Add common code module to special modules
    if(inst.addCommonCodeModule)
    {
        modules.push
        ({
            name        : "CommonCodeModule",
            displayName : "Common Code Module",
            moduleName  : `/ti/security/${corePrefix}EasyMode_link`,
            collapsed   : true,
            group       : "specialModules",
            collapsed   : true,
            requiredArgs:
            {
                $name       : corePermaPrefix + "CommonCodeModule",
                isCommonCode: true
            },
            args        :
            {
                //fileNames : "error",
                libs    : "libc.a,libclang_rt.builtins.a,driverlib.lib"
            }
        })
    }

    if(inst.addLink1)
    {
        modules.push
        ({
            name        : "LINK1",
            displayName : "Bootloader Module",
            moduleName  : `/ti/security/${corePrefix}EasyMode_link`,
            group       : "specialModules",
            collapsed   : true,
            requiredArgs:
            {
                $name : corePermaPrefix + "LINK1",
                isLink1 : true
            },
            args        :
            {
                codesizeFlash   : 0,
                codesizeRAM     : 0,
                rodatasize      : 0,
                rwdatasize      : 0,
                datasize        : 0,
                periphs_rw      : Common.isContextCPU1(inst) ? Common.getBootPeripherals(inst) : []
            }
        })
    }

    if(inst.addStack1)
    {
        modules.push
        ({
            name        : "STACK1",
            displayName : "Custom Bootloader Sandbox",
            moduleName  : `/ti/security/${corePrefix}EasyMode_stack`,
            group       : "specialSandboxes",
            collapsed   : true,
            requiredArgs:
            {
                $name   : corePermaPrefix + "STACK1",
                zone    : "ZONE1",
            },
            args        :
            {
                modules : inst.addLink1 ? [corePermaPrefix + "LINK1_Link"] : []
            }
        })
    }

    // Add STACK2
    modules.push
    ({
        name        : "STACK2",
        displayName : "Secure Root Sandbox",
        moduleName  : `/ti/security/${corePrefix}EasyMode_stack`,
        group       : "specialSandboxes",
        collapsed   : true,
        requiredArgs:
        {
            $name   : corePermaPrefix + "STACK2",
            zone    : "ZONE1",
        },
        args        :
        {
            modules : inst.addLink2 ? [corePermaPrefix + "LINK2_Link"] : []
        }
    })

    // Sandboxes with no default Instances
    modules.push
    ({
        name        : "sandbox",
        displayName : "Sandbox",
        style       : "tab",
        moduleName  : `/ti/security/${corePrefix}EasyMode_stack`,
        useArray    : true,
        group       : "SSUSettings",
    })

    // SharedMem with no default Instances
    modules.push
    ({
        name        : "sharedMem",
        displayName : "Shared Memory",
        style       : "tab",
        moduleName  : `/ti/security/${corePrefix}EasyMode_sharedMem`,
        useArray    : true,
        group       : "SSUSettings",
    })

    if(Common.isContextCPU1(inst) == true)
    {
        inst.cpuList.forEach(core =>
        {
            if(core == "CPU2")
            {
                modules.push
                ({
                    name        : "CPU2_FLASH_REGION",
                    displayName : "CPU2 Flash Load APR",
                    moduleName  : `/ti/security/${corePrefix}APR`,
                    collapsed   : true,
                    hidden      : false,
                    group       : "addlAprs",
                    args        :
                    {
                        memSize : 64,
                    },
                    requiredArgs:
                    {
                        $name   : "CPU2_FLASH_REGION",
                        type    : "Data",
                        memType : "Flash",
                    }
                })
            }
        })
    }

    return modules;
}

function config_resources(core){
return  [
            {
                name    : 'r_linkIds',
                default : "",
                shouldBeAllocatedAsResource: true,
                hidden  : true,
                getValue: (inst) => {
                    let a = Common.assignLinkID_configure(core)
                    return JSON.stringify(a)
                }
            },
            {
                name    : 'r_stackIds',
                default : "",
                shouldBeAllocatedAsResource: true,
                hidden  : true,
                getValue: (inst) => {
                    let a = Common.assignStackID_configure(core)
                    return JSON.stringify(a)
                }
            },
            {
                name    : 'r_aprMap',
                default : "",
                shouldBeAllocatedAsResource: true,
                hidden  : true,
                getValue: (inst) => {
                    let ret = {}
                    let aprList = Common.allocateAllMemoryRegions()[core]
                    aprList.forEach(apr => {
                        ret[apr.name] = 
                        {
                            "linkAccess": Common.getLinkAccess_configure(apr, core),
                            "exeLink": (Common.getExeLink_configure(apr, core)) ? Common.getExeLink_configure(apr, core).$name : null,
                            "apiLink": (Common.getAPILink_configure(apr, core)) ? Common.getAPILink_configure(apr, core).$name : null,
                        }
                    })
                    return JSON.stringify(ret)
                }
            },
            {
                name    : 'r_linkMap',
                default : "",
                shouldBeAllocatedAsResource: true,
                hidden  : true,
                getValue: (inst) => {
                    let ret = {}
                    let links = Common.modInstances(`/ti/security/${core}_Link`);
                    links.forEach(link => {
                        ret[link.$name] = 
                        {
                            "stackName": (Common.getStack_configure(link, core)) ? Common.getStack_configure(link, core).$name : null,
                            "isLink1": link.isLink1,
                            "isLink2": link.isLink2,
                        }
                    })
                    return JSON.stringify(ret)
                }
            },
            {
                name    : 'r_stackMap',
                default : "",
                shouldBeAllocatedAsResource: true,
                hidden  : true,
                getValue: (inst) => {
                    let ret = {}
                    let stacks = Common.modInstances(`/ti/security/${core}_Stack`);
                    stacks.forEach(stack => {
                        ret[stack.$name] = 
                        {
                            "zoneName": (Common.getZone_configure(stack, core)) ? Common.getZone_configure(stack, core) : null,
                        }
                        if(stack.$name == `${core}_STACK2_STACK`)
                            ret[stack.$name]["size"] = stack.size
                    })
                    return JSON.stringify(ret)
                }
            },
            {
                name    : 'r_updateOwners',
                default : "",
                shouldBeAllocatedAsResource: true,
                hidden  : true,
                getValue: (inst) => {
                    let ret = {}
                    let SS_CPU1 = Common.modStaticByCPU(`/ti/security/System_Security`, Common.CONTEXT_CPU1);
                    ["SECCFG", "ZONE1", "ZONE2", "ZONE3"].forEach(x => {
                        ret[x+'_UPDATE_LINK'] = SS_CPU1[x+'_UPDATE_LINK']?.$name ??  null
                    })
                    return JSON.stringify(ret)
                }
            },
            {
                name    : 'r_dltLinks',
                default : "",
                shouldBeAllocatedAsResource: true,
                hidden  : true,
                getValue: (inst) => {
                    let ret = []
                    let dltLinks = Common.getConfigFromStaticModule(`/ti/security/System_Security`, "dltLinks", core);
                    if(dltLinks.available){
                        dltLinks.value.forEach(link => {
                            ret.push(link.$name)
                        })
                    }
                    return JSON.stringify(ret)
                }
            },
        ]
}

function validate(inst, vo)
{
    let reqdContext = check ? Common.getCurrentCorePrefix(inst).slice(0,-1) : currentContext;
    let aprList     = Common.allocateAllMemoryRegions()[reqdContext]
    let coresValid  = Common.getCoreList(1).map(c => {return c.name})

    // CHECK: # of APRs
    if(aprList && aprList.length > ssuData.instanceCount.APR)
    {
        vo.logError(`Maximum APR count of ${ssuData.instanceCount.APR} exceeded`, inst)
    }

    // CHECK: Corelist validation
    if(Common.isContextCPU1(inst))
    {
        let invalidcoreList = _.difference(inst.cpuList, coresValid)
        if(invalidcoreList.length)
            vo.logError("Invalid core(s) selected: " + invalidcoreList.join(","), inst, 'cpuList')
    }
    // CHECK:  Curernt core should be enabled on CPU1
    else
    {
        let coresEnabled = Common.getConfigFromStaticModule("/ti/security/System_Security", "cpuList", Common.CONTEXT_CPU1)
        if(!coresEnabled.available)
        {
            vo.logError("System Security module not enabled on CPU1 (or) Cannot find CPU1 context!", inst)
        }
        else
        {
            if(!coresEnabled.value.includes(reqdContext))
                vo.logError("Current core is not enabled by System Security module on CPU1", inst)
        }
    }

    // CHECK: Bankmode >= 2 for CPU3 usage
    if(Common.isContextCPU3(inst))
    {
        let bankmode = Common.getConfigFromStaticModule("/ti/security/APR", "bankMode", Common.CONTEXT_CPU1)
        if(!bankmode.available)
        {
            vo.logWarning("Bankmode setting not found in CPU1", inst)
        }
        else
        {
            if(bankmode.value < 2)
                vo.logError("Bankmode must be set to 2/3 in CPU1 to use System Security on CPU3", inst)
        }
    }

    // CHECK: bootpins
    if((inst.bootPinCount > 0) && (inst.BMSP0 > 254))
        vo.logError("Enter a value between 0 and 254.", inst, 'BMSP0');

    if((inst.bootPinCount > 1) && (inst.BMSP1 > 254))
        vo.logError("Enter a value between 0 and 254.", inst, 'BMSP1');

    if((inst.bootPinCount > 2) && (inst.BMSP2 > 254))
        vo.logError("Enter a value between 0 and 254.", inst, 'BMSP2');


    // CHECK: update counter
    let format16Hex = new RegExp(/^[A-F0-9]{16}$/i);
    if(!format16Hex.test(inst.updateCtr))
        vo.logError("Invalid 16 digit hex value.", inst, 'updateCtr');

    // CHECK: uppRev
    if(inst.uppRev > 0xFFFF)
        vo.logError("UPP revision must be less than 0xFFFF", inst, 'uppRev');

    // WARNING: Log message for jtag lock on ssumode 3
    if(inst.ssumode == 3)
    {
        if(inst.C29DBGEN_CFG == 4)
            vo.logWarning("This causes C29 Debug to be disabled permanently!", inst, 'C29DBGEN_CFG');

        if(inst.C29DBGEN_CFG == 1)
            vo.logWarning("Make sure to include authentication logic into your application to enable C29 Debug. Else C29 Debug will be disabled permanently!", inst, 'C29DBGEN_CFG');

        ["ZONE1", "ZONE2", "ZONE3"].forEach (x =>
        {
            if(inst[x + '_DEBUG_CFG'] == 4)
                vo.logWarning("This causes Zone Debug to be disabled permanently.", inst, x + '_DEBUG_CFG');

            if(inst[x + '_DEBUG_CFG'] == 1)
                vo.logWarning("Make sure to include authentication logic into your application to enable ZONE Debug. Else ZONE Debug will be disabled permanently!", inst, x + '_DEBUG_CFG');
        })

        // Check passwords in ssumode 3
        let format32Hex = new RegExp(/^[A-F0-9]{32}$/i);
        if(!format32Hex.test(inst.C29DBGEN_PSWD))
            vo.logError("Invalid 32 digit hex value.", inst, 'C29DBGEN_PSWD');
        ["ZONE1", "ZONE2", "ZONE3"].forEach (x =>
        {
            if(!format32Hex.test(inst[x + '_PDBGPSWD']))
                vo.logError("Invalid 32 digit hex value.", inst, x + '_PDBGPSWD');

            if(!format32Hex.test(inst[x + '_FDBGPSWD']))
                vo.logError("Invalid 32 digit hex value.", inst, x + '_FDBGPSWD');
        })
    }

    // CHECK: LINK1 Boot peripheral APRs exist
    if(Common.isContextCPU1(inst))
    {
        const bootPeripheralList    = Common.getBootPeripherals(inst);
        let l1AddedPeripheralAprs   = []
        let addedPeripheralList     = []
        let corePrefix              = Common.getCurrentCorePrefix(inst);

        const link1Instance = Common.modInstances(`/ti/security/${corePrefix}Link`, inst).filter(x=>x.isLink1)
        if(link1Instance[0])    // If no LINK1, will always throw error
        {
            l1AddedPeripheralAprs = _.union(link1Instance[0].readwriteAPRsEasy, link1Instance[0].readwriteAPRs)
        }

        let peripheralAprs = aprList.filter(apr => ((apr.type == "Peripheral") && (l1AddedPeripheralAprs.includes(apr.name))))
        peripheralAprs.forEach(apr =>
        {
            addedPeripheralList = addedPeripheralList.concat(apr.peripheralList)
        })

        let diff = _.difference(bootPeripheralList, addedPeripheralList)
        if(diff.length > 0)
        {
            vo.logError(`LINK1 must have RW access to the following peripherals in order to boot correctly in the selected configuration:\n - ${diff.join("\n - ")}\nAdd memory regions covering these peripherals. If they already exist, allow LINK1 RW permissions via System Security / LINK module`, inst);
        }
    }

    // CHECK: LINK2 required APRs
}


exports =
{
    configStatic: configStatic,
    config_main_core: config_main_core,
    config_resources: config_resources,
    validate: validate,
    moduleInstances: moduleInstances
}