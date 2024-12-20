let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_watchdog.js");


/* Intro splash on GUI */
let longDescription = "";



var WATCHDOG_INSTANCE = [
    { name: "WATCHDOG_BASE", displayName: "WATCHDOG"},

]




function onchangeWDMode(inst, ui)
{
    if (inst.wdMode == "SYSCTL_WD_MODE_RESET"){
        ui.registerInterrupts.hidden = true;
		ui.wdPulse.hidden = false;
		inst.registerInterrupts = false;
    }
    else {

	  ui.registerInterrupts.hidden = false;
	  ui.wdPulse.hidden = true;
    }

}

//function onchangeWindowEnable(inst, ui)
//{
//    if (inst.wdWindowEnable == true){
//        ui.wdWindowThreshold.hidden = false;
//    }
//    else {
//      ui.wdWindowThreshold.hidden = true;
//	  inst.wdWindowThreshold = 0;
//    }

//}

function onchangewdpredivider(inst, ui)
{
   var calcwdtimeresults = calcwdtime(inst.wdPredivider,inst.wdPrescalar);

   inst.wdClock = calcwdtimeresults.wdclock;
   inst.wdTime = calcwdtimeresults.wdtime;
   inst.wdPulse = calcwdtimeresults.wdpulse;

}
function onchangewdprescalar(inst, ui)
{
   if(inst.wdPredivider)
   {

//   calcwdtime(inst.wdPredivider,inst.wdPrescalar);

   var calcwdtimeresults = calcwdtime(inst.wdPredivider,inst.wdPrescalar);

   inst.wdClock = calcwdtimeresults.wdclock;
   inst.wdTime = calcwdtimeresults.wdtime;
   inst.wdPulse = calcwdtimeresults.wdpulse;
   }
   else
   {
//	calcwdtime(inst.wdPredivider,inst.wdPrescalar);

   var calcwdtimeresults = calcwdtime('SYSCTL_WD_PREDIV_512',inst.wdPrescalar);

   inst.wdClock = calcwdtimeresults.wdclock;
   inst.wdTime = calcwdtimeresults.wdtime;
   inst.wdPulse = calcwdtimeresults.wdpulse;
   }
}

function calcwdtime(predivide, prescale)
{
 var localwdclock
 var predivsubstr;
 var prescalesubstr;
 var intprediv;
 var intprescale;
 var localwdtime;
 var localwdpulse;


   predivsubstr = predivide.substring(17);
   prescalesubstr = prescale.substring(19);
   intprediv = parseFloat(predivsubstr);
   intprescale = parseFloat(prescalesubstr);


 localwdclock = 10000000.0/intprediv;
 localwdclock = (localwdclock/intprescale)/1000.0 ;
 localwdtime = (1/localwdclock) * 256.0;
 localwdpulse = (1/localwdclock) * 512.0;

   return {
        wdclock: localwdclock,
        wdtime : localwdtime,
        wdpulse : localwdpulse
    }

}


