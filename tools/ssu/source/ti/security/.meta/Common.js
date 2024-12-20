const cpuData           = system.getScript('/ti/security/device_specific_information/cpu_data.js');
const memoryData        = system.getScript('/ti/security/device_specific_information/memory_data.js');
const ssuData           = system.getScript('/ti/security/device_specific_information/ssu_data.js');
const peripheralData    = system.getScript('/ti/security/device_specific_information/peripheral_data.js');

let     flash_code_sets         = memoryData.flashMemories.flash_code_sets
let     flash_data_sets         = memoryData.flashMemories.flash_data_sets
const   crc32Table              = ssuData.crc32Table
const   seccfgAddressMapping    = ssuData.seccfgAddressMapping

let CONTEXT_CPU1    = "CPU1";
let CONTEXT_CPU2    = "CPU2";
let CONTEXT_CPU3    = "CPU3";
let CONTEXT_SYSTEM  = "system";

exports = {
    autoForceModules,
    productPath,
    getNodePath,
    findInstance,
    capitalizeFirst,
    esc,
    quoted,
    modStatic,
    modStaticByCPU,
    modInstances,
    modInstancesByCPU,
    modInstNames,
    findDefault,
    validateNames,
    nameResolve,
    CONTEXT_CPU1,
    CONTEXT_CPU2,
    CONTEXT_CPU3,
    isContextCPU1,
    isContextCPU2,
    isContextCPU3,
    getExeLink,
    getAPILink,
    getLinkAccess,
    getStack,
    getZone,
    getAPRListSorted,
    toHex,
    isContiguous,
    findAPRbyName,
    getSectionsList,
    getMemoryList,
    assignLinkID,
    assignStackID,
    getAprWeprotVal,
    calcWeprotValues,
    getSeccfgCrc,
    getSeccfgLocation,
    getSeccfgLocationDummy,
    getSpecialAprList,
    allocateAllMemoryRegions,
    allocateRamMemories,
    allocateFlashMemories,
    allocatePeripheralMemories,
    updatePeripheralAllocation,
    getPeripheralPermissions,
    getConfigFromStaticModule,
    getCoreList,
    getAutoPeriphAPRsByLink,
    getSummaryList,
    getBankModeConfig,
    getFlashRegion,
    getBootPeripherals
};

/*
 *  ======== esc ========
 *  Windows file names in the format of c:\home\user\work are represented in
 *  javascript as c:\\home\\user\\work. When they are written to a file the
 *  double back slahes become a single back slash.  If the written file is
 *  itself a javascript file, then it needs to be written as c:\\home\user\\work.
 *  Therefore this function will expand '\\' to '\\\\' so when written it
 *  again becomes '\\'.  This only needs to be run if generating a javascript file.
 *  If generating a bash or bat file, this does not need to occur.
 *
 *  @param s      - input String
 */
function esc(s)
{
    if (system.getOS() == 'win') return s.replace(/\\/g,'\\\\');
    else return s;
}

/*
 *  ======== quoted ========
 *  Surround a string with double quotes
 *
 *  @param s      - input String
 */
function quoted(s)
{
    return '"'+s+'"';
}

/*
 *  ======== capitalizeFirst ========
 *  Capitalize the first letter of a string
 *
 *  @param s      - input String
 */
function capitalizeFirst (s)
{
    return s.charAt(0).toUpperCase() + s.slice(1);
}

/*
 *  ======== autoForceModules ========
 *  Returns an implementation of a module's modules method that just
 *  forces the addition of the specified modules
 *
 *  @param kwargs An array of module name strings.
 *
 *  @return An array with module instance objects
 *
 *  Example:
 *     modules: Common.autoForceModules(["modA", "modB"])
 */
function autoForceModules(kwargs)
{
    return (function(){

        let modArray = [];

        if (kwargs == undefined || kwargs == null || !Array.isArray(kwargs)) {
            console.log("autoForceModules('kwargs'): 'kwargs' invalid!");
            return (modArray);
        }

        for (let args = kwargs.length - 1; args >= 0; args--) {
            let modPath = kwargs[args];
            if (modPath.indexOf('/') == -1) {
                modPath = "/ti/security/" + modPath;
            }
            modArray.push({
                name      : modPath.substring(modPath.lastIndexOf('/') + 1),
                moduleName: modPath,
                hidden    : true
            });
        }

        return modArray;
    });
}

