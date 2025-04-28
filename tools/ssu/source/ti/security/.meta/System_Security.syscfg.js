const Common = system.getScript('/ti/security/Common.js');
const Cmn    = system.getScript("/driverlib/Common.js");

const peripheralData    = system.getScript('/ti/security/device_specific_information/peripheral_data.js');
const ssuData           = system.getScript('/ti/security/device_specific_information/ssu_data.js');


let config_Global =
    {
        name       : "globalInfo",
        displayName: "Global Settings",
        collapsed  : false,
        config     : [
            {
                name       : "ssumode",
                displayName: "SSU Mode",
                default    : 1,
                hidden       : !Cmn.isContextCPU1(),
                options    : [1,2,3] .map(x => {return {name:x, displayName:"SSUMODE"+x.toString()};}),
                onChange   : (inst, ui) => {
                    // ui.inter_security_context_behavior.hidden = inst.ssumode != 3;
                    config_debugAccess.config.forEach(x => {
                        x.config.forEach (y => {ui[y.name].hidden = inst.ssumode != 3})
                    })

                    ui.dltLinks.hidden = (inst.ssumode>1) ? false : true
                }
            },
            {
                name             : 'cpuList',
                displayName      : "Cores enabled",
                default          : [],
                hidden           : !Cmn.isContextCPU1(),
                options          : () => {return Common.getCoreList(1)
                                                        .filter(x => { return x.name != Cmn.CONTEXT_CPU1
                                          })},
                minSelections    : 0,
            },
            {
                name       : "uppRev",
                displayName: "UPP Revision",
                hidden       : !Cmn.isContextCPU1(),
                default    : 0
            },
            {
                name             : 'cpuMarker',
                default          : 1,
                hidden           : true,
                getValue         : (inst, ui) => {
                    if(Cmn.isContextCPU1()) return 1;
                    if(Cmn.isContextCPU2()) return 2;
                    if(Cmn.isContextCPU3()) return 3;
                    return 0;
                }
            },
        ]
    }

let config_SecurityMode =
    {
        name       : "mode",
        displayName: "Security Mode",
        collapsed  : false,
        config     : [
            {
                name       : "inter_security_context_behavior",
                displayName: "Cross Security Context Call Behavior",
                default    : 'error',
                hidden     : true,
                options    : [
                    { name : 'error',   displayName : 'Generate an Error'},
                    { name : 'autofix', displayName : 'Auto Convert To Protected Call'},
                ]
            },
            {
                name       : "updateCtr",
                displayName: "SECCFG Update Counter",
                hidden     : true,
                default    : "FFFFFFFFFFFFFFFF",
            },
        ]
    }

if(Cmn.isContextCPU1()){
    config_SecurityMode.config.unshift(
        {
            name            : "cpu1marker",
            default         : true,
            hidden          : true,
        },
    )
}

if(Cmn.isContextCPU3()){
    config_SecurityMode.config.unshift(
        {
            name            : "cpu3marker",
            default         : true,
            hidden          : true,
        },
    )
}

let config_WEPROT =
    {
        name       : "flashWEPROT",
        displayName: "Flash Write/Erase Protections",
        collapsed  : true,
        config     : [
            {
                name         : 'WEPROT_CODE_BANKS',
                displayName  : 'Write/Erase Protection for Code Banks',
                default      : false,
                hidden       : !Cmn.isContextCPU1(),
            },
            {
                name         : 'WEPROT_DATA_BANKS',
                displayName  : 'Write/Erase Protection for Data Banks',
                default      : false,
                hidden       : !Cmn.isContextCPU1(),
            },
            {
                name         : 'WEPROT_APRs',
                displayName  : 'Write/Erase Protection for Memory Regions (selected sectors)',
                default          : [],
                options      : (inst, ui) => {
                    let aprs = Common.allocateAllMemoryRegions()[system.context].filter(x => x.memType == "Flash")
                                        .map(x => {return {name: x.name}})
                                        .sort((a,b) => a.name - b.name)
                    if(Cmn.isContextCPU1()){
                        if(inst.WEPROT_CODE_BANKS && inst.WEPROT_DATA_BANKS)
                            return []
                        else if(inst.WEPROT_CODE_BANKS)
                            return aprs.filter(x => x.type == "Data")
                        else
                            return aprs
                    }
                    else{
                        let ss = Common.modStaticByCPU("/ti/security/System_Security", "CPU1");
                        if(!ss) return []
                        if(ss.WEPROT_CODE_BANKS && ss.WEPROT_DATA_BANKS)
                            return []
                        else if(ss.WEPROT_CODE_BANKS)
                            return aprs.filter(x => x.type == "Data")
                        else
                            return aprs
                    }

                },
            },
        ]
    }

