let Common  = system.getScript("/driverlib/Common.js");

function makeInstanceConfig() {
    let config                  = {};
    let staticConfigArr         = getStaticConfigArr();
    let defaultInstanceIndex    = getDefaultInstance();

    if(staticConfigArr.length == 0)
        return undefined;

    config.name         = "instance";
    config.displayName  = "Instance";
    config.description  = "Select Instance";
    config.default      = staticConfigArr[defaultInstanceIndex].name;
    config.options      = [];
    config.readOnly     = true;

    for (let i = 0; i < staticConfigArr.length; i++) {
        let option = {};

        option.name = staticConfigArr[i].name;
        config.options.push(option);
    }

    return config;
}

function getDefaultInstance() {
    return 2;
}

function getStaticConfigArr() {
    let staticConfigArr = [];

    for(let i = 0; i < 3; i++)
    {
        staticConfigArr.push(
            {
                name:                   `CPUTIMER${i}`,
                timerBaseAddr:          0x30218000 + i*0x1000,
                timerHwiIntNum:         6 + i,
                timerInputPreScaler:    1,
            }
        )
    }

    return staticConfigArr;
}

function getDefaultTimerClockSourceMhz(clkSource) {
    let clkSourceHz = Common.getSYSCLK()*1000000;

    return clkSourceHz;
}

exports = {
    getStaticConfigArr,
    getDefaultTimerClockSourceMhz,
    makeInstanceConfig,
};