let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_epwm.js");
let device_driverlib_hrpwm = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_hrpwm.js");


function onChangeEnableDisable(inst, ui)
{
    if (inst.epwmTimebase_phaseEnable == true)
    {
        ui.epwmTimebase_phaseShift.hidden = false;
    }
    else if (inst.epwmTimebase_phaseEnable == false)
    {
        ui.epwmTimebase_phaseShift.hidden = true;
        inst.epwmTimebase_phaseShift = 0; // Set default
    }

    if (inst.epwmTimebase_periodLoadMode == "EPWM_PERIOD_SHADOW_LOAD")
    {
        ui.epwmTimebase_periodLoadEvent.hidden = false;
    }
    else if (inst.epwmTimebase_periodLoadMode == "EPWM_PERIOD_DIRECT_LOAD")
    {
        ui.epwmTimebase_periodLoadEvent.hidden = true;
        inst.epwmTimebase_periodLoadEvent = device_driverlib_peripheral.EPWM_PeriodShadowLoadMode[0].name; // Set default
    }

    if (inst.epwmTimebase_counterMode == "EPWM_COUNTER_MODE_UP_DOWN")
    {
        ui.epwmTimebase_counterModeAfterSync.hidden = false;
    }
    else if (inst.epwmTimebase_counterMode == "EPWM_COUNTER_MODE_UP" || 
        inst.epwmTimebase_counterMode =="EPWM_COUNTER_MODE_DOWN" ||
        inst.epwmTimebase_counterMode == "EPWM_COUNTER_MODE_STOP_FREEZE")
    {
        ui.epwmTimebase_counterModeAfterSync.hidden = true;
        inst.epwmTimebase_counterModeAfterSync = device_driverlib_peripheral.EPWM_SyncCountMode[0].name;
    }
}

