const device  = system.deviceData.device
/////////////////////////////////////////////Device Specific Functions//////////////////////////
// For a new device, you need to find out which functions are available for the device
// and add it to the list.
// If a new subcategory is needed, just define a new variable and address that in the related function.xdt file.
// For example, if you need a new Include Header type, you can add Include_Headers_Typex to the list and then go to Include folder and add that
//variable to the Include.xdt. Also, you need to copy and past your content to a new file, let's call Include_Headers_xxx.xdt. 

// C29 DEVICES

// Multi-core devices list
const multi_core 																= ["F29H85x"]

//
// Available Include Header 
//
// General Include Header 
const Include_Headers_Type0														= []

// Include Header with hw_ipc.h
const Include_Headers_Type1														= []

// Include Header with hw_lcm.h
const Include_Headers_Type2														= []

// Include Header with driverlib.h  
const Include_Headers_Type3														= ["F29H85x"]

//
// Available Boot_CM 
//
// Devices with Boot_CM
const Device_Boot_CM 															= []

//
// Available Initilization 
//
//Function to initialize the device (suprano dual-core devices, Type0)
const Initilization_General_Type0												= []

// Function to initialize the device (suprano single-core device, Type1)
const Initilization_General_Type1												= []

//configuring the XTAL for device initilization
const Initilization_XTAL_Type0												= []

//configuring device initilization with Device_initGPIO()
const Initilization_Device_initGPIO_Type0									= []

//configuring the AGPIO pins 12, 13, 20, 21, 28 in digital mode for device initilization
const Initilization_AGPIO_Type0													= []

//configuring the AGPIO pins 12, 13, 20, 21, 28 in digital mode and enabling lockstep module for device initilization
const Initilization_AGPIO_Type1													= []

//configuring the GPIO pins 22, 23 in digital mode and Disabling DC DC in Analog block for device initilization
const Initilization_GPIO_22_23											= []

//configuring the GPIO pins 20, 21 in digital mode and Lock VREGCTL Register for device initilization
const Initilization_GPIO_20_21_Type0										= []

//configuring the Lock VREGCTL Register for device initilization
const Initilization_AGPIO_Dual_Core_Type0										= []

//configuring the GPIO pins 11, 12, 13, 16, 17, 20, 21, 24, 
// and 28 in digital mode, turn on all peripherals, and Lock VREGCTL Register for device initilization
const Initilization_GPIO_20_21_Type1										= []

// configuring F29H85x for device initialization
const Initialization_Tri_Core_Type0											= ["F29H85x"]

//
// Available InitGPIO 
//
// Disabling pin locks and enabling pullups on GPIOs Port A-Port F.
const InitGPIO_PortA_PortF_Type0 											= []

// Disabling pin locks and enabling pullups on GPIOs only Ports A, B, and H.
const InitGPIO_PortA_PortH_Type0 											= []

// Disabling pin locks and enabling pullups on GPIOs Ports A, B, C, D, E, F, and H.
const InitGPIO_PortA_PortH_Type1 											= []

// Disabling pin locks and enabling pullups on GPIOs only Ports A, B, C, G, and H.
const InitGPIO_PortA_PortH_Type2 											= []

//
// Available VerifyXTAL 
//
// verifying the XTAL frequency
const VerifyXTAL_Type0														= []

// verifying the XTAL frequency with Turning-on XTAL
const VerifyXTAL_Type1 														= ["F29H85x"]

//
// Available BootCPU2 
//
// Boot CPU2 to Flash Sector 0 to Sector 13 
const Boot_CPU2_Type0														=[]

// Boot CPU2 to Flash Bank 0 to Bank 4
const Boot_CPU2_Type1														=[]

// Boot CPU2 with different boot mode. It can be from PARALLEL, SCI, SPI, I2C, CAN, RAM, and FLASH.
const Boot_CPU2_Boot_Mode_Type0												=[]

//
// Available Enable_Unbounded_GPIO_Pullups 
//
// enable pullups for the unbonded GPIOs on the 100PZ or 176PTP package.
const Enable_Unbounded_GPIO_Pullups_100PZ_176PTP_Type0						=[]

// enable pullups for the unbonded GPIOs on the 176PTP package.
const Enable_Unbounded_GPIO_Pullups_176PTP_Type0							=[]

//
// Available Configure_TMX_Analog_Trim 
//
// Implementing Analog trim of TMX devices with ADC A, ADC B, and ADC D
const Configure_TMX_Analog_Trim_Type0										=[]

