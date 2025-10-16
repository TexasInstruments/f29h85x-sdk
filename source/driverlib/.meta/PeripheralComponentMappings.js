let Common      = system.getScript("/driverlib/Common.js");

const CATEGORY_ANALOG = "Analog";
const CATEGORY_COMS   = "Communication";
const CATEGORY_CONTROL= "Control";
const CATEGORY_SYSTEM = "System";
const CATEGORY_BOARD  = "Board Components"
const CATEGORY_SW     = "Software";
const CATEGORY_RTDMA  = "RTDMA";
const CATEGORY_XBAR   = "XBAR";

let supported_peripheralName_moduleFile = [

    { moduleCategory: CATEGORY_ANALOG ,  peripheralName : "ANALOG",         moduleFile : "/driverlib/analog.js"},

    { moduleCategory: CATEGORY_CONTROL,  peripheralName : "EPWM",           moduleFile : "/driverlib/epwm.js"},

    { moduleCategory: CATEGORY_XBAR,     peripheralName : "OUTPUTXBAR",     moduleFile : "/driverlib/outputxbar.js"},

    { moduleCategory: CATEGORY_COMS,     peripheralName : "LIN",            moduleFile : "/driverlib/lin.js"},
    { moduleCategory: CATEGORY_COMS,     peripheralName : "SPI",            moduleFile : "/driverlib/spi.js"},
    { moduleCategory: CATEGORY_COMS,     peripheralName : "UART",           moduleFile : "/driverlib/uart.js"},
    { moduleCategory: CATEGORY_COMS,     peripheralName : "I2C",            moduleFile : "/driverlib/i2c.js"},
    { moduleCategory: CATEGORY_COMS,     peripheralName : "MCAN",           moduleFile : "/driverlib/mcan.js"},
    { moduleCategory: CATEGORY_COMS,     peripheralName : "FSITX",          moduleFile : "/driverlib/fsitx.js"},
    { moduleCategory: CATEGORY_COMS,     peripheralName : "FSIRX",          moduleFile : "/driverlib/fsirx.js"},
    { moduleCategory: CATEGORY_COMS,     peripheralName : "SENT",           moduleFile : "/driverlib/sent.js"},
    { moduleCategory: CATEGORY_COMS,     peripheralName : "PMBUS",          moduleFile : "/driverlib/pmbus.js"},
    { moduleCategory: CATEGORY_COMS ,    peripheralName : "ECAT",           moduleFile : "/driverlib/ecat.js"},

    { moduleCategory: CATEGORY_SYSTEM ,  peripheralName : "EMIF1",          moduleFile : "/driverlib/emif1.js"},
];