var config = [
    {
        name        : "epwmTimebase_emulationMode",
        displayName : "Emulation Mode",
        description : 'Behavior of the ePWM time-base counter during emulation events',
        hidden      : false,
        default     : device_driverlib_peripheral.EPWM_EmulationMode[0].name,
        options     : device_driverlib_peripheral.EPWM_EmulationMode
    },
    {
        name: "epwmTimebase_clockDiv",
        displayName : "Time Base Clock Divider",
        description : 'CLKDIV: These bits select the time base clock pre-scale value, TBCLK = EPWMCLK/(HSPCLKDIV*CLKDIV)',
        hidden      : false,
        default     : device_driverlib_peripheral.EPWM_ClockDivider[0].name,
        options     : device_driverlib_peripheral.EPWM_ClockDivider,
    },
    {
        name: "epwmTimebase_hsClockDiv",
        displayName : "High Speed Clock Divider",
        description : 'HSPCLKDIV: These bits determine part of the time-base clock pre-scale value, TBCLK = EPWMCLK/(HSPCLKDIV*CLKDIV)',
        hidden      : false,
        default     : "EPWM_HSCLOCK_DIVIDER_2",
        options     : device_driverlib_peripheral.EPWM_HSClockDivider,
    },
    {
        name: "epwmTimebase_period",
        displayName : "Time Base Period",
        description : 'Period for the Time Base Counter Submodule',
        hidden      : false,
        default     : 0,
    },
    {
        name: "epwmTimebase_counterMode",
        displayName : "Counter Mode",
        description : 'Mode of the Counter value for the Time Base Counter Submodule',
        hidden      : false,
        default     : "EPWM_COUNTER_MODE_UP",
        options     : device_driverlib_peripheral.EPWM_TimeBaseCountMode,
        onChange    : onChangeEnableDisable
    },
    {
        name: "EPWM_Frequency",
        displayName : "EPWM Frequency [Mhz]",
        hidden      : false,
        default     : Common.SYSCLK_getMaxMHz(),
        getValue    : (inst) => {
            var clockTree = Common.getClockTree();
            if(clockTree){
                var epwm_clk_div = {
                    "EPWM_CLOCK_DIVIDER_1"  : 1,
                    "EPWM_CLOCK_DIVIDER_2"  : 2,
                    "EPWM_CLOCK_DIVIDER_4"  : 4,
                    "EPWM_CLOCK_DIVIDER_8"  : 8,
                    "EPWM_CLOCK_DIVIDER_16" : 16,
                    "EPWM_CLOCK_DIVIDER_32" : 32,
                    "EPWM_CLOCK_DIVIDER_64" : 64,
                    "EPWM_CLOCK_DIVIDER_128": 128
                }
                var hs_clk_div = {
                    "EPWM_HSCLOCK_DIVIDER_1"  : 1,
                    "EPWM_HSCLOCK_DIVIDER_2"  : 2,
                    "EPWM_HSCLOCK_DIVIDER_4"  : 4,
                    "EPWM_HSCLOCK_DIVIDER_6"  : 6,
                    "EPWM_HSCLOCK_DIVIDER_8"  : 8,
                    "EPWM_HSCLOCK_DIVIDER_10" : 10,
                    "EPWM_HSCLOCK_DIVIDER_12" : 12,
                    "EPWM_HSCLOCK_DIVIDER_14" : 14
                }
                var tbclk = (clockTree["EPWMCLK"].in/(epwm_clk_div[inst.epwmTimebase_clockDiv] * hs_clk_div[inst.epwmTimebase_hsClockDiv]))
                var num
                if(inst.epwmTimebase_counterMode == "EPWM_COUNTER_MODE_UP" || inst.epwmTimebase_counterMode == "EPWM_COUNTER_MODE_DOWN"){
                    num = tbclk/(1 + inst.epwmTimebase_period)
                }
                else if(inst.epwmTimebase_counterMode == "EPWM_COUNTER_MODE_UP_DOWN"){
                    num = tbclk/(2 * inst.epwmTimebase_period)
                }
                else{
                    return 0
                }
                return Math.round(num*100)/100   
            }
            else{
                return 0
            }
        }
    },
    {
        name: "epwmTimebase_periodLoadMode", 
        displayName : "Time Base Period Load Mode",
        description : 'Period load mode for the Time Base Counter Submodule',
        hidden      : false,
        default     : device_driverlib_peripheral.EPWM_PeriodLoadMode[0].name,
        options     : device_driverlib_peripheral.EPWM_PeriodLoadMode,
        onChange    : onChangeEnableDisable
    },
    {
        name: "epwmTimebase_periodLoadEvent",
        displayName : "Time Base Period Load Event",
        description : 'Period load event for the Time Base Counter Submodule',
        hidden      : false,
        default     : device_driverlib_peripheral.EPWM_PeriodShadowLoadMode[0].name,
        options     : device_driverlib_peripheral.EPWM_PeriodShadowLoadMode,
    },
    {
        name: "epwmTimebase_periodGld",
        displayName : "Enable Time Base Period Global Load",
        description : 'Use global load configuration for PRD',
        hidden      : false,
        default     : false,
    },
    {
        name: "epwmTimebase_counterValue",
        displayName : "Initial Counter Value",
        description : 'Initial Counter value for the Time Base Counter Submodule',
        hidden      : false,
        default     : 0,
    },
    {
        name: "epwmTimebase_counterModeAfterSync",
        displayName : 'Counter Mode After Sync',
        description : 'The direction the time-base counter (TBCTR) will count after a synchronization event occurs',
        hidden      : true,
        default     : device_driverlib_peripheral.EPWM_SyncCountMode[0].name,
        options     : device_driverlib_peripheral.EPWM_SyncCountMode,
    },
    {
        name: "epwmTimebase_phaseEnable",
        displayName : "Enable Phase Shift Load",
        description : 'Enable phase shift load for the Time Base Counter Submodule',
        hidden      : false,
        default     : false,
        onChange    : onChangeEnableDisable
    },
    {
        name: "epwmTimebase_phaseShift",
        displayName : 'Phase Shift Value',
        description : 'Phase Shift Value for the Time Base Counter Submodule',
        hidden      : true,
        default     : 0,
    },
    {
        name: "epwmTimebase_forceSyncPulse",
        displayName : 'Force a Sync Pulse',
        description : 'Force a sync pulse for the Time Base Counter Submodule',
        hidden      : false,
        default     : false,
    },
    {
        name: "hrpwm_syncSource",
        displayName : "EPWMxSYNCPER Source Select",
        description : 'Selects the source of the EPWMSYNCPER signal that goes to the CMPSS and GPDAC',
        hidden      : false,
        default     : device_driverlib_hrpwm.HRPWM_SyncPulseSource[0].name,
        options     : device_driverlib_hrpwm.HRPWM_SyncPulseSource
    },
];

