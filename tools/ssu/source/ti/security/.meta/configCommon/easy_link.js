const Common            = system.getScript('/ti/security/Common.js');
const peripheralData    = system.getScript('/ti/security/device_specific_information/peripheral_data.js');

let config =
[
    {
        name    : "$name",
        hidden  : false,
    },
    {
        name        : "isLink2",
        default     : false,
        hidden      : true,
        onChange    : (inst, ui) =>
        {
            ui.link2CodeSection.hidden          = !inst.isLink2
            ui.link2DefaultAllSections.hidden   = !inst.isLink2
        }
    },
    {
        name    : "isLink1",
        default : false,
        hidden  : true,
    },
    {
        name        : "isCommonCode",
        default     : false,
        hidden      : true,
        onChange    : (inst, ui) =>
        {
            ui.secGroupAttr.hidden  = !inst.isCommonCode
            ui.periphs_rw.hidden    = inst.isCommonCode
            ui.periphs_ro.hidden    = inst.isCommonCode
            ui.interrupts.hidden    = inst.isCommonCode
        }
    },
    {
        name        : 'secGroupAttr',
        displayName : "Unprotected calls to common code",
        hidden      : true,
        default     : "PUBLIC",
        options     :
        [
            {name : "NONE",           displayName : "Generate Linker error"},
            {name : "PUBLIC",         displayName : "Add linker trampolines and landing pads (Secure)"},
            {name : "PUBLIC_TRUSTED", displayName : "Add linker trampolines and landing pads (Unsecure, Faster)"},
        ]
    }
]

let g_Section_common =
{
    name        : "group_section",
    displayName : "Code & Data - Sections",
    collapsed   : false,
    config      :
    [
        {
            name        : "fileNames",
            displayName : "File to be included (comma separated)",
            default     : "",
        },
        {
            name        : "libs",
            displayName : "Libraries to be included (comma separated)",
            default     : "",
        },
        {
            name        : "useCustomSections",
            displayName : "Use Custom Sections",
            default     : false,
            onChange    : (inst, ui) =>
            {
                ui.customCodeSectionFlash.hidden    = !inst.useCustomSections
                ui.customCodeSectionRAM.hidden      = !inst.useCustomSections
                ui.customRWSection.hidden           = !inst.useCustomSections
                ui.customROSection.hidden           = !inst.useCustomSections
            }
        },
        {
            name        : "customCodeSectionFlash",
            displayName : "Custom code sections to be run from Flash (comma separated)",
            default     : "",
            multiline   : true,
            hidden      : true
        },
        {
            name        : "customCodeSectionRAM",
            displayName : "Custom code sections to be run from RAM (comma separated)",
            default     : "",
            hidden      : true
        },
        {
            name        : "customRWSection",
            displayName : "Custom RW Data sections (comma separated)",
            default     : "",
            hidden      : true
        },
        {
            name        : "customROSection",
            displayName : "Custom RO Data sections (comma separated)",
            default     : "",
            hidden      : true
        },
        {
            name          : "link2CodeSection",
            displayName   : "Default code sections included in Link2",
            default       : "libc.a<boot.c.obj>(.text), libc.a<autoinit.c.obj>(.text), libc.a<cpy_tbl.c.obj>(.text), *(.text.link2)" + ((Common.isContextCPU1()) ? "" : ", codestart"),
            multiline     : true,
            hidden        : true,
            readOnly      : true
        },
        {
            name        : "link2DefaultAllSections",
            displayName : "Default sections included in Link2",
            default     : "libc.a<copy_zero_init.c.obj>, libc.a<copy_decompress_lzss.c.obj>, libc.a<copy_decompress_none.c.obj>, libc.a<copy_decompress_rle.c.obj>, libc.a<pre_init.c.obj>,libc.a<exit.c.obj>,libc.a<startup.c.obj>,device.o,board.o,ssu_config.o",
            multiline   : true,
            hidden      : true,
            readOnly    : true
        },
        {
            name            : "textInRAM",
            displayName     : "Place the .text section in RAM",
            longDescription : "If enabled, all the .text sections from selected files/libraries will be run from RAM. If disabled, only functions marked as ramfunc will be run from RAM",
            default         : Common.isContextCPU2() ? true : false,
            onChange        : (inst, ui) =>
            {
                ui.codesizeFlash.hidden = inst.textInRAM
            }
        },
        {
            name            : "roInRAM",
            displayName     : "Place RO section in RAM",
            longDescription : "If enabled, all the RO sections will be placed in RAM. If disabled, they will be placed in Flash",
            default         : Common.isContextCPU2() ? true : false,
            onChange        : (inst, ui) =>
            {
                ui.combine_ro_rw.hidden = !inst.roInRAM
                if(!inst.roInRAM)
                {
                    inst.combine_ro_rw      = false
                    ui.datasize.hidden      = !inst.combine_ro_rw
                    ui.rwdatasize.hidden    = inst.combine_ro_rw
                    ui.rodatasize.hidden    = inst.combine_ro_rw
                }
            }
        },
        {
            name            : "combine_ro_rw",
            displayName     : "Place both RO and RW sections in a single APR",
            longDescription : "If enabled, both RO and RW sections in a single APR with read/write access enabled. If disabled, RO sections will be placed in a separate APR with read-only access",
            default         : false,
            hidden          : true,
            onChange        : (inst, ui) =>
            {
                ui.datasize.hidden      = !inst.combine_ro_rw
                ui.rwdatasize.hidden    = inst.combine_ro_rw
                ui.rodatasize.hidden    = inst.combine_ro_rw
            }
        },
    ]
}

