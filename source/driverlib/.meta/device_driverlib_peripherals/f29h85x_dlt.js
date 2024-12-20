let DLT_EventSelect = [
	{ name: "DLT_EVENT_CPUx_ERAD_EBC_EVT1", displayName: "CPUx ERAD EBC EVT1" },
	{ name: "DLT_EVENT_CPUx_ERAD_EBC_EVT2", displayName: "CPUx ERAD EBC EVT2" },
	{ name: "DLT_EVENT_CPUx_ERAD_EBC_EVT3", displayName: "CPUx ERAD EBC EVT3" },
	{ name: "DLT_EVENT_CPUx_ERAD_EBC_EVT4", displayName: "CPUx ERAD EBC EVT4" },
	{ name: "DLT_EVENT_CPUx_ERAD_EBC_EVT5", displayName: "CPUx ERAD EBC EVT5" },
	{ name: "DLT_EVENT_CPUx_ERAD_EBC_EVT6", displayName: "CPUx ERAD EBC EVT6" },
	{ name: "DLT_EVENT_CPUx_ERAD_EBC_EVT7", displayName: "CPUx ERAD EBC EVT7" },
	{ name: "DLT_EVENT_CPUx_ERAD_EBC_EVT8", displayName: "CPUx ERAD EBC EVT8" },
	{ name: "DLT_EVENT_CPUx_ERAD_SEC_EVT1", displayName: "CPUx ERAD SEC EVT1" },
	{ name: "DLT_EVENT_CPUx_ERAD_SEC_EVT2", displayName: "CPUx ERAD SEC EVT2" },
	{ name: "DLT_EVENT_CPUx_ERAD_SEC_EVT3", displayName: "CPUx ERAD SEC EVT3" },
	{ name: "DLT_EVENT_CPUx_ERAD_SEC_EVT4", displayName: "CPUx ERAD SEC EVT4" },
	{ name: "DLT_EVENT_CPUx_ERAD_AND_MASK1", displayName: "CPUx ERAD AND MASK1" },
	{ name: "DLT_EVENT_CPUx_ERAD_AND_MASK2", displayName: "CPUx ERAD AND MASK2" },
	{ name: "DLT_EVENT_CPUx_ERAD_AND_MASK3", displayName: "CPUx ERAD AND MASK3" },
	{ name: "DLT_EVENT_CPUx_ERAD_AND_MASK4", displayName: "CPUx ERAD AND MASK4" },
	{ name: "DLT_EVENT_CPUx_ERAD_OR_MASK1", displayName: "CPUx ERAD OR MASK1" },
	{ name: "DLT_EVENT_CPUx_ERAD_OR_MASK2", displayName: "CPUx ERAD OR MASK2" },
	{ name: "DLT_EVENT_CPUx_ERAD_OR_MASK3", displayName: "CPUx ERAD OR MASK3" },
	{ name: "DLT_EVENT_CPUx_ERAD_OR_MASK4", displayName: "CPUx ERAD OR MASK4" },
]
let DLT_CaptureMode = [
	{ name: "DLT_CAPTURE_TIME", displayName: "With each entry, TIME is captured" },
	{ name: "DLT_CAPTURE_PC_SOURCE", displayName: "With each entry, PC Source is captured" },
]
let DLT_INT = [
	{ name: "DLT_INT_INT", displayName: "Global Interrupt" },
	{ name: "DLT_INT_TIMER1_OVF", displayName: "TIMER1 overflow" },
	{ name: "DLT_INT_TIMER2_OVF", displayName: "TIMER2 overflow" },
	{ name: "DLT_INT_FIFO_OVF", displayName: "FIFO overflow" },
	{ name: "DLT_INT_FIFO_UF", displayName: "FIFO underflow" },
	{ name: "DLT_INT_FIFO_TRIG", displayName: "FIFO reached Trigger level" },
]
module.exports = {
	DLT_EventSelect: DLT_EventSelect,
	DLT_CaptureMode: DLT_CaptureMode,
	DLT_INT: DLT_INT,
}