// Implementing Analog trim of TMX devices with ADC A, ADC B, ADC C, and ADC D
const Configure_TMX_Analog_Trim_Type1										=[]

// Implementing Analog trim of TMX devices with ADC A, ADC B, ADC C, and ADC D starting with If condition
const Configure_TMX_Analog_Trim_Type2										=[]

//
// Available EnableAllPeripherals 
//
// Enabling HRCAL for F2838x with checking if context is on CPU1. If enabling HRCAL in your device needs 
//to be done only in CPU1, add your device to this list.
const EnableAllPeripherals_CLK_HRCAL								= []

// Enabling HRPWM for F2837xD with checking if context is on CPU1. If enabling HRPWM in your device needs 
//to be done only in CPU1, add your device to this list.
const EnableAllPeripherals_CLK_HRPWM								= []

// Enabling EMIF with checking if context is on CPU1. If enabling EMIF in your device needs 
//to be done only in CPU1, add your device to this list.
const EnableAllPeripherals_CLK_EMIF_With_If									= []

// Checking devices need enabling peripheral EMIF1. If peripheral EMIF1 needs to be enabled 
//in your device, add your device to this list.
const EnableAllPeripherals_CLK_EMIF1										= []

// Checking devices need enabling peripheral EMIF2. If peripheral EMIF2 needs to be enabled 
//in your device, add your device to this list.
const EnableAllPeripherals_CLK_EMIF2										= []

// Enabling USB and UPPA with checking if context is on CPU1. If enabling USB or UPPA in your device needs 
//to be done only in CPU1, add your device to this list.
const EnableAllPeripherals_CLK_USB_UPPA							= []

// Checking devices with SysCtl_enablePeripheral for peripheral USBA. If peripheral USBA needs to be enabled 
//in your device, add your device to this list.
const EnableAllPeripherals_CLK_USBA											= []

// Checking devices with SysCtl_enablePeripheral for peripheral UPPA. If peripheral UPPA needs to be enabled 
//in your device, add your device to this list.
const EnableAllPeripherals_CLK_UPPA											= []

// Enabling DCC and ECAT, and MCAN with checking if context is on CPU1. If enabling DCC and ECAT, and MCAN  
//in your device needs to be done only in CPU1, add your device to this list.
const EnableAllPeripherals_CLK_DCC_ECAT_MCAN							= []

// Enabling CLA1BGCRC with checking if context is on CPU1. If enabling CLA1BGCRC  
//in your device needs to be done only in CPU1, add your device to this list.
const EnableAllPeripherals_CLK_CLA1BGCRC							= []

// Enabling PMBUSA with checking if context is on CPU1. If enabling PMBUSA  
//in your device needs to be done only in CPU1, add your device to this list.
const EnableAllPeripherals_CLK_PMBUSA									= [ ]

// Enabling CLA1 with checking if context is on CPU1. If enabling CLA1  
//in your device needs to be done only in CPU1, add your device to this list.
const EnableAllPeripherals_CLK_CLA1									= []

//
// Clocktree 
//
// clocktree Configuring Analog Trim in case of untrimmed or TMX sample
const clocktree_Analog_Trim_Type0                                         	=[]

// clocktree Setting up PLL control and clock dividers
const clocktree_PLL_Ctl_Dividers_Type0                                 		=[]

// clocktree Setting up PLL and AUXPLL control and clock dividers
//and AUXPLL control and clock dividers needed for CMCLK
const clocktree_PLL_Ctl_Dividers_Type1                                  =[]

// clocktree Setting up PLL control and clock dividers
//and AUXPLL control and clock dividers needed for CMCLK
const clocktree_PLL_Ctl_Dividers_Type2                                  =[]

// clocktree Setting up PLL control and clock dividers
const clocktree_PLL_Ctl_Dividers_Type3                                  =["F29H85x"]


// clocktree asserts will check that the #defines for the clock rates in device.h
//set clock source for CANA, CANB, MCAN peripherals and EPWM and EMIF1 clock divider
const clocktree_Asserts_Type0                                          =[]

// clocktree asserts will check that the #defines for the clock rates in device.h
//set clock source for CANA, CANB, MCAN, ECAT, ENET peripherals and EPWM and EMIF1 clock divider
const clocktree_Asserts_Type1                                          =[]

