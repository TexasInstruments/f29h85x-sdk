//#############################################################################
//
//   FILE:  HwiP_c29_pipe.h
//
//   TITLE: Driver porting layer (DPL): Hardware Interrupts
//
//#############################################################################
//  $ Copyright: $
//#############################################################################

#ifndef HWIP_C29_PIPE_H
#define HWIP_C29_PIPE_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//! \addtogroup KERNEL_DPL_HWI
//! @{
//
//*****************************************************************************

#include "kernel/dpl/HwiP.h"
#include "driverlib.h"


#define HWI_SECTION __attribute__((section(".text.hwi")))




//*****************************************************************************
//
//! Total number of interrupts available in the device. Defined in driverlib.
//
//*****************************************************************************
#define HwiP_MAX_INTERRUPTS     (INTERRUPT_NO_OF_CHANNELS)
#define HwiP_MAX_PRIORITY       (INTERRUPT_NO_OF_CHANNELS)

//*****************************************************************************
//
//! Values that are returned from HwiP_inISR()
//
//*****************************************************************************
typedef enum
{
    HWIP_IN_ISR_MAIN    = (uint8_t)0,
    HWIP_IN_ISR_INT     = (uint8_t)1,
    HWIP_IN_ISR_RTINT   = (uint8_t)2,
    HWIP_IN_ISR_NMI     = (uint8_t)3
} HWIP_IN_ISR_STATUS;


//*****************************************************************************
//
//! Structure used to control INT call-back servicing within
//! HwiP_int_handler().
//!
//! For C29, the element number of the isr and isrArgs arrays correspond
//! to a priority level. For example isr[12] corresponds to the call-back
//! function for the INT configured with priority level 12.
//! Therefore, each configured INT must have a unique priority level specified
//! by the application
//
//*****************************************************************************
typedef struct HwiP_Ctrl_s {
    HwiP_FxnCallback isr[HwiP_MAX_INTERRUPTS];
    void *isrArgs[HwiP_MAX_INTERRUPTS];
    uint32_t spuriousINTCount;
} HwiP_Ctrl;


extern HwiP_Ctrl gHwiCtrl;
extern HwiP_Config gHwiConfig;

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! The HwiP provided handler for INT interrupts.
//!
//! \return None.
//
//*****************************************************************************
void HwiP_int_handler(void);

//*****************************************************************************
//
// HwiP_setPri
//
//*****************************************************************************
static inline void  HWI_SECTION
HwiP_setPri(uint32_t intNum, uint32_t priority)
{
    Interrupt_setPriority(intNum, (uint8_t)priority);
}

//*****************************************************************************
//
// HwiP_setVecAddr
//
//*****************************************************************************
static inline void HWI_SECTION
HwiP_setVecAddr(uint32_t intNum, uintptr_t vecAddr)
{
    Interrupt_register(intNum, (void*)vecAddr);
}

//*****************************************************************************
//
//! C29 PIPE specific. Set the Threshold for RTINT
//!
//! \param threshold Threshold value (0-INTERRUPT_NO_OF_CHANNELS)
//!
//! \return None
//
//*****************************************************************************
static inline void HWI_SECTION
HwiP_setRTINTThreshold(uint8_t threshold)
{
    Interrupt_setThreshold(threshold);
}

//*****************************************************************************
//
//! C29 PIPE specific. Get the priority of the INT being serviced.
//!
//! If an INT is not being serviced, return SystemP_FAILURE. In this
//! case, intPriority is invalid.
//!
//! If an INT is being serviced, then SystemP_SUCCESS is returned and
//! intPriority is set to the priority of that INT.
//!
//! \sa HwiP_inISR()
//! \param intPriority is set to the priority of the INT being serviced
//! \return SystemP_SUCCESS or SystemP_FAILURE
//
//*****************************************************************************
int32_t HWI_SECTION HwiP_getIntPriority(uint8_t *intPriority);

#ifdef __cplusplus
}
#endif

#endif /* HWIP_C29_PIPE_H */

