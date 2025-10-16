let CONTEXT_CPU1 = "CPU1";
let CONTEXT_CPU2 = "CPU2";
let CONTEXT_CPU3 = "CPU3";
let CONTEXT_SYSTEM = "system"
// let Collateral = system.getScript("/driverlib/sysconfig_collateral_links.js");
let json_import = system.getScript(`/driverlib/.meta/gpn/F29.json`);

exports = {
    getBoard : getBoard,
    getBoardName : getBoardName,
    getDeviceTRM: getDeviceTRM,
    getDeviceDatasheet: getDeviceDatasheet,
    findDuplicates : findDuplicates,
    peripheralCount: peripheralCount,
    typeMatches: typeMatches,
    peripheralNames: peripheralNames,
    stringOrEmpty: stringOrEmpty,
    removeNonNumber : removeNonNumber,
    gpioNameToNumber : gpioNameToNumber,
    printDebugObject : printDebugObject,
    printDebugObjectKeys : printDebugObjectKeys,
    getGPIOs : getGPIOs,
    getAIOs : getAIOs,
    peripheralListFromSysCtl : peripheralListFromSysCtl,
    getDeviceName: getDeviceName,
    getVariant: getVariant,
    is_instance_not_in_variant: is_instance_not_in_variant,
    countinstances: countinstances,
    getDevicePart: getDevicePart,
    getDevicePackage: getDevicePackage,
	getSDK: getSDK,
	onlyPinmux: onlyPinmux,
	CLB_isType1 : CLB_isType1,
	CLB_isType1_Type2 : CLB_isType1_Type2,
	CLB_isType2 : CLB_isType2,
    autoForce : autoForce,
    autoForceMultiple : autoForceMultiple,
    SYSCLK_getMaxMHz : SYSCLK_getMaxMHz,
	getConfigNameRecursive: getConfigNameRecursive,
    getConfigsRecursive: getConfigsRecursive,
    printConfigsInfo : printConfigsInfo,
    getCollateralFindabilityList : getCollateralFindabilityList,
    getSysCfgCoreNames : getSysCfgCoreNames,
    getSelfSysCfgCoreName : getSelfSysCfgCoreName,
	zero_to_15        : [
        { name: 0 },
        { name: 1 },
        { name: 2 },
        { name: 3 },
        { name: 4 },
        { name: 5 },
        { name: 6 },
        { name: 7 },
        { name: 8 },
        { name: 9 },
        { name: 10 },
        { name: 11 },
        { name: 12 },
        { name: 13 },
        { name: 14 },
        { name: 15 },
	],
	zero_to_16        : [
        { name: 0 },
        { name: 1 },
        { name: 2 },
        { name: 3 },
        { name: 4 },
        { name: 5 },
        { name: 6 },
        { name: 7 },
        { name: 8 },
        { name: 9 },
        { name: 10 },
        { name: 11 },
        { name: 12 },
        { name: 13 },
        { name: 14 },
        { name: 15 },
        { name: 16 },
	],

    CONTEXT_CPU1: CONTEXT_CPU1,
    CONTEXT_CPU2: CONTEXT_CPU2,
    CONTEXT_CPU3: CONTEXT_CPU3,
    isContextCPU1: isContextCPU1,
    isContextCPU2: isContextCPU2,
    isContextCPU3: isContextCPU3,
    isMultiCoreSysConfig : isMultiCoreSysConfig,
    isMultiCoreDevice : isMultiCoreDevice,
    getModuleForCore : getModuleForCore,
    getContextNames: getContextNames,
    getAllModulesForCore: getAllModulesForCore,
    getModulePaths, getModulePaths,
    getContextDisplayName: getContextDisplayName,
    getOtherContextNames: getOtherContextNames,
    isModuleOnThisContext: isModuleOnThisContext,
    isModuleOnAnyContext: isModuleOnAnyContext,
    isModuleOnOtherContext: isModuleOnOtherContext,
    getModuleForTheFirstAvailableCore : getModuleForTheFirstAvailableCore,
    removeArrayFromArray : removeArrayFromArray,
    getSYSCLK: getSYSCLK,
    getClockTree : getClockTree,
    getC2000WarePath: getC2000WarePath,
    modInstances : modInstances,
    isAllocationSetupMode: isAllocationSetupMode,
    isAllocationConfigureMode : isAllocationConfigureMode,
    isAllocationOff: isAllocationOff,
    filterConfigurationList: filterConfigurationList,
    filterConfigsIfInSetupMode: filterConfigsIfInSetupMode
};