/*
 *  ======== productPath ========
 *  Returns the path to the installation of this product.
 *  @return A string
 */
function productPath(subdir)
{
    const path  = system.utils.path;
    const prods = system.getProducts();
    const prod  = (prods.length == 1) ? prods[0] :
                   prods.find(prod => prod.name == 'SecuritySDK');

    if (prod === undefined) return 'Not Found';

    let result = path.dirname(prod.path); // remove the product.json file
    if (path.basename(result).startsWith('.meta')) result = path.dirname(result);
    return path.normalize(subdir ? result + path.sep + subdir : result);
}

function getNodePath()
{
    return system.getNodePath();
}

function findInstance(modName, instName)
{
    const module    = system.modules[modName];
    const instances = (module && module.$instances) || [];
    return instances.find((inst) => inst.$name == instName);
}

function getConfigFromStaticModule(modName, configName, cpuName){
    let ret = {
        available: false,
        value: "",
        module: ""
    }

    const context = system.contexts[cpuName];
    if (!context)   return ret;
    const mod = context.system.modules[modName];
    if(mod){
        ret.module = mod
        ret.value = mod.$static[configName]
        ret.available = true
    }
    return ret;
}

function modStatic(modName) {
    const mod = system.modules[modName];
    return mod ? mod.$static : mod;
}

function modStaticByCPU(modName, cpuName)
{
    const context = system.contexts[cpuName];
    if (!context)   return [];
    const mod = context.system.modules[modName];
    return mod ? mod.$static : mod;
}

function modInstances(modName) {
    const mod = system.modules[modName];
    if (!mod)            return [];
    if (!mod.$instances) return [];
    return mod.$instances;
}

function modInstancesByCPU(modName, cpuName)
{
    const context = system.contexts[cpuName];
    if (!context)   return [];
    const modules = context.system.modules;
    if (!modules)   return [];
    let mod = modules[modName];
    if (!mod || !mod.$instances)    return [];

    return mod.$instances;
}

function modInstNames(x) {
    return (system.modules[x] && system.modules[x].$instances || []).map(x=>{return {name:x.$name};});
}

function findDefault(modName, opts = {isArray : false, createNew : false})
{
    if (!modName.includes('/ti/security/')) modName = '/ti/security/' + modName;

    // If some exist, return the first one
    if (system.modules[modName]?.$instances)
        return system.modules[modName].$instances[0];

    // If none exist and null is not an option, then create a new one and return it
    if (opts.createNew)
        return scripting.addModule(modName).addInstance();

    // Otherwise return no default
    else return opts.isArray ? [] : null;
}

/*
 *  ======== isCName ========
 *  Determine if specified id is either empty or a valid C identifier
 *
 *  @param id  - String that may/may not be a valid C identifier
 *
 *  @returns true if id is a valid C identifier OR is the empty
 *           string; otherwise false.
 */
function isCName(id)
{
    if ((id != null && id.match(/^[a-zA-Z_][0-9a-zA-Z_]*$/) != null)
            || id == '') { /* '' is a special value that means "default" */
        return true;
    }
    return false;
}

/*
 *  ======== validateNames ========
 *  Validate that all names defined by inst are globally unique and
 *  valid C identifiers.
 */
function validateNames(inst, vo)
{
    let myNames = {}; /* all C identifiers defined by inst) */

    /* check that $name is a C identifier */
    if (inst.$name != "") {
        let token = inst.$name;
        if (!isCName(token)) {
            vo.logError("'" + token + "' is not a valid a C identifier", inst, "$name");
        }
        myNames[token] = 1;
    }

    /* check that cAliases are all C identifiers and there are no dups */
    let tokens = [];
    if ("cAliases" in inst && inst.cAliases != "") {
        tokens = inst.cAliases.split(/[,;\s]+/);
    }

    for (let i = 0; i < tokens.length; i++) {
        let token = tokens[i];
        if (!isCName(token)) {
            vo.logError("'" + token + "' is not a valid a C identifier", inst, "cAliases");
        }
        if (myNames[token] != null) {
            vo.logError("'" + token + "' is defined twice", inst, "cAliases");
        }
        myNames[token] = 1;
    }

    /* ensure all inst C identifiers are globally unique */
    let mods = system.modules;
    for (let i in mods) {
        /* for all instances in all modules in /ti/drivers ... */
        let instances = mods[i].$instances;
        for (let j = 0; j < instances.length; j++) {
            let other = instances[j];

            /* skip self */
            if (inst.$name == other.$name) {
                continue;
            }

            /* compute all other names */
            let name = other.$name;
            if (name != "" && name in myNames) {
                vo.logError("multiple instances with the same name: '"
                         + name + "': " + inst.$name + " and " + other.$name,
                    inst, "cAliases");
                break;
            }
            if (other.cAliases != null && other.cAliases != "") {
                let tokens = other.cAliases.split(/[,;\s]+/);
                for (let k = 0; k < tokens.length; k++) {
                    name = tokens[k];
                    if (name != "" && name in myNames) {
                        vo.logError(
                            "multiple instances with the same name: '" + name
                                 + "': " + inst.$name + " and " + other.$name,
                            inst, "cAliases");
                        break;
                    }
                }
            }
        }
    }
}

