//#############################################################################
//
// FILE:   fota_bankmode.h
//
// TITLE:  API definition to change the BANKMODE for FOTA
//
//#############################################################################

#ifndef FOTA_BANKMODE_
#define FOTA_BANKMODE_

//
//  Macro definitions
//
//
//  Bank status offset
//
#define BANKMMGMT_O_BANK_STATUS             (0x0U)
//
//  Bank update counter offset
//
#define BANKMMGMT_O_BANK_UPDATE_CTR         (0x8U)
//
//  Valid bank status
//
#define BANKMGMT_VALID_BANK_STATUS          (0x5555555555555555U)
//
//  Invalid bank status
//
#define BANKMGMT_INVALID_BANK_STATUS        (0xFFFFFFFFFFFFFFFFU)
//
//  Invalid update counter
//
#define BANKMGMT_INVALID_UPDATE_CTR         (0x0000000000000000U)
//
//  2KB sector in 4 bytes
//
#define SECTOR2KB_IN_4BYTES                 (0x200U)
//
//  Flash controller base address
//
#define FlashTech_CPU0_BASE_ADDRESS         ((Fapi_FmcRegistersType *)FLASHCONTROLLER1_BASE)
//
//  Bankmgmt sector address used for programming
//
#define BANKMGMT_PROG_ADDR                  (0x10D80000U)

//
//  Enum
//
//
//  Bankmode
//
typedef enum
{
    FOTA_BANKMODE_0     = 0U,
    FOTA_BANKMODE_1     = 1U,
    FOTA_BANKMODE_2     = 2U,
    FOTA_BANKMODE_3     = 3U,
    FOTA_BANKMODE_MAX   = 4U
} fota_bankMode;

//
//  Function declaration
//
//
//  Fota_SetBankMode
//
Fapi_StatusType Fota_SetBankMode(fota_bankMode fotaBankMode);

#endif /* FOTA_BANKMODE_ */
