const Common = system.getScript('/ti/security/Common.js');
let sysSec   = system.getScript('/ti/security/System_Security');

let config = [
    {
        name: "$name",
        hidden: false,
    },
    {
        name           : 'zone',
        displayName    : 'Zone',
        options        : [1,2,3].map(x=> {return {name: "ZONE" + x}}),
        default        : "ZONE1",
    },
    {
        name           : 'modules',
        displayName    : 'Modules',
        default        : [],
        options        : () => {
            let links = Common.modInstances('/ti/security/EasyMode_link')
            if(links && links.length){
                return links.map(x=>{return {name: x.Link.$name};})
            }
            return []
        },
    },
    {
        name           : 'secGroupAttr',
        displayName    : "Unprotected cross-STACK calls",
        default        : "NONE",
        options        : [
            {name : "NONE",           displayName : "Generate Linker error"},
            {name : "PUBLIC",         displayName : "Add linker trampolines and landing pads (Secure)"},
            {name : "PUBLIC_TRUSTED", displayName : "Add linker trampolines and landing pads (Unsecure, Faster)"},
        ]
    },
    {
        name           : 'stackAPRsize',
        displayName    : 'Stack memory APR size (in kB)',
        default        : 4,
    },
    {
        name           : 'stacksize',
        displayName    : 'Actual Stack size (in Bytes)',
        default        : 0x100,
    },
]


function validate(inst, vo)
{
    let l2 = undefined
    l2 = Common.modInstances('/ti/security/Link').forEach(l => { return l.$name == "LINK2_Link" })

    // LINK2 must be associated with STACK2
    if(inst.$name == "STACK2"){
        if(l2 && !inst.modules.includes("LINK2_Link")){
            vo.logError("LINK2 must be associated with STACK2", inst, "modules")
        }
    }
}


exports = {
    displayName  : 'EasyMode',
    defaultInstanceName: 'Sandbox',
    validate,
    config,
    moduleInstances : (inst) => {
        return [
            {
                name           : "stackMem",
                displayName    : "Stack Memory Region",
                longDescription: "A stack region of specified size will be created and placed in an APR which is RW accessible to all modules within this sandbox. Remaining bytes in the APR can be used to store additional data sections (can be added below)",
                moduleName     : "/ti/security/EasyMode_sharedMem",
                collapsed      : true,
                requiredArgs   : {
                    $name       : inst.$name + "_stack_mem",
                    isStackMem  : true,
                    type        : "RAM",
                    datasize    : inst.stackAPRsize,
                }
            },
            {
                name        : "stack",
                displayName : "STACK",
                moduleName  : "/ti/security/Stack",
                collapsed   : true,
                hidden      : true,
                requiredArgs: {
                    $name            : inst.$name + "_STACK",
                    size             : inst.stacksize,
                    zone             : inst.zone,
                    secGroupAttr     : inst.secGroupAttr,
                    easyModeGenerated: true,
                    
                },
                args: {
                    stackAPR         : {
                        memSize         : inst.stackAPRsize,
                    }
                }
            }
        ]
    },
};