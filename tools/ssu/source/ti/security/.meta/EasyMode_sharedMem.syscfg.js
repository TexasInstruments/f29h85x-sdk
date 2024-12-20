const Common = system.getScript('/ti/security/Common.js');
let sysSec   = system.getScript('/ti/security/System_Security');


let config = [
    {
        name   : "$name",
        hidden : false,
    },
    {
        name    : "isStackMem",
        default : false,
        hidden  : true,
        onChange : (inst, ui) => {
            ui.module_ro.hidden  = inst.isStackMem
            ui.module_rw.hidden  = inst.isStackMem
        }
    },
    {
        name       : "type",
        displayName: "Type",
        default    : "RAM",
        options    : [
            {name : "RAM"},
            {name : "Flash"},
        ],
        onChange : (inst, ui) => {
            ui.dataFiles.hidden          = inst.type == "Flash"
            ui.customDataSections.hidden = !inst.useCustomSections || inst.type == "Flash"
            ui.module_rw.hidden          = inst.type == "Flash"
        }
    },
    {
        name       : "datasize",
        displayName: "Data size(in kB)",
        default    : 4
    },
    {
        name        : "group_sections",
        displayName : "Memory Sections",
        collapsed   : false,
        config      : [
            {
                name       : "dataFiles",
                displayName: "Include bss/data from files (comma separated)",
                default    : "",
            },
            {
                name       : "constFiles",
                displayName: "Include const/rodata from files (comma separated)",
                default    : "",
            },
            {
                name          : "useCustomSections",
                displayName   : "Use Custom Sections",
                default       : false,
                onChange      : (inst, ui) => {
                    ui.customDataSections.hidden  = !inst.useCustomSections || inst.type == "Flash"
                    ui.customConstSections.hidden = !inst.useCustomSections
                }
            },
            {
                name       : "customDataSections",
                displayName: "Include custom data sections (comma separated)",
                default    : "",
                hidden     : true
            },
            {
                name       : "customConstSections",
                displayName: "Include custom const sections (comma separated)",
                default    : "",
                hidden     : true
            },
        ]
    },
    {
        name        : "group_perm",
        displayName : "Module Access Permissions",
        collapsed   : false,
        config      : [
            {
                name        : "module_ro",
                displayName : "Modules that need read only permission",
                options     : () => Common.modInstances('/ti/security/EasyMode_link'),
                isArray : true
            },
            {
                name        : "module_rw",
                displayName : "Module that need read write permission",
                options     : () => Common.modInstances('/ti/security/EasyMode_link'),
                isArray : true
            },
        ]
    },
];

function moduleInstances(inst)
{
    let components = []

    if(!inst.isStackMem)
        components.push(
            {
                name: "APR",
                moduleName: "/ti/security/APR",
                collapsed: true,
                hidden : true,
                requiredArgs:{
                    $name : inst.$name + "_APR",
                    type : "Data",
                    memType : inst.type,
                    memSize : inst.datasize,
                }
            }
        )

    return components;
}

function validate(inst, vo)
{
}

exports = {
    displayName  : 'SharedMem',
    defaultInstanceName : "SharedMem",
        validate,
        config,
        moduleInstances,

};