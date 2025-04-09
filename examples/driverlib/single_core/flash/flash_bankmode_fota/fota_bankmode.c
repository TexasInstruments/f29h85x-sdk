//#############################################################################
//
// FILE:   fota_bankmode.c
//
// TITLE:  API definition to change the BANKMODE for FOTA
//
//#############################################################################
//
//  Includes
//
#include "board.h"
#include "FlashTech_F29H85x_C29x.h"
#include "fota_bankmode.h"

//
//  Global
//
//
//  User flash config
//
uint32_t g_UserFlashConfig;
//
//  BANKMGMT 1 address
//
uint32_t g_BankMgmtAddr1[FOTA_BANKMODE_MAX] =
{
    0x10D80000U,
    0x10D80000U,
    0x10D80000U,
    0x10D80000U
};
//
//  BANKMGMT 2 address
//
uint32_t g_BankMgmtAddr2[FOTA_BANKMODE_MAX] =
{
    0x10D84000U,
    0x10D98000U,
    0x10D84000U,
    0x10D98000U
};
//
//  BANKMGMT 2 address
//
uint8_t g_BankMode[FOTA_BANKMODE_MAX] =
{
    0x03U,
    0x06U,
    0x09U,
    0x0C
};
//
//  Bankmgmt sector
//
uint8_t g_BankmgmtSector[32U] =
{
    0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,     //  BANK_STATUS
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     //  BANK_UPDATE_CTR
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,     //  BANKMODE
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF      //  Reserved
};

