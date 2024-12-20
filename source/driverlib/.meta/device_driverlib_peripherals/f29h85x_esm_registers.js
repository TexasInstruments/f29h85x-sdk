let ESMRegisters = [
	{ name: "PID", description: "Revision Register", offset: "0x0",
		bits: [
			{ name: "MINOR", description: "", size: "6", shift: "0", mask: "0x3F" },
			{ name: "CUSTOM", description: "", size: "2", shift: "6", mask: "0xC0" },
			{ name: "MAJOR", description: "", size: "3", shift: "8", mask: "0x700" },
			{ name: "RTL", description: "", size: "5", shift: "11", mask: "0xF800" },
			{ name: "FUNC", description: "", size: "12", shift: "16", mask: "0xFFF0000" },
			{ name: "BU", description: "", size: "2", shift: "28", mask: "0x30000000" },
			{ name: "SCHEME", description: "", size: "2", shift: "30", mask: "0xC0000000" },
		]
	},
	{ name: "INFO", description: "Info Register", offset: "0x4",
		bits: [
			{ name: "GROUPS", description: "", size: "8", shift: "0", mask: "0xFF" },
			{ name: "PULSE_GROUPS", description: "", size: "8", shift: "8", mask: "0xFF00" },
			{ name: "CRIT_INTR", description: "", size: "1", shift: "30", mask: "0x40000000" },
			{ name: "LAST_RESET", description: "", size: "1", shift: "31", mask: "0x80000000" },
		]
	},
	{ name: "EN", description: "Global Enable Register", offset: "0x8",
		bits: [
			{ name: "KEY", description: "", size: "4", shift: "0", mask: "0xF" },
		]
	},
	{ name: "SFT_RST", description: "Global Soft Reset Register", offset: "0xC",
		bits: [
			{ name: "KEY", description: "", size: "4", shift: "0", mask: "0xF" },
		]
	},
	{ name: "LOW_PRI", description: "Low Priority Prioritized", offset: "0x20",
		bits: [
			{ name: "PLS", description: "", size: "16", shift: "16", mask: "0xFFFF0000" },
			{ name: "LVL", description: "", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "HI_PRI", description: "High Priority Prioritized", offset: "0x24",
		bits: [
			{ name: "PLS", description: "", size: "16", shift: "16", mask: "0xFFFF0000" },
			{ name: "LVL", description: "", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "WD_CFG_WD_EN", description: "", size: "4", shift: "0", mask: "0xF" },
			{ name: "WD_INTR_SET_VAL", description: "", size: "1", shift: "0", mask: "0x1" },
			{ name: "WD_INTR_CLR_VAL", description: "", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "LOW", description: "Low Priority Interrupt Status", offset: "0x28",
		bits: [
			{ name: "PRI_PLS", description: "", size: "16", shift: "16", mask: "0xFFFF0000" },
			{ name: "PRI_LVL", description: "", size: "16", shift: "0", mask: "0xFFFF" },
		]
	},
	{ name: "HI", description: "High Priority Interrupt Status", offset: "0x2C",
		bits: [
			{ name: "PRI_PLS", description: "", size: "16", shift: "16", mask: "0xFFFF0000" },
			{ name: "PRI_LVL", description: "", size: "16", shift: "0", mask: "0xFFFF" },
			{ name: "PRI_WD_CFG_WD_EN", description: "", size: "4", shift: "0", mask: "0xF" },
			{ name: "PRI_WD_INTR_SET_VAL", description: "", size: "1", shift: "0", mask: "0x1" },
			{ name: "PRI_WD_INTR_CLR_VAL", description: "", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "EOI", description: "EOI Interrupt Register", offset: "0x30",
		bits: [
			{ name: "KEY", description: "", size: "11", shift: "0", mask: "0x7FF" },
		]
	},
	{ name: "PIN_CTRL", description: "Error Pin Control Register", offset: "0x40",
		bits: [
			{ name: "POLARITY", description: "", size: "4", shift: "8", mask: "0xF00" },
			{ name: "PWM_EN", description: "", size: "4", shift: "4", mask: "0xF0" },
			{ name: "KEY", description: "", size: "4", shift: "0", mask: "0xF" },
		]
	},
	{ name: "PIN_STS", description: "Error Pin Status Register", offset: "0x44",
		bits: [
			{ name: "VAL", description: "", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "PIN_CNTR", description: "Error Counter Value Register", offset: "0x48",
		bits: [
			{ name: "COUNT", description: "", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "PRE_COUNT", description: "", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PIN_CNTR_PRE", description: "Error Counter Value Pre-Load", offset: "0x4C",
		bits: [
			{ name: "COUNT", description: "", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PWMH_PIN_CNTR", description: "Error PWM High Counter Value", offset: "0x50",
		bits: [
			{ name: "COUNT", description: "", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "PRE_COUNT", description: "", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PWMH_PIN_CNTR_PRE", description: "Error PWM High Counter Value", offset: "0x54",
		bits: [
			{ name: "COUNT", description: "", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PWML_PIN_CNTR", description: "Error PWM Low Counter Value", offset: "0x58",
		bits: [
			{ name: "COUNT", description: "", size: "24", shift: "0", mask: "0xFFFFFF" },
			{ name: "PRE_COUNT", description: "", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "PWML_PIN_CNTR_PRE", description: "Error PWM Low Counter Value", offset: "0x5C",
		bits: [
			{ name: "COUNT", description: "", size: "24", shift: "0", mask: "0xFFFFFF" },
		]
	},
	{ name: "HI_PRI_WD_CFG", description: "High Priority Watchdog Config", offset: "0x80",
		bits: [
			{ name: "WD_EN", description: "", size: "4", shift: "0", mask: "0xF" },
		]
	},
	{ name: "HI_PRI_WD_CNTR", description: "High Priority Watchdog Counter", offset: "0x84",
		bits: [
		]
	},
	{ name: "HI_PRI_WD_CNTR_PRE", description: "High Priority Watchdog Pre-Load", offset: "0x88",
		bits: [
		]
	},
	{ name: "HI_PRI_WD_INTR_SET", description: "High Priority Watchdog", offset: "0x8C",
		bits: [
			{ name: "VAL", description: "", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "HI_PRI_WD_INTR_CLR", description: "High Priority Watchdog", offset: "0x90",
		bits: [
			{ name: "VAL", description: "", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "GROUP_N_LOCK", description: "Group N Interrupt Lock Register", offset: "0x100",
		bits: [
		]
	},
	{ name: "GROUP_N_COMMIT", description: "Group N Interrupt Commit", offset: "0x104",
		bits: [
		]
	},
	{ name: "ERR_PIN_INFLUENCE_LOCK", description: "Error Pin Influence Lock", offset: "0x110",
		bits: [
		]
	},
	{ name: "ERR_PIN_INFLUENCE_COMMIT", description: "Error Pin Influence Commit", offset: "0x114",
		bits: [
		]
	},
	{ name: "CRI_PRI_INFLUENCE_LOCK", description: "Critical Prioirty Interrupt", offset: "0x118",
		bits: [
		]
	},
	{ name: "CRI_PRI_INFLUENCE_COMMIT", description: "Critical Priority Interrupt", offset: "0x11C",
		bits: [
		]
	},
	{ name: "MMR_CONFIG_LOCK", description: "MMR Config Lock Register", offset: "0x120",
		bits: [
			{ name: "GLOBEL_EN_LOCK", description: "", size: "1", shift: "8", mask: "0x100" },
			{ name: "GLOBAL_SOFT_RST_LOCK", description: "", size: "1", shift: "5", mask: "0x20" },
			{ name: "ERRPIN_LOCK", description: "", size: "1", shift: "2", mask: "0x4" },
			{ name: "ERRPIN_MON_LOCK", description: "", size: "1", shift: "1", mask: "0x2" },
			{ name: "HI_PRI_WD_LOCK", description: "", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "MMR_CONFIG_COMMIT", description: "MMR Config Commit Register", offset: "0x124",
		bits: [
			{ name: "GLOBEL_EN_COMMIT", description: "", size: "1", shift: "8", mask: "0x100" },
			{ name: "GLOBAL_SOFT_RST_COMMIT", description: "", size: "1", shift: "5", mask: "0x20" },
			{ name: "ERRPIN_COMMIT", description: "", size: "1", shift: "2", mask: "0x4" },
			{ name: "ERRPIN_MON_COMMIT", description: "", size: "1", shift: "1", mask: "0x2" },
			{ name: "HI_PRI_WD_COMMIT", description: "", size: "1", shift: "0", mask: "0x1" },
		]
	},
	{ name: "RAW", description: "(0 <= i < 8) Error Group N", offset: "(0x400U + ((i) * 32))", count: "8",
		bits: [
		]
	},
	{ name: "STS", description: "(0 <= i < 8) Error Group N", offset: "(0x404U + ((i) * 32))", count: "8",
		bits: [
		]
	},
	{ name: "INTR_EN_SET", description: "(0 <= i < 8) Error Group N", offset: "(0x408U + ((i) * 32))", count: "8",
		bits: [
		]
	},
	{ name: "INTR_EN_CLR", description: "(0 <= i < 8) Error Group N", offset: "(0x40CU + ((i) * 32))", count: "8",
		bits: [
		]
	},
	{ name: "INT_PRIO", description: "(0 <= i < 8) Error Group N", offset: "(0x410U + ((i) * 32))", count: "8",
		bits: [
		]
	},
	{ name: "PIN_EN_SET", description: "(0 <= i < 8) Error Group N", offset: "(0x414U + ((i) * 32))", count: "8",
		bits: [
		]
	},
	{ name: "PIN_EN_CLR", description: "(0 <= i < 8) Error Group N", offset: "(0x418U + ((i) * 32))", count: "8",
		bits: [
		]
	},
	{ name: "CRIT_EN_SET", description: "(0 <= i < 8) Error Group N", offset: "(0x800U + ((i) * 32))", count: "8",
		bits: [
		]
	},
	{ name: "CRIT_EN_CLR", description: "(0 <= i < 8) Error Group N", offset: "(0x804U + ((i) * 32))", count: "8",
		bits: [
		]
	},
];
module.exports = {
	ESMRegisters: ESMRegisters,
}
