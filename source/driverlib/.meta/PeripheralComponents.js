let Common   = system.getScript("/driverlib/Common.js");
let references = system.getScript("/driverlib/PeripheralComponentsReferences.js");

let CATEGORY_ANALOG = "Analog";
let CATEGORY_COMS = "Communication";
let CATEGORY_CONTROL = "Control";
let CATEGORY_SYSTEM = "System";
let CATEGORY_BOARD = "Board Components"
let CATEGORY_SW = "Software";
let CATEGORY_RTDMA = "RTDMA";
let CATEGORY_XBAR = "XBAR";

let CATEGORY_LIST = [
    CATEGORY_ANALOG,
    CATEGORY_COMS,
    CATEGORY_CONTROL,
    CATEGORY_SYSTEM,
    CATEGORY_BOARD,
    CATEGORY_SW,
    CATEGORY_RTDMA,
    CATEGORY_XBAR,
]

var supported_modules_analog  = [];
var supported_modules_coms    = [];
var supported_modules_system  = [];
var supported_modules_control = [];
var supported_modules_board   = [];
var supported_modules_sw      = [];
var supported_modules_rtdma   = [];
var supported_modules_xbar    = [];

var supported_modules = {};
supported_modules[CATEGORY_ANALOG]  = supported_modules_analog
supported_modules[CATEGORY_COMS]    = supported_modules_coms
supported_modules[CATEGORY_SYSTEM]  = supported_modules_system
supported_modules[CATEGORY_CONTROL] = supported_modules_control
supported_modules[CATEGORY_BOARD]   = supported_modules_board
supported_modules[CATEGORY_SW]      = supported_modules_sw
supported_modules[CATEGORY_RTDMA]   = supported_modules_rtdma
supported_modules[CATEGORY_XBAR]    = supported_modules_xbar

var supported_peripheralName_moduleFile = [

    { moduleCategory: CATEGORY_ANALOG ,  peripheralName : "ANALOG", moduleFile : "/driverlib/analog.js"},

    { moduleCategory: CATEGORY_CONTROL,  peripheralName : "EPWM",           moduleFile : "/driverlib/epwm.js"},

    { moduleCategory: CATEGORY_XBAR,     peripheralName : "OUTPUTXBAR",     moduleFile : "/driverlib/outputxbar.js"},

    { moduleCategory: CATEGORY_COMS,     peripheralName : "LIN",            moduleFile : "/driverlib/lin.js"},
    { moduleCategory: CATEGORY_COMS   ,  peripheralName : "SD",             moduleFile : "/driverlib/sd.js"},
    { moduleCategory: CATEGORY_COMS,     peripheralName : "SPI",            moduleFile : "/driverlib/spi.js"},
    { moduleCategory: CATEGORY_COMS,     peripheralName : "UART",           moduleFile : "/driverlib/uart.js"},
    { moduleCategory: CATEGORY_COMS,     peripheralName : "I2C",            moduleFile : "/driverlib/i2c.js"},
    { moduleCategory: CATEGORY_COMS,     peripheralName : "MCAN",           moduleFile : "/driverlib/mcan.js"},
    { moduleCategory: CATEGORY_COMS,     peripheralName : "FSITX",          moduleFile : "/driverlib/fsitx.js"},
    { moduleCategory: CATEGORY_COMS,     peripheralName : "FSIRX",          moduleFile : "/driverlib/fsirx.js"},
    { moduleCategory: CATEGORY_COMS,     peripheralName : "SENT",           moduleFile : "/driverlib/sent.js"},
    { moduleCategory: CATEGORY_COMS,     peripheralName : "PMBUS",           moduleFile : "/driverlib/pmbus.js"},
];


