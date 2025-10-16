const cpuData           = system.getScript('/ti/security/device_specific_information/cpu_data.js');
const memoryData        = system.getScript('/ti/security/device_specific_information/memory_data.js');
const ssuData           = system.getScript('/ti/security/device_specific_information/ssu_data.js');
const peripheralData    = system.getScript('/ti/security/device_specific_information/peripheral_data.js');

let flash_code_sets         = memoryData.flashMemories.flash_code_sets
let flash_data_sets         = memoryData.flashMemories.flash_data_sets
const crc32Table            = ssuData.crc32Table
const seccfgAddressMapping  = ssuData.seccfgAddressMapping

let CONTEXT_CPU1    = "CPU1";
let CONTEXT_CPU2    = "CPU2";
let CONTEXT_CPU3    = "CPU3";
let CONTEXT_SYSTEM  = "system";

const STRING_TAB    = "    ";

const coreSpecificModulesInSetupMode =
[
    "/ti/security/System_Security",
    "/ti/security/Link",
    "/ti/security/Stack",
    "/ti/security/APR",
    "/ti/security/EasyMode_link",
    "/ti/security/EasyMode_stack",
    "/ti/security/EasyMode_sharedMem",
]

//
// Generic functions
//

function isContextCPU1(inst)
{
    let csm = coreSpecificModuleCheck(inst)
    if(isAllocationSetupMode() && csm.check)
    {
        return (csm.core == CONTEXT_CPU1)
    }
    else
    {
        return (system.context == CONTEXT_CPU1 || system.context == CONTEXT_SYSTEM)
    }
}

function isContextCPU2(inst)
{
    let csm = coreSpecificModuleCheck(inst)
    if(isAllocationSetupMode() && csm.check)
    {
        return (csm.core == CONTEXT_CPU2)
    }
    else
    {
        return (system.context == CONTEXT_CPU2)
    }

}

function isContextCPU3(inst)
{
    let csm = coreSpecificModuleCheck(inst)
    if(isAllocationSetupMode() && csm.check)
    {
        return (csm.core == CONTEXT_CPU3)
    }
    else
    {
        return (system.context == CONTEXT_CPU3)
    }
}

function getAllCoreContexts()
{
    return [CONTEXT_CPU1, CONTEXT_CPU2, CONTEXT_CPU3]
}

function getActiveContexts()
{
    let contextNames = Object.keys(system.contexts)
    return contextNames;
}

function getActiveContexts_configure(raData)
{
    let allCtxs = getAllCoreContexts()
    let ret = []
    allCtxs.forEach(ctx => {
        if(raData["modules"].find(a => (a["moduleName"] == `/ti/security/${ctx}_APR`)))
            ret.push(ctx)
    })

    return ret
}

function currentContext() 
{
    let ctx = CONTEXT_CPU1
    if(isContextCPU2()) ctx = CONTEXT_CPU2
    if(isContextCPU3()) ctx = CONTEXT_CPU3
    return ctx
}

function toHex(val, digits)
{
    return val.toString(16).padStart(digits, '0').toUpperCase()
}

//
//  Cross-module and cross-context data access in SysConfig
//

function modStatic(modName, inst = null)
{
    let csm = coreSpecificModuleCheck(inst)
    if (isAllocationSetupMode() && csm.check && coreSpecificModulesInSetupMode.includes(modName)) // core specific SSU related module
    {
        let coreSpecificModName = getCoreSpecificModuleName(modName, csm.core)

        if(csm.isSS)    // system security is now instanced module here
        {
            const mod = system.modules[coreSpecificModName];
            if (!mod)
                return undefined;
            if (!mod.$instances || !mod.$instances.length)
                return undefined;
            return mod.$instances[0];
        }
        else
        {
            const mod = system.modules[coreSpecificModName];
            return mod ? mod.$static : mod;
        }
    }
    else // normal static module
    {
        const mod = system.modules[modName];
        return mod ? mod.$static : mod;
    }
}

function modStaticByCPU(modName, cpuName)
{
    if (isAllocationSetupMode() && coreSpecificModulesInSetupMode.includes(modName)) // core specific SSU related module
    {
        let coreSpecificModName = getCoreSpecificModuleName(modName, cpuName)
        if(coreSpecificModName.endsWith("_System_Security"))
        {
            const mod = system.modules[coreSpecificModName];
            if (!mod)
                return undefined;
            if (!mod.$instances || !mod.$instances.length)
                return undefined;
            return mod.$instances[0];
        }
        else
        {
            const mod = system.modules[coreSpecificModName];
            return mod ? mod.$static : mod;
        }
    }
    else
    {
        let reqdContext = isAllocationSetupMode() ? CONTEXT_SYSTEM : cpuName

        const context = system.contexts[reqdContext];
        if (!context)
            return undefined;
        const mod = context.system.modules[modName];
        return mod ? mod.$static : mod;
    }
}

function modInstances(modName, inst = null)
{
    let coreSpecificModName = modName
    let csm = coreSpecificModuleCheck(inst)
    if (isAllocationSetupMode() && csm.check && coreSpecificModulesInSetupMode.includes(modName)) // core specific SSU related module
    {
        coreSpecificModName = getCoreSpecificModuleName(modName, csm.core)
    }

    const mod = system.modules[coreSpecificModName];
    if (!mod)
        return [];
    if (!mod.$instances)
        return [];
    return mod.$instances;
}

function modInstancesByCPU(modName, cpuName)
{
    if (isAllocationSetupMode() && coreSpecificModulesInSetupMode.includes(modName)) // core specific SSU related module
    {
        let coreSpecificModName = getCoreSpecificModuleName(modName, cpuName)

        const mod = system.modules[coreSpecificModName];
        if (!mod)
            return [];
        if (!mod.$instances)
            return [];
        return mod.$instances;
    }
    else
    {
        let reqdContext = isAllocationSetupMode() ? CONTEXT_SYSTEM : cpuName
        const context = system.contexts[reqdContext];
        if (!context)
            return [];

        const modules = context.system.modules;
        if (!modules)
            return [];

        const mod = modules[modName];
        if (!mod || !mod.$instances)
            return [];

        return mod.$instances;
    }
}

function modInstanceNames(moduleName, inst)
{
    const instances = modInstances(moduleName, inst);
    if(instances.length)
        return instances.map(instance =>({name: instance.$name}));

    return [];
}

function getConfigFromStaticModule(modName, configName, cpuName)
{
    let ret =
    {
        available   : false,
        value       : "",
        module      : ""
    }

    let staticMod = modStaticByCPU(modName, cpuName)
    if(staticMod)
    {
        ret.available   = true
        ret.value       = staticMod[configName]
        ret.module      = staticMod
    }
    return ret;
}

function getCoreList(lockstepFilter = 0)
{
    let coreList = _.map(cpuData.cpuList, (cpuItem) => {return {name: cpuItem.name}})

    if(lockstepFilter != 0) // Reject CPU2 if in LockStep
    {
        let lsConfig = getConfigFromStaticModule("/driverlib/sysctl.js", "LSConfig", CONTEXT_CPU1)
        if(!lsConfig.available || (lsConfig.available && lsConfig.value == "LockStep")){
            coreList = _.reject(coreList, i => (i.name == CONTEXT_CPU2))
        }
    }

    return coreList
}

//
//  SSU and Memory Allocation functionality
//

function getExeLink(apr) 
{
    return (modInstances('/ti/security/Link').
                filter(x => x.codeAPRs.includes(apr.name) || x.codeAPRsEasy.includes(apr.name))
                [0])
}

function getAPILink(apr) 
{
    return (modInstances('/ti/security/Link').
                filter(x => x.APIAPRs.includes(apr.name) || x.APIAPRsEasy.includes(apr.name))
                [0])
}

function getLinkAccess(apr, sysSec) 
{
    const linkInstances = modInstances('/ti/security/Link')
    let access = ""
    access  +=  linkInstances.
                filter(x => getStack(x) && getStack(x).stackAPR == apr.memRegion).
                map(x=>{return "SSU_LINK_RW_ACCESS(" + x.$name + ") | "}).
                join("");
    access  +=  linkInstances.
                filter(x => x.readwriteAPRs.includes(apr.name) ||  x.readwriteAPRsEasy.includes(apr.name)).
                map(x=>{return "SSU_LINK_RW_ACCESS(" + x.$name + ") | "}).
                join("");
    access  +=  linkInstances.
                filter(x => x.readAPRs.includes(apr.name) || x.readAPRsEasy.includes(apr.name)).
                map(x=>{return "SSU_LINK_RD_ACCESS(" + x.$name + ") | "}).
                join("");

    return access + '0U'
}

function getStack(link) 
{
    return (modInstances('/ti/security/Stack').
                    filter(x => x.links.includes(link) || x.linksEasy.includes(link.$name))
                    [0])
}

function getStackv2(link, inst) // used in SETUP mode
{
    return (modInstances('/ti/security/Stack', inst).
                    filter(x => x.links.includes(link) || x.linksEasy.includes(link.$name))
                    [0])
}

function getZone(stack)
{
    return stack.zone
}

function getExeLink_configure(apr, core) 
{
    return (modInstances(`/ti/security/${core}_Link`).
                filter(x => x.codeAPRs.includes(apr.name) || x.codeAPRsEasy.includes(apr.name))
                [0])
}

function getAPILink_configure(apr, core) 
{
    return (modInstances(`/ti/security/${core}_Link`).
                filter(x => x.APIAPRs.includes(apr.name) || x.APIAPRsEasy.includes(apr.name))
                [0])
}

function getLinkAccess_configure(apr, core) 
{
    const linkInstances = modInstances(`/ti/security/${core}_Link`)
    let access = ""
    access  +=  linkInstances.
                filter(x => getStack_configure(x, core) && getStack_configure(x, core).stackAPR == apr.memRegion).
                map(x=>{return "SSU_LINK_RW_ACCESS(" + x.$name + ") | "}).
                join("");
    access  +=  linkInstances.
                filter(x => x.readwriteAPRs.includes(apr.name) ||  x.readwriteAPRsEasy.includes(apr.name)).
                map(x=>{return "SSU_LINK_RW_ACCESS(" + x.$name + ") | "}).
                join("");
    access  +=  linkInstances.
                filter(x => x.readAPRs.includes(apr.name) || x.readAPRsEasy.includes(apr.name)).
                map(x=>{return "SSU_LINK_RD_ACCESS(" + x.$name + ") | "}).
                join("");

    return access + '0U'
}

function getStack_configure(link, core) 
{
    return (modInstancesByCPU(`/ti/security/${core}_Stack`, core).
                    filter(x => x.links.includes(link) || x.linksEasy.includes(link.$name))
                    [0])
}

function getZone_configure(stack)
{
    return stack.zone
}

function isContiguous(list, sublist)
{
    var temp = []
    sublist.forEach(x=>{
        temp.push(list.indexOf(x))
    })

    temp = temp.sort((a,b) => {return a-b})
    for(var i=1; i< temp.length; i++)
    {
        if(temp[i] != (temp[i-1] + 1))
            return false
    }
    return true
}

function getAPRsInRAMAll()
{
    let ret = {}
    let existingContexts = getCoreList().map(o => {return o.name});
    existingContexts.forEach(cpu => {
        ret[cpu] = []
    })
    existingContexts.forEach(cpu => {
        let aprs = modInstancesByCPU('/ti/security/APR', cpu)
                .filter(apr =>  (apr.type != "Peripheral") && (apr.memType == "RAM"))
                .forEach(apr => {ret[cpu].push(apr)})
    })
    return ret
}


function getAPRsInFlashAllNew()
{
    let ret = {}
    let existingContexts = getCoreList().map(o => {return o.name});
    existingContexts.forEach(cpu => {
        ret[cpu] = []
    })
    existingContexts.forEach(cpu => {
        let aprs = modInstancesByCPU('/ti/security/APR', cpu)
                .filter(apr =>  (apr.type != "Peripheral") && (apr.memType == "Flash"))
                .forEach(apr => {ret[cpu].push(apr)})
    })
    return ret
}

function getPeripheralAPRsAll()
{
    let ret = {}
    let existingContexts = getCoreList().map(o => {return o.name});
    existingContexts.forEach(cpu => {
        ret[cpu] = []
    })
    existingContexts.forEach(cpu => {
        let aprs = modInstancesByCPU('/ti/security/APR', cpu)
                .filter(apr =>  (apr.type == "Peripheral"))
                .forEach(apr => {ret[cpu].push({
                    name: apr.$name,
                    memRegion: apr,
                    startAddr: apr.startAddr,
                    endAddr:  (apr.endAddr>0) ? (apr.endAddr + 1) : 0,
                    peripheralList: apr.peripherals,
                    permList: [],
                    autoPeriphRegion: false,
                    type: "Peripheral",
                    memType: null
                })})
    })
    return ret
}

function updateFlashUsageProtection(flMem, weprotVal, flx)
{
    let weprotUpdateList = new Set()
    flMem.forEach(flUnit => {
        getWeprotRange(flUnit).forEach(item => weprotUpdateList.add(item))
    })

    flx.forEach(unit => {
        if(flMem.includes(unit.name))
            unit.used = 1;
        if(weprotUpdateList.has(unit.name)){
            unit.weprot = weprotVal
        }
    })
}

function getWeprotRange(flUnit)
{
    let ret = []
    let arr = flUnit.split("_");
    let idx = Number(arr[2])
    if(!arr[0].includes("DATA") && (idx < 32)){
        ret.push(flUnit)
    }
    else{
        let m = Math.floor(idx/8)
        for(let i=0; i<8; i++){
            let j = 8*m + i
            ret.push(arr[0] + "_" + arr[1] + "_" + j.toString())
        }
    }
    return ret;
}

