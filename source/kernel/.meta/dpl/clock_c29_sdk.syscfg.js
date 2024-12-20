
let Common  = system.getScript("/driverlib/Common.js");
let soc     = system.getScript(`/kernel/dpl/clock_c29_sdk_${Common.getDeviceName().toLowerCase()}`);
let ssu     = system.getScript("/driverlib/device_driverlib_peripherals/f29h85x_ssu.js");

function getInstanceConfig(moduleInstance) {
    let staticConfigArr = soc.getStaticConfigArr();
    let staticConfig    = staticConfigArr.find( o => o.name === moduleInstance.instance);

    return {
        ...staticConfig,
        ...moduleInstance,
    }
};

let clock_module = {
    displayName:        "Clock",
    longDescription:    "Make sure one and only one clock instance is added and setup properly to generate timer ticks at required frequency",

    templates: {
        "/kernel/dpl/dpl_config.c.xdt": {
            dpl_config: "/kernel/dpl/clock.c.xdt",
            dpl_init:   "/kernel/dpl/clock_init.c.xdt",
        },
        "/kernel/dpl/dpl_config.h.xdt": "/kernel/dpl/clock.h.xdt",
    },

    moduleStatic : {
        config: [
            soc.makeInstanceConfig(),
            {
                name:           "timerInputClkHz",
                displayName:    "Input Clock Frequency (Hz)",
                default:        soc.getDefaultTimerClockSourceMhz(),
                readOnly:       true,
                description:    "Make sure the value put here matches the actual input clock frequency provided on the board/SOC"
            },
            {
                name:           "usecPerTick",
                displayName:    "Tick Period (usecs)",
                default:        1000,
                description:    "Timer tick period in units of usecs. MUST be >= 100 and <= 1000000. MUST divide 1000000, i.e 1sec in integer units.",
            },
            {
                name:           "intlinkowner",
                displayName:    "Interrupt Link Owner",
                default:        "SSU_LINK2",
                description:    "Link Owner for the Clock interrupt",
                options:        ssu.SSU_Link
            },
            {
                name:           "intsp",
                displayName:    "Interrupt Stack Pointer",
                default:        "SSU_STACK2",
                description:    "Interrupt Stack Pointer",
                options:        ssu.SSU_Stack
            },
            {
                name:           "rtos",
                displayName:    "RTOS",
                default:        "NORTOS",
                description:    "RTOS for which DPL is created",
                options: [
                    {
                        name:"NORTOS"
                    },
                    {
                        name:"FREERTOS"
                    }]
            },
        ],

        moduleInstances: (inst) => {
            var submodules = [];

            if(inst.rtos == "NORTOS") {
                submodules = submodules.concat(
                    [
                        {
                            name:           "dplTimer",
                            displayName:    "DPL Timer (CPUTIMER2)",
                            moduleName:     "/driverlib/cputimer.js",
                            readOnly:       true,
                            requiredArgs:
                            {
                                $name              : "DplTimer",
                                cputimerBase       : "CPUTIMER2_BASE",
                                enableInterrupt    : false,
                                registerInterrupts : false,
                                startTimer         : false,
                                timerPeriod        : 100000,
                                timerPrescaler     : 0,
                            },
                        },
                        {
                            name:       "nortos_source",
                            moduleName: "/kernel/dpl/nortos_source.js",
                        }
                    ]
                )
            }
            else
            {
                submodules = submodules.concat(
                    [
                        {
                            name:       "freertos_source",
                            moduleName: "/kernel/dpl/freertos_source.js",
                        }
                    ]
                )
            }

            return submodules;
        },

        validate : function (instance, report) {
            if((1000000 % instance.usecPerTick) != 0) {
                report.logError( `Tick period must divide 1000000 usecs (1sec) in integer multiples`, instance, "usecPerTick");
            }
        },
    },

    getInstanceConfig,
};

exports = clock_module;
