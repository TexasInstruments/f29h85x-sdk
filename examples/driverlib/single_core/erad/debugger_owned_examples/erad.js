//#############################################################################
//
// erad.js
//
// This file contains addresses and offsets for the ERAD registers, and the
// enums.
//
//#############################################################################

console.log("Including erad.js \n");

//
// ERAD Registers Base Address
//
let ERAD_BASE  =  0x30030000;

//
// ERAD Enhanced Bus Comparator (EBC) Instances
//
let ERAD_EBC_BASE = [
    0x30030040,
    0x30030080,
    0x300300C0,
    0x30030100,
    0x30030140,
    0x30030180,
    0x300301C0,
    0x30030200
]

//
// ERAD System Event Counter (SEC) Instances
//
let ERAD_SEC_BASE = [
    0x30030440,
    0x30030480,
    0x300304C0,
    0x30030500,
]

//
// ERAD Global Register Offsets
//
let ERAD_Global_Regs_Offset = {
    "GLBL_ERAD_ID"     : 0x0,    //  Global ERAD ID 
    "GLBL_EVENT_STAT"  : 0x4,    //  Global Event Status Register
}

//
// Enhanced Bus Comparator (EBC) Register Offsets
//
let ERAD_Ebc_Regs_Offset = {
    "EBC_OWNER"        : 0x0  ,   // (0 <: i < 8) EBC Owner Register
    "EBC_CNTL"         : 0x4  ,   // (0 <: i < 8) EBC Control Register
    "EBC_STATUS"       : 0x8  ,   // (0 <: i < 8) EBC Status Register
    "EBC_STATUSCLEAR"  : 0xC  ,   // (0 <: i < 8) EBC Clear Register
    "EBC_REFL"         : 0x10 ,   // (0 <: i < 8) EBC Reference Low Register
    "EBC_REFH"         : 0x14 ,   // (0 <: i < 8) EBC Reference High Register
    "EBC_MASKL"        : 0x18 ,   // (0 <: i < 8) EBC Mask Low Register
    "EBC_MASKH"        : 0x1C ,   // (0 <: i < 8) EBC Mask High Register
    "EBC_WP_PC"        : 0x20 ,   // (0 <: i < 8) EBC Watchpoint PC Register
}

//
// System Event Counter (SEC) Register Offsets
//
let ERAD_Sec_Regs_Offset = {
    "SEC_OWNER"        : 0x0 ,    // (0 <: i < 8) SEC Owner Register
    "SEC_CNTL"         : 0x4 ,    // (0 <: i < 8) SEC Control Register
    "SEC_STATUS"       : 0x8 ,    // (0 <: i < 8) SEC Status Register
    "SEC_STATUSCLEAR"  : 0xC ,    // (0 <: i < 8) SEC Clear Register
    "SEC_REF"          : 0x10,    // (0 <: i < 8) SEC Reference Register
    "SEC_INPUT_SEL1"   : 0x14,    // (0 <: i < 8) SEC Input Select Register1
    "SEC_INPUT_SEL2"   : 0x18,    // (0 <: i < 8) SEC Input Select Register2
    "SEC_INPUT_COND"   : 0x1C,    // (0 <: i < 8) SEC Input Conditioning Register
    "SEC_COUNT"        : 0x20,    // (0 <: i < 8) SEC Counter Register
    "SEC_MAX_COUNT"    : 0x24,    // (0 <: i < 8) SEC Max Count Register
    "SEC_MIN_COUNT"    : 0x28,    // (0 <: i < 8) SEC Min Count Register
}