function memName(mem)
{
    return mem.name.toUpperCase();
}

function caps(a)
{
    return a.toUpperCase();
}

function sectName(mem)
{
    return '.'+ mem.$name.replace(/_/g,'.');
}


function getList(x)
{
    return x.split(",").
            map(a=>{return a.trim()}).
            filter(a=>a !="")
}


function getSECGROUPNew(apr, indent)
{
    let ctx = currentContext()
    let secGroup = " "
    if(apr.type != "Code")
        return secGroup

    let exeLink = getExeLink(apr)
    if(exeLink)
    {
        let stack           = getStack(exeLink)
        let secGroupName    = stack ? stack.$name : `${ctx}_STACK2_STACK`
        let secGroupAttr    = stack ? stack.secGroupAttr : "NONE"

        if(exeLink.easyModeGenerated && exeLink.$ownedBy.isCommonCode)
        {
            secGroupName    += "_COMMONCODE"
            secGroupAttr    = exeLink.$ownedBy.secGroupAttr
        }

        let readsList   = _.union(exeLink.readAPRsEasy, exeLink.readAPRs).map(a => caps(a))
        let writesList  = _.union(exeLink.readwriteAPRsEasy, exeLink.readwriteAPRs).map(a => caps(a))

        if(secGroupAttr == "NONE")
            secGroup = "\n" + ' '.repeat(indent + 4) + "   SECURE_GROUP(" + secGroupName + ",\n"
        else
            secGroup = "\n" + ' '.repeat(indent + 4) + "   SECURE_GROUP(" + secGroupName + ", " + secGroupAttr + ",\n"

        secGroup += ' '.repeat(indent + 7) + "READS=(" + readsList.join((",\n"+' '.repeat(indent + 7)))
        secGroup += "),\n" + ' '.repeat(indent + 7) + "WRITES=(" + writesList.join((",\n"+' '.repeat(indent + 7))) + "))"
    }

    return secGroup
}


function getSECGROUPNew_configure(apr, indent, core)
{
    let secGroup = " "
    if(apr.type != "Code")
        return secGroup

    let exeLink = getExeLink_configure(apr, core)
    if(exeLink)
    {
        let stack           = getStack_configure(exeLink, core)
        let secGroupName    = stack ? stack.$name : `${core}_STACK2_STACK`
        let secGroupAttr    = stack ? stack.secGroupAttr : "NONE"

        if(exeLink.easyModeGenerated && exeLink.$ownedBy.isCommonCode)
        {
            secGroupName    += "_COMMONCODE"
            secGroupAttr    = exeLink.$ownedBy.secGroupAttr
        }

        let readsList   = _.union(exeLink.readAPRsEasy, exeLink.readAPRs).map(a => caps(a))
        let writesList  = _.union(exeLink.readwriteAPRsEasy, exeLink.readwriteAPRs).map(a => caps(a))

        if(secGroupAttr == "NONE")
            secGroup = "\n" + ' '.repeat(indent + 4) + "   SECURE_GROUP(" + secGroupName + ",\n"
        else
            secGroup = "\n" + ' '.repeat(indent + 4) + "   SECURE_GROUP(" + secGroupName + ", " + secGroupAttr + ",\n"

        secGroup += ' '.repeat(indent + 7) + "READS=(" + readsList.join((",\n"+' '.repeat(indent + 7)))
        secGroup += "),\n" + ' '.repeat(indent + 7) + "WRITES=(" + writesList.join((",\n"+' '.repeat(indent + 7))) + "))"
    }

    return secGroup
}

function inputSectionFormat(userSection)
{
    var sectName = userSection["sectionName"]
    var libName  = userSection["libraryName"]
    var objName  = userSection["objectName"]
    var sectionDetails = ""

    if(sectName.length != 0)
        sectionDetails = "*(" + sectName + ")"
    if((libName.length != 0) &&  (objName.length != 0))
        sectionDetails = libName + "<" + objName + ">" + sectionDetails.replace("*", "")
    if((libName.length != 0) &&  (objName.length == 0))
        sectionDetails = libName + "<*>" + sectionDetails.replace("*", "")
    if((libName.length == 0) &&  (objName.length != 0))
        sectionDetails = objName + sectionDetails.replace("*", "")

    return sectionDetails
}

function symbolsFormat(section){
    let ret = ""
    let sps = "          "

    if(section.sectionRunFromDifferentAddr && section.sectionRun != "None"){
        ret += sps + "LOAD = " + (section.sectionMemory) + "\n"
        ret += sps + "RUN = " +  (section.sectionRun) + "\n"
        ret += sps + "TABLE(" +  ((section.sectionBinit) ? "BINIT" : "copyTable") + ")\n"
    }
    if(section.sectionAlignEnable){
        ret += sps + "PALIGN(" +  (section.sectionAlign).toString() + ")\n"
    }
    if(section.sectionFillEnable){
        ret += sps + "FILL(" +  (section.sectionFill).toString() + ")\n"
    }
    section.sectionSymbols.forEach(sym => {
        ret += sps + sym + "(" +  _.camelCase((section.$name) + "_" + sym) + ")\n"
    })
    if(section.sectionType != "None"){
        ret += sps + "TYPE(" +  (section.sectionType).toString() + ")\n"
    }
    return ret
}

function where(apr)
{
    let ctx = currentContext()
    if(apr.memType == "LoadRun")                                                    //!! do tag check instead or add extra attribute for this
        return "LOAD=APR_FLASHLOAD, RUN="  + memName(apr) + ", TABLE(copyTable)"
    else if (apr.name == `${ctx}_LINK2_codeAPR_RAM`)
    {
        let loadAPR = "APR_FLASHLOAD_" + ctx
        let bankmode = getBankModeConfig();
        if(isContextCPU1() || (isContextCPU3() && bankmode > 1))
            loadAPR = `${ctx}_LINK2_CODEAPR_FLASH`
        return `LOAD = ${loadAPR}, RUN=${ctx}_LINK2_CODEAPR_RAM, table(BINIT)`
    }
    else if (apr.name == `${ctx}_CommonCodeModule_codeAPR_RAM`)
    {
        let loadAPR = "APR_FLASHLOAD_" + ctx
        let bankmode = getBankModeConfig();
        if(isContextCPU1() || (isContextCPU3() && bankmode > 1))
            loadAPR = `${ctx}_COMMONCODEMODULE_CODEAPR_FLASH`
        return `LOAD = ${loadAPR}, RUN=${ctx}_COMMONCODEMODULE_CODEAPR_RAM, table(BINIT)`
    }
    else
        return "> " + memName(apr)
}

function wherev2(apr, knownContext)
{
    let ctx = knownContext
    if(apr.memType == "LoadRun")                                                    //!! do tag check instead or add extra attribute for this
        return "LOAD=APR_FLASHLOAD, RUN="  + memName(apr) + ", TABLE(copyTable)"
    else if (apr.name == `${ctx}_LINK2_codeAPR_RAM`)
    {
        let loadAPR = "APR_FLASHLOAD_" + ctx
        let bankmode = getBankModeConfig();
        if(isContextCPU1() || (isContextCPU3() && bankmode > 1))
            loadAPR = `${ctx}_LINK2_CODEAPR_FLASH`
        return `LOAD = ${loadAPR}, RUN=${ctx}_LINK2_CODEAPR_RAM, table(BINIT)`
    }
    else if (apr.name == `${ctx}_CommonCodeModule_codeAPR_RAM`)
    {
        let loadAPR = "APR_FLASHLOAD_" + ctx
        let bankmode = getBankModeConfig();
        if(isContextCPU1() || (isContextCPU3() && bankmode > 1))
            loadAPR = `${ctx}_COMMONCODEMODULE_CODEAPR_FLASH`
        return `LOAD = ${loadAPR}, RUN=${ctx}_COMMONCODEMODULE_CODEAPR_RAM, table(BINIT)`
    }
    else
        return "> " + memName(apr)
}

function sectionListManual(section, aprList, sysSecPresent = true)
{
    var secGroup = " : "
    var inputSections = ""
    var ret = ""

    var apr = aprList.filter(a => a.name == section.sectionMemory)[0]
    if(section.sectionRunFromDifferentAddr && section.sectionRun != "None")
        apr = aprList.filter(a => a.name == section.sectionRun)[0]

    if(!apr)
        return ret

    ret = "    " + section.$name + secGroup + " {\n"

    if(section.addInputSections){
        inputSections = ""
        for(let i=0; i<section.inputSection.length; i++){
            let x = section.inputSection[i]
            inputSections += "        " + inputSectionFormat(x) + "\n"
        }
        ret += inputSections
    }

    if(!section.sectionRunFromDifferentAddr)
        ret += "    }     " + where(apr) + "\n"
    else
        ret += "    }"

    ret += symbolsFormat(section)

    ret += "\n"

    return ret
}


function sectionListManual_configure(section, aprList, sysSecPresent = true, cpu)
{
    var secGroup = " : "
    var inputSections = ""
    var ret = ""

    var apr = aprList.filter(a => a.name == section.sectionMemory)[0]
    if(section.sectionRunFromDifferentAddr && section.sectionRun != "None")
        apr = aprList.filter(a => a.name == section.sectionRun)[0]

    if(!apr)
        return ret

    ret = "    " + section.$name + secGroup + " {\n"

    if(section.addInputSections){
        inputSections = ""
        for(let i=0; i<section.inputSection.length; i++){
            let x = section.inputSection[i]
            inputSections += "        " + inputSectionFormat(x) + "\n"
        }
        ret += inputSections
    }

    if(!section.sectionRunFromDifferentAddr)
        ret += "    }     " + wherev2(apr, cpu) + "\n"
    else
        ret += "    }"

    ret += symbolsFormat(section)

    ret += "\n"

    return ret
}

function isSectionIncluded(str)
{
    let regexp = /.*(\<).+(\>)/;
    if (regexp.test(str)) return true;
    else return false;
}

function textSectionList(x, fileList, libList, customListCodeFlash)
{
    var inputSections = ""

    if(x.isLink2) {
        getList(x.link2CodeSection).forEach(f => {
            f = f.endsWith(")") ? f : "*(" + f + ")"
            inputSections += "        " + f + "\n"
        })
        getList(x.link2DefaultAllSections).forEach(f => {
            inputSections += "        " + f + "(.text)\n"
        })
    }
    fileList.forEach(f => {
        inputSections += "        " + f + ".o(.text)\n"
    })
    libList.forEach(f => {
        let specifier = isSectionIncluded(f) ? "" : "<*>"
        inputSections += "        " + f + specifier +"(.text)\n"
    })
    customListCodeFlash.forEach(f => {
        inputSections += "        " + f + "\n"
    })

    return inputSections
}

function ramFunctionSectionList(x, fileList, libList, customListCodeRAM)
{
    var inputSections = ""

    if(x.isLink2){
        inputSections += "        " + "*(.TI.ramfunc.link2)\n"
        getList(x.link2DefaultAllSections).forEach(f => {
            inputSections += "        " + f + "(.TI.ramfunc)\n"
        })
    }
    fileList.forEach( f => {
        inputSections += "        " + f + ".o(.TI.ramfunc)\n"
    })
    libList.forEach( f => {
        let specifier = isSectionIncluded(f) ? "" : "<*>"
        inputSections += "        " + f + specifier +"(.TI.ramfunc)\n"
    })
    customListCodeRAM.forEach( f => {
        inputSections += "        " + f + "\n"
    })

    return inputSections
}

