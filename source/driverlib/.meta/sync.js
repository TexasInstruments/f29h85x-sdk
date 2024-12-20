let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_sysctl.js");

/* Array of CAN configurables that are common across device families */
let staticConfig = [

    {
        name        : "syncOutSource",
        displayName : "SYNCOUT (EXTSYNCOUT) Source",
        description : 'Source for the SYNCOUT (EXTSYNCOUT) signal',
        // options     : () => Common.modInstances('/driverlib/epwm.js').concat(Common.modInstances('/driverlib/ecap.js'))
        options     : device_driverlib_peripheral.SysCtl_SyncOutputSource,
        minSelections : 0,
        default     : [],
    },
    {
        name        : "ADCSOCAOutputSelect",
        displayName : "ADC SOCA Output Enable (ADCSOCAO)",
        description : 'Enable all sources for the ADC SOCA external output',
        // options     : () => Common.modInstances('/driverlib/epwm.js'),
        // isArray     : true,
        options     : ()=>{
            let retArr = []
            for (let i of device_driverlib_peripheral.SYSCTL_ADCSOC_SRC_PWM)
            {
                if (i.name.includes("SOCA"))
                {
                    retArr.push(i)
                }
            } 
            return retArr
        },
        minSelections : 0,
        default     : [],
    },
    {
        name        : "ADCSOCBOutputSelect",
        displayName : "ADC SOCB Output Enable (ADCSOCBO)",
        description : 'Enable all sources for the ADC SOCB external output',
        // options     : () => Common.modInstances('/driverlib/epwm.js'),
        // isArray     : true,
        options     : (inst,ui)=>{
            let retArr = []
            for (let i of device_driverlib_peripheral.SYSCTL_ADCSOC_SRC_PWM)
            {
                if (i.name.includes("SOCB"))
                {
                    retArr.push(i)
                }
            } 
            return retArr
        },
        minSelections : 0,
        default     : [],
    },
];



staticConfig = staticConfig.concat([
    {
        name: "ADCSOCOutputLock",
        displayName : "ADC SOCA/B Output Lock",
        description : 'Prevent changes to the ADCSOCAO and ADCSOCBO source',
        hidden      : false,
        default     : false,
    },
    {
        name: "syncOutLock",
        displayName : "EPWM External SYNCOUT Lock",
        description : 'Prevent changes to the SYNCOUT source',
        hidden      : false,
        default     : false,
    },
])

staticConfig.push(
    {
        name: "useCase",
        displayName : "PinMux Use Case",
        description : 'Peripheral use case',
        longDescription : "The Pinmux Use Case for SYNC Module are defaulted to Custom. Please switch to All or add cutom Pins for Pinmux Configurations",
        hidden      : false,
        default     : 'CUSTOM',
        options     : Pinmux.getPeripheralUseCaseNames("SYNC"),
        onChange    : Pinmux.useCaseChanged,

    }
)



/*
 *  ======== filterHardware ========
 *  Control RX, TX Pin usage by the user specified dataDirection.
 *
 *  param component - hardware object describing signals and
 *                     resources they're attached to
 *
 *  returns Boolean indicating whether or not to allow the component to
 *           be assigned to an instance's $hardware config
 */
function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["SYNC"]));
}

var syncModule = {
    peripheralName: "SYNC",
    displayName: "SYNC",
    maxInstances: 1,
    open : true,
    defaultInstanceName: "mySYNC",
    description: "Synchronization",
    filterHardware : filterHardware,
    config          : staticConfig,
    pinmuxRequirements    : Pinmux.syncPinmuxRequirements,
    moduleInstances : (inst) => {

        var ownedInstances = []
        
        // Pinmux qualification
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("SYNC", inst)
        ownedInstances = ownedInstances.concat(pinmuxQualMods)
        return ownedInstances
    },
    templates: {
        boardc : "/driverlib/sync/sync.board.c.xdt",
        boardh : "/driverlib/sync/sync.board.h.xdt"
    },
};

if (syncModule.maxInstances <= 0)
{
    delete syncModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(syncModule)
    
    for (let cfg of syncModule.config)
    {
        if (cfg.name == "useInterfacePins")
        {
            cfg.longDescription = "The Pinmux for SYNC Module are defaulted to none. Please add pins to which the Pinmux is expected to be generated."
        }
    }

    Pinmux.addPinMuxQualGroupToConfig(syncModule)
}

exports = syncModule;