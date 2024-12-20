let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral = 
    system.getScript("/driverlib/device_driverlib_peripherals/" + 
        Common.getDeviceName().toLowerCase() + "_spi.js");

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


var pteOption = device_driverlib_peripheral.SPI_PTEPolarity;
if(!pteOption)
{
    pteOption = device_driverlib_peripheral.SPI_STEPolarity;
}

/* Intro splash on GUI */
let longDescription = "The Serial Peripheral Interface (SPI) "
    + "driver is a generic, full-duplex driver that transmits "
    + "and receives data on an SPI bus. SPI is sometimes called SSI "
    + "(Synchronous Serial Interface). The SPI protocol defines "
    + "the format of a data transfer over the SPI bus, but it "
    + "leaves flow control, data formatting, and handshaking "
    + "mechanisms to higher-level software layers."


function onChangeUseFIFO(inst, ui)
{
    onChangeUseInterrupts(inst, ui);
}

function onChangeRegisterInterrupts(inst, ui){
    if(inst.useInterrupts && inst.registerInterrupts){
        inst.registerSpiRxInt = true;
        inst.registerSpiTxInt = true;
        ui.registerSpiRxInt.hidden = false;
        ui.registerSpiTxInt.hidden = false;
    }
    else{
        inst.registerSpiRxInt = false;
        inst.registerSpiTxInt = false;
        ui.registerSpiRxInt.hidden = true;
        ui.registerSpiTxInt.hidden = true;
    }
}

function burstSizeMapping(fifoLevel, inst){
    switch(fifoLevel) {
        case "SPI_FIFO_TXEMPTY":
        case "SPI_FIFO_TX0":
        case "SPI_FIFO_RXEMPTY":
        case "SPI_FIFO_RX0":
        case "SPI_FIFO_RXDEFAULT":
            return 2;
        case "SPI_FIFO_TXFULL":
        case "SPI_FIFO_RXFULL":
            return 32;
        default:{
            let retString = fifoLevel.split('_')[2];
            return 2*Number(retString.slice(2));
        }
            
    }
}

function onValidate(inst, validation) 
{   
    var bitRateError = false;
    var bitRateInt;
    try{
        bitRateInt = parseInt(inst.bitRate);
        if (bitRateInt < ((Common.getSYSCLK()*(1e6))/128)|| bitRateInt > ((Common.getSYSCLK()*(1e6))/4))
        {
            bitRateError = true;
        }
    }
    catch (ex){
        bitRateError = true;
    }
    if(bitRateError)
    {
        validation.logError(
            "Enter an integer for bit rates between SYSCLK/128 and SYSCLK/4!", 
            inst, "bitRate");
    }

    if(bitRateInt >= 12500000 && !inst.useHSMode && !bitRateError){
        validation.logInfo(
            "Use High Speed mode for maximum performance", 
            inst, "bitRate");
    }

    if(bitRateInt < 12500000 && inst.useHSMode && !bitRateError){
        validation.logInfo(
            "Consider disabling High Speed mode", 
            inst, "bitRate");
    }

    if(inst.useHSMode){
        validation.logInfo(
            "Pinmux options are limited to GPIOs supporting high speed mode", 
            inst, "useHSMode");
    }

    if (inst.useDMARX && inst.spiRXDMA.databusWidthConfig == "DMA_CFG_SIZE_32BIT") {
        validation.logError("32 bit databus width is not valid while linked to SPI!", inst.spiRXDMA, "databusWidthConfig");   
    }

    if (inst.useDMATX && inst.spiTXDMA.databusWidthConfig == "DMA_CFG_SIZE_32BIT") {
        validation.logError("32 bit databus width is not valid while linked to SPI!", inst.spiTXDMA, "databusWidthConfig");   
    }

    if ((inst.useDMATX || inst.useDMARX) && !inst.useFifo) {
        validation.logError("FIFO must be enabled for DMA linking!", inst, "useFifo");   
    }

    if(inst.useDMARX && (inst.spiRXDMA.burstSize != burstSizeMapping(inst.rxFifo, inst)))
    {
        validation.logWarning(
            "Burst size is not equal to RX FIFO size", inst.spiRXDMA, "burstSize");
    }

    if(inst.useDMATX && (inst.spiTXDMA.burstSize != burstSizeMapping(inst.txFifo, inst)))
    {
        validation.logWarning(
            "Burst size is not equal to TX FIFO size", inst.spiTXDMA, "burstSize");
    }

    var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("SPI", inst)
    for (var pinmuxQualMod of pinmuxQualMods)
    {
        if (inst[pinmuxQualMod.name].padConfig.includes("OD"))
        {
            validation.logError("The open-drain pad configuration should not be used for the SPI module.", inst);
        }
    }
}