var static_peripheralName_moduleFile = [

    {moduleCategory: CATEGORY_ANALOG ,  peripheralName : "ASYSCTL",         moduleFile : "/driverlib/asysctl.js"},
    { moduleCategory: CATEGORY_ANALOG , peripheralName : "ADC",             moduleFile : "/driverlib/adc.js"},

    { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "DCC",             moduleFile : "/driverlib/dcc.js"},
    { moduleCategory: CATEGORY_SYSTEM,  peripheralName : "DLT",             moduleFile : "/driverlib/dlt.js"},
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

var device_specific_modules = [
    { moduleCategory: CATEGORY_ANALOG , devices : ["F29H85x"], peripheralName : "ADCSafetyChecker", moduleFile : "/driverlib/adcsafetychecker.js"},
    { moduleCategory: CATEGORY_CONTROL, devices : ["F29H85x"], peripheralName : "CLB", moduleFile : "/driverlib/clb.js"},
    { moduleCategory: CATEGORY_ANALOG , devices : ["F29H85x"], peripheralName : "CMPSS", moduleFile : "/driverlib/cmpss.js"},
    { moduleCategory: CATEGORY_ANALOG , devices : ["F29H85x"], peripheralName : "DAC", moduleFile : "/driverlib/dac.js"},
    { moduleCategory: CATEGORY_BOARD  , devices : ["F29H85x"], peripheralName : "FSI", moduleFile : "/driverlib/board_components/fsi"},
    { moduleCategory: CATEGORY_BOARD  , devices : ["F29H85x"], peripheralName : "FLASH", moduleFile : "/driverlib/flash.js"},
]

if (Common.onlyPinmux())
{
    static_peripheralName_moduleFile = []
    device_specific_modules = []
}

var cpu2_unavailable_peripherals = {
    "F29H85x" : [
        { peripheralName: "AIO", moduleFile : "/driverlib/aio.js"},
        { peripheralName: "GPIO", moduleFile : "/driverlib/gpio.js"},
        { peripheralName: "INPUTXBAR INPUT", moduleFile : "/driverlib/inputxbar_input.js"},
        { peripheralName: "OUTPUTXBAR", moduleFile : "/driverlib/outputxbar.js" },
        { peripheralName: "EPWMXBAR", moduleFile : "/driverlib/epwmxbar.js"},
        { peripheralName: "CLBXBAR", moduleFile : "/driverlib/clbxbar.js"},
        { peripheralName: "ICLXBAR", moduleFile : "/driverlib/iclxbar.js"},
        { peripheralName: "MINDBXBAR", moduleFile : "/driverlib/mindbxbar.js"},
        { peripheralName: "XBARFLAGS", moduleFile : "/driverlib/xbar_flags.js"},
    ],
}

var cpu3_unavailable_peripherals = {
    "F29H85x" : [
        { peripheralName: "AIO", moduleFile : "/driverlib/aio.js"},
        { peripheralName: "GPIO", moduleFile : "/driverlib/gpio.js"},
        { peripheralName: "INPUTXBAR INPUT", moduleFile : "/driverlib/inputxbar_input.js"},
        { peripheralName: "OUTPUTXBAR", moduleFile : "/driverlib/outputxbar.js" },
        { peripheralName: "EPWMXBAR", moduleFile : "/driverlib/epwmxbar.js"},
        { peripheralName: "CLBXBAR", moduleFile : "/driverlib/clbxbar.js"},
        { peripheralName: "ICLXBAR", moduleFile : "/driverlib/iclxbar.js"},
        { peripheralName: "MINDBXBAR", moduleFile : "/driverlib/mindbxbar.js"},
        { peripheralName: "XBARFLAGS", moduleFile : "/driverlib/xbar_flags.js"},
    ],
}

for (var periphName_moduleFile_index in supported_peripheralName_moduleFile)
{
    if (Common.peripheralCount(
        supported_peripheralName_moduleFile[periphName_moduleFile_index].peripheralName) > 0)
    {
        supported_modules[supported_peripheralName_moduleFile[periphName_moduleFile_index].moduleCategory].
            push(supported_peripheralName_moduleFile[periphName_moduleFile_index].moduleFile)
    }

}

for (var periphName_moduleFile_index in static_peripheralName_moduleFile)
{
    supported_modules[static_peripheralName_moduleFile[periphName_moduleFile_index].moduleCategory].
        push(static_peripheralName_moduleFile[periphName_moduleFile_index].moduleFile)
}


for (var device_specific_modules_index in device_specific_modules)
{
    if (device_specific_modules[device_specific_modules_index].
        devices.includes(Common.getDeviceName()))
    {
        supported_modules[device_specific_modules[device_specific_modules_index].moduleCategory].
            push(device_specific_modules[device_specific_modules_index].moduleFile)
    }
}

var views = []
if(Common.getBoard())
{
    views.push(
        {
            "name": "/boards/templates/board_info.xdt",
            "displayName": "Board Info",
            "viewType": "markdown"
        },
    )
}

if (["F29H85x"].includes(Common.getDeviceName()))
{
    // Multi-core Check
    var device_cpu2_unavailable_peripherals = cpu2_unavailable_peripherals[Common.getDeviceName()];
    if (device_cpu2_unavailable_peripherals)
    {
        if (Common.isContextCPU2())
        {
            for (var category of CATEGORY_LIST)
            {
                for (var unavailable_peripheral of device_cpu2_unavailable_peripherals)
                {
                    var indexToRemove = supported_modules[category].indexOf(unavailable_peripheral.moduleFile)
                    if (indexToRemove > -1)
                    {
                        supported_modules[category].splice(indexToRemove, 1)
                    }
                }
            }
        }
    }
    var device_cpu3_unavailable_peripherals = cpu3_unavailable_peripherals[Common.getDeviceName()];
    if (device_cpu3_unavailable_peripherals)
    {
        if (Common.isContextCPU3())
        {
            for (var category of CATEGORY_LIST)
            {
                for (var unavailable_peripheral of device_cpu3_unavailable_peripherals)
                {
                    var indexToRemove = supported_modules[category].indexOf(unavailable_peripheral.moduleFile)
                    if (indexToRemove > -1)
                    {
                        supported_modules[category].splice(indexToRemove, 1)
                    }
                }
            }
        }
    }
}

// console.log(supported_modules[CATEGORY_SYSTEM])
// console.log(supported_modules[CATEGORY_COMS])
// console.log(supported_modules[CATEGORY_ANALOG])
// console.log(supported_modules[CATEGORY_CONTROL])

exports = {

    displayName: "C29 SysConfig",
    topModules: [
        {
            displayName: CATEGORY_SYSTEM,
            description: "System configured here",
            modules: supported_modules[CATEGORY_SYSTEM]
        },
        {
            displayName: CATEGORY_ANALOG,
            description: "Analog peripherals get configured here",
            modules: supported_modules[CATEGORY_ANALOG],
            // categories: [{
            //     displayName: "Sub Cat",
            //     modules: ["/driverlib/sysctl.js"]
            // }]
        },
        {
            displayName: CATEGORY_CONTROL,
            description: "Control peripherals get configured here",
            modules: supported_modules[CATEGORY_CONTROL]
            // categories: [{
            // }]
        },
        {
            displayName: CATEGORY_COMS,
            description: "Communication peripherals get configured here",
            modules: supported_modules[CATEGORY_COMS]
        },
        {
            displayName: CATEGORY_RTDMA,
            description: "The RTDMA peripheral gets configured here",
            modules: supported_modules[CATEGORY_RTDMA]
        },
        {
            displayName: CATEGORY_XBAR,
            description: "The XBAR gets configured here",
            modules: supported_modules[CATEGORY_XBAR]
        },
        {
            displayName : CATEGORY_BOARD,
            description : "Board component configurations",
            modules : supported_modules[CATEGORY_BOARD]
        },
        // {
        //     displayName: CATEGORY_SW,
        //     description: "Software modules configuration",
        //     modules: supported_modules[CATEGORY_SW]
        // },

    ],
    references: references.componentReferences,
    templates: [{
            name: "/driverlib/board.c.xdt",
            outputPath: "board.c",
            alwaysRun: true
        },
        {
            name: "/driverlib/board.h.xdt",
            outputPath: "board.h",
            alwaysRun: true
        },
        {
            name: "/driverlib/board.cmd.genlibs.xdt",
            outputPath: "board.cmd.genlibs",
            alwaysRun: true
        },
        {
            name: "/driverlib/perConfig/peripheral_frame_mapping.h.xdt",
            outputPath: "peripheral_frame_mapping.h",
            alwaysRun: true
        },
        {
            name: "/driverlib/interrupt/interrupt_list.txt.xdt",
            outputPath: "interrupt_list.txt",
            alwaysRun: true
        },
        {
            name: "/driverlib/esm/errorevent_list.txt.xdt",
            outputPath: "errorevent_list.txt",
            alwaysRun: true
        },
        // {
        //     name: "/driverlib/board.opt.xdt",
        //     outputPath: "board.opt",
        //     alwaysRun: true
        // },
        {
            name: "/driverlib/pinmux.csv.xdt",
            outputPath: "pinmux.csv",
            alwaysRun: true
        },
        {
            name: "/driverlib/device/device.c.xdt",
            outputPath: "device.c",
            alwaysRun: true
        },
        {
            name: "/driverlib/device/device.h.xdt",
            outputPath: "device.h",
            alwaysRun: true
        },
        {
            name: "/driverlib/system/system_config.c.xdt",
            outputPath: "ti_drivers_config.c",
            alwaysRun: true,
        },
        {
            name: "/driverlib/system/system_config.h.xdt",
            outputPath: "ti_drivers_config.h",
            alwaysRun: true,
        },
        /* {
            name: "/driverlib/error.c.xdt",
            outputPath: "error.c",
            alwaysRun: true
        } */
        // {
        //     name: "/driverlib/epwm/templates/epwm.dot.xdt",
        //     outputPath: "epwm.dot",
        // },
        // {
        //     name: "/driverlib/adc/templates/adc.dot.xdt",
        //     outputPath: "adc.dot",
        // },
        // {
        //     name: "/driverlib/sysctl/sysctl_config.c.xdt",
        //     outputPath: "sysctl_config.c",
        // },
        // {
        //     name: "/driverlib/interrupt_nesting/sw_prioritized_defaultisr.c.xdt",
        //     outputPath: "sw_prioritized_defaultisr.c",
        // },
        // {
        //     name: "/driverlib/interrupt_nesting/sw_prioritized_isr_levels.h.xdt",
        //     outputPath: "sw_prioritized_isr_levels.h",
        // }
    ],
    views : views

}