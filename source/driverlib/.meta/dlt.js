// DLT module as a completely static module
// Used in non-RA mode

let dlt_shared = system.getScript("/driverlib/dlt_shared.js");

var dltModule = {
    peripheralName        : "DLT",
    displayName           : "DLT",
    defaultInstanceName   : "myDLT",
    description           : "Data Logger and Trace (DLT) module",
    longDescription       : dlt_shared.longDescription,
    filterHardware        : dlt_shared.filterHardware,
    moduleStatic          : {
        config            : dlt_shared.config.concat(dlt_shared.globalConfig),
        moduleInstances   : (inst) => dlt_shared.moduleInstances(inst, false, false),
        validate          : dlt_shared.onValidate
    },
    templates: {
     boardc : "/driverlib/dlt/dlt.board.c.xdt",
     boardh : "/driverlib/dlt/dlt.board.h.xdt"
    },
};


exports = dltModule;
