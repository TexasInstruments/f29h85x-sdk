let Common      = system.getScript("/driverlib/Common.js");
let references  = system.getScript("/driverlib/PeripheralComponentsReferences.js");
let Mappings    = system.getScript("/driverlib/PeripheralComponentMappings.js");

let CATEGORY_ANALOG     = Mappings.CATEGORY_ANALOG
let CATEGORY_COMS       = Mappings.CATEGORY_COMS
let CATEGORY_CONTROL    = Mappings.CATEGORY_CONTROL
let CATEGORY_SYSTEM     = Mappings.CATEGORY_SYSTEM
let CATEGORY_BOARD      = Mappings.CATEGORY_BOARD
let CATEGORY_SW         = Mappings.CATEGORY_SW
let CATEGORY_RTDMA      = Mappings.CATEGORY_RTDMA
let CATEGORY_XBAR       = Mappings.CATEGORY_XBAR

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

let supported_peripheralName_moduleFile = Mappings.supported_peripheralName_moduleFile
let static_peripheralName_moduleFile    = Mappings.static_peripheralName_moduleFile
let device_specific_modules             = Mappings.device_specific_modules
let ra_setup_unavailable_modules        = Mappings.ra_setup_unavailable_modules
let ra_configure_unavailable_modules    = Mappings.ra_configure_unavailable_modules
let cpu2_unavailable_peripherals        = Mappings.cpu2_unavailable_peripherals
let cpu3_unavailable_peripherals        = Mappings.cpu3_unavailable_peripherals

if (Common.onlyPinmux())
{
    static_peripheralName_moduleFile = []
    device_specific_modules = []
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
    let moduleFilePath = device_specific_modules[device_specific_modules_index].moduleFile;
    let count=10;
    try {
        let temp = system.getScript(moduleFilePath);
        count = temp.maxInstances;
    } catch (e) {
        
    }
    if (device_specific_modules[device_specific_modules_index].
        devices.includes(Common.getDeviceName()) && count>0)
    {
        supported_modules[device_specific_modules[device_specific_modules_index].moduleCategory].
            push(device_specific_modules[device_specific_modules_index].moduleFile)
    }
}

var views = []
/*
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
*/

if (["F29H85x"].includes(Common.getDeviceName()))
{
    // SETUP mode check
    if(Common.isAllocationSetupMode()){
        let device_ra_setup_unavailable_modules = ra_setup_unavailable_modules[Common.getDeviceName()];
        if (device_ra_setup_unavailable_modules)
        {
            for (let category of CATEGORY_LIST)
            {
                for (let unavailable_peripheral of device_ra_setup_unavailable_modules)
                {
                    let indexToRemove = supported_modules[category].indexOf(unavailable_peripheral.moduleFile)
                    if (indexToRemove > -1)
                    {
                        supported_modules[category].splice(indexToRemove, 1)
                    }
                }
            }
        }
    }
    // Multi-core Check
    else{
        let device_configure_mode_unavailable_peripherals = ra_configure_unavailable_modules[Common.getDeviceName()];
        if (Common.isAllocationConfigureMode() && device_configure_mode_unavailable_peripherals)
        {
            for (let category of CATEGORY_LIST)
            {
                for (let unavailable_peripheral of device_configure_mode_unavailable_peripherals)
                {
                    let indexToRemove = supported_modules[category].indexOf(unavailable_peripheral.moduleFile)
                    if (indexToRemove > -1)
                    {
                        supported_modules[category].splice(indexToRemove, 1)
                    }
                }
            }
        }
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
}

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
			// alwaysRun: true,
            alwaysRun: !(Common.isAllocationSetupMode())
        },
        {
            name: "/driverlib/board.h.xdt",
            outputPath: "board.h",
			// alwaysRun: true,
            alwaysRun: !(Common.isAllocationSetupMode())
        },
        {
            name: "/driverlib/board.cmd.genlibs.xdt",
            outputPath: "board.cmd.genlibs",
			// alwaysRun: true,
            alwaysRun: !(Common.isAllocationSetupMode())
        },
        {
            name: "/driverlib/perConfig/peripheral_frame_mapping.h.xdt",
            outputPath: "peripheral_frame_mapping.h",
			// alwaysRun: true,
            alwaysRun: !(Common.isAllocationSetupMode())
        },
        {
            name: "/driverlib/interrupt/interrupt_list.txt.xdt",
            outputPath: "interrupt_list.txt",
			// alwaysRun: true,
            alwaysRun: !(Common.isAllocationSetupMode())
        },
        {
            name: "/driverlib/esm/errorevent_list.txt.xdt",
            outputPath: "errorevent_list.txt",
			// alwaysRun: true,
            alwaysRun: !(Common.isAllocationSetupMode())
        },
        // {
        //     name: "/driverlib/board.opt.xdt",
        //     outputPath: "board.opt",
        //     alwaysRun: true
        // },
        {
            name: "/driverlib/pinmux.csv.xdt",
            outputPath: "pinmux.csv",
			// alwaysRun: true,
            alwaysRun: !(Common.isAllocationSetupMode())
        },
        {
            name: "/driverlib/device/device.c.xdt",
            outputPath: "device.c",
			// alwaysRun: true,
            alwaysRun: !(Common.isAllocationSetupMode())
        },
        {
            name: "/driverlib/device/device.h.xdt",
            outputPath: "device.h",
			// alwaysRun: true,
            alwaysRun: !(Common.isAllocationSetupMode())
        },
        {
            name: "/driverlib/system/system_config.c.xdt",
            outputPath: "ti_drivers_config.c",
			// alwaysRun: true,
            alwaysRun: !(Common.isAllocationSetupMode())
        },
        {
            name: "/driverlib/system/system_config.h.xdt",
            outputPath: "ti_drivers_config.h",
			// alwaysRun: true,
            alwaysRun: !(Common.isAllocationSetupMode())
        },
        /* {
            name: "/driverlib/error.c.xdt",
            outputPath: "error.c",
            alwaysRun: true
        } */
    ],
    views : views

}