let g_Section_main =
{
    name        : "group_section",
    displayName : "Code & Data - Sections",
    collapsed   : false,
    config      :
    [
        {
            name        : "fileNames",
            displayName : "File to be included (comma separated)",
            default     : "",
        },
        {
            name        : "libs",
            displayName : "Libraries to be included (comma separated)",
            default     : "",
        },
        {
            name        : "useCustomSections",
            displayName : "Use Custom Sections",
            default     : false,
            onChange    : (inst, ui) =>
            {
                ui.customCodeSectionFlash.hidden    = !inst.useCustomSections
                ui.customCodeSectionRAM.hidden      = !inst.useCustomSections
                ui.customRWSection.hidden           = !inst.useCustomSections
                ui.customROSection.hidden           = !inst.useCustomSections
            }
        },
        {
            name        : "customCodeSectionFlash",
            displayName : "Custom code sections to be run from Flash (comma separated)",
            default     : "",
            multiline   : true,
            hidden      : true
        },
        {
            name        : "customCodeSectionRAM",
            displayName : "Custom code sections to be run from RAM (comma separated)",
            default     : "",
            hidden      : true
        },
        {
            name        : "customRWSection",
            displayName : "Custom RW Data sections (comma separated)",
            default     : "",
            hidden      : true
        },
        {
            name        : "customROSection",
            displayName : "Custom RO Data sections (comma separated)",
            default     : "",
            hidden      : true
        },
        {
            name          : "link2CodeSection",
            displayName   : "Default code sections included in Link2",
            default       : "libc.a<boot.c.obj>(.text), libc.a<autoinit.c.obj>(.text), libc.a<cpy_tbl.c.obj>(.text), *(.text.link2)",
            multiline     : true,
            hidden        : true,
            readOnly      : true
        },
        {
            name        : "link2DefaultAllSections",
            displayName : "Default sections included in Link2",
            default     : "libc.a<copy_zero_init.c.obj>, libc.a<copy_decompress_lzss.c.obj>, libc.a<copy_decompress_none.c.obj>, libc.a<copy_decompress_rle.c.obj>, libc.a<pre_init.c.obj>,libc.a<exit.c.obj>,libc.a<startup.c.obj>,device.o,board.o,ssu_config.o",
            multiline   : true,
            hidden      : true,
            readOnly    : true
        },
        {
            name            : "textInRAM",
            displayName     : "Place the .text section in RAM",
            longDescription : "If enabled, all the .text sections from selected files/libraries will be run from RAM. If disabled, only functions marked as ramfunc will be run from RAM",
            default         : false,
            onChange        : (inst, ui) =>
            {
                ui.codesizeFlash.hidden = inst.textInRAM
            }
        },
        {
            name            : "roInRAM",
            displayName     : "Place RO section in RAM",
            longDescription : "If enabled, all the RO sections will be placed in RAM. If disabled, they will be placed in Flash",
            default         : false,
            onChange        : (inst, ui) =>
            {
                ui.combine_ro_rw.hidden = !inst.roInRAM
                if(!inst.roInRAM)
                {
                    inst.combine_ro_rw      = false
                    ui.datasize.hidden      = !inst.combine_ro_rw
                    ui.rwdatasize.hidden    = inst.combine_ro_rw
                    ui.rodatasize.hidden    = inst.combine_ro_rw
                }
            }
        },
        {
            name            : "combine_ro_rw",
            displayName     : "Place both RO and RW sections in a single APR",
            longDescription : "If enabled, both RO and RW sections in a single APR with read/write access enabled. If disabled, RO sections will be placed in a separate APR with read-only access",
            default         : false,
            hidden          : true,
            onChange        : (inst, ui) =>
            {
                ui.datasize.hidden      = !inst.combine_ro_rw
                ui.rwdatasize.hidden    = inst.combine_ro_rw
                ui.rodatasize.hidden    = inst.combine_ro_rw
            }
        },
    ]
}

