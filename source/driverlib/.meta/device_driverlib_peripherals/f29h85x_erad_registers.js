let ERADRegisters = [
	{ name: "GLBL_ERAD_ID", description: "Debug Peripheral ID", offset: "0x0",
		bits: [
			{ name: "MINOR", description: "Minor", size: "6", shift: "0", mask: "0x3F" },
			{ name: "CUSTOM", description: "Custom", size: "2", shift: "6", mask: "0xC0" },
			{ name: "MAJOR", description: "Major", size: "3", shift: "8", mask: "0x700" },
			{ name: "RTL", description: "RTL", size: "5", shift: "11", mask: "0xF800" },
			{ name: "FUNC", description: "Func", size: "12", shift: "16", mask: "0xFFF0000" },
			{ name: "BUSINESS_UNIT", description: "Business Unit", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "SCHEME", description: "Scheme", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "GLBL_EVENT_STAT", description: "Global Event Status", offset: "0x4",
		bits: [
			{ name: "EBC", description: "EBC Module Event Status", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "SEC", description: "SEC Module Event Status", size: "16", shift: "16", mask: "0xFFFF0000" },
		]
	},
	{ name: "EBC_OWNER", description: "(0 <= i < 8) EBC Owner", offset: "(0x40U + ((i) * 64))", count: "8",
		bits: [
			{ name: "OWNER", description: "Ownership ID", size: "2", shift: "0", mask: "0x3" },
			{ name: "ZONE", description: "Zone ID", size: "4", shift: "8", mask: "0xF00" },
			{ name: "SROOT", description: "SROOT LINK ownership", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SEM", description: "Semaphore", size: "1", shift: "16", mask: "0x10000" },
			{ name: "CONFIG", description: "Configuration", size: "2", shift: "17", mask: "0x60000" },
		]
	},
	{ name: "EBC_CNTL", description: "(0 <= i < 8) EBC Control", offset: "(0x44U + ((i) * 64))", count: "8",
		bits: [
			{ name: "EN", description: "Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "BUS_SEL", description: "Bus select bits", size: "5", shift: "1", mask: "0x3E" },
			{ name: "HALT", description: "CPU Halt", size: "1", shift: "6", mask: "0x40" },
			{ name: "INTERRUPT", description: "Interrupt enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "NMI_EN", description: "NMI enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "COMP_MODE", description: "Compare mode", size: "3", shift: "9", mask: "0xE00" },
			{ name: "STACK_QUAL", description: "Stack access qualifier", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SPSEL_MATCH_EN", description: "SPSEL match enable", size: "1", shift: "13", mask: "0x2000" },
			{ name: "SPSEL", description: "SPSEL", size: "4", shift: "14", mask: "0x3C000" },
		]
	},
	{ name: "EBC_STATUS", description: "(0 <= i < 8) EBC Status", offset: "(0x48U + ((i) * 64))", count: "8",
		bits: [
			{ name: "EVENT_FIRED", description: "EBC Event Fired bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "STATUS", description: "Status bits", size: "2", shift: "8", mask: "0x300" },
		]
	},
	{ name: "EBC_STATUSCLEAR", description: "(0 <= i < 8) EBC Clear", offset: "(0x4CU + ((i) * 64))", count: "8",
		bits: [
			{ name: "EVENT_FIRED", description: "Event Clear register", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "EBC_REFL", description: "(0 <= i < 8) EBC Reference", offset: "(0x50U + ((i) * 64))", count: "8",
		bits: [
		]
	},
	{ name: "EBC_REFH", description: "(0 <= i < 8) EBC Reference", offset: "(0x54U + ((i) * 64))", count: "8",
		bits: [
		]
	},
	{ name: "EBC_MASKL", description: "(0 <= i < 8) EBC Mask Low", offset: "(0x58U + ((i) * 64))", count: "8",
		bits: [
		]
	},
	{ name: "EBC_MASKH", description: "(0 <= i < 8) EBC Mask High", offset: "(0x5CU + ((i) * 64))", count: "8",
		bits: [
		]
	},
	{ name: "EBC_WP_PC", description: "(0 <= i < 8) EBC", offset: "(0x60U + ((i) * 64))", count: "8",
		bits: [
		]
	},
	{ name: "SEC_OWNER", description: "(0 <= i < 4) SEC Owner", offset: "(0x440U + ((i) * 64))", count: "4",
		bits: [
			{ name: "OWNER", description: "Ownership ID", size: "2", shift: "0", mask: "0x3" },
			{ name: "ZONE", description: "Zone ID", size: "4", shift: "8", mask: "0xF00" },
			{ name: "SROOT", description: "SROOT LINK ownership", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SEM", description: "Semaphore", size: "1", shift: "16", mask: "0x10000" },
			{ name: "CONFIG", description: "Configuration", size: "2", shift: "17", mask: "0x60000" },
		]
	},
	{ name: "SEC_CNTL", description: "(0 <= i < 4) SEC Control", offset: "(0x444U + ((i) * 64))", count: "4",
		bits: [
			{ name: "EN", description: "Enable", size: "1", shift: "0", mask: "0x1" },
			{ name: "EDGE_LEVEL", description: "Event mode bit", size: "1", shift: "1", mask: "0x2" },
			{ name: "START_STOP_MODE", description: "Start_stop mode bit", size: "1", shift: "2", mask: "0x4" },
			{ name: "START_STOP_CUMULATIVE", description: "Start stop cumulative bit", size: "1", shift: "3", mask: "0x8" },
			{ name: "RST_ON_MATCH", description: "Reset_on_match bit", size: "1", shift: "4", mask: "0x10" },
			{ name: "HALT", description: "CPU Halt", size: "1", shift: "5", mask: "0x20" },
			{ name: "INTERRUPT", description: "Interrupt enable", size: "1", shift: "6", mask: "0x40" },
			{ name: "NMI_EN", description: "NMI enable", size: "1", shift: "7", mask: "0x80" },
			{ name: "CNT_INP_SEL_EN", description: "Counter input select enable", size: "1", shift: "8", mask: "0x100" },
			{ name: "RST_INP_SEL_EN", description: "Counter reset input select enable", size: "1", shift: "9", mask: "0x200" },
			{ name: "FREE_RUN", description: "counter behaviour on CPU Halt", size: "1", shift: "10", mask: "0x400" },
		]
	},
	{ name: "SEC_STATUS", description: "(0 <= i < 4) SEC Status", offset: "(0x448U + ((i) * 64))", count: "4",
		bits: [
			{ name: "EVENT_FIRED", description: "Counter Event Fired bits", size: "1", shift: "0", mask: "0x1" },
			{ name: "OVERFLOW", description: "Counter Overflowed", size: "1", shift: "1", mask: "0x2" },
			{ name: "STATUS", description: "Status bits", size: "2", shift: "8", mask: "0x300" },
		]
	},
	{ name: "SEC_STATUSCLEAR", description: "(0 <= i < 4) SEC Clear", offset: "(0x44CU + ((i) * 64))", count: "4",
		bits: [
			{ name: "EVENT_FIRED", description: "Clear EVENT_FIRED", size: "1", shift: "0", mask: "0x1" },
			{ name: "OVERFLOW", description: "Clear OVERFLOW", size: "1", shift: "1", mask: "0x2" },
		]
	},
	{ name: "SEC_REF", description: "(0 <= i < 4) SEC Reference", offset: "(0x450U + ((i) * 64))", count: "4",
		bits: [
		]
	},
	{ name: "SEC_INPUT_SEL1", description: "(0 <= i < 4) SEC Input", offset: "(0x454U + ((i) * 64))", count: "4",
		bits: [
			{ name: "CNT_INP_SEL", description: "Counter Input Select", size: "8", shift: "0", mask: "0xFF" },
			{ name: "RST_INP_SEL", description: "Counter Reset input Select", size: "8", shift: "16", mask: "0xFF0000" },
		]
	},
	{ name: "SEC_INPUT_SEL2", description: "(0 <= i < 4) SEC Input", offset: "(0x458U + ((i) * 64))", count: "4",
		bits: [
			{ name: "STA_INP_SEL", description: "Counter Sart Input Select", size: "8", shift: "0", mask: "0xFF" },
			{ name: "STO_INP_SEL", description: "Counter Stop Input Select", size: "8", shift: "16", mask: "0xFF0000" },
		]
	},
	{ name: "SEC_INPUT_COND", description: "(0 <= i < 4) SEC Input", offset: "(0x45CU + ((i) * 64))", count: "4",
		bits: [
			{ name: "SEC_INP_INV", description: "Counter Input Invert", size: "1", shift: "0", mask: "0x1" },
			{ name: "STA_INP_INV", description: "Start input Invert", size: "1", shift: "4", mask: "0x10" },
			{ name: "STO_INP_INV", description: "Stop input Invert", size: "1", shift: "8", mask: "0x100" },
			{ name: "RST_INP_INV", description: "Reset input Invert", size: "1", shift: "12", mask: "0x1000" },
		]
	},
	{ name: "SEC_COUNT", description: "(0 <= i < 4) SEC Counter", offset: "(0x460U + ((i) * 64))", count: "4",
		bits: [
		]
	},
	{ name: "SEC_MAX_COUNT", description: "(0 <= i < 4) SEC Max Count", offset: "(0x464U + ((i) * 64))", count: "4",
		bits: [
		]
	},
	{ name: "SEC_MIN_COUNT", description: "(0 <= i < 4) SEC Min Count", offset: "(0x468U + ((i) * 64))", count: "4",
		bits: [
		]
	},
	{ name: "AND_MASK_OWNER", description: "(0 <= i < 4) AND Owner", offset: "(0x640U + ((i) * 32))", count: "4",
		bits: [
			{ name: "OWNER", description: "Ownership ID", size: "2", shift: "0", mask: "0x3" },
			{ name: "ZONE", description: "Zone ID", size: "4", shift: "8", mask: "0xF00" },
			{ name: "SROOT", description: "SROOT LINK ownership", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SEM", description: "Semaphore", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "AND_MASK_CTL", description: "(0 <= i < 4) AND Control", offset: "(0x644U + ((i) * 32))", count: "4",
		bits: [
			{ name: "HALT", description: "CPU Halt", size: "1", shift: "0", mask: "0x1" },
			{ name: "INTERRUPT", description: "Interrupt enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "NMI_EN", description: "NMI enable", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "EVENT_AND_MASK", description: "(0 <= i < 4) AND Event", offset: "(0x648U + ((i) * 32))", count: "4",
		bits: [
			{ name: "MASK_EBC", description: "EBC, SEC AND Event Mask", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "OR_MASK_OWNER", description: "(0 <= i < 4) OR Owner", offset: "(0x740U + ((i) * 32))", count: "4",
		bits: [
			{ name: "OWNER", description: "Ownership ID", size: "2", shift: "0", mask: "0x3" },
			{ name: "ZONE", description: "Zone ID", size: "4", shift: "8", mask: "0xF00" },
			{ name: "SROOT", description: "SROOT LINK ownership", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SEM", description: "Semaphore", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "OR_MASK_CTL", description: "(0 <= i < 4) OR Control", offset: "(0x744U + ((i) * 32))", count: "4",
		bits: [
			{ name: "HALT", description: "CPU Halt", size: "1", shift: "0", mask: "0x1" },
			{ name: "INTERRUPT", description: "Interrupt enable", size: "1", shift: "1", mask: "0x2" },
			{ name: "NMI_EN", description: "NMI enable", size: "1", shift: "2", mask: "0x4" },
		]
	},
	{ name: "EVENT_OR_MASK", description: "(0 <= i < 4) OR Event", offset: "(0x748U + ((i) * 32))", count: "4",
		bits: [
			{ name: "MASK_EBC", description: "EBC, SEC OR Event Mask", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PCTRACE_OWNER", description: "Owner Register", offset: "0x840",
		bits: [
			{ name: "OWNER", description: "Ownership ID", size: "2", shift: "0", mask: "0x3" },
			{ name: "ZONE", description: "Zone ID", size: "4", shift: "8", mask: "0xF00" },
			{ name: "SROOT", description: "SROOT LINK ownership", size: "1", shift: "12", mask: "0x1000" },
			{ name: "SEM", description: "Semaphore", size: "1", shift: "16", mask: "0x10000" },
		]
	},
	{ name: "PCTRACE_GLOBAL", description: "Global Control Register", offset: "0x844",
		bits: [
			{ name: "EN", description: "Enable PC  trace", size: "1", shift: "0", mask: "0x1" },
			{ name: "INIT", description: "Initialize the PC Trace and buffer", size: "1", shift: "8", mask: "0x100" },
			{ name: "BUFFER_SIZE", description: "Trace buffer size", size: "2", shift: "16", mask: "0x30000" },
		]
	},
	{ name: "PCTRACE_BUFFER", description: "Trace Buffer pointer", offset: "0x848",
		bits: [
			{ name: "PTR", description: "Trace Buffer Pointer", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "BUFFER_FULL", description: "Trace Buffer Full", size: "1", shift: "16", mask: "0x10000" },
			{ name: "BASE_BLOCKED", description: "Access blocked due to", size: "1", shift: "0", mask: "0x1" },
			{ name: "BASE_PROGRAM_COUNTER", description: "Program Counter", size: "31", shift: "1", mask: "0xFFFFFFFE" },
		]
	},
	{ name: "PCTRACE_QUAL1", description: "Trace Qualifier register 1", offset: "0x84C",
		bits: [
			{ name: "WINDOWED_INP_SEL", description: "Windowed trace qualifier", size: "8", shift: "0", mask: "0xFF" },
			{ name: "TRACE_MODE", description: "Trace qualifier mode", size: "2", shift: "16", mask: "0x30000" },
			{ name: "WINDOWED_INP_INV", description: "Windowed trace Input Invert", size: "1", shift: "18", mask: "0x40000" },
			{ name: "START_INP_INV", description: "Start input Invert", size: "1", shift: "20", mask: "0x100000" },
			{ name: "STOP_INP_INV", description: "Stop input Invert", size: "1", shift: "22", mask: "0x400000" },
		]
	},
	{ name: "PCTRACE_QUAL2", description: "Trace Qualifier register 2", offset: "0x850",
		bits: [
			{ name: "START_INP_SEL", description: "Trace Start event select", size: "8", shift: "0", mask: "0xFF" },
			{ name: "STOP_INP_SEL", description: "Trace Stop event select", size: "8", shift: "16", mask: "0xFF0000" },
		]
	},
	{ name: "PCTRACE_LOGPC_SOFTENABLE", description: "PC when PC Trace was last", offset: "0x854",
		bits: [
		]
	},
	{ name: "PCTRACE_LOGPC_SOFTDISABLE", description: "PC when PC Trace was last", offset: "0x858",
		bits: [
		]
	},
	{ name: "PCTRACE_BUFFER_BASE", description: "(0 <= i < 256) Trace", offset: "(0x1000U + ((i) * 0x4U))", count: "256",
		bits: [
			{ name: "BLOCKED", description: "Access blocked due to", size: "1", shift: "0", mask: "0x1" },
			{ name: "PROGRAM_COUNTER", description: "Program Counter", size: "31", shift: "1", mask: "0xFFFFFFFE" },
		]
	},
];
module.exports = {
	ERADRegisters: ERADRegisters,
}
