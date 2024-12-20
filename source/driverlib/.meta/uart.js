let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_uart.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

let dma_instances = [];
for (var dma of device_driverlib_memmap.DMAMemoryMap) {
    dma_instances.push({
        name : dma.name,
        displayName : dma.displayName
    })
}

/* Intro splash on GUI */
let longDescription = "UART";


function onChangeFIFOInterrupts(inst, ui)
{
    // If interrupt enabled, unhide everything, let later if-statements re-
    // hide necessary items
    if (inst.enInterrupt) 
    {
        ui.registerInterrupts.hidden = false;
        ui.enabledInterrupts.hidden = false;
        ui.txiflsel.hidden = false;
        ui.rxiflsel.hidden = false;
    }
    else
    {
        ui.registerInterrupts.hidden = true;
        ui.enabledInterrupts.hidden = true;
        ui.txiflsel.hidden = true;
        ui.rxiflsel.hidden = true;
    }
    // Hide fifo-related interrupts based on FEN
    if (inst.enInterrupt && inst.fen)
    {
        ui.txiflsel.hidden = false;
        ui.rxiflsel.hidden = false;
    }
    else
    {
        ui.txiflsel.hidden = true;
        ui.rxiflsel.hidden = true;
    }
}

function onChangeParity(inst, ui)
{
    // If parity is enabled, unhide everything, let later if-statements re-
    // hide necessary items
    if (inst.pen)
    {
        ui.eps.hidden = false;
        ui.sps.hidden = false;
        ui.stickParityVal.hidden = false;
    }
    else
    {
        ui.eps.hidden = true;
        ui.sps.hidden = true;
        ui.stickParityVal.hidden = true;
    }
    // Hide/unhide stickParityVal as necessary, based on stick parity select
    if (inst.pen && inst.sps)
    {
        ui.stickParityVal.hidden = false;
    }
    else
    {
        ui.stickParityVal.hidden = true;
    }
}

function onChangeUseDMARX(inst, ui)
{
    if (inst.useDMARX)
    {
        ui.DMARXInst.hidden = false;
        ui.disableDMARXonError.hidden = false;
    }
    else 
    {
        ui.DMARXInst.hidden = true;
        ui.disableDMARXonError.hidden = true;
    }
}

function onChangeUseDMATX(inst, ui)
{
    if (inst.useDMATX)
    {
        ui.DMATXInst.hidden = false;
    }
    else 
    {
        ui.DMATXInst.hidden = true;
    }
}

function onChangeBaudSelect(inst, ui){
    if(inst.baudSelect != "Custom"){
        ui.baud.hidden = true;
        inst.baud = Number(inst.baudSelect)
    }
    else{
        ui.baud.hidden = false;
    }
}

function burstSizeMapping(fifoLevel, inst){
    if(inst.fen == false){
        return 1;
    }
    switch(fifoLevel) {
        case "UART_FIFO_TX1_8":
        case "UART_FIFO_RX1_8":
            return 2;
        case "UART_FIFO_TX2_8":
        case "UART_FIFO_RX2_8":
            return 4;
        case "UART_FIFO_TX4_8":
        case "UART_FIFO_RX4_8":
            return 8;
        case "UART_FIFO_TX6_8":
        case "UART_FIFO_RX6_8":
            return 12;
        case "UART_FIFO_TX7_8":
        case "UART_FIFO_RX7_8":
            return 14;
        default:
          return 1;
    }
}