let g_Section_cpu2 =
{
    name        : "group_section",
    displayName : "Code & Data - Sections",
    collapsed   : false,
    config      :
    [
        {
            name        : "fileNames",
            displayName : "File to be included (comma separated)",
            default     : "",
        },
        {
            name        : "libs",
            displayName : "Libraries to be included (comma separated)",
            default     : "",
        },
        {
            name        : "useCustomSections",
            displayName : "Use Custom Sections",
            default     : false,
            onChange    : (inst, ui) =>
            {
                ui.customCodeSectionFlash.hidden    = !inst.useCustomSections
                ui.customCodeSectionRAM.hidden      = !inst.useCustomSections
                ui.customRWSection.hidden           = !inst.useCustomSections
                ui.customROSection.hidden           = !inst.useCustomSections
            }
        },
        {
            name        : "customCodeSectionFlash",
            displayName : "Custom code sections to be run from Flash (comma separated)",
            default     : "",
            multiline   : true,
            hidden      : true
        },
        {
            name        : "customCodeSectionRAM",
            displayName : "Custom code sections to be run from RAM (comma separated)",
            default     : "",
            hidden      : true
        },
        {
            name        : "customRWSection",
            displayName : "Custom RW Data sections (comma separated)",
            default     : "",
            hidden      : true
        },
        {
            name        : "customROSection",
            displayName : "Custom RO Data sections (comma separated)",
            default     : "",
            hidden      : true
        },
        {
            name          : "link2CodeSection",
            displayName   : "Default code sections included in Link2",
            default       : "libc.a<boot.c.obj>(.text), libc.a<autoinit.c.obj>(.text), libc.a<cpy_tbl.c.obj>(.text), *(.text.link2), codestart",
            multiline     : true,
            hidden        : true,
            readOnly      : true
        },
        {
            name        : "link2DefaultAllSections",
            displayName : "Default sections included in Link2",
            default     : "libc.a<copy_zero_init.c.obj>, libc.a<copy_decompress_lzss.c.obj>, libc.a<copy_decompress_none.c.obj>, libc.a<copy_decompress_rle.c.obj>, libc.a<pre_init.c.obj>,libc.a<exit.c.obj>,libc.a<startup.c.obj>,device.o,board.o,ssu_config.o",
            multiline   : true,
            hidden      : true,
            readOnly    : true
        },
        {
            name            : "textInRAM",
            displayName     : "Place the .text section in RAM",
            longDescription : "If enabled, all the .text sections from selected files/libraries will be run from RAM. If disabled, only functions marked as ramfunc will be run from RAM",
            default         : true,
            onChange        : (inst, ui) =>
            {
                ui.codesizeFlash.hidden = inst.textInRAM
            }
        },
        {
            name            : "roInRAM",
            displayName     : "Place RO section in RAM",
            longDescription : "If enabled, all the RO sections will be placed in RAM. If disabled, they will be placed in Flash",
            default         : true,
            onChange        : (inst, ui) =>
            {
                ui.combine_ro_rw.hidden = !inst.roInRAM
                if(!inst.roInRAM)
                {
                    inst.combine_ro_rw      = false
                    ui.datasize.hidden      = !inst.combine_ro_rw
                    ui.rwdatasize.hidden    = inst.combine_ro_rw
                    ui.rodatasize.hidden    = inst.combine_ro_rw
                }
            }
        },
        {
            name            : "combine_ro_rw",
            displayName     : "Place both RO and RW sections in a single APR",
            longDescription : "If enabled, both RO and RW sections in a single APR with read/write access enabled. If disabled, RO sections will be placed in a separate APR with read-only access",
            default         : false,
            hidden          : true,
            onChange        : (inst, ui) =>
            {
                ui.datasize.hidden      = !inst.combine_ro_rw
                ui.rwdatasize.hidden    = inst.combine_ro_rw
                ui.rodatasize.hidden    = inst.combine_ro_rw
            }
        },
    ]
}

