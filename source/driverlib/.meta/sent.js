let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_sent.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

let dma_instances = [];
for (var dma of device_driverlib_memmap.DMAMemoryMap) {
    dma_instances.push({
        name : dma.name,
        displayName : dma.displayName
    })
}

function burstSizeMapping(fifoLevel, inst){
    switch(fifoLevel) {
        case "SENT_TRIGDISABLE":
            return 4;
        default:{
            let retString = fifoLevel.split('_')[1];
            return 2*Number(retString.slice(7));
        }
            
    }
}

function onChangeDataNibble(inst, ui)
{
    for(var nibIndex in device_driverlib_peripheral.SENT_NibbleNumber){
        var currentNIB = device_driverlib_peripheral.SENT_NibbleNumber[nibIndex].name
        var nibi = (currentNIB).replace(/[^0-9]/g,'')
        var nibConfigs = [
            "d0Nibble" + nibi.toString(),
            "d1Nibble" + nibi.toString(),
        ]

        if (ui)
        {
            for (var nibConfig of nibConfigs)
            {
                if(inst.dataNibble)
                {
                    ui[nibConfig].hidden = false;
                }
                else
                {
                    ui[nibConfig].hidden = true;
                }
            }
        }
    }
}

function onChangeCRC(inst, ui)
{
    if(inst.enableCRC)
    {
        ui.enableCRCStatus.hidden = false;
        ui.setCRCType.hidden = false;
        ui.setCRCWidth.hidden = false;
    }
    else
    {
        ui.enableCRCStatus.hidden = true;
        ui.setCRCType.hidden = true;
        ui.setCRCWidth.hidden = true;
    }
}

function onChangeEnableFIFO(inst, ui)
{
    if(inst.enableFIFO)
    {
        ui.setFIFOLevel.hidden = false;
    }
    else
    {
        ui.setFIFOLevel.hidden = true;
    }
}

function onChangeUseInterrupts(inst, ui)
{
    if (inst.useInterrupts){
        ui.enableInterrupt.hidden = false
        ui.registerInterrupts.hidden = false
        ui.interruptSource.hidden = false     
    }
    else{
        ui.enableInterrupt.hidden = true
        ui.registerInterrupts.hidden = true
        ui.interruptSource.hidden = true
    }
}

function onChangeUseDMARX(inst, ui)
{
    if (inst.useDMARX)
    {
        ui.DMARXInst.hidden = false;
    }
    else 
    {
        ui.DMARXInst.hidden = true;
    }
}

function onChangeEnableBroadcastCh(inst, ui)
{
    if (inst.enableBroadcastCh){
        ui.broadcastChPeriod.hidden = false
        ui.broadcastChTrigger.hidden = false
        ui.broadcastcmp1TT.hidden = false
        ui.broadcastcmp2TT.hidden = false     
        ui.broadcastcmp3TT.hidden = false     
        ui.broadcastcmp4TT.hidden = false     
        ui.broadcastcmp5TT.hidden = false     
        ui.broadcastcmp6TT.hidden = false     
        ui.broadcastcmp7TT.hidden = false     
        ui.broadcastcmp8TT.hidden = false
        ui.broadcastcmp9TT.hidden = false
    }
    else
    {
        ui.broadcastChPeriod.hidden = true
        ui.broadcastChTrigger.hidden = true
        ui.broadcastcmp1TT.hidden = true
        ui.broadcastcmp2TT.hidden = true     
        ui.broadcastcmp3TT.hidden = true     
        ui.broadcastcmp4TT.hidden = true     
        ui.broadcastcmp5TT.hidden = true     
        ui.broadcastcmp6TT.hidden = true     
        ui.broadcastcmp7TT.hidden = true     
        ui.broadcastcmp8TT.hidden = true     
        ui.broadcastcmp9TT.hidden = true  
    }
}