function onValidate(inst, validation)
{
    if ((inst.enInterrupt) && (inst.enabledInterrupts.length <= 0) && (inst.txiflsel != "EOT"))
    {
        validation.logWarning(
            "At least one interrupt should be enabled when 'Enable Interrupts' is checked. Either choose one here, or Enable FIFO and choose Transmit FIFO Interrupt Level 'End of Transmission'.", 
            inst, "enabledInterrupts");
    }

    // Baud rate checks
    // min  = (Max 16 bit integer+((Max 6 bit fractional)/64))*16 low speed mode
    //      = (2^16+((2^6)/64)*16
    //      = 1048592
    var minBaud = inst.$module.$static["baudSYSCLK"]/(1048592);
    var maxBaud = inst.$module.$static["baudSYSCLK"]/8;
    if (inst.baud > maxBaud)
    {
        validation.logError(
            "Baud rate out of range, Max. baud rate given current UART source clock is " + String(maxBaud),
            inst, "baud");
    }
    
    else if (inst.baud < minBaud)
    {
        validation.logError(
            "Baud rate out of range, Min. baud rate given current UART source clock is " + String(minBaud),
            inst, "baud");
    }

    if((inst.useDMARX || inst.useDMATX) &&  !inst.fen)
    {
        validation.logWarning(
            "DMA operation is enabled without enabling FIFO", inst, "fen");
    }

    if(inst.useDMARX && (inst.uartRXDMA.burstSize != burstSizeMapping(inst.rxiflsel, inst)))
    {
        validation.logWarning(
            "Burst size is not equal to RX FIFO size", inst.uartRXDMA, "burstSize");
    }

    if(inst.useDMATX && (inst.uartTXDMA.burstSize != burstSizeMapping(inst.txiflsel, inst)))
    {
        validation.logWarning(
            "Burst size is not equal to TX FIFO size", inst.uartRXDMA, "burstSize");
    }
}

