const Common = system.getScript('/ti/security/Common.js');
let check       = Common.isAllocationSetupMode() ? true : false
const currentContext    = system.context;

let config =
[
    {   name            : '$name',
        startingIndex   : 3
    },
    {
        name        : 'links',
        displayName : 'LINKs',
        options     : (inst) =>
        {
            let corePrefix  = Common.getCurrentCorePrefix(inst)
            return Common.modInstances(`/ti/security/${corePrefix}Link`, inst)
        },
        isArray     : true,
    },
    {
        name            : 'linksEasy',
        displayName     : 'LINKs',
        options         : (inst) => Common.modInstanceNames('/ti/security/Link', inst),
        default         : [],
        minSelections   : 0,
        hidden          : true,
        getValue        : (inst) =>
        {
            if(inst.easyModeGenerated)
                return inst.$ownedBy.modules
            else
                return []
        }
    },
    {
        name        : 'size',
        displayName : 'Software stack size (in Bytes)',
        default     : 0x100,
    },
    {
        name        : 'zone',
        displayName : 'ZONE',
        default     : "ZONE1",
        options     : [1,2,3].map(x=> {return {name: "ZONE" + x}}),
    },
    {
        name        : 'secGroupAttr',
        displayName : "Unprotected cross-STACK call behaviour",
        default     : "NONE",
        options     :
        [
            {name : "NONE",           displayName : "Generate Linker error"},
            {name : "PUBLIC",         displayName : "Add linker trampolines and landing pads (Secure)"},
            {name : "PUBLIC_TRUSTED", displayName : "Add linker trampolines and landing pads (Unsecure, Faster)"},
        ]
    },
    {
        name    : "easyModeGenerated",
        default : false,
        hidden  : true,
        onChange : (inst, ui) =>
        {
            ui.links.hidden     = inst.easyModeGenerated
            ui.linksEasy.hidden = !inst.easyModeGenerated
        }
    }
];

function validate(inst, vo)
{
    let corePrefix      = Common.getCurrentCorePrefix(inst)
    let corePermaPrefix = check ? corePrefix : currentContext + "_"

    // Check for System Security module
    const sysSec        = Common.modStatic(`/ti/security/${corePrefix}System_Security`, inst);
    const createdLINKs  = Common.modInstances(`/ti/security/${corePrefix}Link`, inst)
    const createdSTACKs = Common.modInstances(`/ti/security/${corePrefix}Stack`, inst)

    // CHECK: System Security module exists
    if(!sysSec)
        vo.logError("System Security module must be added to configure STACKs", inst)

    // CHECK: No duplication of LINKs across STACKs
    _.without(createdSTACKs, inst).forEach(stack =>
    {
        let linkNames = stack.easyModeGenerated ? stack.linksEasy : stack.links.map(x=>{return x.$name})

        inst.links.
            filter(link => linkNames.includes(link.$name)).
            forEach(link => vo.logError(link.$name + " is already added in " + stack.$name, inst, 'links'))

        inst.linksEasy.
            filter(link => linkNames.includes(link)).
            forEach(link => vo.logError(link + " is already added in " + stack.$name, inst, 'linksEasy'))
    })


    // CHECK: STACK mem size larger than APR size
    if(inst.size > (inst.stackAPR.memSize * 1024))
        vo.logError("Stack memory size is greater than APR size", inst, 'size');

    // CHECK: Link1 or Link2 in correct STACKs
    if((inst.$name != (corePermaPrefix + "STACK2_STACK")))
    {
        let link2 = createdLINKs.filter(x=>x.isLink2)
        if(link2[0])
        {
            link2 = link2[0]
            if(inst.links.includes(link2))
                vo.logError("LINK2 cannot be part of this STACK", inst, 'links')

            if(inst.linksEasy.includes(link2.$name))
                vo.logError("LINK2 cannot be part of this STACK", inst, 'linksEasy')
        }
    }

    if((inst.$name != (corePermaPrefix + "STACK1_STACK")))
    {
        let link1 = createdLINKs.filter(x=>x.isLink1)
        if(link1[0])
        {
            link1 = link1[0]

            if(inst.links.includes(link1))
                vo.logError("LINK1 cannot be part of this STACK", inst, 'links')

            if(inst.linksEasy.includes(link1.$name))
                vo.logError("LINK1 cannot be part of this STACK", inst, 'linksEasy')
        }
    }
}


function moduleInstances(inst)
{
    let corePrefix  = Common.getCurrentCorePrefix(inst)
    let components = []

    components.push
    ({
        name        : "stackAPR",
        displayName : "Stack APR",
        moduleName  : `/ti/security/${corePrefix}APR`,
        collapsed   : false,
        requiredArgs:
        {
            $name           : inst.$name.replace(new RegExp('_STACK$'), "") + "_stackmem_apr",
            type            : "Data",
            memType         : "RAM",
            specialAprStatus: "stack_mem"
        }
    })

    return components;
}

exports =
{
    config: config,
    validate: validate,
    moduleInstances: moduleInstances
}