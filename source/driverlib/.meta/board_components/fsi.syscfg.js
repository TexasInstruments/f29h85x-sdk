
"use strict";
let Common   = system.getScript("/driverlib/Common.js");


let config = [

];

function _getPinResources(inst)
{
    let modRX;
    let pin;

    // modRX = system.getScript("/driverlib/fsirx.js");
    // modTX = system.getScript("/driverlib/fsirx.js");
    // pin = modRX._getPinResources(inst.fsirx.fsirx_d0Pin);
    // console.log(pin)

    return (pin);
}


/*
 *  ========= filterHardware ========
 *  param component - hardware object describing signals and
 *                    resources
 *
 *  returns Boolean indicating whether or not to allow the component to
 *           be assigned to an instance's $hardware config
 */
function filterHardware(component)
{
    if (component.type) {
        if (Common.typeMatches(component.type, ["FSI"])) {
            return (true);
        }
    }
    return (false);
}

/*
 *  ======== validate ========
 *  Validate this inst's configuration
 */
function validate(inst, validation)
{
    
}

/*
 *  ======== moduleInstances ========
 */
function moduleInstances(inst)
{
    
    let devInstanceRX;
    devInstanceRX = {
        displayName: "FSIRX",
        name: "fsiRx",
        description: "",
        moduleName: "/driverlib/fsirx.js",
        args: {
            $name: inst.$name + "_FSIRX"
        },
    };
    devInstanceRX.hardware = inst.$hardware;

    let devInstanceTX;
    devInstanceTX = {
        displayName: "FSITX",
        name: "fsiTx",
        description: "",
        moduleName: "/driverlib/fsitx.js",
        args: {
            $name: inst.$name + "_FSITX"
        },
    };
    devInstanceTX.hardware = inst.$hardware;
    return ([devInstanceRX, devInstanceTX]);
}

/*
 *  ======== onHardwareChanged ========
 *  Handle new hardware selection
 */
function onHardwareChanged(inst, ui)
{

}

/*
 *  ======== base ========
 *  Define the base properties and methods
 */
let base = {
    name: "FSI",
    peripheralName: "FSI",
    displayName: "FSI",
    description: "FSI",
    longDescription: "",
    defaultInstanceName: "myBoardFSI",

    config: config,
    validate: validate,
    moduleInstances: moduleInstances,
    filterHardware: filterHardware,
    _getPinResources: _getPinResources,

    /* make GUI changes in response to HW model changes */
    onHardwareChanged: onHardwareChanged,

    templates: {
        boardc: "/driverlib/board_components/fsi/fsi.board.c.xdt",
        boardh: "/driverlib/board_components/fsi/fsi.board.h.xdt"
    },
};

exports = base;