let config_debugAccess =
    {
        name       : 'DebugAccess',
        displayName: "Debug Access (SSU MODE 3 Only)",
        collapsed  : true,
        config     : [
            {
                name       : 'C29DebugLock',
                displayName: "C29 Debug Lock",
                collapsed  : false,
                config     : [
                    {
                        name         : 'C29DBGEN_CFG',
                        displayName  : 'C29 Debug Unlock Configuration',
                        hidden       : true,
                        default      : 2,
                        options      : [
                            { name: 1, displayName : "CPU based"},
                            { name: 2, displayName : "Password based"},
                            { name: 4, displayName : "Disable C29 Debug"},
                        ],
                        onChange   : (inst, ui) => {
                            ui.C29DBGEN_PSWD.hidden = inst.C29DBGEN_CFG != 2;
                        }
                    },
                    {
                        name       : 'C29DBGEN_PSWD',
                        hidden     : true,
                        displayName: 'Password',
                        default    : "55555555555555555555555555555555",
                    },
                ]
            },
        ]
    };
["ZONE1", "ZONE2", "ZONE3"].forEach (x => {
    config_debugAccess.config.push(
        {
            name       : 'Zone' + x + "Debug",
            displayName:  x + " Debug Lock",
            collapsed  : false,
            config     : [
                {
                    name         : x + '_DEBUG_CFG',
                    displayName  : 'ZONE Debug Unlock Configuration',
                    hidden       : true,
                    default      : 2,
                    options      : [
                        { name: 1, displayName: "CPU based"},
                        { name: 2, displayName: "Password based"},
                        { name: 4, displayName: "Disable debug"},
                    ],
                    onChange   : (inst, ui) => {
                        ui[x + "_FDBGPSWD"].hidden = inst[x + 'DEBUG_CFG'] != 2;
                        ui[x + "_PDBGPSWD"].hidden = inst[x + 'DEBUG_CFG'] != 2;
                    }
                },
                {
                    name       : x + '_PDBGPSWD',
                    hidden     : true,
                    displayName: 'Partial debug password',
                    default    : "55555555555555555555555555555555",
                },
                {
                    name       : x + '_FDBGPSWD',
                    hidden     : true,
                    displayName: 'Full debug password',
                    default    : "55555555555555555555555555555555",
                },
            ]
        },
    )
})

let config_flashUpdateOwner =
    {
        name       : 'FlashUpdateOwner',
        displayName: "Flash Update Owner",
        collapsed  : true,
        config     : []
    };
["SECCFG", "ZONE1", "ZONE2", "ZONE3"].forEach ((x) => {
    config_flashUpdateOwner.config.push(
        {
            name       : x + "UpdateOwner" ,
            displayName: x + " Update Owner",
            collapsed  : false,
            config     : [
                {
                    name         : x + '_UPDATE_EN',
                    displayName  : 'Enable update',
                    hidden       : !Cmn.isContextCPU1(),
                    default      : true,
                },
                {
                    name         : x + '_UPDATE_CPU',
                    displayName  : 'Update Owner CPU',
                    hidden       : !Cmn.isContextCPU1(),
                    default      : 1,
                    options      : [
                        { name: 0, displayName :"CPU-HSM"},
                        { name: 1, displayName :"CPU1"},
                        { name: 2, displayName :"CPU2"},
                        { name: 3, displayName :"CPU3"},
                    ]
                },
                {
                    name         :  x + '_UPDATE_LINK',
                    displayName  : 'Update Owner LINK',
                    hidden       : !Cmn.isContextCPU1(),
                    options      : () => Common.modInstances('/ti/security/Link'),
                    hideNoneOption : true
                },
            ]
        },
    )
})