let static_peripheralName_moduleFile = [

    { moduleCategory: CATEGORY_ANALOG,  peripheralName : "ASYSCTL",         moduleFile : "/driverlib/asysctl.js"},
    { moduleCategory: CATEGORY_ANALOG,  peripheralName : "ADC",             moduleFile : "/driverlib/adc.js"},

    { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "DCC",             moduleFile : "/driverlib/dcc.js"},
    { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "ERAD",            moduleFile : "/driverlib/erad.js"},
    { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "ESM CPU",         moduleFile : "/driverlib/esm_cpu.js"},
    { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "ESM SYS",         moduleFile : "/driverlib/esm_system.js"},
    { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "INTERRUPT",       moduleFile : "/driverlib/interrupt.js"},
    { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "IPC",             moduleFile : "/driverlib/ipc.js"},
    { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "TIMER",           moduleFile : "/driverlib/cputimer.js"},
    { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "GPIO",            moduleFile : "/driverlib/gpio.js"},
    { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "AIO",             moduleFile : "/driverlib/aio.js"},
    { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "CLOCKTREE",       moduleFile : "/driverlib/clocktree.js"},
    { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "WATCHDOG",        moduleFile : "/driverlib/watchdog.js"},
    { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "SYSCTL",          moduleFile : "/driverlib/sysctl.js"},
    { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "JTAG",            moduleFile : "/driverlib/jtag.js"},
    { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "XLCKOUT",         moduleFile : "/driverlib/xclkout.js"},
    { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "HSMCLIENT",       moduleFile : "/driverlib/hsmclient/hsmclient"},

    { moduleCategory: CATEGORY_CONTROL, peripheralName : "ECAP",            moduleFile : "/driverlib/ecap.js"},
    { moduleCategory: CATEGORY_CONTROL, peripheralName : "EQEP",            moduleFile : "/driverlib/eqep.js"},
    { moduleCategory: CATEGORY_CONTROL, peripheralName : "SYNC",            moduleFile : "/driverlib/sync.js"},
    { moduleCategory: CATEGORY_CONTROL, peripheralName : "SD",              moduleFile : "/driverlib/sd.js"},

    { moduleCategory: CATEGORY_XBAR,    peripheralName : "XBARFLAGS",       moduleFile : "/driverlib/xbar_flags.js"},
    { moduleCategory: CATEGORY_XBAR,    peripheralName : "CLBXBAR",         moduleFile : "/driverlib/clbxbar.js"},
    { moduleCategory: CATEGORY_XBAR,    peripheralName : "EPWMXBAR",        moduleFile : "/driverlib/epwmxbar.js"},
    { moduleCategory: CATEGORY_XBAR,    peripheralName : "ICLXBAR",         moduleFile : "/driverlib/iclxbar.js"},
    { moduleCategory: CATEGORY_XBAR,    peripheralName : "INPUTXBAR INPUT", moduleFile : "/driverlib/inputxbar_input.js"},
    { moduleCategory: CATEGORY_XBAR,    peripheralName : "MINDBXBAR",       moduleFile : "/driverlib/mindbxbar.js"},

    { moduleCategory: CATEGORY_RTDMA,   peripheralName : "RTDMA1",          moduleFile : "/driverlib/rtdma1.js"},
    { moduleCategory: CATEGORY_RTDMA,   peripheralName : "RTDMA2",          moduleFile : "/driverlib/rtdma2.js"},
    { moduleCategory: CATEGORY_RTDMA,   peripheralName : "RTDMA1 MPU",      moduleFile : "/driverlib/rtdma1_mpu.js"},
    { moduleCategory: CATEGORY_RTDMA,   peripheralName : "RTDMA2 MPU",      moduleFile : "/driverlib/rtdma2_mpu.js"},

    { moduleCategory: CATEGORY_BOARD,   peripheralName : "",                moduleFile : "/driverlib/board_components/led"},
    { moduleCategory: CATEGORY_BOARD,   peripheralName : "",                moduleFile : "/driverlib/board_components/swtch"},
]

let device_specific_modules = [
    { moduleCategory: CATEGORY_ANALOG , devices : ["F29H85x"],  peripheralName : "ADCSafetyChecker",    moduleFile : "/driverlib/adcsafetychecker.js"},
    { moduleCategory: CATEGORY_ANALOG , devices : ["F29H85x"],  peripheralName : "CMPSS",               moduleFile : "/driverlib/cmpss.js"},
    { moduleCategory: CATEGORY_ANALOG , devices : ["F29H85x"],  peripheralName : "DAC",                 moduleFile : "/driverlib/dac.js"},

    { moduleCategory: CATEGORY_CONTROL, devices : ["F29H85x"],  peripheralName : "CLB",                 moduleFile : "/driverlib/clb.js"},

    { moduleCategory: CATEGORY_BOARD  , devices : ["F29H85x"],  peripheralName : "FSI",                 moduleFile : "/driverlib/board_components/fsi"},
    { moduleCategory: CATEGORY_BOARD  , devices : ["F29H85x"],  peripheralName : "FLASH",               moduleFile : "/driverlib/flash.js"},
]

let cpu2_unavailable_peripherals = {
    "F29H85x" : [
        { peripheralName: "ANALOG", moduleFile : "/driverlib/analog.js"},
        { peripheralName: "ASYSCTL", moduleFile : "/driverlib/asysctl.js" },
        { peripheralName: "CLOCKTREE", moduleFile : "/driverlib/clocktree.js"},
        { peripheralName: "SYNC", moduleFile : "/driverlib/sync.js" },
        { peripheralName: "INPUTXBAR INPUT", moduleFile : "/driverlib/inputxbar_input.js"},
        { peripheralName: "OUTPUTXBAR", moduleFile : "/driverlib/outputxbar.js" },
        { peripheralName: "EPWMXBAR", moduleFile : "/driverlib/epwmxbar.js"},
        { peripheralName: "CLBXBAR", moduleFile : "/driverlib/clbxbar.js"},
        { peripheralName: "ICLXBAR", moduleFile : "/driverlib/iclxbar.js"},
        { peripheralName: "MINDBXBAR", moduleFile : "/driverlib/mindbxbar.js"},
        { peripheralName: "XBARFLAGS", moduleFile : "/driverlib/xbar_flags.js"},
        { peripheralName: "FLASH", moduleFile : "/driverlib/flash.js"},
        { peripheralName: "XLCKOUT", moduleFile : "/driverlib/xclkout.js"},
        { peripheralName: "JTAG", moduleFile : "/driverlib/jtag.js"},
    ],
}

