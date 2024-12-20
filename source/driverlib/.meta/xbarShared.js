let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_xbar.js");

function onChangeStretchedPulseSource(inst, ui){
    if(inst.selectStretchedPulseSource){
        ui.selectStretchedPulseLength.hidden = false
    }
    else{
        ui.selectStretchedPulseLength.hidden = true
    }
}

function getXbarConfig(xbar){
    if(xbar != "OUTPUTXBAR" && xbar != "EPWMXBAR" && xbar != "CLBXBAR" && xbar != "MINDBXBAR" && xbar != "ICLXBAR"){
        throw new Error("INVALID XBAR")
    }

    let config = []
    
    var invertOutputBeforeLatchConfig = {
        name        : "invertOutputBeforeLatch",
        displayName : "Invert Output Before Latch",
        description : "Inverts the Xbar output before it is latched.",
        default     : false,
    }

    var selectLatchSignalSourceConfig = {
        name        : "latchMode",
        displayName : "Select Latched Signal as Output",
        description : "Selects the latched signal as output.",
        default     : false,
    }

    var selectStretchedPulseSourceConfig = {
        name        : "selectStretchedPulseSource",
        displayName : "Select Stretched Pulse as Output",
        description : "Selects the stretched pulse as the output.",
        default     : false,
        onChange    : onChangeStretchedPulseSource,
    }
    
    var selectStretchedPulseLengthConfig = {
        name        : "selectStretchedPulseLength",
        displayName : "Stretched Pulse Length",
        description : "Selects the stretched pulse length",
        default     : device_driverlib_peripheral.XBAR_OutputStretchLength[0].name,
        options     : device_driverlib_peripheral.XBAR_OutputStretchLength,
        hidden      : true,
    }

    var invertOutputConfig = {
        name        : "invertMode",
        displayName : "Invert XBAR Output",
        description : "Inverts the Xbar output",
        default     : false,
    }

    var useSourceSelectConfig = {
        name        : "useSourceSelect",
        displayName : "Select all Input sources",
        description : "Select all your input sources without knowing the group",
        default     : true,
        hidden      : true,
        deprecated  : true,
    }

    if(xbar == "OUTPUTXBAR"){
        config.push(invertOutputBeforeLatchConfig);
        config.push(selectLatchSignalSourceConfig);
        config.push(selectStretchedPulseSourceConfig);
        config.push(selectStretchedPulseLengthConfig);
    }
    
    config.push(useSourceSelectConfig);
    config.push(invertOutputConfig);

    return config
}

let globalConfig = []

globalConfig.push(
    {
        name        : "lockConfiguration",
        displayName : "Lock XBAR Configuration",
        description : "Locks the configuration of the XBAR",
        default     : false,
    }
);

var sharedModuleInstances = undefined;

var xbar_shared = {
    getXbarConfig : getXbarConfig,
    globalConfig : globalConfig,
};

exports = xbar_shared;