//
// Values for EBC Bus select parameter to choose which CPU bus to monitor.
//
let ERAD_Buscomp_Bus_Select = {
    "ERAD_BUS_PAB"           : 0x0 ,  //! Use the Program Address Bus (PAB)
    "ERAD_BUS_DWAB"          : 0x1 ,  //! Use the Data Write Address Bus (DWAB)
    "ERAD_BUS_DRAB_W"        : 0x5 ,  //! Use the Data Read Address Bus (DRAB_W)
    "ERAD_BUS_DRAB1_W"       : 0x6 ,  //! Use the Data Read Address Bus (DRAB1_W)
    "ERAD_BUS_DRAB2_W"       : 0x7 ,  //! Use the Data Read Address Bus (DRAB2_W)
    "ERAD_BUS_DWDB"          : 0x8 ,  //! Use the Data Write Data Bus (DWDB)
    "ERAD_BUS_DRDB"          : 0x9 ,  //! Use the Data Read Data Bus (DRDB)
    "ERAD_BUS_DRDB1"         : 0xA ,  //! Use the Data Read Data Bus (DRDB1)
    "ERAD_BUS_DRDB2"         : 0xB ,  //! Use the Data Read Data Bus (DRDB2)
    "ERAD_BUS_VPC_I_ALIGNED" : 0xC ,  //! Use VPC Instruction aligned match
    "ERAD_BUS_VPC_W_ALIGNED" : 0xE ,  //! Use VPC Write aligned match
}

//
// ERAD Owner
//
let ERAD_Owner = {
    "ERAD_OWNER_NOOWNER"     : 0,     //! No owner
    "ERAD_OWNER_DEBUGGER"    : 1,     //! Debugger owned
    "ERAD_OWNER_APPLICATION" : 2,     //! Application owned
}

//
// ERAD Miscellaneous constants
//
let ERAD_Misc = {
    "SEC_STATUS_M"         : 0xF000,
    "EBC_BUS_SEL_M"        : 0x1,
    "SEC_INP_SEL_ENABLE"   : 0x100,
    "SEC_STARTSTOP"        : 0x1 << 2,
    "SEC_MODE_RISING_EDGE" : 0x2,
    "ENABLE"               : 1,
}