// clocktree asserts will check that the #defines for the clock rates in device.h
//set clock source for CANA, MCANA, MCANB, ECAT peripherals and EPWM and EMIF1 clock divider
const clocktree_Asserts_Type2                                          =[]

// clocktree asserts will check that the #defines for the clock rates in device.h
//set clock source for CANA and MCAN peripherals
const clocktree_Asserts_Type3                                          =[]

// clocktree asserts will check that the #defines for the clock rates in device.h
//set clock source for CANA peripheral
const clocktree_Asserts_Type4                                          =[]

// clocktree asserts will check that the #defines for the clock rates in device.h
const clocktree_Asserts_Type5                                          =[]

// clocktree asserts will check that the #defines for the clock rates in device.h
//set clock source for MCANA, MCANB, MCANC, MCAND, MCANE, MCANF, ECAT peripherals and EPWM and EMIF1 clock divider 
const clocktree_Asserts_Type6                                          =["F29H85x"]

///////////////////////////List of Template Files For Different Functions///////////////////////////
// If you want to add a new sub-function from available functions, you need to create a .xdt file in related function folder
// and add it here.

// Template for General Header
var Include 	= system.getTemplate('Include/Include.xdt');

// // Template for Boot_CM
// var Boot_CM = system.getTemplate('BootCM/Boot_CM.xdt');

// Template for device initialization
var Initialization = system.getTemplate('Initialization/Initialization.xdt');

// // Template for disabling pin locks and enabling pullups on GPIOs Port A-Port F.
// var InitGPIO = system.getTemplate('InitGPIO/InitGPIO.xdt');

// Template for verifying the XTAL frequency
var VerifyXTAL = system.getTemplate('VerifyXTAL/VerifyXTAL.xdt');

// Template for Error handling function
var Error_Handling = system.getTemplate('ErrorChecking/Error_Handling.xdt');

// Template for Booting CPU2/ CPU3
var Boot_Cpu_2_3 = system.getTemplate('BootCpu/Boot_Cpu_2_3.xdt');

// Template for Errata Workaround
var Workaround = system.getTemplate('Workaround/Workaround.xdt');

// // Template for boot CPU2 
// var Boot_CPU2 = system.getTemplate('BootCPU2/Boot_CPU2.xdt');

// // Template for enable unbounded GPIO pullups
// var Enable_Unbounded_GPIO_Pullups = system.getTemplate('EnableUnboundedGPIOPullups/Enable_Unbounded_GPIO_Pullups.xdt');

// // Template for implementing Analog trim of TMX devices 
// var Configure_TMX_Analog_Trim = system.getTemplate('ConfigureTMXAnalogTrim/Configure_TMX_Analog_Trim.xdt');

// // Template for enabling all the peripherals
// var Enable_All_Peripherals 	= system.getTemplate('EnableAllPeripherals/Enable_All_Peripherals.xdt');