let g_Section_cpu3 =
{
    name        : "group_section",
    displayName : "Code & Data - Sections",
    collapsed   : false,
    config      :
    [
        {
            name        : "fileNames",
            displayName : "File to be included (comma separated)",
            default     : "",
        },
        {
            name        : "libs",
            displayName : "Libraries to be included (comma separated)",
            default     : "",
        },
        {
            name        : "useCustomSections",
            displayName : "Use Custom Sections",
            default     : false,
            onChange    : (inst, ui) =>
            {
                ui.customCodeSectionFlash.hidden    = !inst.useCustomSections
                ui.customCodeSectionRAM.hidden      = !inst.useCustomSections
                ui.customRWSection.hidden           = !inst.useCustomSections
                ui.customROSection.hidden           = !inst.useCustomSections
            }
        },
        {
            name        : "customCodeSectionFlash",
            displayName : "Custom code sections to be run from Flash (comma separated)",
            default     : "",
            multiline   : true,
            hidden      : true
        },
        {
            name        : "customCodeSectionRAM",
            displayName : "Custom code sections to be run from RAM (comma separated)",
            default     : "",
            hidden      : true
        },
        {
            name        : "customRWSection",
            displayName : "Custom RW Data sections (comma separated)",
            default     : "",
            hidden      : true
        },
        {
            name        : "customROSection",
            displayName : "Custom RO Data sections (comma separated)",
            default     : "",
            hidden      : true
        },
        {
            name          : "link2CodeSection",
            displayName   : "Default code sections included in Link2",
            default       : "libc.a<boot.c.obj>(.text), libc.a<autoinit.c.obj>(.text), libc.a<cpy_tbl.c.obj>(.text), *(.text.link2), codestart",
            multiline     : true,
            hidden        : true,
            readOnly      : true
        },
        {
            name        : "link2DefaultAllSections",
            displayName : "Default sections included in Link2",
            default     : "libc.a<copy_zero_init.c.obj>, libc.a<copy_decompress_lzss.c.obj>, libc.a<copy_decompress_none.c.obj>, libc.a<copy_decompress_rle.c.obj>, libc.a<pre_init.c.obj>,libc.a<exit.c.obj>,libc.a<startup.c.obj>,device.o,board.o,ssu_config.o",
            multiline   : true,
            hidden      : true,
            readOnly    : true
        },
        {
            name            : "textInRAM",
            displayName     : "Place the .text section in RAM",
            longDescription : "If enabled, all the .text sections from selected files/libraries will be run from RAM. If disabled, only functions marked as ramfunc will be run from RAM",
            default         : false,
            onChange        : (inst, ui) =>
            {
                ui.codesizeFlash.hidden = inst.textInRAM
            }
        },
        {
            name            : "roInRAM",
            displayName     : "Place RO section in RAM",
            longDescription : "If enabled, all the RO sections will be placed in RAM. If disabled, they will be placed in Flash",
            default         : false,
            onChange        : (inst, ui) =>
            {
                ui.combine_ro_rw.hidden = !inst.roInRAM
                if(!inst.roInRAM)
                {
                    inst.combine_ro_rw      = false
                    ui.datasize.hidden      = !inst.combine_ro_rw
                    ui.rwdatasize.hidden    = inst.combine_ro_rw
                    ui.rodatasize.hidden    = inst.combine_ro_rw
                }
            }
        },
        {
            name            : "combine_ro_rw",
            displayName     : "Place both RO and RW sections in a single APR",
            longDescription : "If enabled, both RO and RW sections in a single APR with read/write access enabled. If disabled, RO sections will be placed in a separate APR with read-only access",
            default         : false,
            hidden          : true,
            onChange        : (inst, ui) =>
            {
                ui.datasize.hidden      = !inst.combine_ro_rw
                ui.rwdatasize.hidden    = inst.combine_ro_rw
                ui.rodatasize.hidden    = inst.combine_ro_rw
            }
        },
    ]
}