//
//  Local function definitions
//
//
//  getWinBankMgmt
//
static uint32_t getWinBankMgmt(uint32_t bankMgmt1, uint32_t bankMgmt2)
{
    uint64_t bankStatus1    = BANKMGMT_INVALID_BANK_STATUS;
    uint64_t bankStatus2    = BANKMGMT_INVALID_BANK_STATUS;
    uint64_t bankUpdateCtr1 = BANKMGMT_INVALID_UPDATE_CTR;
    uint64_t bankUpdateCtr2 = BANKMGMT_INVALID_UPDATE_CTR;
    uint32_t winBankMgmt    = 0x0U;
    //
    //  Read bank status
    //
    bankStatus1 =
        (uint64_t)((uint64_t)HWREG(bankMgmt1 + BANKMMGMT_O_BANK_STATUS) | \
                        ((uint64_t)HWREG(bankMgmt1 + (BANKMMGMT_O_BANK_STATUS + 4U)) << 32U));
    bankStatus2 =
        (uint64_t)((uint64_t)HWREG(bankMgmt2 + BANKMMGMT_O_BANK_STATUS) | \
                        ((uint64_t)HWREG(bankMgmt2 + (BANKMMGMT_O_BANK_STATUS + 4U)) << 32U));
    //
    //  Read update counters
    //
    bankUpdateCtr1 = \
        (uint64_t)((uint64_t)HWREG(bankMgmt1 + BANKMMGMT_O_BANK_UPDATE_CTR) | \
                        ((uint64_t)HWREG(bankMgmt1 + (BANKMMGMT_O_BANK_UPDATE_CTR + 4U)) << 32U));
    bankUpdateCtr2 = \
        (uint64_t)((uint64_t)HWREG(bankMgmt2 + BANKMMGMT_O_BANK_UPDATE_CTR) | \
                        ((uint64_t)HWREG(bankMgmt2 + (BANKMMGMT_O_BANK_UPDATE_CTR + 4U)) << 32U));
    //
    //  Return the lowest update counter
    //
    if((BANKMGMT_VALID_BANK_STATUS == bankStatus1) && (BANKMGMT_VALID_BANK_STATUS == bankStatus2))
    {
        if(bankUpdateCtr1 <= bankUpdateCtr2)
        {
            winBankMgmt = bankMgmt1;
        }
        else if(bankUpdateCtr2 < bankUpdateCtr1)
        {
            winBankMgmt = bankMgmt2;
        }
    }
    else if(BANKMGMT_VALID_BANK_STATUS == bankStatus1)
    {
        winBankMgmt = bankMgmt1;
    }
    else if(BANKMGMT_VALID_BANK_STATUS == bankStatus2)
    {
        winBankMgmt = bankMgmt2;
    }
    else
    {
        winBankMgmt = 0x0U;
    }

    return winBankMgmt;
}
//
//  clearFsmStatus
//
static Fapi_StatusType clearFsmStatus(uint32_t startAddr, uint32_t userFlashConfig)
{
    Fapi_StatusType retVal  = Fapi_Status_Success;

    while(Fapi_checkFsmForReady(startAddr, userFlashConfig) != Fapi_Status_FsmReady)
    {
        ;
    }

    (void)Fapi_getFsmStatus(startAddr, userFlashConfig);

    retVal = Fapi_issueAsyncCommand(
                        startAddr,
                        userFlashConfig,
                        Fapi_ClearStatus);
    //
    // Wait until status is cleared
    //
    while (Fapi_getFsmStatus(startAddr, userFlashConfig) != 0)
    {
        ;
    }

    return retVal;
}
//
//  eraseBankmgmt
//
static Fapi_StatusType eraseBankmgmt(uint32_t bankMgmt)
{
    Fapi_StatusType             retVal  = Fapi_Status_Success;
    Fapi_FlashStatusType        flashRetVal;
    Fapi_FlashStatusWordType    flashStatusWord;
    uint32_t                    cnt     = 0U;

    for(cnt = 1U; cnt <= 2U; cnt++)
    {
        retVal = clearFsmStatus(bankMgmt, g_UserFlashConfig);
        if(Fapi_Status_Success == retVal)
        {
            Fapi_setupBankSectorEnable(
                            (uint32_t*)(bankMgmt),
                            g_UserFlashConfig,
                            FLASH_NOWRAPPER_O_CMDWEPROTNM,
                            0x00000000);
            retVal = Fapi_issueAsyncCommandWithAddress(
                            Fapi_EraseSector,
                            (uint32_t*)(bankMgmt),
                            cnt,
                            g_UserFlashConfig);
            //
            //  Wait until sector erase is completed
            //
            while(Fapi_checkFsmForReady(bankMgmt, g_UserFlashConfig) != Fapi_Status_FsmReady)
            {
                ;
            }

            if(Fapi_Status_Success == retVal)
            {
                flashRetVal = Fapi_getFsmStatus(bankMgmt, g_UserFlashConfig);
                if(0x3U != flashRetVal)
                {
                    retVal = Fapi_Error_Fail;
                    break;
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    return retVal;
}
//
//  programBankmgmt
//
static Fapi_StatusType programBankmgmt(uint32_t bankMgmt, uint8_t bankMode)
{
    Fapi_StatusType             retVal  = Fapi_Status_Success;
    uint32_t                    cnt     = 0U;
    Fapi_FlashStatusType        flashRetVal;
    Fapi_FlashStatusWordType    flashStatusWord;
    //
    //  Update the counter and bankmode
    //
    g_BankmgmtSector[16U] = bankMode;

    for(cnt = 16U;cnt <= 16U;cnt -= 16U)
    {
        retVal = clearFsmStatus((bankMgmt + cnt), g_UserFlashConfig);
        if(Fapi_Status_Success == retVal)
        {
            Fapi_setupBankSectorEnable(
                            (uint32_t*)(bankMgmt + cnt),
                            g_UserFlashConfig,
                            FLASH_NOWRAPPER_O_CMDWEPROTNM,
                            0x00000000);
            retVal = Fapi_issueProgrammingCommand(
                            (uint32_t*)(bankMgmt + cnt),
                            g_BankmgmtSector + cnt,
                            16U,
                            0U,
                            0U,
                            Fapi_AutoEccGeneration,
                            g_UserFlashConfig);
            //
            // Wait until the Flash program operation is over
            //
            while(Fapi_checkFsmForReady((bankMgmt + cnt), g_UserFlashConfig) == Fapi_Status_FsmBusy)
            {
                ;
            }

            if(Fapi_Status_Success == retVal)
            {
                flashRetVal = Fapi_getFsmStatus((bankMgmt + cnt), g_UserFlashConfig);
                if(3U != flashRetVal)
                {
                    retVal = Fapi_Error_Fail;
                    break;
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    return retVal;
}
//
//  eraseProgramBankMgmt
//
static Fapi_StatusType eraseProgramBankMgmt(uint32_t bankMgmt, uint8_t  bankMode)
{
    Fapi_StatusType retVal  = Fapi_Status_Success;
    Fapi_BankMode   curBankMode;
    //
    // Request semaphore for CPU1
    //
    HWREG(SSUGEN_BASE + SSU_O_FLSEMREQ) = SSU_FLSEMREQ_REQ;
    //
    //  Wait for MATCH status
    //
    while((HWREG( SSUGEN_BASE + SSU_O_FLSEMSTAT) & SSU_FLSEMSTAT_MATCH) != SSU_FLSEMSTAT_MATCH)
    {
        ;
    }

    g_UserFlashConfig   = Fapi_getUserConfiguration(C29Bank, FOTA_Image);
    curBankMode         = (Fapi_BankMode)(((HWREG(SSUGEN_BASE + SSU_O_BANKMODE)) & SSU_BANKMODE_MODE_M) >> SSU_BANKMODE_MODE_S);
    //
    //  Configure the PROG_BANKMODE
    //
    retVal = Fapi_SetFlashCPUConfiguration(curBankMode);
    if(Fapi_Status_Success == retVal)
    {
        retVal = Fapi_initializeAPI(FlashTech_CPU0_BASE_ADDRESS, (DEVICE_SYSCLK_FREQ/1000000U));
        if(Fapi_Status_Success == retVal)
        {
            retVal = eraseBankmgmt(bankMgmt);
            if(Fapi_Status_Success == retVal)
            {
                retVal = programBankmgmt(bankMgmt, bankMode);
            }
        }
    }
    //
    //  Release semaphore
    //
    HWREG(SSUGEN_BASE + SSU_O_FLSEMCLR) = SSU_FLSEMCLR_CLR;

    return retVal;
}
//
//  getBankModeIndex
//
fota_bankMode getBankModeIndex(uint8_t bankMode)
{
    fota_bankMode bankModeIdx = 0U;

    switch(bankMode)
    {
        case 0x03U:
            bankModeIdx = FOTA_BANKMODE_0;
            break;
        case 0x06U:
            bankModeIdx = FOTA_BANKMODE_1;
            break;
        case 0x09U:
            bankModeIdx = FOTA_BANKMODE_2;
            break;
        case 0x0CU:
            bankModeIdx = FOTA_BANKMODE_3;
            break;
    }

    return bankModeIdx;
}

//
//  Export function definitions
//
//
//  Fota_SetBankMode
//
Fapi_StatusType Fota_SetBankMode(fota_bankMode fotaBankMode)
{
    uint8_t         curBankMode     = 0x03U;
    fota_bankMode   curBankModeIdx  = FOTA_BANKMODE_0;
    Fapi_StatusType retVal          = Fapi_Status_Success;
    uint32_t        winningBankMgmt = 0x0U;
    //
    //  Supports only MODE1 and MODE3
    //
    if((FOTA_BANKMODE_1 == fotaBankMode) || (FOTA_BANKMODE_3 == fotaBankMode))
    {
        //
        //  Read current bankmode and if same as argument, then return
        //
        curBankMode = (uint8_t)(HWREG(SSUGEN_BASE + SSU_O_BANKMODE) & SSU_BANKMODE_MODE_M);
        //
        //  Get bankmode index
        //
        curBankModeIdx = getBankModeIndex(curBankMode);
        if(curBankModeIdx != fotaBankMode)
        {
            //
            //  The current and new bankmodes are different
            //
            //
            //  Get the Winning Bankmgmt sector
            //
            winningBankMgmt = getWinBankMgmt(g_BankMgmtAddr1[curBankModeIdx], g_BankMgmtAddr2[curBankModeIdx]);
            if(0x0U != winningBankMgmt)
            {
                //
                //  Erase and program bankmgmt sectors
                //
                retVal = eraseProgramBankMgmt(BANKMGMT_PROG_ADDR, g_BankMode[fotaBankMode]);

                if(((FOTA_BANKMODE_0 == curBankModeIdx) || (FOTA_BANKMODE_2 == curBankModeIdx)) &&
                   ((FOTA_BANKMODE_1 == fotaBankMode)   || (FOTA_BANKMODE_3 == fotaBankMode)))
                {
                    //
                    //  Bankmode 0 -> 1
                    //  Bankmode 0 -> 3
                    //  Bankmode 2 -> 1
                    //  Bankmode 2 -> 3
                    //
                    //  If the winning bankmgmt is first sector call again to make cpu1swap = 0
                    //
                    if(winningBankMgmt == g_BankMgmtAddr1[curBankModeIdx])
                    {
                        retVal = eraseProgramBankMgmt(BANKMGMT_PROG_ADDR, g_BankMode[fotaBankMode]);
                    }
                }
            }
            else
            {
                retVal = Fapi_Error_Fail;
            }
        }
    }
    else
    {
        retVal = Fapi_Error_Fail;
    }

    return retVal;
}

