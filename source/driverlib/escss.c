//###########################################################################
//
// FILE:   escss.c
//
// TITLE:  C29x ESC driver.
//
//###########################################################################
// $Copyright:
//###########################################################################

#include "escss.h"

//*****************************************************************************
//
// ESCSS_setRawInterruptStatus
//
//*****************************************************************************
uint16_t
ESCSS_setRawInterruptStatus(uint32_t base, uint16_t interruptMask,
                            uint16_t writeKey)
{
    uint16_t keyMatchStatus;

    //
    // Check if the passed parameter base is valid.
    //
    ASSERT(ESCSS_isBaseValid(base));
    ASSERT((interruptMask & ~(ECAT_SS_ESCSS_SET_INTERRUPT_MASK)) == 0U);

    if(ESCSS_VALID_KEY_VALUE == writeKey)
    {
        //
        // Set the individual Interrupt cause to emulate the interrupt.
        //
        HWREGH(base + ECAT_SS_O_ESCSS_INTR_SET) |= (interruptMask |
         ((uint16_t)((uint32_t)writeKey << ECAT_SS_ESCSS_INTR_SET_WRITE_KEY_S)
          & ECAT_SS_ESCSS_INTR_SET_WRITE_KEY_M));

        //
        // Set the return value when correct key is passed.
        //
        keyMatchStatus = ESCSS_API_SUCCESS ;
    }
    else
    {
        //
        // Set the return value when bad key is passed.
        //
        keyMatchStatus = ESCSS_API_FAIL;
    }

    return(keyMatchStatus);
}

//*****************************************************************************
//
// ESCSS_setGPINGroupCaptureTriggerSelect
//
//*****************************************************************************
void
ESCSS_setGPINGroupCaptureTriggerSelect(uint32_t base,
                                       ESCSS_GroupCaptureSelect selectGPIN,
                                       ESCSS_CaptureTrigger triggerCapSelect)
{
    //
    // Check if the passed parameter base is valid.
    //
    ASSERT(ESCSS_isBaseValid(base));
    ASSERT((triggerCapSelect == ESCSS_SOF_CAPTURE_TRIGGER) ||
           (triggerCapSelect == ESCSS_SYNC0_CAPTURE_TRIGGER) ||
           (triggerCapSelect == ESCSS_SYNC1_CAPTURE_TRIGGER) ||
           (triggerCapSelect == ESCSS_LATCH0_CAPTURE_TRIGGER) ||
           (triggerCapSelect == ESCSS_LATCH1_CAPTURE_TRIGGER));
    ASSERT((selectGPIN == ESCSS_GROUP_CAPTURE_SELECT0) ||
           (selectGPIN == ESCSS_GROUP_CAPTURE_SELECT1) ||
           (selectGPIN == ESCSS_GROUP_CAPTURE_SELECT2) ||
           (selectGPIN == ESCSS_GROUP_CAPTURE_SELECT3));

    if(selectGPIN == ESCSS_GROUP_CAPTURE_SELECT0)
    {
        HWREG(base + ECAT_SS_O_ESCSS_GPIN_GRP_CAP_SEL) |=
        (((uint16_t)((uint32_t)triggerCapSelect) << ((uint32_t)selectGPIN)) &
         ECAT_SS_ESCSS_GRP_CAP_SELECT0_MASK);
    }
    else if(selectGPIN == ESCSS_GROUP_CAPTURE_SELECT1)
    {
        HWREG(base + ECAT_SS_O_ESCSS_GPIN_GRP_CAP_SEL) |=
        (((uint16_t)((uint32_t)triggerCapSelect) << ((uint32_t)selectGPIN)) &
         ECAT_SS_ESCSS_GRP_CAP_SELECT1_MASK);
    }
    else if(selectGPIN == ESCSS_GROUP_CAPTURE_SELECT2)
    {
        HWREG(base + ECAT_SS_O_ESCSS_GPIN_GRP_CAP_SEL) |=
        (((uint16_t)((uint32_t)triggerCapSelect) << ((uint32_t)selectGPIN)) &
         ECAT_SS_ESCSS_GRP_CAP_SELECT2_MASK);
    }
    else if(selectGPIN == ESCSS_GROUP_CAPTURE_SELECT3)
    {
        HWREG(base + ECAT_SS_O_ESCSS_GPIN_GRP_CAP_SEL) |=
        (((uint16_t)((uint32_t)triggerCapSelect) << ((uint32_t)selectGPIN)) &
         ECAT_SS_ESCSS_GRP_CAP_SELECT3_MASK);
    }
    else
    {
        //
        // Not a valid value.
        //
    }
}