let config_bootSettings =
    {
        name       : 'BootSetting',
        displayName: "Boot Settings",
        collapsed  : true,
        config     : [
            {
                name       : 'BootConfig',
                displayName: "Boot configuration",
                collapsed  : false,
                config     : [
                    {
                        name        : 'EMU_BOOTEN',
                        displayName : 'Enable emulation boot',
                        hidden       : !Cmn.isContextCPU1(),
                        default     : false,
                    },
                    {
                        name        : 'LPOST_EN',
                        displayName : 'LPOST Enable',
                        hidden       : !Cmn.isContextCPU1(),
                        default     : "00",
                        options     : [
                            {name : "00", displayName : "Run LPOST with PLL disabled (10MHz INTOSC)"},
                            {name : "01", displayName : "Run LPOST with high shift frequency"},
                            {name : "10", displayName : "Run LPOST with medium shift frequency"},
                            {name : "11", displayName : "Do not run LPOST"}
                        ]
                    },
                    {
                        name        : 'LPOST_COVER',
                        displayName : 'LPOST Coverage',
                        hidden       : !Cmn.isContextCPU1(),
                        default     : "01",
                        options     : [
                            {name : "01", displayName : "≥ 60% coverage (ASIL-B configuration)"},
                            {name : "10", displayName : "≥ 80% coverage (ASIL-C configuration)"},
                            {name : "11", displayName : "≥ 90% coverage (ASIL-D configuration)"},
                        ]
                    },
                    {
                        name        : 'MPOST_EN',
                        displayName : 'MPOST Enable',
                        hidden       : !Cmn.isContextCPU1(),
                        default     : "00",
                        options     : [
                            {name : "00", displayName : "Run MPOST with PLL disabled (10MHz INTOSC)"},
                            {name : "01", displayName : "Run MPOST at PLLCLK"},
                            {name : "10", displayName : "Run MPOST at PLLCLK/2"},
                            {name : "11", displayName : "Do not run MPOST"},
                        ]
                    },
                    {
                        name        : 'ERROR_STS_PIN',
                        displayName : 'Error Status Pin',
                        hidden       : !Cmn.isContextCPU1(),
                        default     : 219,
                        options     : [
                            {name:255,  displayName: "None"},
                            {name:4,    displayName: "GPIO4"},
                            {name:79,   displayName: "GPIO79"},
                            {name:80,   displayName: "GPIO80"},
                            {name:219,  displayName: "GPIO219"},
                            {name:247,  displayName: "GPIO247"},
                        ]
                    },
                    {
                        name        : 'BOOT_LOADER_LOCK',
                        displayName : 'Lock the ROM Boot loaders',
                        hidden       : !Cmn.isContextCPU1(),
                        default     : false
                    },
                    {
                        name        : 'ENABLE_XTAL',
                        displayName : 'Enable XTAL during boot time',
                        hidden       : !Cmn.isContextCPU1(),
                        default     : '0xFF',
                        options     : [
                            {name:"0xC9", displayName: "Enable Crystal Mode"},
                            {name:"0x9C", displayName: "Enable Single ended Mode"},
                            {name:"0xFF", displayName: "Disable XTAL"},

                        ]
                    },
                ]
            },
            {
                name       : 'BootPinConfig',
                displayName: "Boot pin configuration",
                collapsed  : false,
                config     : [
                    {
                        name        : 'defaultBootmode',
                        displayName : 'Use default boot modes',
                        hidden       : !Cmn.isContextCPU1(),
                        default     : true,
                        onChange    : (inst, ui) => {
                                if(inst.defaultBootmode) {
                                    inst.bootPinCount = 2
                                    ui.BMSP0.hidden = false
                                    ui.BMSP1.hidden = false
                                    ui.BMSP2.hidden = true
                                    inst.BMSP0 = 84
                                    inst.BMSP1 = 72
                                    ui.BOOTDEF0.hidden = false
                                    ui.BOOTDEF1.hidden = false
                                    ui.BOOTDEF2.hidden = false
                                    ui.BOOTDEF3.hidden = false
                                    ui.BOOTDEF4.hidden = true
                                    ui.BOOTDEF5.hidden = true
                                    ui.BOOTDEF6.hidden = true
                                    ui.BOOTDEF7.hidden = true
                                    inst.BOOTDEF0 = '00'
                                    inst.BOOTDEF1 = '01'
                                    inst.BOOTDEF2 = '02'
                                    inst.BOOTDEF3 = '03'
                                }
                                ui.bootPinCount.readOnly = inst.defaultBootmode
                                ui.BMSP0.readOnly        = inst.defaultBootmode
                                ui.BMSP1.readOnly        = inst.defaultBootmode
                                ui.BMSP2.readOnly        = inst.defaultBootmode
                                ui.BOOTDEF0.readOnly     = inst.defaultBootmode
                                ui.BOOTDEF1.readOnly     = inst.defaultBootmode
                                ui.BOOTDEF2.readOnly     = inst.defaultBootmode
                                ui.BOOTDEF3.readOnly     = inst.defaultBootmode
                                ui.BOOTDEF4.readOnly     = inst.defaultBootmode
                                ui.BOOTDEF5.readOnly     = inst.defaultBootmode
                                ui.BOOTDEF6.readOnly     = inst.defaultBootmode
                                ui.BOOTDEF7.readOnly     = inst.defaultBootmode
                            }
                    },
                    {
                        name        : 'bootPinCount',
                        displayName : 'Number of Boot Pins',
                        hidden       : !Cmn.isContextCPU1(),
                        default     : 2,
                        readOnly    : true,
                        options     : [
                            {name: 0},
                            {name: 1},
                            {name: 2},
                            {name: 3}
                        ],
                        onChange    : (inst, ui) => {
                                ui.BMSP0.hidden    = inst.bootPinCount == 0;
                                ui.BMSP1.hidden    = inst.bootPinCount <= 1;
                                ui.BMSP2.hidden    = inst.bootPinCount <= 2;
                                ui.BOOTDEF1.hidden = inst.bootPinCount == 0;
                                ui.BOOTDEF2.hidden = inst.bootPinCount <= 1;
                                ui.BOOTDEF3.hidden = inst.bootPinCount <= 1;
                                ui.BOOTDEF4.hidden = inst.bootPinCount <= 2;
                                ui.BOOTDEF5.hidden = inst.bootPinCount <= 2;
                                ui.BOOTDEF6.hidden = inst.bootPinCount <= 2;
                                ui.BOOTDEF7.hidden = inst.bootPinCount <= 2;
                        }
                    },
                    {
                        name        : 'BMSP0',
                        displayName : 'Boot Pin 0 (BMSP0)',
                        hidden      : !Cmn.isContextCPU1(),//false,
                        readOnly    : true,
                        default     : 84,
                    },
                    {
                        name        : 'BMSP1',
                        displayName : 'Boot Pin 1 (BMSP1)',
                        hidden      : !Cmn.isContextCPU1(),//false,
                        readOnly    : true,
                        default     : 72,
                    },
                    {
                        name        : 'BMSP2',
                        displayName : 'Boot Pin 2 (BMSP2)',
                        hidden      : true,
                        readOnly    : true,
                        default     : 0xFF,
                    },
                    {
                        name        : 'BOOTDEF0',
                        description : "Boot mode when the value of the GPIOs used for valid BSMP2-BSMP1-BSMP0 are 0b000",
                        hidden      : !Cmn.isContextCPU1(),//false,
                        readOnly    : true,
                        default     : "00",
                        options     : peripheralData.bootmodes,
                    },
                    {
                        name        : 'BOOTDEF1',
                        description : "Boot mode when the value of the GPIOs used for valid BSMP2-BSMP1-BSMP0 are 0b001",
                        hidden      : !Cmn.isContextCPU1(),//false,
                        readOnly    : true,
                        default     : "01",
                        options     : peripheralData.bootmodes,
                    },
                    {
                        name        : 'BOOTDEF2',
                        description : "Boot mode when the value of the GPIOs used for valid BSMP2-BSMP1-BSMP0 are 0b010",
                        hidden      : !Cmn.isContextCPU1(),//false,
                        readOnly    : true,
                        default     : "02",
                        options     : peripheralData.bootmodes,
                    },
                    {
                        name        : 'BOOTDEF3',
                        description : "Boot mode when the value of the GPIOs used for valid BSMP2-BSMP1-BSMP0 are 0b011",
                        hidden      : !Cmn.isContextCPU1(),//false,
                        readOnly    : true,
                        default     : "03",
                        options     : peripheralData.bootmodes,
                    },
                    {
                        name        : 'BOOTDEF4',
                        description : "Boot mode when the value of the GPIOs used for valid BSMP2-BSMP1-BSMP0 are 0b100",
                        hidden      : true,
                        readOnly    : true,
                        default     : "00",
                        options     : peripheralData.bootmodes,
                    },
                    {
                        name        : 'BOOTDEF5',
                        description : "Boot mode when the value of the GPIOs used for valid BSMP2-BSMP1-BSMP0 are 0b101",
                        hidden      : true,
                        readOnly    : true,
                        default     : "00",
                        options     : peripheralData.bootmodes,
                    },
                    {
                        name        : 'BOOTDEF6',
                        description : "Boot mode when the value of the GPIOs used for valid BSMP2-BSMP1-BSMP0 are 0b110",
                        hidden      : true,
                        readOnly    : true,
                        default     : "00",
                        options     : peripheralData.bootmodes,
                    },
                    {
                        name        : 'BOOTDEF7',
                        description : "Boot mode when the value of the GPIOs used for valid BSMP2-BSMP1-BSMP0 are 0b111",
                        hidden      : true,
                        readOnly    : true,
                        default     : "00",
                        options     : peripheralData.bootmodes,
                    },

                ]
            },
        ]
    }