function onChangeEnableSensor(inst, ui)
{
    for(var channelIndex in device_driverlib_peripheral.SENT_SensorNumber){ 
        var currentCh = device_driverlib_peripheral.SENT_SensorNumber[channelIndex].name
        var chli = (currentCh).replace(/[^0-9]/g,'')
        var chlConfigs = [
            "enableSensor" + chli.toString(),
            "sensor" + chli.toString() + "cmp1TT",
            "sensor" + chli.toString() + "cmp2TT",
            "sensor" + chli.toString() + "cmp3TT",
            "sensor" + chli.toString() + "cmp4TT",
            "sensor" + chli.toString() + "cmp5TT",
            "sensor" + chli.toString() + "cmp6TT",
            "sensor" + chli.toString() + "cmp7TT",
            "sensor" + chli.toString() + "cmp8TT",
            "sensor" + chli.toString() + "cmp9TT",
            "sensor" + chli.toString() + "cmp10TT",
            "sensor" + chli.toString() + "Period",
            "sensor" + chli.toString() + "Trigger",
            "sensor" + chli.toString() + "Timeout",
        ]

        if (ui)
        {
            for (var chlConfig of chlConfigs)
            {
                if((inst.enabledSensor).includes(currentCh))
                {
                    ui[chlConfig].hidden = false;
                }
                else
                {
                    ui[chlConfig].hidden = true;
                }
            }
        }
    }
}

/* Array of SENT configurables that are common across device families */
let config = [
    {
        name: "GROUP_PERCFG",
        displayName: "Peripheral Configuration",
        collapsed: false,
        config: [
            //**********************************************************************
            // Baud Settings
            {
                name        : "enablePausePulse",
                displayName : "Enable Pause Pulse",
                description : "Pause pulse will be expected after the CRC",
                hidden      : false,
                default     : false,
            },
            {
                name        : "clockTickTime",
                displayName : "Clock Cycle per Tick",
                description : "The number of clock cycle per tick when generating the internal tick clock",
                hidden      : false,
                default     : 300,
            },
            {
                name        : "enableFIFO",
                displayName : "Enable FIFO Mode",
                description : 'Enable FIFO Mode',
                longDescription : "In Direct mapping mode, the Timestamp, data0 and data1 data will be mapped directly to a memory. In FIFO mode, Receivers memory is in FIFO mode which contains Timestamp, data0 and data1.",
                hidden      : false,
                default     : device_driverlib_peripheral.SENT_FIFOMode[0].name,
                options     : device_driverlib_peripheral.SENT_FIFOMode,
                onChange    : onChangeEnableFIFO,
            },
            {
                name        : "setFIFOLevel",
                displayName : "FIFO Trigger Level",
                description : 'Select trigger level for FIFO Trigger Interrupt and DMA Trigger',
                hidden      : true,
                default     : device_driverlib_peripheral.SENT_TriggerLevel[0].name,
                options     : device_driverlib_peripheral.SENT_TriggerLevel,
            },
            {
                name        : "disableTS",
                displayName : "Disable Time Stamp",
                description : 'Disable write of timestamp to memory',
                hidden      : false,
                default     : false,        
            },
            {
                name        : "disableERRData",
                displayName : "Disable Error Data Write",
                description : 'Disable write of error data to memory',
                hidden      : false,
                default     : false,   
            },
            {
                name        : "gFilt",
                displayName : "Glitch Filter",
                description : 'Number of clock cycle pulse to be filtered out',
                hidden      : false,
                default     : 5,
            },
            {
                name        : "timeOut",
                displayName : "Sync Pulse Timeout",
                description : 'Timeout for triggering interrupt if no sync pulse is received during this time',
                hidden      : false,
                default     : 0,
            },        
        ]
    },
];

var nib_configs = [
    {
        name        : "dataNibble",
        displayName : "Data Nibbles",
        description : 'The number of data nibbles to be configured for SENT.',
        hidden      : false,
        default     : device_driverlib_peripheral.SENT_DataNibble[0].name,
        options     : device_driverlib_peripheral.SENT_DataNibble,
        onChange    : onChangeDataNibble,
    },
]

let d0_nibbles_config = []
let d1_nibbles_config = []