function sectionListModule(easyModeModule, APRList, cpu, sysSec, configure = false)
{
    var sections = ""
    var x = easyModeModule

    var fileList            = getList(x.fileNames)
    var libList             = getList(x.libs)
    var customListCodeFlash = x.useCustomSections ? getList(x.customCodeSectionFlash) : []
    var customListCodeRAM   = x.useCustomSections ? getList(x.customCodeSectionRAM)   : []
    var customListRWSection = x.useCustomSections ? getList(x.customRWSection) : []
    var customListROSection = x.useCustomSections ? getList(x.customROSection) : []

    customListCodeFlash = customListCodeFlash.map(a => {return a.endsWith(")") ? a : "*(" + a + ")"})
    customListCodeRAM   = customListCodeRAM.map  (a => {return a.endsWith(")") ? a : "*(" + a + ")"})
    customListRWSection = customListRWSection.map(a => {return a.endsWith(")") ? a : "*(" + a + ")"})
    customListROSection = customListROSection.map(a => {return a.endsWith(")") ? a : "*(" + a + ")"})

    //Case        codeAPR_Flash   codeAPR_RAM     flashLoadSize   Action
    //-------     -------------   -------------   -----------     ------
    //
    //1           0               1               0               .text       => RAM
    //                                                            .TI.ramfunc => RAM
    //
    //2           0               1               1               .text       => RAM
    //                                                            .TI.ramfunc => LOAD=FLASHL RUN=RAM
    //
    //3           1               0               X               .text       => FLASH
    //
    //4           1               1               0               .text       => FLASH
    //                                                            .TI.ramfunc => LOAD=FLASH RUN=RAM
    //
    //5           1               1               1               .text       => FLASH
    //                                                            .TI.ramfunc => LOAD=FLASHL RUN=RAM

    if(x.codeAPR_Flash)
    {
        if(x.codeAPR_RAM)
        {
            if(sysSec.APR_FlashLoad)
            {
                //  CASE 5
                //      .text       => FLASH
                //      .TI.ramfunc => LOAD=FLASHL RUN=RAM

                var inputSections = textSectionList(x, fileList, libList, customListCodeFlash)
                if(inputSections != "")
                {
                    let reqdApr = APRList.find(o => {return o.name == x.codeAPR_Flash.$name})
                    sections += "    ." + x.codeAPR_Flash.$name + " : {\n"
                    sections += inputSections
                    sections += "    }   > " + memName(reqdApr) + ", palign(8)  \n\n"
                }

                var inputSections = ramFunctionSectionList(x, fileList, libList, customListCodeRAM)
                if(inputSections != "") {
                    let reqdApr = APRList.find(o => {return o.name == x.codeAPR_RAM.$name})
                    sections += "    ." + x.codeAPR_RAM.$name + " : {\n"
                    sections += inputSections
                    sections += "    }   LOAD = APR_FLASHLOAD_" + cpu.toUpperCase() + ", RUN = " + memName(reqdApr) + ", table(BINIT)\n\n"
                }
            }
            else
            {
                //  CASE 4
                //      .text       => FLASH
                //      .TI.ramfunc => LOAD=FLASH RUN=RAM

                var inputSections = textSectionList(x, fileList, libList, customListCodeFlash)
                if(inputSections != "")
                {
                    let reqdApr = APRList.find(o => {return o.name == x.codeAPR_Flash.$name})
                    sections += "    ." + x.codeAPR_Flash.$name + " : {\n"
                    sections += inputSections
                    sections += "    }   > " + memName(reqdApr) + ", palign(8)  \n\n"
                }

                var inputSections = ramFunctionSectionList(x, fileList, libList, customListCodeRAM)
                if(inputSections != "") {
                    let reqdApr = APRList.find(o => {return o.name == x.codeAPR_RAM.$name})
                    let reqdAprf = APRList.find(o => {return o.name == x.codeAPR_Flash.$name})
                    sections += "    ." + x.codeAPR_RAM.$name + " : {\n"
                    sections += inputSections
                    sections += "    }   LOAD = " + memName(reqdAprf) + ", RUN = " + memName(reqdApr) + ", table(BINIT)\n\n"
                }
            }
        }
        else
        {
            //  CASE 3
            //      .text       => FLASH

            var inputSections = textSectionList(x, fileList, libList, customListCodeFlash)
            if(inputSections != "")
            {
                let reqdApr = APRList.find(o => {return o.name == x.codeAPR_Flash.$name})
                sections += "    ." + x.codeAPR_Flash.$name + " : {\n"
                sections += inputSections
                sections += "    }   > " + memName(reqdApr) + ", palign(8)  \n\n"
            }
        }
    }
    else
    {
        if(x.codeAPR_RAM)
        {
            if(sysSec.APR_FlashLoad)
            {
                //  CASE 2
                //      .text       => RAM
                //      .TI.ramfunc => LOAD=FLASHL RUN=RAM

                var inputSections = textSectionList(x, fileList, libList, customListCodeFlash)
                if(inputSections != "")
                {
                    let reqdApr = APRList.find(o => {return o.name == x.codeAPR_RAM.$name})
                    sections += "    ." + x.codeAPR_RAM.$name + " : {\n"
                    sections += inputSections
                    sections += "    }   > " + memName(reqdApr) + ", palign(8)  \n\n"
                }
                //
                //  .TI.ramfunc => LOAD=Flash RUN=RAM
                //
                var inputSections = ramFunctionSectionList(x, fileList, libList, customListCodeRAM)
                if(inputSections != "") {
                    let reqdApr = APRList.find(o => {return o.name == x.codeAPR_RAM.$name})
                    sections += "    ." + x.codeAPR_RAM.$name + " : {\n"
                    sections += inputSections
                    sections += "    }   LOAD = APR_FLASHLOAD_" + cpu.toUpperCase() + ", RUN = " + memName(reqdApr) + ", table(BINIT)\n\n"
                }
            }
            else
            {
                //  CASE 1
                //      .text       => RAM
                //      .TI.ramfunc => RAM

                var inputSections = ""

                if(x.isLink2) {
                    inputSections += "        " + "*(.TI.ramfunc.link2)\n"
                    getList(x.link2CodeSection).forEach(f => {
                        f = f.endsWith(")") ? f : "*(" + f + ")"
                        inputSections += "        " + f + "\n"
                    })
                    getList(x.link2DefaultAllSections).forEach(f => {
                        inputSections += "        " + f + "(.text .TI.ramfunc)\n"
                    })
                }
                fileList.forEach(f => {
                    inputSections += "        " + f + ".o(.text .TI.ramfunc)\n"
                })
                libList.forEach(f => {
                    let specifier = isSectionIncluded(f) ? "" : "<*>"
                    inputSections += "        " + f + specifier +"(.text .TI.ramfunc)\n"
                })
                customListCodeFlash.forEach(f => {
                    inputSections += "        " + f + "\n"
                })

                if(inputSections != "")
                {
                    let reqdApr = APRList.find(o => {return o.name == x.codeAPR_RAM.$name})
                    sections += "    ." + x.codeAPR_RAM.$name + " : {\n"
                    sections += inputSections
                    sections += "    }   > " + memName(reqdApr) + "\n\n"
                }
            }
        }
    }

    if(x.dataAPR_RW)
    {
        var inputSections = ""

        if(x.isLink2){
            getList(x.link2DefaultAllSections).forEach(f => {
                inputSections += "        " + f + "(.bss .data)\n"
            })
        }

        fileList.forEach( f => {
            inputSections += "        " + f + ".o(.bss .data)\n"
        })
        libList.forEach( f => {
            let specifier = isSectionIncluded(f) ? "" : "<*>"
            inputSections += "        " + f + specifier +"(.bss .data)\n"
        })
        customListRWSection.forEach( f => {
            inputSections += "        " + f + "\n"
        })

        if(inputSections != "") {
            let reqdApr = APRList.find(o => {return o.name == x.dataAPR_RW.$name})
            sections += "    ." + x.dataAPR_RW.$name + " : {\n"
            sections += inputSections
            sections += "    }     " + (configure ? where(reqdApr) : wherev2(reqdApr, cpu)) + "\n\n"
        }
    }

    if(x.dataAPR_RO && (!x.roInRAM || !x.combine_ro_rw))
    {
        var inputSections = ""

        if(x.isLink2){
            getList(x.link2DefaultAllSections).forEach(f => {
                inputSections += "        " + f + "(.rodata .const)\n"
            })
        }

        fileList.forEach( f => {
            inputSections += "        " + f + ".o(.rodata .const)\n"
        })
        libList.forEach( f => {
            let specifier = isSectionIncluded(f) ? "" : "<*>"
            inputSections += "        " + f + specifier +"(.rodata .const)\n"
        })
        customListROSection.forEach( f => {
            inputSections += "        " + f + "\n"
        })

        if(inputSections != "") {
            let reqdApr = APRList.find(o => {return o.name == x.dataAPR_RO.$name})
            sections += "    ." + x.dataAPR_RO.$name + " : {\n"
            sections += inputSections
            sections += "    }     " + (configure ? where(reqdApr) : wherev2(reqdApr, cpu)) + ", palign(8) \n\n"
        }
    }

    if(x.dataAPR)
    {
        var inputSections = ""

        fileList.forEach( f => {
            inputSections += "        " + f + ".o(.bss .data)\n"
        })
        libList.forEach( f => {
            let specifier = isSectionIncluded(f) ? "" : "<*>"
            inputSections += "        " + f + specifier +"(.bss .data)\n"
        })
        customListRWSection.forEach( f => {
            inputSections += "        " + f + "\n"
        })

        if(inputSections != "") {
            let reqdApr = APRList.find(o => {return o.name == x.dataAPR.$name})
            sections += "    ." + x.dataAPR.$name + "_S1 : {\n"
            sections += inputSections
            sections += "    }     " + (configure ? where(reqdApr) : wherev2(reqdApr, cpu)) + "\n\n"
        }


        inputSections = ""

        fileList.forEach( f => {
            inputSections += "        " + f + ".o(.rodata .const)\n"
        })
        libList.forEach( f => {
            let specifier = isSectionIncluded(f) ? "" : "<*>"
            inputSections += "        " + f + specifier +"(.rodata .const)\n"
        })
        customListROSection.forEach( f => {
            inputSections += "        " + f + "\n"
        })

        if(inputSections != "") {
            let reqdApr = APRList.find(o => {return o.name == x.dataAPR.$name})
            sections += "    ." + x.dataAPR.$name + "_S2 : {\n"
            sections += inputSections
            sections += "    }     LOAD=APR_FLASHLOAD_" + cpu.toUpperCase() + ", RUN=" +  memName(reqdApr) + ", palign(8),  TABLE(copyTable)\n\n" //!! upd
        }
    }
    return sections
}

function sectionListSharedMem(sharedMem, APRList, cpu, configure = false)
{
    var sections = ""
    var x = sharedMem

    var dataFiles           = (x.type == "RAM") ? getList(x.dataFiles) : []
    var constFiles          = getList(x.constFiles)
    var customListRWSection = (x.useCustomSections && (x.type == "RAM")) ? getList(x.customDataSections) : []
    var customListROSection = x.useCustomSections ? getList(x.customConstSections) : []
    var apr                 = x.isStackMem ? APRList.find(o => {return o.name == x.$ownedBy.stack.stackAPR.$name})
                                            : APRList.find(o => {return o.name == x.APR.$name})

    customListRWSection = customListRWSection.map(a => {return a.endsWith(")") ? a : "*(" + a + ")"})
    customListROSection = customListROSection.map(a => {return a.endsWith(")") ? a : "*(" + a + ")"})

    // data sections
    var inputSections = ""
    dataFiles.forEach( f => {
        inputSections += "        " + f + ".o(.bss .data)\n"
    })
    customListRWSection.forEach( f => {
        inputSections += "        " + f + "\n"
    })

    if(inputSections != "") {
        sections += "    ." + apr.name + " : {\n"
        sections += inputSections
        sections += "    }     " + (configure ? where(apr) : wherev2(apr, cpu)) + "\n\n"
    }

    // ro sections
    var inputSections = ""
    constFiles.forEach( f => {
        inputSections += "        " + f + ".o(.rodata .const)\n"
    })
    customListROSection.forEach( f => {
        inputSections += "        " + f + "\n"
    })
    if(inputSections != "") {
        sections += "    ." + apr.name + "_1 : {\n"
        sections += inputSections
        if(x.type == "Flash")
            sections += "    }     " + (configure ? where(apr) : wherev2(apr, cpu)) + ", palign(8) \n\n"
        else
            sections += "    }     LOAD=APR_FLASHLOAD_" + cpu.toUpperCase() + ", RUN=" +  memName(apr) + ", palign(8), TABLE(copyTable)\n\n" //!! update
    }


    return sections
}