let config_registerLocks =
    {
        name       : 'registerLocks',
        displayName: "Register Lock & Commit",
        collapsed  : true,
        config     : [
            {
                name        : 'disableAPR',
                displayName : 'Disable APR registers',
                default          : [],
                options          : () => Common.allocateAllMemoryRegions()[system.context]
                                            .map(x => {return {name: x.name}}),
                disableSelectAll : true,
            },
            {
                name        : 'lockAPR',
                displayName : 'Lock APR registers',
                default          : [],
                options          : () => Common.allocateAllMemoryRegions()[system.context]
                                            .map(x => {return {name: x.name}}),
                disableSelectAll : true,
            },
            {
                name        : 'commitAPR',
                displayName : 'Commit APR registers',
                default          : [],
                options          : () => Common.allocateAllMemoryRegions()[system.context]
                                            .map(x => {return {name: x.name}}),
                disableSelectAll : true,
            },
            {
                name        : 'LockUnusedAPRs',
                displayName : 'Lock the unused APR registers',
                default     : false
            },
            {
                name        : 'CommitUnusedAPRs',
                displayName : 'Commit the unused APR registers',
                default     : false
            },
            {
                name        : 'DEBUG_CFG_LOCK',
                displayName : 'Lock DEBUG_CFG register',
                hidden       : !Cmn.isContextCPU1(),
                default     : false
            },
            {
                name        : 'DEBUG_CFG_COMMIT',
                displayName : 'Commit DEBUG_CFG register',
                hidden       : !Cmn.isContextCPU1(),
                default     : false
            },
            {
                name          : 'lockWEPROTRegs',
                displayName   : 'Lock WEPROT registers',
                hidden       : !Cmn.isContextCPU1(),
                default       : [],
                minSelections : 0,
                options       : [
                    {name: "WEPROT_CODE_BANKS"},
                    {name: "WEPROT_DATA_BANKS"},
                    {name: "WEPROT_FLC1_B0"},
                    {name: "WEPROT_FLC1_B2"},
                    {name: "WEPROT_FLC2_B0"},
                    {name: "WEPROT_FLC2_B2"},
                ],
            },
            {
                name          : 'commitWEPROTRegs',
                displayName   : 'Commit WEPROT registers',
                hidden       : !Cmn.isContextCPU1(),
                default       : [],
                minSelections : 0,
                options       : [
                    {name: "WEPROT_CODE_BANKS"},
                    {name: "WEPROT_DATA_BANKS"},
                    {name: "WEPROT_FLC1_B0"},
                    {name: "WEPROT_FLC1_B2"},
                    {name: "WEPROT_FLC2_B0"},
                    {name: "WEPROT_FLC2_B2"},
                ],
            },
            {
                name        : 'RAMOPEN_LOCK',
                displayName : 'Lock RAMOPEN register',
                hidden      : !Cmn.isContextCPU1(),
                default     : false
            },
            {
                name        : 'RAMOPEN_COMMIT',
                displayName : 'Commit RAMOPEN register',
                hidden      : !Cmn.isContextCPU1(),
                default     : false
            },
        ]
    }

