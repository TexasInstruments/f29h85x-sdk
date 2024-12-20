--entry_point="code_start"


/* Specify the system memory map */

MEMORY
{
    SRAM_LDAx : o=0x200FC000, l=0x3FFF
    APPL_ENTRY : o=0x20100000, l=0x000040
    SRAM_LPAx : o=0x20100040, l=0x01FFC0
    SRAM_CDAx : o=0x20120000, l=0x30000

    FLASH_RP0 : o=0x10000000, l=0x100000
    FLASH_RP1 : o=0x10100000, l=0x100000
    FLASH_RP2 : o=0x10200000, l=0x100000
    FLASH_RP3 : o=0x10300000, l=0x100000
    MAILBOX_R5F : o=0x302C0800, l=0x000007FF
    MAILBOX_HSM : o=0x302C1000, l=0x000007FF
}



/* Specify the sections allocation into memory */

SECTIONS
{
    codestart     : {} > APPL_ENTRY

    .text         : {} > SRAM_LPAx
    .TI.ramfunc   : {} > SRAM_LPAx
    .cinit        : {} > SRAM_LPAx
    .const        : {} > SRAM_LPAx
    .rodata       : {} > SRAM_LPAx
    .init_array   : {} > SRAM_LPAx

    .data         : {} > SRAM_LPAx
    .bss          : {} > SRAM_LPAx
    .stack        : {} > SRAM_LPAx
    .sysmem       : {} > SRAM_LPAx
    .cio          : {} > SRAM_LPAx

    .bss.sipc_hsm_queue_mem   (NOLOAD) : {} > MAILBOX_HSM
    .bss.sipc_secure_host_queue_mem   (NOLOAD) : {} > MAILBOX_R5F

}
