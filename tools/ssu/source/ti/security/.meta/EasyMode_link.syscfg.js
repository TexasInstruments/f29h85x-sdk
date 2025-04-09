const Common = system.getScript('/ti/security/Common.js');
const Cmn    = system.getScript("/driverlib/Common.js");
let sysSec   = system.getScript('/ti/security/System_Security');
const peripheralData    = system.getScript('/ti/security/device_specific_information/peripheral_data.js');

let config = [
    {
        name: "$name",
        hidden: false,
    },
    {
        name          : "isLink2",
        default       : false,
        hidden        : true,
        onChange      : (inst, ui) => {
            ui.link2CodeSection.hidden          = !inst.isLink2
            ui.link2DefaultAllSections.hidden   = !inst.isLink2
        }
    },
    {
        name          : "isLink1",
        default       : false,
        hidden        : true,
    },
    {
        name          : "isCommonCode",
        default       : false,
        hidden        : true,
        onChange      : (inst, ui) => {
            ui.secGroupAttr.hidden = !inst.isCommonCode
            ui.periphs_rw.hidden   = inst.isCommonCode
            ui.periphs_ro.hidden   = inst.isCommonCode
            ui.interrupts.hidden   = inst.isCommonCode
        }
    },
    {
        name           : 'secGroupAttr',
        displayName    : "Unprotected calls to common code",
        hidden         : true,
        default        : "PUBLIC",
        options        : [
            {name : "NONE",           displayName : "Generate Linker error"},
            {name : "PUBLIC",         displayName : "Add linker trampolines and landing pads (Secure)"},
            {name : "PUBLIC_TRUSTED", displayName : "Add linker trampolines and landing pads (Unsecure, Faster)"},
        ]
    },
    {
        name        : "group_section",
        displayName : "Code & Data - Sections",
        //style        : "tab",
        collapsed   : false,
        config      : [
            {
                name          : "fileNames",
                displayName   : "File to be included (comma separated)",
                default       : "",
            },
            {
                name          : "libs",
                displayName   : "Libraries to be included (comma separated)",
                default       : "",
            },
            {
                name          : "useCustomSections",
                displayName   : "Use Custom Sections",
                default       : false,
                onChange      : (inst, ui) => {
                    ui.customCodeSectionFlash.hidden = !inst.useCustomSections
                    ui.customCodeSectionRAM.hidden   = !inst.useCustomSections
                    ui.customRWSection.hidden        = !inst.useCustomSections
                    ui.customROSection.hidden        = !inst.useCustomSections
                }
            },
            {
                name          : "customCodeSectionFlash",
                displayName   : "Custom code sections to be run from Flash (comma separated)",
                default       : "",
                multiline     : true,
                hidden        : true
            },
            {
                name          : "customCodeSectionRAM",
                displayName   : "Custom code sections to be run from RAM (comma separated)",
                default       : "",
                hidden        : true
            },
            {
                name          : "customRWSection",
                displayName   : "Custom RW Data sections (comma separated)",
                default       : "",
                hidden        : true
            },
            {
                name          : "customROSection",
                displayName   : "Custom RO Data sections (comma separated)",
                default       : "",
                hidden        : true
            },
            {
                name          : "link2CodeSection",
                displayName   : "Default code sections included in Link2",
                default       : "libc.a<boot.c.obj>(.text), libc.a<autoinit.c.obj>(.text), libc.a<cpy_tbl.c.obj>(.text), libc.a<memcpy.S.obj>(.text), *(.text.link2)" + ((Cmn.isContextCPU1()) ? "" : ", codestart"),
                multiline     : true,
                hidden        : true,
                readOnly      : true
            },
            {
                name          : "link2DefaultAllSections",
                displayName   : "Default sections included in Link2",
                default       : "libc.a<copy_zero_init.c.obj>, libc.a<copy_decompress_lzss.c.obj>, libc.a<pre_init.c.obj>,libc.a<exit.c.obj>,libc.a<startup.c.obj>,device.o,board.o,ssu_config.o",
                multiline     : true,
                hidden        : true,
                readOnly      : true
            },
            {
                name            : "textInRAM",
                displayName     : "Place the .text section in RAM",
                longDescription : "If enabled, all the .text sections from selected files/libraries will be run from RAM. If disabled, only functions marked as ramfunc will be run from RAM",
                default         : Cmn.isContextCPU2() ? true : false,
                onChange        : (inst, ui) => {
                    ui.codesizeFlash.hidden = inst.textInRAM
                }
            },
            {
                name            : "roInRAM",
                displayName     : "Place RO section in RAM",
                longDescription : "If enabled, all the RO sections will be placed in RAM. If disabled, they will be placed in Flash",
                default         : Cmn.isContextCPU2() ? true : false,
                onChange        : (inst, ui) => {
                    ui.combine_ro_rw.hidden = !inst.roInRAM
                    if(!inst.roInRAM)
                    {
                        inst.combine_ro_rw = false
                        ui.datasize.hidden    = !inst.combine_ro_rw
                        ui.rwdatasize.hidden  = inst.combine_ro_rw
                        ui.rodatasize.hidden  = inst.combine_ro_rw
                    }
                }
            },
            {
                name            : "combine_ro_rw",
                displayName     : "Place both RO and RW sections in a single APR",
                longDescription : "If enabled, both RO and RW sections in a single APR with read/write access enabled. If disabled, RO sections will be placed in a separate APR with read-only access",
                default         : false,
                hidden          : true,
                onChange        : (inst, ui) => {
                    ui.datasize.hidden    = !inst.combine_ro_rw
                    ui.rwdatasize.hidden  = inst.combine_ro_rw
                    ui.rodatasize.hidden  = inst.combine_ro_rw
                }
            },
        ]
    },
    /* {
        name        : "group_placement",
        displayName : "Section Placement",
        //style        : "tab",
        collapsed   : false,
        config      : [
            {
                name            : "textInRAM",
                displayName     : "Place the .text section in RAM",
                longDescription : "If enabled, all the .text sections from selected files/libraries will be run from RAM. If disabled, only functions marked as ramfunc will be run from RAM",
                default         : false,
                onChange        : (inst, ui) => {
                    ui.codesizeFlash.hidden = inst.textInRAM
                }
            },
            {
                name            : "roInRAM",
                displayName     : "Place RO section in RAM",
                longDescription : "If enabled, all the RO sections will be placed in RAM. If disabled, they will be placed in Flash",
                default         : false,
                onChange        : (inst, ui) => {
                    ui.combine_ro_rw.hidden = !inst.roInRAM
                    if(!inst.roInRAM)
                    {
                        inst.combine_ro_rw = false
                        ui.datasize.hidden    = !inst.combine_ro_rw
                        ui.rwdatasize.hidden  = inst.combine_ro_rw
                        ui.rodatasize.hidden  = inst.combine_ro_rw
                    }
                }
            },
            {
                name            : "combine_ro_rw",
                displayName     : "Place both RO and RW sections in a single APR",
                longDescription : "If enabled, both RO and RW sections in a single APR with read/write access enabled. If disabled, RO sections will be placed in a separate APR with read-only access",
                default         : false,
                hidden          : true,
                onChange        : (inst, ui) => {
                    ui.datasize.hidden    = !inst.combine_ro_rw
                    ui.rwdatasize.hidden  = inst.combine_ro_rw
                    ui.rodatasize.hidden  = inst.combine_ro_rw
                }
            },
        ]
    }, */
    {
        name        : "group_size",
        displayName : "Code & Data - Sizes",
        //style        : "tab",
        collapsed   : false,
        config      : [
            {
                name       : "codesizeFlash",
                displayName: "Code size in Flash (in kB)",
                default    : Cmn.isContextCPU1() ? 4 : 0,
            },
            {
                name       : "codesizeRAM",
                displayName: "Code size in RAM (in kB)",
                default    : 4,
            },
            {
                name       : "rwdatasize",
                displayName: "RW Data size in RAM (in kB)",
                default    : 4
            },
            {
                name       : "rodatasize",
                displayName: "RO Data size in Flash / RAM (in kB)",
                default    : Cmn.isContextCPU1() ? 4 : 0
            },
            {
                name       : "datasize",
                displayName: "RW/RO Data size in RAM (in kB)",
                default    : 4,
                hidden     : true
            },
        ]
    },
    {
        name        : "group_periph",
        displayName : "Peripheral Access",
        //style        : "tab",
        collapsed   : false,
        config      : [
            {
                name          : "periphs_rw",
                displayName   : "Peripherals with RW access",
                default       : [],
                minSelections : 0,
                options       : () => {return peripheralData.getPeriphsSortedbyFrame().map(x=> { return {name: x.name}})},
                disableSelectAll : true,
            },
            {
                name          : "periphs_ro",
                displayName   : "Peripherals with RO access",
                default       : [],
                minSelections : 0,
                options       : () => {return peripheralData.getPeriphsSortedbyFrame().map(x=> { return {name: x.name}})},
                disableSelectAll : true,
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
    },
    {
        name        : "group_moduleAPRs",
        displayName : "Auto-Generated Components",
        //style        : "tab",
        collapsed   : true,
        config      : [
        ]
    }
];

function validate(inst, vo)
{
    ['codesizeFlash', 'codesizeRAM', 'rwdatasize', 'rodatasize', 'datasize'].forEach((x)=>{
        if((inst[x] %4) != 0)
            vo.logError("Memory Size should be multiple of 4kB" , inst, x);
    })

    let bankmode = Common.getBankModeConfig();

    if(inst.codesizeFlash > 0){
        if(Cmn.isContextCPU2()){
            vo.logError("Current core doesn't have flash access" , inst, 'codesizeFlash');
        }
        if(Cmn.isContextCPU3() && bankmode<2){
            vo.logError("Current core doesn't have flash access" , inst, 'codesizeFlash');
        }
    }

    if(inst.rodatasize > 0 && !inst.roInRAM){
        if(Cmn.isContextCPU2()){
            vo.logError("Current core doesn't have flash access" , inst, 'rodatasize');
        }
        if(Cmn.isContextCPU3() && bankmode<2){
            vo.logError("Current core doesn't have flash access" , inst, 'rodatasize');
        }
    }

    //!! Check if LINK1 has correct peripheral boot APRs
    if(inst.isLink1){

    }
}

function dependentModuleInstances(inst){

    let components = []
    return components
}
function moduleInstances(inst)
{
    let components = []

    var add_codeAPR_Flash = inst.codesizeFlash && !inst.textInRAM
    var add_codeAPR_RAM   = inst.codesizeRAM
    var add_dataAPR_RW    = inst.rwdatasize && !inst.combine_ro_rw
    var add_dataAPR_RO    = inst.rodatasize && !inst.combine_ro_rw
    var add_dataAPR       = inst.datasize && inst.combine_ro_rw

    if(add_codeAPR_Flash && !(inst.codesizeFlash%4))
        components.push(
            {
                name: "codeAPR_Flash",
                displayName: "Code APR (Flash)",
                moduleName: "/ti/security/APR",
                collapsed: true,
                hidden : false,
                group : "group_moduleAPRs",
                requiredArgs:{
                    $name           : inst.$name + "_codeAPR_Flash",
                    type            : "Code",
                    memType         : "Flash",
                    memSize         : inst.codesizeFlash,
                    specialAprStatus: inst.isLink2 ? "link2_flash_code" : "none"
                }
            }
        )

    if(add_codeAPR_RAM && !(inst.codesizeRAM%4))
        components.push(
            {
                name: "codeAPR_RAM",
                displayName: "Code APR (RAM)",
                moduleName: "/ti/security/APR",
                collapsed: true,
                hidden : false,
                group : "group_moduleAPRs",
                requiredArgs:{
                    $name           : inst.$name + "_codeAPR_RAM",
                    type            : "Code",
                    memType         : "RAM",
                    memSize         : inst.codesizeRAM,
                    specialAprStatus: inst.isLink2 ? "link2_ram_code" : "none"
                }
            }
        )

    if(add_dataAPR_RW && !(inst.rwdatasize%4))
        components.push(
            {
                name: "dataAPR_RW",
                displayName: "RW Data APR (RAM)",
                moduleName: "/ti/security/APR",
                collapsed: true,
                hidden : false,
                group : "group_moduleAPRs",
                requiredArgs:{
                    $name           : inst.$name + "_dataAPR_RW",
                    type            : "Data",
                    memType         : "RAM",
                    memSize         : inst.rwdatasize,
                }
            }
        )

    if(add_dataAPR_RO && !(inst.rodatasize%4))
        components.push(
            {
                name: "dataAPR_RO",
                displayName: "RO Data APR (Flash)",
                moduleName: "/ti/security/APR",
                collapsed: true,
                hidden : false,
                group : "group_moduleAPRs",
                requiredArgs:{
                    $name           : inst.$name + "_dataAPR_RO",
                    type            : "Code",
                    memType         : inst.roInRAM ? "RAM"  : "Flash",
                    memSize         : inst.rodatasize,
                }
            }
        )

    if(add_dataAPR && !(inst.datasize%4))
        components.push(
            {
                name: "dataAPR",
                displayName: "RW Data APR (RAM)",
                moduleName: "/ti/security/APR",
                collapsed: true,
                hidden : false,
                group : "group_moduleAPRs",
                requiredArgs:{
                    $name           : inst.$name + "_dataAPR",
                    type            : "Data",
                    memType         : "RAM",
                    memSize         : inst.datasize,
                }
            }
        )

    components.push(
        {
            name: "Link",
            displayName: "LINK",
            moduleName: "/ti/security/Link",
            collapsed: true,
            hidden : false,
            group : "group_moduleAPRs",
            requiredArgs:{
                $name            : inst.$name + "_Link",
                easyModeGenerated: true,
                isLink1          : inst.isLink1,
                isLink2          : inst.isLink2
            }
        }
    )

    return components;
}

exports = {
    displayName  : 'Link',
    defaultInstanceName : "AppModule",
    config,
    validate,
    moduleInstances,


};