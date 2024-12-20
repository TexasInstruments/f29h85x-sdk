const Common = system.getScript('/ti/security/Common.js');
const Cmn    = system.getScript("/driverlib/Common.js");
const ssuData       = system.getScript('/ti/security/device_specific_information/ssu_data.js');

let config = [
    {
        name: '$name', 
        startingIndex:  3
    },
    {
        name       : "isLink1",
        displayName: 'Use as LINK1',
        longDescription: "Use this Link as LINK1 (Bootloader Link)",
        default    : false,
    },
    {
        name       : "isLink2",
        displayName: 'Use as LINK2',
        longDescription: "Use this Link as LINK2 (Most secure Link)",
        default    : false,
    },

    // Custom settings

    {
        name       : "memoryAccess",
        displayName: 'Memory Region Access Permissions',
        collapsed  : false,
        config     : [
            {
                name             : 'codeAPRs',
                displayName      : 'Code Regions',
                default          : [],
                options          : () => {
                    let list = Common.allocateAllMemoryRegions()[system.context]
                    if(list) return list.filter(x => x.type == "Code")
                                        .map(x => {return {name: x.name}})
                    return []
                },
                disableSelectAll : true,
            },

            {
                name             : 'readAPRs',
                displayName      : 'Regions with Read-Only access',
                default          : [],
                options          : (inst) => {
                    let list = Common.allocateAllMemoryRegions()[system.context]
                    if(list){
                        if(inst.easyModeGenerated){
                            list = list.filter(x => x.type == "Data" && !inst.readAPRsEasy.includes(x.name))
                        }
                        return list.filter(x => x.type != "Code" && !x.name.endsWith("_stackmem_apr") && //!! tag
                                                x.name != "APR_RESERVED_sign_CPU1") //!! tag
                                    .map(x => {return {name: x.name}})
                    } 
                    return []
                },
                disableSelectAll : true,
            },
            
            {
                name             : 'readwriteAPRs',
                displayName      : 'Regions with Read-Write access',
                default          : [],
                options          : (inst) => {
                    let list = Common.allocateAllMemoryRegions()[system.context]
                    if(list){
                        if(inst.easyModeGenerated){
                            list = list.filter(x => x.type == "Data" && !inst.readwriteAPRsEasy.includes(x.name))
                        }
                        return list.filter(x => x.type != "Code" && !x.name.endsWith("_stackmem_apr") && //!! tag
                                                x.name != "APR_RESERVED_sign_CPU1") //!! tag
                                    .map(x => {return {name: x.name}})
                    } 
                    return []
                },
                disableSelectAll : true,
            },
            
            {
                name             : 'APIAPRs',
                displayName      : 'Regions with Access Protection Inheritance',
                default          : [],
                options          : () => {
                    let list = Common.allocateAllMemoryRegions()[system.context]
                    if(list) return list.filter(x => x.type != "Code" &&
                                                    x.name != "APR_RESERVED_sign_CPU1" /* &&   //!! tag
                                                    !x.name.includes("APR_Boot_") */)
                                                    .map(x => {return {name: x.name}})
                    return []
                },
                disableSelectAll : true,
            },

            // Easy Mode Settings

            {
                name             : 'codeAPRsEasy',
                displayName      : 'Default Code Regions',
                options          : () => {
                    let list = Common.allocateAllMemoryRegions()[system.context]
                    if(list) return list.map(x => {return {name: x.name}})
                    return []
                },
                default          : [],
                minSelections    : 0,
                hidden           : true,
                getValue         : (inst) => {
                    var list = []
                    if(inst.easyModeGenerated) {
                        if(inst.$ownedBy.codeAPR_Flash) list.push(inst.$ownedBy.codeAPR_Flash.$name)
                        if(inst.$ownedBy.codeAPR_RAM)   list.push(inst.$ownedBy.codeAPR_RAM.$name)
                    }
                    return list
                }
            },

            {
                name             : 'readAPRsEasy',
                displayName      : 'Default regions with Read-Only access',
                options          : () => {
                    let list = Common.allocateAllMemoryRegions()[system.context]
                    if(list) return list.map(x => {return {name: x.name}})
                    return []
                },
                default          : [],
                minSelections    : 0,
                hidden           : true,
                getValue         : (inst) => {
                    var list = []
                    if(inst.easyModeGenerated) {
                        if(inst.$ownedBy.dataAPR_RO) 
                            list.push(inst.$ownedBy.dataAPR_RO.$name)

                        if(inst.$ownedBy.$name == "LINK1" && Cmn.isContextCPU1())
                                list.push("APR_RESERVED_sign_CPU1")

                        Common.modInstances('/ti/security/EasyMode_sharedMem').forEach(x=> {
                            if(x.module_ro.includes(inst.$ownedBy))
                                list.push(x.APR.$name)
                        })
                        
                        let autoPeriphPermissions = Common.getAutoPeriphAPRsByLink(inst.$ownedBy.$name, system.context)
                        autoPeriphPermissions["RO"].forEach(x => list.push(x))
                    }
                    return list
                }
            },

            {
                name             : 'readwriteAPRsEasy',
                displayName      : 'Default regions with Read-Write access',
                options          : () => {
                    let list = Common.allocateAllMemoryRegions()[system.context]
                    if(list) return list.map(x => {return {name: x.name}})
                    return []
                },
                default          : [],
                minSelections    : 0,
                hidden           : true,
                getValue         : (inst) => {
                    var list = []
                    if(inst.easyModeGenerated) {
                        if(inst.$ownedBy.dataAPR_RW) list.push(inst.$ownedBy.dataAPR_RW.$name)
                        if(inst.$ownedBy.dataAPR)    list.push(inst.$ownedBy.dataAPR.$name)

                        Common.modInstances('/ti/security/EasyMode_sharedMem').forEach(x=> {
                            if(x.module_rw.includes(inst.$ownedBy))
                                list.push(x.APR.$name)
                        })

                        let autoPeriphPermissions = Common.getAutoPeriphAPRsByLink(inst.$ownedBy.$name, system.context)
                        autoPeriphPermissions["RW"].forEach(x => list.push(x))
                    }
                    return list
                }
            },

            {
                name             : 'APIAPRsEasy',
                displayName      : 'Default regions with Access Protection Inheritance',
                options          : () => {
                    let list = Common.allocateAllMemoryRegions()[system.context]
                    if(list) return list.map(x => {return {name: x.name}})
                    return []
                },
                default          : [],
                minSelections    : 0,
                hidden           : true,
                getValue         : (inst) => {
                    if(inst.easyModeGenerated && inst.$ownedBy.isCommonCode){
                        let list = Common.allocateAllMemoryRegions()[system.context]
                        if(list) return list.filter(x => x.type != "Code" &&
                                                        !inst.readAPRsEasy.includes(x.name) &&
                                                        !inst.readwriteAPRsEasy.includes(x.name) && //!! tag
                                                        x.name != "APR_RESERVED_sign_CPU1"/*  &&
                                                        !x.name.includes("APR_Boot_") */)
                                                        .map(x=>x.name)
                        else return []
                    }
                    else
                        return []
                }
            },
        ]
    },
    {
        name       : "ints",
        displayName: 'Interrupt Configuration',
        collapsed  : false,
        config     : [
            {
                name             : 'interrupts',
                displayName      : 'Interrupts included in this link',
                longDescription  : 'User should make sure the ISR is placed in one of the code memory regions',
                options          : () => Common.modInstances('/driverlib/interrupt.js'),
                isArray          : true,
                disableSelectAll : true,
            },
            {
                name             : 'interruptsEasy',
                displayName      : 'Interrupts included in this link',
                longDescription  : 'User should make sure the ISR is placed in one of the code memory regions',
                options          : () => Common.modInstNames('/driverlib/interrupt.js'),
                default          : [],
                minSelections    : 0,
                hidden           : true,
                getValue         : (inst) => {
                    if(inst.easyModeGenerated)
                        return inst.$ownedBy.interrupts.map(x=>{return x.$name})
                    else
                        return []
                }
            },
            {
                name             : 'interruptsAPI',
                displayName      : 'Interrupts with Access Protection Inheritance ',
                options          : () => Common.modInstances('/driverlib/interrupt.js'),
                isArray          : true,
                disableSelectAll : true,
            },
            {
                name             : 'interruptsAPIEasy',
                displayName      : 'Interrupts with Access Protection Inheritance ',
                options          : () => Common.modInstNames('/driverlib/interrupt.js'),
                default          : [],
                minSelections    : 0,
                hidden           : true
            },
        ]
    },
    {
        name    : "easyModeGenerated",
        default : false,
        hidden  : true,
        onChange : (inst, ui) => {
            ui.codeAPRs.hidden      = inst.easyModeGenerated
            ui.readAPRs.hidden      = !inst.easyModeGenerated
            ui.readwriteAPRs.hidden = !inst.easyModeGenerated
            ui.APIAPRs.hidden       = inst.easyModeGenerated
            ui.interrupts.hidden  = inst.easyModeGenerated
            ui.interruptsAPI.hidden = inst.easyModeGenerated

            ui.codeAPRsEasy.hidden      = !inst.easyModeGenerated
            ui.readAPRsEasy.hidden      = !inst.easyModeGenerated
            ui.readwriteAPRsEasy.hidden = !inst.easyModeGenerated
            ui.APIAPRsEasy.hidden       = !inst.easyModeGenerated
            ui.interruptsEasy.hidden    = !inst.easyModeGenerated
            ui.interruptsAPIEasy.hidden = !inst.easyModeGenerated
        }
    },

];

