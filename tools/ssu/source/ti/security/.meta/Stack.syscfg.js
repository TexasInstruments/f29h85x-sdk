const Common = system.getScript('/ti/security/Common.js');

let config = [
    { name: '$name', startingIndex:3},
    {
        name             : 'links',
        displayName      : 'LINKs',
        options          : () => Common.modInstances('/ti/security/Link'),
        isArray          : true,
    },
    {
        name             : 'linksEasy',
        displayName      : 'LINKs',
        options          : () => Common.modInstNames('/ti/security/Link'),
        default          : [],
        minSelections    : 0,
        hidden           : true,
        getValue         : (inst) => {
            if(inst.easyModeGenerated)
                return inst.$ownedBy.modules//.map(x => x.Link.$name)          
            else
                return []
        }
    },
    {
        name           : 'size',
        displayName    : 'Stack size (in Bytes)',
        default        : 0x100,
    },
    {
        name           : 'zone',
        displayName    : 'ZONE',
        default        : "ZONE1",
        options        : [1,2,3].map(x=> {return {name: "ZONE" + x}}),
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
        name    : "easyModeGenerated",
        default : false,
        hidden  : true,
        onChange : (inst, ui) => {
            ui.links.hidden      = inst.easyModeGenerated
            ui.linksEasy.hidden      = !inst.easyModeGenerated
        }
    }
];

function validate(inst, vo)
{
    // Check for System Security module
    const sysSec = Common.modStatic('/ti/security/System_Security');
    if(!sysSec)
        vo.logError("System security module must be added to configure STACKs", inst)

    // Check if links selected are used in other stacks
    _.without(Common.modInstances('/ti/security/Stack'), inst).forEach(stack => {
        var linkNames = stack.easyModeGenerated ? stack.linksEasy : stack.links.map(x=>{return x.$name})

        inst.links.
            filter(link => linkNames.includes(link.$name)).
            forEach(link => vo.logError(link.$name + " is already added in " + stack.$name, inst, 'links'))

        inst.linksEasy.
            filter(link => linkNames.includes(link)).
            forEach(link => vo.logError(link + " is already added in " + stack.$name, inst, 'linksEasy'))
    })


    // Check if the stack size is larger than APR size
    if(inst.size > (inst.stackAPR.memSize * 1024))
        vo.logError("Stack size is greater than the APR size", inst, 'size');

    // Check if Link1 or Link2 is included in STACK3+
    if((inst.$name != "STACK2_STACK")) {
        var link2 = Common.modInstances('/ti/security/Link').filter(x=>x.isLink2)
        if(link2[0]){
            link2 = link2[0]
            if(inst.links.includes(link2))
                vo.logError("LINK2 cannot be part of this stack", inst, 'links')
            if(inst.linksEasy.includes(link2.$name))
                vo.logError("LINK2 cannot be part of this stack", inst, 'linksEasy')
        }

    }
    if((inst.$name != "STACK1_STACK")) {
        var link1 = Common.modInstances('/ti/security/Link').filter(x=>x.isLink1)
        if(link1[0]){
            link1 = link1[0]
            if(inst.links.includes(link1))
                vo.logError("LINK1 cannot be part of this stack", inst, 'links')
            if(inst.linksEasy.includes(link1.$name))
                vo.logError("LINK1 cannot be part of this stack", inst, 'linksEasy')
        }
    }

}


function moduleInstances(inst)
{
    let components = []
    components.push(
        {
            name: "stackAPR",
            displayName: "Stack APR",
            moduleName: "/ti/security/APR",
            collapsed: false,
            requiredArgs:{
                $name : inst.$name.replace("_STACK", "") + "_stackmem_apr",
                type : "Data",
                memType : "RAM",
                specialAprStatus: "stack_mem"
            }
        }
    )
    return components;
}
exports = {
    displayName         : 'STACK',
    defaultInstanceName : 'STACK_10',
    maxInstances        : 7,
    validate,
    config,
    moduleInstances
};
