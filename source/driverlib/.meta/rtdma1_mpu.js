let Common   = system.getScript("/driverlib/Common.js");
let Pinmux   = system.getScript("/driverlib/pinmux.js");

let device_driverlib_peripheral =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_rtdma.js");

let device_driverlib_memmap =
    system.getScript("/driverlib/device_driverlib_peripherals/" +
        Common.getDeviceName().toLowerCase() + "_memmap.js");

let rtdma_mpu_shared =
    system.getScript("/driverlib/rtdma_mpu.js");
  
var sharedModuleInstances = undefined;

let str = Common.isAllocationSetupMode() ? ""  : system.context

var uiAddOption = "instanceOnly"
if (Common.isContextCPU1())
{
    uiAddOption = "staticAndInstance"
}

var rtdma1mpuModule = {
    peripheralName        : "RTDMA1_MPU",
    displayName           : "RTDMA1 MPU",
    totalMaxInstances     : 16,
    defaultInstanceName   : "my" + str + "RTDMA1MPU",
    config                : rtdma_mpu_shared.getRTDMAMPUConfig("RTDMA1"),
    sharedModuleInstances : sharedModuleInstances,
    templates: {
        boardc : "/driverlib/rtdma1_mpu/rtdma1_mpu.board.c.xdt",
        boardh : "/driverlib/rtdma1_mpu/rtdma1_mpu.board.h.xdt"
    },

    moduleStatic: {
        name        : "rtdma1mpuGlobal",
        displayName : "RTDMA1 MPU Global",
        config      : rtdma_mpu_shared.getRTDMAMPUGlobalConfig("RTDMA1"),
        validate    : rtdma_mpu_shared.onValidateStatic,
        shouldBeAllocatedAsResource: true,
        alwaysAllocateAsResource: true,
    },
    shouldBeAllocatedAsResource : true,
    alwaysAllocateAsResource    : true,
    validate        : rtdma_mpu_shared.onValidate,
    uiAdd           : uiAddOption
};


exports = rtdma1mpuModule;