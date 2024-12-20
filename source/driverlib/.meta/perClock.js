let Common   = system.getScript("/driverlib/Common.js");


/* Intro splash on GUI */
let longDescription = "";

function onChangeInt(inst, ui)
{
}


/* Array of CAN configurables that are common across device families */
let config = [
    {
        name        : "enable",
        displayName : "Enable Peripheral clock",
        default     : true,
    },
    {
        name        : "pinmuxPeripheralModule",
        hidden      : true,
        default     : ''
    },
    {
        name        : "peripheralInst",
        hidden      : true,
        default     : ''
    },
]

function onValidate(inst, validation) {

}


var perClockModule = {
    peripheralName: "PERCLOCK",
    displayName: "Peripheral Clock",
    description: "",
    config: config,
    templates: {
        boardc : "/driverlib/perClock/perClock.board.c.xdt",
        boardh : "/driverlib/perClock/perClock.board.h.xdt"
    },
    validate    : onValidate,
    uiAdd: "summary"
};

exports = perClockModule;