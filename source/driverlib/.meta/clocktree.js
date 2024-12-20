let Common   = system.getScript("/driverlib/Common.js");

/* Intro splash on GUI */
let longDescription = "";

// let f29h85x_defaults = {
//     "pllSource" : "SYSCTL_OSCSRC_XTAL",
//     "xtalFreq"  : 1230000,
//     "pllConfig" : "SYSCTL_PLL_DISABLE",
//     "refDiv"    : "SYSCTL_REFDIV_1",
//     "imult"     : "SYSCTL_IMULT_4",
//     "odiv"      : "SYSCTL_ODIV_1",
//     "sysDiv"    : "SYSCTL_SYSDIV_1",
//     "intClk"    : 0,
//     "vcoClk"    : 0,
//     "pllrawClk" : 1230000,
//     "sysClk"    : 1230000,
// }

// var clock_default_setting = f29h85x_defaults;

var config = [
    {
        name: "GROUP1_DEFAULTS",
        displayName : "Default SYSPLL Configuration with 20 MHz XTAL",
        config     : [
            {
                name: "100_XTAL_Default",
                displayName: "100 MHz Configuration",
                description : '',
                buttonText: "Setup SYSPLL Default",
                scriptingOnComplete: (inst, ui, result) => {
                    //Select XTAL and set frequency to 20 MHz
                    system.clockTree["XTAL"].XTAL_Freq = 20;
                    system.clockTree["XTAL_OR_X1"].inputSelect = "XTAL";

                    // Select XTAL as clock source for SYSPLL and configure multipliers and dividers
                    system.clockTree["OSCCLKSRCSEL"].inputSelect = "X1_XTAL";
                    system.clockTree["PLL_REFDIV"].divideValue = 1;
                    system.clockTree["PLL_IMULT"].multiplyValue = 15;
                    system.clockTree["PLL_ODIV"].divideValue = 3;

                },
            },
            {
                name: "150_XTAL_Default",
                displayName: "150 MHz Configuration",
                description : '',
                buttonText: "Setup SYSPLL Default",
                scriptingOnComplete: (inst, ui, result) => {
                    //Select XTAL and set frequency to 20 MHz
                    system.clockTree["XTAL"].XTAL_Freq = 20;
                    system.clockTree["XTAL_OR_X1"].inputSelect = "XTAL";

                    // Select XTAL as clock source for SYSPLL and configure multipliers and dividers
                    system.clockTree["OSCCLKSRCSEL"].inputSelect = "X1_XTAL";
                    system.clockTree["PLL_REFDIV"].divideValue = 2;
                    system.clockTree["PLL_IMULT"].multiplyValue = 30;
                    system.clockTree["PLL_ODIV"].divideValue = 2;
                },
            },
            {
                name: "200_XTAL_Default",
                displayName: "200 MHz Configuration",
                description : '',
                buttonText: "Setup SYSPLL Default",
                scriptingOnComplete: (inst, ui, result) => {
                    //Select XTAL and set frequency to 20 MHz
                    system.clockTree["XTAL"].XTAL_Freq = 20;
                    system.clockTree["XTAL_OR_X1"].inputSelect = "XTAL";

                    // Select XTAL as clock source for SYSPLL and configure multipliers and dividers
                    system.clockTree["OSCCLKSRCSEL"].inputSelect = "X1_XTAL";
                    system.clockTree["PLL_REFDIV"].divideValue = 1;
                    system.clockTree["PLL_IMULT"].multiplyValue = 30;
                    system.clockTree["PLL_ODIV"].divideValue = 3;
                },
            },
        ],
    },
    {
        name: "GROUP2_DEFAULTS",
        displayName : "Default SYSPLL Configuration with 25 MHz X1",
        config     : [
            {
                name: "100_X1_Default",
                displayName: "100 MHz Configuration",
                description : '',
                buttonText: "Setup SYSPLL Default",
                scriptingOnComplete: (inst, ui, result) => {
                    //Select X1 and set frequency to 25 MHz
                    system.clockTree["X1"].XTAL_Freq = 25;
                    system.clockTree["XTAL_OR_X1"].inputSelect = "X1";

                    // Select X1 as clock source for SYSPLL and configure multipliers and dividers
                    system.clockTree["OSCCLKSRCSEL"].inputSelect = "X1_XTAL";
                    system.clockTree["PLL_REFDIV"].divideValue = 1;
                    system.clockTree["PLL_IMULT"].multiplyValue = 16;
                    system.clockTree["PLL_ODIV"].divideValue = 4;
                },
            },
            {
                name: "150_X1_Default",
                displayName: "150 MHz Configuration",
                description : '',
                buttonText: "Setup SYSPLL Default",
                scriptingOnComplete: (inst, ui, result) => {
                    //Select X1 and set frequency to 25 MHz
                    system.clockTree["X1"].XTAL_Freq = 25;
                    system.clockTree["XTAL_OR_X1"].inputSelect = "X1";

                    // Select X1 as clock source for SYSPLL and configure multipliers and dividers
                    system.clockTree["OSCCLKSRCSEL"].inputSelect = "X1_XTAL";
                    system.clockTree["PLL_REFDIV"].divideValue = 1;
                    system.clockTree["PLL_IMULT"].multiplyValue = 24;
                    system.clockTree["PLL_ODIV"].divideValue = 4;
                },
            },
            {
                name: "200_X1_Default",
                displayName: "200 MHz Configuration",
                description : '',
                buttonText: "Setup SYSPLL Default",
                scriptingOnComplete: (inst, ui, result) => {
                    //Select X1 and set frequency to 25 MHz
                    system.clockTree["X1"].XTAL_Freq = 25;
                    system.clockTree["XTAL_OR_X1"].inputSelect = "X1";

                    // Select X1 as clock source for SYSPLL and configure multipliers and dividers
                    system.clockTree["OSCCLKSRCSEL"].inputSelect = "X1_XTAL";
                    system.clockTree["PLL_REFDIV"].divideValue = 2;
                    system.clockTree["PLL_IMULT"].multiplyValue = 32;
                    system.clockTree["PLL_ODIV"].divideValue = 2;
                },
            },
        ],
    },
    {
        name: "GROUP3_DEFAULTS",
        displayName : "Default SYSPLL Configuration with 10 MHz INTOSC1",
        config     : [
            {
                name: "100_INTOSC1_Default",
                displayName: "100 MHz Configuration",
                description : '',
                buttonText: "Setup SYSPLL Default",
                scriptingOnComplete: (inst, ui, result) => {
                    // Select INTOSC1 as clock source for SYSPLL and configure multipliers and dividers
                    system.clockTree["OSCCLKSRCSEL"].inputSelect = "INTOSC1";
                    system.clockTree["PLL_REFDIV"].divideValue = 1;
                    system.clockTree["PLL_IMULT"].multiplyValue = 30;
                    system.clockTree["PLL_ODIV"].divideValue = 3;
                },
            },
            {
                name: "150_INTOSC1_Default",
                displayName: "150 MHz Configuration",
                description : '',
                buttonText: "Setup SYSPLL Default",
                scriptingOnComplete: (inst, ui, result) => {
                    // Select INTOSC1 as clock source for SYSPLL and configure multipliers and dividers
                    system.clockTree["OSCCLKSRCSEL"].inputSelect = "INTOSC1";
                    system.clockTree["PLL_REFDIV"].divideValue = 1;
                    system.clockTree["PLL_IMULT"].multiplyValue = 30;
                    system.clockTree["PLL_ODIV"].divideValue = 2;
                },
            },
            {
                name: "200_INTOSC1_Default",
                displayName: "200 MHz Configuration",
                description : '',
                buttonText: "Setup SYSPLL Default",
                scriptingOnComplete: (inst, ui, result) => {
                    // Select INTOSC1 as clock source for SYSPLL and configure multipliers and dividers
                    system.clockTree["OSCCLKSRCSEL"].inputSelect = "INTOSC1";
                    system.clockTree["PLL_REFDIV"].divideValue = 1;
                    system.clockTree["PLL_IMULT"].multiplyValue = 40;
                    system.clockTree["PLL_ODIV"].divideValue = 2;
                },
            },
        ],
    },
    {
        name: "GROUP4_DEFAULTS",
        displayName : "Default SYSPLL Configuration with 10 MHz INTOSC2",
        config     : [
            {
                name: "100_INTOSC2_Default",
                displayName: "100 MHz Configuration",
                description : '',
                buttonText: "Setup SYSPLL Default",
                scriptingOnComplete: (inst, ui, result) => {
                    // Select INTOSC2 as clock source for SYSPLL and configure multipliers and dividers
                    system.clockTree["OSCCLKSRCSEL"].inputSelect = "INTOSC2";
                    system.clockTree["PLL_REFDIV"].divideValue = 1;
                    system.clockTree["PLL_IMULT"].multiplyValue = 30;
                    system.clockTree["PLL_ODIV"].divideValue = 3;
                },
            },
            {
                name: "150_INTOSC2_Default",
                displayName: "150 MHz Configuration",
                description : '',
                buttonText: "Setup SYSPLL Default",
                scriptingOnComplete: (inst, ui, result) => {
                    // Select INTOSC2 as clock source for SYSPLL and configure multipliers and dividers
                    system.clockTree["OSCCLKSRCSEL"].inputSelect = "INTOSC2";
                    system.clockTree["PLL_REFDIV"].divideValue = 1;
                    system.clockTree["PLL_IMULT"].multiplyValue = 30;
                    system.clockTree["PLL_ODIV"].divideValue = 2;
                },
            },
            {
                name: "200_INTOSC2_Default",
                displayName: "200 MHz Configuration",
                description : '',
                buttonText: "Setup SYSPLL Default",
                scriptingOnComplete: (inst, ui, result) => {
                    // Select INTOSC2 as clock source for SYSPLL and configure multipliers and dividers
                    system.clockTree["OSCCLKSRCSEL"].inputSelect = "INTOSC2";
                    system.clockTree["PLL_REFDIV"].divideValue = 1;
                    system.clockTree["PLL_IMULT"].multiplyValue = 40;
                    system.clockTree["PLL_ODIV"].divideValue = 2;
                },
            },
        ],
    },
    {
        name: "PERIPHERAL_CLOCKS",
        displayName : "Peripheral Clocks Customization",
        collapsed: false,
        config: [
            {
                name: "enable_all_peripheral_clocks",
                displayName: "Enable all Peripheral clocks",
                longDescription: "By default, the clock is enabled for all the peripherals (as part of Device_init()). To enable the clocks only for peripherals added in SysConfig , disable this configurable.",
                default: true,
            },
        ],
    },
];