let cpu3_unavailable_peripherals = {
    "F29H85x" : [
        { peripheralName: "ANALOG", moduleFile : "/driverlib/analog.js"},
        { peripheralName: "ASYSCTL", moduleFile : "/driverlib/asysctl.js" },
        { peripheralName: "CLOCKTREE", moduleFile : "/driverlib/clocktree.js"},
        { peripheralName: "SYNC", moduleFile : "/driverlib/sync.js" },
        { peripheralName: "INPUTXBAR INPUT", moduleFile : "/driverlib/inputxbar_input.js"},
        { peripheralName: "OUTPUTXBAR", moduleFile : "/driverlib/outputxbar.js" },
        { peripheralName: "EPWMXBAR", moduleFile : "/driverlib/epwmxbar.js"},
        { peripheralName: "CLBXBAR", moduleFile : "/driverlib/clbxbar.js"},
        { peripheralName: "ICLXBAR", moduleFile : "/driverlib/iclxbar.js"},
        { peripheralName: "MINDBXBAR", moduleFile : "/driverlib/mindbxbar.js"},
        { peripheralName: "XBARFLAGS", moduleFile : "/driverlib/xbar_flags.js"},
        { peripheralName: "FLASH", moduleFile : "/driverlib/flash.js"},
        { peripheralName: "XLCKOUT", moduleFile : "/driverlib/xclkout.js"},
        { peripheralName: "JTAG", moduleFile : "/driverlib/jtag.js"},
    ],
}

let ra_setup_unavailable_modules = {
    "F29H85x" : [
        { peripheralName: "INTERRUPT",  moduleFile : "/driverlib/interrupt.js"},
        { peripheralName: "TIMER",      moduleFile : "/driverlib/cputimer.js"},
        { peripheralName: "ERAD",       moduleFile : "/driverlib/erad.js"},
        { peripheralName: "ESM CPU",    moduleFile : "/driverlib/esm_cpu.js"},
        { peripheralName: "WATCHDOG",   moduleFile : "/driverlib/watchdog.js"},
        { peripheralName: "IPC",        moduleFile : "/driverlib/ipc.js"},
        { peripheralName: "HSMCLIENT",  moduleFile : "/driverlib/hsmclient/hsmclient"},
        { peripheralName: "FSI",        moduleFile : "/driverlib/board_components/fsi"},
        { peripheralName: "ADCSafetyChecker", moduleFile : "/driverlib/adcsafetychecker.js"},   
    ],
}

let ra_configure_unavailable_modules = {
    "F29H85x" : [
        { peripheralName: "CLOCKTREE",  moduleFile : "/driverlib/clocktree.js"},        // all clocktree settings are fixed by RA
    ],
}

if(Common.isAllocationOff())
{
    static_peripheralName_moduleFile.push(
        { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "DLT", moduleFile : "/driverlib/dlt.js"},
    )
}
else
{
    static_peripheralName_moduleFile.push(
        { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "DLT", moduleFile : "/driverlib/dlt_inst.js"},
    )
}

if(Common.isAllocationOff())
{
    cpu2_unavailable_peripherals["F29H85x"].push(
        { peripheralName: "AIO",    moduleFile : "/driverlib/aio.js"},
        { peripheralName: "GPIO",   moduleFile : "/driverlib/gpio.js"},
    )

    cpu3_unavailable_peripherals["F29H85x"].push(
        { peripheralName: "AIO",    moduleFile : "/driverlib/aio.js"},
        { peripheralName: "GPIO",   moduleFile : "/driverlib/gpio.js"},
    )
}

exports =
{
    supported_peripheralName_moduleFile : supported_peripheralName_moduleFile,
    static_peripheralName_moduleFile    : static_peripheralName_moduleFile,
    device_specific_modules             : device_specific_modules,
    ra_setup_unavailable_modules        : ra_setup_unavailable_modules,
    ra_configure_unavailable_modules    : ra_configure_unavailable_modules,
    cpu2_unavailable_peripherals        : cpu2_unavailable_peripherals,
    cpu3_unavailable_peripherals        : cpu3_unavailable_peripherals,
    CATEGORY_ANALOG,
    CATEGORY_COMS,
    CATEGORY_CONTROL,
    CATEGORY_SYSTEM,
    CATEGORY_BOARD,
    CATEGORY_SW,
    CATEGORY_RTDMA,
    CATEGORY_XBAR,
}