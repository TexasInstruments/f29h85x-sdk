const device  = system.deviceData.device

/////////////////////////////////////////////Device Specific Functions//////////////////////////
// For a new device, you need to find out which functions are available for the device
// and add it to the list.
// If a new subcategory is needed, just define a new variable and address that in the related function.xdt file.
// For example, if you need a new Include Header type, you can add Initilization_Typex to the list and then go to Include folder and add that
//variable to the Initilization.xdt. Also, you need to copy and past your content to a new file, let's call Initilization_xxx.xdt. 

// Multi-core devices list
const multi_core 																= ["F29H85x"]

//
// Available BootCM 
//
// Devices with Boot_CM
const Device_Boot_CM 															= []

//
// Available Initialization 
//
//Function to initialize the device (legacy dual core device)
const Initilization_General_DualCore_Type0										= []

// General single core device initilization Type0 with DEVICE_FLASH_WAITSTATES=3
const Initilization_General_Type0												= []

// General single core device initilization Type1 with DEVICE_FLASH_WAITSTATES=2
const Initilization_General_Type1												= []

//configuring the AGPIO pins 12, 13, 20, 21, 28 in digital mode for device initilization
const Initilization_AGPIO_Type0													= []

//configuring the GPIO pins 22, 23 in digital mode and Disabling DC DC in Analog block for device initilization
const Initilization_GPIO_22_23												= []

//configuring the GPIO pins 20, 21 in digital mode for device initilization
const Initilization_GPIO_20_21_Type0											= []

//configuring the GPIO pins 20, 21 in digital mode for device initilization
const Initilization_GPIO_20_21_Type1											= []

//configuring the GPIO pins 20, 21 in digital mode for device initilization
const Initilization_GPIO_20_21_Type2											= []

//configuring device initilization with Device_initGPIO() call
const Initilization_Device_initGPIO_Type0										= []

//
// Available VerifyXTAL 
//
// verifying the XTAL frequency
const VerifyXTAL_Type0 															= ["F29H85x"]

// verifying the XTAL frequency with endIf condition
const VerifyXTAL_Type1															= []

//
// Available Error_Handling 
//
// Error handling function
const Error_Handling_Type0 														= []

// Error handling function with "Close the Doxygen group"
const Error_Handling_Type1 														= ["F29H85x"]

//
// Available BootCPU2 
//
// Boot CPU2 to Flash Sector 0 to Sector 13 
const Boot_CPU2_Type0															=[]

// Boot CPU2 to Flash Bank 0 to Bank 4
const Boot_CPU2_Type1														=[]

// Boot CPU2 with different boot modes. It can be from PARALLEL, SCI, SPI, I2C, CAN, RAM, and FLASH.
const Boot_CPU2_Boot_Mode_Type0													=[]

//
// Available Enable_Unbounded_GPIO_Pullups 
//
// enable pullups for the unbonded GPIOs on the 100PZ or 176PTP package.
const Enable_Unbounded_GPIO_Pullups_100PZ_176PTP_Type0							=[]

// enable pullups for the unbonded GPIOs on the 176PTP package.
const Enable_Unbounded_GPIO_Pullups_176PTP_Type0							    =[]

//
// Available Configure_TMX_Analog_Trim 
//
// Implementing Analog trim of TMX devices with ADC A, ADC B, ADC C, and ADC D
const Configure_TMX_Analog_Trim_Type1											=[]

// Implementing Analog trim of TMX devices with ADC A, ADC B, ADC C, and ADC D starting with If condition
const Configure_TMX_Analog_Trim_Type2											=[]

///////////////////////////List of Template Files For Different Functions///////////////////////////
// If you want to add a new sub-function from available functions, you need to create a .xdt file in related function folder
// and add it here.

// Template for General Header
var Include 	= system.getTemplate('Include/Include.xdt');

// // Template for Boot_CM
// var Boot_CM 	= system.getTemplate('BootCM/Boot_CM.xdt');

// // Template for device initilization
// var Initilization 	= system.getTemplate('Initilization/Initilization.xdt');

// // Template for disabling pin locks and enabling pullups on all devices.
// var InitGPIO 	= system.getTemplate('InitGPIO/InitGPIO.xdt');

// Template for verifying the XTAL frequency
var VerifyXTAL 	= system.getTemplate('VerifyXTAL/VerifyXTAL.xdt');

// Template for Error handling function
var Error_Handling 	= system.getTemplate('ErrorChecking/Error_Handling.xdt');

// Template for Booting CPU2/ CPU3
var Boot_Cpu_2_3 = system.getTemplate('BootCpu/Boot_Cpu_2_3.xdt');

// Template for Errata Workaround
var Workaround = system.getTemplate('Workaround/Workaround.xdt');

// // Template for boot CPU2 with Flash Sector 0 to Sector 13
// var Boot_CPU2 	= system.getTemplate('BootCPU2/Boot_CPU2.xdt');

// // Template for enable pullups for the unbonded GPIOs on the 176PTP package.
// var Enable_Unbounded_GPIO_Pullups 	= system.getTemplate('EnableUnboundedGPIOPullups/Enable_Unbounded_GPIO_Pullups.xdt');

// // Template for implementing Analog trim of TMX devices ADC A, ADC B, ADC C, and ADC D
// var Configure_TMX_Analog_Trim 	= system.getTemplate('ConfigureTMXAnalogTrim/Configure_TMX_Analog_Trim.xdt');

// // Template for enabling all the peripherals
// var Enable_All_Peripherals 	= system.getTemplate('EnableAllPeripherals/Enable_All_Peripherals.xdt');

exports = {
	Include : Include,
	// Boot_CM : Boot_CM,
	// Initilization : Initilization,
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
	Device_Boot_CM : Device_Boot_CM ,
	Initilization_General_Type0 : Initilization_General_Type0,
	Initilization_General_Type1 : Initilization_General_Type1,
	Initilization_General_DualCore_Type0 : Initilization_General_DualCore_Type0,
	Initilization_AGPIO_Type0 : Initilization_AGPIO_Type0,
	Initilization_GPIO_22_23 : Initilization_GPIO_22_23,
	Initilization_GPIO_20_21_Type0 : Initilization_GPIO_20_21_Type0,
	Initilization_GPIO_20_21_Type1 : Initilization_GPIO_20_21_Type1,
	Initilization_GPIO_20_21_Type2 : Initilization_GPIO_20_21_Type2,
	Initilization_Device_initGPIO_Type0 : Initilization_Device_initGPIO_Type0,
	VerifyXTAL_Type0 : VerifyXTAL_Type0,
	VerifyXTAL_Type1 : VerifyXTAL_Type1,
	Error_Handling_Type0 : Error_Handling_Type0,
	Error_Handling_Type1 : Error_Handling_Type1,
    Boot_CPU2_Type0 : Boot_CPU2_Type0,
	Boot_CPU2_Type1 : Boot_CPU2_Type1,
	Boot_CPU2_Boot_Mode_Type0 : Boot_CPU2_Boot_Mode_Type0,
	Enable_Unbounded_GPIO_Pullups_100PZ_176PTP_Type0 : Enable_Unbounded_GPIO_Pullups_100PZ_176PTP_Type0,
	Enable_Unbounded_GPIO_Pullups_176PTP_Type0 : Enable_Unbounded_GPIO_Pullups_176PTP_Type0,
	Configure_TMX_Analog_Trim_Type1 : Configure_TMX_Analog_Trim_Type1,
	Configure_TMX_Analog_Trim_Type2 : Configure_TMX_Analog_Trim_Type2
}