if(["F29H85x"].includes(Common.getDeviceName())) //else
{    
    config.splice.apply(config, [config.length - 1, 0].concat([
        {
            name: "epwmTimebase_syncInPulseSource",
            displayName : "Sync In Pulse Source",
            description : 'Sync in Pulse for the Time Base Counter Submodule',
            hidden      : false,
            default     : device_driverlib_peripheral.EPWM_SyncInPulseSource[1].name,
            options     : device_driverlib_peripheral.EPWM_SyncInPulseSource,
        },
        {
            name: "epwmTimebase_syncOutPulseMode",
            displayName : "Sync Out Pulse",
            description : 'Sync Out Pulse for the Time Base Counter Submodule',
            hidden      : false,
            minSelections: 0,
            default     : [],
            options     : [
                { name: "EPWM_SYNC_OUT_PULSE_ON_SOFTWARE", displayName: "Software force generated EPWM sync-out pulse" },
                { name: "EPWM_SYNC_OUT_PULSE_ON_CNTR_ZERO", displayName: "Counter zero event generates EPWM sync-out pulse" },
                { name: "EPWM_SYNC_OUT_PULSE_ON_CNTR_COMPARE_B", displayName: "Counter equal to CMPB event generates EPWM sync-out pulse" },
                { name: "EPWM_SYNC_OUT_PULSE_ON_CNTR_COMPARE_C", displayName: "Counter equal to CMPC event generates EPWM sync-out pulse" },
                { name: "EPWM_SYNC_OUT_PULSE_ON_CNTR_COMPARE_D", displayName: "Counter equal to CMPD event generates EPWM sync-out pulse" },
                { name: "EPWM_SYNC_OUT_PULSE_ON_DCA_EVT1_SYNC", displayName: "DCA Event 1 Sync signal generates EPWM sync-out pulse" },
                { name: "EPWM_SYNC_OUT_PULSE_ON_DCB_EVT1_SYNC", displayName: "DCB Event 1 Sync signal generates EPWM sync-out pulse" },
                { name: "EPWM_SYNC_OUT_PULSE_ON_ALL", displayName: "Enable all the above sources" },
            ],
        },
        {
            name: "epwmTimebase_oneShotSyncOutTrigger",
            displayName : "One-Shot Sync Out Trigger",
            description : 'One-Shot Sync Out Trigger for the Time Base Counter Submodule',
            hidden      : false,
            default     : device_driverlib_peripheral.EPWM_OneShotSyncOutTrigger[0].name,
            options     : device_driverlib_peripheral.EPWM_OneShotSyncOutTrigger,
        },
    ]));
}



var epwmTimebaseSubmodule = {
    displayName: "EPWM Time Base",
    maxInstances: Common.peripheralCount("EPWM"),
    defaultInstanceName: "EPWM_TB",
    description: "Enhanced Pulse Width Modulator Time Base Counter",
    config: config,
    templates: {
        boardc : "", //"/gpio/gpio.board.c.xdt",
        boardh : ""//"/gpio/gpio.board.h.xdt"
    },
};


exports = epwmTimebaseSubmodule;
