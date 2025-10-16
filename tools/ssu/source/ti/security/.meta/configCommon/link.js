const Common            = system.getScript('/ti/security/Common.js');
const ssuData           = system.getScript('/ti/security/device_specific_information/ssu_data.js');
const currentContext    = system.context;

let check = Common.isAllocationSetupMode() ? true : false

function onChangeEasyModeLink(inst, ui)
{
    const hiddenEasy = inst.easyModeGenerated
    const hidden    = !hiddenEasy

    // Manual
    ui.codeAPRs.hidden      = hiddenEasy
    ui.APIAPRs.hidden       = hiddenEasy
    ui.interrupts.hidden    = hiddenEasy
    ui.interruptsAPI.hidden = hiddenEasy

    // Easy mode
    ui.codeAPRsEasy.hidden      = hidden
    ui.readAPRsEasy.hidden      = hidden
    ui.readwriteAPRsEasy.hidden = hidden
    ui.APIAPRsEasy.hidden       = hidden
    ui.interruptsEasy.hidden    = hidden
    ui.interruptsAPIEasy.hidden = hidden

    // Manual but still needed for adding custom regions in easy mode
    ui.readAPRs.hidden      = hidden
    ui.readwriteAPRs.hidden = hidden
}

let config =
[
    {
        name            : '$name',
        startingIndex   :  3
    },
    {
        name            : "isLink1",
        displayName     : 'Use as LINK1',
        longDescription : "Use this Link as LINK1 (Bootloader Link)",
        default         : false,
    },
    {
        name            : "isLink2",
        displayName     : 'Use as LINK2',
        longDescription : "Use this Link as LINK2 (Most secure Link)",
        default         : false,
    },
    {
        name        : "memoryAccess",
        displayName : 'Memory Region Access Permissions',
        collapsed   : false,
        config      :
        [
            // Custom settings
            {
                name                : 'codeAPRs',
                displayName         : 'Code Regions',
                default             : [],
                disableSelectAll    : true,
                options             : (inst) =>
                {
                    let reqdContext = check ? Common.getCurrentCorePrefix(inst).slice(0,-1) : currentContext;
                    let list = Common.allocateAllMemoryRegions()[reqdContext]
                    if(list)
                    {
                        return  list
                                .filter(x => x.type == "Code")
                                .map(x => {return {name: x.name}})
                    }

                    return []
                },
            },
            {
                name                : 'readAPRs',
                displayName         : 'Regions with Read-Only access',
                default             : [],
                disableSelectAll    : true,
                options             : (inst) =>
                {
                    let reqdContext = check ? Common.getCurrentCorePrefix(inst).slice(0,-1) : currentContext;
                    let list = Common.allocateAllMemoryRegions()[reqdContext]
                    if(list)
                    {
                        if(inst.easyModeGenerated)
                        {
                            list = list.filter(x => x.type == "Data" && !inst.readAPRsEasy.includes(x.name))
                        }
                        return  list
                                .filter(x => x.type != "Code" &&
                                            !x.name.endsWith("_stackmem_apr") && //!! tag
                                             x.name != "APR_RESERVED_sign_CPU1" &&
                                             x.name != "APR_RESERVED_sign_CPU3") //!! tag
                                .map(x => {return {name: x.name}})
                    }
                    return []
                },
            },
            {
                name                : 'readwriteAPRs',
                displayName         : 'Regions with Read-Write access',
                default             : [],
                disableSelectAll    : true,
                options             : (inst) =>
                {
                    let reqdContext = check ? Common.getCurrentCorePrefix(inst).slice(0,-1) : currentContext;
                    let list = Common.allocateAllMemoryRegions()[reqdContext]
                    if(list)
                    {
                        if(inst.easyModeGenerated)
                        {
                            list = list.filter(x => x.type == "Data" && !inst.readwriteAPRsEasy.includes(x.name))
                        }
                        return  list
                                .filter(x => x.type != "Code" &&
                                            !x.name.endsWith("_stackmem_apr") && //!! tag
                                             x.name != "APR_RESERVED_sign_CPU1" &&
                                             x.name != "APR_RESERVED_sign_CPU3") //!! tag
                                .map(x => {return {name: x.name}})
                    }
                    return []
                },
            },
            {
                name                : 'APIAPRs',
                displayName         : 'Regions with Access Protection Inheritance',
                default             : [],
                disableSelectAll    : true,
                options             : (inst) =>
                {
                    let reqdContext = check ? Common.getCurrentCorePrefix(inst).slice(0,-1) : currentContext;
                    let list = Common.allocateAllMemoryRegions()[reqdContext]
                    if(list)
                    {
                        return  list
                                .filter(x => x.type != "Code" &&
                                             x.name != "APR_RESERVED_sign_CPU1" &&
                                             x.name != "APR_RESERVED_sign_CPU3" /* &&   //!! tag
                                             !x.name.includes("APR_Boot_") */)
                                .map(x => {return {name: x.name}})
                    }
                    return []
                },
            },

            // Easy Mode Settingss
            {
                name            : 'codeAPRsEasy',
                displayName     : 'Default Code Regions',
                default         : [],
                minSelections   : 0,
                hidden          : true,
                options         : (inst) =>
                {
                    let reqdContext = check ? Common.getCurrentCorePrefix(inst).slice(0,-1) : currentContext;
                    let list = Common.allocateAllMemoryRegions()[reqdContext]
                    if(list)
                        return list.map(x => {return {name: x.name}})
                    return []
                },
                getValue        : (inst) =>
                {
                    let list = []
                    if(inst.easyModeGenerated)
                    {
                        if(inst.$ownedBy.codeAPR_Flash)
                            list.push(inst.$ownedBy.codeAPR_Flash.$name)
                        if(inst.$ownedBy.codeAPR_RAM)
                            list.push(inst.$ownedBy.codeAPR_RAM.$name)
                    }
                    return list
                }
            },

            {
                name            : 'readAPRsEasy',
                displayName     : 'Default regions with Read-Only access',
                default         : [],
                minSelections   : 0,
                hidden          : true,
                options         : (inst) =>
                {
                    let reqdContext = check ? Common.getCurrentCorePrefix(inst).slice(0,-1) : currentContext;
                    let list = Common.allocateAllMemoryRegions()[reqdContext]
                    if(list)
                        return list.map(x => {return {name: x.name}})
                    return []
                },
                getValue        : (inst) =>
                {
                    let list = []
                    let corePrefix  = Common.getCurrentCorePrefix(inst)
                    let corePermaPrefix = check ? corePrefix : currentContext + "_"
                    let reqdContext = check ? corePrefix.slice(0,-1) : currentContext;
                    if(inst.easyModeGenerated)
                    {
                        if(inst.$ownedBy.dataAPR_RO)
                            list.push(inst.$ownedBy.dataAPR_RO.$name)

                        if(inst.$ownedBy.$name == (corePermaPrefix + "LINK1") && Common.isContextCPU1(inst))
                                list.push("APR_RESERVED_sign_CPU1")

                        if(inst.$ownedBy.$name == (corePermaPrefix + "LINK1") && Common.isContextCPU3(inst))
                                list.push("APR_RESERVED_sign_CPU3")

                        Common.modInstances(`/ti/security/${corePrefix}EasyMode_sharedMem`, inst).forEach(x =>
                        {
                            if(x.module_ro.includes(inst.$ownedBy))
                                list.push(x.APR.$name)
                        })

                        let autoPeriphPermissions = Common.getAutoPeriphAPRsByLink(inst.$ownedBy.$name, reqdContext)
                        autoPeriphPermissions["RO"].forEach(x => list.push(x))
                    }
                    return list
                }
            },
            {
                name            : 'readwriteAPRsEasy',
                displayName     : 'Default regions with Read-Write access',
                default         : [],
                minSelections   : 0,
                hidden          : true,
                options         : (inst) =>
                {
                    let reqdContext = check ? Common.getCurrentCorePrefix(inst).slice(0,-1) : currentContext;
                    let list = Common.allocateAllMemoryRegions()[reqdContext]
                    if(list)
                        return list.map(x => {return {name: x.name}})
                    return []
                },
                getValue        : (inst) =>
                {
                    let corePrefix  = Common.getCurrentCorePrefix(inst)
                    let reqdContext = check ? corePrefix.slice(0,-1) : currentContext;
                    let list = []
                    if(inst.easyModeGenerated)
                    {
                        if(inst.$ownedBy.dataAPR_RW)
                            list.push(inst.$ownedBy.dataAPR_RW.$name)
                        if(inst.$ownedBy.dataAPR)
                            list.push(inst.$ownedBy.dataAPR.$name)

                        Common.modInstances(`/ti/security/${corePrefix}EasyMode_sharedMem`, inst).forEach(x =>
                        {
                            if(x.module_rw.includes(inst.$ownedBy))
                                list.push(x.APR.$name)
                        })

                        let autoPeriphPermissions = Common.getAutoPeriphAPRsByLink(inst.$ownedBy.$name, reqdContext)
                        autoPeriphPermissions["RW"].forEach(x => list.push(x))
                    }
                    return list
                }
            },
            {
                name            : 'APIAPRsEasy',
                displayName     : 'Default regions with Access Protection Inheritance',
                default         : [],
                minSelections   : 0,
                hidden          : true,
                options         : (inst) =>
                {
                    let reqdContext = check ? Common.getCurrentCorePrefix(inst).slice(0,-1) : currentContext;
                    let list = Common.allocateAllMemoryRegions()[reqdContext]
                    if(list)
                        return list.map(x => {return {name: x.name}})
                    return []
                },
                getValue        : (inst) =>
                {
                    if(inst.easyModeGenerated && inst.$ownedBy.isCommonCode)
                    {
                        let reqdContext = check ? Common.getCurrentCorePrefix(inst).slice(0,-1) : currentContext;
                        let list = Common.allocateAllMemoryRegions()[reqdContext]
                        if(list)
                        {
                            return  list
                                    .filter( x => x.type != "Code" &&
                                             !inst.readAPRsEasy.includes(x.name) &&
                                             !inst.readwriteAPRsEasy.includes(x.name) &&
                                             x.name != "APR_RESERVED_sign_CPU1" &&
                                             x.name != "APR_RESERVED_sign_CPU3" ||
                                             (x.type === "Code" && x.memType === "RAM"))
                                    .map( x => x.name)
                        }
                        else
                            return []
                    }
                    else
                        return []
                }
            },
        ]
    },
    {
        name        : "ints",
        displayName : 'Interrupt Configuration',
        collapsed   : false,
        config      :
        [
            {
                name            : 'interrupts',
                displayName     : 'Interrupts included in this LINK',
                longDescription : 'User should make sure the ISR is placed in one of the code memory regions',
                options         : () => Common.modInstances('/driverlib/interrupt.js'),
                isArray         : true,
                disableSelectAll: true,
            },
            {
                name            : 'interruptsEasy',
                displayName     : 'Interrupts included in this LINK',
                longDescription : 'User should make sure the ISR is placed in one of the code memory regions',
                options         : () => Common.modInstanceNames('/driverlib/interrupt.js'),
                default         : [],
                minSelections   : 0,
                hidden          : true,
                getValue        : (inst) =>
                {
                    if(inst.easyModeGenerated)
                        return inst.$ownedBy.interrupts.map(x=>{return x.$name})
                    else
                        return []
                }
            },
            {
                name            : 'interruptsAPI',
                displayName     : 'Interrupts with Access Protection Inheritance ',
                options         : () => Common.modInstances('/driverlib/interrupt.js'),
                isArray         : true,
                disableSelectAll: true,
            },
            {
                name            : 'interruptsAPIEasy',
                displayName     : 'Interrupts with Access Protection Inheritance ',
                options         : () => Common.modInstanceNames('/driverlib/interrupt.js'),
                default         : [],
                minSelections   : 0,
                hidden          : true
            },
        ]
    },
    {
        name    : "easyModeGenerated",
        default : false,
        hidden  : true,
        onChange: (inst, ui) => onChangeEasyModeLink(inst, ui)
    },
];