let config_misc =
    {
        name       : 'miscSettings',
        displayName: "Other Settings",
        collapsed  : true,
        config     : [
            {
                name        : 'dltLinks',
                displayName : 'Links with DLT write permission',
                hidden      : true,
                options     : () => Common.modInstances('/ti/security/Link'),
                isArray     : true
            },
        ]
    }

function validate(inst, vo)
{
    let aprList = Common.allocateAllMemoryRegions()[system.context]
    if(aprList && aprList.length > ssuData.instanceCount.APR){
        vo.logError(`Maximum APR count of ${ssuData.instanceCount.APR} exceeded`, inst)
    }

    let coresEnabled = Common.getConfigFromStaticModule("/ti/security/System_Security", "cpuList", Cmn.CONTEXT_CPU1)
    let coresValid  = Common.getCoreList(1).map(c => {return c.name})
    // Corelist validation
    if(Cmn.isContextCPU1()){
        let invalidcoreList = "", flag = false
        coresEnabled.value.forEach(core => {
            if(!coresValid.includes(core)){
                flag = true
                invalidcoreList += core + " "
            }
        })

        if(flag)
            vo.logError("Invalid core(s) selected: " + invalidcoreList, inst, 'cpuList')
    }
    // Check if core is enabled on CPU1
    else{
        let coresEnabled = Common.getConfigFromStaticModule("/ti/security/System_Security", "cpuList", Cmn.CONTEXT_CPU1)
        if(!coresEnabled.available){
            vo.logError("System Security module not enabled on CPU1 / CPU1 context not found!", inst)
        }
        else{
            if(!coresEnabled.value.includes(system.context)){
                vo.logError("Current core is not enabled by CPU1 System Security", inst)
            }
        }
    }

    // Bankmode >= 2 for CPU3 usage validation
    if(Cmn.isContextCPU3()){
        let bankmode = Common.getConfigFromStaticModule("/ti/security/APR", "bankMode", Cmn.CONTEXT_CPU1)
        if(!bankmode.available){
            vo.logWarning("Bankmode setting not found on CPU1", inst)
        }
        else{
            if(![2,3].includes(bankmode.value)){
                vo.logError("Bankmode must be set to 2/3 on CPU1 to use System Security on CPU3", inst)
            }
        }
    }

    if(inst.cpu2RunAPR && !(Cmn.getModuleForCore("/ti/security/System_Security", "CPU2"))){
        vo.logError("Please create security context in CPU2 first!!", inst);
    }

    if(inst.cpu3RunAPR && !(Cmn.getModuleForCore("/ti/security/System_Security", "CPU3"))){
        vo.logError("Please create security context in CPU3 first!!", inst);
    }

    // Check for bootpins
    if((inst.bootPinCount > 0) && (inst.BMSP0 > 254))
        vo.logError("Enter a value between 0 and 254.", inst, 'BMSP0');
    if((inst.bootPinCount > 1) && (inst.BMSP1 > 254))
        vo.logError("Enter a value between 0 and 254.", inst, 'BMSP1');
    if((inst.bootPinCount > 2) && (inst.BMSP2 > 254))
        vo.logError("Enter a value between 0 and 254.", inst, 'BMSP2');

    // Check for password
    var format32Hex = new RegExp(/^[A-F0-9]{32}$/i);
    if(!format32Hex.test(inst.C29DBGEN_PSWD))
        vo.logError("Invalid 32 digit hex value.", inst, 'C29DBGEN_PSWD');
    ["ZONE1", "ZONE2", "ZONE3"].forEach (x => {
        if(!format32Hex.test(inst[x + '_PDBGPSWD']))
            vo.logError("Invalid 32 digit hex value.", inst, x + '_PDBGPSWD');
        if(!format32Hex.test(inst[x + '_FDBGPSWD']))
            vo.logError("Invalid 32 digit hex value.", inst, x + '_FDBGPSWD');
    })

    // Check for update counter
    var format16Hex = new RegExp(/^[A-F0-9]{16}$/i);
    if(!format16Hex.test(inst.updateCtr))
        vo.logError("Invalid 16 digit hex value.", inst, 'updateCtr');

    // Check for uppRev
    if(inst.uppRev > 0xFFFF)
        vo.logError("UPP revision must be less than 0xFFFF", inst, 'uppRev');


    // warning message for jtag lock on ssumode 3
    if(inst.ssumode == 3)
    {
        if(inst.C29DBGEN_CFG == 4)
            vo.logWarning("This causes C29 Debug to be disabled permanently.", inst, 'C29DBGEN_CFG');
        if(inst.C29DBGEN_CFG == 1)
            vo.logWarning("Make sure to include authentication logic into your application to enable C29 Debug. Else C29 Debug will be disabled permanently", inst, 'C29DBGEN_CFG');

        ["ZONE1", "ZONE2", "ZONE3"].forEach (x => {
            if(inst[x + '_DEBUG_CFG'] == 4)
                vo.logWarning("This causes Zone Debug to be disabled permanently.", inst, x + '_DEBUG_CFG');
            if(inst[x + '_DEBUG_CFG'] == 1)
                vo.logWarning("Make sure to include authentication logic into your application to enable Zone Debug. Else Zone Debug will be disabled permanently", inst, x + '_DEBUG_CFG');
        })
    }

    // Boot peripheral APRs check
    if(Cmn.isContextCPU1()){
        let bootAprList = Common.getBootPeripherals(inst);
        let reqSet = new Set(), perSet = new Set()
        let l1AddedAprs = []
        let link1Instance = Common.modInstances('/ti/security/Link').filter(x=>x.isLink1)
        if(link1Instance[0]){
            link1Instance[0].readwriteAPRsEasy.forEach(p=> l1AddedAprs.push(p))
            link1Instance[0].readwriteAPRs.forEach(p=> l1AddedAprs.push(p))
        }
        let periphAprs = aprList.filter(apr => (apr.type == "Peripheral") && (l1AddedAprs.includes(apr.name)))
        bootAprList.forEach(p => {
            reqSet.add(p)
        })
        periphAprs.forEach(apr => {
            apr.peripheralList.forEach(p => {
                perSet.add(p)
            })
        })

        let r = Array.from(reqSet), p = Array.from(perSet)
        let diff = r.filter(x => ! p.includes(x));
        diff.forEach(p => {
            vo.logError(`LINK1 must have RW access to ${p} in order to boot correctly in selected configurations. Add a memory region covering this peripheral. If one already exists,
            allow LINK1 RW permissions to this region through System Security / LINK module`, inst);
        })
    }

    //LINK2 required APRs check //!!
}