//*****************************************************************************
//
// ESCSS_setGPOUTGroupCaptureTriggerSelect
//
//*****************************************************************************
void
ESCSS_setGPOUTGroupCaptureTriggerSelect(uint32_t base,
                                        ESCSS_GroupCaptureSelect selectGPOUT,
                                        ESCSS_CaptureTrigger triggerCapSelect)
{
    //
    // Check if the passed parameter base is valid.
    //
    ASSERT(ESCSS_isBaseValid(base));
    ASSERT((triggerCapSelect == ESCSS_SOF_CAPTURE_TRIGGER) ||
           (triggerCapSelect == ESCSS_SYNC0_CAPTURE_TRIGGER) ||
           (triggerCapSelect == ESCSS_SYNC1_CAPTURE_TRIGGER) ||
           (triggerCapSelect == ESCSS_LATCH0_CAPTURE_TRIGGER) ||
           (triggerCapSelect == ESCSS_LATCH1_CAPTURE_TRIGGER));
    ASSERT((selectGPOUT == ESCSS_GROUP_CAPTURE_SELECT0) ||
           (selectGPOUT == ESCSS_GROUP_CAPTURE_SELECT1) ||
           (selectGPOUT == ESCSS_GROUP_CAPTURE_SELECT2) ||
           (selectGPOUT == ESCSS_GROUP_CAPTURE_SELECT3));

    if(selectGPOUT == ESCSS_GROUP_CAPTURE_SELECT0)
    {
        HWREG(base + ECAT_SS_O_ESCSS_GPOUT_GRP_CAP_SEL) |=
        (((uint16_t)((uint32_t)triggerCapSelect) << ((uint32_t)selectGPOUT)) &
         ECAT_SS_ESCSS_GRP_CAP_SELECT0_MASK);
    }
    else if(selectGPOUT == ESCSS_GROUP_CAPTURE_SELECT1)
    {
        HWREG(base + ECAT_SS_O_ESCSS_GPOUT_GRP_CAP_SEL) |=
        (((uint16_t)((uint32_t)triggerCapSelect) << ((uint32_t)selectGPOUT)) &
         ECAT_SS_ESCSS_GRP_CAP_SELECT1_MASK);
    }
    else if(selectGPOUT == ESCSS_GROUP_CAPTURE_SELECT2)
    {
        HWREG(base + ECAT_SS_O_ESCSS_GPOUT_GRP_CAP_SEL) |=
        (((uint16_t)((uint32_t)triggerCapSelect) << ((uint32_t)selectGPOUT)) &
         ECAT_SS_ESCSS_GRP_CAP_SELECT2_MASK);
    }
    else if(selectGPOUT == ESCSS_GROUP_CAPTURE_SELECT3)
    {
        HWREG(base + ECAT_SS_O_ESCSS_GPOUT_GRP_CAP_SEL) |=
        (((uint16_t)((uint32_t)triggerCapSelect) << ((uint32_t)selectGPOUT)) &
         ECAT_SS_ESCSS_GRP_CAP_SELECT3_MASK);
    }
    else
    {
        //
        // Not a valid value.
        //
    }
}

