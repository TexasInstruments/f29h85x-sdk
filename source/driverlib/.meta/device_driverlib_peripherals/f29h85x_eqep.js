let EQEP_PositionResetMode = [
	{ name: "EQEP_POSITION_RESET_IDX", displayName: "Reset position on index pulse" },
	{ name: "EQEP_POSITION_RESET_MAX_POS", displayName: "Reset position on maximum position" },
	{ name: "EQEP_POSITION_RESET_1ST_IDX", displayName: "Reset position on the first index pulse" },
	{ name: "EQEP_POSITION_RESET_UNIT_TIME_OUT", displayName: "Reset position on a unit time event" },
]
let EQEP_CAPCLKPrescale = [
	{ name: "EQEP_CAPTURE_CLK_DIV_1", displayName: "CAPCLK = SYSCLKOUT/1" },
	{ name: "EQEP_CAPTURE_CLK_DIV_2", displayName: "CAPCLK = SYSCLKOUT/2" },
	{ name: "EQEP_CAPTURE_CLK_DIV_4", displayName: "CAPCLK = SYSCLKOUT/4" },
	{ name: "EQEP_CAPTURE_CLK_DIV_8", displayName: "CAPCLK = SYSCLKOUT/8" },
	{ name: "EQEP_CAPTURE_CLK_DIV_16", displayName: "CAPCLK = SYSCLKOUT/16" },
	{ name: "EQEP_CAPTURE_CLK_DIV_32", displayName: "CAPCLK = SYSCLKOUT/32" },
	{ name: "EQEP_CAPTURE_CLK_DIV_64", displayName: "CAPCLK = SYSCLKOUT/64" },
	{ name: "EQEP_CAPTURE_CLK_DIV_128", displayName: "CAPCLK = SYSCLKOUT/128" },
]
let EQEP_UPEVNTPrescale = [
	{ name: "EQEP_UNIT_POS_EVNT_DIV_1", displayName: "UPEVNT = QCLK/1" },
	{ name: "EQEP_UNIT_POS_EVNT_DIV_2", displayName: "UPEVNT = QCLK/2" },
	{ name: "EQEP_UNIT_POS_EVNT_DIV_4", displayName: "UPEVNT = QCLK/4" },
	{ name: "EQEP_UNIT_POS_EVNT_DIV_8", displayName: "UPEVNT = QCLK/8" },
	{ name: "EQEP_UNIT_POS_EVNT_DIV_16", displayName: "UPEVNT = QCLK/16" },
	{ name: "EQEP_UNIT_POS_EVNT_DIV_32", displayName: "UPEVNT = QCLK/32" },
	{ name: "EQEP_UNIT_POS_EVNT_DIV_64", displayName: "UPEVNT = QCLK/64" },
	{ name: "EQEP_UNIT_POS_EVNT_DIV_128", displayName: "UPEVNT = QCLK/128" },
	{ name: "EQEP_UNIT_POS_EVNT_DIV_256", displayName: "UPEVNT = QCLK/256" },
	{ name: "EQEP_UNIT_POS_EVNT_DIV_512", displayName: "UPEVNT = QCLK/512" },
	{ name: "EQEP_UNIT_POS_EVNT_DIV_1024", displayName: "UPEVNT = QCLK/1024" },
	{ name: "EQEP_UNIT_POS_EVNT_DIV_2048", displayName: "UPEVNT = QCLK/2048" },
]
let EQEP_StrobeSource = [
	{ name: "EQEP_STROBE_FROM_GPIO", displayName: "Strobe signal comes from GPIO" },
	{ name: "EQEP_STROBE_OR_ADCSOCA", displayName: "Strobe signal is OR'd with ADCSOCA" },
	{ name: "EQEP_STROBE_OR_ADCSOCB", displayName: "Strobe signal is OR'd with ADCSOCB" },
]
let EQEP_QMAMode = [
	{ name: "EQEP_QMA_MODE_BYPASS", displayName: "QMA module is bypassed" },
	{ name: "EQEP_QMA_MODE_1", displayName: "QMA mode-1 operation is selected" },
	{ name: "EQEP_QMA_MODE_2", displayName: "QMA mode-2 operation is selected" },
]
let EQEP_Source = [
	{ name: "EQEP_SOURCE_INPUTXBAR", displayName: "SOURCE INPUTXBAR" },
	{ name: "EQEP_SOURCE_CMPSS1", displayName: "signal comes from CMPSS1" },
	{ name: "EQEP_SOURCE_CMPSS2", displayName: "signal comes from CMPSS2" },
	{ name: "EQEP_SOURCE_CMPSS3", displayName: "signal comes from CMPSS3" },
	{ name: "EQEP_SOURCE_CMPSS4", displayName: "signal comes from CMPSS4" },
	{ name: "EQEP_SOURCE_CMPSS5", displayName: "signal comes from CMPSS5" },
	{ name: "EQEP_SOURCE_CMPSS6", displayName: "signal comes from CMPSS6" },
	{ name: "EQEP_SOURCE_CMPSS7", displayName: "signal comes from CMPSS7" },
	{ name: "EQEP_SOURCE_CMPSS8", displayName: "signal comes from CMPSS8" },
	{ name: "EQEP_SOURCE_PWMXBAR1", displayName: "signal comes from PWMXBAR1" },
	{ name: "EQEP_SOURCE_PWMXBAR2", displayName: "signal comes from PWMXBAR2" },
	{ name: "EQEP_SOURCE_PWMXBAR3", displayName: "signal comes from PWMXBAR3" },
	{ name: "EQEP_SOURCE_PWMXBAR4", displayName: "signal comes from PWMXBAR4" },
	{ name: "EQEP_SOURCE_PWMXBAR5", displayName: "signal comes from PWMXBAR5" },
	{ name: "EQEP_SOURCE_PWMXBAR6", displayName: "signal comes from PWMXBAR6" },
	{ name: "EQEP_SOURCE_PWMXBAR7", displayName: "signal comes from PWMXBAR7" },
]
let EQEP_EmulationMode = [
	{ name: "EQEP_EMULATIONMODE_STOPIMMEDIATELY", displayName: "Counters stop immediately" },
	{ name: "EQEP_EMULATIONMODE_STOPATROLLOVER", displayName: "Counters stop at period rollover" },
	{ name: "EQEP_EMULATIONMODE_RUNFREE", displayName: "Counter unaffected by suspend" },
]
let EQEP_CONFIG = [
	{ name: "EQEP_CONFIG_QUADRATURE", displayName: "Quadrature-clock mode" },
	{ name: "EQEP_CONFIG_CLOCK_DIR", displayName: "Direction-count mode" },
	{ name: "EQEP_CONFIG_UP_COUNT", displayName: "Up-count mode, QDIR = 1" },
	{ name: "EQEP_CONFIG_DOWN_COUNT", displayName: "Down-count mode, QDIR = 0" },
	{ name: "EQEP_CONFIG_2X_RESOLUTION", displayName: "Count rising and falling edge" },
	{ name: "EQEP_CONFIG_1X_RESOLUTION", displayName: "Count rising edge only" },
	{ name: "EQEP_CONFIG_NO_SWAP", displayName: "Do not swap QEPA and QEPB" },
	{ name: "EQEP_CONFIG_SWAP", displayName: "Swap QEPA and QEPB" },
	{ name: "EQEP_CONFIG_IGATE_DISABLE", displayName: "Disable gating of Index pulse" },
	{ name: "EQEP_CONFIG_IGATE_ENABLE", displayName: "Gate the index pin with strobe" },
]
let EQEP_COMPARE = [
	{ name: "EQEP_COMPARE_NO_SYNC_OUT", displayName: "Disable sync output" },
	{ name: "EQEP_COMPARE_IDX_SYNC_OUT", displayName: "Sync output on index pin" },
	{ name: "EQEP_COMPARE_STROBE_SYNC_OUT", displayName: "Sync output on strobe pin" },
	{ name: "EQEP_COMPARE_NO_SHADOW", displayName: "Disable shadow of QPOSCMP" },
	{ name: "EQEP_COMPARE_LOAD_ON_ZERO", displayName: "Load on QPOSCNT = 0" },
	{ name: "EQEP_COMPARE_LOAD_ON_MATCH", displayName: "Load on QPOSCNT = QPOSCMP" },
]
let EQEP_INT = [
	{ name: "EQEP_INT_GLOBAL", displayName: "Global interrupt flag" },
	{ name: "EQEP_INT_POS_CNT_ERROR", displayName: "Position counter error" },
	{ name: "EQEP_INT_PHASE_ERROR", displayName: "Quadrature phase error" },
	{ name: "EQEP_INT_DIR_CHANGE", displayName: "Quadrature direction change" },
	{ name: "EQEP_INT_WATCHDOG", displayName: "Watchdog time-out" },
	{ name: "EQEP_INT_UNDERFLOW", displayName: "Position counter underflow" },
	{ name: "EQEP_INT_OVERFLOW", displayName: "Position counter overflow" },
	{ name: "EQEP_INT_POS_COMP_READY", displayName: "Position-compare ready" },
	{ name: "EQEP_INT_POS_COMP_MATCH", displayName: "Position-compare match" },
	{ name: "EQEP_INT_STROBE_EVNT_LATCH", displayName: "Strobe event latch" },
	{ name: "EQEP_INT_INDEX_EVNT_LATCH", displayName: "Index event latch" },
	{ name: "EQEP_INT_UNIT_TIME_OUT", displayName: "Unit time-out" },
	{ name: "EQEP_INT_QMA_ERROR", displayName: "QMA error" },
]
let EQEP_STS = [
	{ name: "EQEP_STS_UNIT_POS_EVNT", displayName: "Unit position event detected" },
	{ name: "EQEP_STS_DIR_ON_1ST_IDX", displayName: "Direction was clockwise on first index event" },
	{ name: "EQEP_STS_DIR_FLAG", displayName: "Direction is CW (forward)" },
	{ name: "EQEP_STS_DIR_LATCH", displayName: "Direction was CW on index" },
	{ name: "EQEP_STS_CAP_OVRFLW_ERROR", displayName: "Capture timer overflow" },
	{ name: "EQEP_STS_CAP_DIR_ERROR", displayName: "Direction changed between position capture events" },
	{ name: "EQEP_STS_1ST_IDX_FLAG", displayName: "First index pulse occurred" },
	{ name: "EQEP_STS_POS_CNT_ERROR", displayName: "Position counter error" },
]
let EQEP_LATCH = [
	{ name: "EQEP_LATCH_CNT_READ_BY_CPU", displayName: "On position counter read" },
	{ name: "EQEP_LATCH_UNIT_TIME_OUT", displayName: "On unit time-out event" },
	{ name: "EQEP_LATCH_RISING_STROBE", displayName: "On rising edge of strobe" },
	{ name: "EQEP_LATCH_EDGE_DIR_STROBE", displayName: "On rising edge when clockwise, on falling when counter clockwise" },
	{ name: "EQEP_LATCH_RISING_INDEX", displayName: "On rising edge of index" },
	{ name: "EQEP_LATCH_FALLING_INDEX", displayName: "On falling edge of index" },
	{ name: "EQEP_LATCH_SW_INDEX_MARKER", displayName: "On software index marker" },
]
let EQEP_INIT = [
	{ name: "EQEP_INIT_DO_NOTHING", displayName: "Action is disabled" },
	{ name: "EQEP_INIT_RISING_STROBE", displayName: "On rising edge of strobe" },
	{ name: "EQEP_INIT_EDGE_DIR_STROBE", displayName: "On rising edge when clockwise, on falling when counter clockwise" },
	{ name: "EQEP_INIT_RISING_INDEX", displayName: "On rising edge of index" },
	{ name: "EQEP_INIT_FALLING_INDEX", displayName: "On falling edge of index" },
]
module.exports = {
	EQEP_PositionResetMode: EQEP_PositionResetMode,
	EQEP_CAPCLKPrescale: EQEP_CAPCLKPrescale,
	EQEP_UPEVNTPrescale: EQEP_UPEVNTPrescale,
	EQEP_StrobeSource: EQEP_StrobeSource,
	EQEP_QMAMode: EQEP_QMAMode,
	EQEP_Source: EQEP_Source,
	EQEP_EmulationMode: EQEP_EmulationMode,
	EQEP_CONFIG: EQEP_CONFIG,
	EQEP_COMPARE: EQEP_COMPARE,
	EQEP_INT: EQEP_INT,
	EQEP_STS: EQEP_STS,
	EQEP_LATCH: EQEP_LATCH,
	EQEP_INIT: EQEP_INIT,
}