let g_Size_common =
{
    name        : "group_size",
    displayName : "Code & Data - Sizes",
    collapsed   : false,
    config      :
    [
        {
            name        : "codesizeFlash",
            displayName : "Code size in Flash (in kB)",
            default     : Common.isContextCPU1() ? 4 : 0
        },
        {
            name        : "codesizeRAM",
            displayName : "Code size in RAM (in kB)",
            default     : 4,
        },
        {
            name        : "rwdatasize",
            displayName : "RW Data size in RAM (in kB)",
            default     : 4
        },
        {
            name        : "rodatasize",
            displayName : "RO Data size in Flash / RAM (in kB)",
            default     : Common.isContextCPU1() ? 4 : 0
        },
        {
            name        : "datasize",
            displayName : "RW/RO Data size in RAM (in kB)",
            default     : 4,
            hidden      : true
        },
    ]
}

let g_Size_main =
{
    name        : "group_size",
    displayName : "Code & Data - Sizes",
    collapsed   : false,
    config      :
    [
        {
            name        : "codesizeFlash",
            displayName : "Code size in Flash (in kB)",
            default     : 4
        },
        {
            name        : "codesizeRAM",
            displayName : "Code size in RAM (in kB)",
            default     : 4,
        },
        {
            name        : "rwdatasize",
            displayName : "RW Data size in RAM (in kB)",
            default     : 4
        },
        {
            name        : "rodatasize",
            displayName : "RO Data size in Flash / RAM (in kB)",
            default     : 4
        },
        {
            name        : "datasize",
            displayName : "RW/RO Data size in RAM (in kB)",
            default     : 4,
            hidden      : true
        },
    ]
}

