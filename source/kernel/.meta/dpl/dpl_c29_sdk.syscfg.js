let Common      = system.getScript("/driverlib/Common.js");
let soc         = system.getScript(`/kernel/dpl/dpl_c29_sdk_${Common.getDeviceName().toLowerCase()}`);
let references  = system.getScript("/kernel/dpl/dpl_c29_sdk_references.js");

exports = {
    displayName: "TI Driver Porting Layer (DPL)",
    templates: [
        {
            name:       "/kernel/dpl/dpl_config.c.xdt",
            outputPath: "ti_dpl_config.c",
            alwaysRun:  true,
        },
        {
            name:       "/kernel/dpl/dpl_config.h.xdt",
            outputPath: "ti_dpl_config.h",
            alwaysRun:  true,
        },
    ],
    references: references.componentReferences,
    topModules: soc.getTopModules(),
};
