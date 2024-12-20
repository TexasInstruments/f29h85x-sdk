let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");
let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_clockconfig.js");

/* Intro splash on GUI */
let longDescription = "";


/* Array of Clock configurables */
let config = [
    {
        name: "xclkOutSource",
        displayName : "External Clock Output (XCLKOUT) Source",
        default     : device_driverlib_peripheral.SysCtl_XClkSource[0].name,
        options     : device_driverlib_peripheral.SysCtl_XClkSource
    },
    {
        name: "xclkOutDiv",
        displayName : "External Clock Output (XCLKOUT) Divider",
        default     : "SYSCTL_XCLKOUT_DIV_8",
        options     : device_driverlib_peripheral.SysCtl_XClkDivider
    },
];


function onValidate(inst, validation) 
{

}


function filterHardware(component)
{
}

var clockModule = {
    peripheralName: "XCLKOUT",
    displayName: "XCLKOUT",
    maxInstances: 1,
    description: "XCLKOUT",
    defaultInstanceName: "myXCLKOUT",
    filterHardware : filterHardware,

    config: config,
    validate    : onValidate,
    pinmuxRequirements    : Pinmux.xclkoutPinmuxRequirements,

    templates: {
        boardc : "/driverlib/sysctl/xclkout.board.c.xdt",
    },

};




exports = clockModule;