function modInstances(modName) {
    const mod = system.modules[modName];
    if (!mod)            return [];
    if (!mod.$instances) return [];
    return mod.$instances;
}

function getSYSCLK(cpu)
{
    var clockTree = getClockTree();
    if (clockTree){

        if (isMultiCoreDevice() || isAllocationSetupMode())
        {
            if (!cpu)
            {
                if (isContextCPU1())
                {
                    cpu = "1"
                    return clockTree["CPU" + cpu + "_CPUCLK"].in
                }
                else if (isContextCPU2())
                {
                    cpu = "2"
                    return clockTree["CPU" + cpu + "_CPUCLK"].in
                }
                else
                {
                    cpu = "3"
                    return clockTree["CPU" + cpu + "_CPUCLK"].in
                }
            }
        }
        else
        {
            return clockTree["CPUCLK"].in
        }
    }
    else
    {
        return SYSCLK_getMaxMHz()
    }
}

function getC2000WarePath()
{
    var currnetSDKProductPath = system.getProducts()[0].path
    var sdkPath = system.utils.path.join(currnetSDKProductPath + "../../../")
    sdkPath = sdkPath.replace(new RegExp('\\' + system.utils.path.sep, 'g'), '/')
    if (system.getProducts()[0].name != "C2000WARE")
    {
        sdkPath = sdkPath + "c2000ware/"
    }

    return sdkPath
}

function removeArrayFromArray(arrSource, arrRem)
{
    return arrSource.filter( function( el ) {
      return !arrRem.includes( el );
    } );
}


