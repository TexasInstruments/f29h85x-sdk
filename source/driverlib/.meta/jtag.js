let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_clockconfig.js");

/* Intro splash on GUI */
let longDescription = "";


/* Array of Clock configurables */
let config = [

];


function onValidate(inst, validation) 
{

}


function filterHardware(component)
{
}

var clockModule = {
    peripheralName: "JTAG",
    displayName: "JTAG",
    maxInstances: 1,
    description: "JTAG",
    filterHardware : filterHardware,

    moduleStatic : {
        config: config,
        validate    : onValidate,
        pinmuxRequirements    : Pinmux.jtagPinmuxRequirements,
    },

};




exports = clockModule;