let config_ssu =
{
    name         : "SSUSettings",
    displayName  : 'SSU Setup',
    collapsed    : false,
    style        : "tab",
    config       : [
        {
            name            : "flashLoadSize",
            displayName     : "Flash size used as Load memory (in kB)",
            longDescription : "This is used for as Load memory for functions and RO sections in RAM and for storing cinit section copy tables",
            default         : !Cmn.isContextCPU2() ? 4 : 0,
        },
        {
            name            : "addStack1",
            displayName     : "Add Custom Bootloader Sandbox",
            longDescription : "Enables STACK1 (Bootloader STACK) for application usage",
            default         : true,
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
        },
        {
            name            : "addLink2",
            displayName     : "Add Secure Root Module",
            longDescription : "Add LINK2 (Most secure LINK) with code and data APRs",
            default         : true,
        },
        {
            name            : "addCommonCodeModule",
            displayName     : "Add Common Code Module",
            longDescription : "Libraries or functions which are called across modules can be placed in this module. This modules inherits the caller module's accesses to memory regions and peripherals",
            default         : true,
        },
        {
            name            : "specialModules",
            displayName     : "Special Modules",
            style           : "tab",
            config          : []
        },
        {
            name            : "specialSandboxes",
            displayName     : "Special Sandboxes",
            style           : "tab",
            config          : []
        }
    ],
}

