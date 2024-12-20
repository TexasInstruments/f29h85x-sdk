let ECAPRegisters = [
	{ name: "TSCTR", description: "Time-Stamp Counter", offset: "0x0",
		bits: [
		]
	},
	{ name: "CTRPHS", description: "Counter Phase Offset Value Register", offset: "0x4",
		bits: [
		]
	},
	{ name: "CAP1", description: "Capture 1 Register", offset: "0x8",
		bits: [
		]
	},
	{ name: "CAP2", description: "Capture 2 Register", offset: "0xC",
		bits: [
		]
	},
	{ name: "CAP3", description: "Capture 3 Register", offset: "0x10",
		bits: [
		]
	},
	{ name: "CAP4", description: "Capture 4 Register", offset: "0x14",
		bits: [
		]
	},
	{ name: "ECCTL0", description: "Capture Control Register 0", offset: "0x24",
		bits: [
			{ name: "INPUTSEL", description: "INPUT source select", size: "8", shift: "0", mask: "0xFF" },
			{ name: "QUALPRD", description: "Reserved", size: "4", shift: "12", mask: "0xF000" },
			{ name: "SOCEVTSEL", description: "Reserved", size: "2", shift: "16", mask: "0x30000" },
		]
	},
	{ name: "ECCTL1", description: "Capture Control Register 1", offset: "0x28",
		bits: [
			{ name: "CAP1POL", description: "Capture Event 1 Polarity select", size: "1", shift: "0", mask: "0x1" },
			{ name: "CTRRST1", description: "Counter Reset on Capture Event 1", size: "1", shift: "1", mask: "0x2" },
			{ name: "CAP2POL", description: "Capture Event 2 Polarity select", size: "1", shift: "2", mask: "0x4" },
			{ name: "CTRRST2", description: "Counter Reset on Capture Event 2", size: "1", shift: "3", mask: "0x8" },
			{ name: "CAP3POL", description: "Capture Event 3 Polarity select", size: "1", shift: "4", mask: "0x10" },
			{ name: "CTRRST3", description: "Counter Reset on Capture Event 3", size: "1", shift: "5", mask: "0x20" },
			{ name: "CAP4POL", description: "Capture Event 4 Polarity select", size: "1", shift: "6", mask: "0x40" },
			{ name: "CTRRST4", description: "Counter Reset on Capture Event 4", size: "1", shift: "7", mask: "0x80" },
			{ name: "CAPLDEN", description: "Enable Loading CAP1-4 regs on a Cap Event", size: "1", shift: "8", mask: "0x100" },
			{ name: "PRESCALE", description: "Event Filter prescale select", size: "5", shift: "9", mask: "0x3E00" },
			{ name: "FREE_SOFT", description: "Emulation mode", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "ECCTL2", description: "Capture Control Register 2", offset: "0x2A",
		bits: [
			{ name: "CONT_ONESHT", description: "Continuous or one-shot", size: "1", shift: "0", mask: "0x1" },
			{ name: "STOP_WRAP", description: "Stop value for one-shot, Wrap for continuous", size: "2", shift: "1", mask: "0x6" },
			{ name: "REARM", description: "One-shot re-arm", size: "1", shift: "3", mask: "0x8" },
			{ name: "TSCTRSTOP", description: "TSCNT counter stop", size: "1", shift: "4", mask: "0x10" },
			{ name: "SYNCI_EN", description: "Counter sync-in select", size: "1", shift: "5", mask: "0x20" },
			{ name: "SYNCO_SEL", description: "Sync-out mode", size: "2", shift: "6", mask: "0xC0" },
			{ name: "SWSYNC", description: "SW forced counter sync", size: "1", shift: "8", mask: "0x100" },
			{ name: "CAP_APWM", description: "CAP/APWM operating mode select", size: "1", shift: "9", mask: "0x200" },
			{ name: "APWMPOL", description: "APWM output polarity select", size: "1", shift: "10", mask: "0x400" },
			{ name: "CTRFILTRESET", description: "Reset event filter, modulus counter, and interrupt", size: "1", shift: "11", mask: "0x800" },
			{ name: "DMAEVTSEL", description: "DMA event select", size: "2", shift: "12", mask: "0x3000" },
			{ name: "MODCNTRSTS", description: "modulo counter status", size: "2", shift: "14", mask: "0xC000" },
		]
	},
	{ name: "ECEINT", description: "Capture Interrupt Enable Register", offset: "0x2C",
		bits: [
			{ name: "CEVT1", description: "Capture Event 1 Interrupt Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "CEVT2", description: "Capture Event 2 Interrupt Enable", size: "1", shift: "2", mask: "0x4" },
			{ name: "CEVT3", description: "Capture Event 3 Interrupt Enable", size: "1", shift: "3", mask: "0x8" },
			{ name: "CEVT4", description: "Capture Event 4 Interrupt Enable", size: "1", shift: "4", mask: "0x10" },
			{ name: "CTROVF", description: "Counter Overflow Interrupt Enable", size: "1", shift: "5", mask: "0x20" },
			{ name: "CTR_EQ_PRD", description: "Period Equal Interrupt Enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "CTR_EQ_CMP", description: "Compare Equal Interrupt Enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "MUNIT_1_ERROR_EVT1", description: "Monitoring unit 1 error event-1 interrupt", size: "1", shift: "9", mask: "0x200" },
			{ name: "MUNIT_1_ERROR_EVT2", description: "Monitoring unit 1 error event-2 interrupt", size: "1", shift: "10", mask: "0x400" },
			{ name: "MUNIT_2_ERROR_EVT1", description: "Monitoring unit 2 error event-1 interrupt", size: "1", shift: "11", mask: "0x800" },
			{ name: "MUNIT_2_ERROR_EVT2", description: "Monitoring unit 2 error event-2 interrupt", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "ECFLG", description: "Capture Interrupt Flag Register", offset: "0x2E",
		bits: [
			{ name: "INT", description: "Global Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "CEVT1", description: "Capture Event 1 Interrupt Flag", size: "1", shift: "1", mask: "0x2" },
			{ name: "CEVT2", description: "Capture Event 2 Interrupt Flag", size: "1", shift: "2", mask: "0x4" },
			{ name: "CEVT3", description: "Capture Event 3 Interrupt Flag", size: "1", shift: "3", mask: "0x8" },
			{ name: "CEVT4", description: "Capture Event 4 Interrupt Flag", size: "1", shift: "4", mask: "0x10" },
			{ name: "CTROVF", description: "Counter Overflow Interrupt Flag", size: "1", shift: "5", mask: "0x20" },
			{ name: "CTR_PRD", description: "Period Equal Interrupt Flag", size: "1", shift: "6", mask: "0x40" },
			{ name: "CTR_CMP", description: "Compare Equal Interrupt Flag", size: "1", shift: "7", mask: "0x80" },
			{ name: "MUNIT_1_ERROR_EVT1", description: "Error event 2 Interrupt Flag from monitoring", size: "1", shift: "9", mask: "0x200" },
			{ name: "MUNIT_1_ERROR_EVT2", description: "Error event 2 Interrupt Flag from monitoring", size: "1", shift: "10", mask: "0x400" },
			{ name: "MUNIT_2_ERROR_EVT1", description: "Error event 2 Interrupt Flag from monitoring", size: "1", shift: "11", mask: "0x800" },
			{ name: "MUNIT_2_ERROR_EVT2", description: "Error event 2 Interrupt Flag from monitoring", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "ECCLR", description: "Capture Interrupt Clear Register", offset: "0x30",
		bits: [
			{ name: "INT", description: "ECAP Global Interrupt Status Clear", size: "1", shift: "0", mask: "0x1" },
			{ name: "CEVT1", description: "Capture Event 1 Status Clear", size: "1", shift: "1", mask: "0x2" },
			{ name: "CEVT2", description: "Capture Event 2 Status Clear", size: "1", shift: "2", mask: "0x4" },
			{ name: "CEVT3", description: "Capture Event 3 Status Clear", size: "1", shift: "3", mask: "0x8" },
			{ name: "CEVT4", description: "Capture Event 4 Status Clear", size: "1", shift: "4", mask: "0x10" },
			{ name: "CTROVF", description: "Counter Overflow Status Clear", size: "1", shift: "5", mask: "0x20" },
			{ name: "CTR_PRD", description: "Period Equal Status Clear", size: "1", shift: "6", mask: "0x40" },
			{ name: "CTR_CMP", description: "Compare Equal Status Clear", size: "1", shift: "7", mask: "0x80" },
			{ name: "MUNIT_1_ERROR_EVT1", description: "MUNIT_1_ERROR_EVT1 interrupt flag Clear", size: "1", shift: "9", mask: "0x200" },
			{ name: "MUNIT_1_ERROR_EVT2", description: "MUNIT_1_ERROR_EVT2 interrupt flag Clear", size: "1", shift: "10", mask: "0x400" },
			{ name: "MUNIT_2_ERROR_EVT1", description: "MUNIT_2_ERROR_EVT1 interrupt flag Clear", size: "1", shift: "11", mask: "0x800" },
			{ name: "MUNIT_2_ERROR_EVT2", description: "MUNIT_2_ERROR_EVT2 interrupt flag Clear", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "ECFRC", description: "Capture Interrupt Force Register", offset: "0x32",
		bits: [
			{ name: "CEVT1", description: "Capture Event 1 Force Interrupt", size: "1", shift: "1", mask: "0x2" },
			{ name: "CEVT2", description: "Capture Event 2 Force Interrupt", size: "1", shift: "2", mask: "0x4" },
			{ name: "CEVT3", description: "Capture Event 3 Force Interrupt", size: "1", shift: "3", mask: "0x8" },
			{ name: "CEVT4", description: "Capture Event 4 Force Interrupt", size: "1", shift: "4", mask: "0x10" },
			{ name: "CTROVF", description: "Counter Overflow Force Interrupt", size: "1", shift: "5", mask: "0x20" },
			{ name: "CTR_PRD", description: "Period Equal Force Interrupt", size: "1", shift: "6", mask: "0x40" },
			{ name: "CTR_CMP", description: "Compare Equal Force Interrupt", size: "1", shift: "7", mask: "0x80" },
			{ name: "MUNIT_1_ERROR_EVT1", description: "MUNIT_1_ERROR_EVT1 interrupt flag Set", size: "1", shift: "9", mask: "0x200" },
			{ name: "MUNIT_1_ERROR_EVT2", description: "MUNIT_1_ERROR_EVT2 interrupt flag Set", size: "1", shift: "10", mask: "0x400" },
			{ name: "MUNIT_2_ERROR_EVT1", description: "MUNIT_2_ERROR_EVT1 interrupt flag Set", size: "1", shift: "11", mask: "0x800" },
			{ name: "MUNIT_2_ERROR_EVT2", description: "MUNIT_2_ERROR_EVT2 interrupt flag Set", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "SYNCINSEL", description: "SYNC source select register", offset: "0x3C",
		bits: [
			{ name: "SEL", description: "SYNCIN source select", size: "7", shift: "0", mask: "0x7F" },
		]
	},
	{ name: "HRCTL", description: "High-Res Control Register", offset: "0x0",
		bits: [
			{ name: "HRE", description: "High Resolution Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "HRCLKE", description: "High Resolution Clock Enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "PRDSEL", description: "Calibration Period Match", size: "1", shift: "2", mask: "0x4" },
			{ name: "CALIBSTART", description: "Calibration start", size: "1", shift: "3", mask: "0x8" },
			{ name: "CALIBSTS", description: "Calibration status", size: "1", shift: "4", mask: "0x10" },
			{ name: "CALIBCONT", description: "Continuous mode Calibration Select", size: "1", shift: "5", mask: "0x20" },
		]
	},
	{ name: "HRINTEN", description: "High-Res Calibration Interrupt Enable Register", offset: "0x8",
		bits: [
			{ name: "CALIBDONE", description: "Calibration doe interrupt enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "CALPRDCHKSTS", description: "Calibration period check status enable", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "HRFLG", description: "High-Res Calibration Interrupt Flag Register", offset: "0xC",
		bits: [
			{ name: "CALIBINT", description: "Global calibration Interrupt Status Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "CALIBDONE", description: "Calibration Done Interrupt Flag Bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "CALPRDCHKSTS", description: "Calibration period check status Flag Bi", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "HRCLR", description: "High-Res Calibration Interrupt Clear Register", offset: "0x10",
		bits: [
			{ name: "CALIBINT", description: "Clear Global calibration Interrupt Flag", size: "1", shift: "0", mask: "0x1" },
			{ name: "CALIBDONE", description: "Clear Calibration Done Interrupt Flag Bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "CALPRDCHKSTS", description: "Clear Calibration period check status Flag Bit", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "HRFRC", description: "High-Res Calibration Interrupt Force Register", offset: "0x14",
		bits: [
			{ name: "CALIBDONE", description: "Force Calibration Done Interrupt Flag Bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "CALPRDCHKSTS", description: "Force Calibration period check status Flag Bit", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "HRCALPRD", description: "High-Res Calibration Period Register", offset: "0x18",
		bits: [
		]
	},
	{ name: "HRSYSCLKCTR", description: "High-Res Calibration SYSCLK Counter Register", offset: "0x1C",
		bits: [
		]
	},
	{ name: "HRSYSCLKCAP", description: "High-Res Calibration SYSCLK Capture Register", offset: "0x20",
		bits: [
		]
	},
	{ name: "HRCLKCTR", description: "High-Res Calibration HRCLK Counter Register", offset: "0x24",
		bits: [
		]
	},
	{ name: "HRCLKCAP", description: "High-Res Calibration HRCLK Capture Register", offset: "0x28",
		bits: [
		]
	},
	{ name: "MUNIT_COMMON_CTL", description: "Control registers for monitoring unit {#}", offset: "0x0",
		bits: [
			{ name: "TRIPSEL", description: "Trip signal select", size: "7", shift: "0", mask: "0x7F" },
			{ name: "GLDSTRBSEL", description: "Global Load strobe select", size: "7", shift: "8", mask: "0x7F00" },
		]
	},
	{ name: "MUNIT_1_CTL", description: "Control registers for monitoring unit 1", offset: "0x40",
		bits: [
			{ name: "EN", description: "Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "DEBUG_RANGE_EN", description: "Debug enable to aquire the range of", size: "1", shift: "1", mask: "0x2" },
			{ name: "DISABLE_EARLY_MAX_ERR", description: "Disable early max error check", size: "1", shift: "2", mask: "0x4" },
			{ name: "MON_SEL", description: "Selects type of monitoring", size: "4", shift: "8", mask: "0xF00" },
		]
	},
	{ name: "MUNIT_1_SHADOW_CTL", description: "Shadow control registers for monitoring unit 1", offset: "0x44",
		bits: [
			{ name: "SYNCI_EN", description: "Enable for shadowing on Min and Max Registers", size: "1", shift: "0", mask: "0x1" },
			{ name: "SWSYNC", description: "SW sync to copy shadow to active Min and Max", size: "1", shift: "1", mask: "0x2" },
			{ name: "LOADMODE", description: "Load mode", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "MUNIT_1_MIN", description: "Min value for monitoring unit 1", offset: "0x50",
		bits: [
		]
	},
	{ name: "MUNIT_1_MAX", description: "Max value for monitoring unit 1", offset: "0x54",
		bits: [
		]
	},
	{ name: "MUNIT_1_MIN_SHADOW", description: "Shadow register for Min value of monitoring", offset: "0x58",
		bits: [
		]
	},
	{ name: "MUNIT_1_MAX_SHADOW", description: "Shadow register for Max value of monitoring", offset: "0x5C",
		bits: [
		]
	},
	{ name: "MUNIT_1_DEBUG_RANGE_MIN", description: "Observed Min value of check being enabled on", offset: "0x60",
		bits: [
		]
	},
	{ name: "MUNIT_1_DEBUG_RANGE_MAX", description: "Observed Max value of check being enabled on", offset: "0x64",
		bits: [
		]
	},
	{ name: "MUNIT_2_CTL", description: "Control registers for monitoring unit 2", offset: "0x80",
		bits: [
			{ name: "EN", description: "Enable bit", size: "1", shift: "0", mask: "0x1" },
			{ name: "DEBUG_RANGE_EN", description: "Debug enable to aquire the range of", size: "1", shift: "1", mask: "0x2" },
			{ name: "DISABLE_EARLY_MAX_ERR", description: "Disable early max error check", size: "1", shift: "2", mask: "0x4" },
			{ name: "MON_SEL", description: "Selects type of monitoring", size: "4", shift: "8", mask: "0xF00" },
		]
	},
	{ name: "MUNIT_2_SHADOW_CTL", description: "Shadow control registers for monitoring unit 2", offset: "0x84",
		bits: [
			{ name: "SYNCI_EN", description: "Enable for shadowing on Min and Max Registers", size: "1", shift: "0", mask: "0x1" },
			{ name: "SWSYNC", description: "SW sync to copy shadow to active Min and Max", size: "1", shift: "1", mask: "0x2" },
			{ name: "LOADMODE", description: "Load mode", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "MUNIT_2_MIN", description: "Min value for monitoring unit 2", offset: "0x90",
		bits: [
		]
	},
	{ name: "MUNIT_2_MAX", description: "Max value for monitoring unit 2", offset: "0x94",
		bits: [
		]
	},
	{ name: "MUNIT_2_MIN_SHADOW", description: "Shadow register for Min value of monitoring", offset: "0x98",
		bits: [
		]
	},
	{ name: "MUNIT_2_MAX_SHADOW", description: "Shadow register for Max value of monitoring", offset: "0x9C",
		bits: [
		]
	},
	{ name: "MUNIT_2_DEBUG_RANGE_MIN", description: "Observed Min value of check being enabled on", offset: "0xA0",
		bits: [
		]
	},
	{ name: "MUNIT_2_DEBUG_RANGE_MAX", description: "Observed Max value of check being enabled on", offset: "0xA4",
		bits: [
		]
	},
];
module.exports = {
	ECAPRegisters: ECAPRegisters,
}