/* Array of Watchdog configurables that are common across device families */
let staticConfig = [

    {
        name : "GROUP_PERCFG",
        displayName: "Peripheral Configuration",
        collapsed: false,
        config: [
            {
                name        : "watchdogBase",
                displayName : "Watchdog Instance",
                description : 'Instance of the Watchdog used.',
                hidden      : true,
                default     : WATCHDOG_INSTANCE[0].name,
                options     : WATCHDOG_INSTANCE
            },

            {
                name        : "wdMode",
                displayName : "Set the WD Mode",
                description : 'Set the WD Action either Interrupt or Reset',
                hidden      : false,
                onChange    : onchangeWDMode,
                default     : 'SYSCTL_WD_MODE_RESET',
                options     : device_driverlib_peripheral.SysCtl_WDMode
            },
            {
                name        : "wdPredivider",
                displayName : "Watchdog Predivider",
                description : 'Watchdog Clock Predivider',
                hidden      : false,
                onChange    : onchangewdpredivider,
                default     : 'SYSCTL_WD_PREDIV_512',
                options     : device_driverlib_peripheral.SysCtl_WDPredivider,
            },
            {
                name        : "wdPrescalar",
                displayName : "Watchdog Prescalar",
                description : 'Watchdog Clock Prescalar',
                hidden      : false,
                onChange    : onchangewdprescalar,
                default     : 'SYSCTL_WD_PRESCALE_1',
                options     : device_driverlib_peripheral.SysCtl_WDPrescaler
            },
            {
                name        : "wdClock",
                displayName : "Watchdog Clock(kHz)",
                description : 'Watchdog Clock',
                hidden      : false,
                readOnly    : true,
                default     : 19.53125,

            },
            {
                name        : "wdTime",
                displayName : "Watchdog Countdown Time(ms)",
                description : 'Max time allowed between write to the WDKEY register',
                hidden      : false,
                readOnly    : true,
                default     : 13.1072,

            },
            {
                name        : "wdPulse",
                displayName : "Watchdog Reset Pulse Duration(ms)",
                description : 'Time that Watchdog will hold XRSn low on WD Reset',
                hidden      : false,
                readOnly    : true,
                default     : 26.2144,

            },
            {
                name        : "wdWindowThreshold",
                displayName : "Minimum Count of WDCTR Before Service",
                description : 'Watchdog lower limit threshold',
                hidden      : false,
                default     : 0,
            },
            {
                name        : "enableModule",
                displayName : "Start the Watchdog",
                description : 'Starts the Watchdog',
                hidden      : false,
                default     : true
            },
        ]
    },
    {
        name: "GROUP_ISR",
        displayName: "Interrupt Configuration",
        collapsed: true,
        config: [
            {
            name        : "registerInterrupts",
            displayName : "Register Interrupt Handler",
            description : 'Whether or not to register interrupt handlers in the interrupt module.',
            hidden      : true,
            default     : false
            },
        ]
    }
];

function moduleInstances(inst)
{
    let components = []
    if (inst.registerInterrupts)
    {
        components.push({
            name: "wdInt",
            group: "GROUP_ISR",
            displayName: "Watchdog Interrupt",
            moduleName: "/driverlib/interrupt.js",
            collapsed: false,
            args: {
                $name : "WATCHDOG_INT",
                typeInterruptName : true,
                pinmuxPeripheralModule : "",
                driverlibInt: "INT_WD",
                interruptHandler : "INT_Watchdog_ISR",
            }
        })
    }
    return components;
}

function onValidate(inst, validation)
{
    var usedWATCHDOGInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedWATCHDOGInsts.push(instance_obj.watchdogBase);
    }

    var duplicatesResult = Common.findDuplicates(usedWATCHDOGInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ")
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The Watchdog Instance used. Duplicates: " + allDuplicates,
            inst, "watchdogBase");
    }


    if (inst.wdWindowThreshold < 0 || inst.wdWindowThreshold > 255)
    {
        validation.logError(
            "Enter an integer for Watchdog Window Threshold between 0 and 255!",
            inst, "wdWindowThreshold");
    }
    if (!Number.isInteger(inst.wdWindowThreshold))
    {
        validation.logError(
            "Watchdog Window Threshold must be an integer",
            inst, "wdWindowThreshold");

    }




}




function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["WATCHDOG"]));
}

var watchdogModule = {
    peripheralName: "WATCHDOG",
    displayName: "WATCHDOG",
    maxInstances: 1,
    defaultInstanceName: "myWATCHDOG",
    description: "Watchdog Peripheral",
    longDescription: longDescription,
    filterHardware : filterHardware,
    templates: {
        boardc : "/driverlib/watchdog/watchdog.board.c.xdt",
        boardh : "/driverlib/watchdog/watchdog.board.h.xdt"
    },
    moduleStatic : {
        config          : staticConfig,
        validate        : onValidate,
        moduleInstances : moduleInstances,

    }
};


if (watchdogModule.maxInstances <= 0)
{
    delete watchdogModule.pinmuxRequirements;
}

exports = watchdogModule;