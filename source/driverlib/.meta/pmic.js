let Common      = system.getScript("/driverlib/Common.js");
let pmicExport  = {}

if (!Common.isAllocationSetupMode())
{
    let exportedModules =
    [
        "/driverlib/pmicconfig.js",
    ];

    pmicExport = {
        displayName : "Power Management IC (PMIC)",
        topModules  : exportedModules,
        templates   :
        [
            {
                name        : "/driverlib/pmic.c.xdt",
                outputPath  : "pmic.c",
                alwaysRun   : false
            }
        ]
    };
}

exports = pmicExport