//
// ERAD Counter events
//
let ERAD_Counter_Input_Event = {
     "ERAD_EVENT_EBC0"                       : 0 ,  //!EVENT EBC0
     "ERAD_EVENT_EBC1"                       : 1 ,  //!EVENT EBC1
     "ERAD_EVENT_EBC2"                       : 2 ,  //!EVENT EBC2
     "ERAD_EVENT_EBC3"                       : 3 ,  //!EVENT EBC3
     "ERAD_EVENT_EBC4"                       : 4 ,  //!EVENT EBC4
     "ERAD_EVENT_EBC5"                       : 5 ,  //!EVENT EBC5
     "ERAD_EVENT_EBC6"                       : 6 ,  //!EVENT EBC6
     "ERAD_EVENT_EBC7"                       : 7 ,  //!EVENT EBC7
     "ERAD_EVENT_COUNTER0_EVENT"    	     : 8 ,  //!EVENT COUNTER0 EVENT
     "ERAD_EVENT_COUNTER1_EVENT"    	     : 9 ,  //!EVENT COUNTER1 EVENT
     "ERAD_EVENT_COUNTER2_EVENT"    	     : 10 , //!EVENT COUNTER2 EVENT
     "ERAD_EVENT_COUNTER3_EVENT"    	     : 11 , //!EVENT COUNTER3 EVENT
     "ERAD_EVENT_ERAD_OR_MASK0"		         : 12 , //!EVENT ERAD OR MASK0
     "ERAD_EVENT_ERAD_OR_MASK1"		         : 13 , //!EVENT ERAD OR MASK1
     "ERAD_EVENT_ERAD_OR_MASK2"		         : 14 , //!EVENT ERAD OR MASK2
     "ERAD_EVENT_ERAD_OR_MASK3"		         : 15 , //!EVENT ERAD OR MASK3
     "ERAD_EVENT_ERAD_AND_MASK0"		     : 16 , //!EVENT ERAD AND MASK0
     "ERAD_EVENT_ERAD_AND_MASK1"		     : 17 , //!EVENT ERAD AND MASK1
     "ERAD_EVENT_ERAD_AND_MASK2"		     : 18 , //!EVENT ERAD AND MASK2
     "ERAD_EVENT_ERAD_AND_MASK3"		     : 19 , //!EVENT ERAD AND MASK3
     "ERAD_EVENT_PIPE_INT"		             : 20 , //!EVENT PIPE INT
     "ERAD_EVENT_PIPE_RTINT"		         : 21 , //!EVENT PIPE RTINT
     "ERAD_EVENT_PIPE_NMI"		             : 22 , //!EVENT PIPE NMI
     "ERAD_EVENT_CPU1_TIMER0_INT"            : 23 , //!CPU1 TIMER0 Interrupt
     "ERAD_EVENT_CPU1_TIMER1_INT"            : 24 , //!CPU1 TIMER1 Interrupt
     "ERAD_EVENT_CPU1_TIMER2_INT"            : 25 , //!CPU1 TIMER2 Interrupt
     "ERAD_EVENT_CPU2_TIMER0_INT"            : 26 , //!CPU2 TIMER0 Interrupt
     "ERAD_EVENT_CPU2_TIMER1_INT"            : 27 , //!CPU2 TIMER1 Interrupt
     "ERAD_EVENT_CPU2_TIMER2_INT"            : 28 , //!CPU2 TIMER2 Interrupt
     "ERAD_EVENT_CPU3_TIMER0_INT"            : 29 , //!CPU3 TIMER0 Interrupt
     "ERAD_EVENT_CPU3_TIMER1_INT"            : 30 , //!CPU3 TIMER1 Interrupt
     "ERAD_EVENT_CPU3_TIMER2_INT"            : 31 , //!CPU3 TIMER2 Interrupt
     "ERAD_EVENT_RTDMA1_CH1INT"	             : 32 , //!EVENT RTDMA1 CH1INT
     "ERAD_EVENT_RTDMA1_CH2INT"	             : 33 , //!EVENT RTDMA1 CH2INT
     "ERAD_EVENT_RTDMA1_CH3INT"	             : 34 , //!EVENT RTDMA1 CH3INT
     "ERAD_EVENT_RTDMA1_CH4INT"	             : 35 , //!EVENT RTDMA1 CH4INT
     "ERAD_EVENT_RTDMA1_CH5INT"	             : 36 , //!EVENT RTDMA1 CH5INT
     "ERAD_EVENT_RTDMA1_CH6INT"	             : 37 , //!EVENT RTDMA1 CH6INT
     "ERAD_EVENT_RTDMA1_CH7INT"	             : 38 , //!EVENT RTDMA1 CH7INT
     "ERAD_EVENT_RTDMA1_CH8INT"	             : 39 , //!EVENT RTDMA1 CH8INT
     "ERAD_EVENT_RTDMA1_CH9INT"	             : 40 , //!EVENT RTDMA1 CH9INT
     "ERAD_EVENT_RTDMA1_CH10INT"	         : 41 , //!EVENT RTDMA1 CH10INT
     "ERAD_EVENT_ADCAEVTINT"		         : 42 , //!EVENT ADCAEVTINT
     "ERAD_EVENT_ADCBEVTINT"		         : 43 , //!EVENT ADCBEVTINT
     "ERAD_EVENT_ADCCEVTINT"		         : 44 , //!EVENT ADCCEVTINT
     "ERAD_EVENT_ADCDEVTINT"		         : 45 , //!EVENT ADCDEVTINT
     "ERAD_EVENT_ADCEEVTINT"		         : 46 , //!EVENT ADCEEVTINT
     "ERAD_EVENT_ADCSOCA"		             : 47 , //!EVENT ADCSOCA
     "ERAD_EVENT_ADCSOCB"		             : 48 , //!EVENT ADCSOCB
     "ERAD_EVENT_RTDMA2_CH1INT"		         : 49 , //!EVENT RTDMA2 CH1INT
     "ERAD_EVENT_RTDMA2_CH2INT"		         : 50 , //!EVENT RTDMA2 CH2INT
     "ERAD_EVENT_RTDMA2_CH3INT"		         : 51 , //!EVENT RTDMA2 CH3INT
     "ERAD_EVENT_RTDMA2_CH4INT"		         : 52 , //!EVENT RTDMA2 CH4INT
     "ERAD_EVENT_RTDMA2_CH5INT"		         : 53 , //!EVENT RTDMA2 CH5INT
     "ERAD_EVENT_RTDMA2_CH6INT"		         : 54 , //!EVENT RTDMA2 CH6INT
     "ERAD_EVENT_RTDMA2_CH7INT"		         : 55 , //!EVENT RTDMA2 CH7INT
     "ERAD_EVENT_RTDMA2_CH8INT"		         : 56 , //!EVENT RTDMA2 CH8INT
     "ERAD_EVENT_RTDMA2_CH9INT"		         : 57 , //!EVENT RTDMA2 CH9INT
     "ERAD_EVENT_RTDMA2_CH10INT"		     : 58 , //!EVENT RTDMA2 CH10INT
     "ERAD_EVENT_EPWMXBAR_OUT1"		         : 59 , //!EVENT EPWMXBAR OUT1
     "ERAD_EVENT_EPWMXBAR_OUT2"		         : 60 , //!EVENT EPWMXBAR OUT2
     "ERAD_EVENT_EPWMXBAR_OUT3"		         : 61 , //!EVENT EPWMXBAR OUT3
     "ERAD_EVENT_EPWMXBAR_OUT4"		         : 62 , //!EVENT EPWMXBAR OUT4
     "ERAD_EVENT_EPWMXBAR_OUT5"		         : 63 , //!EVENT EPWMXBAR OUT5
     "ERAD_EVENT_EPWMXBAR_OUT6"		         : 64 , //!EVENT EPWMXBAR OUT6
     "ERAD_EVENT_EPWMXBAR_OUT7"		         : 65 , //!EVENT EPWMXBAR OUT7
     "ERAD_EVENT_EPWMXBAR_OUT8"		         : 66 , //!EVENT EPWMXBAR OUT8
     "ERAD_EVENT_INPUTXBAR1"                 : 67 , //!EVENT INPUTXBAR1
     "ERAD_EVENT_INPUTXBAR2"		         : 68 , //!EVENT INPUTXBAR2
     "ERAD_EVENT_INPUTXBAR3"		         : 69 , //!EVENT INPUTXBAR3
     "ERAD_EVENT_INPUTXBAR4"		         : 70 , //!EVENT INPUTXBAR4
     "ERAD_EVENT_INPUTXBAR5"		         : 71 , //!EVENT INPUTXBAR5
     "ERAD_EVENT_INPUTXBAR6"		         : 72 , //!EVENT INPUTXBAR6
     "ERAD_EVENT_INPUTXBAR7"		         : 73 , //!EVENT INPUTXBAR7
     "ERAD_EVENT_INPUTXBAR8"		         : 74 , //!EVENT INPUTXBAR8
     "ERAD_EVENT_INPUTXBAR9"    	         : 75 , //!EVENT INPUTXBAR9
     "ERAD_EVENT_INPUTXBAR10"		         : 76 , //!EVENT INPUTXBAR10
     "ERAD_EVENT_INPUTXBAR11"		         : 77 , //!EVENT INPUTXBAR11
     "ERAD_EVENT_INPUTXBAR12"		         : 78 , //!EVENT INPUTXBAR12
     "ERAD_EVENT_INPUTXBAR13"		         : 79 , //!EVENT INPUTXBAR13
     "ERAD_EVENT_INPUTXBAR14"		         : 80 , //!EVENT INPUTXBAR14
     "ERAD_EVENT_INPUTXBAR15"		         : 81 , //!EVENT INPUTXBAR15
     "ERAD_EVENT_INPUTXBAR16"		         : 82 , //!EVENT INPUTXBAR16
     "ERAD_EVENT_CMPSS1_CTRIPH_OR_CTRIPL"	 : 83 , //!EVENT CMPSS1 CTRIPH OR CTRIPL
     "ERAD_EVENT_CMPSS2_CTRIPH_OR_CTRIPL"	 : 84 , //!EVENT CMPSS2 CTRIPH OR CTRIPL
     "ERAD_EVENT_CMPSS3_CTRIPH_OR_CTRIPL"	 : 85 , //!EVENT CMPSS3 CTRIPH OR CTRIPL
     "ERAD_EVENT_CMPSS4_CTRIPH_OR_CTRIPL"	 : 86 , //!EVENT CMPSS4 CTRIPH OR CTRIPL
     "ERAD_EVENT_CMPSS5_CTRIPH_OR_CTRIPL"	 : 87 , //!EVENT CMPSS5 CTRIPH OR CTRIPL
     "ERAD_EVENT_CMPSS6_CTRIPH_OR_CTRIPL"	 : 88 , //!EVENT CMPSS6 CTRIPH OR CTRIPL
     "ERAD_EVENT_CMPSS7_CTRIPH_OR_CTRIPL"	 : 89 , //!EVENT CMPSS7 CTRIPH OR CTRIPL
     "ERAD_EVENT_CMPSS8_CTRIPH_OR_CTRIPL"	 : 90 , //!EVENT CMPSS8 CTRIPH OR CTRIPL
     "ERAD_EVENT_CMPSS9_CTRIPH_OR_CTRIPL"	 : 91 , //!EVENT CMPSS9 CTRIPH OR CTRIPL
     "ERAD_EVENT_CMPSS10_CTRIPH_OR_CTRIPL"	 : 92 , //!EVENT CMPSS10 CTRIPH OR CTRIPL
     "ERAD_EVENT_CMPSS11_CTRIPH_OR_CTRIPL"	 : 93 , //!EVENT CMPSS11 CTRIPH OR CTRIPL
     "ERAD_EVENT_CMPSS12_CTRIPH_OR_CTRIPL"	 : 94 , //!EVENT CMPSS12 CTRIPH OR CTRIPL
     "ERAD_EVENT_SD1FLT1_COMPH_OR_COMPL"	 : 95 , //!EVENT SD1FLT1 COMPH OR COMPL
     "ERAD_EVENT_SD1FLT2_COMPH_OR_COMPL"	 : 96 , //!EVENT SD1FLT2 COMPH OR COMPL
     "ERAD_EVENT_SD1FLT3_COMPH_OR_COMPL"	 : 97 , //!EVENT SD1FLT3 COMPH OR COMPL
     "ERAD_EVENT_SD1FLT4_COMPH_OR_COMPL"	 : 98 , //!EVENT SD1FLT4 COMPH OR COMPL
     "ERAD_EVENT_SD2FLT1_COMPH_OR_COMPL"	 : 99 , //!EVENT SD2FLT1 COMPH OR COMPL
    "ERAD_EVENT_SD2FLT2_COMPH_OR_COMPL"		 : 100,  //!EVENT SD2FLT2 COMPH OR COMPL
    "ERAD_EVENT_SD2FLT3_COMPH_OR_COMPL"		 : 101,  //!EVENT SD2FLT3 COMPH OR COMPL
    "ERAD_EVENT_SD2FLT4_COMPH_OR_COMPL"		 : 102,  //!EVENT SD2FLT4 COMPH OR COMPL
    "ERAD_EVENT_SD3FLT1_COMPH_OR_COMPL"		 : 103,  //!EVENT SD3FLT1 COMPH OR COMPL
    "ERAD_EVENT_SD3FLT2_COMPH_OR_COMPL"		 : 104,  //!EVENT SD3FLT2 COMPH OR COMPL
    "ERAD_EVENT_SD3FLT3_COMPH_OR_COMPL"		 : 105,  //!EVENT SD3FLT3 COMPH OR COMPL
    "ERAD_EVENT_SD3FLT4_COMPH_OR_COMPL"		 : 106,  //!EVENT SD3FLT4 COMPH OR COMPL
    "ERAD_EVENT_SD4FLT1_COMPH_OR_COMPL"		 : 107,  //!EVENT SD4FLT1 COMPH OR COMPL
    "ERAD_EVENT_SD4FLT2_COMPH_OR_COMPL"		 : 108,  //!EVENT SD4FLT2 COMPH OR COMPL
    "ERAD_EVENT_SD4FLT3_COMPH_OR_COMPL"		 : 109,  //!EVENT SD4FLT3 COMPH OR COMPL
    "ERAD_EVENT_SD4FLT4_COMPH_OR_COMPL"		 : 110,  //!EVENT SD4FLT4 COMPH OR COMPL
    "ERAD_EVENT_ADCAINT1"		             : 111,  //!EVENT ADCAINT1
    "ERAD_EVENT_ADCAINT2"		             : 112,  //!EVENT ADCAINT2
    "ERAD_EVENT_ADCAINT3"		             : 113,  //!EVENT ADCAINT3
    "ERAD_EVENT_ADCAINT4"		             : 114,  //!EVENT ADCAINT4
    "ERAD_EVENT_ADCBINT1"		             : 115,  //!EVENT ADCBINT1
    "ERAD_EVENT_ADCBINT2"		             : 116,  //!EVENT ADCBINT2
    "ERAD_EVENT_ADCBINT3"		             : 117,  //!EVENT ADCBINT3
    "ERAD_EVENT_ADCBINT4"		             : 118,  //!EVENT ADCBINT4
    "ERAD_EVENT_ADCCINT1"		             : 119,  //!EVENT ADCCINT1
    "ERAD_EVENT_ADCCINT2"		             : 120,  //!EVENT ADCCINT2
    "ERAD_EVENT_ADCCINT3"		             : 121,  //!EVENT ADCCINT3
    "ERAD_EVENT_ADCCINT4"		             : 122,  //!EVENT ADCCINT4
    "ERAD_EVENT_ADCDINT1"		             : 123,  //!EVENT ADCDINT1
    "ERAD_EVENT_ADCDINT2"		             : 124,  //!EVENT ADCDINT2
    "ERAD_EVENT_ADCDINT3"		             : 125,  //!EVENT ADCDINT3
    "ERAD_EVENT_ADCDINT4"		             : 126,  //!EVENT ADCDINT4
    "ERAD_EVENT_ADCEINT1"		             : 127,  //!EVENT ADCEINT1
    "ERAD_EVENT_ADCEINT2"		             : 128,  //!EVENT ADCEINT2
    "ERAD_EVENT_ADCEINT3"		             : 129,  //!EVENT ADCEINT3
    "ERAD_EVENT_ADCEINT4"		             : 130,  //!EVENT ADCEINT4
    "ERAD_EVENT_ECAT_PDI_SOF"		         : 131,  //!EVENT ECAT PDI SOF
    "ERAD_EVENT_ECAT_PDI_EOF"		         : 132,  //!EVENT ECAT PDI EOF
    "ERAD_EVENT_ECAT_PCI_WD_TRIGGER"	     : 133,  //!EVENT ECAT PCI WD TRIGGER
    "ERAD_EVENT_ECAT_PDI_UC_IRQ"		     : 134,  //!EVENT ECAT PDI UC IRQ
    "ERAD_EVENT_ECAT_SYNC_OUT0"		         : 135,  //!EVENT ECAT SYNC OUT0
    "ERAD_EVENT_ECAT_SYNC_OUT1"		         : 136,  //!EVENT ECAT SYNC OUT1
    "ERAD_EVENT_ECAT_DRAM_PARITY_ERROR"	 	 : 137,  //!EVENT ECAT DRAM PARITY ERROR
    "ERAD_EVENT_INPUTXBAR17"		         : 138,  //!EVENT INPUTXBAR17
    "ERAD_EVENT_INPUTXBAR18"		         : 139,  //!EVENT INPUTXBAR18
    "ERAD_EVENT_INPUTXBAR19"		         : 140,  //!EVENT INPUTXBAR19
    "ERAD_EVENT_INPUTXBAR20"		         : 141,  //!EVENT INPUTXBAR20
    "ERAD_EVENT_INPUTXBAR21"		         : 142,  //!EVENT INPUTXBAR21
    "ERAD_EVENT_INPUTXBAR22"		         : 143,  //!EVENT INPUTXBAR22
    "ERAD_EVENT_INPUTXBAR23"		         : 144,  //!EVENT INPUTXBAR23
    "ERAD_EVENT_INPUTXBAR24"		         : 145,  //!EVENT INPUTXBAR24
    "ERAD_EVENT_INPUTXBAR25"		         : 146,  //!EVENT INPUTXBAR25
    "ERAD_EVENT_INPUTXBAR26"		         : 147,  //!EVENT INPUTXBAR26
    "ERAD_EVENT_INPUTXBAR27"		         : 148,  //!EVENT INPUTXBAR27
    "ERAD_EVENT_INPUTXBAR28"		         : 149,  //!EVENT INPUTXBAR28
    "ERAD_EVENT_INPUTXBAR29"		         : 150,  //!EVENT INPUTXBAR29
    "ERAD_EVENT_INPUTXBAR30"		         : 151,  //!EVENT INPUTXBAR30
    "ERAD_EVENT_INPUTXBAR31"		         : 152,  //!EVENT INPUTXBAR31
    "ERAD_EVENT_INPUTXBAR32"		         : 153,  //!EVENT INPUTXBAR32
    "ERAD_EVENT_FSIA_DATA_PKT_RCVD"		     : 154,  //!EVENT FSIA DATA PKT RCVD
    "ERAD_EVENT_FSIA_ERROR_PKT_RCVD"		 : 155,  //!EVENT FSIA ERROR PKT RCVD
    "ERAD_EVENT_FSIA_PING_PKT_RCVD"		     : 156,  //!EVENT FSIA PING PKT RCVD
    "ERAD_EVENT_FSIA_PING_FRAME_TAG_MATCH"   : 157,  //!EVENT FSIA PING FRAME TAG MATCH
    "ERAD_EVENT_FSIA_DATA_FRAME_TAG_MATCH"   : 158,  //!EVENT FSIA DATA FRAME TAG MATCH
    "ERAD_EVENT_FSIA_ERROR_FRAME_TAG_MATCH"  : 159,  //!EVENT FSIA ERROR FRAME TAG MATCH
    "ERAD_EVENT_FSIA_FRAME_DONE"		     : 160,  //!EVENT FSIA FRAME DONE
    "ERAD_EVENT_FSIB_DATA_PKT_RCVD"		     : 161,  //!EVENT FSIB DATA PKT RCVD
    "ERAD_EVENT_FSIB_ERROR_PKT_RCVD"		 : 162,  //!EVENT FSIB ERROR PKT RCVD
    "ERAD_EVENT_FSIB_PING_PKT_RCVD"		     : 163,  //!EVENT FSIB PING PKT RCVD
    "ERAD_EVENT_FSIB_PING_FRAME_TAG_MATCH"	 : 164,  //!EVENT FSIB PING FRAME TAG MATCH
    "ERAD_EVENT_FSIB_DATA_FRAME_TAG_MATCH"	 : 165,  //!EVENT FSIB DATA FRAME TAG MATCH
    "ERAD_EVENT_FSIB_ERROR_FRAME_TAG_MATCH"	 : 166,  //!EVENT FSIB ERROR FRAME TAG MATCH
    "ERAD_EVENT_FSIB_FRAME_DONE"		     : 167,  //!EVENT FSIB FRAME DONE
    "ERAD_EVENT_FSIC_DATA_PKT_RCVD"		     : 168,  //!EVENT FSIC DATA PKT RCVD
    "ERAD_EVENT_FSIC_ERROR_PKT_RCVD"		 : 169,  //!EVENT FSIC ERROR PKT RCVD
    "ERAD_EVENT_FSIC_PING_PKT_RCVD"		     : 170,  //!EVENT FSIC PING PKT RCVD
    "ERAD_EVENT_FSIC_PING_FRAME_TAG_MATCH"   : 171,  //!EVENT FSIC PING FRAME TAG MATCH
    "ERAD_EVENT_FSIC_DATA_FRAME_TAG_MATCH"	 : 172,  //!EVENT FSIC DATA FRAME TAG MATCH
    "ERAD_EVENT_FSIC_ERROR_FRAME_TAG_MATCH"	 : 173,  //!EVENT FSIC ERROR FRAME TAG MATCH
    "ERAD_EVENT_FSIC_FRAME_DONE"		     : 174,  //!EVENT FSIC FRAME DONE
    "ERAD_EVENT_FSID_DATA_PKT_RCVD"	         : 175,  //!EVENT FSID DATA PKT RCVD
    "ERAD_EVENT_FSID_ERROR_PKT_RCVD"	     : 176,  //!EVENT FSID ERROR PKT RCVD
    "ERAD_EVENT_FSID_PING_PKT_RCVD"	         : 177,  //!EVENT FSID PING PKT RCVD
    "ERAD_EVENT_FSID_PING_FRAME_TAG_MATCH"	 : 178,  //!EVENT FSID PING FRAME TAG MATCH
    "ERAD_EVENT_FSID_DATA_FRAME_TAG_MATCH"	 : 179,  //!EVENT FSID DATA FRAME TAG MATCH
    "ERAD_EVENT_FSID_ERROR_FRAME_TAG_MATCH"	 : 180,  //!EVENT FSID ERROR FRAME TAG MATCH
    "ERAD_EVENT_FSID_FRAME_DONE"		     : 181,  //!EVENT FSID FRAME DONE
    "ERAD_EVENT_TRACE_HIT_EVENT"		     : 182,  //!EVENT TRACE HIT EVENT
    "ERAD_EVENT_CPU1_LCMCM_ERR"		         : 183,  //!CPU1 EVENT LCMCM ERR
    "ERAD_EVENT_RTDMA_LCM_CMP_ERR"		     : 184,  //!EVENT RTDMA LCM CMP ERR
    "ERAD_EVENT_MCANA_EVT0"		             : 185,  //!EVENT MCANA EVT0
    "ERAD_EVENT_MCANA_EVT1"		             : 186,  //!EVENT MCANA EVT1
    "ERAD_EVENT_MCANA_EVT2"		             : 187,  //!EVENT MCANA EVT2
    "ERAD_EVENT_MCANB_EVT0"		             : 188,  //!EVENT MCANB EVT0
    "ERAD_EVENT_MCANB_EVT1"		             : 189,  //!EVENT MCANB EVT1
    "ERAD_EVENT_MCANB_EVT2"		             : 190,  //!EVENT MCANB EVT2
    "ERAD_EVENT_MCANC_EVT0"		             : 191,  //!EVENT MCANC EVT0
    "ERAD_EVENT_MCANC_EVT1"		             : 192,  //!EVENT MCANC EVT1
    "ERAD_EVENT_MCANC_EVT2"		             : 193,  //!EVENT MCANC EVT2
    "ERAD_EVENT_MCAND_EVT0"		             : 194,  //!EVENT MCAND EVT0
    "ERAD_EVENT_MCAND_EVT1"		             : 195,  //!EVENT MCAND EVT1
    "ERAD_EVENT_MCAND_EVT2"		             : 196,  //!EVENT MCAND EVT2
    "ERAD_EVENT_MCANE_EVT0"		             : 197,  //!EVENT MCANE EVT0
    "ERAD_EVENT_MCANE_EVT1"		             : 198,  //!EVENT MCANE EVT1
    "ERAD_EVENT_MCANE_EVT2"		             : 199,  //!EVENT MCANE EVT2
    "ERAD_EVENT_MCANF_EVT0"		             : 200,  //!EVENT MCANF EVT0
    "ERAD_EVENT_MCANF_EVT1"		             : 201,  //!EVENT MCANF EVT1
    "ERAD_EVENT_MCANF_EVT2"		             : 202,  //!EVENT MCANF EVT2
    "ERAD_EVENT_CPUx_INT_ACK"		         : 203,  //!CPUx INT ACK
    "ERAD_EVENT_CPUx_RTINT_ACK"		         : 204,  //!CPUx RTINT ACK
    "ERAD_EVENT_CPUx_VIS_R1_PC_VALID"		 : 205,  //!CPUx VIS R1 PC VALID
    "ERAD_EVENT_CPUx_VIS_W_DR1_REQ"		     : 206,  //!CPUx VIS W DR1 REQ
    "ERAD_EVENT_CPUx_VIS_W_DR2_REQ"		     : 207,  //!CPUx VIS W DR2 REQ
    "ERAD_EVENT_CPUx_VIS_W_DW_REQ"		     : 208,  //!CPUx VIS W DW REQ
    "ERAD_EVENT_CPUx_CPI_D2_READY"		     : 209,  //!CPUx CPI D2 READY
    "ERAD_EVENT_CPUx_CPI_R1_READY"		     : 210,  //!CPUx CPI R1 READY
    "ERAD_EVENT_CPUx_CPI_EXE_READY"		     : 211,  //!CPUx CPI EXE READY
    "ERAD_EVENT_NO_EVENT"					 : 256,  //!EVENT NO EVENT
}

module.exports = {
    ERAD_BASE,
    ERAD_EBC_BASE,
    ERAD_SEC_BASE,
    ERAD_Global_Regs_Offset,
    ERAD_Ebc_Regs_Offset,
    ERAD_Sec_Regs_Offset,
    ERAD_Owner,
    ERAD_Buscomp_Bus_Select,
    ERAD_Counter_Input_Event,
    ERAD_Misc,
 }

//
// End of File
//