function onChangeUseInterrupts(inst, ui)
{
    onChangeRegisterInterrupts(inst, ui);
    if (inst.useInterrupts)
    {
        ui.registerInterrupts.hidden = false;
        if (inst.useFifo)
        {
            ui.enabledFIFOInterrupts.hidden = false;
            ui.enabledInterrupts.hidden = true;

            ui.txFifo.hidden = false;
            ui.rxFifo.hidden = false;
        }
        else
        {
            ui.enabledFIFOInterrupts.hidden = true;
            ui.enabledInterrupts.hidden = false;

            ui.txFifo.hidden = true;
            ui.rxFifo.hidden = true;
        }
        
    }
    else
    {
        ui.registerInterrupts.hidden = true;

        ui.enabledFIFOInterrupts.hidden = true;
        ui.enabledInterrupts.hidden = true;
        
        ui.txFifo.hidden = true;
        ui.rxFifo.hidden = true;
    }
}

function onChangeUseDMARX(inst, ui)
{
    if (inst.useDMARX)
    {
        ui.DMARXInst.hidden = false;
    }
    else 
    {
        ui.DMARXInst.hidden = true;
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

/* Array of SPI configurables that are common across device families */
let config = [
    {
        name: "GROUP_PERCFG",
        displayName: "Peripheral Configuration",
        collapsed: false,
        config: [
            {
                name        : "transferProtocol",
                displayName : "Transfer Protocol",
                description : 'Mode for transfer protocol',
                hidden      : false,
                default     : device_driverlib_peripheral.SPI_TransferProtocol[0].name,
                options     : device_driverlib_peripheral.SPI_TransferProtocol
            },
        
            {
                name        : "mode",
                displayName : "Mode",
                description : 'Mode for device',
                hidden      : false,
                default     : device_driverlib_peripheral.SPI_Mode[0].name,
                options     : device_driverlib_peripheral.SPI_Mode
            },
        
            {
                name        : "ptePolarity",
                legacyNames : ["stePolarity"],
                displayName : "PTE Polarity",
                description : 'Polarity of the PTE Pin',
                hidden      : false,
                default     : pteOption[0].name,
                options     : pteOption
            },
        
            {
                name        : "emulationMode",
                displayName : "Emulation Mode",
                description : 'Emulation Mode',
                hidden      : false,
                default     : device_driverlib_peripheral.SPI_EmulationMode[0].name,
                options     : device_driverlib_peripheral.SPI_EmulationMode
            },
        
            {
                name        : "bitRate",
                displayName : "Bit Rate (Hz)",
                description : 'Bit rate for device in (Hz). Must be between SYSCLK/128 and SYSCLK/4',
                hidden      : false,
                default     : 2000000
            },

            {
                name        : "useHSMode",
                displayName : "Enable High Speed Mode",
                description : 'Whether or not to use SPI in High Speed mode.',
                hidden      : false,
                default     : false
                
            },
        
            {
                name        : "dataWidth",
                displayName : "Data Width",
                description : 'Data width used for transmission',
                hidden      : false,
                default     : '16',
                options     : [
                    {name: "1"},
                    {name: "2"},
                    {name: "3"},
                    {name: "4"},
                    {name: "5"},
                    {name: "6"},
                    {name: "7"},
                    {name: "8"},
                    {name: "9"},
                    {name: "10"},
                    {name: "11"},
                    {name: "12"},
                    {name: "13"},
                    {name: "14"},
                    {name: "15"},
                    {name: "16"}
                ]
            },
            
            {
                name        : "useFifo",
                displayName : "Use FIFO",
                description : 'Whether or not to use FIFO mode.',
                hidden      : false,
                onChange    : onChangeUseFIFO,
                default     : true
                
            },
            {
                name        : "loopback",
                displayName : "Use Loopback Mode",
                description : 'Whether or not to use loopback mode.',
                hidden      : false,
                default     : false
                
            },
            
            {
                name: "useCase",
                displayName : "Use Case",
                description : 'Peripheral use case',
                hidden      : false,
                default     : 'ALL',
                options     : Pinmux.getPeripheralUseCaseNames("SPI"),
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
                name        : "useInterrupts",
                displayName : "Use Interrupt",
                description : 'Whether or not to use Interrupt mode.',
                hidden      : false,
                onChange    : onChangeUseInterrupts,
                default     : true
                
            },
            {
                name        : "registerInterrupts",
                displayName : "Register Interrupt Handler",
                description : 'Whether or not to register interrupt handlers in the interrupt module.',
                hidden      : false,
                default     : false,
                onChange    : onChangeRegisterInterrupts
                
            },
            {
                name: "registerSpiRxInt",      
                displayName: "Register RX Interrupt",
                hidden: true,
                default: false,
            },
            {
                name: "registerSpiTxInt",
                displayName: "Register TX Interrupt",
                hidden: true,
                default: false,
            },
            {
                name        : "enabledInterrupts",
                displayName : "Enabled Interrupts",
                description : 'Which interrupts to enable.',
                hidden      : true,
                default     : [],
                minSelections: 0,
                options     : device_driverlib_peripheral.SPI_INT.slice(0,2)
                
            },
            {
                name        : "enabledFIFOInterrupts",
                displayName : "Enabled FIFO Interrupts",
                description : 'Which FIFO interrupts to enable.',
                hidden      : false,
                default     : [],
                minSelections: 0,
                options     : device_driverlib_peripheral.SPI_INT.slice(2)
                
            },
        
            {
                name        : "txFifo",
                displayName : "Transmit FIFO Interrupt Level",
                description : 'Transmit FIFO interrupt level used.',
                hidden      : false,
                default     : device_driverlib_peripheral.SPI_TxFIFOLevel[0].name,
                options     : device_driverlib_peripheral.SPI_TxFIFOLevel
            },
        
            {
                name        : "rxFifo",
                displayName : "Receive FIFO Interrupt Level",
                description : 'Receive FIFO interrupt level used.',
                hidden      : false,
                default     : device_driverlib_peripheral.SPI_RxFIFOLevel[0].name,
                options     : device_driverlib_peripheral.SPI_RxFIFOLevel
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
    return (Common.typeMatches(component.type, ["SPI"]));
}

if (Common.onlyPinmux())
{
    config = [config[config.length - 1]];
}

var spiModule = {
    peripheralName: "SPI",
    displayName: "SPI",
    maxInstances: Common.peripheralCount("SPI"),
    defaultInstanceName: "mySPI",
    description: "Serial Peripheral Interface Peripheral",
    filterHardware : filterHardware,
    config: config,
    moduleInstances: (inst) => {
        var submodules = []

        var pinmuxQualMods = Pinmux.getGpioQualificationModInstDefinitions("SPI", inst)
        for (var pinmuxQualMod of pinmuxQualMods)
        {
            pinmuxQualMod.args = {
                qualMode : "GPIO_QUAL_ASYNC",
            }
            pinmuxQualMod.args.padConfig = "STD";
        }
        submodules = submodules.concat(pinmuxQualMods)
        
        if (inst.useInterrupts && inst.registerInterrupts)
        {
            if(inst.registerSpiRxInt){
                submodules = submodules.concat([{
                    name: "spiRXInt",      
                    group: "GROUP_ISR",
                    displayName: "RX Interrupt",
                    moduleName: "/driverlib/interrupt.js",
                    collapsed: true,
                    args: {
                        $name : inst.$name + "_RX_INT",
                        typeInterruptName : true,
                        pinmuxPeripheralModule : "spi",
                        driverlibInt: "INT_#_RX",
                        interruptHandler : "INT_" + inst.$name + "_RX_ISR",
                    }
                }]);
            }
            if(inst.registerSpiTxInt){
                submodules = submodules.concat([{
                    name: "spiTXInt",    
                    group: "GROUP_ISR",  
                    displayName: "TX Interrupt",
                    moduleName: "/driverlib/interrupt.js",
                    collapsed: true,
                    args: {
                        $name : inst.$name + "_TX_INT",
                        typeInterruptName : true,
                        pinmuxPeripheralModule : "spi",
                        driverlibInt: "INT_#_TX",
                        interruptHandler : "INT_" + inst.$name + "_TX_ISR",
                    }
                }]);
            }
        }

        if (inst.useDMARX)
        {
            let dmaInst = inst.DMARXInst.split('_')[0].toLowerCase()
            submodules = submodules.concat([
                {
                    name: "spiRXDMA",
                    group: "GROUP_DMA",    
                    displayName: "RX DMA",
                    moduleName: "/driverlib/" + dmaInst + ".js",
                    collapsed: true,
                    args: {
                        $name : inst.$name + "_RX_DMA",
                        burstSize : burstSizeMapping(inst.rxFifo, inst)
                    },
                    requiredArgs: {
                        srcAddressLinked: inst.$name + "_RX_DMA_ADDRESS",
                        peripheralRXLinked: true,
                        databusWidthConfig: "DMA_CFG_READ_SIZE_16BIT",
                        writeDatasizeConfig: "DMA_CFG_WRT_SIZE_16BIT",
                        triggerSource: "DMA_TRIGGER_LINKED"
                    }
                },
            ])
        }

        if (inst.useDMATX) 
        {
            let dmaInst = inst.DMATXInst.split('_')[0].toLowerCase()
            submodules = submodules.concat([
                {
                    name: "spiTXDMA",
                    group: "GROUP_DMA",
                    displayName: "TX DMA",
                    moduleName: "/driverlib/" + dmaInst + ".js",
                    collapsed: true,
                    args: {
                        $name: inst.$name + "_TX_DMA",
                        burstSize : burstSizeMapping(inst.txFifo, inst)
                    },
                    requiredArgs: {
                        destAddressLinked: inst.$name + "_TX_DMA_ADDRESS",
                        peripheralTXLinked: true,
                        databusWidthConfig: "DMA_CFG_READ_SIZE_16BIT",
                        writeDatasizeConfig: "DMA_CFG_WRT_SIZE_16BIT",
                        triggerSource: "DMA_TRIGGER_LINKED"
                    }
                },
            ])
        }

        submodules = submodules.concat([
            {
                name: "periphClock",
                group: "GROUP_SYS",
                displayName: "",
                moduleName: "/driverlib/perClock.js",
                collapsed: false,
                requiredArgs:{
                    pinmuxPeripheralModule : "spi",
                    peripheralInst: inst.$name
                }
            },
            {
                name: "periphConfig",
                group: "GROUP_SYS",
                displayName: "",
                moduleName: "/driverlib/perConfig.js",
                collapsed: false,
                requiredArgs:{
                    pinmuxPeripheralModule : "spi",
                    peripheralInst: inst.$name
                }
            },
        ])

        return submodules;
    },
    templates: {
        boardc : "/driverlib/spi/spi.board.c.xdt",
        boardh : "/driverlib/spi/spi.board.h.xdt"
    },
    pinmuxRequirements    : Pinmux.spiPinmuxRequirements,
    validate    : onValidate,
    // Static module for all instances to hold SYSCLK for baud calculation
    moduleStatic: {
        name: "SpiGlobal",
        displayName: "SPI Global",
        config: [
            {
                name: "baudSYSCLK",
                displayName: "SYSCLK [Hz]",
                description: "This is the SYSCLK value that determines baud rate range for SPI",
                //default: parseInt(Common.SYSCLK_getMaxMHz()*1e6),
                default: 100000000,
                readOnly : true,
                getValue : () => {return Common.getSYSCLK()*(1e6)}
            },
        ],
        modules: undefined,
    },
};


if (spiModule.maxInstances <= 0)
{
    delete spiModule.pinmuxRequirements;
}
else
{
    Pinmux.addCustomPinmuxEnumToConfig(spiModule)
    Pinmux.addPinMuxQualGroupToConfig(spiModule)
}


exports = spiModule;