exports = {
	Include : Include ,
	// Boot_CM : Boot_CM,
	Initialization : Initialization,
	// InitGPIO : InitGPIO,
	VerifyXTAL : VerifyXTAL,
	Error_Handling : Error_Handling,
	Boot_Cpu_2_3 : Boot_Cpu_2_3,
	Workaround : Workaround,
	// Boot_CPU2 : Boot_CPU2,
	// Enable_Unbounded_GPIO_Pullups : Enable_Unbounded_GPIO_Pullups,
	// Configure_TMX_Analog_Trim : Configure_TMX_Analog_Trim,
	// Enable_All_Peripherals : Enable_All_Peripherals,
	device : device,
	multi_core : multi_core,
	Include_Headers_Type0 : Include_Headers_Type0,
	Include_Headers_Type1 : Include_Headers_Type1,
	Include_Headers_Type2 : Include_Headers_Type2,
	Include_Headers_Type3 : Include_Headers_Type3,
	Device_Boot_CM  : Device_Boot_CM ,
	Initilization_General_Type0 : Initilization_General_Type0,
	Initilization_General_Type1 : Initilization_General_Type1,
	Initilization_AGPIO_Type0	 : Initilization_AGPIO_Type0	,
	Initilization_AGPIO_Type1 : Initilization_AGPIO_Type1	,
	Initilization_GPIO_22_23 : Initilization_GPIO_22_23,
	Initilization_GPIO_20_21_Type0 : Initilization_GPIO_20_21_Type0,
	Initilization_AGPIO_Dual_Core_Type0 : Initilization_AGPIO_Dual_Core_Type0,
	Initilization_GPIO_20_21_Type1 : Initilization_GPIO_20_21_Type1,
	Initilization_XTAL_Type0 : Initilization_XTAL_Type0,
	Initilization_Device_initGPIO_Type0 : Initilization_Device_initGPIO_Type0,
	Initialization_Tri_Core_Type0 : Initialization_Tri_Core_Type0,
	InitGPIO_PortA_PortF_Type0 : InitGPIO_PortA_PortF_Type0,
	InitGPIO_PortA_PortH_Type0 : InitGPIO_PortA_PortH_Type0,
	InitGPIO_PortA_PortH_Type1 : InitGPIO_PortA_PortH_Type1,
	InitGPIO_PortA_PortH_Type2 : InitGPIO_PortA_PortH_Type2,
	VerifyXTAL_Type0 : VerifyXTAL_Type0,
	VerifyXTAL_Type1 : VerifyXTAL_Type1,
    Boot_CPU2_Type0 : Boot_CPU2_Type0,
	Boot_CPU2_Type1 : Boot_CPU2_Type1,
	Boot_CPU2_Boot_Mode_Type0 : Boot_CPU2_Boot_Mode_Type0,
	Enable_Unbounded_GPIO_Pullups_100PZ_176PTP_Type0 : Enable_Unbounded_GPIO_Pullups_100PZ_176PTP_Type0,
	Enable_Unbounded_GPIO_Pullups_176PTP_Type0 : Enable_Unbounded_GPIO_Pullups_176PTP_Type0,
	Configure_TMX_Analog_Trim_Type0 : Configure_TMX_Analog_Trim_Type0,
	Configure_TMX_Analog_Trim_Type1 : Configure_TMX_Analog_Trim_Type1,
	Configure_TMX_Analog_Trim_Type2 : Configure_TMX_Analog_Trim_Type2,
	EnableAllPeripherals_CLK_HRCAL : EnableAllPeripherals_CLK_HRCAL,
	EnableAllPeripherals_CLK_HRPWM : EnableAllPeripherals_CLK_HRPWM,
	EnableAllPeripherals_CLK_EMIF_With_If : EnableAllPeripherals_CLK_EMIF_With_If,
	EnableAllPeripherals_CLK_EMIF1 : EnableAllPeripherals_CLK_EMIF1,
	EnableAllPeripherals_CLK_EMIF2: EnableAllPeripherals_CLK_EMIF2,
	EnableAllPeripherals_CLK_USB_UPPA : EnableAllPeripherals_CLK_USB_UPPA,
	EnableAllPeripherals_CLK_USBA : EnableAllPeripherals_CLK_USBA,
	EnableAllPeripherals_CLK_UPPA : EnableAllPeripherals_CLK_UPPA,
	EnableAllPeripherals_CLK_DCC_ECAT_MCAN : EnableAllPeripherals_CLK_DCC_ECAT_MCAN,
	EnableAllPeripherals_CLK_CLA1BGCRC : EnableAllPeripherals_CLK_CLA1BGCRC,
	EnableAllPeripherals_CLK_PMBUSA : EnableAllPeripherals_CLK_PMBUSA,
	EnableAllPeripherals_CLK_CLA1 : EnableAllPeripherals_CLK_CLA1,
	clocktree_Analog_Trim_Type0 : clocktree_Analog_Trim_Type0,
	clocktree_PLL_Ctl_Dividers_Type0 : clocktree_PLL_Ctl_Dividers_Type0,
	clocktree_PLL_Ctl_Dividers_Type1 : clocktree_PLL_Ctl_Dividers_Type1,
	clocktree_PLL_Ctl_Dividers_Type2 : clocktree_PLL_Ctl_Dividers_Type2,
	clocktree_PLL_Ctl_Dividers_Type3 : clocktree_PLL_Ctl_Dividers_Type3,
	clocktree_Asserts_Type0 : clocktree_Asserts_Type0,
	clocktree_Asserts_Type1 : clocktree_Asserts_Type1,
	clocktree_Asserts_Type2 : clocktree_Asserts_Type2, 
	clocktree_Asserts_Type3 : clocktree_Asserts_Type3,
	clocktree_Asserts_Type4 : clocktree_Asserts_Type4,
	clocktree_Asserts_Type5 : clocktree_Asserts_Type5,
	clocktree_Asserts_Type6 : clocktree_Asserts_Type6 

}