//*****************************************************************************
//
// ESCSS_enableCPUReset
//
//*****************************************************************************
uint16_t
ESCSS_enableCPUReset(uint32_t base, uint16_t writeKey)
{
    uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Enable the bit and set the Key Value.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_RESET_DEST_CONFIG) |=
             (ECAT_SS_ESCSS_RESET_DEST_CONFIG_CPU_RESET_EN | ((uint16_t)((uint32_t)
             writeKey << ECAT_SS_ESCSS_RESET_DEST_CONFIG_WRITE_KEY_S) &
             ECAT_SS_ESCSS_RESET_DEST_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_disableCPUReset
//
//*****************************************************************************
uint16_t
ESCSS_disableCPUReset(uint32_t base, uint16_t writeKey)
{
    uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Reset the Value of the Bit and set the Key Value.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_RESET_DEST_CONFIG) =
            ((HWREGH(base + ECAT_SS_O_ESCSS_RESET_DEST_CONFIG) &
             (~(ECAT_SS_ESCSS_RESET_DEST_CONFIG_CPU_RESET_EN))) | ((uint16_t)
             ((uint32_t)writeKey << ECAT_SS_ESCSS_RESET_DEST_CONFIG_WRITE_KEY_S)
             & ECAT_SS_ESCSS_RESET_DEST_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_enableResetToNMI
//
//*****************************************************************************
uint16_t
ESCSS_enableResetToNMI(uint32_t base, uint16_t writeKey)
{
    uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Set the Reset out set the Write Key Value.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_RESET_DEST_CONFIG) |=
            (ECAT_SS_ESCSS_RESET_DEST_CONFIG_CPU_NMI_EN | ((uint16_t)((uint32_t)
             writeKey << ECAT_SS_ESCSS_RESET_DEST_CONFIG_WRITE_KEY_S) &
             ECAT_SS_ESCSS_RESET_DEST_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_disableResetToNMI
//
//*****************************************************************************
uint16_t
ESCSS_disableResetToNMI(uint32_t base, uint16_t writeKey)
{
    uint16_t apiStatus;
    //
    // Check if the passed parameter base is valid.
    //
    ASSERT(ESCSS_isBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Reset out does not drive the CPU NMI.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_RESET_DEST_CONFIG) =
            ((HWREGH(base + ECAT_SS_O_ESCSS_RESET_DEST_CONFIG) &
             (~(ECAT_SS_ESCSS_RESET_DEST_CONFIG_CPU_NMI_EN))) | ((uint16_t)((uint32_t)
             writeKey << ECAT_SS_ESCSS_RESET_DEST_CONFIG_WRITE_KEY_S)
             & ECAT_SS_ESCSS_RESET_DEST_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_enableResetToInterrupt
//
//*****************************************************************************
uint16_t
ESCSS_enableResetToInterrupt(uint32_t base, uint16_t writeKey)
{
    uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Reset out drives interrupt to the main CPU to the respective
            // EtherCATSS.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_RESET_DEST_CONFIG) |=
            (ECAT_SS_ESCSS_RESET_DEST_CONFIG_CPU_INT_EN | ((uint16_t)((uint32_t)
             writeKey << ECAT_SS_ESCSS_RESET_DEST_CONFIG_WRITE_KEY_S) &
             ECAT_SS_ESCSS_RESET_DEST_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_disableResetToInterrupt
//
//*****************************************************************************
uint16_t
ESCSS_disableResetToInterrupt(uint32_t base, uint16_t writeKey)
{
    uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Disable the Reset out and set the Write Key Value.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_RESET_DEST_CONFIG) =
            ((HWREGH(base + ECAT_SS_O_ESCSS_RESET_DEST_CONFIG) &
             (~(ECAT_SS_ESCSS_RESET_DEST_CONFIG_CPU_INT_EN))) | ((uint16_t)((uint32_t)
             writeKey << ECAT_SS_ESCSS_RESET_DEST_CONFIG_WRITE_KEY_S)
             & ECAT_SS_ESCSS_RESET_DEST_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}


//*****************************************************************************
//
// ESCSS_configureSync0Connections
//
//*****************************************************************************
uint16_t
ESCSS_configureSync0Connections(uint32_t base, uint16_t connectionInterrupt,
                                 uint16_t writeKey)
{
    uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isBaseValid(base));
    ASSERT((connectionInterrupt & ~(ECAT_SS_ESCSS_SYNC0_CONFIG_CPUX_INT_EN |
                                    ECAT_SS_ESCSS_SYNC0_CONFIG_DMAX_TRIG_EN)) == 0U);


    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Configure the connection from SYNC0 to passed interrupt type.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_SYNC0_CONFIG) |=
             (connectionInterrupt | ((uint16_t)((uint32_t)writeKey <<
              ECAT_SS_ESCSS_SYNC0_CONFIG_WRITE_KEY_S) &
              ECAT_SS_ESCSS_SYNC0_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_configureSync1Connections
//
//*****************************************************************************
uint16_t
ESCSS_configureSync1Connections(uint32_t base, uint16_t connectionInterrupt,
                                 uint16_t writeKey)
{
     uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isBaseValid(base));
    ASSERT((connectionInterrupt & ~(ECAT_SS_ESCSS_SYNC1_CONFIG_CPUX_INT_EN |
                                    ECAT_SS_ESCSS_SYNC1_CONFIG_DMAX_TRIG_EN)) == 0U);

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Configure the connection from SYNC1 to passed interrupt type and
            // set the Write Key Value.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_SYNC1_CONFIG) |=
            (connectionInterrupt | ((uint16_t)((uint32_t)writeKey <<
             ECAT_SS_ESCSS_SYNC1_CONFIG_WRITE_KEY_S) &
             ECAT_SS_ESCSS_SYNC1_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_enableConfigurationLock
//
//*****************************************************************************
uint16_t
ESCSS_enableConfigurationLock(uint32_t base, uint16_t writeKey)
{
    uint16_t keyMatchStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    if(ESCSS_VALID_KEY_VALUE == writeKey)
    {
        //
        // Set the lock bit and Write Key.
        //
        HWREGH(base + ECAT_SS_O_ESCSS_CONFIG_LOCK) |=
        (ECAT_SS_ESCSS_CONFIG_LOCK_LOCK_ENABLE | ((uint16_t)((uint32_t)writeKey <<
         ECAT_SS_ESCSS_CONFIG_LOCK_WRITE_KEY_S) & ECAT_SS_ESCSS_CONFIG_LOCK_WRITE_KEY_M));

        //
        // Set the return value when correct key is passed.
        //
        keyMatchStatus = ESCSS_API_SUCCESS ;
    }
    else
    {
        //
        // Set the return value when bad key is passed.
        //
        keyMatchStatus = ESCSS_API_FAIL;
    }

    return(keyMatchStatus);
}

//*****************************************************************************
//
// ESCSS_enableIOConnectionLock
//
//*****************************************************************************
uint16_t
ESCSS_enableIOConnectionLock(uint32_t base, uint16_t writeKey)
{
    uint16_t keyMatchStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    if(ESCSS_VALID_KEY_VALUE == writeKey)
    {
        //
        // Set the lock bit and Write Key.
        //
        HWREGH(base + ECAT_SS_O_ESCSS_CONFIG_LOCK) |=
        (ECAT_SS_ESCSS_CONFIG_LOCK_IO_CONFIG_ENABLE | ((uint16_t)((uint32_t)writeKey
         << ECAT_SS_ESCSS_CONFIG_LOCK_WRITE_KEY_S) & ECAT_SS_ESCSS_CONFIG_LOCK_WRITE_KEY_M));

        //
        // Set the return value when correct key is passed.
        //
        keyMatchStatus = ESCSS_API_SUCCESS ;
    }
    else
    {
        //
        // Set the return value when bad key is passed.
        //
        keyMatchStatus = ESCSS_API_FAIL;
    }

    return(keyMatchStatus);
}

//*****************************************************************************
//
// ESCSS_disableIOConnectionLock
//
//*****************************************************************************
uint16_t
ESCSS_disableIOConnectionLock(uint32_t base, uint16_t writeKey)
{
    uint16_t keyMatchStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    if(ESCSS_VALID_KEY_VALUE == writeKey)
    {
        //
        // Disable the lock bit and set the write Key Value.
        //
        HWREGH(base + ECAT_SS_O_ESCSS_CONFIG_LOCK) =
        ((HWREGH(base + ECAT_SS_O_ESCSS_CONFIG_LOCK) &
          (~(ECAT_SS_ESCSS_CONFIG_LOCK_IO_CONFIG_ENABLE))) |
         ((uint16_t)((uint32_t)writeKey << ECAT_SS_ESCSS_CONFIG_LOCK_WRITE_KEY_S) &
          ECAT_SS_ESCSS_CONFIG_LOCK_WRITE_KEY_M));

        //
        // Set the return value when correct key is passed.
        //
        keyMatchStatus = ESCSS_API_SUCCESS ;
    }
    else
    {
        //
        // Set the return value when bad key is passed.
        //
        keyMatchStatus = ESCSS_API_FAIL;
    }

    return(keyMatchStatus);
}

//*****************************************************************************
//
// ESCSS_enableResetInputFromGpioPad
//
//*****************************************************************************
uint16_t
ESCSS_enableResetInputFromGpioPad(uint32_t base, uint16_t writeKey)
{
     uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Set the bit to enable ResetIN from GPIO and the write Key Value.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_MISC_IO_CONFIG) |=
            (ECAT_SS_ESCSS_MISC_IO_CONFIG_RESETIN_GPIO_EN | ((uint16_t)((uint32_t)
             writeKey << ECAT_SS_ESCSS_MISC_IO_CONFIG_WRITE_KEY_S) &
             ECAT_SS_ESCSS_MISC_IO_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_disableResetInputFromGpioPad
//
//*****************************************************************************
uint16_t
ESCSS_disableResetInputFromGpioPad(uint32_t base, uint16_t writeKey)
{
    uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Disable ResetIN from GPIO.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_MISC_IO_CONFIG) =
            ((HWREGH(base + ECAT_SS_O_ESCSS_MISC_IO_CONFIG) &
            (~(ECAT_SS_ESCSS_MISC_IO_CONFIG_RESETIN_GPIO_EN))) |
            ((uint16_t)((uint32_t)writeKey << ECAT_SS_ESCSS_MISC_IO_CONFIG_WRITE_KEY_S)
            & ECAT_SS_ESCSS_MISC_IO_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_enableESCEEPROMI2CIoPadConnection
//
//*****************************************************************************
uint16_t
ESCSS_enableESCEEPROMI2CIoPadConnection(uint32_t base, uint16_t writeKey)
{
     uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Set the EEPROM I2C IOPAD connection.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_MISC_IO_CONFIG) |=
            (ECAT_SS_ESCSS_MISC_IO_CONFIG_EEPROM_I2C_IO_EN | ((uint16_t)((uint32_t)
             writeKey << ECAT_SS_ESCSS_MISC_IO_CONFIG_WRITE_KEY_S) &
             ECAT_SS_ESCSS_MISC_IO_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_disableESCEEPROMI2CIoPadConnection
//
//*****************************************************************************
uint16_t
ESCSS_disableESCEEPROMI2CIoPadConnection(uint32_t base, uint16_t writeKey)
{
     uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Disable the EEPROM I2C IOPAD connection.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_MISC_IO_CONFIG) =
            ((HWREGH(base + ECAT_SS_O_ESCSS_MISC_IO_CONFIG) &
             (~(ECAT_SS_ESCSS_MISC_IO_CONFIG_EEPROM_I2C_IO_EN))) | ((uint16_t)
             ((uint32_t)writeKey << ECAT_SS_ESCSS_MISC_IO_CONFIG_WRITE_KEY_S)
             & ECAT_SS_ESCSS_MISC_IO_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_configurePortCount
//
//*****************************************************************************
uint16_t
ESCSS_configurePortCount(uint32_t base, ESCSS_PortSelection portConfig,
                          uint16_t writeKey)
{
    uint16_t keyMatchStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));
    ASSERT((portConfig == ESCSS_ONE_PORT_SELECTION) ||
           (portConfig == ESCSS_TWO_PORT_SELECTION));

    if(ESCSS_VALID_KEY_VALUE == writeKey)
    {
        //
        // Set the Number of PHY Ports.
        //
        HWREGH(base + ECAT_SS_O_ESCSS_PHY_IO_CONFIG) |=
        (((uint16_t)((uint32_t)portConfig <<
         ECAT_SS_ESCSS_PHY_IO_CONFIG_PHY_PORT_CNT_S)
         & ECAT_SS_ESCSS_PHY_IO_CONFIG_PHY_PORT_CNT_M) |
        ((uint16_t)((uint32_t)writeKey << ECAT_SS_ESCSS_PHY_IO_CONFIG_WRITE_KEY_S) &
        ECAT_SS_ESCSS_PHY_IO_CONFIG_WRITE_KEY_M));

        //
        // Set the return value when correct key is passed.
        //
        keyMatchStatus = ESCSS_API_SUCCESS ;
    }
    else
    {
        //
        // Set the return value when bad key is passed.
        //
        keyMatchStatus = ESCSS_API_FAIL;
    }

    return(keyMatchStatus);
}

//*****************************************************************************
//
// ESCSS_enableAutoCompensationTxClkIOPad
//
//*****************************************************************************
uint16_t
ESCSS_enableAutoCompensationTxClkIOPad(uint32_t base, uint16_t writeKey)
{
    uint16_t keyMatchStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    if(ESCSS_VALID_KEY_VALUE == writeKey)
    {
        //
        // Set the Auto Compensation based on sampling of TX_CLK.
        //
        HWREGH(base + ECAT_SS_O_ESCSS_PHY_IO_CONFIG) |=
        (ECAT_SS_ESCSS_PHY_IO_CONFIG_TX_CLK_AUTO_COMP | ((uint16_t)((uint32_t)writeKey
         << ECAT_SS_ESCSS_PHY_IO_CONFIG_WRITE_KEY_S) &
         ECAT_SS_ESCSS_PHY_IO_CONFIG_WRITE_KEY_M));

        //
        // Set the return value when correct key is passed.
        //
        keyMatchStatus = ESCSS_API_SUCCESS ;
    }
    else
    {
        //
        // Set the return value when bad key is passed.
        //
        keyMatchStatus = ESCSS_API_FAIL;
    }

    return(keyMatchStatus);
}

//*****************************************************************************
//
// ESCSS_disableAutoCompensationTxClkIOPad
//
//*****************************************************************************
uint16_t
ESCSS_disableAutoCompensationTxClkIOPad(uint32_t base, uint16_t writeKey)
{
    uint16_t keyMatchStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    if(ESCSS_VALID_KEY_VALUE == writeKey)
    {
        //
        // Set Manual Compensation to be there using CLK_IN.
        //
        HWREGH(base + ECAT_SS_O_ESCSS_PHY_IO_CONFIG) =
        ((HWREGH(base + ECAT_SS_O_ESCSS_PHY_IO_CONFIG) &
          (~(ECAT_SS_ESCSS_PHY_IO_CONFIG_TX_CLK_AUTO_COMP))) |
         ((uint16_t)((uint32_t)writeKey << ECAT_SS_ESCSS_PHY_IO_CONFIG_WRITE_KEY_S)
          & ECAT_SS_ESCSS_PHY_IO_CONFIG_WRITE_KEY_M));

        //
        // Set the return value when correct key is passed.
        //
        keyMatchStatus = ESCSS_API_SUCCESS ;
    }
    else
    {
        //
        // Set the return value when bad key is passed.
        //
        keyMatchStatus = ESCSS_API_FAIL;
    }

    return(keyMatchStatus);
}

//*****************************************************************************
//
// ESCSS_enableSync0GpioMuxConnection
//
//*****************************************************************************
uint16_t
ESCSS_enableSync0GpioMuxConnection(uint32_t base, uint16_t writeKey)
{
    uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Set the SYNC0 connection to OUT pad.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_SYNC_IO_CONFIG) |=
             (ECAT_SS_ESCSS_SYNC_IO_CONFIG_SYNC0_GPIO_EN | ((uint16_t)((uint32_t)
             writeKey << ECAT_SS_ESCSS_SYNC_IO_CONFIG_WRITE_KEY_S) &
             ECAT_SS_ESCSS_SYNC_IO_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_disableSync0GpioMuxConnection
//
//*****************************************************************************
uint16_t
ESCSS_disableSync0GpioMuxConnection(uint32_t base, uint16_t writeKey)
{
    uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Disable the SYNC0 connection to OUT pad.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_SYNC_IO_CONFIG) =
            ((HWREGH(base + ECAT_SS_O_ESCSS_SYNC_IO_CONFIG) &
             (~(ECAT_SS_ESCSS_SYNC_IO_CONFIG_SYNC0_GPIO_EN))) |
             ((uint16_t)((uint32_t)writeKey <<
              ECAT_SS_ESCSS_SYNC_IO_CONFIG_WRITE_KEY_S)
             & ECAT_SS_ESCSS_SYNC_IO_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_enableSync1GpioMuxConnection
//
//*****************************************************************************
uint16_t
ESCSS_enableSync1GpioMuxConnection(uint32_t base, uint16_t writeKey)
{
    uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Set the SYNC1 connection to OUT pad.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_SYNC_IO_CONFIG) |=
            (ECAT_SS_ESCSS_SYNC_IO_CONFIG_SYNC1_GPIO_EN | ((uint16_t)((uint32_t)
             writeKey << ECAT_SS_ESCSS_SYNC_IO_CONFIG_WRITE_KEY_S) &
             ECAT_SS_ESCSS_SYNC_IO_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_disableSync1GpioMuxConnection
//
//*****************************************************************************
uint16_t
ESCSS_disableSync1GpioMuxConnection(uint32_t base, uint16_t writeKey)
{
    uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Disable the SYNC1 connection to OUT pad.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_SYNC_IO_CONFIG) =
            ((HWREGH(base + ECAT_SS_O_ESCSS_SYNC_IO_CONFIG) &
             ((~ECAT_SS_ESCSS_SYNC_IO_CONFIG_SYNC1_GPIO_EN))) | ((uint16_t)((uint32_t)
             writeKey << ECAT_SS_ESCSS_SYNC_IO_CONFIG_WRITE_KEY_S)
             & ECAT_SS_ESCSS_SYNC_IO_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_enableLatch0GpioMuxConnection
//
//*****************************************************************************
uint16_t
ESCSS_enableLatch0GpioMuxConnection(uint32_t base, uint16_t writeKey)
{
    uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Set the LATCH0 connection to IN pad.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_LATCH_IO_CONFIG) |=
            (ECAT_SS_ESCSS_LATCH_IO_CONFIG_LATCH0_GPIO_EN | ((uint16_t)((uint32_t)
             writeKey << ECAT_SS_ESCSS_LATCH_IO_CONFIG_WRITE_KEY_S) &
             ECAT_SS_ESCSS_LATCH_IO_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_disableLatch0GpioMuxConnection
//
//*****************************************************************************
uint16_t
ESCSS_disableLatch0GpioMuxConnection(uint32_t base, uint16_t writeKey)
{
    uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Reset the LATCH0 connection to IN pad.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_LATCH_IO_CONFIG) =
            ((HWREGH(base + ECAT_SS_O_ESCSS_LATCH_IO_CONFIG) &
             (~(ECAT_SS_ESCSS_LATCH_IO_CONFIG_LATCH0_GPIO_EN))) | ((uint16_t)
             ((uint32_t)writeKey << ECAT_SS_ESCSS_LATCH_IO_CONFIG_WRITE_KEY_S)
             & ECAT_SS_ESCSS_LATCH_IO_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_enableLatch1GpioMuxConnection
//
//*****************************************************************************
uint16_t
ESCSS_enableLatch1GpioMuxConnection(uint32_t base, uint16_t writeKey)
{
    uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Set the LATCH1 connection to IN pad.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_LATCH_IO_CONFIG) |=
            (ECAT_SS_ESCSS_LATCH_IO_CONFIG_LATCH1_GPIO_EN | ((uint16_t)((uint32_t)
             writeKey << ECAT_SS_ESCSS_LATCH_IO_CONFIG_WRITE_KEY_S) &
             ECAT_SS_ESCSS_LATCH_IO_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_disableLatch1GpioMuxConnection
//
//*****************************************************************************
uint16_t
ESCSS_disableLatch1GpioMuxConnection(uint32_t base, uint16_t writeKey)
{
    uint16_t apiStatus;

    //
    // Check the arguments.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    if((bool)true != ESCSS_isConfigurationLockEnabled(ESC_SS_CONFIG_BASE))
    {
        if(ESCSS_VALID_KEY_VALUE == writeKey)
        {
            //
            // Reset the LATCH1 connection to IN pad.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_LATCH_IO_CONFIG) =
            ((HWREGH(base + ECAT_SS_O_ESCSS_LATCH_IO_CONFIG) &
             (~(ECAT_SS_ESCSS_LATCH_IO_CONFIG_LATCH1_GPIO_EN))) | ((uint16_t)
             ((uint32_t)writeKey << ECAT_SS_ESCSS_LATCH_IO_CONFIG_WRITE_KEY_S) &
             ECAT_SS_ESCSS_LATCH_IO_CONFIG_WRITE_KEY_M));

            //
            // Set the return value when correct key is passed.
            //
            apiStatus = ESCSS_API_SUCCESS ;
        }
        else
        {
            //
            // Set the return value when bad key is passed.
            //
            apiStatus = ESCSS_API_FAIL;
        }
    }
    else
    {
        //
        // Return API Fail if Configuration Lock is Enabled.
        //
        apiStatus = ESCSS_API_FAIL;
    }

    return(apiStatus);
}

//*****************************************************************************
//
// ESCSS_configureEEPROMSize
//
//*****************************************************************************
void
ESCSS_configureEEPROMSize(uint32_t base, ESCSS_SizeSelect eepromSize)
{
    //
    // Check if the passed parameter base is valid.
    //
    ASSERT(ESCSS_isConfigBaseValid(base));

    //
    // Set the Value as per the selected size.
    //
    switch(eepromSize)
    {
        case ESCSS_LESS_THAN_16K:
            //
            // Set the value as zero.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_MISC_CONFIG) &=
            ~ECAT_SS_ESCSS_MISC_CONFIG_EEPROM_SIZE;
            break;

        case ESCSS_GREATER_THAN_16K:
            //
            // Set the value as one.
            //
            HWREGH(base + ECAT_SS_O_ESCSS_MISC_CONFIG) |=
            ECAT_SS_ESCSS_MISC_CONFIG_EEPROM_SIZE;
            break;
        default:
            //
            // Do nothing. Not a valid selection value.
            //
            break;
    }
}
