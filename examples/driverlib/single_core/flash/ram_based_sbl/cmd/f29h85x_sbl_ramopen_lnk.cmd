--entry_point="code_start"

/* LPAx RAM boot entry address - Do not change */
#define RAM_ENTRY 0x20100000

/* Specify the system memory map */
MEMORY
{
    /* Address range 0x200E0000 - 0x200F4000 (LDA7 - LDA2) is reserved for Ram-based HSM Runtime */
    SRAM_LDA1 (RWX)         : o=0x200F8000, l=0x04000
    SRAM_LDA0 (RWX)         : o=0x200FC000, l=0x04000

    /* ROM Periperial boot supports a max SBL image size of 96KB (LPA0/1+CPA0 ram) and loads the image into address 0x20100000 (LPA0) */  
    /* Of which only LPAx is executable (r/w/x) (In RAMOPEN mode only LDAx & LPAx ram are r/w/x) */
    /* Therefore, code goes to LPAx (64KB) and initialized data to CPA0 (32KB) */             
    SRAM_LPAx (RWIX)        : o=0x20100000, l=0x10000
    SRAM_CPA0 (RWI)         : o=0x20110000, l=0x08000

    /* CPA1 & CDAx are all uninitialized */
    SRAM_CPA1 (RW)          : o=0x20118000, l=0x08000
    SRAM_CDAx (RW)          : o=0x20120000, l=0x30000

    FLASH_RP0               : o=0x10000000, l=0x100000
    FLASH_RP1               : o=0x10100000, l=0x100000
    FLASH_RP2               : o=0x10200000, l=0x100000
    FLASH_RP3               : o=0x10300000, l=0x100000
    MAILBOX_R5F             : o=0x302C0800, l=0x000007FF
    MAILBOX_HSM             : o=0x302C1000, l=0x000007FF
}

/* Specify the sections allocation into memory */
SECTIONS
{
    /* Initialized Section */
    codestart     : {} > RAM_ENTRY 
    .text         : {} > SRAM_LPAx
    .TI.ramfunc   : {} > SRAM_LPAx
    .binit        : {} > SRAM_CPA0
    .cinit        : {} > SRAM_CPA0
    .const        : {} > SRAM_CPA0
    .rodata       : {} > SRAM_CPA0
    .init_array   : {} > SRAM_CPA0
    .ovly         : {} > SRAM_CPA0
    .data         : {} > SRAM_CPA0

    /* LDA1 is reserved as a scratchpad to pass in rcvd img to HSMRT for authentication (KP & CP) or to store Fapi (DFU, or program bankmodes in KP/CP with mannual copy to re-populate the library) */   
    UNION: RUN = SRAM_LDA1
    {
        secure_scratchpad : { . = . + 0x4000; } /* Map HSM authenticate data to HSM accessible region */
        GROUP: 
        {
            cert_scratchpad : { . = . + 0x1000; }
    /* Due to limited LPAx space (initalized and executable RAM), store fapi in CPA0 (non-executable) and *manually* copy_in & run in LDA1 (scratchpad) when needed */
            fapi         : {"*F29H85x_NWFlashAPI*.lib"(.text)} LOAD=SRAM_CPA0, table(fapiCopyTable)
        }
    }

    hsmlib       : {"*security_drivers.lib"(.text)} RUN=SRAM_LDA0, LOAD=SRAM_CPA0, table(BINIT) /* Map HSMClient and SIPC funcs to HSM accessible region (LDAx) */

    /* Uninitialized Section */
    .bss      (NOLOAD)  : {} > SRAM_CPA1
    .stack    (NOLOAD)  : {} > SRAM_LDA0 (HIGH)    /* Stack in HSM accessible region */
    .sysmem   (NOLOAD)  : {} > SRAM_CPA1
    .cio      (NOLOAD)  : {} > SRAM_CPA1
    hsm_accessible (NOLOAD)  : {} > SRAM_LDA0     /* Section for mapping memory range accessible to HSM (uninitialized) */

    .bss.sipc_hsm_queue_mem   (NOLOAD) : {} > MAILBOX_HSM
    .bss.sipc_secure_host_queue_mem   (NOLOAD) : {} > MAILBOX_R5F

    sbl_packet_scratchpad  (NOLOAD) : {} >> SRAM_CPA1 | SRAM_CDAx 
}