function validate(inst, vo)
{
    // Check if codeAPRs / APIAPRs / interrupts selected are used in other links
    _.without(Common.modInstances('/ti/security/Link'), inst).forEach(link => {
        var codeAPRNames      = link.easyModeGenerated ? link.codeAPRsEasy      : link.codeAPRs
        var APIAPRNames       = link.easyModeGenerated ? link.APIAPRsEasy       : link.APIAPRs
        var interruptNames    = link.easyModeGenerated ? link.interruptsEasy    : link.interrupts
        var interruptAPINames = link.easyModeGenerated ? link.interruptsAPIEasy : link.interruptsAPI

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
            filter(apr => interruptNames.includes(apr)).
            forEach(apr => vo.logError(apr + " is already added in " + link.$name, inst, 'interrupts'))

        inst.interruptsEasy.
            filter(apr => interruptNames.includes(apr)).
            forEach(apr => vo.logError(apr + " is already added in " + link.$name, inst, 'interruptsEasy'))

        // interruptsAPI
        inst.interruptsAPI.
            filter(apr => interruptAPINames.includes(apr.$name)).
            forEach(apr => vo.logError(apr.$name + " is already added in " + link.$name, inst, 'interruptsAPI'))

        inst.interruptsAPIEasy.
            filter(apr => interruptAPINames.includes(apr)).
            forEach(apr => vo.logError(apr + " is already added in " + link.$name, inst, 'interruptsAPIEasy'))

    });

    // Check if both link1 and link2 is enabled
    if(inst.isLink2 && inst.isLink1)
        vo.logError("Instance cannot be configured as LINK1 and LINK2", inst, 'isLink1')

    // Check if LINK is associated with a STACK
    let coveredLinks = []
    Common.modInstances('/ti/security/Stack').forEach(stack => {
        let linksList = stack.easyModeGenerated ? stack.linksEasy : stack.links.map(x=>{return x.$name})
        coveredLinks.push(...linksList)
    })
    if(!coveredLinks.includes(inst.$name))
        vo.logWarning(`${inst.$name} is not associated with a STACK. Use STACK / Sandbox in System Security to add the LINK / Application Module`, inst)

}

