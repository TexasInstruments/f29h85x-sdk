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

var rtdma2mpuModule = {
    peripheralName        : "RTDMA2_MPU",
    displayName           : "RTDMA2 MPU",
    totalMaxInstances     : 16,
    defaultInstanceName   : "my" + str + "RTDMA2MPU",
    config                : rtdma_mpu_shared.getRTDMAMPUConfig("RTDMA2"),
    sharedModuleInstances : sharedModuleInstances,
    templates: {
        boardc : "/driverlib/rtdma2_mpu/rtdma2_mpu.board.c.xdt",
        boardh : "/driverlib/rtdma2_mpu/rtdma2_mpu.board.h.xdt"
    },

    moduleStatic: {
        name        : "rtdma2mpuGlobal",
        displayName : "RTDMA2 MPU Global",
        config      : rtdma_mpu_shared.getRTDMAMPUGlobalConfig("RTDMA2"),
        validate    : rtdma_mpu_shared.onValidateStatic,
        shouldBeAllocatedAsResource: true,
        alwaysAllocateAsResource: true,
    },
    shouldBeAllocatedAsResource : true,
    alwaysAllocateAsResource    : true,
    validate        : rtdma_mpu_shared.onValidate,
    uiAdd           : uiAddOption
};


exports = rtdma2mpuModule;