function getSectionsList(sysSec, cpu)
{
    if(!sysSec || sysSec == undefined) return getSectionsMinimal(cpu)
    //else if(sysSec.ssumode == 1) return getSectionsMinimal(cpu)

    var sections = ""
    let APRsAll = allocateAllMemoryRegions()
    let APRList = APRsAll[cpu].filter(apr=> apr.type != "Peripheral")

    if(isContextCPU1()){
        let reqdAPR = APRList.find(o => {return o.name == `${cpu}_LINK2_codeAPR_Flash`}) //!! tag
        if(reqdAPR)
            sections += `    codestart : > 0x${reqdAPR.startAddr.toString(16)}, palign(8)  \n`

        let certSection = `    cert      : {} > CERT, palign(8) \n`
        sections += certSection
    }
    else{
        let section_resetvector = ""
        let section_nmivector = ""
        let section_codestart = ""

        if(isContextCPU3()){
            let certSection = `    cert      : {} > CERT, palign(8) \n`
            sections += certSection
        }

        let reqdAPR = APRList.find(o => {return o.name == `${cpu}_LINK2_codeAPR_Flash`}) //!! tag
        if(reqdAPR){
            section_resetvector = `    resetvector  : > 0x${reqdAPR.startAddr.toString(16)}, palign(8)  \n`
            section_nmivector   = `    nmivector    : > 0x${(reqdAPR.startAddr + 0x40).toString(16)}, palign(8)  \n`
            section_codestart   = `    codestart    : > ${reqdAPR.name.toUpperCase()}, palign(8)  \n`
        }
        else{
            reqdAPR = APRList.find(o => {return o.name == `${cpu}_LINK2_codeAPR_RAM`}) //!! tag
            if(reqdAPR){
                section_resetvector = `    resetvector  : > 0x${reqdAPR.startAddr.toString(16)}, palign(8)  \n`
                section_nmivector   = `    nmivector    : > 0x${(reqdAPR.startAddr + 0x40).toString(16)}, palign(8)  \n`
                section_codestart   = `    codestart    : > ${reqdAPR.name.toUpperCase()}, palign(8)  \n`
            }
        }

        let resetVectorAddr = getConfigFromStaticModule("/ti/security/APR", "resetVectorAddress", system.context)
        let nmiVectorAddr = getConfigFromStaticModule("/ti/security/APR", "nmiVectorAddress", system.context)

        if(resetVectorAddr.available && resetVectorAddr.value > 0x0){
            section_resetvector = `    resetvector   : > 0x${resetVectorAddr.value.toString(16)}, palign(8)  \n`
        }
        if(nmiVectorAddr.available && nmiVectorAddr.value > 0x0){
            section_nmivector   = `    nmivector    : > 0x${nmiVectorAddr.value.toString(16)}, palign(8)  \n`
        }

        sections += section_resetvector
        sections += section_nmivector
        sections += section_codestart
    }

    if(sysSec.APR_FlashLoad) {
        let reqdAPR = APRsAll[CONTEXT_CPU1].find(o => {return o.name == ("APR_FlashLoad_"+system.context)}) //!! tag
/*
        if(!isContextCPU1()){
            sections += `    .ovly       : > 0x${reqdAPR.startAddr.toString(16)}, palign(8)  \n`
        }
        sections += `    .cinit      : > APR_FLASHLOAD_${system.context}, palign(8)  // Tables for explicitly initialized global and static variables.\n`
        //?? bankmode
        if(isContextCPU1()){
            sections += `    .binit    : > APR_FLASHLOAD_${system.context}, palign(8)  // Boot time copy tables\n`
            sections += `    .ovly      : > APR_FLASHLOAD_${system.context}, palign(8)  // Copy tables other than boot time (.binit) copy tables.\n\n`
        }
 */
        reqdAPR = APRList.find(o => {return o.name == "APR_FlashLoad_"+system.context}) //!! tag
        if(reqdAPR){
            sections += `    .cinit       : > APR_FLASHLOAD_${system.context}, palign(8)  // Tables for explicitly initialized global and static variables.\n`
            sections += `    .binit       : > APR_FLASHLOAD_${system.context}, palign(8)  // Boot time copy tables\n`
            sections += `    .ovly        : > APR_FLASHLOAD_${system.context}, palign(8)  // Copy tables other than boot time (.binit) copy tables.\n`
        }
        reqdAPR = APRList.find(o => {return o.name == `${cpu}_LINK2_dataAPR_RW`}) //!! tag
        if(reqdAPR){
            sections += `    .sysmem      : > ${cpu}_LINK2_DATAAPR_RW,   palign(8)  // Sysmem\n\n`
        }
    }
    else {
        let reqdAPR = APRList.find(o => {return o.name == `${cpu}_LINK2_codeAPR_RAM`}) //!! tag
        if(reqdAPR){
            sections += `    .cinit       : > ${cpu}_LINK2_CODEAPR_RAM, palign(8)  // Tables for explicitly initialized global and static variables.\n`
            sections += `    .binit       : > ${cpu}_LINK2_CODEAPR_RAM, palign(8)  // Boot time copy tables\n`
            sections += `    .ovly        : > ${cpu}_LINK2_CODEAPR_RAM, palign(8)  // Copy tables other than boot time (.binit) copy tables.\n`
        }
        reqdAPR = APRList.find(o => {return o.name == `${cpu}_LINK2_dataAPR_RW`}) //!! tag
        if(reqdAPR){
            sections += `    .sysmem      : > ${cpu}_LINK2_DATAAPR_RW,  palign(8)  // Sysmem\n\n`
        }
    }

    // Get the stack sections
    modInstances('/ti/security/Stack').forEach(stack => { 
        var sectName = ".stack_" + stack.$name + ' '.repeat(Math.max(0,15 - stack.$name.length))
        var stackSize = stack.size
        if(stack.$name == `${cpu}_STACK2_STACK`) {
            let stack2Apr = APRList.find(o => {return o.name == `${cpu}_STACK2_stackmem_apr`}) //!! tag
            sections += "    .stack    : " + where(stack2Apr) + "\n"
        }
        else {
            let stackNApr = APRList.find(o => {return o.name == stack.stackAPR.$name})
            sections += "    " + sectName + " : { .+= " + stackSize + "; }  " + where(stackNApr) + ",\n"
            sections += ' '.repeat(45) + "TYPE(NOINIT),\n"
            sections += ' '.repeat(45) + "START(" + stack.$name + "_start),\n"
            sections += ' '.repeat(45) + "END(" + stack.$name + "_end)\n"
        }
    })

    sections += "\n\n"

    // Get sections corresponding to Easy Mode Link
    let commonCodeSections = ""
    modInstances('/ti/security/EasyMode_link').forEach(x => { 
        if(x.isCommonCode)
            commonCodeSections += sectionListModule(x, APRList, cpu, sysSec)
        else
            sections += sectionListModule(x, APRList, cpu, sysSec)
    })
    sections += commonCodeSections                                  //!! Always placing common code sections at the end

    // Get sections corresponding to Easy Mode SharedMem
    modInstances('/ti/security/EasyMode_sharedMem').forEach(x => { 
        sections += sectionListSharedMem(x, APRList, cpu)
    })

    // Get sections for manually created Sections
    modInstances('/ti/security/OutputSection').forEach(section => { 
        sections += sectionListManual(section, APRList)
    })

    return sections
}

function getSectionsList_configure(sysSec, cpu, inst)
{
    if(!sysSec || sysSec == undefined) return getSectionsMinimal_configure(cpu)
    //else if(sysSec.ssumode == 1) return getSectionsMinimal(cpu)

    var sections = ""
    let APRsAll = allocateAllMemoryRegions()
    let APRList = APRsAll[cpu].filter(apr=> apr.type != "Peripheral")

    if(isContextCPU1(inst)){
        let reqdAPR = APRList.find(o => {return o.name == `${cpu}_LINK2_codeAPR_Flash`}) //!! tag
        if(reqdAPR)
            sections += `    codestart : > 0x${reqdAPR.startAddr.toString(16)}, palign(8)  \n`

        let certSection = `    cert      : {} > CERT, palign(8) \n`
        sections += certSection
    }
    else{
        let section_resetvector = ""
        let section_nmivector = ""
        let section_codestart = ""

        if(isContextCPU3(inst)){
            let certSection = `    cert      : {} > CERT, palign(8) \n`
            sections += certSection
        }

        let reqdAPR = APRList.find(o => {return o.name == `${cpu}_LINK2_codeAPR_Flash`}) //!! tag
        if(reqdAPR){
            section_resetvector = `    resetvector  : > 0x${reqdAPR.startAddr.toString(16)}, palign(8)  \n`
            section_nmivector   = `    nmivector    : > 0x${(reqdAPR.startAddr + 0x40).toString(16)}, palign(8)  \n`
            section_codestart   = `    codestart    : > ${reqdAPR.name.toUpperCase()}, palign(8)  \n`
        }
        else{
            reqdAPR = APRList.find(o => {return o.name == `${cpu}_LINK2_codeAPR_RAM`}) //!! tag
            if(reqdAPR){
                section_resetvector = `    resetvector  : > 0x${reqdAPR.startAddr.toString(16)}, palign(8)  \n`
                section_nmivector   = `    nmivector    : > 0x${(reqdAPR.startAddr + 0x40).toString(16)}, palign(8)  \n`
                section_codestart   = `    codestart    : > ${reqdAPR.name.toUpperCase()}, palign(8)  \n`
            }
        }

        let resetVectorAddr = getConfigFromStaticModule("/ti/security/APR", "resetVectorAddress", cpu)
        let nmiVectorAddr = getConfigFromStaticModule("/ti/security/APR", "nmiVectorAddress", cpu)

        if(resetVectorAddr.available && resetVectorAddr.value > 0x0){
            section_resetvector = `    resetvector   : > 0x${resetVectorAddr.value.toString(16)}, palign(8)  \n`
        }
        if(nmiVectorAddr.available && nmiVectorAddr.value > 0x0){
            section_nmivector   = `    nmivector    : > 0x${nmiVectorAddr.value.toString(16)}, palign(8)  \n`
        }

        sections += section_resetvector
        sections += section_nmivector
        sections += section_codestart
    }

    if(sysSec.APR_FlashLoad) {
        let reqdAPR = APRsAll[CONTEXT_CPU1].find(o => {return o.name == ("APR_FlashLoad_"+cpu)}) //!! tag

        reqdAPR = APRList.find(o => {return o.name == "APR_FlashLoad_"+cpu}) //!! tag
        if(reqdAPR){
            sections += `    .cinit       : > APR_FLASHLOAD_${cpu}, palign(8)  // Tables for explicitly initialized global and static variables.\n`
            sections += `    .binit       : > APR_FLASHLOAD_${cpu}, palign(8)  // Boot time copy tables\n`
            sections += `    .ovly        : > APR_FLASHLOAD_${cpu}, palign(8)  // Copy tables other than boot time (.binit) copy tables.\n`
        }
        reqdAPR = APRList.find(o => {return o.name == `${cpu}_LINK2_dataAPR_RW`}) //!! tag
        if(reqdAPR){
            sections += `    .sysmem      : > ${cpu}_LINK2_DATAAPR_RW,   palign(8)  // Sysmem\n\n`
        }
    }
    else {
        let reqdAPR = APRList.find(o => {return o.name == `${cpu}_LINK2_codeAPR_RAM`}) //!! tag
        if(reqdAPR){
            sections += `    .cinit       : > ${cpu}_LINK2_CODEAPR_RAM, palign(8)  // Tables for explicitly initialized global and static variables.\n`
            sections += `    .binit       : > ${cpu}_LINK2_CODEAPR_RAM, palign(8)  // Boot time copy tables\n`
            sections += `    .ovly        : > ${cpu}_LINK2_CODEAPR_RAM, palign(8)  // Copy tables other than boot time (.binit) copy tables.\n`
        }
        reqdAPR = APRList.find(o => {return o.name == `${cpu}_LINK2_dataAPR_RW`}) //!! tag
        if(reqdAPR){
            sections += `    .sysmem      : > ${cpu}_LINK2_DATAAPR_RW,  palign(8)  // Sysmem\n\n`
        }
    }

    // Get the stack sections
    modInstances('/ti/security/Stack', inst).forEach(stack => { 
        var sectName = ".stack_" + stack.$name + ' '.repeat(Math.max(0,15 - stack.$name.length))
        var stackSize = stack.size
        if(stack.$name == `${cpu}_STACK2_STACK`) {
            let stack2Apr = APRList.find(o => {return o.name == `${cpu}_STACK2_stackmem_apr`}) //!! tag
            sections += "    .stack    : " + wherev2(stack2Apr, cpu) + "\n"
        }
        else {
            let stackNApr = APRList.find(o => {return o.name == stack.stackAPR.$name})
            sections += "    " + sectName + " : { .+= " + stackSize + "; }  " + wherev2(stackNApr, cpu) + ",\n"
            sections += ' '.repeat(45) + "TYPE(NOINIT),\n"
            sections += ' '.repeat(45) + "START(" + stack.$name + "_start),\n"
            sections += ' '.repeat(45) + "END(" + stack.$name + "_end)\n"
        }
    })

    sections += "\n\n"

    // Get sections corresponding to Easy Mode Link
    let commonCodeSections = ""
    modInstances('/ti/security/EasyMode_link', inst).forEach(x => { 
        if(x.isCommonCode)
            commonCodeSections += sectionListModule(x, APRList, cpu, sysSec)
        else
            sections += sectionListModule(x, APRList, cpu, sysSec, true)
    })
    sections += commonCodeSections                                  //!! Always placing common code sections at the end

    // Get sections corresponding to Easy Mode SharedMem
    modInstances('/ti/security/EasyMode_sharedMem', inst).forEach(x => { 
        sections += sectionListSharedMem(x, APRList, cpu, true)
    })

    // Get sections for manually created Sections                           -----> This is CPU specific, thus done separately inside CPUx CONFIGURE context
    /* modInstances('/ti/security/OutputSection', inst).forEach(section => { 
        sections += sectionListManual_configure(section, APRList, true, cpu)
    }) */

    return sections
}

function appendManualSections_configure(sections, APRList, cpu){
    let ret = sections
    modInstancesByCPU('/ti/security/OutputSectionConfigure', cpu).forEach(section => { 
        ret += sectionListManual_configure(section, APRList, true, cpu)
    })
    return ret
}

function getSectionsMinimal(cpu){
    let sections = ""
    let APRList = allocateAllMemoryRegions()[cpu].filter(apr=> apr.type != "Peripheral")
    let sectionsList = modInstancesByCPU('/ti/security/OutputSection', cpu)

    if(!isContextCPU1()){
        let resetVectorAddr = getConfigFromStaticModule("/ti/security/APR", "resetVectorAddress", system.context)
        let nmiVectorAddr = getConfigFromStaticModule("/ti/security/APR", "nmiVectorAddress", system.context)

        if(resetVectorAddr.available && resetVectorAddr.value > 0x0){
            sections += `    resetvector : > 0x${resetVectorAddr.value.toString(16)}, palign(8)  \n`
        }

        if(nmiVectorAddr.available && nmiVectorAddr.value > 0x0){
            sections += `    nmivector   : > 0x${nmiVectorAddr.value.toString(16)}, palign(8)  \n`
        }
    }

    let firstCode = APRList.filter(apr => {return apr.type == "Code"})
                            .sort((a,b) => {return a.startAddr - b.startAddr})[0]   //!! check what to put
    let codeStartSection = ""
    if(firstCode){
        codeStartSection = `    codestart : > 0x${firstCode.startAddr.toString(16)}, palign(8)  \n`
    }
    let a = sectionsList.filter(sec => sec.$name == "codestart")[0]
    if(a){
        let codestartApr = APRList.filter(apr => apr.name == a.sectionMemory)[0]
        if(codestartApr)
            codeStartSection = `    codestart : > 0x${codestartApr.startAddr.toString(16)}, palign(8)  \n`
    }

    sections += codeStartSection

    let flashAprList = allocateAllMemoryRegions()[cpu].filter(apr=> apr.memType == "Flash")
    if((cpu == "CPU1" || cpu == "CPU3") && flashAprList.length){
        let certSection = `    cert : {} > CERT, palign(8) \n`
        sections += certSection
    }

    // Get sections for manually created Sections
    modInstances('/ti/security/OutputSection') 
    .filter(sec => sec.$name != "codestart" && sec.sectionMemory != "None" )
    .forEach(section => {
        sections += sectionListManual(section, APRList, false)
    })

    return sections
}

