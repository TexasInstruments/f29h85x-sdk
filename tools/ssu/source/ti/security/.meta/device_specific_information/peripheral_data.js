const peripheralList = [
    { name:'CPU_SYS_REGS',         start : 0x30200000, end : 0x30201000},
    { name:'PER_CFG_REGS_WD_REGS', start : 0x30208000, end : 0x30209000},
    { name:'CPUTIMER0_REGS',       start : 0x30218000, end : 0x30219000},
    { name:'CPUTIMER1_REGS',       start : 0x30219000, end : 0x3021A000},
    { name:'CPUTIMER2_REGS',       start : 0x3021A000, end : 0x3021B000},

    { name:'IPC_CPU1_SEND_REGS_CPU2_CH0_CH1', start : 0x30220000, end : 0x30221000},
    { name:'IPC_CPU1_SEND_REGS_CPU2_CH2_CH3', start : 0x30221000, end : 0x30222000},
    { name:'IPC_CPU1_SEND_REGS_CPU3_CH0_CH1', start : 0x30222000, end : 0x30223000},
    { name:'IPC_CPU1_SEND_REGS_CPU3_CH2_CH3', start : 0x30223000, end : 0x30224000},
    { name:'IPC_CPU1_SEND_REGS_HSM_CH0',      start : 0x30226000, end : 0x30227000},
    { name:'IPC_CPU1_SEND_REGS_HSM_CH1',      start : 0x30227000, end : 0x30228000},

    { name:'IPC_CPU2_SEND_REGS_CPU1_CH0_CH1', start : 0x30228000, end : 0x30229000},
    { name:'IPC_CPU2_SEND_REGS_CPU1_CH2_CH3', start : 0x30229000, end : 0x3022A000},
    { name:'IPC_CPU2_SEND_REGS_CPU3_CH0_CH1', start : 0x3022A000, end : 0x3022B000},
    { name:'IPC_CPU2_SEND_REGS_CPU3_CH2_CH3', start : 0x3022B000, end : 0x3022C000},
    { name:'IPC_CPU2_SEND_REGS_HSM_CH0',      start : 0x3022E000, end : 0x3022F000},
    { name:'IPC_CPU2_SEND_REGS_HSM_CH1',      start : 0x3022F000, end : 0x30230000},

    { name:'IPC_CPU3_SEND_REGS_CPU1_CH0_CH1', start : 0x30230000, end : 0x30231000},
    { name:'IPC_CPU3_SEND_REGS_CPU1_CH2_CH3', start : 0x30231000, end : 0x30232000},
    { name:'IPC_CPU3_SEND_REGS_CPU2_CH0_CH1', start : 0x30232000, end : 0x30233000},
    { name:'IPC_CPU3_SEND_REGS_CPU2_CH2_CH3', start : 0x30233000, end : 0x30234000},
    { name:'IPC_CPU3_SEND_REGS_HSM_CH0',      start : 0x30236000, end : 0x30237000},
    { name:'IPC_CPU3_SEND_REGS_HSM_CH1',      start : 0x30237000, end : 0x30238000},

    { name:'IPC_CPU1_RECV_REGS_CPU2_CH0_CH1', start : 0x30240000, end : 0x30241000},
    { name:'IPC_CPU1_RECV_REGS_CPU2_CH2_CH3', start : 0x30241000, end : 0x30242000},
    { name:'IPC_CPU1_RECV_REGS_CPU3_CH0_CH1', start : 0x30242000, end : 0x30243000},
    { name:'IPC_CPU1_RECV_REGS_CPU3_CH2_CH3', start : 0x30243000, end : 0x30244000},
    { name:'IPC_CPU1_RECV_REGS_HSM_CH0',      start : 0x30246000, end : 0x30247000},
    { name:'IPC_CPU1_RECV_REGS_HSM_CH1',      start : 0x30247000, end : 0x30248000},

    { name:'IPC_CPU2_RECV_REGS_CPU1_CH0_CH1', start : 0x30248000, end : 0x30249000},
    { name:'IPC_CPU2_RECV_REGS_CPU1_CH2_CH3', start : 0x30249000, end : 0x3024A000},
    { name:'IPC_CPU2_RECV_REGS_CPU3_CH0_CH1', start : 0x3024A000, end : 0x3024B000},
    { name:'IPC_CPU2_RECV_REGS_CPU3_CH2_CH3', start : 0x3024B000, end : 0x3024C000},
    { name:'IPC_CPU2_RECV_REGS_HSM_CH0',      start : 0x3024E000, end : 0x3024F000},
    { name:'IPC_CPU2_RECV_REGS_HSM_CH1',      start : 0x3024F000, end : 0x30250000},

    { name:'IPC_CPU3_RECV_REGS_CPU1_CH0_CH1', start : 0x30250000, end : 0x30251000},
    { name:'IPC_CPU3_RECV_REGS_CPU1_CH2_CH3', start : 0x30251000, end : 0x30252000},
    { name:'IPC_CPU3_RECV_REGS_CPU2_CH0_CH1', start : 0x30252000, end : 0x30253000},
    { name:'IPC_CPU3_RECV_REGS_CPU2_CH2_CH3', start : 0x30253000, end : 0x30254000},
    { name:'IPC_CPU3_RECV_REGS_HSM_CH0',      start : 0x30256000, end : 0x30257000},
    { name:'IPC_CPU3_RECV_REGS_HSM_CH1',      start : 0x30257000, end : 0x30258000},

    { name:'GPIO_DATA_REGS',       start : 0x30268000, end : 0x30269000},
    { name:'GPIO_DATA_READ_REGS',  start : 0x30269000, end : 0x3026A000},
    { name:'XINT_REGS',            start : 0x30270000, end : 0x30271000},

    { name:'DTHE_REGS',            start : 0x30280000, end : 0x30281000},
    { name:'CRC_S_REGS',           start : 0x30281000, end : 0x30282000},
    { name:'CRC_P_REGS',           start : 0x30282000, end : 0x30283000},
    { name:'SHA_S_REGS',           start : 0x30284000, end : 0x30285000},
    { name:'SHA_P_REGS',           start : 0x30285000, end : 0x30286000},
    { name:'AES_S_REGS',           start : 0x30286000, end : 0x30287000},
    { name:'AES_P_REGS',           start : 0x30287000, end : 0x30288000},
    { name:'SM4_REGS',             start : 0x30288000, end : 0x30289000},
    { name:'SM3_REGS',             start : 0x30289000, end : 0x3028A000},
    { name:'TRNG_REGS',            start : 0x3028A000, end : 0x3028B000},
    { name:'PKA_REGS',             start : 0x30290000, end : 0x30294000},
    { name:'HSM_MAILBOX',          start : 0x302C0000, end : 0x302C2000},

    { name:'ECAT_REGS',            start : 0x30380000, end : 0x30381000}, // TODO: Are these needed?
    { name:'ECAT_RAM',             start : 0x30381000, end : 0x30385000}, // TODO: Are these needed?
    { name:'ESC_REGS',             start : 0x30388000, end : 0x30389000},
    { name:'ECAT_RAM_DIRECT',      start : 0x303A1000, end : 0x303A5000},

    { name:'ADCA_RESULT_REGS',     start : 0x303C0000, end : 0x303C1000},
    { name:'ADCB_RESULT_REGS',     start : 0x303C1000, end : 0x303C2000},
    { name:'ADCC_RESULT_REGS',     start : 0x303C2000, end : 0x303C3000},
    { name:'ADCD_RESULT_REGS',     start : 0x303C3000, end : 0x303C4000},
    { name:'ADCE_RESULT_REGS',     start : 0x303C4000, end : 0x303C5000},
    { name:'EMIF_CFG_REGS',        start : 0x30800000, end : 0x30801000},

    // Peripherals with framesel. Address 0x6..
    { name:'RTDMA1_CH1_REGS',       start : 0x60000000, end : 0x60001000,},
    { name:'RTDMA1_CH2_REGS',       start : 0x60001000, end : 0x60002000,},
    { name:'RTDMA1_CH3_REGS',       start : 0x60002000, end : 0x60003000,},
    { name:'RTDMA1_CH4_REGS',       start : 0x60003000, end : 0x60004000,},
    { name:'RTDMA1_CH5_REGS',       start : 0x60004000, end : 0x60005000,},
    { name:'RTDMA1_CH6_REGS',       start : 0x60005000, end : 0x60006000,},
    { name:'RTDMA1_CH7_REGS',       start : 0x60006000, end : 0x60007000,},
    { name:'RTDMA1_CH8_REGS',       start : 0x60007000, end : 0x60008000,},
    { name:'RTDMA1_CH9_REGS',       start : 0x60008000, end : 0x60009000,},
    { name:'RTDMA1_CH10_REGS',      start : 0x60009000, end : 0x6000A000,},
    { name:'RTDMA2_CH1_REGS',       start : 0x60010000, end : 0x60011000,},
    { name:'RTDMA2_CH2_REGS',       start : 0x60011000, end : 0x60012000,},
    { name:'RTDMA2_CH3_REGS',       start : 0x60012000, end : 0x60013000,},
    { name:'RTDMA2_CH4_REGS',       start : 0x60013000, end : 0x60014000,},
    { name:'RTDMA2_CH5_REGS',       start : 0x60014000, end : 0x60015000,},
    { name:'RTDMA2_CH6_REGS',       start : 0x60015000, end : 0x60016000,},
    { name:'RTDMA2_CH7_REGS',       start : 0x60016000, end : 0x60017000,},
    { name:'RTDMA2_CH8_REGS',       start : 0x60017000, end : 0x60018000,},
    { name:'RTDMA2_CH9_REGS',       start : 0x60018000, end : 0x60019000,},
    { name:'RTDMA2_CH10_REGS',      start : 0x60019000, end : 0x6001A000,},
    { name:'MCANA_MSGRAM',          start : 0x60020000, end : 0x60021000,},
    { name:'MCANA_REGS',            start : 0x60024000, end : 0x60025000,},
    { name:'MCANB_MSGRAM',          start : 0x60028000, end : 0x60029000,},
    { name:'MCANB_REGS',            start : 0x6002C000, end : 0x6002D000,},
    { name:'MCANC_MSGRAM',          start : 0x60030000, end : 0x60031000,},
    { name:'MCANC_REGS',            start : 0x60034000, end : 0x60035000,},
    { name:'MCAND_MSGRAM',          start : 0x60038000, end : 0x60039000,},
    { name:'MCAND_REGS',            start : 0x6003C000, end : 0x6003D000,},
    { name:'MCANE_MSGRAM',          start : 0x60040000, end : 0x60041000,},
    { name:'MCANE_REGS',            start : 0x60044000, end : 0x60045000,},
    { name:'MCANF_MSGRAM',          start : 0x60048000, end : 0x60049000,},
    { name:'MCANF_REGS',            start : 0x6004C000, end : 0x6004D000,},
    { name:'LINA_REGS',             start : 0x60060000, end : 0x60061000,},
    { name:'LINB_REGS',             start : 0x60061000, end : 0x60062000,},
    { name:'SENT1_REGS',            start : 0x60068000, end : 0x60069000,},
    { name:'SENT2_REGS',            start : 0x60069000, end : 0x6006A000,},
    { name:'SENT3_REGS',            start : 0x6006A000, end : 0x6006B000,},
    { name:'SENT4_REGS',            start : 0x6006B000, end : 0x6006C000,},
    { name:'SENT5_REGS',            start : 0x6006C000, end : 0x6006D000,},
    { name:'SENT6_REGS',            start : 0x6006D000, end : 0x6006E000,},
    { name:'UARTA_REGS',            start : 0x60070000, end : 0x60072000,},
    { name:'UARTB_REGS',            start : 0x60072000, end : 0x60074000,},
    { name:'UARTC_REGS',            start : 0x60074000, end : 0x60076000,},
    { name:'UARTD_REGS',            start : 0x60076000, end : 0x60078000,},
    { name:'UARTE_REGS',            start : 0x60078000, end : 0x6007A000,},
    { name:'UARTF_REGS',            start : 0x6007A000, end : 0x6007C000,},
    { name:'DCC1_REGS',             start : 0x60080000, end : 0x60081000,},
    { name:'DCC2_REGS',             start : 0x60081000, end : 0x60082000,},
    { name:'DCC3_REGS',             start : 0x60082000, end : 0x60083000,},
    { name:'ERR_AGG_REGS',          start : 0x6008C000, end : 0x6008D000,},
    { name:'ESM_CPU1_REGS',         start : 0x60090000, end : 0x60091000,},
    { name:'ESM_CPU2_REGS',         start : 0x60091000, end : 0x60092000,},
    { name:'ESM_CPU3_REGS',         start : 0x60092000, end : 0x60093000,},
    { name:'ESM_SYS_REGS',          start : 0x6009F000, end : 0x600A0000,},
    { name:'ESM_SAFETY_AGG_REGS',   start : 0x600A0000, end : 0x600A1000,},
    { name:'WADI1_CONFIG_REGS',     start : 0x600B0000, end : 0x600B1000,},
    { name:'WADI1_OPER_SSS_REGS',   start : 0x600B1000, end : 0x600B2000,},
    { name:'WADI2_CONFIG_REGS',     start : 0x600B2000, end : 0x600B3000,},
    { name:'WADI2_OPER_SSS_REGS',   start : 0x600B3000, end : 0x600B4000,},
    { name:'OUTXBAR1_FLAG_REGS',    start : 0x600C0000, end : 0x600C1000,},
    { name:'OUTXBAR2_FLAG_REGS',    start : 0x600C1000, end : 0x600C2000,},
    { name:'OUTXBAR3_FLAG_REGS',    start : 0x600C2000, end : 0x600C3000,},
    { name:'OUTXBAR4_FLAG_REGS',    start : 0x600C3000, end : 0x600C4000,},
    { name:'OUTXBAR5_FLAG_REGS',    start : 0x600C4000, end : 0x600C5000,},
    { name:'OUTXBAR6_FLAG_REGS',    start : 0x600C5000, end : 0x600C6000,},
    { name:'OUTXBAR7_FLAG_REGS',    start : 0x600C6000, end : 0x600C7000,},
    { name:'OUTXBAR8_FLAG_REGS',    start : 0x600C7000, end : 0x600C8000,},
    { name:'OUTXBAR9_FLAG_REGS',    start : 0x600C8000, end : 0x600C9000,},
    { name:'OUTXBAR10_FLAG_REGS',   start : 0x600C9000, end : 0x600CA000,},
    { name:'OUTXBAR11_FLAG_REGS',   start : 0x600CA000, end : 0x600CB000,},
    { name:'OUTXBAR12_FLAG_REGS',   start : 0x600CB000, end : 0x600CC000,},
    { name:'OUTXBAR13_FLAG_REGS',   start : 0x600CC000, end : 0x600CD000,},
    { name:'OUTXBAR14_FLAG_REGS',   start : 0x600CD000, end : 0x600CE000,},
    { name:'OUTXBAR15_FLAG_REGS',   start : 0x600CE000, end : 0x600CF000,},
    { name:'OUTXBAR16_FLAG_REGS',   start : 0x600CF000, end : 0x600D0000,},
    { name:'INPUTXBARFLAGS_REGS',   start : 0x600E0000, end : 0x600E1000,},
    { name:'CPU1_DLT_FIFO_REGS',    start : 0x600F8000, end : 0x600FA000,},
    { name:'CPU2_DLT_FIFO_REGS',    start : 0x600FA000, end : 0x600FC000,},
    { name:'CPU3_DLT_FIFO_REGS',    start : 0x600FC000, end : 0x600FE000,},

    // Peripherals with framesel. Address 0x7..
    { name:'EPWM1_REGS',                  start : 0x70000000, end : 0x70001000},
    { name:'EPWM2_REGS',                  start : 0x70001000, end : 0x70002000},
    { name:'EPWM3_REGS',                  start : 0x70002000, end : 0x70003000},
    { name:'EPWM4_REGS',                  start : 0x70003000, end : 0x70004000},
    { name:'EPWM5_REGS',                  start : 0x70004000, end : 0x70005000},
    { name:'EPWM6_REGS',                  start : 0x70005000, end : 0x70006000},
    { name:'EPWM7_REGS',                  start : 0x70006000, end : 0x70007000},
    { name:'EPWM8_REGS',                  start : 0x70007000, end : 0x70008000},
    { name:'EPWM9_REGS',                  start : 0x70008000, end : 0x70009000},
    { name:'EPWM10_REGS',                 start : 0x70009000, end : 0x7000A000},
    { name:'EPWM11_REGS',                 start : 0x7000A000, end : 0x7000B000},
    { name:'EPWM12_REGS',                 start : 0x7000B000, end : 0x7000C000},
    { name:'EPWM13_REGS',                 start : 0x7000C000, end : 0x7000D000},
    { name:'EPWM14_REGS',                 start : 0x7000D000, end : 0x7000E000},
    { name:'EPWM15_REGS',                 start : 0x7000E000, end : 0x7000F000},
    { name:'EPWM16_REGS',                 start : 0x7000F000, end : 0x70010000},
    { name:'EPWM17_REGS',                 start : 0x70010000, end : 0x70011000},
    { name:'EPWM18_REGS',                 start : 0x70011000, end : 0x70012000},
    { name:'EPWM_XLINK',                  start : 0x70040000, end : 0x70080000}, // TODO : What is this?
    { name:'HRPWMCAL1_REGS',              start : 0x70080000, end : 0x70081000},
    { name:'HRPWMCAL2_REGS',              start : 0x70081000, end : 0x70082000},
    { name:'HRPWMCAL3_REGS',              start : 0x70082000, end : 0x70083000},
    { name:'EQEP1_REGS',                  start : 0x70088000, end : 0x70089000},
    { name:'EQEP2_REGS',                  start : 0x70089000, end : 0x7008A000},
    { name:'EQEP3_REGS',                  start : 0x7008A000, end : 0x7008B000},
    { name:'EQEP4_REGS',                  start : 0x7008B000, end : 0x7008C000},
    { name:'EQEP5_REGS',                  start : 0x7008C000, end : 0x7008D000},
    { name:'EQEP6_REGS',                  start : 0x7008D000, end : 0x7008E000},
    { name:'SDFM1_REGS',                  start : 0x70090000, end : 0x70091000},
    { name:'SDFM2_REGS',                  start : 0x70091000, end : 0x70092000},
    { name:'SDFM3_REGS',                  start : 0x70092000, end : 0x70093000},
    { name:'SDFM4_REGS',                  start : 0x70093000, end : 0x70094000},
    { name:'ADCA_REGS',                   start : 0x700A0000, end : 0x700A1000},
    { name:'ADCB_REGS',                   start : 0x700A1000, end : 0x700A2000},
    { name:'ADCC_REGS',                   start : 0x700A2000, end : 0x700A3000},
    { name:'ADCD_REGS',                   start : 0x700A3000, end : 0x700A4000},
    { name:'ADCE_REGS',                   start : 0x700A4000, end : 0x700A5000},
    { name:'ADC_SAFETY_CHECKER1_REGS',    start : 0x700B0000, end : 0x700B1000},
    { name:'ADC_SAFETY_CHECKER2_REGS',    start : 0x700B0000, end : 0x700B2000},
    { name:'ADC_SAFETY_CHECKER3_REGS',    start : 0x700B2000, end : 0x700B3000},
    { name:'ADC_SAFETY_CHECKER4_REGS',    start : 0x700B3000, end : 0x700B4000},
    { name:'ADC_SAFETY_CHECKER5_REGS',    start : 0x700B4000, end : 0x700B5000},
    { name:'ADC_SAFETY_CHECKER6_REGS',    start : 0x700B5000, end : 0x700B6000},
    { name:'ADC_SAFETY_CHECKER7_REGS',    start : 0x700B6000, end : 0x700B7000},
    { name:'ADC_SAFETY_CHECKER8_REGS',    start : 0x700B7000, end : 0x700B8000},
    { name:'ADC_SAFETY_CHECKER9_REGS',    start : 0x700B8000, end : 0x700B9000},
    { name:'ADC_SAFETY_CHECKER10_REGS',   start : 0x700B9000, end : 0x700BA000},
    { name:'ADC_SAFECHECK_INTEVT1_REGS',  start : 0x700C0000, end : 0x700C1000},
    { name:'ADC_SAFECHECK_INTEVT2_REGS',  start : 0x700C1000, end : 0x700C2000},
    { name:'ADC_SAFECHECK_INTEVT3_REGS',  start : 0x700C2000, end : 0x700C3000},
    { name:'ADC_GLOBAL_SOC_REGS',         start : 0x700C8000, end : 0x700C9000},
    { name:'DACA_REGS',                   start : 0x700D0000, end : 0x700D1000},
    { name:'DACB_REGS',                   start : 0x700D1000, end : 0x700D2000},
    { name:'CMPSS1_REGS',                 start : 0x700E0000, end : 0x700E1000},
    { name:'CMPSS2_REGS',                 start : 0x700E1000, end : 0x700E2000},
    { name:'CMPSS3_REGS',                 start : 0x700E2000, end : 0x700E3000},
    { name:'CMPSS4_REGS',                 start : 0x700E3000, end : 0x700E4000},
    { name:'CMPSS5_REGS',                 start : 0x700E4000, end : 0x700E5000},
    { name:'CMPSS6_REGS',                 start : 0x700E5000, end : 0x700E6000},
    { name:'CMPSS7_REGS',                 start : 0x700E6000, end : 0x700E7000},
    { name:'CMPSS8_REGS',                 start : 0x700E7000, end : 0x700E8000},
    { name:'CMPSS9_REGS',                 start : 0x700E8000, end : 0x700E9000},
    { name:'CMPSS10_REGS',                start : 0x700E9000, end : 0x700EA000},
    { name:'CMPSS11_REGS',                start : 0x700EA000, end : 0x700EB000},
    { name:'CMPSS12_REGS',                start : 0x700EB000, end : 0x700EC000},
    { name:'ECAP1_REGS',                  start : 0x70100000, end : 0x70101000},
    { name:'ECAP2_REGS',                  start : 0x70101000, end : 0x70102000},
    { name:'ECAP3_REGS',                  start : 0x70102000, end : 0x70103000},
    { name:'ECAP4_REGS',                  start : 0x70103000, end : 0x70104000},
    { name:'ECAP5_REGS',                  start : 0x70104000, end : 0x70105000},
    { name:'ECAP6_REGS',                  start : 0x70105000, end : 0x70106000},
    { name:'CLB1_REGS',                   start : 0x70120000, end : 0x70121000},
    { name:'CLB2_REGS',                   start : 0x70121000, end : 0x70122000},
    { name:'CLB3_REGS',                   start : 0x70122000, end : 0x70123000},
    { name:'CLB4_REGS',                   start : 0x70123000, end : 0x70124000},
    { name:'CLB5_REGS',                   start : 0x70124000, end : 0x70125000},
    { name:'CLB6_REGS',                   start : 0x70125000, end : 0x70126000},
    { name:'PMBUSA_REGS',                 start : 0x70148000, end : 0x70149000},
    { name:'I2CA_REGS',                   start : 0x70150000, end : 0x70151000},
    { name:'I2CB_REGS',                   start : 0x70151000, end : 0x70152000},
    { name:'SPIA_REGS',                   start : 0x70158000, end : 0x70159000},
    { name:'SPIB_REGS',                   start : 0x70159000, end : 0x7015A000},
    { name:'SPIC_REGS',                   start : 0x7015A000, end : 0x7015B000},
    { name:'SPID_REGS',                   start : 0x7015B000, end : 0x7015C000},
    { name:'SPIE_REGS',                   start : 0x7015C000, end : 0x7015D000},
    { name:'FSITXA_REGS',                 start : 0x70180000, end : 0x70181000},
    { name:'FSITXB_REGS',                 start : 0x70181000, end : 0x70182000},
    { name:'FSITXC_REGS',                 start : 0x70182000, end : 0x70183000},
    { name:'FSITXD_REGS',                 start : 0x70183000, end : 0x70184000},
    { name:'FSIRXA_REGS',                 start : 0x70188000, end : 0x70189000},
    { name:'FSIRXB_REGS',                 start : 0x70189000, end : 0x7018A000},
    { name:'FSIRXC_REGS',                 start : 0x7018A000, end : 0x7018B000},
    { name:'FSIRXD_REGS',                 start : 0x7018B000, end : 0x7018C000},
    { name:'EPG_REGS',                    start : 0x701C0000, end : 0x701C1000},
];