function validate(inst, vo)
{
    let corePrefix  = Common.getCurrentCorePrefix(inst)
    // Check if codeAPRs / APIAPRs / interrupts selected are used in other links
    _.without(Common.modInstances(`/ti/security/${corePrefix}Link`, inst), inst).forEach(link =>
    {
        const isLinkEasyModeGenerated = link.easyModeGenerated

        let codeAPRNames        = isLinkEasyModeGenerated ? link.codeAPRsEasy      : link.codeAPRs
        let APIAPRNames         = isLinkEasyModeGenerated ? link.APIAPRsEasy       : link.APIAPRs
        let interruptNames      = isLinkEasyModeGenerated ? link.interruptsEasy    : link.interrupts
        let interruptAPINames   = isLinkEasyModeGenerated ? link.interruptsAPIEasy : link.interruptsAPI

        // codeAPRs
        inst.codeAPRs.
            filter(apr => codeAPRNames.includes(apr)).
            forEach(apr => vo.logError(apr + " is already added in " + link.$name, inst, 'codeAPRs'))

        inst.codeAPRsEasy.
            filter(apr => codeAPRNames.includes(apr)).
            forEach(apr => vo.logError(apr + " is already added in " + link.$name, inst, 'codeAPRsEasy'))

        // APIAPRs
        inst.APIAPRs.
            filter(apr => APIAPRNames.includes(apr)).
            forEach(apr => vo.logError(apr + " is already added in " + link.$name, inst, 'APIAPRs'))

        inst.APIAPRsEasy.
            filter(apr => APIAPRNames.includes(apr)).
            forEach(apr => vo.logError(apr + " is already added in " + link.$name, inst, 'APIAPRsEasy'))

        // interrupts
        inst.interrupts.
            filter(int => interruptNames.includes(int)).
            forEach(int => vo.logError(int.$name + " is already added in " + link.$name, inst, 'interrupts'))

        inst.interruptsEasy.
            filter(int => interruptNames.includes(int)).
            forEach(int => vo.logError(int + " is already added in " + link.$name, inst, 'interruptsEasy'))

        // interruptsAPI
        inst.interruptsAPI.
            filter(int => interruptAPINames.includes(int.$name)).
            forEach(int => vo.logError(int.$name + " is already added in " + link.$name, inst, 'interruptsAPI'))

        inst.interruptsAPIEasy.
            filter(int => interruptAPINames.includes(int)).
            forEach(int => vo.logError(int + " is already added in " + link.$name, inst, 'interruptsAPIEasy'))

    });

    // CHECK: Both LINK1 and LINK2 selected
    if(inst.isLink2 && inst.isLink1)
        vo.logError("Instance cannot be configured as LINK1 and LINK2", inst, 'isLink1')

    // CHECK: Every LINK is associated with a STACK
    let coveredLinks = []
    Common.modInstances(`/ti/security/${corePrefix}Stack`, inst).forEach(stack =>
    {
        let linksList = stack.easyModeGenerated ? stack.linksEasy : stack.links.map(x=>{return x.$name})
        coveredLinks.push(...linksList)
    })
    if(!coveredLinks.includes(inst.$name))
        vo.logWarning(`${inst.$name} is not associated with a STACK. Use STACK / Sandbox in System Security to add the LINK / Application Module`, inst)

}

