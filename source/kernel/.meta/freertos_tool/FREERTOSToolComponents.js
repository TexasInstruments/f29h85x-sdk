let references = system.getScript("/kernel/freertos_tool/FREERTOSReferences.js");
var freertos_export = {}

if ([ "F29H85x"].includes(system.deviceData.device))
{
    freertos_export = {
        displayName: "FreeRTOS Configuration Tool",
        templates:
        [
            {
                name      : "/kernel/freertos_tool/templates/c2000_freertos.c.xdt",
                outputPath: "c2000_freertos.c",
            },
            {
                name      : "/kernel/freertos_tool/templates/c2000_freertos.h.xdt",
                outputPath: "c2000_freertos.h",
            },
            {
                name      : "/kernel/freertos_tool/templates/c2000_freertos_source.c.xdt",
                outputPath: "c2000_freertos_source.c",
            },
            {
                name      : "/kernel/freertos_tool/templates/c2000_freertos_asm.asm.xdt",
                outputPath: "c2000_freertos_asm.asm",
            },
            {
                name      : "/kernel/freertos_tool/templates/FreeRTOSConfig.h.xdt",
                outputPath: "FreeRTOSConfig.h",
            },
            {
                name      : "/kernel/freertos_tool/templates/c2000_freertos.cmd.genlibs.xdt",
                outputPath: "c2000_freertos.cmd.genlibs",
            },
            {
                name      : "/kernel/freertos_tool/templates/c2000_freertos.opt.xdt",
                outputPath: "c2000_freertos.opt",
            },
            {
                name      : "/driverlib/rov/syscfg_c.rov.xs.xdt",
                outputPath: "syscfg_c.rov.xs",
            },
        ],
        references: references.componentReferences,
        topModules:
        [
            {
                displayName: "FreeRTOS Configuration",
                description: "FreeRTOS gets configured here",
                modules:
                [
                    "/kernel/freertos_tool/FREERTOS",
                ]
            }
        ]
    }
}

exports = freertos_export