let g_Size_non_main =
{
    name        : "group_size",
    displayName : "Code & Data - Sizes",
    collapsed   : false,
    config      :
    [
        {
            name        : "codesizeFlash",
            displayName : "Code size in Flash (in kB)",
            default     : 0
        },
        {
            name        : "codesizeRAM",
            displayName : "Code size in RAM (in kB)",
            default     : 4,
        },
        {
            name        : "rwdatasize",
            displayName : "RW Data size in RAM (in kB)",
            default     : 4
        },
        {
            name        : "rodatasize",
            displayName : "RO Data size in Flash / RAM (in kB)",
            default     : 0
        },
        {
            name        : "datasize",
            displayName : "RW/RO Data size in RAM (in kB)",
            default     : 4,
            hidden      : true
        },
    ]
}

let g_Periph =
{
    name        : "group_periph",
    displayName : "Peripheral Access",
    collapsed   : false,
    config      :
    [
        {
            name            : "periphs_rw",
            displayName     : "Peripherals with RW access",
            default         : [],
            minSelections   : 0,
            options         : () => {return peripheralData.getPeriphsSortedbyFrame().map(x=> { return {name: x.name}})},
            disableSelectAll: true,
        },
        {
            name            : "periphs_ro",
            displayName     : "Peripherals with RO access",
            default         : [],
            minSelections   : 0,
            options         : () => {return peripheralData.getPeriphsSortedbyFrame().map(x=> { return {name: x.name}})},
            disableSelectAll: true,
        },
        {
            name            : "interrupts",
            displayName     : "Interrupts Included in this module",
            longDescription : "User should make sure the ISR is placed in this module",
            options         : () => Common.modInstances('/driverlib/interrupt.js'),
            isArray         : true,
            disableSelectAll: true,
        },
    ]
}

let g_moduleAPRs =
{
    name        : "group_moduleAPRs",
    displayName : "Auto-Generated Components",
    collapsed   : true,
    config      : []
}

let config_common = config.concat(
    g_Section_common,
    g_Size_common,
    g_Periph,
    g_moduleAPRs
)

let config_main = config.concat(
    g_Section_main,
    g_Size_main,
    g_Periph,
    g_moduleAPRs
)

let config_cpu2 = config.concat(
    g_Section_cpu3,
    g_Size_non_main,
    g_Periph,
    g_moduleAPRs
)

let config_cpu3 = config.concat(
    g_Section_cpu3,
    g_Size_non_main,
    g_Periph,
    g_moduleAPRs
)


function validate(inst, vo)
{
    const bankmode = Common.getBankModeConfig();

    // CHECK: APR Size should be multiple of 4kB
    ['codesizeFlash', 'codesizeRAM', 'rwdatasize', 'rodatasize', 'datasize'].forEach((x)=>
    {
        if((inst[x] % 4) != 0)
            vo.logError("Memory Size should be multiple of 4kB" , inst, x);
    })

    // CHECK: No flash access
    if(inst.codesizeFlash > 0)
    {
        if(Common.isContextCPU2(inst))
            vo.logError("Current core doesn't have flash access" , inst, 'codesizeFlash');

        if(Common.isContextCPU3(inst) && bankmode<2)
            vo.logError("Current core doesn't have flash access" , inst, 'codesizeFlash');
    }

    if(inst.rodatasize > 0 && !inst.roInRAM)
    {
        if(Common.isContextCPU2(inst))
            vo.logError("Current core doesn't have flash access" , inst, 'rodatasize');

        if(Common.isContextCPU3(inst) && bankmode<2)
            vo.logError("Current core doesn't have flash access" , inst, 'rodatasize');
    }
}

