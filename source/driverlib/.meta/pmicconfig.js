
exports = {
    displayName: "Configurations",
    moduleStatic: {
        config:[
            {
                name:           "Type",
                displayName:    "Type",
                default:        "TPS653860XX",
                readOnly:       false,
                description:    "PMIC type",
                options: [
                    {name:"TPS653860XX", displayName:"TPS653860XX"},
                    {name:"TPS65036XX",  displayName:"TPS65036XX"},
                ]
            }
        ],

        moduleInstances: (inst) => {
            var submodules = [];

            if(inst.Type == "TPS653860XX")
            {
                submodules = submodules.concat(
                    [
                        {
                            name:                           "pmicspi",
                            displayName:                    "TPS653860XX PMIC SPI",
                            moduleName:                     "/driverlib/spi.js",
                            collapsed:                      true,
                            description:                    "SPI instance used for TPS653860XX PMIC",
                            args: {
                                bitRate:                    2000000,
                            },
                            requiredArgs: {
                                $name :                     "TPS653860XX_PMIC_SPI",
                                transferProtocol:           "SPI_PROT_POL0PHA1",
                                mode:                       "SPI_MODE_CONTROLLER",
                                dataWidth:                  "16",
                                useFifo:                    true,
                                useInterrupts:              false,
                                useDMARX:                   false,
                                useDMATX:                   false,
                                useHSMode:                  false,
                                loopback:                   false,
                                useCase:                    "3-WIRE CONTROLLER",
                                emulationMode:              "SPI_EMULATION_FREE_RUN",
                            }
                        },
                        {
                            name:                           "cspin",
                            displayName:                    "SPI CS GPIO",
                            moduleName:                     "/driverlib/gpio.js",
                            description:                    "GPIO used for TPS653860XX PMIC SPI CS",
                            requiredArgs: {
                                $name:                      "TPS653860XX_PMIC_CS_GPIO",
                                direction :                 "GPIO_DIR_MODE_OUT",
                                padConfig:                  "STD",
                                qualMode:                   "GPIO_QUAL_ASYNC",
                                writeInitialValue:          false,
                            }
                        }
                    ]
                )
            }
            else
            {
                submodules = submodules.concat(
                    [
                        {
                            name:                           "pmici2c",
                            displayName:                    "TPS65036XX PMIC I2C",
                            moduleName:                     "/driverlib/i2c.js",
                            collapsed:                      true,
                            description:                    "I2C instance used for TPS65036XX PMIC",
                            args: {
                                bitRate:                    100000,
                            },
                            requiredArgs: {
                                $name :                     "TPS65036XX_PMIC_I2C",
                                mode:                       "CONTROLLER",
                                duty:                       "I2C_DUTYCYCLE_50",
                                bitCount:                   "I2C_BITCOUNT_8",
                                addressMode:                "I2C_ADDR_MODE_7BITS",
                                useFifo:                    true,
                                useInterrupts:              false,
                                useExtendedClockStretching: false,
                                loopback:                   false,
                                emulationMode:              "I2C_EMULATION_FREE_RUN",
                            }
                        }
                    ]
                )
            }

            return submodules;
        },
    },
    templates: {
        '/driverlib/pmic.c.xdt':    true,
    },
};