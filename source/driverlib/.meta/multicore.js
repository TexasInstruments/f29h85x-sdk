const Common = system.getScript("/driverlib/Common.js");
let exportedModules = [];

if(Common.isContextCPU1())
{
    exportedModules = [
        "/driverlib/cpu2.js",
        "/driverlib/cpu3.js",
    ];
}
exports = {
    displayName: "Multi Core",
    topModules: exportedModules
};