function getSectionsMinimal_configure(cpu, inst){
    let sections = ""
    let APRList = allocateAllMemoryRegions()[cpu].filter(apr=> apr.type != "Peripheral")
    let sectionsList = modInstancesByCPU('/ti/security/OutputSection', cpu)

    if(!isContextCPU1()){
        let resetVectorAddr = getConfigFromStaticModule("/ti/security/APR", "resetVectorAddress", cpu)
        let nmiVectorAddr = getConfigFromStaticModule("/ti/security/APR", "nmiVectorAddress", cpu)

        if(resetVectorAddr.available && resetVectorAddr.value > 0x0){
            sections += `    resetvector : > 0x${resetVectorAddr.value.toString(16)}, palign(8)  \n`
        }

        if(nmiVectorAddr.available && nmiVectorAddr.value > 0x0){
            sections += `    nmivector   : > 0x${nmiVectorAddr.value.toString(16)}, palign(8)  \n`
        }
    }

    let firstCode = APRList.filter(apr => {return apr.type == "Code"})
                            .sort((a,b) => {return a.startAddr - b.startAddr})[0]   //!! check what to put
    let codeStartSection = ""
    if(firstCode){
        codeStartSection = `    codestart : > 0x${firstCode.startAddr.toString(16)}, palign(8)  \n`
    }
    let a = sectionsList.filter(sec => sec.$name == "codestart")[0]
    if(a){
        let codestartApr = APRList.filter(apr => apr.name == a.sectionMemory)[0]
        if(codestartApr)
            codeStartSection = `    codestart : > 0x${codestartApr.startAddr.toString(16)}, palign(8)  \n`
    }

    sections += codeStartSection

    let flashAprList = allocateAllMemoryRegions()[cpu].filter(apr=> apr.memType == "Flash")
    if((cpu == "CPU1" || cpu == "CPU3") && flashAprList.length){
        let certSection = `    cert : {} > CERT, palign(8) \n`
        sections += certSection
    }

    // Get sections for manually created Sections
    modInstances('/ti/security/OutputSection', inst)
    .filter(sec => sec.$name != "codestart" && sec.sectionMemory != "None" )
    .forEach(section => {
        sections += sectionListManual(section, APRList, false)
    })

    return sections
}

function getMemoryList(cpu)
{
    let APRList     = allocateAllMemoryRegions()[cpu]
                        .filter(apr=> /* apr.type != "Peripheral" && */
                                      !apr.name.startsWith("FLASHCOVER_"))
                        .sort((a,b) => {return a.startAddr - b.startAddr})
    let maxLen      = _.maxBy(APRList, apr => apr.name.length).name.length

    var list = ""

    // RAM memories
    list += "    // RAM MEMORY\n\n"

    APRList
    .filter(apr => {return apr.memType == "RAM"})
    .forEach(item =>
    {
        let size    = item.endAddr - item.startAddr
        let spaces  = ' '.repeat(maxLen - item.name.length)

        list += "    " + memName(item) + spaces + " : origin = 0x" + toHex(item.startAddr, 8) + ", length = 0x" + toHex(size, 8)
        list += getSECGROUPNew(item, maxLen) + "\n"
    })

    // FLASH memories
    list += "\n    // FLASH MEMORY\n\n"

    let flashMemoryList = APRList.filter(apr => {return apr.memType == "Flash"})

    // Create CERT memory for non-SSU allocation
    let checkSysSec = modStaticByCPU("/ti/security/System_Security", CONTEXT_CPU1)
    if(cpu == CONTEXT_CPU1 && !checkSysSec && flashMemoryList.length)
    {
        flashMemoryList.unshift
        ({
                "name": "CERT",
                "ramMem": ["flc1set1_SECT_1"],
                "startAddr": 0x10000000,
                "endAddr": 0x10001000,
                "size": 4096,
                "memRegion": null,
                "type": "Data",
                "memType": "Flash",
                "implicitRegion": true,
                "specialAprStatus": "signature_CPU1"
            }
        )
    }

    let checkSysSecCpu3 = modStaticByCPU("/ti/security/System_Security", CONTEXT_CPU3)
    if(cpu == CONTEXT_CPU3 && !checkSysSecCpu3 && flashMemoryList.length)
    {
        flashMemoryList.unshift
        ({
                "name": "CERT",
                "ramMem": ["flc2set1_SECT_1"],
                "startAddr": 0x10400000,
                "endAddr": 0x10401000,
                "size": 4096,
                "memRegion": null,
                "type": "Data",
                "memType": "Flash",
                "implicitRegion": true,
                "specialAprStatus": "signature_CPU3"
            }
        )
    }

    flashMemoryList
    .forEach(item =>
    {
        let size    = item.endAddr - item.startAddr
        let spaces  = ' '.repeat(maxLen - item.name.length)

        if((item.name == "APR_RESERVED_sign_CPU1") || ((item.name == "APR_RESERVED_sign_CPU3"))) //!! tag
        {
            spaces = ' '.repeat(maxLen - 4)
            list += "    " + "CERT" + spaces + " : origin = 0x" + toHex(item.startAddr, 8) + ", length = 0x" + toHex(size, 8)
        }
        else
            list += "    " + memName(item) + spaces + " : origin = 0x" + toHex(item.startAddr, 8) + ", length = 0x" + toHex(size, 8)
        list += getSECGROUPNew(item, maxLen) + "\n"
    })

    // PERIPHERAL memories

    if(checkSysSec && checkSysSec["togglePeripheralRegionsInLinker"]){
        list += "\n    // PERIPHERAL MEMORY REGIONS\n\n"

        APRList
        .filter(apr => {return apr.type == "Peripheral"})
        .forEach(item =>
        {
            let size    = item.endAddr - item.startAddr
            let spaces  = ' '.repeat(maxLen - item.name.length)

            list += "    " + memName(item) + spaces + " : origin = 0x" + toHex(item.startAddr, 8) + ", length = 0x" + toHex(size, 8) + " \n"
        })
    }
    
    return list
}


function getMemoryList_configure(cpu)
{
    var list = ""

    let APRList     = allocateAllMemoryRegions()[cpu]
                        .filter(apr=> /* apr.type != "Peripheral" && */
                                      !apr.name.startsWith("FLASHCOVER_"))
                        .sort((a,b) => {return a.startAddr - b.startAddr})

    if(!APRList || !APRList.length) return list
    let maxLen      = _.maxBy(APRList, apr => apr.name.length).name.length


    // RAM memories
    list += "    // RAM MEMORY\n\n"

    APRList
    .filter(apr => {return apr.memType == "RAM"})
    .forEach(item =>
    {
        let size    = item.endAddr - item.startAddr
        let spaces  = ' '.repeat(maxLen - item.name.length)

        list += "    " + memName(item) + spaces + " : origin = 0x" + toHex(item.startAddr, 8) + ", length = 0x" + toHex(size, 8)
        list += getSECGROUPNew_configure(item, maxLen, cpu) + "\n"
    })

    // FLASH memories
    list += "\n    // FLASH MEMORY\n\n"

    let flashMemoryList = APRList.filter(apr => {return apr.memType == "Flash"})

    // Create CERT memory for non-SSU allocation
    let checkSysSec = modStaticByCPU("/ti/security/System_Security", CONTEXT_CPU1)
    if(cpu == CONTEXT_CPU1 && !checkSysSec && flashMemoryList.length)
    {
        flashMemoryList.unshift
        ({
                "name": "CERT",
                "ramMem": ["flc1set1_SECT_1"],
                "startAddr": 0x10000000,
                "endAddr": 0x10001000,
                "size": 4096,
                "memRegion": null,
                "type": "Data",
                "memType": "Flash",
                "implicitRegion": true,
                "specialAprStatus": "signature_CPU1"
            }
        )
    }

    let checkSysSecCpu3 = modStaticByCPU("/ti/security/System_Security", CONTEXT_CPU3)
    if(cpu == CONTEXT_CPU3 && !checkSysSecCpu3 && flashMemoryList.length)
    {
        flashMemoryList.unshift
        ({
                "name": "CERT",
                "ramMem": ["flc2set1_SECT_1"],
                "startAddr": 0x10400000,
                "endAddr": 0x10401000,
                "size": 4096,
                "memRegion": null,
                "type": "Data",
                "memType": "Flash",
                "implicitRegion": true,
                "specialAprStatus": "signature_CPU3"
            }
        )
    }

    flashMemoryList
    .forEach(item =>
    {
        let size    = item.endAddr - item.startAddr
        let spaces  = ' '.repeat(maxLen - item.name.length)

        if((item.name == "APR_RESERVED_sign_CPU1") || ((item.name == "APR_RESERVED_sign_CPU3"))) //!! tag
        {
            spaces = ' '.repeat(maxLen - 4)
            list += "    " + "CERT" + spaces + " : origin = 0x" + toHex(item.startAddr, 8) + ", length = 0x" + toHex(size, 8)
        }
        else
            list += "    " + memName(item) + spaces + " : origin = 0x" + toHex(item.startAddr, 8) + ", length = 0x" + toHex(size, 8)
        list += getSECGROUPNew_configure(item, maxLen, cpu) + "\n"
    })

    // PERIPHERAL memories

    if(checkSysSec && checkSysSec["togglePeripheralRegionsInLinker"]){
        list += "\n    // PERIPHERAL MEMORY REGIONS\n\n"

        APRList
        .filter(apr => {return apr.type == "Peripheral"})
        .forEach(item =>
        {
            let size    = item.endAddr - item.startAddr
            let spaces  = ' '.repeat(maxLen - item.name.length)

            list += "    " + memName(item) + spaces + " : origin = 0x" + toHex(item.startAddr, 8) + ", length = 0x" + toHex(size, 8) + " \n"
        })
    }
    
    return list
}

function assignLinkID() 
{
    var linkID = []
    var id = 3
    modInstances('/ti/security/Link').forEach(x =>
    {
        if(x.isLink2)
            linkID[x.$name] = 2
        else if(x.isLink1)
            linkID[x.$name] = 1
        else
           linkID[x.$name] = id++
    })
    return linkID
}

function assignLinkID_configure(core) 
{
    var linkID = {}
    var id = 3
    modInstances(`/ti/security/${core}_Link`).forEach(x =>
    {
        if(x.isLink2)
            linkID[x.$name] = 2
        else if(x.isLink1)
            linkID[x.$name] = 1
        else
           linkID[x.$name] = id++
    })
    return linkID
}


function assignStackID() 
{
    let ctx = currentContext()
    var stackID = []
    var id = 3
    modInstances('/ti/security/Stack').forEach(x =>
    {
        if(x.$name == `${ctx}_STACK2_STACK`) //!! tags
            stackID[x.$name] = 2
        else if(x.$name == `${ctx}_STACK1_STACK`)
            stackID[x.$name] = 1
        else
            stackID[x.$name] = id++
    })
    return stackID
}

function assignStackID_configure(core)
{
    var stackID = {}
    var id = 3
    modInstances(`/ti/security/${core}_Stack`).forEach(x =>
    {
        if(x.$name == `${core}_STACK2_STACK`) //!! tags
            stackID[x.$name] = 2
        else if(x.$name == `${core}_STACK1_STACK`)
            stackID[x.$name] = 1
        else
            stackID[x.$name] = id++
    })
    return stackID
}

function getAprWeprotVal(aprName, aprType, cpuId)
{
    let aprNameList = [];
    let ssMain = modStaticByCPU("/ti/security/System_Security", "CPU1")
    let ssCur = modStaticByCPU("/ti/security/System_Security", ("CPU"+String(cpuId)))
    if(ssMain && ssCur)
    {
        ssCur.WEPROT_APRs.forEach(x => {aprNameList.push(x)})

        if(aprNameList.includes(aprName))   
            return 1
        if(aprType == "Code" && ssMain.WEPROT_CODE_BANKS) 
            return 1
        if(aprType == "Data" && ssMain.WEPROT_DATA_BANKS) 
            return 1
    }
    return 0;
}

function addFlashRegions2(type, regions, flx){
    if(type == "cpu1"){
        regions.forEach((set, j) => {
            for(let i=0; i<set.size/4; i++){
                flx.push({name      : set.name + "_SECT_" + i.toString(),
                        weprot    : -1,
                        type      : 'flash',
                        start     : 0x10000000 + j*0x100000  + i*0x1000,
                        size      : 0x1000,
                        end       : 0x10001000 + j*0x100000  + i*0x1000,}
                )
            }
        })
    }
    else if(type == "cpu3"){
        regions.forEach((set, j) => {
            for(let i=0; i<set.size/4; i++){
                flx.push({name      : set.name + "_SECT_" + i.toString(),
                        weprot    : -1,
                        type      : 'flash',
                        start     : 0x10400000 + j*0x100000  + i*0x1000,
                        size      : 0x1000,
                        end       : 0x10401000 + j*0x100000  + i*0x1000,}
                )
            }
        })
    }
    else if(type == "data"){
        regions.forEach((set, j) => {
            for(let i=0; i<set.size/4; i++){
                flx.push({name      : set.name + "_SECT_" + i.toString(),
                        weprot    : -1,
                        type      : 'flash',
                        start     : 0x10C00000 + j*0x100000  + i*0x1000,
                        size      : 0x1000,
                        end       : 0x10C01000 + j*0x100000  + i*0x1000,}
                )
            }
        })
    }
}