for(var nibIndex in device_driverlib_peripheral.SENT_NibbleNumber){
    var currentNIB = device_driverlib_peripheral.SENT_NibbleNumber[nibIndex].name
    var nibi = (currentNIB).replace(/[^0-9]/g,'')
    d0_nibbles_config = d0_nibbles_config.concat([
        {
                name        : "d0Nibble" + nibi.toString(),
                displayName : "Data 0 Nibble " + nibi.toString(),
                description : 'Select which received nibble will be stored in Data 0 Nibble' + nibi.toString(),
                hidden      : true,
                default     : device_driverlib_peripheral.SENT_Nibble[0].name,
                options     : device_driverlib_peripheral.SENT_Nibble,
            }
    ])
    d1_nibbles_config = d1_nibbles_config.concat([
        {
                name        : "d1Nibble" + nibi.toString(),
                displayName : "Data 1 Nibble " + nibi.toString(),
                description : 'Select which received nibble will be stored in Data 1 Nibble' + nibi.toString(),
                hidden      : true,
                default     : device_driverlib_peripheral.SENT_Nibble[0].name,
                options     : device_driverlib_peripheral.SENT_Nibble,
            }
    ])
}

nib_configs = nib_configs.concat([
    {
        name        : "GROUP_D0Nibble",
        displayName : "Data 0 Nibbles",
        config      : d0_nibbles_config
    },
    {
        name        : "GROUP_D1Nibble",
        displayName : "Data 1 Nibbles",
        config      : d1_nibbles_config
    }

])
config = config.concat([
    {
        name: "GROUP_DataNibble",
        displayName: "Data Nibble Configuration",
        config: nib_configs
    }
])

config = config.concat([{
        name        : "GROUP_CRC",
        displayName : "CRC Configuration",
        config      : [
            {
                name        : "enableCRC",
                displayName : "Enable CRC",
                description : 'Enable for fast and slow channel',
                hidden      : false,
                default     : false,
                onChange    : onChangeCRC,
            },
            {
                name        : "enableCRCStatus",
                displayName : "Enable CRC with Status",
                description : 'CRC Calculation of data nibble along with status',
                hidden      : true,
                default     : device_driverlib_peripheral.SENT_RxCRC[0].name,
                options     : device_driverlib_peripheral.SENT_RxCRC,
            },
            {
                name        : "setCRCType",
                displayName : "CRC Type",
                description : 'Select CRC Type',
                hidden      : true,
                default     : device_driverlib_peripheral.SENT_CRCType[0].name,
                options     : device_driverlib_peripheral.SENT_CRCType,
            },
            {
                name        : "setCRCWidth",
                displayName : "CRC Width",
                description : 'The number of CRC bits for fast channel',
                hidden      : true,
                default     : device_driverlib_peripheral.SENT_CRCWidth[0].name,
                options     : device_driverlib_peripheral.SENT_CRCWidth,
            },
        ]
    }]);