function moduleInstances(inst)
{
    let corePrefix  = Common.getCurrentCorePrefix(inst)
    let components = []

    let add_codeAPR_Flash   = inst.codesizeFlash && !inst.textInRAM
    let add_codeAPR_RAM     = inst.codesizeRAM
    let add_dataAPR_RW      = inst.rwdatasize && !inst.combine_ro_rw
    let add_dataAPR_RO      = inst.rodatasize && !inst.combine_ro_rw
    let add_dataAPR         = inst.datasize && inst.combine_ro_rw

    if(add_codeAPR_Flash && !(inst.codesizeFlash%4))
        components.push
        ({
            name        : "codeAPR_Flash",
            displayName : "Code APR (Flash)",
            moduleName  : `/ti/security/${corePrefix}APR`,
            collapsed   : true,
            hidden      : false,
            group       : "group_moduleAPRs",
            requiredArgs:
            {
                $name           : inst.$name + "_codeAPR_Flash",
                type            : "Code",
                memType         : "Flash",
                memSize         : inst.codesizeFlash,
                specialAprStatus: inst.isLink2 ? "link2_flash_code" : inst.isCommonCode ? "commoncode_flash_code" : "none"
            }
        })

    if(add_codeAPR_RAM && !(inst.codesizeRAM%4))
        components.push
        ({
                name        : "codeAPR_RAM",
                displayName : "Code APR (RAM)",
                moduleName  : `/ti/security/${corePrefix}APR`,
                collapsed   : true,
                hidden      : false,
                group       : "group_moduleAPRs",
                requiredArgs:
                {
                    $name           : inst.$name + "_codeAPR_RAM",
                    type            : "Code",
                    memType         : "RAM",
                    memSize         : inst.codesizeRAM,
                    specialAprStatus: inst.isLink2 ? "link2_ram_code" : inst.isCommonCode ? "commoncode_ram_code" : "none"
                }
        })

    if(add_dataAPR_RW && !(inst.rwdatasize%4))
        components.push
        ({
                name        : "dataAPR_RW",
                displayName : "RW Data APR (RAM)",
                moduleName  : `/ti/security/${corePrefix}APR`,
                collapsed   : true,
                hidden      : false,
                group       : "group_moduleAPRs",
                requiredArgs:
                {
                    $name   : inst.$name + "_dataAPR_RW",
                    type    : "Data",
                    memType : "RAM",
                    memSize : inst.rwdatasize,
                    specialAprStatus: inst.isLink2 ? "link2_rw_data" : "none"
                }
        })

    if(add_dataAPR_RO && !(inst.rodatasize%4))
        components.push
        ({
                name        : "dataAPR_RO",
                displayName : "RO Data APR (Flash)",
                moduleName  : `/ti/security/${corePrefix}APR`,
                collapsed   : true,
                hidden      : false,
                group       : "group_moduleAPRs",
                requiredArgs:
                {
                    $name   : inst.$name + "_dataAPR_RO",
                    type    : "Code",
                    memType : inst.roInRAM ? "RAM"  : "Flash",
                    memSize : inst.rodatasize,
                    specialAprStatus: inst.isLink2 ? "link2_ro_data" : "none"
                }
        })

    if(add_dataAPR && !(inst.datasize%4))
        components.push
        ({
                name        : "dataAPR",
                displayName : "RW Data APR (RAM)",
                moduleName  : `/ti/security/${corePrefix}APR`,
                collapsed   : true,
                hidden      : false,
                group       : "group_moduleAPRs",
                requiredArgs:
                {
                    $name   : inst.$name + "_dataAPR",
                    type    : "Data",
                    memType : "RAM",
                    memSize : inst.datasize,
                    specialAprStatus: inst.isLink2 ? "link2_data" : "none"
                }
        })

    components.push
    ({
        name        : "Link",
        displayName : "LINK",
        moduleName  : `/ti/security/${corePrefix}Link`,
        collapsed   : true,
        hidden      : false,
        group       : "group_moduleAPRs",
        requiredArgs:
        {
            $name               : inst.$name + "_Link",
            easyModeGenerated   : true,
            isLink1             : inst.isLink1,
            isLink2             : inst.isLink2
        }
    })

    return components;
}

exports =
{
    config_common       : config_common,
    config_main         : config_main,
    config_cpu2         : config_cpu2,
    config_cpu3         : config_cpu3,
    validate            : validate,
    moduleInstances     : moduleInstances,
};