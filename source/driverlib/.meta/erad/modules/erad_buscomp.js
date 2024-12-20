let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_erad.js");

let ADDRESS_INPUT_MODE = [
    {name: "MANUAL", displayName: "Manual"},
    {name: "CODE", displayName: "Variable/Function Name"}
]

function onChangeAddressInputMode(inst, ui)
{
    ui.ebcRefCodeName.hidden = (inst.ebcAddressInputMode == ADDRESS_INPUT_MODE[0].name)
    ui.ebcRef.hidden = !(inst.ebcAddressInputMode == ADDRESS_INPUT_MODE[0].name)
    ui.ebcMask.hidden = !((inst.ebcMode == device_driverlib_peripheral.ERAD_BusComp_Comp_Mode[0].name) &&
                            (!ui.ebcMode.hidden))
}

function onChangeSpselEnable(inst, ui)
{
    ui.spsel.hidden = !inst.spselEnable
}

var config = [
    {
        name        : "instance",
        displayName : "EBC Instance",
        description : 'Enhanced Bus Comparator (EBC) Instance used',
        hidden      : false,
        default     : device_driverlib_peripheral.ERAD_BusCompInstance[0].name,
        options     : device_driverlib_peripheral.ERAD_BusCompInstance,
    },
    {
        name        : "owner",
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
        name        : "ebcBusSel",
        displayName : "Address Monitoring Type",
        description : 'Type of address monitoring for the EBC.',
        hidden      : false,
        default     : device_driverlib_peripheral.ERAD_BusComp_Bus_Select[0].name,
        options     : device_driverlib_peripheral.ERAD_BusComp_Bus_Select,
        onChange    : onChangeAddressInputMode
    },
    {
        name        : "ebcAddressInputMode",
        displayName : "Address Input Type",
        description : 'Type of address input.',
        hidden      : false,
        default     : ADDRESS_INPUT_MODE[0].name,
        options     : ADDRESS_INPUT_MODE,
        onChange    : onChangeAddressInputMode
    },
    {
        name        : "ebcRefCodeName",
        displayName : "Void pointer to Function/Variable",
        description : 'Address for the EBC to monitor.',
        hidden      : true,
        default     : "",
    },
    {
        name        : "ebcRef",
        displayName : "Reference Address",
        description : 'Address for the EBC to monitor.',
        hidden      : false,
        default     : 0,
    },
    {
        name        : "ebcMode",
        displayName : "Reference Address Compare Type",
        description : "Use a mask or a select a comparison type for the reference address",
        hidden      : false,
        default     : device_driverlib_peripheral.ERAD_BusComp_Comp_Mode[0].name,
        options     : device_driverlib_peripheral.ERAD_BusComp_Comp_Mode,
        onChange    : onChangeAddressInputMode

    },
    {
        name        : "ebcMask",
        displayName : "Address Mask",
        description : 'Address mask applied to the EBC_REF address.',
        hidden      : false,
        default     : 0,
    },
    {
        name        : "haltCPU",
        displayName : "Halt CPU on Match",
        description : "Whether or not to halt the CPU when the EBC matches the REF value",
        default     : false
    },
    {
        name        : "interrupt",
        displayName : "Generate Interrupt on Match",
        description : "Whether or not to generate Interrupt when the EBC matches the REF value",
        default     : false
    },
    {
        name        : "NMI",
        displayName : "Generate NMI on Match",
        description : "Whether or not to generate NMI when the EBC matches the REF value",
        default     : false
    },
    {
        name        : "stackQual",
        displayName : "Enable stack access qualifier",
        description : "Enable to additionally consider the corresponding stack access qualifier to generate a match.",
        default     : false
    },
    {
        name        : "spselEnable",
        displayName : "Enable SPSEL match",
        description : "Enable to additionally consider the SPSEL match to generate a match.",
        default     : false,
        onChange    : onChangeSpselEnable
    },
    {
        name        : "spsel",
        displayName : "Stack Pointer select (SPSEL) value",
        description : "Stack pointer Select value to be used for SPSEL match.",
        hidden      : true,
        default     : 0,
    },
];

function onValidate(inst, validation)
{
    var usedBusCompInsts = [];
    for (var instance_index in inst.$module.$instances)
    {
        var instance_obj = inst.$module.$instances[instance_index];
        usedBusCompInsts.push(instance_obj.instance);
    }

    var duplicatesResult = Common.findDuplicates(usedBusCompInsts)

    if (duplicatesResult.duplicates.length != 0)
    {
        var allDuplicates = "";
        for (var duplicateNamesIndex in duplicatesResult.duplicates)
        {
            allDuplicates = allDuplicates + Common.stringOrEmpty(allDuplicates, ", ")
                            + duplicatesResult.duplicates[duplicateNamesIndex];
        }
        validation.logError(
            "The EBC Instance is already in use. Duplicates: " + allDuplicates,
            inst, "instance");
    }

    if(inst.interrupt && inst.NMI)
    {
        validation.logError("Cannot enable both interrupt and NMI for an event.", inst, "NMI")
    }
    if ((inst.ebcMask > 0xFFFFFFFFFFFFFFFF) || (inst.ebcMask < 0) || !Number.isInteger(inst.ebcMask))
    {
        validation.logError("The bus comparator mask value must be an integer between 0 and 0xFFFFFFFFFFFFFFFF", inst, "ebcMask");
    }
    if ((inst.ebcRef > 0xFFFFFFFFFFFFFFFF) || (inst.ebcRef < 0) || !Number.isInteger(inst.ebcRef))
    {
        validation.logError("The bus comparator reference value must be an integer between 0 and 0xFFFFFFFFFFFFFFFF", inst, "ebcRef");
    }
    if ((inst.spsel > 0xF) || (inst.spsel < 0) || !Number.isInteger(inst.spsel))
    {
        validation.logError("The Stack pointer select value must be an integer between 0 and 0xF", inst, "spsel");
    }
    if(inst.NMI)
    {
        validation.logInfo("This NMI signal is routed to the ESM. Configure the " + system.context + "_ERAD_NMI event in the Error Signaling Configuration block.", inst, "NMI");
    }
    if(inst.stackQual)
    {
        validation.logInfo("This is relevant only for data read and data write address comparison.", inst, "stackQual");
    }
    if(inst.spselEnable)
    {
        validation.logInfo("This is relevant only for data read and data write address comparison.", inst, "spselEnable");
    }
}

var eradEBCSubmodule = {
    displayName: "ERAD BUS COMPARATOR",
    defaultInstanceName: "myERAD_BUSCOMP",
    description: "ERAD Enhanced Bus Comparator (EBC)",
    config: config,
    validate: onValidate,
    templates: {
        boardc : "",
        boardh : ""
    },
};


exports = eradEBCSubmodule;