var mtp_configs = [
    {
        name        : "enableMTP",
        displayName : "Enable MTP Mode",
        description : 'Enable Master Trigger Pulse Generator',
        hidden      : false,
        default     : false,
        //onChange    : onChangeMTP,
    },
    {
        name        : "waitTime",
        displayName : "Global Wait Time",
        description : 'Time delay between the last data frame received to new master trigger pulse to be generated',
        hidden      : false,
        default     : 256,
    },
    {
        name        : "GROUP_BroadcastChannel",
        displayName : "Broadcast Channel",
        config      : [
            {
                name        : "enableBroadcastCh",
                displayName : "Enable Broadcast Channel",
                description : 'Enable Broadcast Channel MTPG to generate trigger pulse',
                hidden      : false,
                default     : false,
                onChange    : onChangeEnableBroadcastCh,
            },
            {
                name        : "broadcastChPeriod",
                displayName : "Broadcast Channel Period",
                description : 'Set the broadcast channel period',
                hidden      : true,
                default     : 0
            },
            {
                name        : "broadcastChTrigger",
                displayName : "Broadcast Channel Trigger Source",
                description : 'Select trigger source to enable broadcast channel MTPG',
                hidden      : true,
                default     : device_driverlib_peripheral.SENT_Trigger[0].name,
                options     : device_driverlib_peripheral.SENT_Trigger,
            },
            {
                name: "broadcastcmp1TT",
                displayName : "Broadcast CMP1 Toggle Time",
                description : 'Set the time for CMP1 of the broadcast channel to toggle the MTPG output',
                hidden      : true,
                default     : 0
            },
            {
                name: "broadcastcmp2TT",
                displayName : "Broadcast CMP2 Toggle Time",
                description : 'Set the time for CMP2 of the broadcast channel to toggle the MTPG output',
                hidden      : true,
                default     : 0
            },
            {
                name: "broadcastcmp3TT",
                displayName : "Broadcast CMP3 Toggle Time",
                description : 'Set the time for CMP3 of the broadcast channel to toggle the MTPG output',
                hidden      : true,
                default     : 0
            },
            {
                name: "broadcastcmp4TT",
                displayName : "Broadcast CMP4 Toggle Time",
                description : 'Set the time for CMP4 of the broadcast channel to toggle the MTPG output',
                hidden      : true,
                default     : 0
            },
            {
                name: "broadcastcmp5TT",
                displayName : "Broadcast CMP5 Toggle Time",
                description : 'Set the time for CMP5 of the broadcast channel to toggle the MTPG output',
                hidden      : true,
                default     : 0
            },
            {
                name: "broadcastcmp6TT",
                displayName : "Broadcast CMP6 Toggle Time",
                description : 'Set the time for CMP6 of the broadcast channel to toggle the MTPG output',
                hidden      : true,
                default     : 0
            },
            {
                name: "broadcastcmp7TT",
                displayName : "Broadcast CMP7 Toggle Time",
                description : 'Set the time for CMP7 of the broadcast channel to toggle the MTPG output',
                hidden      : true,
                default     : 0
            },
            {
                name: "broadcastcmp8TT",
                displayName : "Broadcast CMP8 Toggle Time",
                description : 'Set the time for CMP8 of the broadcast channel to toggle the MTPG output',
                hidden      : true,
                default     : 0
            },
            {
                name: "broadcastcmp9TT",
                displayName : "Broadcast CMP9 Toggle Time",
                description : 'Set the time for CMP9 of the broadcast channel to toggle the MTPG output',
                hidden      : true,
                default     : 0
            },
        ]
    },

]

mtp_configs = mtp_configs.concat([
    {
        name        : "enabledSensor",
        displayName : "Enable Sensor Channel",
        description : 'Select which Sensor channels to enable.',
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : device_driverlib_peripheral.SENT_SensorNumber,
        onChange    : onChangeEnableSensor
    },
])