function getBankModeConfig(){
    let bankMode = 0;
    let bankModeObj = getConfigFromStaticModule("/ti/security/APR", "bankMode", CONTEXT_CPU1)
    if(bankModeObj.available)
        bankMode = bankModeObj.value;   //!! Add error check if needed
    return bankMode;
}

function constructFlashRegions(){
    let flx = [];
    let bankMode = getBankModeConfig();
    if(bankMode == 0){
        addFlashRegions2("cpu1", flash_code_sets, flx)
    }
    else if(bankMode == 1){
        addFlashRegions2("cpu1", flash_code_sets.filter(x => { return (x.name == "flc1set1" || x.name == "flc2set1")}), flx)
    }
    else if(bankMode == 2){
        addFlashRegions2("cpu1", flash_code_sets.filter(x => { return (x.name == "flc1set1" || x.name == "flc1set2")}), flx)
        addFlashRegions2("cpu3", flash_code_sets.filter(x => { return (x.name == "flc2set1" || x.name == "flc2set2")}), flx)
    }
    else if(bankMode == 3){
        addFlashRegions2("cpu1", flash_code_sets.filter(x => { return x.name == "flc1set1"}), flx)
        addFlashRegions2("cpu3", flash_code_sets.filter(x => { return x.name == "flc2set1"}), flx)
    }
    addFlashRegions2("data", flash_data_sets, flx)
    return flx;
}

function calcWeprotValues(flashSpace){
    let ret = {}

    let flashList = flashSpace;
    let flc1 = flashList.filter(x=>{return x.name.startsWith("flc1")}), flc2 = flashList.filter(x=>{return x.name.startsWith("flc2")})
    let flc1_b0 = flc1.filter(x=>{return x.name.includes("set1")}), flc1_b2 = flc1.filter(x=>{return x.name.includes("set2")})
    let flc2_b0 = flc2.filter(x=>{return x.name.includes("set1")}), flc2_b2 = flc2.filter(x=>{return x.name.includes("set2")})

    ret["flc1_b0"] = weprotCalcUtil(flc1_b0)
    ret["flc1_b2"] = weprotCalcUtil(flc1_b2)
    ret["flc2_b0"] = weprotCalcUtil(flc2_b0)
    ret["flc2_b2"] = weprotCalcUtil(flc2_b2)

    return ret;
}

function weprotCalcUtil(bank){
    let a=0, b=0;
    if(!bank || !bank.length)
        return {a: 0x0, b: 0x0}

    for(let i = 31; i>=0; i--){
        if(i!=31)  a = (a << 1)>>>0;
        let val = (bank[i].weprot != 0) ? 0 : 1;
        a = (a | val)>>>0;
        if(i==0) break;
    }

    for(let i=248; i>=32; i-=8){
        if(i!=248)  b = (b << 1)>>>0;
        let val = (bank[i].weprot != 0) ? 0 : 1;
        b = (b | val)>>>0;
        if(i==32) break;
    }
    // Removed OR with 0xF because of inversion
    b = (b << 4)>>>0;

    return {a,b}
}

function crc32Lookup(bytes){
    //const divisor = 0xEDB88320;       // Reversed polynomial of 0x04C11DB7
    let crc         = 0xFFFFFFFF;       // Initial Value
    const finalXOR  = 0xFFFFFFFF;       // Final XOR value

    for (const byte of bytes){
      crc = crc32Table[(crc ^ byte) & 0xFF] ^ (crc >>> 8);
    }

    return (crc ^ finalXOR)>>>0;
}

function divideBytes(arrayMixed){
    let arrayBytes = [];
    arrayMixed.forEach(a => {
        arrayBytes.push((a & 0xFF)>>>0)
        arrayBytes.push((a & 0xFF00)>>>8)
        arrayBytes.push((a & 0xFF0000)>>>16)
        arrayBytes.push((a & 0xFF000000)>>>24)
    })
    return arrayBytes;
}

function getSeccfgCrc(arrayMixed){
    let arrayBytes = divideBytes(arrayMixed)
    return crc32Lookup(arrayBytes)
}

function getSeccfgLocation(cpuName){
    let bankMode = getConfigFromStaticModule("/ti/security/APR", "bankMode", CONTEXT_CPU1) //!! update with api
    if(bankMode.available)
        return seccfgAddressMapping[cpuName][bankMode.value];
    return 0x0;
}

function getSeccfgLocation_configure(cpuName, bankmode){
    return seccfgAddressMapping[cpuName][bankmode];
}

function getSpecialAprList(){
    let ret = []
    ssuData.aprTags.forEach(a => {
        ret.push({name: a.name})
    })
    return ret;
}

function mergeRegions(objFinal, objFrom, keyList){
    let x = objFinal
    keyList.forEach(key => {
        if(objFinal[key] && objFrom[key]){
            let y = x[key].concat(objFrom[key])
            x[key] = y
        }
    })
    return x
}

function allocateAllMemoryRegions(){
    let cpuListInOrder = getCoreList(1).map(o => {return o.name}).sort().reverse();
    let finalAllocations = {};
    cpuListInOrder.forEach(cpu => {
        finalAllocations[cpu] = []
    })

    finalAllocations = mergeRegions(finalAllocations, allocateRamMemories(), cpuListInOrder)
    let flashAllocReturnObject = allocateFlashMemories()
    finalAllocations = mergeRegions(finalAllocations, flashAllocReturnObject.aprList, cpuListInOrder)
    finalAllocations = mergeRegions(finalAllocations, allocatePeripheralMemories(), cpuListInOrder)

    //!! Add external memories

    finalAllocations["flashSpace"] = flashAllocReturnObject.available_flash
    //console.log(finalAllocations)
    return finalAllocations
}


function allocateRamMemories(){
    // SSU rules allocation
    return allocateRamMemoriesUtil();

    //!! Add non SSU rules allocation
}

function allocateRamMemoriesUtil(){
    let cpuListInOrder = getCoreList(1).map(o => {return o.name}).sort().reverse();
    let memRegionsAll = getAPRsInRAMAll()
    let availableMemoryAll = memoryData.ram_mem;
    availableMemoryAll.forEach(memUnit => {
        memUnit.used = 0;
    })
    let finalAllocations = {};
    cpuListInOrder.forEach(cpu => {
        finalAllocations[cpu] = []
    })

    cpuListInOrder.forEach(cpu => {
        // No regions on this CPU
        if(!(memRegionsAll[cpu]) || !(memRegionsAll[cpu].length)) {return;}

        if(cpu == "CPU1"){
            let check = getConfigFromStaticModule("/ti/security/System_Security", "cpuList", CONTEXT_CPU1)
            let bankMode = getBankModeConfig();
            cpuListInOrder.filter(core => core != cpu)
            .forEach(core => {
                if(check.available && check.value.includes(core))
                    placeRamCoverRegion(core, cpu, finalAllocations)
                    if(core == CONTEXT_CPU3 && bankMode >= 2)
                        placeFlashCoverRegion(core, cpu, finalAllocations)
            })
        }

        // Sorted order of regions
        // 1. ZeroWS 2. Normal 3. Shared (overall in decreasing order of size)
        // For shared regions
        // - Assume to be part of CPU2/CPU3 and allot, then apply same boundaries on CPU1 region
        // - If shared bw 2+3 or 1+2+3, allotted at very end since WS are least optimal
        // - Can also retry unallotted regions at very end, if not possible, return with -1

        let sharedRegions = _.remove(memRegionsAll[cpu], (reg) => {
            return (reg.share.length > 0)
        })

       // console.log(sharedRegions)

        let sortedRegions = _.sortBy(memRegionsAll[cpu],
                                    [
                                        (reg) => {
                                            if (reg.specialAprStatus == "link2_ram_code") return -2;
                                            return 0;
                                        },
                                        (reg) => {
                                            if(reg.isShared) return reg.sharedCores.length;
                                            return 0;
                                        },
                                        (reg) => { return -reg.zeroWS},
                                        (reg) => { return -reg.memSize},
                                        (reg) => {                             // Code then data
                                            if(reg.type == "Code") return 0;
                                            return 1;
                                        }
                                    ])

        /* let lowPriorityRegions = _.remove(sortedRegions, (reg) => {
            if(reg.isShared && (reg.sharedCores.includes("CPU2") && reg.sharedCores.includes("CPU3")))
                return true;
            if(reg.coreName == "CPU2" && (reg.sharedCores.includes("CPU3")))
                return true;
            if(reg.coreName == "CPU3" && (reg.sharedCores.includes("CPU2")))
                return true;
            return false;
        }) */

        sortedRegions.forEach(memRegion => {
            placeRamMemory(availableMemoryAll, memRegion, cpu, finalAllocations, false)
        })

        sharedRegions.forEach(memRegion => {
            placeRamMemory(availableMemoryAll, memRegion, cpu, finalAllocations, true)
        })
    })
    //console.log(finalAllocations)
    return finalAllocations;
}

function placeRamMemory(availableMemoryAll, memRegion, cpu, finalAllocations, isShared = false){
    let placementOrder = memoryData.ramPlacementPreference
                                    [cpu]
                                    [memRegion.type]

    let found = 0;
    placementOrder.forEach(item => {
        if(found) return;
        let allowedRegions = _.filter(availableMemoryAll, (mem) =>
                                {return (!(mem.used) &&
                                          (mem.name.includes(item.region))
                                        )})
        let result = findRAM(allowedRegions, item.order,  memRegion)

        if(result.found){
            found = result.found;
            result.allottedRamUnits.forEach(ramUnit => {
                let thisIdx = ramUnit.unitIndex;
                availableMemoryAll[thisIdx].used = 1;
                //!! func for updating used and shared
            })

            finalAllocations[cpu].push({
                name: memRegion.$name,
                memRegion: memRegion,
                ramUnits: result.allottedRamUnits,
                startAddr: result.allottedRamUnits[0].start,
                endAddr: result.allottedRamUnits[result.num_reqd - 1].end,
                type: memRegion.type,
                memType: "RAM",
                implicitRegion: false,
                specialAprStatus: memRegion.specialAprStatus
            })

            if(isShared){
                memRegion.share.forEach(core => {
                    // Other core context is not opened
                    if(!finalAllocations[core])
                        return;

                    let flag = checkRamRegionOverlap(finalAllocations[core], result.allottedRamUnits[0].start, result.allottedRamUnits[result.num_reqd - 1].end)
                    if(flag){
                        // NO OVERLAP
                        // create region on other core implicitly
                        finalAllocations[core].push({
                            name: memRegion.$name + "_SHARED_" + cpu.toUpperCase(),
                            memRegion: memRegion,
                            ramUnits: result.allottedRamUnits,
                            startAddr: result.allottedRamUnits[0].start,
                            endAddr: result.allottedRamUnits[result.num_reqd - 1].end,
                            type: memRegion.type,
                            memType: "RAM",
                            implicitRegion: true,
                            specialAprStatus: memRegion.specialAprStatus,
                            sharedAutoRegion : true
                        })
                    }
                    else{
                        // cant create shared region due to overlap
                        finalAllocations[cpu].push({
                            name: memRegion.$name + "_SHARED_" + cpu.toUpperCase(),
                            memRegion: null,
                            ramUnits: [],
                            startAddr: -1,
                            endAddr: -1,
                            type: memRegion.type,
                            memType: "RAM",
                            implicitRegion: true,
                            specialAprStatus: memRegion.specialAprStatus,
                            sharedAutoRegion : true
                        })
                    }
                })
                //console.log(memRegion, result)
            }
        }
        else{
            finalAllocations[cpu].push({
                name: memRegion.$name,
                memRegion: memRegion,
                ramUnits: [],
                startAddr: -1,
                endAddr: -1,
                type: memRegion.type,
                memType: "RAM",
                specialAprStatus: memRegion.specialAprStatus,
                implicitRegion: false //!!
            })
        }
    })
}

function checkRamRegionOverlap(coreAllocations, xS, xE){
    let flag = true;
    coreAllocations.every(reg => {
        let yS = reg.startAddr, yE = reg.endAddr
        if(xS<yE && yS<xE){
            flag = false;
            return false;
        }
        return true;
    })
    return flag
}

function placeRamCoverRegion(srcCore, destCore, finalAllocations){
    let ramRegions = finalAllocations[srcCore]
                        .filter(a => (a.memType == "RAM") && (a.type == "Code"))
                        .sort((a,b) => a.startAddr - b.startAddr)

    let ret= []
    if(ramRegions.length == 0){
        return ret;
    }

    let idx = 0;
    for(let i=0; i<ramRegions.length; i++){
        if(i==0){
            ret[idx] = {startAddr: 0, endAddr: 0, ramCoverRegion: true, name: srcCore+"_RamCoverRegion"+String(idx), type: null, memType: "RAM", implicitRegion: true, specialAprStatus: "ram_cover_" + srcCore};
            ret[idx].startAddr = ramRegions[i].startAddr
            ret[idx].endAddr = ramRegions[i].endAddr
            ret[idx].type = "Data"
            ret[idx].memRegion = null
            continue;
        }
        if((ramRegions[i].startAddr == (ramRegions[i-1].endAddr))){
            ret[idx].endAddr = ramRegions[i].endAddr
        }
        else{
            idx++;
            ret[idx] = {startAddr: 0, endAddr: 0, ramCoverRegion: true, name: srcCore+"_RamCoverRegion"+String(idx), type: null, memType: "RAM", implicitRegion: true, specialAprStatus: "ram_cover_" + srcCore};
            ret[idx].startAddr = ramRegions[i].startAddr
            ret[idx].endAddr = ramRegions[i].endAddr
            ret[idx].type = "Data"
            ret[idx].memRegion = null
            continue;
        }
    }

    ret.forEach(r => finalAllocations[destCore].push(r))
}