let config_additional_aprs =
{
    name         : "addlAprs",
    displayName  : 'Auto-Generated Regions',
    collapsed    : true,
    config       : [
    ],
}


function dependentModuleInstances(inst){

    let components = []
    return components
}

function moduleInstances(inst)
{
    var modules = []

    // Reserved Flash APR for signature
    if(inst.cpu1marker){
        modules.push({
            name        : "APR_RESERVED_sign_CPU1",
            displayName : "Flash Certificate APR",
            moduleName  : "/ti/security/APR",
            collapsed   : true,
            hidden      : false,
            group       : "addlAprs",
            requiredArgs: {
                $name           : "APR_RESERVED_sign_CPU1",
                type            : "Data",
                memType         : "Flash",
                memSize         : 4,
                specialAprStatus: "signature_CPU1"
                //showUserSections: false
            }
        })
    }

    if(inst.cpu3marker){
        modules.push({
            name        : "APR_RESERVED_sign_CPU3",
            displayName : "Flash Certificate APR",
            moduleName  : "/ti/security/APR",
            collapsed   : true,
            hidden      : false,
            group       : "addlAprs",
            requiredArgs: {
                $name           : "APR_RESERVED_sign_CPU3",
                type            : "Data",
                memType         : "Flash",
                memSize         : 4,
                specialAprStatus: "signature_CPU3"
                //showUserSections: false
            }
        })
    }

    // Default APR for flashload
    if(inst.flashLoadSize != 0)
        modules.push({
            name        : "APR_FlashLoad",
            displayName : "CPU" + String(inst.cpuMarker) + " Flash Load APR",
            moduleName  : "/ti/security/APR",
            collapsed   : true,
            hidden      : false,
            group       : "addlAprs",
            requiredArgs: {
                $name           : "APR_FlashLoad_CPU"+String(inst.cpuMarker),
                type            : "Data",
                memType         : "Flash",
                memSize         : inst.flashLoadSize,
                /* diffContext     : true,
                diffContextName : "CPU1", */
                specialAprStatus: "flash_load_CPU"+String(inst.cpuMarker)
            }
        })

    // Modules with no Instances
    modules.push({
        name              : "module",
        displayName       : "Application Module",
        moduleName        : "/ti/security/EasyMode_link",
        useArray          : true,
        style             : "tab",
        group             : "SSUSettings",
    })

    // Add LINK2 module to special modules
    if(inst.addLink2)
    {
        modules.push({
            name              : "LINK2",
            displayName       : "Secure Root Module",
            moduleName        : "/ti/security/EasyMode_link",
            group             : "specialModules",
            collapsed         : true,
            requiredArgs      : {
                $name : "LINK2", isLink2 : true
            },
            args : {
                periphs_rw: Common.getLink2RequiredAprs()
            }
        })
    }

    // add common code module to special modules
    if(inst.addCommonCodeModule)
    {
        modules.push({
            name        : "CommonCodeModule",
            displayName : "Common Code Module",
            moduleName  : "/ti/security/EasyMode_link",
            collapsed   : true,
            group       : "specialModules",
            collapsed   : true,
            requiredArgs: {
                $name       : "CommonCodeModule",
                isCommonCode: true
            },
            args : {
                //fileNames   : "error",
                libs        : "libc.a,libclang_rt.builtins.a,driverlib.lib"
            }
        })
    }
    if(inst.addLink1)
    {
        modules.push({
            name              : "LINK1",
            displayName       : "Bootloader Module",
            moduleName        : "/ti/security/EasyMode_link",
            group             : "specialModules",
            collapsed         : true,
            requiredArgs      : {
                $name : "LINK1", isLink1 : true
            },
            args : {
                codesizeFlash : 0,
                codesizeRAM : 0,
                rwdatasize : 0,
                rodatasize : 0,
                datasize : 0,
                periphs_rw: Cmn.isContextCPU1() ? Common.getBootPeripherals(inst) : []
            }
        })
    }
    if(inst.addStack1)
    {
        modules.push({
            name              : "STACK1",
            displayName       : "Custom Bootloader Sandbox",
            moduleName        : "/ti/security/EasyMode_stack",
            group             : "specialSandboxes",
            collapsed         : true,
            requiredArgs      : {
                $name : "STACK1", zone : "ZONE1",
            },
            args              : {
                modules: inst.addLink1 ? ["LINK1_Link"] : []
            }
        })
    }

    // Add STACK2
    modules.push({
        name              : "STACK2",
        displayName       : "Secure Root Sandbox",
        moduleName        : "/ti/security/EasyMode_stack",
        group             : "specialSandboxes",
        collapsed         : true,
        requiredArgs      : {
            $name : "STACK2", zone : "ZONE1",
        },
        args              : {
            modules: inst.addLink2 ? ["LINK2_Link"] : []
        }
    })

    // Sandboxes with no default Instances
    modules.push({
        name              : "sandbox",
        displayName       : "Sandbox",
        style             : "tab",
        moduleName        : '/ti/security/EasyMode_stack',
        useArray          : true,
        group             : "SSUSettings",
    })

    // SharedMem with no default Instances
    modules.push({
        name              : "sharedMem",
        displayName       : "Shared Memory",
        style             : "tab",
        moduleName        : "/ti/security/EasyMode_sharedMem",
        useArray          : true,
        group             : "SSUSettings",
    })

    if(Cmn.isContextCPU1() == true)
    {
        inst.cpuList.forEach(core => {
            if(core == "CPU2")
            {
                modules.push({
                    name        : "CPU2_FLASH_REGION",
                    displayName : "CPU2 Flash Load APR",
                    moduleName  : "/ti/security/APR",
                    collapsed   : true,
                    hidden      : false,
                    group       : "group_moduleAPRs",
                    requiredArgs: {
                        $name           : "CPU2_FLASH_REGION",
                        type            : "Data",
                        memType         : "Flash",
                        memSize         : 64,
                    }
                })
            }
        })
    }

    return modules;
}

exports = {
    displayName  : 'System Security',
    moduleStatic : {
        validate,
        config : [
            {
                name        : "generalSettings",
                displayName : "General settings",
                collapsed   : false,
                config      : [
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
        ],
        moduleInstances,
        dependentModuleInstances
    },
    templates          : {  '/ti/security/templates/ssu_config.c.xdt'       : true,
                            '/ti/security/templates/ssu_config.h.xdt'       : true,
                            '/ti/security/templates/seccfg_old.c.xdt'       : true
                        },
};