for(var channelIndex in device_driverlib_peripheral.SENT_SensorNumber){ 
        var currentCh = device_driverlib_peripheral.SENT_SensorNumber[channelIndex].name
        var chli = (currentCh).replace(/[^0-9]/g,'')
        mtp_configs = mtp_configs.concat([
            {
                name: "GROUP_SENSOR" + chli.toString(),
                displayName: "S" + chli.toString(),
                description: "Sensor " + chli.toString() + " Channel",
                config: [
                    {
                        name: "enableSensor" + chli.toString(),
                        displayName : "Enable Sensor " + chli.toString() + " Channel",
                        description : 'Enable Sensor ' + chli.toString() + ' channel MTPG to generate trigger pulse',
                        hidden      : true,
                        default     : false
                    },
                    {
                        name        : "sensor"+ chli.toString() + "Period",
                        displayName : "Sensor " + chli.toString() + " Period",
                        description : 'Set the sensor ' + chli.toString() + 'period',
                        hidden      : true,
                        default     : 0
                    },
                    {
                        name        : "sensor"+ chli.toString() + "Trigger",
                        displayName : "Sensor " + chli.toString() + " Trigger Source",
                        description : 'Select trigger source to enable sensor' + chli.toString() + 'MTPG',
                        hidden      : true,
                        default     : device_driverlib_peripheral.SENT_Trigger[0].name,
                        options     : device_driverlib_peripheral.SENT_Trigger,
                    },     
                    {
                        name: "sensor" + chli.toString() + "cmp1TT",
                        displayName : "Sensor " + chli.toString() + " CMP1 Toggle Time",
                        description : 'Set the time for CMP1 of the sensor ' + chli.toString() + ' channel to toggle the MTPG output',
                        hidden      : true,
                        default     : 0
                    },
                    {
                        name: "sensor" + chli.toString() + "cmp2TT",
                        displayName : "Sensor " + chli.toString() + " CMP2 Toggle Time",
                        description : 'Set the time for CMP2 of the sensor ' + chli.toString() + ' channel to toggle the MTPG output',
                        hidden      : true,
                        default     : 0
                    },
                    {
                        name: "sensor" + chli.toString() + "cmp3TT",
                        displayName : "Sensor " + chli.toString() + " CMP3 Toggle Time",
                        description : 'Set the time for CMP3 of the sensor ' + chli.toString() + ' channel to toggle the MTPG output',
                        hidden      : true,
                        default     : 0
                    },
                    {
                        name: "sensor" + chli.toString() + "cmp4TT",
                        displayName : "Sensor " + chli.toString() + " CMP4 Toggle Time",
                        description : 'Set the time for CMP4 of the sensor ' + chli.toString() + ' channel to toggle the MTPG output',
                        hidden      : true,
                        default     : 0
                    },
                    {
                        name: "sensor" + chli.toString() + "cmp5TT",
                        displayName : "Sensor " + chli.toString() + " CMP5 Toggle Time",
                        description : 'Set the time for CMP5 of the sensor ' + chli.toString() + ' channel to toggle the MTPG output',
                        hidden      : true,
                        default     : 0
                    },
                    {
                        name: "sensor" + chli.toString() + "cmp6TT",
                        displayName : "Sensor " + chli.toString() + " CMP6 Toggle Time",
                        description : 'Set the time for CMP6 of the sensor ' + chli.toString() + ' channel to toggle the MTPG output',
                        hidden      : true,
                        default     : 0
                    },
                    {
                        name: "sensor" + chli.toString() + "cmp7TT",
                        displayName : "Sensor " + chli.toString() + " CMP7 Toggle Time",
                        description : 'Set the time for CMP7 of the sensor ' + chli.toString() + ' channel to toggle the MTPG output',
                        hidden      : true,
                        default     : 0
                    },
                    {
                        name: "sensor" + chli.toString() + "cmp8TT",
                        displayName : "Sensor " + chli.toString() + " CMP8 Toggle Time",
                        description : 'Set the time for CMP8 of the sensor ' + chli.toString() + ' channel to toggle the MTPG output',
                        hidden      : true,
                        default     : 0
                    },
                    {
                        name: "sensor" + chli.toString() + "cmp9TT",
                        displayName : "Sensor " + chli.toString() + " CMP9 Toggle Time",
                        description : 'Set the time for CMP9 of the sensor ' + chli.toString() + ' channel to toggle the MTPG output',
                        hidden      : true,
                        default     : 0
                    },
                    {
                        name: "sensor" + chli.toString() + "cmp10TT",
                        displayName : "Sensor " + chli.toString() + " CMP10 Toggle Time",
                        description : 'Set the time for CMP10 of the sensor ' + chli.toString() + ' channel to toggle the MTPG output',
                        hidden      : true,
                        default     : 0
                    },
                    {
                        name: "sensor" + chli.toString() + "Timeout",
                        displayName : "Sensor " + chli.toString() + " Timeout",
                        description : 'Timeout for triggering interrupt if receiver has not received response from sensor ' + chli.toString() + 'within this timeout time after MTPG is generated',
                        hidden      : true,
                        default     : 0
                    },
                ]
            }
        ])
    }

config = config.concat([
    {
        name: "GROUP_MTP",
        displayName: "SENT MTP Configurations",
        description: "MTPG Configurations",
        longDescription: "",
        config: mtp_configs
    }
])

config = config.concat([{
        name : "GROUP_Interrupts",
        displayName : "Interrupts Configuration",
        description     : "",
        config : [
        {
            name        : "useInterrupts",
            displayName : "Use Interrupt",
            onChange    : onChangeUseInterrupts,
            description : 'Whether or not to use Interrupt mode.',
            hidden      : false,
            default     : true
        },
        {
            name        : "registerInterrupts",
            displayName : "Register Interrupt Handler",
            description : 'Whether or not to register interrupt handlers in the interrupt module.',
            hidden      : false,
            default     : false
        },
        {
            name        : "enableInterrupt",
            displayName : "Enable Interrupt",
            description : 'Enables interrupt source.',
            hidden      : false,
            default     : false
        },
        {
            name        : "interruptSource",
            displayName : "Interrupt Source",
            description : 'Select interrupt source.',
            hidden      : false,
            default     : [],
            minSelections: 0,
            options     : device_driverlib_peripheral.SENT_INT
        },
      ]
     }]);

