let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_erad.js");

var config = [
    {
        name        : "instance",
        displayName : "OR Mask Instance",
        description : 'OR Mask Instance used',
        hidden      : false,
        default     : device_driverlib_peripheral.ERAD_Mask[4].name,
        options     : device_driverlib_peripheral.ERAD_Mask.slice(4,),
    },
    {
        name: "owner",
        displayName : "Owner",
        description : 'Owner of the ERAD module',
        hidden      : false,
		readOnly    : true,
        default     : "C29x",
        options     : [
            {name: "C29x"},
            {name: "Debugger"}
        ]
    },
    {
        name        : "busComptoOR",
        displayName : "Bus Comparators and Counters used",
        description : "Choose which bus comparators and counters to OR",
        hidden      : false,
        default     : [],
        minSelections: 0,
        options     : device_driverlib_peripheral.ERAD_INST
    },
    {
        name        : "interrupt",
        displayName : "Generate Interrupt on Count Match",
        description : "Whether or not to generate Interrupt when the COUNT matches the REF value",
        default     : false
    },
    {
        name        : "NMI",
        displayName : "Generate NMI on Match",
        description : "Whether or not to generate NMI when event matches occur",
        default     : false
    }
]

function onValidate(inst, validation)
{
    var usedORMaskInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedORMaskInsts.push(instance_obj.instance);
    }

    var duplicatesResult = Common.findDuplicates(usedORMaskInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ")
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The OR Mask Instance is already in use. Duplicates: " + allDuplicates,
            inst, "instance");
    }

    if(inst.interrupt && inst.NMI)
    {
        validation.logError("Cannot enable both interrupt and NMI for an event.", inst, "NMI")
    }
    if(inst.NMI)
    {
        validation.logInfo("This NMI signal is routed to the ESM. Configure the " + system.context + "_ERAD_NMI event in the Error Signaling Configuration block.", inst, "NMI");
    }
}

var eradORSubmodule = {
    displayName: "ERAD OR MASK",
    defaultInstanceName: "myERAD_OR_MASK",
    description: "ERAD Or Mask",
    config: config,
    validate: onValidate,
    templates: {
        boardc : "",
        boardh : ""
    },
};

exports = eradORSubmodule;