function validateGlobal(inst, vo)
{
    let corePrefix      =   Common.getCurrentCorePrefix(inst)
    const sysSec        =   Common.modStatic(`/ti/security/${corePrefix}System_Security`, inst);
    const createdLINKs  =   Common.modInstances(`/ti/security/${corePrefix}Link`, inst)
    const lpInterrupts  =   Common
                            .modInstances('/driverlib/interrupt.js')
                            .filter(inst => inst.interruptPriority >= inst.$module.$static.RTINT_Threshold)
                            .map(i => i.$name)

    // CHECK: System Security module exists
    if(!sysSec)
        vo.logError("System Security module must be added to configure LINKs", inst)

    // CHECK: No duplicate link1
    let link1 = createdLINKs.filter(x=>x.isLink1)
    if (link1.length > 1)
    {
        link1.forEach(x => vo.logError("Multiple links configured as LINK1", x, 'isLink1' ))
    }

    // CHECK: No duplicate link2
    let link2 = createdLINKs.filter(x=>x.isLink2)
    if (link2.length > 1)
    {
        link2.forEach(x => vo.logError("Multiple links configured as LINK2", x, 'isLink2'))
    }

    // CHECK: # of LINKs
    let userLinks = createdLINKs.filter(x=> !x.isLink1 && !x.isLink2)
    if(userLinks.length > (ssuData.instanceCount.LINK - 3))
        vo.logError("Maximum number of LINKs exceeded", inst, '')

    // CHECK: All regular interrupts are in same STACK
    let stacksWithInterrupts = new Set()
    createdLINKs.forEach(link =>
    {
        let intList = (link.isLinkEasyModeGenerated) ? link.interruptsEasy : link.interrupts.map(i => i.$name)
        if(_.intersection(intList, lpInterrupts).length > 0)
        {
            let assignedStack = check ? Common.getStackv2(link, inst) : Common.getStack(link)
            if(assignedStack)
                stacksWithInterrupts.add(assignedStack.$name)
        }
    })
    if(stacksWithInterrupts.size > 1)
        vo.logError("All INTs must be part of the same STACK. Currently multiple STACKs are used:\n- " + Array.from(stacksWithInterrupts).join("\n- "), inst, '')
}

exports =
{
    config: config,
    validate: validate,
    validateGlobal: validateGlobal
}