// .bss .sysmem .stack .text .rodata .data .comm .const


function nameResolve(inst, fields)
{
    const nameFind = name => _.chain      (system.modules)
                              .map        (mod => [mod.$instances])
                              .flattenDeep()
                              .find       (inst => inst.$name == name)
                              .value      ();

    if (typeof(fields) === 'string') {
        return nameFind(inst[fields]);
    }
    else {
        fields.every(field => inst = nameFind(inst[field]));
        return inst;
    }
}

function isContextCPU1()
{
    if (system.context == CONTEXT_CPU1 || system.context == CONTEXT_SYSTEM)
    {
        return true;
    }
    return false
}

function isContextCPU2()
{
    if (system.context == CONTEXT_CPU2)
    {
        return true;
    }
    return false
}

function isContextCPU3()
{
    if (system.context == CONTEXT_CPU3)
    {
        return true;
    }
    return false
}

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
    var access = ""
    access +=  modInstances('/ti/security/Link').
                    filter(x => getStack(x) && getStack(x).stackAPR == apr.memRegion).
                    map(x=>{return "SSU_LINK_RW_ACCESS(" + x.$name + ") | "}).
                    join("");
    access +=  modInstances('/ti/security/Link').
                    filter(x => x.readwriteAPRs.includes(apr.name) ||  x.readwriteAPRsEasy.includes(apr.name)).
                    map(x=>{return "SSU_LINK_RW_ACCESS(" + x.$name + ") | "}).
                    join("");
    access +=  modInstances('/ti/security/Link').
                    filter(x => x.readAPRs.includes(apr.name) || x.readAPRsEasy.includes(apr.name)).
                    map(x=>{return "SSU_LINK_RD_ACCESS(" + x.$name + ") | "}).
                    join("");

    if(sysSec){
        if(sysSec.addCommonCodeModule){
            if(apr.name == "LINK2_codeAPR_Flash")
            {
                access += "SSU_LINK_RD_ACCESS(CommonCodeModule_Link) | "
            }
            if(apr.name == "LINK2_codeAPR_RAM")
            {
                access += "SSU_LINK_RW_ACCESS(CommonCodeModule_Link) | "
            }
        }
    }

    return access + '0U'
}

function getStack(link)
{
    return (modInstances('/ti/security/Stack').
                    filter(x => x.links.includes(link) || x.linksEasy.includes(link.$name))
                    [0])
}

function getZone(stack)
{
    return stack.zone
}

function getAPRListSorted()
{
    let aprs = modInstances('/ti/security/APR')
    return aprs.filter(a => a.useExtAP).concat(aprs.filter(a => !a.useExtAP))   //!! Limited ExtAP Count
}