function validateGlobal(inst, vo)
{
    // Check for System Security module
    const sysSec = Common.modStatic('/ti/security/System_Security');
    if(!sysSec)
        vo.logError("System security module must be added to configure Links", inst)
    
    // Check for duplicate link1
    var link1 = Common.modInstances('/ti/security/Link').filter(x=>x.isLink1)
    if (link1.length > 1) {
        link1.forEach(x => {
            vo.logError("Multiple links configured as Link1", x, 'isLink1')
        })
    }

    // Check for duplicate link2
    var link2 = Common.modInstances('/ti/security/Link').filter(x=>x.isLink2)
    if (link2.length > 1) {
        link2.forEach(x => {
            vo.logError("Multiple links configured as Link2", x, 'isLink2')
        })
    }

    // Check for total number of links
    var userLinks = Common.modInstances('/ti/security/Link').filter(x=> !x.isLink1 && !x.isLink2)
    if(userLinks.length > (ssuData.instanceCount.LINK - 3))
        vo.logError("Total number of links exceeded", inst, '')

    // Check that all interrupts are in same stack
    //let a = Common.modInstances('/ti/security/Link').filter(x=> !x.isLink1 && !x.isLink2)
}

exports = {
    displayName         : 'LINK',
    defaultInstanceName : 'LINK_10',
    maxInstances        : 15,
    validate,
    config,
    moduleStatic : {
        validate:   validateGlobal
    }
};
