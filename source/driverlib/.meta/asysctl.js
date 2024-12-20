let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_asysctl.js");

/* Array of CAN configurables that are common across device families */
let staticConfig = [
    {
        name: "GROUP_TEMP_CONTROL",
        displayName: "Temperature Sensor",
        description: "",
        longDescription: "",
        collapsed: false,
        config: [
            // enableTemperatureSensor / disableTemperatureSensor
            {
                name: "enableTemperatureSensor",
                displayName : "Enable Temperature Sensor",
                default: false,
            },
            // lockTemperatureSensor
            {
                name: "lockTemperatureSensor",
                displayName : "Lock Temperature Sensor Control Register",
                default: false,
            },
        ]
    },
];

//**************************************************************************
// analogReference OPTIONS - choose which device+package combinations have 
// only one reference mode option

var analogReference_opts = [];

    analogReference_opts = [
        {name: "INTERNAL_3_3_V", displayName: "Internal 3.3V"},
        {name: "INTERNAL_2_5_V", displayName: "Internal 2.5V"},
        {name: "EXTERNAL", displayName: "External"},
    ];

var selectTestNode_opts = [];

selectTestNode_opts = [
    { name: "NO_CONN", displayName: "NO CONN" },
    { name: "VDDCORE", displayName: "VDDCORE" },
    { name: "VDDA", displayName: "VDDA" },
    { name: "VSSA", displayName: "VSSA" },
    { name: "VREFLOAB", displayName: "VREFLOAB" },
    { name: "CDAC1H", displayName: "CDAC1H" },
    { name: "CDAC1L", displayName: "CDAC1L" },
    { name: "CDAC2H", displayName: "CDAC2H" },
    { name: "CDAC2L", displayName: "CDAC2L" },
    { name: "CDAC3H", displayName: "CDAC3H" },
    { name: "CDAC3L", displayName: "CDAC3L" },
    { name: "CDAC4H", displayName: "CDAC4H" },
    { name: "CDAC4L", displayName: "CDAC4L" },
    { name: "CDAC5H", displayName: "CDAC5H" },
    { name: "CDAC5L", displayName: "CDAC5L" },
    { name: "CDAC6H", displayName: "CDAC6H" },
    { name: "CDAC6L", displayName: "CDAC6L" },
    { name: "CDAC7H", displayName: "CDAC7H" },
    { name: "CDAC7L", displayName: "CDAC7L" },
    { name: "CDAC8H", displayName: "CDAC8H" },
    { name: "CDAC8L", displayName: "CDAC8L" },
    { name: "CDAC9H", displayName: "CDAC9H" },
    { name: "CDAC9L", displayName: "CDAC9L" },
    { name: "CDAC10H", displayName: "CDAC10H" },
    { name: "CDAC10L", displayName: "CDAC10L" },
    { name: "CDAC11H", displayName: "CDAC11H" },
    { name: "CDAC11L", displayName: "CDAC11L" },	
    { name: "CDAC12H", displayName: "CDAC12H" },
    { name: "CDAC12L", displayName: "CDAC12L" },
    { name: "ENZ_CALIB_GAIN_3P3", displayName: "ENZ CALIB GAIN 3P3" },
    { name: "VREFLOCDE", displayName: "VREFLOCDE" },
]

staticConfig.push(
    {
        name: "GROUP_ANAREF",
        displayName: "Analog Reference",
        description: "",
        longDescription: "",
        collapsed: false,
        config: [
            {
                name        : "analogReferenceAB",
                displayName : "Analog Reference for ADCA and ADCB (VREFHIAB)",
                default     : "EXTERNAL",
                options     : analogReference_opts
            },
            {
                name        : "analogReferenceCDE",
                displayName : "Analog Reference for ADCC, ADCD and ADCE (VREFHICDE)",
                default     : "EXTERNAL",
                options     : analogReference_opts
            },
        ]
    },
);


staticConfig.push(
    {

    name: "GROUP_INTERNAL_TEST_NODE",
    displayName: "Select Test Node",
    collapsed: false,
    longDescription: "It supports the CMP-DAC to ADC loopback on internal connection. This field defines which internal node, if any, is selected to come out on the INTERNALTEST node connected to the ADC.",
    config: [
        {
        name: "SelectTestNode",
        displayName: "Select Test Node",
        default: "NO_CONN",
        options: selectTestNode_opts,

        },
    ]

    },

);

var sharedModuleInstances = undefined;

/*
 *  ======== filterHardware ========
 *  Control RX, TX Pin usage by the user specified dataDirection.
 *
 *  param component - hardware object describing signals and
 *                     resources they're attached to
 *
 *  returns Boolean indicating whether or not to allow the component to
 *           be assigned to an instance's $hardware config
 */
function filterHardware(component)
{
    return (Common.typeMatches(component.type, ["ASYSCTL"]));
}

function onValidate(inst, validation){

    let a = Common.getModuleForCore("/driverlib/adc.js", system.context)

    if (a && a.$instances) {
        for (let instance_index in a.$instances) {
            let instance_obj = a.$instances[instance_index];
            if (instance_obj) {
                if (instance_obj.adcBase == "ADCA_BASE" || instance_obj.adcBase == "ADCB_BASE") {
                    if (instance_obj.adcResolutionMode == "ADC_RESOLUTION_16BIT" && inst.analogReferenceAB == "INTERNAL_3_3_V") {
                        validation.logError(`Internal ref 3.3V is not supported on 16-bit resolution mode. Please reconfigure ${instance_obj.adcBase} resolution to 12-bit`,
                            inst, "analogReferenceAB")
                    }
                }
            }
        }
    }
}

var asysctlModule = {
    peripheralName: "ASYSCTL",
    displayName: "ASYSCTL",
    maxInstances: 1,
    defaultInstanceName: "myASYSCTL",
    description: "Analog SysCtl",
    filterHardware : filterHardware,
    moduleStatic : {
        config          : staticConfig,
        validate        : onValidate,   
    },
    //config: config,
    templates: {
        boardc : "/driverlib/asysctl/asysctl.board.c.xdt",
        boardh : "/driverlib/asysctl/asysctl.board.h.xdt"
    },
};
exports = asysctlModule;