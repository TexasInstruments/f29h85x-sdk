let Common   = system.getScript("/driverlib/Common.js");


/* Intro splash on GUI */
let longDescription = "";

function onChangeRemoveCpuSelStandbyDbgHalt(inst, ui)
{
    if(inst.removeCpuSelStandbyDbgHalt){
        ui.cpuSel.hidden = true;
        inst.standbyEn = false;
        ui.standbyEn.hidden = true;
        inst.dbgHaltEn = false;
        ui.dbgHaltEn.hidden = true;
    }
    else{
        ui.cpuSel.hidden = false;
        inst.standbyEn = true;
        ui.standbyEn.hidden = false;
        inst.dbgHaltEn = true;
        ui.dbgHaltEn.hidden = false;
    }
}

function onChangeRemoveFrameSel(inst, ui)
{
    if(inst.removeFrameSel){
        ui.removeFrameSel.hidden = true;
    }
    else{
        ui.removeFrameSel.hidden = false;
    }
}

/* Array of CAN configurables that are common across device families */
let config = [
    {
        name        : "cpuSel",
        displayName : "Select CPU",
        default     : system.context,
        options     : [
            {name: "CPU1"},
            {name: "CPU2"},
            {name: "CPU3"},
        ],
        readOnly    : true
    },
    {
        name        : "frameSel",
        displayName : "Select Peripheral Frame",
        default     : 'FRAME0',
        options     : [
            {name: "FRAME0"},
            {name: "FRAME1"},
            {name: "FRAME2"},
            {name: "FRAME3"},
        ]
    },
    {
        name        : "removeCpuSelStandbyDbgHalt",
        displayName : "Remove CPU select, Gate peripheral clock and DBGHALT signal configurations",
        hidden      : true,
        default     : false,
        onChange    : onChangeRemoveCpuSelStandbyDbgHalt,
    },
    {
        name        : "removeFrameSel",
        displayName : "Remove Frame select configuration",
        hidden      : true,
        default     : false,
        onChange    : onChangeRemoveFrameSel,
    },
    {
        name        : "standbyEn",
        displayName : "Gate peripheral clock when CPU enters Standby mode",
        default     : true,
    },
    {
        name        : "dbgHaltEn",
        displayName : "Activate Peripheral DBGHALT signal when CPU enters HALT mode",
        description : 'The interrupt handler function name',
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
];

function onValidate(inst, validation) {
    if (!Common.isContextCPU1()) 
    {
        validation.logInfo("The code for the configurations made here is generated in CPU1 context.", inst);
    }
}


var perConfigModule = {
    peripheralName: "PERCONFIG",
    displayName: "Peripheral config",
    description: "",
    config: config,
    templates: {
        boardc : "/driverlib/perConfig/perConfig.board.c.xdt",
        boardh : "/driverlib/perConfig/perConfig.board.h.xdt"
    },
    validate    : onValidate,
    uiAdd: "summary"
};

exports = perConfigModule;