config = config.concat([{
name: "GROUP_DMA",
displayName: "RTDMA Configuration",
collapsed: true,
config: [
    {
        name        : "useDMARX",
        displayName : "Use RTDMA for Receive",
        description : 'Whether or not to use DMA mode for RX.',
        hidden      : false,
        default     : false,
        onChange    : onChangeUseDMARX,
    },
    {
        name        : "DMARXInst",
        displayName : "RTDMA instance to be used for Receive",
        description : "Choose the RTDMA instance for the channel used for Receive",
        hidden      : true,
        default     : dma_instances[0].name,
        options     : dma_instances,
    },
]
}]);

config = config.concat([{
        name: "GROUP_SYS",
        displayName: "System Configuration",
        collapsed: true,
        config: []
    }]);



function onValidate(inst, validation) {

    if (inst.clockTickTime > 65535)
    {
        validation.logError(
            "Clock Cycle per Tick out of range, The maximum tick value for calibration sync error calculation is 65535",
            inst, "clockTickTime");
    }
    if (inst.gFilt > 255)
    {
        validation.logError(
            "Glitch filter out of range, Clock cycle should be in the range of 0-255", inst, "gFilt");
    }
    if (inst.timeOut > 4294967295)
    {
        validation.logError(
            "Maximum value supported for timeout is in 32 bit number", inst, "gFilt");
    }

    for(var channelIndex in device_driverlib_peripheral.SENT_CompareNumber){ 
        var currentCh = device_driverlib_peripheral.SENT_CompareNumber[channelIndex].name
        let chli = (currentCh).replace(/[^0-9]/g,'')
        if (inst["broadcastcmp" + chli.toString()+ "TT"] > 2047)
        {
            validation.logError(
                "Maximum value supported for toggle time is 2047",
                inst, "broadcastcmp" + chli.toString()+ "TT");
        }
    }
    for(var channelIndex in device_driverlib_peripheral.SENT_CompareNumber){ 
        var currentCh = device_driverlib_peripheral.SENT_CompareNumber[channelIndex].name
        let chli = (currentCh).replace(/[^0-9]/g,'')
        if (inst["sensor1cmp" + chli.toString()+ "TT"] > 2047)
        {
            validation.logError(
                "Maximum value supported for toggle time is 2047",
                inst, "sensor1cmp" + chli.toString()+ "TT");
        }
    }
    for(var channelIndex in device_driverlib_peripheral.SENT_CompareNumber){ 
        var currentCh = device_driverlib_peripheral.SENT_CompareNumber[channelIndex].name
        let chli = (currentCh).replace(/[^0-9]/g,'')
        if (inst["sensor2cmp" + chli.toString()+ "TT"] > 2047)
        {
            validation.logError(
                "Maximum value supported for toggle time is 2047",
                inst, "sensor2cmp" + chli.toString()+ "TT");
        }
    }
    for(var channelIndex in device_driverlib_peripheral.SENT_CompareNumber){ 
        var currentCh = device_driverlib_peripheral.SENT_CompareNumber[channelIndex].name
        let chli = (currentCh).replace(/[^0-9]/g,'')
        if (inst["sensor3cmp" + chli.toString()+ "TT"] > 2047)
        {
            validation.logError(
                "Maximum value supported for toggle time is 2047",
                inst, "sensor3cmp" + chli.toString()+ "TT");
        }
    }
    for(var channelIndex in device_driverlib_peripheral.SENT_CompareNumber){ 
        var currentCh = device_driverlib_peripheral.SENT_CompareNumber[channelIndex].name
        let chli = (currentCh).replace(/[^0-9]/g,'')
        if (inst["sensor4cmp" + chli.toString()+ "TT"] > 2047)
        {
            validation.logError(
                "Maximum value supported for toggle time is 2047",
                inst, "sensor4cmp" + chli.toString()+ "TT");
        }
    }
    
    for(var channelIndex in device_driverlib_peripheral.SENT_CompareNumber){ 
        var currentCh = device_driverlib_peripheral.SENT_CompareNumber[channelIndex].name
        let chli = (currentCh).replace(/[^0-9]/g,'')
        let chlj = chli-1;
        if (inst["sensor1cmp" + chli.toString()+ "TT"] != 0)
        {
            if (inst["sensor1cmp" + chli.toString()+ "TT"] < inst["sensor1cmp" + chlj.toString()+ "TT"])
            {
                validation.logWarning(
                    "Sensor1 CMP" + chli.toString() + " Toggle Time should be greater than Sensor1 CMP" + chlj.toString() + " Toggle Time",
                    inst, "sensor1cmp" + chli.toString()+ "TT");
            }
        }

    }
    for(var channelIndex in device_driverlib_peripheral.SENT_CompareNumber){ 
        var currentCh = device_driverlib_peripheral.SENT_CompareNumber[channelIndex].name
        let chli = (currentCh).replace(/[^0-9]/g,'')
        let chlj = chli-1;
        if (inst["sensor2cmp" + chli.toString()+ "TT"] != 0)
        {
            if (inst["sensor2cmp" + chli.toString()+ "TT"] < inst["sensor2cmp" + chlj.toString()+ "TT"])
            {
                validation.logWarning(
                    "Sensor2 CMP" + chli.toString() + " Toggle Time should be greater than Sensor2 CMP" + chlj.toString() + " Toggle Time",
                    inst, "sensor2cmp" + chli.toString()+ "TT");
            }
        }

    }
    for(var channelIndex in device_driverlib_peripheral.SENT_CompareNumber){ 
        var currentCh = device_driverlib_peripheral.SENT_CompareNumber[channelIndex].name
        let chli = (currentCh).replace(/[^0-9]/g,'')
        let chlj = chli-1;
        if (inst["sensor3cmp" + chli.toString()+ "TT"] != 0)
        {
            if (inst["sensor3cmp" + chli.toString()+ "TT"] < inst["sensor3cmp" + chlj.toString()+ "TT"])
            {
                validation.logWarning(
                    "Sensor3 CMP" + chli.toString() + " Toggle Time should be greater than Sensor3 CMP" + chlj.toString() + " Toggle Time",
                    inst, "sensor3cmp" + chli.toString()+ "TT");
            }
        }

    }
    for(var channelIndex in device_driverlib_peripheral.SENT_CompareNumber){ 
        var currentCh = device_driverlib_peripheral.SENT_CompareNumber[channelIndex].name
        let chli = (currentCh).replace(/[^0-9]/g,'')
        let chlj = chli-1;
        if (inst["sensor4cmp" + chli.toString()+ "TT"] != 0)
        {
            if (inst["sensor4cmp" + chli.toString()+ "TT"] < inst["sensor4cmp" + chlj.toString()+ "TT"])
            {
                validation.logWarning(
                    "Sensor4 CMP" + chli.toString() + " Toggle Time should be greater than Sensor4 CMP" + chlj.toString() + " Toggle Time",
                    inst, "sensor4cmp" + chli.toString()+ "TT");
            }
        }

    }
    for(var channelIndex in device_driverlib_peripheral.SENT_CompareNumber){ 
        var currentCh = device_driverlib_peripheral.SENT_CompareNumber[channelIndex].name
        let chli = (currentCh).replace(/[^0-9]/g,'')
        let chlj = chli-1;
        if (inst["broadcastcmp" + chli.toString()+ "TT"] != 0)
        {
            if (inst["broadcastcmp" + chli.toString()+ "TT"] < inst["broadcastcmp" + chlj.toString()+ "TT"])
            {
                validation.logWarning(
                    "Broadcast Channel CMP" + chli.toString() + " Toggle Time should be greater than Broadcast Channel CMP" + chlj.toString() + " Toggle Time",
                    inst, "broadcastcmp" + chli.toString()+ "TT");
            }
        }

    }

    if (inst.waitTime > 65535)
    {
        validation.logError(
            "Maximum value supported for wait time is 65535", inst, "waitTime");
    }

    if (inst.broadcastChPeriod > 2047)
    {
        validation.logError(
            "Maximum value supported for period is 2047", inst, "broadcastChPeriod");
    }

    for(var channelIndex in device_driverlib_peripheral.SENT_SensorNumber){ 
        var currentCh = device_driverlib_peripheral.SENT_SensorNumber[channelIndex].name
        let chli = (currentCh).replace(/[^0-9]/g,'')
        if (inst["sensor" + chli.toString()+ "Period"] > 2047)
        {
            validation.logError(
                "Maximum value supported for period is 2047", inst, "sensor" + chli.toString()+ "Period");
        }
    }

    for(var channelIndex in device_driverlib_peripheral.SENT_SensorNumber){ 
        var currentCh = device_driverlib_peripheral.SENT_SensorNumber[channelIndex].name
        let chli = (currentCh).replace(/[^0-9]/g,'')
        if (inst["sensor" + chli.toString()+ "Timeout"] > 4294967295)
        {
            validation.logError(
                "Maximum value supported for timeout is in 32 bit number", inst, "sensor" + chli.toString()+ "Timeout");
        }
    }

}