const bootmodes = [
    // Flash boot
    {name: "03", displayName:"Flash Boot"},

    // RAM boot
    {name: "05", displayName:"RAM Boot at LPA0_RAM"},
    {name: "25", displayName:"RAM Boot at CPA0_RAM"},

    // Parallel bootloader
    {name: "00", displayName:"Parallel Boot 1"},
    {name: "20", displayName:"Parallel Boot 2"},

    // CAN Bootloader
    {name: "02", displayName:"Classic CAN Boot 1"},
    {name: "22", displayName:"Classic CAN Boot 2"},
    {name: "42", displayName:"Classic CAN Boot 3"},
    {name: "62", displayName:"Classic CAN Boot 4"},
    {name: "08", displayName:"CAN-FD Boot 1"},
    {name: "48", displayName:"CAN-FD Boot 3"},
    {name: "28", displayName:"CAN-FD Boot 2"},
    {name: "68", displayName:"CAN-FD Boot 4"},

    // I2C Bootloader
    {name: "07", displayName:"I2C Boot 1"},
    {name: "27", displayName:"I2C Boot 2"},
    {name: "47", displayName:"I2C Boot 3"},
    {name: "67", displayName:"I2C Boot 4"},

    // SPI Bootloader
    {name: "06", displayName:"SPI Boot 1"},
    {name: "26", displayName:"SPI Boot 2"},
    {name: "46", displayName:"SPI Boot 3"},
    {name: "66", displayName:"SPI Boot 4"},

    // UART Bootloader
    {name: "01", displayName:"UART Boot 1"},
    {name: "21", displayName:"UART Boot 2"},
    {name: "41", displayName:"UART Boot 3"},
    {name: "61", displayName:"UART Boot 4"},
    {name: "81", displayName:"UART Boot 5"},

    // Wait boot
    {name: "04", displayName:"Wait Boot"},
]


