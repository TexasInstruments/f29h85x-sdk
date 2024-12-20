let DeviceMemoryMap = [
	{ name: "PIPE_BASE", displayName: "PIPE", baseAddress: "0x30020000U" },
	{ name: "DCC1_BASE", displayName: "DCC1", baseAddress: "0x60080000U" },
	{ name: "DCC2_BASE", displayName: "DCC2", baseAddress: "0x60081000U" },
	{ name: "DCC3_BASE", displayName: "DCC3", baseAddress: "0x60082000U" },
	{ name: "RTDMA1_BASE", displayName: "RTDMA1", baseAddress: "0x301C0000U" },
	{ name: "RTDMA2_BASE", displayName: "RTDMA2", baseAddress: "0x301C8000U" },
	{ name: "RTDMA1CH1_BASE", displayName: "RTDMA1 CH1", baseAddress: "0x30400000U" },
	{ name: "RTDMA1CH2_BASE", displayName: "RTDMA1 CH2", baseAddress: "0x30401000U" },
	{ name: "RTDMA1CH3_BASE", displayName: "RTDMA1 CH3", baseAddress: "0x30402000U" },
	{ name: "RTDMA1CH4_BASE", displayName: "RTDMA1 CH4", baseAddress: "0x30403000U" },
	{ name: "RTDMA1CH5_BASE", displayName: "RTDMA1 CH5", baseAddress: "0x30404000U" },
	{ name: "RTDMA1CH6_BASE", displayName: "RTDMA1 CH6", baseAddress: "0x30405000U" },
	{ name: "RTDMA1CH7_BASE", displayName: "RTDMA1 CH7", baseAddress: "0x30406000U" },
	{ name: "RTDMA1CH8_BASE", displayName: "RTDMA1 CH8", baseAddress: "0x30407000U" },
	{ name: "RTDMA1CH9_BASE", displayName: "RTDMA1 CH9", baseAddress: "0x30408000U" },
	{ name: "RTDMA1CH10_BASE", displayName: "RTDMA1 CH10", baseAddress: "0x30409000U" },
	{ name: "RTDMA2CH1_BASE", displayName: "RTDMA2 CH1", baseAddress: "0x30410000U" },
	{ name: "RTDMA2CH2_BASE", displayName: "RTDMA2 CH2", baseAddress: "0x30411000U" },
	{ name: "RTDMA2CH3_BASE", displayName: "RTDMA2 CH3", baseAddress: "0x30412000U" },
	{ name: "RTDMA2CH4_BASE", displayName: "RTDMA2 CH4", baseAddress: "0x30413000U" },
	{ name: "RTDMA2CH5_BASE", displayName: "RTDMA2 CH5", baseAddress: "0x30414000U" },
	{ name: "RTDMA2CH6_BASE", displayName: "RTDMA2 CH6", baseAddress: "0x30415000U" },
	{ name: "RTDMA2CH7_BASE", displayName: "RTDMA2 CH7", baseAddress: "0x30416000U" },
	{ name: "RTDMA2CH8_BASE", displayName: "RTDMA2 CH8", baseAddress: "0x30417000U" },
	{ name: "RTDMA2CH9_BASE", displayName: "RTDMA2 CH9", baseAddress: "0x30418000U" },
	{ name: "RTDMA2CH10_BASE", displayName: "RTDMA2 CH10", baseAddress: "0x30419000U" },
	{ name: "RTDMA1_MPU_BASE", displayName: "RTDMA1 MPU", baseAddress: "0x301C1000U" },
	{ name: "RTDMA2_MPU_BASE", displayName: "RTDMA2 MPU", baseAddress: "0x301C9000U" },
	{ name: "RTDMA1_DIAG_BASE", displayName: "RTDMA1 DIAG", baseAddress: "0x301C0800U" },
	{ name: "RTDMA2_DIAG_BASE", displayName: "RTDMA2 DIAG", baseAddress: "0x301C8800U" },
	{ name: "RTDMA1_SELFTEST_BASE", displayName: "RTDMA1 SELFTEST", baseAddress: "0x301C0C00U" },
	{ name: "RTDMA2_SELFTEST_BASE", displayName: "RTDMA2 SELFTEST", baseAddress: "0x301C8C00U" },
	{ name: "FRI1_BASE", displayName: "FRI1", baseAddress: "0x301D0000" },
];
let PIPEMemoryMap = [
	{ name: "PIPE_BASE", displayName: "PIPE", baseAddress: "0x30020000U" },
];
let DCCMemoryMap = [
	{ name: "DCC1_BASE", displayName: "DCC1", baseAddress: "0x60080000U" },
	{ name: "DCC2_BASE", displayName: "DCC2", baseAddress: "0x60081000U" },
	{ name: "DCC3_BASE", displayName: "DCC3", baseAddress: "0x60082000U" },
];
let DMAMemoryMap = [
	{ name: "RTDMA1_BASE", displayName: "RTDMA1", baseAddress: "0x301C0000U" },
	{ name: "RTDMA2_BASE", displayName: "RTDMA2", baseAddress: "0x301C8000U" },
];
let DMAChMemoryMap = [
	{ name: "RTDMA1CH1_BASE", displayName: "RTDMA1 CH1", baseAddress: "0x30400000U" },
	{ name: "RTDMA1CH2_BASE", displayName: "RTDMA1 CH2", baseAddress: "0x30401000U" },
	{ name: "RTDMA1CH3_BASE", displayName: "RTDMA1 CH3", baseAddress: "0x30402000U" },
	{ name: "RTDMA1CH4_BASE", displayName: "RTDMA1 CH4", baseAddress: "0x30403000U" },
	{ name: "RTDMA1CH5_BASE", displayName: "RTDMA1 CH5", baseAddress: "0x30404000U" },
	{ name: "RTDMA1CH6_BASE", displayName: "RTDMA1 CH6", baseAddress: "0x30405000U" },
	{ name: "RTDMA1CH7_BASE", displayName: "RTDMA1 CH7", baseAddress: "0x30406000U" },
	{ name: "RTDMA1CH8_BASE", displayName: "RTDMA1 CH8", baseAddress: "0x30407000U" },
	{ name: "RTDMA1CH9_BASE", displayName: "RTDMA1 CH9", baseAddress: "0x30408000U" },
	{ name: "RTDMA1CH10_BASE", displayName: "RTDMA1 CH10", baseAddress: "0x30409000U" },
	{ name: "RTDMA2CH1_BASE", displayName: "RTDMA2 CH1", baseAddress: "0x30410000U" },
	{ name: "RTDMA2CH2_BASE", displayName: "RTDMA2 CH2", baseAddress: "0x30411000U" },
	{ name: "RTDMA2CH3_BASE", displayName: "RTDMA2 CH3", baseAddress: "0x30412000U" },
	{ name: "RTDMA2CH4_BASE", displayName: "RTDMA2 CH4", baseAddress: "0x30413000U" },
	{ name: "RTDMA2CH5_BASE", displayName: "RTDMA2 CH5", baseAddress: "0x30414000U" },
	{ name: "RTDMA2CH6_BASE", displayName: "RTDMA2 CH6", baseAddress: "0x30415000U" },
	{ name: "RTDMA2CH7_BASE", displayName: "RTDMA2 CH7", baseAddress: "0x30416000U" },
	{ name: "RTDMA2CH8_BASE", displayName: "RTDMA2 CH8", baseAddress: "0x30417000U" },
	{ name: "RTDMA2CH9_BASE", displayName: "RTDMA2 CH9", baseAddress: "0x30418000U" },
	{ name: "RTDMA2CH10_BASE", displayName: "RTDMA2 CH10", baseAddress: "0x30419000U" },
];
let DMAMPUMemoryMap = [
	{ name: "RTDMA1_MPU_BASE", displayName: "RTDMA1 MPU", baseAddress: "0x301C1000U" },
	{ name: "RTDMA2_MPU_BASE", displayName: "RTDMA2 MPU", baseAddress: "0x301C9000U" },
];
let DMADiagMemoryMap = [
	{ name: "RTDMA1_DIAG_BASE", displayName: "RTDMA1 DIAG", baseAddress: "0x301C0800U" },
	{ name: "RTDMA2_DIAG_BASE", displayName: "RTDMA2 DIAG", baseAddress: "0x301C8800U" },
];
let DMASelftestMemoryMap = [
	{ name: "RTDMA1_SELFTEST_BASE", displayName: "RTDMA1 SELFTEST", baseAddress: "0x301C0C00U" },
	{ name: "RTDMA2_SELFTEST_BASE", displayName: "RTDMA2 SELFTEST", baseAddress: "0x301C8C00U" },
];
let ADCSAFETYCHKMemoryMap = [
	{ name: "ADCSAFETYCHECK1_BASE", displayName: "ADCSAFETYCHECK1", baseAddress: "0x700B0000U" },
	{ name: "ADCSAFETYCHECK2_BASE", displayName: "ADCSAFETYCHECK2", baseAddress: "0x700B1000U" },
	{ name: "ADCSAFETYCHECK3_BASE", displayName: "ADCSAFETYCHECK3", baseAddress: "0x700B2000U" },
	{ name: "ADCSAFETYCHECK4_BASE", displayName: "ADCSAFETYCHECK4", baseAddress: "0x700B3000U" },
	{ name: "ADCSAFETYCHECK5_BASE", displayName: "ADCSAFETYCHECK5", baseAddress: "0x700B4000U" },
	{ name: "ADCSAFETYCHECK6_BASE", displayName: "ADCSAFETYCHECK6", baseAddress: "0x700B5000U" },
	{ name: "ADCSAFETYCHECK7_BASE", displayName: "ADCSAFETYCHECK7", baseAddress: "0x700B6000U" },
	{ name: "ADCSAFETYCHECK8_BASE", displayName: "ADCSAFETYCHECK8", baseAddress: "0x700B7000U" },
	{ name: "ADCSAFETYCHECK9_BASE", displayName: "ADCSAFETYCHECK9", baseAddress: "0x700B8000U" },
	{ name: "ADCSAFETYCHECK10_BASE",displayName: "ADCSAFETYCHECK10",baseAddress: "0x700B9000U" },

];
let ADCSAFETYINTEVTAGGMemoryMap = [
	{ name: "ADCSAFETYCHECKINTEVT1_BASE", displayName: "ADCSAFETYCHECKINTEVT1", baseAddress: "0x700C0000U"},
	{ name: "ADCSAFETYCHECKINTEVT2_BASE", displayName: "ADCSAFETYCHECKINTEVT2", baseAddress: "0x700C1000U"},
	{ name: "ADCSAFETYCHECKINTEVT3_BASE", displayName: "ADCSAFETYCHECKINTEVT3", baseAddress: "0x700C2000U"},
];
let CMPSSMemoryMap = [
	{ name: "CMPSS1_BASE", displayName: "CMPSS1", baseAddress: "0x700E0000U" },
	{ name: "CMPSS2_BASE", displayName: "CMPSS2", baseAddress: "0x700E1000U" },
	{ name: "CMPSS3_BASE", displayName: "CMPSS3", baseAddress: "0x700E2000U" },
	{ name: "CMPSS4_BASE", displayName: "CMPSS4", baseAddress: "0x700E3000U" },
	{ name: "CMPSS5_BASE", displayName: "CMPSS5", baseAddress: "0x700E4000U" },
	{ name: "CMPSS6_BASE", displayName: "CMPSS6", baseAddress: "0x700E5000U" },
	{ name: "CMPSS7_BASE", displayName: "CMPSS7", baseAddress: "0x700E6000U" },
	{ name: "CMPSS8_BASE", displayName: "CMPSS8", baseAddress: "0x700E7000U" },
	{ name: "CMPSS9_BASE", displayName: "CMPSS9", baseAddress: "0x700E8000U" },
	{ name: "CMPSS10_BASE", displayName: "CMPSS10", baseAddress: "0x700E9000U" },
	{ name: "CMPSS11_BASE", displayName: "CMPSS11", baseAddress: "0x700EA000U" },
	{ name: "CMPSS12_BASE", displayName: "CMPSS12", baseAddress: "0x700EB000U" },
];

let FLASH0MemoryMap = [
	{ name: "FRI1_BASE", displayName: "C29 FRI", baseAddress: "0x301D0000" },
];


module.exports = {
	PIPEMemoryMap: PIPEMemoryMap,
	DCCMemoryMap: DCCMemoryMap,
	DMAMemoryMap: DMAMemoryMap,
	DMAChMemoryMap: DMAChMemoryMap,
	DMAMPUMemoryMap: DMAMPUMemoryMap,
	DMADiagMemoryMap: DMADiagMemoryMap,
	DMASelftestMemoryMap: DMASelftestMemoryMap,
	DeviceMemoryMap: DeviceMemoryMap,
	ADCSAFETYCHKMemoryMap: ADCSAFETYCHKMemoryMap,
	ADCSAFETYINTEVTAGGMemoryMap: ADCSAFETYINTEVTAGGMemoryMap,
	CMPSSMemoryMap: CMPSSMemoryMap,
	FLASH0MemoryMap: FLASH0MemoryMap,
}