function toHex(val, digits)
{
    return val.toString(16).padStart(digits, '0').toUpperCase()
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

function findAPRbyName(aprName) // Assuming APRs have unique names across contexts
{
    let ret = [];
    let aprs = allocateAllMemoryRegions()
    Object.keys(aprs).forEach(core => {
        let match = aprs[core].filter(a => {return a.name == aprName})
        .forEach(apr => {ret.push(apr)})
    })
    return ret;
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

function getPeripheralAPRsAll(){
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

function updateFlashUsageProtection(flMem, weprotVal, flx){
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

function getWeprotRange(flUnit){
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

function getSECGROUP(apr)
{
    var secGroup = " : "

    var exeLink = getExeLink(apr)
    if(exeLink) {
        var stack        = getStack(exeLink)
        var secGroupName = stack ? stack.$name : "STACK2_STACK"
        var secGroupAttr = stack ? stack.secGroupAttr : "NONE"

        if(exeLink.easyModeGenerated && exeLink.$ownedBy.isCommonCode) {
            secGroupName += "_COMMONCODE"
            secGroupAttr = exeLink.$ownedBy.secGroupAttr
        }
        if(secGroupAttr == "NONE")
            secGroup = " : SECURE_GROUP(" + secGroupName + ")"
        else
            secGroup = " : SECURE_GROUP(" + secGroupName + ", " + secGroupAttr + ")"
    }
    return secGroup
}

function inputSectionFormat(userSection)
{
    //console.log(userSection)
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
        ret += sps + "ALIGN(" +  (section.sectionAlign).toString() + ")\n"
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
    if(apr.memType == "LoadRun")                                                    //!! do tag check instead or add extra attribute for this
        return "LOAD=APR_FLASHLOAD, RUN="  + memName(apr) + ", TABLE(copyTable)"
    else if (apr.name == "LINK2_codeAPR_RAM"){
        let loadAPR = "APR_FLASHLOAD_" + system.context.toUpperCase()
        let bankmode = getBankModeConfig();
        if(isContextCPU1() || (isContextCPU3() && bankmode > 1))
            loadAPR = "LINK2_CODEAPR_FLASH"
        return `LOAD = ${loadAPR}, RUN=LINK2_CODEAPR_RAM, table(BINIT)`
    }
    else if (apr.name == "CommonCodeModule_codeAPR_RAM"){
        let loadAPR = "APR_FLASHLOAD_" + system.context.toUpperCase()
        let bankmode = getBankModeConfig();
        if(isContextCPU1() || (isContextCPU3() && bankmode > 1))
            loadAPR = "COMMONCODEMODULE_CODEAPR_FLASH"
        return `LOAD = ${loadAPR}, RUN=COMMONCODEMODULE_CODEAPR_RAM, table(BINIT)`
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

    if(sysSecPresent && apr.type == "Code") {
        secGroup = getSECGROUP(apr)
    }

    ret = "    " + section.$name + secGroup + " {\n"

    if(section.addInputSections){
        inputSections = ""
        for(let i=0; i<section.inputSection.length; i++){
            let x = section.inputSection[i]
            inputSections += "        " + inputSectionFormat(x) + "\n"
        }
        ret += inputSections
    }

    ret += "    }     " + where(apr) + "\n"

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

function sectionListModule(easyModeModule, APRList, cpu)
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

    if(x.codeAPR_Flash)
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

        if(inputSections != "")
        {
            let reqdApr = APRList.find(o => {return o.name == x.codeAPR_Flash.$name})
            sections += "    ." + x.codeAPR_Flash.$name + getSECGROUP(reqdApr) + " {\n"
            sections += inputSections
            sections += "    }     " + where(reqdApr) + ", palign(8)  \n\n"
        }
    }

    if(x.codeAPR_RAM)
    {
        var inputSections = ""

        if(x.isLink2){
            inputSections += "        " + "*(.TI.ramfunc.link2)\n"
            getList(x.link2DefaultAllSections).forEach(f => {
                inputSections += "        " + f + "(.TI.ramfunc)\n"
            })
        }
        fileList.forEach( f => {
            if(x.textInRAM)
                inputSections += "        " + f + ".o(.text .TI.ramfunc)\n"
            else
                inputSections += "        " + f + ".o(.TI.ramfunc)\n"
        })
        libList.forEach( f => {
            let specifier = isSectionIncluded(f) ? "" : "<*>"
            if(x.textInRAM)
                inputSections += "        " + f + specifier +"(.text .TI.ramfunc)\n"
            else
                inputSections += "        " + f + specifier +"(.TI.ramfunc)\n"
        })
        customListCodeRAM.forEach( f => {
            inputSections += "        " + f + "\n"
        })

        if(inputSections != "") {
            let reqdApr = APRList.find(o => {return o.name == x.codeAPR_RAM.$name})
            sections += "    ." + x.codeAPR_RAM.$name + getSECGROUP(reqdApr) + " {\n"
            sections += inputSections
            sections += "    }     " + where(reqdApr) + "\n\n"
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
            sections += "    }     " + where(reqdApr) + "\n\n"
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
            sections += "    }     " + where(reqdApr) + ", palign(8) \n\n"
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
            sections += "    }     " + where(reqdApr) + "\n\n"
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

function sectionListSharedMem(sharedMem, APRList, cpu)
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
        sections += "    }     " + where(apr) + "\n\n"
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
            sections += "    }     " + where(apr) + ", palign(8) \n\n"
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
        let reqdAPR = APRList.find(o => {return o.name == "LINK2_codeAPR_Flash"}) //!! tag
        if(reqdAPR)
            sections += `    codestart : > 0x${reqdAPR.startAddr.toString(16)}, palign(8)  \n`
        let certSection = `    cert      : {} > CERT, palign(8) \n`
        sections += certSection
    }
    else{
        let reqdAPR = APRList.find(o => {return o.name == "LINK2_codeAPR_Flash"}) //!! tag
        if(reqdAPR){
            sections += `    resetvector  : > 0x${reqdAPR.startAddr.toString(16)}, palign(8)  \n`
            sections += `    nmivector    : > 0x${(reqdAPR.startAddr + 0x40).toString(16)}, palign(8)  \n`
            sections += `    codestart    : > ${reqdAPR.name.toUpperCase()}, palign(8)  \n`
        }
        else{
            reqdAPR = APRList.find(o => {return o.name == "LINK2_codeAPR_RAM"}) //!! tag
            if(reqdAPR){
                sections += `    resetvector  : > 0x${reqdAPR.startAddr.toString(16)}  \n`
                sections += `    nmivector    : > 0x${(reqdAPR.startAddr + 0x40).toString(16)}, palign(8)  \n`
                sections += `    codestart    : > ${reqdAPR.name.toUpperCase()}  \n`
            }
        }
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
        sections += `    .cinit       : > APR_FLASHLOAD_${system.context}, palign(8)  // Tables for explicitly initialized global and static variables.\n`
        sections += `    .binit       : > APR_FLASHLOAD_${system.context}, palign(8)  // Boot time copy tables\n`
        sections += `    .ovly        : > APR_FLASHLOAD_${system.context}, palign(8)  // Copy tables other than boot time (.binit) copy tables.\n`
        sections += `    .sysmem      : > LINK2_DATAAPR_RW,   palign(8)  // Sysmem\n\n`
    }

    // Get the stack sections
    modInstances('/ti/security/Stack').forEach(stack => {
        var sectName = ".stack_" + stack.$name + ' '.repeat(Math.max(0,15 - stack.$name.length))
        var stackSize = stack.size
        if(stack.$name == "STACK2_STACK") {
            let stack2Apr = APRList.find(o => {return o.name == "STACK2_stackmem_apr"}) //!! tag
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

    // Get section  corresponding to Easy Mode Link
    let commonCodeSections = ""
    modInstances('/ti/security/EasyMode_link').forEach(x => {
        if(x.isCommonCode)
            commonCodeSections += sectionListModule(x, APRList, cpu)
        else
            sections += sectionListModule(x, APRList, cpu)
    })
    sections += commonCodeSections                                  //!! Always placing common code sections at the end

    // Get section  corresponding to Easy Mode SharedMem
    modInstances('/ti/security/EasyMode_sharedMem').forEach(x => {
        sections += sectionListSharedMem(x, APRList, cpu)
    })

    // Get sections for manually created Sections
    modInstances('/ti/security/OutputSection').forEach(section => {
        sections += sectionListManual(section, APRList)
    })

    return sections
}

function getSectionsMinimal(cpu){
    let sections = ""
    let APRList = allocateAllMemoryRegions()[cpu].filter(apr=> apr.type != "Peripheral")
    let sectionsList = modInstancesByCPU('/ti/security/OutputSection', cpu)

    let firstCode = APRList.filter(apr => {return apr.type == "Code"})
                            .sort((a,b) => {return a.startAddr - b.startAddr})[0]   //!! check what to put
    let codeStartSection = ""
    if(firstCode){
        codeStartSection = `    codestart : > 0x${firstCode.startAddr.toString(16)} \n`
    }
    let a = sectionsList.filter(sec => sec.$name == "codestart")[0]
    if(a){
        let codestartApr = APRList.filter(apr => apr.name == a.sectionMemory)[0]
        if(codestartApr)
            codeStartSection = `    codestart : > 0x${codestartApr.startAddr.toString(16)} \n`
    }

    sections += codeStartSection

    let flashAprList = allocateAllMemoryRegions()[cpu].filter(apr=> apr.memType == "Flash")
    if(cpu == "CPU1" && flashAprList.length){
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

function getMemoryList(cpu)
{
    let aprsAll = allocateAllMemoryRegions()
    let APRList = aprsAll[cpu].filter(apr=> apr.type != "Peripheral" && !apr.name.startsWith("FLASHCOVER_"))
                                                    .sort((a,b) => {return a.startAddr - b.startAddr})

    //if(!APRList)
    let APRnameList = APRList.map(apr=>{return apr.name})
    let maxLen = APRnameList.sort((a,b)=>{return b.length-a.length})[0].length

    var list = ""

    list += "    // RAM MEMORY\n\n"
    //console.log(APRList)
    APRList.filter(apr => {return apr.memType == "RAM"})
    .forEach(item => {
        let size = item.endAddr - item.startAddr
        if(item.name.startsWith("APR_Boot_")) //!! tag
            return;
        var spaces = ' '.repeat(maxLen - item.name.length)
        list += "    " + memName(item) + spaces + " : origin = 0x" + toHex(item.startAddr, 8) + ", length = 0x" + toHex(size, 8) + "\n"
    })

    list += "\n    // FLASH MEMORY\n\n"
    /* if(!isContextCPU1()){
        let flashLoadApr = aprsAll[system.context].find(o => {return o.name == ("APR_FlashLoad_"+system.context)})
        if(flashLoadApr){
            let size = flashLoadApr.endAddr - flashLoadApr.startAddr
            let spaces = ' '.repeat(maxLen - flashLoadApr.name.length)
            list += "    " + memName(flashLoadApr) + spaces + " : origin = 0x" + toHex(flashLoadApr.startAddr, 8) + ", length = 0x" + toHex(size, 8) + "\n"
        }
    } */
    APRList.filter(apr => {return apr.memType == "Flash"})
    .forEach(item => {
        //if(item.name.includes("APR_FlashLoad_") && item.name != "APR_FlashLoad_CPU1") return;
        let size = item.endAddr - item.startAddr
        let spaces = ' '.repeat(maxLen - item.name.length)
        if(item.name == "APR_RESERVED_sign_CPU1"){              //!! tag
            spaces = ' '.repeat(maxLen - 4)
            list += "    " + "CERT" + spaces + " : origin = 0x" + toHex(item.startAddr, 8) + ", length = 0x" + toHex(size, 8) + "\n"
        }
        else
            list += "    " + memName(item) + spaces + " : origin = 0x" + toHex(item.startAddr, 8) + ", length = 0x" + toHex(size, 8) + "\n"
     })

    return list
}

/* function getFlashGaps(flashAprList){
    let ret = [];
    for(let i=1; i<flashAprList.length; i++){
        if(flashAprList[i].aprEntry.start != flashAprList[i-1].aprEntry.end)
            ret.push({
                start: flashAprList[i-1].aprEntry.end,
                size: (flashAprList[i].aprEntry.start - flashAprList[i-1].aprEntry.end)
            })
    }
    return ret;
} */

function assignLinkID()
{
    var linkID = []
    var id = 3
    modInstances('/ti/security/Link').forEach(x => {
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
    var stackID = []
    var id = 3
    modInstances('/ti/security/Stack').forEach(x => {
        if(x.$name == "STACK2_STACK") //!! tags
            stackID[x.$name] = 2
        else if(x.$name == "STACK1_STACK")
            stackID[x.$name] = 1
        else
            stackID[x.$name] = id++
    })
    return stackID
}

function getAprWeprotVal(aprName, aprType, cpuId){
    let aprNameList = [];
    let ssMain = modStaticByCPU("/ti/security/System_Security", "CPU1")
    let ssCur = modStaticByCPU("/ti/security/System_Security", ("CPU"+String(cpuId)))
    if(ssMain && ssCur){
        ssCur.WEPROT_APRs.forEach(x => {aprNameList.push(x)})
        if(aprNameList.includes(aprName)) return 1
        if(aprType == "Code" && ssMain.WEPROT_CODE_BANKS) return 1
        if(aprType == "Data" && ssMain.WEPROT_DATA_BANKS) return 1
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
    const cpu1check    = isContextCPU1()
    const retDefault = {a: 0x0, b: 0x0}

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

function getSeccfgLocationDummy(cpuName){
    if(cpuName == "CPU1") return 0x200FC000;
    if(cpuName == "CPU2") return 0x200FC800;
    if(cpuName == "CPU3") return 0x200FD000;
    if(cpuName == "CPU4") return 0x200FD800;
}

function getCoreList(lockstepFilter = 0){
    let coreList = _.map(cpuData.cpuList, (cpuItem) => {
        return {name: cpuItem.name}
    })

    // Check for LockStep
    if(lockstepFilter != 0){
        let lsConfig = getConfigFromStaticModule("/driverlib/sysctl.js", "LSConfig", CONTEXT_CPU1)
        if(!lsConfig.available || (lsConfig.available && lsConfig.value == "LockStep")){
            coreList = coreList.filter((cpuItem) => {
                return cpuItem.name != "CPU2"
            })
        }
    }

    return coreList
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
                                    [(reg) => {
                                        if(reg.isShared) return reg.sharedCores.length;
                                        return 0;
                                    },
                                     (reg) => { return -reg.zeroWS},
                                     (reg) => { return -reg.memSize},
                                     (reg) => {                             // Code then data
                                        if(reg.type == "Code") return 0;
                                        return 1;
                                    }])

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
                implicitRegion: false
            })

            if(isShared){
                memRegion.share.forEach(core => {
                    let flag = checkRamRegionOverlap(finalAllocations[core], result.allottedRamUnits[0].start, result.allottedRamUnits[result.num_reqd - 1].end)
                    if(flag){
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
            ret[idx] = {startAddr: 0, endAddr: 0, ramCoverRegion: true, name: srcCore+"_RamCoverRegion"+String(idx), type: null, memType: "RAM", implicitRegion: true};
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
            ret[idx] = {startAddr: 0, endAddr: 0, ramCoverRegion: true, name: srcCore+"_RamCoverRegion"+String(idx), type: null, memType: "RAM", implicitRegion: true};
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
      /* {tag: "link2_flash_code", core: "CPU1", finalCore: "CPU1"},
        {tag: "link2_flash_code", core: "CPU2", finalCore: "CPU2"},
        {tag: "link2_flash_code", core: "CPU3", finalCore: "CPU3"},
        {tag: "flash_load_CPU1", core: "CPU1", finalCore: "CPU1"},
        {tag: "flash_load_CPU2", core: "CPU2", finalCore: "CPU2"},
        {tag: "flash_load_CPU3", core: "CPU3", finalCore: "CPU3"}, */
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
                    implicitRegion: false
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
                    implicitRegion: false
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
        implicitRegion  : isShared
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
            ret[idx] = {peripheralList: [], startAddr: 0, endAddr: 0, autoPeriphRegion: true, name: "PeriphAutoRegion"+String(idx), type: "Peripheral", memType: null, implicitRegion: true};
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
            ret[idx] = {peripheralList: [], startAddr: 0, endAddr: 0, autoPeriphRegion: true, name: "PeriphAutoRegion"+String(idx), type: "Peripheral", memType: null, implicitRegion: true};
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

function getFlashRegion(core){
    let regions = allocateAllMemoryRegions()[core]
    if(!regions) return {origin: 0, length: 0}
    let sortedFlashRegions = regions.filter(a => a.memType == "Flash").sort((a,b) => a.startAddr - b.startAddr)
    if(!sortedFlashRegions || !sortedFlashRegions[0]) return {origin: 0, length: 0}
    let length = 0;
    sortedFlashRegions.forEach(a => length += a.size)
    return {
        origin: sortedFlashRegions[0].startAddr,
        length: length
    }
}

function getBootPeripherals(inst){
    if(system.context != CONTEXT_CPU1) return [];
    if(!inst) return [];

    let bootModes = new Set(), periphsNeeded = new Set()
    let bootPinCount = inst.bootPinCount
    for(let i=0; i<Math.pow(2,bootPinCount); i++){
        bootModes.add(inst["BOOTDEF" + String(i)])
    }

    bootModes.forEach(bootMode => {
        ssuData["link1BootPeripherals"][bootMode].forEach(p => periphsNeeded.add(p))
    })

    let retArray = Array.from(periphsNeeded)
    return retArray
}