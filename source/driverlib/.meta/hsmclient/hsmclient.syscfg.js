let Common  = system.getScript("/driverlib/Common.js");
let soc     = system.getScript(`/driverlib/soc/drivers_${Common.getDeviceName().toLowerCase()}`);

function getModule() {

    let driverVer = soc.getDriverVer("hsmclient");

    return system.getScript(`/driverlib/hsmclient/${driverVer}/hsmclient_${driverVer}`);
}

exports = getModule();