/* Array of UART configurables that are common across device families */
let config = [
    {
        name: "GROUP_PERCFG",
        displayName: "Peripheral Configuration",
        collapsed: false,
        config: [
            //**********************************************************************
            // Baud Settings
            {
                name        : "baudSelect",
                displayName : "Baud Rate Select",
                description : 'The set of baud rates that are used by this instance. '
                            + 'On some devices, these rates are used to pre-compute '
                            + 'a table of clock dividers necessary for each rate.',
                hidden      : false,
                default     : "9600",
                options     :[
                    {name: "Custom"},
                    {name: "110"},
                    {name: "150"},
                    {name: "300"},
                    {name: "600"},
                    {name: "1200"},
                    {name: "2400"},
                    {name: "4800"},
                    {name: "9600"},
                    {name: "19200"},
                    {name: "38400"},
                    {name: "57600"},
                    {name: "115200"},
                    {name: "230400"},
                    {name: "460800"},
                    {name: "921600"},
                ],
                onChange    : onChangeBaudSelect
            },
            {
                name        : "baud",
                displayName : "Baud Rate Value",
                description : 'The set of baud rates that are used by this instance. '
                            + 'On some devices, these rates are used to pre-compute '
                            + 'a table of clock dividers necessary for each rate.',
                hidden      : true,
                default     : 9600,
            },
            {
                name        : "baudVal",
                displayName : "Actual Baud Rate Value",
                description : 'Actual baud rate value based on requested input and programmable values.',
                hidden      : false,
                getValue    : (inst) => {
                    var baudrt      = inst.baud;
                    var baudrtDiv   = inst.baud;
                    //
                    // Half the supplied baud rate to compensate for enabling high speed
                    // mode. This allows the following code to be common to both cases.
                    //
                    if ((baudrtDiv * 16) > inst.$module.$static["baudSYSCLK"])
                    {
                        baudrtDiv = baudrtDiv/2;
                    }
                    var div = parseInt((((inst.$module.$static["baudSYSCLK"] * 8) / baudrtDiv) + 1) / 2);
                    
                    // High speed mode (source clock /8) if needed for this baud
                    var ClkDiv = ((baudrt * 16) > inst.$module.$static["baudSYSCLK"] ? 8 : 16)

                    // Get the values that would get stored into the regs
                    var integerBaudRateDivider = parseInt(div / 64);
                    var fractionalBaudRateDivider = parseInt(div % 64);
                    
                    // Compute the resultant baud rate of the values that got put
                    // into the registers
                    var baudActual = (inst.$module.$static["baudSYSCLK"]/((integerBaudRateDivider + (fractionalBaudRateDivider/64))*ClkDiv));
                    return Math.round(baudActual);
                },
                default     : 115200,
            },
            {
                name        : "baudErr",
                displayName : "Baud Rate Error Percent",
                description : 'Error percentage of actual vs set baud rate.',
                hidden      : false,
                getValue    : (inst) => {
                    var baudrt      = inst.baud;
                    var baudrtDiv   = inst.baud;
                    //
                    // Half the supplied baud rate to compensate for enabling high speed
                    // mode. This allows the following code to be common to both cases.
                    //
                    if ((baudrtDiv * 16) > inst.$module.$static["baudSYSCLK"])
                    {
                        baudrtDiv = baudrtDiv/2;
                    }
                    var div = parseInt((((inst.$module.$static["baudSYSCLK"] * 8) / baudrtDiv) + 1) / 2);
                    
                    // High speed mode (source clock /8) if needed for this baud
                    var ClkDiv = ((baudrt * 16) > inst.$module.$static["baudSYSCLK"] ? 8 : 16)

                    // get the values that would get stored into the regs
                    var integerBaudRateDivider = parseInt(div / 64);
                    var fractionalBaudRateDivider = parseInt(div % 64);
                    
                    // Compute the resultant baud rate of the values that got put
                    // into the registers
                    var baudActual = (inst.$module.$static["baudSYSCLK"]/((integerBaudRateDivider + (fractionalBaudRateDivider/64))*ClkDiv));
                    return Math.abs((baudActual-baudrt)/baudrt)*100;
                },
                default     : 115200,
            },
            //**********************************************************************
            // Word Settings
            {    
                name        : "GROUP_WORD_SETTINGS",
                displayName : "Word Settings",
                collapsed   : false,
                config      : [
                    {
                        name        : "wlen",
                        displayName : "Word Length",
                        description : 'The number of data bits transmitted or received in a frame.',
                        hidden      : false,
                        default     : 'UART_CONFIG_WLEN_8',
                        options     : device_driverlib_peripheral.UART_CONFIG.slice(0,4)
                    },
                    {
                        name        : "stp2",
                        displayName : "Stop Bits",
                        description : 'Number of stop bits transmitted at end of a frame. The receive logic does not check for two stop bits being received.',
                        hidden      : false,
                        default     : 'UART_CONFIG_STOP_ONE',
                        options     : device_driverlib_peripheral.UART_CONFIG.slice(4,6)
                    },
                    //**********************************************************************
                    // Parity settings
                    // Enable parity
                    {
                        name        : "pen",
                        displayName : "Parity Enable",
                        description : 'Parity enable.',
                        hidden      : false,
                        default     : false,
                        onChange    : onChangeParity,
                    },
                    // Even parity select
                    {
                        name        : "eps",
                        displayName : "Parity Select",
                        description : 'Choose even or odd parity.',
                        hidden      : true,
                        default     : 'UART_CONFIG_PAR_ODD',
                        options     : device_driverlib_peripheral.UART_CONFIG.slice(7,9)
                    },
                    // Stick parity select
                    {
                        name        : "sps",
                        displayName : "Stick Parity",
                        description : 'Force parity bit to be a certain value regardless of word sent.',
                        hidden      : true,
                        default     : false,
                        onChange    : onChangeParity,
                    },
                    // Output a value to user to show what the stick parity value will be, 
                    // based on PEN, EPS, and SPS bits of UARTLCRH
                    {
                        name        : "stickParityVal",
                        displayName : "Stick Parity Value",
                        description : 'When stick parity is enabled the parity bit is transmitted and checked as this value. This is based on even/odd parity selection.',
                        hidden      : true,
                        getValue    : (inst) => {
                            if (    inst.pen == true    &&  // parity enabled
                                    inst.sps == true    &&  // stick parity enabled
                                    inst.eps == "UART_CONFIG_PAR_EVEN")     // even parity selected
                                
                            {
                                return "0"; // Always output 0 for even stick parity
                            }
                            else if (   inst.pen == true    &&  // parity enabled
                                        inst.sps == true    &&  // stick parity enabled
                                        inst.eps == "UART_CONFIG_PAR_ODD")      // odd parity selected
                            {
                                return "1"; // Always output 1 for odd stick parity
                            }
                            return "X"
                        },
                        default     : "X",
                    },
                ]
            },
            {
                name        : "fen",
                displayName : "Enable FIFO",
                description : 'Whether or not to use FIFO mode.',
                hidden      : false,
                onChange    : onChangeFIFOInterrupts,
                default     : false
            },
            //**********************************************************************
            // Debug
            {
                name        : "loopback",
                displayName : "Enable Loopback Mode",
                description : 'Internal loopback mode for diagnostic or debug work.',
                hidden      : false,
                default     : false
                
            },
            //**********************************************************************
            // Pinmux
            {
                name: "useCase",
                displayName : "Use Case",
                description : 'Peripheral use case',
                hidden      : false,
                default     : 'ALL',
                options     : Pinmux.getPeripheralUseCaseNames("UART"),
                onChange    : Pinmux.useCaseChanged, 
            },
        ]
    },
    {
        name: "GROUP_ISR",
        displayName: "Interrupt Configuration",
        collapsed: true,
        config: [
            {
                name        : "enInterrupt",
                displayName : "Enable Interrupts",
                description : 'Choose whether or not to use interrupts.',
                hidden      : false,
                default     : true,
                onChange    : onChangeFIFOInterrupts,
                
            },
            {
                name        : "registerInterrupts",
                displayName : "Register Interrupt Handler",
                description : 'Whether or not to register interrupt handlers in the interrupt module.',
                hidden      : false,
                default     : false,
                
            },
            {
                name        : "enabledInterrupts",
                displayName : "Enabled Interrupts",
                description : 'Choose interrupts to enable.',
                hidden      : false,
                default     : ["UART_INT_TX","UART_INT_RX",],
                minSelections: 0,
                options     : device_driverlib_peripheral.UART_INT 
            },
            {
                name        : "txiflsel",
                displayName : "Transmit FIFO Interrupt Level",
                description : 'Transmit FIFO interrupt level used. If End of Transmission (EOT) is chosen, then TXRIS bit and interrupt is set only after all transmitted data, including stop bits, have cleared the serializer.',
                hidden      : true,
                default     : "UART_FIFO_TX4_8",
                options     : device_driverlib_peripheral.UART_FIFO_TX
            },
            {
                name        : "rxiflsel",
                displayName : "Receive FIFO Interrupt Level",
                description : 'Receive FIFO interrupt level used.',
                hidden      : true,
                default     : "UART_FIFO_RX4_8",
                options     : device_driverlib_peripheral.UART_FIFO_RX
            },
        ]
    },
    {
        name: "GROUP_DMA",
        displayName: "RTDMA Configuration",
        collapsed: true,
        config: [
            {
                name        : "useDMARX",
                displayName : "Use RTDMA for Receive",
                description : 'Whether or not to use DMA mode for RX.',
                hidden      : false,
                default     : false,
                onChange    : onChangeUseDMARX,
            },
            {
                name        : "disableDMARXonError",
                displayName : "Disable Rx RTDMA on receive error",
                description : "Choose whether the Rx RTDMA should be diabled on UART receive error",
                hidden      : true,
                default     : false,
            },
            {
                name        : "DMARXInst",
                displayName : "RTDMA instance to be used for Receive",
                description : "Choose the RTDMA instance for the channel used for Receive",
                hidden      : true,
                default     : dma_instances[0].name,
                options     : dma_instances,
            },
            
            {
                name        : "useDMATX",
                displayName : "Use RTDMA for Transmit",
                description : 'Whether or not to use DMA mode for TX.',
                hidden      : false,
                default     : false,
                onChange    : onChangeUseDMATX,
            },
            {
                name        : "DMATXInst",
                displayName : "RTDMA instance to be used for Transmit",
                description : "Choose the RTDMA instance for the channel used for Transmit",
                hidden      : true,
                default     : dma_instances[0].name,
                options     : dma_instances,
            },        
        ]
    },
    {
        name: "GROUP_SYS",
        displayName: "System Configuration",
        collapsed: true,
        config: []
    },
];

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
    return (Common.typeMatches(component.type, ["UART"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var uartModule = {
    peripheralName: "UART",
    displayName: "UART",
    maxInstances: Common.peripheralCount("UART"),
    defaultInstanceName: "myUART",
    description: "UART Peripheral",
    filterHardware : filterHardware,
    moduleInstances: (inst) => {
        var ownedInstances = []
        
        // Pinmux qualification
        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("UART", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
            if(pinmuxQualMod.name.includes("rx"))
            {
                pinmuxQualMod.args = {
                    padConfig : "PULLUP",
                    qualMode : "GPIO_QUAL_ASYNC",
                }
            }
            else
            {
                pinmuxQualMod.args = {
                    padConfig : "STD",
                    qualMode : "GPIO_QUAL_ASYNC",
                }
            }
        }
        ownedInstances = ownedInstances.concat(pinmuxQualMods)

        // Interrupts
        if (inst.enInterrupt && inst.registerInterrupts)
    	{
	        ownedInstances = ownedInstances.concat([{
	            name: "uartInt",
                group: "GROUP_ISR",  
	            displayName: "UART Interrupt",
	            moduleName: "/driverlib/interrupt.js",
	            collapsed: true,
	            args: {
            		$name : inst.$name + "_UART_INT",
                    typeInterruptName : true,
	                pinmuxPeripheralModule : "uart",
	                driverlibInt: "INT_#",
                    interruptHandler : "INT_" + inst.$name + "_ISR",
	            }
	        }])
    	}

        //DMA
        if (inst.useDMARX)
        {
            let dmaInst = inst.DMARXInst.split('_')[0].toLowerCase()
            ownedInstances = ownedInstances.concat([
                {
                    name: "uartRXDMA",
                    group: "GROUP_DMA",
                    displayName: "RX DMA",
                    moduleName: "/driverlib/" + dmaInst + ".js",
                    collapsed: true,
                    args: {
                        $name : inst.$name + "_RX_DMA",
                        burstSize : burstSizeMapping(inst.rxiflsel, inst)
                    },
                    requiredArgs: {
                        srcAddressLinked: inst.$name + "_RX_DMA_ADDRESS",
                        peripheralRXLinked: true,
                        databusWidthConfig: "DMA_CFG_READ_SIZE_8BIT",
                        writeDatasizeConfig: "DMA_CFG_WRT_SIZE_8BIT",
                        triggerSource: "DMA_TRIGGER_LINKED"
                    }
                },
            ])
        }

        if (inst.useDMATX) 
        {
            let dmaInst = inst.DMATXInst.split('_')[0].toLowerCase()
            ownedInstances = ownedInstances.concat([
                {
                    name: "uartTXDMA",
                    group: "GROUP_DMA",
                    displayName: "TX DMA",
                    moduleName: "/driverlib/" + dmaInst + ".js",
                    collapsed: true,
                    args: {
                        $name: inst.$name + "_TX_DMA",
                        burstSize : burstSizeMapping(inst.txiflsel, inst)
                    },
                    requiredArgs: {
                        destAddressLinked: inst.$name + "_TX_DMA_ADDRESS",
                        peripheralTXLinked: true,
                        databusWidthConfig: "DMA_CFG_READ_SIZE_8BIT",
                        writeDatasizeConfig: "DMA_CFG_WRT_SIZE_8BIT",
                        triggerSource: "DMA_TRIGGER_LINKED"
                    }
                },
            ])
        }

        ownedInstances = ownedInstances.concat([
            {
                name: "periphClock",
                group: "GROUP_SYS",
                displayName: "",
                moduleName: "/driverlib/perClock.js",
                collapsed: false,
                requiredArgs:{
                    pinmuxPeripheralModule : "uart",
                    peripheralInst: inst.$name,
                }
            },
            {
                name: "periphConfig",
                group: "GROUP_SYS",
                displayName: "",
                moduleName: "/driverlib/perConfig.js",
                collapsed: false,
                requiredArgs:{
                    pinmuxPeripheralModule : "uart",
                    peripheralInst: inst.$name
                }
            },
        ])
        
    	return ownedInstances;
    },
    config: config,
    templates: {
        boardc : "/driverlib/uart/uart.board.c.xdt",
        boardh : "/driverlib/uart/uart.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.uartPinmuxRequirements,
    validate : onValidate,

    // Static module for all instances to hold SYSCLK for baud calculation
    moduleStatic: {
        name: "UartGlobal",
        displayName: "UART Global",
        config: [
            {
                name: "baudSYSCLK",
                displayName: "SYSCLK [Hz] for Baud Rate",
                description: "This is the SYSCLK value assumed for baud rate calculation",
                //default: parseInt(Common.SYSCLK_getMaxMHz()*1e6),
                default: 100000000,
                getValue: () => {return Common.getSYSCLK()*(1e6);},
                readOnly : true,
            },
        ],
        modules: undefined,
    },
};


if (uartModule.maxInstances <= 0)
{
    delete uartModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(uartModule)
    Pinmux.addPinMuxQualGroupToConfig(uartModule)
}

exports = uartModule;