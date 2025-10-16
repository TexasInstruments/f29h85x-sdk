// DLT module as an instanceable module with 1 instance. The Frame selection is part of staticConfig.
// Used in RA mode

let Common   = system.getScript("/driverlib/Common.js");

let dlt_shared = system.getScript("/driverlib/dlt_shared.js");


var dltModule = {
    peripheralName        : "DLT",
    displayName           : "DLT",
    defaultInstanceName   : "myDLT",
    description           : "Data Logger and Trace (DLT) module",
    longDescription       : dlt_shared.longDescription,
    filterHardware        : dlt_shared.filterHardware,
    moduleStatic          : {
        config            : dlt_shared.globalConfig,
        moduleInstances   : (inst) => dlt_shared.moduleInstances(inst, true, true),
        shouldBeAllocatedAsResource: true,
    },
    templates: {
     boardc : "/driverlib/dlt/dlt.board.c.xdt",
     boardh : "/driverlib/dlt/dlt.board.h.xdt"
    },
};

if(!Common.isAllocationSetupMode())
{
    dltModule.maxInstances      = 1;
    dltModule.moduleInstances   = (inst) => dlt_shared.moduleInstances(inst, true, false);
    dltModule.validate          = dlt_shared.onValidate;
    dltModule.config            = Common.filterConfigsIfInSetupMode(dlt_shared.config);
    dltModule.uiAdd             = "staticAndInstance";
}

exports = dltModule;