function moduleInstances(inst)
{
    let components = []

    // if (inst.clockFail)
    // {
    //     components = components.concat([{
    //         name        : "ESMConfig_clockfail",
    //         group       : "GROUP_ESM",
    //         displayName : "CLOCKFAIL",
    //         moduleName  : "/driverlib/esm.js",
    //         collapsed   : true,
    //         args        : {
    //             $name        : "CLOCKFAIL_ESM",
    //             eventSource  : "CLOCKFAIL"
    //         },
    //     }])
    // }
    // if (inst.pllSlip)
    // {
    //     components = components.concat([{
    //         name        : "ESMConfig_pllSlip",
    //         group       : "GROUP_ESM",
    //         displayName : "PLLSLIP",
    //         moduleName  : "/driverlib/esm.js",
    //         collapsed   : true,
    //         args        : {
    //             $name        : "PLLSLIP_ESM",
    //             eventSource  : "PLLSLIP"
    //         },
    //     }])
    // }

    return components;
}

function onValidate(inst, validation) 
{ 
}


function filterHardware(component)
{
}

var clockModule = {
    // peripheralName: "CLOCKTREE",
    displayName: "CLOCKTREE",
    maxInstances: 1,
    description: "ClockTree Configuration",
    filterHardware : filterHardware,
    templates: {
        clocktree: "/driverlib/clocktree/clocktree.h.xdt"
    },
    moduleStatic : {
        config  : config,
        validate: onValidate,
        moduleInstances
    }
};




exports = clockModule;