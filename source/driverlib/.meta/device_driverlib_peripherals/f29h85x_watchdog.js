let SysCtl_WDMode = [
	{ name: "SYSCTL_WD_MODE_RESET", displayName: "Watchdog can generate a reset signal" },
	{ name: "SYSCTL_WD_MODE_INTERRUPT", displayName: "Watchdog can generate an interrupt signal; reset signal is disabled" },
]
let SysCtl_WDPredivider = [
	{ name: "SYSCTL_WD_PREDIV_2", displayName: "PREDIVCLK = INTOSC1 / 2" },
	{ name: "SYSCTL_WD_PREDIV_4", displayName: "PREDIVCLK = INTOSC1 / 4" },
	{ name: "SYSCTL_WD_PREDIV_8", displayName: "PREDIVCLK = INTOSC1 / 8" },
	{ name: "SYSCTL_WD_PREDIV_16", displayName: "PREDIVCLK = INTOSC1 / 16" },
	{ name: "SYSCTL_WD_PREDIV_32", displayName: "PREDIVCLK = INTOSC1 / 32" },
	{ name: "SYSCTL_WD_PREDIV_64", displayName: "PREDIVCLK = INTOSC1 / 64" },
	{ name: "SYSCTL_WD_PREDIV_128", displayName: "PREDIVCLK = INTOSC1 / 128" },
	{ name: "SYSCTL_WD_PREDIV_256", displayName: "PREDIVCLK = INTOSC1 / 256" },
	{ name: "SYSCTL_WD_PREDIV_512", displayName: "PREDIVCLK = INTOSC1 / 512" },
	{ name: "SYSCTL_WD_PREDIV_1024", displayName: "PREDIVCLK = INTOSC1 / 1024" },
	{ name: "SYSCTL_WD_PREDIV_2048", displayName: "PREDIVCLK = INTOSC1 / 2048" },
	{ name: "SYSCTL_WD_PREDIV_4096", displayName: "PREDIVCLK = INTOSC1 / 4096" },
]
let SysCtl_WDPrescaler = [
	{ name: "SYSCTL_WD_PRESCALE_1", displayName: "WDCLK = PREDIVCLK / 1" },
	{ name: "SYSCTL_WD_PRESCALE_2", displayName: "WDCLK = PREDIVCLK / 2" },
	{ name: "SYSCTL_WD_PRESCALE_4", displayName: "WDCLK = PREDIVCLK / 4" },
	{ name: "SYSCTL_WD_PRESCALE_8", displayName: "WDCLK = PREDIVCLK / 8" },
	{ name: "SYSCTL_WD_PRESCALE_16", displayName: "WDCLK = PREDIVCLK / 16" },
	{ name: "SYSCTL_WD_PRESCALE_32", displayName: "WDCLK = PREDIVCLK / 32" },
	{ name: "SYSCTL_WD_PRESCALE_64", displayName: "WDCLK = PREDIVCLK / 64" },
]
let SYSCTL_WD = [
	{ name: "SYSCTL_WD_CHKBITS", displayName: "WD CHKBITS" },
	{ name: "SYSCTL_WD_ENRSTKEY", displayName: "WD ENRSTKEY" },
	{ name: "SYSCTL_WD_RSTKEY", displayName: "WD RSTKEY" },
]
module.exports = {
	SysCtl_WDMode: SysCtl_WDMode,
	SysCtl_WDPredivider: SysCtl_WDPredivider,
	SysCtl_WDPrescaler: SysCtl_WDPrescaler,
	SYSCTL_WD: SYSCTL_WD,
}