function getContextDisplayName(cntxName)
{
    return (cntxName == CONTEXT_SYSTEM? CONTEXT_CPU1: cntxName)
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

function getOtherContextNames()
{
    var contextNames = Object.keys(system.contexts)
    return contextNames.filter(e => e !== system.context);
}

function isModuleOnThisContext(moduleName)
{
    return system.modules[moduleName]?true:false;
}

function isModuleOnAnyContext(moduleName)
{
    var cntxs = getContextNames();
    for (var cntx of cntxs){
        if (getModuleForCore(moduleName, cntx)){
            return true;
        }
    }
    return false;
}

function isModuleOnOtherContext(moduleName)
{
    var cntxs = getOtherContextNames();
    for (var cntx of cntxs){
        if (getModuleForCore(moduleName, cntx)){
            return true;
        }
    }
    return false;
}

function getContextNames()
{
    var contextNames = Object.keys(system.contexts)
    return contextNames;
}

//
// Returns true only when the multi-core is laucnhed in sysconfig
// If a multi-core device is launched in signle view it wont return true.
//
function isMultiCoreSysConfig()
{
    return (getContextNames().length > 1);
}

function isMultiCoreDevice()
{
    return (system.context.includes("CPU"));
}

function getAllModulesForCore(coreName)
{
    let context = system.contexts[coreName];
    let modules = context ? context.system.modules : {};

    return modules;
}

//
// Handles getting clocktree for multi-core this for multi-core
//
function getClockTree()
{
    var contextNames = getContextNames();
    var mainContext = "system"
    if (contextNames.includes("CPU1"))
    {
        mainContext = "CPU1"
    }
    let context = system.contexts[mainContext];
    let clocktree = context && context.system ? context.system.clockTree : null;

    if (system.deviceData.clockTree)
    {
        return clocktree
    }
    else
    {
        return null
    }
}

function getModuleForCore(moduleName, coreName)
{
    let context = system.contexts[coreName];
    let modules = context ? context.system.modules : {};
    let module = modules[moduleName];

    return module;
}

function getModuleForTheFirstAvailableCore(moduleName)
{
    var cntxs = getContextNames();
    for (var cntx of cntxs){
        var mod = getModuleForCore(moduleName, cntx)
        if (mod){
            return mod;
        }
    }
    return null;
}

function getModulePaths(modules)
{
    return Object.keys(modules).sort();;
}

function getBoard()
{
    return system.deviceData.board;
}


function getBoardName()
{
    if (system.deviceData.board)
    {
        return system.deviceData.board.name;
    }
    return null;
}


function getConfigNameRecursive(arrayConfigs)
{
    var configNames = [];
    for (var modConfig of arrayConfigs)
    {
        if (modConfig.config)
        {
            configNames = configNames.concat(getConfigNameRecursive(modConfig.config))
        }
        else
        {
            var modConfigName = modConfig.name;
            configNames.push(modConfigName);
        }
    }
    return configNames;
}

function getConfigsRecursive(arrayConfigs)
{
    var configNames = [];
    for (var modConfig of arrayConfigs)
    {
        if (modConfig.config)
        {
            configNames = configNames.concat(getConfigsRecursive(modConfig.config))
        }
        else
        {
            var modConfigName = modConfig;
            configNames.push(modConfigName);
        }
    }
    return configNames;
}

function printConfigsInfo(configByName)
{
    // for (const key in configByName) {
    //     console.log(key);
    //     console.log(configByName[key].name)
    //     console.log(configByName[key].displayName)
    //     console.log(configByName[key].default)
    //     console.log(configByName[key].options)
    // }
    console.log(JSON.stringify(configByName, null, 4));
}


function autoForceMultiple(module_names_paths)
{
    return (function (){
        return module_names_paths
    })

}

function autoForce(module_name, module_path)
{
    return (function (){
        return [{
            name      : module_name,
            moduleName: module_path,
            hidden    : false
        }]
    })

}

function findDuplicates(arrayToCheck)
{
    const count = arrayToCheck =>
      arrayToCheck.reduce((a, b) => ({ ...a,
        [b]: (a[b] || 0) + 1
      }), {})

    const duplicates = dict =>
      Object.keys(dict).filter((a) => dict[a] > 1)

    return {count: count(arrayToCheck), duplicates: duplicates(count(arrayToCheck))};
}

function onlyPinmux()
{
	return false;
}

function getSDK()
{
	var sdk = system.getScript("/.metadata/sdk.json");

    return sdk;
}

function getDeviceName()
{
	var deviceName = system.deviceData.device;
	return deviceName
}

function getVariant()
{
    let variant = system.deviceData.gpnVariant;
    return variant
}

function normalizeVariant(variant) {
    // Remove TMS320 prefix and Q1 suffix
    let v = variant.replace(/^TMS320/, '');
    return v;
}
function is_instance_not_in_variant(element) {
    let variant = normalizeVariant(getVariant());
    if (!json_import || !json_import[variant]) {
        return false;
    }
    let supportTable = json_import[variant];
    return (supportTable && element in supportTable && supportTable[element] == false);
}

function getDevicePart()
{
    var devicePart = system.deviceData.part;
    return devicePart
}

function getDevicePackage()
{
    var devicePackage = system.deviceData.package;
    return devicePackage
}

function stringOrEmpty(stringToCheck, stringToAdd)
{
    if (stringToCheck != "")
    {
        return stringToAdd;
    }
    return "";
}

function printDebugObject(obj)
{
	if (obj == null)
	{
		console.log("Object is null");
		return;
	}
    var keys = Object.keys(obj);
    for (var key in keys)
	{
    	console.log(keys[key] + " : " + obj[keys[key]]);
    }
}

function printDebugObjectKeys(obj)
{
    if (obj == null)
    {
        console.log("Object is null");
        return;
    }
    var keys = Object.keys(obj);
    console.log("Keys:")
    for (var key in keys)
    {
        console.log(keys[key]);
    }
}

function removeNonNumber(stringToCheck)
{
	var numberOnly = "";
    if (stringToCheck != "")
    {
    	for (var i = 0; i < stringToCheck.length; i++)
    	{
    		if ("0123456789".includes(stringToCheck[i]))
    		{
    			numberOnly += stringToCheck[i];
    		}
    	}
        return numberOnly;
    }
    return "";
}

//As soon a number is detected and then more characters are detected, exit.
//Good for usecases like GPIO180_X2, the 2 is not added to the numbers
function gpioNameToNumber(stringToCheck)
{
	var numberOnly = "";
	var numbersDetected = false;
    if (stringToCheck != "")
    {
    	for (var i = 0; i < stringToCheck.length; i++)
    	{
    		if ("0123456789".includes(stringToCheck[i]))
    		{
    			numberOnly += stringToCheck[i];
    			numbersDetected = true;
    		}
    		else
    		{
    			if (numbersDetected)
        		{
        			return numberOnly;
        		}
    		}
    	}
        return numberOnly;
    }
    return "";
}

function getGPIOs()
{
	var allGpioNames = [];
	let gpio = system.deviceData.interfaces.GPIO;
	if (gpio != null)
	{
		for (var i = 0; i < gpio.peripherals.length; i++)
		{
			var gpioperiph = gpio.peripherals[i];
			allGpioNames.push(gpioperiph.name);
		}
	}
	return allGpioNames
}

function getAIOs()
{
	var allAioNames = [];
	let aio = system.deviceData.interfaces.AIO;
	if (aio != null)
	{
		for (var i = 0; i < aio.peripherals.length; i++)
		{
			var aioperiph = aio.peripherals[i];
			allAioNames.push(aioperiph.name);
		}
	}
	return allAioNames;
}

function peripheralListFromSysCtl(peripheralName, sysctl)
{
    var peripherals = []
    sysctl.SysCtl_PeripheralPCLOCKCR.forEach((element, index) => {
        var split_by_underscore = element.name.split("_")
        var peripheralInst = split_by_underscore[split_by_underscore.length - 1];
        if (peripheralInst.startsWith(peripheralName))
        {
            peripherals.push(peripheralInst)
        }
    });
    return peripherals
}
function checkinVar(peripheralName)
{
    let variant = normalizeVariant(getVariant());
    if (!json_import || !json_import[variant]) {
        return true;
    }
    let supportTable = json_import[variant];
    if (supportTable && peripheralName.name in supportTable && supportTable[peripheralName.name] === 0) {
        return false;
    }
    return true;
}
function countinstances(peripheralType,default_instances){//FOR peripherals where instance is selected without pinmux
    let co=0;
    let variant = normalizeVariant(getVariant());
    if (!json_import || !json_import[variant]) {
        return default_instances
    }
    let supportTable = json_import[variant];
    if (supportTable) {
        for (let key in supportTable) {
            if (key.startsWith(peripheralType) && supportTable[key] === 1) {
                co++;
            }
        }
    }
    return co;
}
function peripheralCount(peripheralType)
{
	let peripherals = system.deviceData.peripherals
	let numberOfPeripherals = Object.keys(peripherals).length;
	var count = 0;

	for (var peripheral in peripherals) {
	  	try
	  	{
	  		var interfaces = peripherals[peripheral]["interfaces"];
	  		for (var interfaceType in interfaces)
	  		{
	  			if (peripheralType == interfaceType)
	  			{
	  				peripheralNames = interfaces[interfaceType].peripherals;
	  				for(let i = 0; i < peripheralNames.length; i++){
                        if(checkinVar(peripheralNames[i]))count++;
                    }
	  				return count;
	  			}
			}
		}
		catch(err) {

		}
	}
	if (count == 0)
	{
		return -1;
	}
    return (count);
}


function peripheralNames(peripheralType)
{
	let peripherals = system.deviceData.peripherals
    //console.log(peripherals);
	let numberOfPeripherals = Object.keys(peripherals).length;
	var names = [];

	//console.log(numberOfPeripherals);

	for (var peripheral in peripherals) {

	  	try
	  	{
	  		var interfaces = peripherals[peripheral]["interfaces"];
            //console.log(interfaces);
	  		for (var interfaceType in interfaces)
	  		{
	  			if (peripheralType == interfaceType)
	  			{
	  				names = interfaces[interfaceType].peripherals;
	  				//console.log(names);
	  				return names;
	  			}
			}
		}
		catch(err) {

		}
	}
    //console.log(names);
    return (names);
}


function CLB_isType1() {
    return ["F28004x"].includes(getDeviceName());
}

function CLB_isType2() {
    return ["F29H85x"].includes(getDeviceName());
}

function CLB_isType1_Type2(){
    return (CLB_isType1() | CLB_isType2());
}

function SYSCLK_getMaxMHz()
{
    var sysclk_max = {
        // F2807x      : 120,
        // F2837xS     : 200,
        // F2837xD     : 200,
        // F2838x      : 200,
        // F28004x     : 100,
        // F28002x     : 100,
        // F28003x     : 120,
        // F280013x    : 120,
        // F280015x    : 120,
        F29H85x     : 200
    }
    return sysclk_max[getDeviceName()];
}



/*
 *  ======== typeMatches ========
 *  Check that HW signal type matches a specified array of types
 *
 *  Example: within a module's filterHardware(component) method:
 *      for (sig in component.signals) {
 *          let type = component.signals[sig].type;
 *          if (Common.typeMatches(type, ["PWM", "DOUT"])) {
 *              :
 *          }
 *      }
 *
 *  type      - a string or array of strings that are valid signal types
 *  nameArray - array of signal name types that must match one of the signal
 *              types named by type
 *
 *  Returns true iff nameArray contains at least one type name that's
 *          specified the type parameter.
 */
function typeMatches(type, nameArray)
{
    let options = {};

    if (type instanceof Array || typeof type == "object") {
        for (var i = 0; i < type.length; i++) {
            options[type[i]] = 1;
        }
    }
    else if (typeof type == "string" || type instanceof String) {
        options[type] = 1;
    }

    for (var i = 0; i < nameArray.length; i++) {
        let name = nameArray[i];
        if (name in options) {
            return (true);
        }
    }

    return (false);
}

function getDeviceTRM()
{
    var deviceTRMLinks = {
        "F2807x":   "https://www.ti.com/lit/spruhm9",
        "F2837xS":  "https://www.ti.com/lit/spruhx5",
        "F2837xD":  "https://www.ti.com/lit/spruhm8",
        "F28004x":  "https://www.ti.com/lit/sprui33",
        "F2838x":   "https://www.ti.com/lit/spruii0",
        "F28002x":  "https://www.ti.com/lit/spruin7",
        "F28003x":  "https://www.ti.com/lit/spruiw9",
        "F280013x": "https://www.ti.com/lit/spruix1",
        "F280015x": "https://www.ti.com/lit/spruiy4"
    }

    var deviceTRMLink = deviceTRMLinks[getDeviceName()];
    if (deviceTRMLink)
    {
        return deviceTRMLink
    }
    else
    {
        return ""
    }
}

function getDeviceDatasheet()
{
    var deviceDSLinks = {
        "F2807x":   "https://www.ti.com/lit/gpn/tms320f28075",
        "F2837xS":  "https://www.ti.com/lit/gpn/tms320f28377s",
        "F2837xD":  "https://www.ti.com/lit/gpn/tms320f28379d",
        "F28004x":  "https://www.ti.com/lit/gpn/tms320f280049",
        "F2838x":   "https://www.ti.com/lit/gpn/tms320f28388d",
        "F28002x":  "https://www.ti.com/lit/gpn/tms320f280025c",
        "F28003x":  "https://www.ti.com/lit/gpn/tms320f280039c",
        "F280013x": "https://www.ti.com/lit/gpn/tms320f2800137",
        "F280015x": "https://www.ti.com/lit/gpn/tms320f2800157"
    }

    var deviceDSLink = deviceDSLinks[getDeviceName()];
    if (deviceDSLink)
    {
        return deviceDSLink
    }
    else
    {
        return ""
    }
}

function getCollateralFindabilityList(peripheral)
{
    var res = "";
    //*********************************************************************
    // GETTING STARTED WITH SYSCONFIG
    //*********************************************************************
    res += "**"
    res += "Sysconfig Resources"
    res += "**\n"
    res += "*   [C2000 SysConfig - Step by Step Guide on How to use C2000 SysConfig](https://www.ti.com/lit/spracx3)\n"
    res += "*   [C2000 SysConfig - Speed Up Development With C2000 Real-Time MCUs Using SysConfig](https://www.ti.com/lit/spry341)\n"
    res += "\n"

    var deviceGPN = getDeviceName();
    var cdata = Collateral.getCollateralData();
    // console.log(cdata[peripheral]);
    for (var i=0; i < cdata[peripheral].length; i++)
    {
        //*********************************************************************
        // CATEGORY TITLE
        //*********************************************************************
        var category_dict = cdata[peripheral][i];
        // console.log(category_dict['category_displayName'])

        // first check if the category is used by this device at all (not filtered out from this device)
        var category_used = false;
        for (var j=0; j < category_dict['content'].length; j++)
        {
            var content_dict = category_dict['content'][j]
            if (    ('devices' in content_dict && content_dict['devices'].includes(deviceGPN)) ||
                    !('devices' in content_dict)
            )
            {
                category_used = true;

                // break out of loop on the first occurrence of a collateral that is used for this device
                break;
            }
        }

        // now if it was used, go ahead and add the category title
        if (category_used)
        {
            res += "\n# **" +
                    category_dict['category_displayName'] +
                    "**\n"
        }

        //*********************************************************************
        // COLLATERAL LINKS WITHIN CATEGORY
        //*********************************************************************
        // add each content item that applies
        for (var j=0; j < category_dict['content'].length; j++)
        {
            var content_dict = category_dict['content'][j]
            if (    ('devices' in content_dict && content_dict['devices'].includes(deviceGPN)) ||
                    !('devices' in content_dict)
            )
            {
                // italicize if this is an App Note
                if ( 'appNote' in content_dict )
                {
                    res += "*   *[" +
                            content_dict['name'] +
                            "](" +
                            content_dict['url'] +
                            ")*"
                }
                // don't italicize if not an app note
                else
                {
                    res += "*   [" +
                            content_dict['name'] +
                            "](" +
                            content_dict['url'] +
                            ")"
                }

                // add a (Video) tag if this is a video
                if ('video' in content_dict)
                {
                    res += " (Video)"
                }

                // now add a newline to finish up the normal bullet
                res += "\n"

                //*********************************************************************
                // EXTRA TEXT FOR THIS COLLATERAL LINK
                //*********************************************************************
                // add the "Extra Text" as a sub-bullet if it exits
                if ('description' in content_dict)
                {
                    res += "    *   " +
                            content_dict['description'] +
                            "\n"
                }
            }
        }

    }

    //*********************************************************************
    // DEVICE TRM
    //*********************************************************************
    // finally, add the device TRM to the bottom of the list
    // res += "---\n"
    res += "\n# ***"
    res += "["+deviceGPN+" Technical Reference Manual](" + getDeviceTRM() + ")"
    res += "***\n"


    return res
}

function getSysCfgCoreNames()
{
    let core_names = [];

    for( let core of system.deviceData.cores)
    {
        core_names.push(core.name);
    }
    return core_names;
}

function getSelfSysCfgCoreName() {
    if(system.deviceData.core)
        return system.deviceData.core.name;
}

//*********************************************************************
// Resource Allocation functionality
//*********************************************************************

//
// Check if tool is loaded in SETUP mode in system context
//
function isAllocationSetupMode() {
    return (system.context == "system" && system.resourceAllocation.mode == "SETUP" );
}

//
// Check if tool is loaded in CONFIGURE mode
//
function isAllocationConfigureMode() {
    return (system.resourceAllocation.mode == "CONFIGURE");
}

function filterConfigsIfInSetupMode(configList) {
    if(isAllocationSetupMode()){
        return filterConfigurationList(configList, 'shouldBeAllocatedAsResource', ['default', 'buttonText']);
    }
    else {
        return configList;
    }
}

function filterConfigurationList(configList, keyY = 'shouldBeAllocatedAsResource', keyXList = ['default', 'buttonText']) {
    let filteredList = [];
    filterRecursiveUtil(configList, filteredList, keyY, keyXList);
    return filteredList;
}

function filterRecursiveUtil(configList, finalList, keyY, keyXList) {
    for (let i = 0; i < configList.length; i++) {
        let config = configList[i];
        if(!config)
            continue;
        if(config.name && config.name.startsWith("$")){
            finalList.push(config);
            continue;
        }
        keyXList.forEach(key => {
            if (config.hasOwnProperty(key)) {
                if (!config.hasOwnProperty(keyY) || !config[keyY])
                    config.hidden = true;
            }
        })
        if (config.hasOwnProperty('config')) {
            config.config = filterConfigurationList(config.config, keyY, keyXList);
        }

        finalList.push(config);
    }
}

//
// Check if tool is loaded without Resource Allocation mode
//
function isAllocationOff() {
    return (system.resourceAllocation.mode == "OFF");
}