function placeFlashCoverRegion(srcCore, destCore, finalAllocations){
    finalAllocations[destCore].push({
        name            : "FLASHCOVER_"+ srcCore.toUpperCase(),
        memRegion       : null,
        startAddr       : 0x10400000,
        endAddr         : 0x10600000,
        isShared        : null,
        cores           : null,
        weprot          : null,
        mpuEnabled      : null,
        memType         : "Flash",
        implicitRegion  : true,
        type            : "Data",
        specialAprStatus: "flash_cover_" + srcCore
    })
}

function findRAM(allowedRegions, order, memRegion){
    let found = 0, startIdx=-1, endIdx=-1;
    let num_reqd = Math.floor(memRegion.memSize/4);
    let allottedRamUnits = [];

    // First-Fit allocation

    if(order == "D"){
        let p1=0, p2=0, curr_length=0, flag=0;
        while((p1 < allowedRegions.length) && (p2 < allowedRegions.length)){
            curr_length = p2 - p1 + 1;
            if(curr_length == num_reqd){
                flag = 1;
                break;
            }
            p2++;
            if(p2 == allowedRegions.length)
                break;
            if((p2 != p1) && (allowedRegions[p2].start != allowedRegions[p2-1].end)){
                p1 = p2;
                continue;
            }
        }
        if(flag){
            found = 1; startIdx = p1; endIdx = p2;
        }
    }

    else if(order == "U"){
        let p1=allowedRegions.length - 1, p2=p1, curr_length=0, flag=0;
        while((p1 >= 0) && (p2 >= 0)){
            curr_length = p2 - p1 + 1;
            if(curr_length == num_reqd){
                flag = 1;
                break;
            }
            p1--;
            if(p1 < 0)
                break;
            if((p1 != p2) && (allowedRegions[p1].end != allowedRegions[p1+1].start)){
                p2 = p1;
                continue;
            }
        }
        if(flag){
            found = 1; startIdx = p1; endIdx = p2;
        }
    }

    if(found)
        allottedRamUnits = allowedRegions.slice(startIdx, endIdx + 1)

    return {found, allottedRamUnits, num_reqd}
}

function allocateFlashMemories(){
    // SSU rules allocation
    return allocateFlashMemoriesUtil();

    //!! Add non SSU rules allocation
}

function allocateFlashMemoriesUtil()
{
    let aprList = {}
    let alreadyAllocatedAprs = []

    let aprs = getAPRsInFlashAllNew();
    let contextList = getCoreList(1).map(o => {return o.name}).sort();
    //console.log(contextList)
    contextList.forEach(cpu => {
        aprList[cpu] = []
    })

    let WEPROT_CODE_BANKS = false, WEPROT_DATA_BANKS = false
    let c = getConfigFromStaticModule("/ti/security/System_Security", "WEPROT_CODE_BANKS", CONTEXT_CPU1)
    let d = getConfigFromStaticModule("/ti/security/System_Security", "WEPROT_DATA_BANKS", CONTEXT_CPU1)
    if(!c.available || !d.available){
        //return aprList                      //!! non ssu flash allocation
    }
    else{
        WEPROT_CODE_BANKS = c.value;
        WEPROT_DATA_BANKS = d.value;
    }

    let flx = constructFlashRegions()

    // Create CERT memory for non-SSU allocation
    let checkSysSec = modStaticByCPU("/ti/security/System_Security", CONTEXT_CPU1)
    if(!checkSysSec && flx.length){
        flx = flx.slice(1)  // Remove 1st 4kb block for CPU1 CERT in case of non-ssu allocation
    }
    checkSysSec = modStaticByCPU("/ti/security/System_Security", CONTEXT_CPU3)
    if(!checkSysSec && flx.length){
        flx = _.reject(flx, { 'name': "flc2set1_SECT_0" }); // Remove 4kb block for CPU3 CERT in case of non-ssu allocation
    }

    let available_flash = flx

    for(let i=0; i<available_flash.length; i++){
        available_flash[i].used = 0;
        if(available_flash[i].name.includes("DATA"))
            available_flash[i].weprot = WEPROT_DATA_BANKS ? 1 : 0;
        else
            available_flash[i].weprot = WEPROT_CODE_BANKS ? 1 : -1;
    }


    let num_reqd, ret;
    let indices = { lastIdx : -1, lastCpuIdx : -1 }
    let weprot_last = 0;


    let priorityFlashAprTags = [
        {tag: "signature_CPU1", core: "CPU1", finalCore: "CPU1"},
        {tag: "signature_CPU3", core: "CPU3", finalCore: "CPU3"},
    ]

    priorityFlashAprTags.forEach(priApr => {
        let currApr = aprs[priApr.core].find(o => {return o.specialAprStatus == priApr.tag})
        if(currApr != undefined){
            alreadyAllocatedAprs.push(currApr)
            num_reqd = Math.floor(currApr.memSize/4)
            ret = allocateFromFlash2(currApr, priApr.core, num_reqd, indices, available_flash)
            if(ret == undefined || !ret.length){
                aprList[priApr.core].push({
                    name           : currApr.$name,
                    ramMem          : [],
                    startAddr           : -1,
                    endAddr             : -1,
                    size            : 0,
                    memRegion    : currApr,
                    type: currApr.type,
                    memType: "Flash",
                    implicitRegion: false,
                    specialAprStatus: priApr.tag
                })
                weprot_last = currApr.weprot
            }
            else{
                //console.log(priApr, ret, currApr)
                aprList[priApr.finalCore].push(aprListEntryFlash2(ret, currApr, num_reqd, available_flash))
            }
        }
    })

    contextList.forEach(core => {
        indices.lastCpuIdx = indices.lastIdx;
        let currCoreAprs = aprs[core].filter(o => {return !(alreadyAllocatedAprs.includes(o))})
        //console.log("currCoreAprs:", currCoreAprs)
        /* currCoreAprs = currCoreAprs.sort((a, b) => {if(weprot_last == 0) return a.weprot - b.weprot
                                                                    else return b.weprot - a.weprot}) */
        let sortedRegions = _.sortBy(currCoreAprs,
                                [
                                    (a) => {
                                        if (a.specialAprStatus == "link2_flash_code") return -3         // for remaining cores
                                        else if (a.specialAprStatus.includes("flash_load_")) return -2
                                        else return 0
                                    },
                                    (a) => {
                                        {if(weprot_last == 0) return (a.weprot)
                                            else return (-1 * a.weprot)}
                                    },
                                    (a) => {
                                        if (a.$name == "CPU2_FLASH_REGION") return 0xFFFFFFFF
                                        else return 0
                                    }
                                ])

        sortedRegions.forEach(currApr => {
            num_reqd = Math.floor(currApr.memSize/4)
            ret = allocateFromFlash2(currApr, core, num_reqd, indices, available_flash)
            if(ret == undefined || !ret.length){
                aprList[core].push({
                    name           : currApr.$name,
                    ramMem          : [],
                    startAddr           : -1,
                    endAddr            : -1,
                    size            : 0,
                    memRegion    : currApr,
                    type: currApr.type,
                    memType: "Flash",
                    implicitRegion: false,
                    specialAprStatus: "none"
                })
                weprot_last = currApr.weprot
            }
            else{
                aprList[core].push(aprListEntryFlash2(ret, currApr, num_reqd, available_flash))
                // Create Shared regions
                if(currApr.share.length > 0){
                    currApr.share.forEach(sharedCore => {
                        aprList[sharedCore].push(aprListEntryFlash2(ret, currApr, num_reqd, available_flash, true, core))
                    })
                }
            }
        })
    })

    //console.log(aprList)
    return{aprList, available_flash}
}


function allocateFromFlash2(aprAndCpu, curr_Cpu, num_reqd, indices, flx){
    let {weprot, type, share} = aprAndCpu
    let bankMode = getBankModeConfig();

    // Bankmode 0 & 1
    let freeFlash = flx.filter((a,i) => {return ((a.used != 1) /* && (i>indices.lastCpuIdx) */) })
                             .filter(a => {return [weprot,-1].includes(a.weprot)})
    if(type == "Code")
        freeFlash = freeFlash.filter(a => {return !a.name.includes("DATA")})
    if(share.length > 0){
        if(type != "Data") return []    // Shared Flash APRs can only be in Data Flash Bank
        freeFlash = freeFlash.filter(a => {return a.name.includes("DATA")})
    }

    // Bankmode 2 & 3
    if((bankMode == 2 || bankMode == 3)){
        if(curr_Cpu == "CPU1"){
            freeFlash = freeFlash.filter(a => {return !a.name.includes("flc2")})
        }
        else if(curr_Cpu == "CPU3"){
            freeFlash = freeFlash.filter(a => {return !a.name.includes("flc1")})
        }
    }

    if(!freeFlash.length) return []

    let ptr_start=0, ptr_end=0, curr_length=0, flag=0;
    while(ptr_start < freeFlash.length && ptr_end < freeFlash.length){
        curr_length = ptr_end - ptr_start + 1;
        if(curr_length == num_reqd){
            flag = 1;
            break;
        }
        ptr_end++;
        if(ptr_end == freeFlash.length) break;
        if((ptr_end != ptr_start) && (freeFlash[ptr_end].start != freeFlash[ptr_end-1].end)){
            ptr_start = ptr_end;
            continue;
        }
    }

    if(flag){
        indices.lastIdx = Math.max(indices.lastIdx, flx.indexOf(freeFlash[ptr_end]))
        return freeFlash.slice(ptr_start, ptr_end + 1)
    }
    return [];
}


function aprListEntryFlash2(flMem, apr, num_reqd, flx, isShared = false, sharingCore = ""){

    let ret = {
        name           : apr.$name,
        ramMem          : flMem.map(x=>{return x.name}),
        startAddr       : flMem[0].start,
        endAddr         : flMem[num_reqd-1].end,
        size            : 0x1000 * num_reqd,
        memRegion       : apr,
        type            : apr.type,
        memType         : "Flash",
        implicitRegion  : isShared,
        specialAprStatus: apr.specialAprStatus
    }
    if(!isShared) // Not already created on another core
        updateFlashUsageProtection(ret.ramMem, apr.weprot, flx)
    else{
        ret.name += "_SHARED_" + sharingCore.toUpperCase()
    }
    return ret;
}

function getAutoPeriphAPRsByLink(linkName, core){
    let ret = {
        "RO": [],
        "RW": []
    }
    let autoPeriphList = updatePeripheralAllocation()[core]
    if(!autoPeriphList) return ret

    let easyLinkList = modInstancesByCPU('/ti/security/EasyMode_link', core)
                        .map(l => {return l.$name}).sort()

    let idx = easyLinkList.findIndex(l => l == linkName)
    autoPeriphList.forEach(reg => {
        if(reg.permList[idx] == "R")
            ret["RO"].push(reg.name)
        if(reg.permList[idx] == "W")
            ret["RW"].push(reg.name)
    })

    return ret;
}

function allocatePeripheralMemories(){
    //!! Only used when SSU enabled
    let cpuListInOrder = getCoreList(1).map(o => {return o.name}).sort().reverse();
    let finalAllocations = {};
    cpuListInOrder.forEach(cpu => {
        finalAllocations[cpu] = []
    })
    // !! validate overlap bw auto and manual
    finalAllocations = mergeRegions(finalAllocations, getPeripheralAPRsAll(), cpuListInOrder)
    finalAllocations = mergeRegions(finalAllocations, updatePeripheralAllocation(), cpuListInOrder)

    return finalAllocations
}

function getPeripheralPermissions()
{
    let ret = []
    let existingContexts = getCoreList(1).map(o => {return o.name});
    existingContexts.forEach(cpu => {
        let easyLink = modInstancesByCPU('/ti/security/EasyMode_link', cpu)
        if(easyLink && easyLink.length){
            easyLink.forEach(link => {
                ret.push({
                    $name: link.$name,
                    ro_list: link.periphs_ro,
                    rw_list: link.periphs_rw,
                    cpu: cpu
                })
            })
        }
    })
    return ret
}

function updatePeripheralAllocation(){
    let permByLink = getPeripheralPermissions()
    const cpus = [...new Set(permByLink.map(item => item.cpu))]

    let reqdAprsList = {};
    let existingContexts = getCoreList(1).map(o => {return o.name});
    existingContexts.forEach(cpuCurr => {
        reqdAprsList[cpuCurr] = []
    })

    cpus.forEach(cpuCurr => {
        let permByPeripheral = mapPeripheraltoLink(permByLink.filter(a => {return a.cpu == cpuCurr}))
        reqdAprsList[cpuCurr] = allocatePeripheralAprsAuto(permByPeripheral)
    })
    return reqdAprsList;
}

