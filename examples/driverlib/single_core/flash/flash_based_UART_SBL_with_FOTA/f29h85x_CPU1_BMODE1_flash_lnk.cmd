--entry_point="code_start"
--retain="CPU1_FOTA_ENTRY"
--retain="CPU3_FOTA_ENTRY"
--retain="CPU1_SECURE_FOTA_ENTRY"
--retain="CPU3_SECURE_FOTA_ENTRY"
--retain="HSM_SECURE_FOTA_ENTRY"
--retain="SECCFG_PROGRAM_ENTRY"

/* Specify the system memory map */

MEMORY
{
    SRAM_LDAx : o=0x200E0000, l=0x1C000
    SRAM_LDA0 : o=0x200FC000, l=0x04000
    SRAM_LPAx : o=0x20100000, l=0x10000
    SRAM_CPAx : o=0x20110000, l=0x10000
    SRAM_CDAx : o=0x20120000, l=0x30000

    CERT      : o=0x10000000, l=0x001000
    CPU1_FLASH_RP0 : o=0x10001000, l=0x01E000
    CPU1_FOTA  : o=0x1001F000, l=0x200
    CPU3_FOTA  : o=0x1001F200, l=0x200
    CPU1_SECURE_FOTA : o=0x1001F400, l=0x200
    CPU3_SECURE_FOTA : o=0x1001F600, l=0x200
    HSM_SECURE_FOTA : o=0x1001F800, l=0x200
    SECCFG_PROGRAM  : o=0x1001FA00, l=0x200
    CPU1_APP       : o=0x10020000, l=0x00F000
    CPU3_FLASH_RP0 : o=0x10400000, l=0x100000
    CPU1_UPDATE_FLASH : o=0x10600000, l=0x200000

    MAILBOX_R5F             : o=0x302C0800, l=0x000007FF
    MAILBOX_HSM             : o=0x302C1000, l=0x000007FF
}


/* Specify the sections allocation into memory */

SECTIONS
{
    codestart     : {} > 0x10001000,    palign(8)
    cert          : {} > CERT,          palign(8)

    .text         : {} > CPU1_FLASH_RP0,     palign(8)
    .binit        : {} > CPU1_FLASH_RP0,     palign(8)
    .cinit        : {} > CPU1_FLASH_RP0,     palign(8)
    .const        : {} > CPU1_FLASH_RP0,     palign(8)
    .rodata       : {} > CPU1_FLASH_RP0,     palign(8)
    .init_array   : {} > CPU1_FLASH_RP0,     palign(8)

    CPU1_FOTA_ENTRY : {} > CPU1_FOTA, palign(8)
    CPU3_FOTA_ENTRY : {} > CPU3_FOTA, palign(8)
    CPU1_SECURE_FOTA_ENTRY : {} > CPU1_SECURE_FOTA, palign(8)
    CPU3_SECURE_FOTA_ENTRY : {} > CPU3_SECURE_FOTA, palign(8)
    HSM_SECURE_FOTA_ENTRY : {} > HSM_SECURE_FOTA, palign(8)
    SECCFG_PROGRAM_ENTRY : {} > SECCFG_PROGRAM, palign(8)

    firmware      : {} > CPU1_APP,    palign(8)

    GROUP 
    {
        .TI.ramfunc
        { -l F29H85x_NWFlashAPI_v21.00.00.00.lib}
        { -l security_drivers.lib}
    } LOAD=CPU1_FLASH_RP0, RUN=SRAM_LPAx, table(BINIT), palign(8)
    
    

    .data         : {} > SRAM_LPAx
    .bss          : {} > SRAM_LPAx
    .stack        : {} > SRAM_LDA0
    .sysmem       : {} > SRAM_LPAx
    .cio          : {} > SRAM_LPAx

    .bss.sipc_hsm_queue_mem   (NOLOAD) : {} > MAILBOX_HSM
    .bss.sipc_secure_host_queue_mem   (NOLOAD) : {} > MAILBOX_R5F
}