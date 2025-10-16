--entry_point="code_start"
--retain="app1EntryAddr"

/* Flash boot mode entry address - Do not change */
#define FLASH_ENTRY     0x10001000
/* Cpu1 application firmware entry address, must be at the start of SBL's CPU1_FLASH_APP memory */
#define APP1_ENTRY      0x10018000
/* Address for SBL's command jump table, must be set within CPU1_FLASH_SBL region */
#define CMDTABLE_ENTRY  0x10002000

/* Specify the system memory map */
MEMORY
{
    /* All other RAMs are reserved for the application firmware */
    SRAM_LDA1           : o=0x200F8000, l=0x04000
    SRAM_LDA0           : o=0x200FC000, l=0x04000
    SRAM_CDA10_11       : o=0x20148000, l=0x08000

    CERT                : o=0x10000000, l=0x001000
    CPU1_FLASH_SBL      : o=0x10001000, l=0x017000
    CPU1_FLASH_APP      : o=APP1_ENTRY, l=0x0E8000
    CPU3_FLASH_APP      : o=0x10400000, l=0x100000

    //CPU1_UPDATE_FLASH : o=0x10600000, l=0x100000
    //CPU3_UPDATE_FLASH : o=0x10700000, l=0x100000

    MAILBOX_R5F             : o=0x302C0800, l=0x000007FF
    MAILBOX_HSM             : o=0x302C1000, l=0x000007FF
}


/* Specify the sections allocation into memory */
SECTIONS
{
    codestart     : {} > FLASH_ENTRY,    palign(8)
    command_table : {} > CMDTABLE_ENTRY, palign(8)
    cert          : {} > CERT,           palign(8)

    .text         : {} > CPU1_FLASH_SBL,     palign(8)
    .binit        : {} > CPU1_FLASH_SBL,     palign(8)
    .cinit        : {} > CPU1_FLASH_SBL,     palign(8)
    .const        : {} > CPU1_FLASH_SBL,     palign(8)
    .rodata       : {} > CPU1_FLASH_SBL,     palign(8)
    .init_array   : {} > CPU1_FLASH_SBL,     palign(8)
    .ovly         : {} > CPU1_FLASH_SBL,     palign(8)
    .TI.ramfunc   : {} LOAD=CPU1_FLASH_SBL, RUN=SRAM_LDA0, table(BINIT), palign(8)

    /* hsmlib is for Secure flow only */
    hsmlib       : {"*security_drivers.lib"(.text)} LOAD=CPU1_FLASH_SBL, RUN=SRAM_LDA0, table(BINIT), palign(8) /* Map HSMClient and SIPC funcs to HSM accessible region (LDAx/FLASH) */
    
    /* LDA1 is used as a scratchpad for secure flow, or Fapi lib in nonsecure fota since Fapi must run in RAM */
    UNION: RUN = SRAM_LDA1
    {
        secure_scratchpad : { . = . + 0x4000; } /* Map HSM authenticate data to HSM accessible region */
        GROUP: 
        {
            cert_scratchpad : { . = . + 0x1000; }
    /* Flash API is mainly for Nonsecure flow, except for program bankmode. In secure flow, fapi is sharing the same scratchpad used in KP/CP, therefore the need to *manually* copy_in & run in LDA1 */
            fapi         : {"*F29H85x_NWFlashAPI*.lib"(.text)} LOAD=CPU1_FLASH_SBL, table(fapiCopyTable), palign(8)
        }
    }
    
    cpu1app      : {} > APP1_ENTRY,         FILL=0xFF, START(app1EntryAddr) /* filled copy section to be replaced by application image during post-build steps */
    cpu3app      : {} > CPU3_FLASH_APP,     palign(8)

    .stack        : {} > SRAM_LDA0 (HIGH)  /* stack in HSM accessible region */
    .data         : {} > SRAM_LDA0
    .bss          : {} > SRAM_LDA0
    .sysmem       : {} > SRAM_LDA0
    .cio          : {} > SRAM_LDA0

    .bss.sipc_hsm_queue_mem   (NOLOAD) : {} > MAILBOX_HSM
    .bss.sipc_secure_host_queue_mem   (NOLOAD) : {} > MAILBOX_R5F

    sbl_packet_scratchpad (NOLOAD)  : {} > SRAM_CDA10_11
}