function getFrame(periph)
{
    var perConfig = system.modules['/driverlib/perConfig.js'];
    if (perConfig != null)
    {
        // Find the peripheralInst available in perConfig.js
        var frameSelInstName = periph.name.replace("_REGS", "")
        if(frameSelInstName.startsWith("RTDMA1"))
            frameSelInstName = "RTDMA1"
        if(frameSelInstName.startsWith("RTDMA2"))
            frameSelInstName = "RTDMA2"
        if(frameSelInstName.startsWith("MCAN"))
            frameSelInstName.replace("_MSGRAM", "")
        if(frameSelInstName.startsWith("OUTXBAR"))
            frameSelInstName = "OUTPUTXBARFLAGS"

        for(var i = 0; i < perConfig.$instances.length; i++)
        {
            var instance = perConfig.$instances[i];
            let owner = instance.$ownedBy;

            var peripheralInst = instance.peripheralInst;
            if (instance.pinmuxPeripheralModule)
            {
                let ownerSolution = owner[instance.pinmuxPeripheralModule].$solution;
                if(ownerSolution){
                    var ownerPeripheral = ownerSolution.peripheralName;
                    peripheralInst = ownerPeripheral;
                }
            }
            if(peripheralInst == frameSelInstName)
                return parseInt(instance.frameSel.replace("FRAME",""))
        }
    }
    return 0
}

function getPeriphsSortedbyFrame()
{
    let periphs = peripheralList
    periphs.forEach(periph => {
        if((periph.start >> 28) == 3){          // No frame
            periph.actualStart = periph.start
            periph.actualEnd = periph.end
        }

        else{
            periph.actualStart = periph.start +  getFrame(periph) * 0x400000
            periph.actualEnd = periph.end +  getFrame(periph) * 0x400000
        }
    })
    return periphs.sort((x,y)=>x.actualStart - y.actualStart)
}


exports = {
    peripheralList,
    bootmodes,
    getPeriphsSortedbyFrame
}