if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}    

var sentModule = {
    peripheralName: "SENT",
    displayName: "SENT",
    maxInstances: Common.peripheralCount("SENT"),
    defaultInstanceName: "mySENT",
    description: "SENT Peripheral",
    pinmuxRequirements    : Pinmux.sentPinmuxRequirements,
    config: config,
    moduleInstances: (inst) => {
        var ownedInstances = [];

        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("SENT", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
            pinmuxQualMod.args.qualMode = "GPIO_QUAL_SYNC";
        }
        ownedInstances = ownedInstances.concat(pinmuxQualMods)

        if (inst.useInterrupts && inst.registerInterrupts)
        {
            ownedInstances.push({
                name: "sentInt", 
                group : "GROUP_Interrupts",  
                displayName: "SENT Interrupt",
                moduleName: "/driverlib/interrupt.js",
                collapsed: true,
                args: {
            		$name : inst.$name + "_INT",
                    typeInterruptName : true,
                    pinmuxPeripheralModule :"sent",
                    driverlibInt: "INT_#",
                    interruptHandler : "INT_" + inst.$name + "_ISR",
                }
            });
        }
        //DMA
        if (inst.useDMARX)
        {
            let dmaInst = inst.DMARXInst.split('_')[0].toLowerCase()
            ownedInstances = ownedInstances.concat([
                {
                    name: "sentRXDMA",
                    group: "GROUP_DMA",    
                    displayName: "RX DMA",
                    moduleName: "/driverlib/" + dmaInst + ".js",
                    collapsed: true,
                    args: {
                        $name : inst.$name + "_RX_DMA",
                        burstSize : burstSizeMapping(inst.setFIFOLevel, inst)
                    },
                    requiredArgs: {
                        srcAddressLinked: inst.$name + "_RX_DMA_ADDRESS",
                        peripheralRXLinked: true,
                        databusWidthConfig: "DMA_CFG_READ_SIZE_32BIT",
                        writeDatasizeConfig: "DMA_CFG_WRT_SIZE_32BIT",
                        triggerSource: "DMA_TRIGGER_LINKED"
                    }
                },
            ])
        }
        ownedInstances = ownedInstances.concat([
            {
                name: "periphClock",
                group: "GROUP_SYS",
                displayName: "",
                moduleName: "/driverlib/perClock.js",
                collapsed: false,
                requiredArgs:{
                    pinmuxPeripheralModule : "sent",
                    peripheralInst: inst.$name
                }
            },
            {
                name: "periphConfig",
                group: "GROUP_SYS",
                displayName: "",
                moduleName: "/driverlib/perConfig.js",
                collapsed: false,
                requiredArgs:{
                    pinmuxPeripheralModule : "sent",
                    peripheralInst: inst.$name
                }
            },
        ])
        
        return ownedInstances;
    },
    templates: {
        boardc : "/driverlib/sent/sent.board.c.xdt",
        boardh : "/driverlib/sent/sent.board.h.xdt"
    },
    validate : onValidate,
};


if (sentModule.maxInstances <= 0)
{
    delete sentModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(sentModule)
    Pinmux.addPinMuxQualGroupToConfig(sentModule)
}

exports = sentModule;