function mapPeripheraltoLink(permByLink){
    let linksSorted = []
    let periphsNeeded = new Set()

    permByLink.forEach(a => {
        linksSorted.push(a.$name)
        a.ro_list.forEach(x => periphsNeeded.add(x))
        a.rw_list.forEach(x => periphsNeeded.add(x))
    })
    linksSorted = linksSorted.sort()

    let props = {};
    periphsNeeded.forEach(p => {
        props[p] = {}
        linksSorted.forEach(l => {props[p][l] = "X"})
    })
    permByLink.forEach(a => {
        a.ro_list.forEach(x => {
            props[x][a.$name] = "R"
        })
        a.rw_list.forEach(x => {
            props[x][a.$name] = "W"
        })
    })

    let ret = []
    let periphOrderedList = peripheralData.getPeriphsSortedbyFrame()
    Object.keys(props).forEach(p => {
        let pListItem = periphOrderedList.find(a => a.name == p)
        ret.push({
            name: p,
            permList: Object.values(props[p]),
            start: pListItem.actualStart,           //!! not actually used, but maintaining for info
            end: pListItem.actualEnd,               //!! same as above
            listIndex: periphOrderedList.indexOf(pListItem)
        })
    })
    //console.log(ret)
    return ret.sort((a,b) => {return a.start - b.start});
}

function allocatePeripheralAprsAuto(permByPeripheral){
    let ret= []

    if(permByPeripheral.length == 0){
        return [];
    }

    let idx = 0;
    for(let i=0; i<permByPeripheral.length; i++){
        if(i==0){
            ret[idx] = {peripheralList: [], startAddr: 0, endAddr: 0, autoPeriphRegion: true, name: "PeriphAutoRegion"+String(idx), type: "Peripheral", memType: null, implicitRegion: true, specialAprStatus: "none"};
            ret[idx].peripheralList.push(permByPeripheral[i].name);
            ret[idx].startAddr = permByPeripheral[i].start
            ret[idx].endAddr = permByPeripheral[i].end
            ret[idx].permList = permByPeripheral[i].permList
            ret[idx].memRegion = null
            continue;
        }
        if((permByPeripheral[i].listIndex == (permByPeripheral[i-1].listIndex + 1)) && _.isEqual(permByPeripheral[i].permList, permByPeripheral[i-1].permList)){
            ret[idx].peripheralList.push(permByPeripheral[i].name);
            ret[idx].endAddr = permByPeripheral[i].end
        }
        else{
            idx++;
            ret[idx] = {peripheralList: [], startAddr: 0, endAddr: 0, autoPeriphRegion: true, name: "PeriphAutoRegion"+String(idx), type: "Peripheral", memType: null, implicitRegion: true, specialAprStatus: "none"};
            ret[idx].peripheralList.push(permByPeripheral[i].name);
            ret[idx].startAddr = permByPeripheral[i].start
            ret[idx].endAddr = permByPeripheral[i].end
            ret[idx].permList = permByPeripheral[i].permList
            ret[idx].memRegion = null
            continue;
        }
    }
    //console.log(permByPeripheral)
    return ret;
}

const itemTemplateCommon = {
    name            : null,
    memRegion       : null,
    startAddr       : null,
    endAddr         : null,
    isShared        : null,
    cores           : null,
    weprot          : null,
    mpuEnabled      : null,
    implicitRegion  : null,
    type            : null,
}

function removedOccupiedRegions(memList, aprList){
    let retList = []
    let idx = 0;

    aprList.forEach(a => {
        if(idx >= memList.length) return;
        while(idx < memList.length && memList[idx].start < a.startAddr){
            retList.push(memList[idx])
            idx++;
        }
        while(idx < memList.length && memList[idx].start < a.endAddr){
            idx++;
        }
    })
    while(idx < memList.length){
        retList.push(memList[idx])
        idx++;
    }

    return mergeUnoccupied(retList)
}

function mergeUnoccupied(memList){
    let ret = []
    let idx = 0;
    let itemTemplate = JSON.parse(JSON.stringify(itemTemplateCommon));

    for(let i=0; i<memList.length; i++){

        if(i==0){
            ret[idx] = JSON.parse(JSON.stringify(itemTemplate))
            ret[idx].startAddr = memList[i].start
            ret[idx].endAddr = memList[i].end
            continue;
        }
        if((memList[i].start == (memList[i-1].end))){
            ret[idx].endAddr = memList[i].end
        }
        else{
            idx++;
            ret[idx] = JSON.parse(JSON.stringify(itemTemplate))
            ret[idx].startAddr = memList[i].start
            ret[idx].endAddr = memList[i].end
            continue;
        }
    }

    return ret
}

function getSummaryList(regions, type, flashSpace=null){
    let ret = [], memList
    if(type == "RAM")
        memList = memoryData.ram_mem    //!! replace like flx
    else if (type = "Flash")
        memList = flashSpace

    let idx=0, itemTemplate = JSON.parse(JSON.stringify(itemTemplateCommon));

    for(let i=0; i<regions.length; i++){
        ret[idx] = JSON.parse(JSON.stringify(itemTemplate))

        ret[idx].name       = regions[i].name
        ret[idx].startAddr  = regions[i].startAddr
        ret[idx].endAddr    = regions[i].endAddr
        ret[idx].memRegion  = regions[i].memRegion
        ret[idx].type       = regions[i].type

        if(type == "RAM")
            ret[idx].implicitRegion = regions[i].implicitRegion

        idx++;
    }

    let unusedList = []
    unusedList = removedOccupiedRegions(memList, ret.sort((a,b) => a.startAddr - b.startAddr))
    ret = ret.concat(unusedList).sort((a,b) => a.startAddr - b.startAddr)

    return ret;
}

function getSummaryListv2(regions, type, flashSpace=null){
    let ret = [], memList
    if(type == "RAM")
        memList = memoryData.ram_mem    //!! replace like flx
    else if (type = "Flash")
        memList = flashSpace

    let idx=0, itemTemplate = JSON.parse(JSON.stringify(itemTemplateCommon));

    for(let i=0; i<regions.length; i++){
        ret[idx] = JSON.parse(JSON.stringify(itemTemplate))

        ret[idx].name       = regions[i].name
        ret[idx].startAddr  = regions[i].startAddr
        ret[idx].endAddr    = regions[i].endAddr
        ret[idx].type       = regions[i].type

        if(type == "RAM")
            ret[idx].implicitRegion = regions[i].implicitRegion

        idx++;
    }

    let unusedList = []
    unusedList = removedOccupiedRegions(memList, ret.sort((a,b) => a.startAddr - b.startAddr))
    ret = ret.concat(unusedList).sort((a,b) => a.startAddr - b.startAddr)

    return ret;
}

function getFlashRegion(core){
    let regions = allocateAllMemoryRegions()[core]
    if(!regions)
        return {origin: 0, length: 0}
    let sortedFlashRegions = regions.filter(a => a.memType == "Flash").sort((a,b) => a.startAddr - b.startAddr)
    if(!sortedFlashRegions || !sortedFlashRegions[0])
        return {origin: 0, length: 0}
    let length = 0;
    sortedFlashRegions.forEach(a => length += a.size)
    return {
        origin: sortedFlashRegions[0].startAddr,
        length: length
    }
}

function getBootPeripherals(inst)
{
    if(isAllocationSetupMode())
    {
        if(!inst || (getCurrentCorePrefix(inst).slice(0,-1) != CONTEXT_CPU1))
            return []
    }
    else
    {
        if(!inst || (system.context != CONTEXT_CPU1))
            return [];
    }

    let periphsNeeded = new Set()
    for(let i=0; i < Math.pow( 2 , inst.bootPinCount ); i++)
    {
        ssuData["link1BootPeripherals"][inst["BOOTDEF" + String(i)]].forEach(p => periphsNeeded.add(p))
    }

    return Array.from(periphsNeeded)
}

function getLink2RequiredAprs()
{
    return ssuData["link2RequiredAprs"]
}

function extractAccess(accessList, accessType){
    let arr = accessList.split("|").slice(0,-1)
    if(!arr || !arr.length)
        return "-"
    let elem = arr.filter(str => str.includes(`SSU_LINK_${accessType}_ACCESS`))
    if(!elem || !elem.length)
        return "-"
    let ret = []
    elem.forEach(e => {
        let found = e.match(/\((.*?)\)/) 
        if(found) ret.push(found[1])
    })

    return ret.join(", ")    
}

//*********************************************************************
// Resource Allocation functionality
//*********************************************************************

//
// Check if tool is loaded in SETUP mode in system context
//
function isAllocationSetupMode()
{
    return (system.context == "system" && system.resourceAllocation.mode == "SETUP" );
}

//
// Check if tool is loaded in CONFIGURE mode
//
function isAllocationConfigureMode() {
    return (system.resourceAllocation.mode == "CONFIGURE");
}

//
// Check if tool is loaded without Resource Allocation mode
//
function isAllocationOff()
{
    return (system.resourceAllocation.mode == "OFF");
}

//
// Return prefix for the core that curr inst belongs to
// Will return "" for non RA module since it has no prefix
//
function getCurrentCorePrefix(inst)
{
    let instPrefix = inst?.$module.$name.split("/").at(-1).split("_")[0]
    if(!instPrefix)
        return ""
    return (instPrefix.includes("CPU")) ? (instPrefix + "_") : ""
}


function hideNonMainCoreConfigs(configList, hidelist) {
    let filteredList = [];
    hideNonMainCoreConfigsUtil(configList, filteredList, hidelist);
    return filteredList;
}

function hideNonMainCoreConfigsUtil(configList, finalList, hidelist) {
    for (let i = 0; i < configList.length; i++) {
        let config = configList[i];
        if(!config)
            continue;
        if(config.name && config.name.startsWith("$")){
            finalList.push(config);
            continue;
        }
        hidelist.forEach(key => {
            if (config.name == (key)) {
                config.hidden = true;
            }
        })
        if (config.hasOwnProperty('config')) {
            config.config = hideNonMainCoreConfigs(config.config, hidelist);
        }

        finalList.push(config);
    }
}

function coreSpecificModuleCheck(inst){
    let ret =
    {
        check   : false,
        core    : "",
        isSSU   : false
    }
    if(!inst) return ret
    let modName = inst?.$module.$name
    if(!modName) return ret
    if(modName.startsWith("/ti/security/CPU"))
    {
        ret.check   = true
        ret.core    = modName.split("/").at(-1).split("_")[0]
        ret.isSS    = modName.endsWith("_System_Security")
    }
    return ret
}

function getCoreSpecificModuleName(originalModName, coreNameString)
{
    let temp = originalModName.split("/")
    if(!(temp[temp.length - 1].startsWith(coreNameString)))                     // in case the core specific name has been passed already
        temp[temp.length - 1] = coreNameString + "_" + temp[temp.length - 1]
    return temp.join("/")
}

//console.log(getCoreSpecificModuleName("/ti/security/System_Security", "CPU0"))


exports =
{
    modStatic: modStatic,
    modStaticByCPU: modStaticByCPU,
    modInstances: modInstances,
    modInstancesByCPU: modInstancesByCPU,
    modInstanceNames: modInstanceNames,
    getConfigFromStaticModule: getConfigFromStaticModule,
    getCoreList: getCoreList,
    CONTEXT_CPU1: CONTEXT_CPU1,
    CONTEXT_CPU2: CONTEXT_CPU2,
    CONTEXT_CPU3: CONTEXT_CPU3,
    isContextCPU1: isContextCPU1,
    isContextCPU2: isContextCPU2,
    isContextCPU3: isContextCPU3,
    getActiveContexts: getActiveContexts,
    currentContext: currentContext,
    getExeLink: getExeLink,
    getAPILink: getAPILink,
    getLinkAccess: getLinkAccess,
    getStack: getStack,
    getZone: getZone,
    toHex: toHex,
    isContiguous: isContiguous,
    getSectionsList: getSectionsList,
    getSectionsList_configure: getSectionsList_configure,
    getMemoryList: getMemoryList,
    assignLinkID: assignLinkID,
    assignStackID: assignStackID,
    getAprWeprotVal: getAprWeprotVal,
    calcWeprotValues: calcWeprotValues,
    getSeccfgCrc: getSeccfgCrc,
    getSeccfgLocation: getSeccfgLocation,
    getSpecialAprList: getSpecialAprList,
    allocateAllMemoryRegions: allocateAllMemoryRegions,
    allocateRamMemories: allocateRamMemories,
    allocateFlashMemories: allocateFlashMemories,
    allocatePeripheralMemories: allocatePeripheralMemories,
    updatePeripheralAllocation: updatePeripheralAllocation,
    getPeripheralPermissions: getPeripheralPermissions,
    getAutoPeriphAPRsByLink: getAutoPeriphAPRsByLink,
    getSummaryList: getSummaryList,
    getSummaryListv2: getSummaryListv2,
    getBankModeConfig: getBankModeConfig,
    getFlashRegion: getFlashRegion,
    getBootPeripherals: getBootPeripherals,
    getLink2RequiredAprs: getLink2RequiredAprs,
    isAllocationSetupMode: isAllocationSetupMode,
    isAllocationConfigureMode: isAllocationConfigureMode,
    isAllocationOff: isAllocationOff,
    getCurrentCorePrefix: getCurrentCorePrefix,
    hideNonMainCoreConfigs: hideNonMainCoreConfigs,
    coreSpecificModuleCheck: coreSpecificModuleCheck,
    assignStackID_configure: assignStackID_configure,
    assignLinkID_configure: assignLinkID_configure,
    getExeLink_configure: getExeLink_configure,
    getAPILink_configure: getAPILink_configure,
    getLinkAccess_configure: getLinkAccess_configure,
    getStack_configure: getStack_configure,
    getZone_configure: getZone_configure,
    getMemoryList_configure: getMemoryList_configure,
    getSECGROUPNew_configure: getSECGROUPNew_configure,
    getActiveContexts_configure: getActiveContexts_configure,
    getAllCoreContexts: getAllCoreContexts,
    getSeccfgLocation_configure: getSeccfgLocation_configure,
    appendManualSections_configure: appendManualSections_configure,
    extractAccess: extractAccess
};