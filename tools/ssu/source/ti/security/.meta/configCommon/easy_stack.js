const Common    = system.getScript('/ti/security/Common.js');
let check       = Common.isAllocationSetupMode() ? true : false
const currentContext    = system.context;

let config =
[
    {
        name    : "$name",
        hidden  : false,
    },
    {
        name        : 'zone',
        displayName : 'Zone',
        options     : [1,2,3].map(x=> {return {name: "ZONE" + x}}),
        default     : "ZONE1",
    },
    {
        name        : 'modules',
        displayName : 'Modules',
        default     : [],
        options     : (inst) =>
        {
            let corePrefix  = Common.getCurrentCorePrefix(inst)
            let links = Common.modInstances(`/ti/security/${corePrefix}EasyMode_link`, inst)
            if(links && links.length)
            {
                return links.map(x=>{return {name: x.Link.$name};})
            }
            return []
        },
    },
    {
        name        : 'secGroupAttr',
        displayName : "Unprotected cross-STACK calls",
        default     : "NONE",
        options     :
        [
            {name : "NONE",           displayName : "Generate Linker error"},
            {name : "PUBLIC",         displayName : "Add linker trampolines and landing pads (Secure)"},
            {name : "PUBLIC_TRUSTED", displayName : "Add linker trampolines and landing pads (Unsecure, Faster)"},
        ]
    },
    {
        name        : 'stackAPRsize',
        displayName : 'Stack memory APR size (in kB)',
        default     : 4,
    },
    {
        name        : 'stacksize',
        displayName : 'Actual Stack size (in Bytes)',
        default     : 0x100,
    },
]


function validate(inst, vo)
{
    let corePrefix  = Common.getCurrentCorePrefix(inst)
    let corePermaPrefix = check ? corePrefix : currentContext + "_"

    let l2 = undefined
    l2 = Common.modInstances(`/ti/security/${corePrefix}Link`, inst).forEach(l => { return l.$name == (corePermaPrefix + "LINK2_Link") })

    // CHECK: LINK2 must be associated with STACK2
    if(inst.$name == (corePermaPrefix + "STACK2"))
    {
        if(l2 && !inst.modules.includes(corePermaPrefix + "LINK2_Link"))
        {
            vo.logError("LINK2 must be associated with STACK2", inst, "modules")
        }
    }
}

function moduleInstances(inst)
{
    let corePrefix  = Common.getCurrentCorePrefix(inst)
    let components = []

    components.push
    ({
        name            : "stackMem",
        displayName     : "Stack Memory Region",
        longDescription : "A stack region of specified size will be created and placed in an APR which is RW accessible to all Application Modules within this Sandbox. Remaining bytes in the APR can be used to store additional data sections (can be added below)",
        moduleName      : `/ti/security/${corePrefix}EasyMode_sharedMem`,
        collapsed       : true,
        requiredArgs    :
        {
            $name       : inst.$name + "_stack_mem",
            isStackMem  : true,
            type        : "RAM",
            datasize    : inst.stackAPRsize,
        }
    })

    components.push
    ({
            name        : "stack",
            displayName : "STACK",
            moduleName  : `/ti/security/${corePrefix}Stack`,
            collapsed   : true,
            hidden      : true,
            requiredArgs:
            {
                $name               : inst.$name + "_STACK",
                size                : inst.stacksize,
                zone                : inst.zone,
                secGroupAttr        : inst.secGroupAttr,
                easyModeGenerated   : true,
            },
            args:
            {
                stackAPR:
                {
                    memSize : inst.stackAPRsize,
                }
            }
    })

    return components;
}

exports =
{
    validate            : validate,
    config              : config,
    moduleInstances     : moduleInstances
};