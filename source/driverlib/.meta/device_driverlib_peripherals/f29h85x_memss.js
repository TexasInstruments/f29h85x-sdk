let Memss_RAM = [
	{ name: "MEMSS_RAM_LPA0", displayName: "RAM LPA0" },
	{ name: "MEMSS_RAM_LPA1", displayName: "RAM LPA1" },
	{ name: "MEMSS_RAM_LDA0", displayName: "RAM LDA0" },
	{ name: "MEMSS_RAM_LDA1", displayName: "RAM LDA1" },
	{ name: "MEMSS_RAM_LDA2", displayName: "RAM LDA2" },
	{ name: "MEMSS_RAM_LDA3", displayName: "RAM LDA3" },
	{ name: "MEMSS_RAM_LDA4", displayName: "RAM LDA4" },
	{ name: "MEMSS_RAM_LDA5", displayName: "RAM LDA5" },
	{ name: "MEMSS_RAM_LDA6", displayName: "RAM LDA6" },
	{ name: "MEMSS_RAM_LDA7", displayName: "RAM LDA7" },
	{ name: "MEMSS_RAM_CPA0", displayName: "RAM CPA0" },
	{ name: "MEMSS_RAM_CPA1", displayName: "RAM CPA1" },
	{ name: "MEMSS_RAM_CDA0", displayName: "RAM CDA0" },
	{ name: "MEMSS_RAM_CDA1", displayName: "RAM CDA1" },
	{ name: "MEMSS_RAM_CDA2", displayName: "RAM CDA2" },
	{ name: "MEMSS_RAM_CDA3", displayName: "RAM CDA3" },
	{ name: "MEMSS_RAM_CDA4", displayName: "RAM CDA4" },
	{ name: "MEMSS_RAM_CDA5", displayName: "RAM CDA5" },
	{ name: "MEMSS_RAM_CDA6", displayName: "RAM CDA6" },
	{ name: "MEMSS_RAM_CDA7", displayName: "RAM CDA7" },
	{ name: "MEMSS_RAM_CDA8", displayName: "RAM CDA8" },
	{ name: "MEMSS_RAM_CDA9", displayName: "RAM CDA9" },
	{ name: "MEMSS_RAM_CDA10", displayName: "RAM CDA10" },
	{ name: "MEMSS_RAM_CDA11", displayName: "RAM CDA11" },
	{ name: "MEMSS_RAM_M0", displayName: "RAM M0" },
]
let Memss_RAMTestMode = [
	{ name: "MEMSS_RAM_TEST_NORMAL", displayName: "Normal mode of operation" },
	{ name: "MEMSS_RAM_TEST_WRITE_DATA", displayName: "Write to ECC bits is disabled. ECC check on Read Data is disabled." },
	{ name: "MEMSS_RAM_TEST_WRITE_ECC", displayName: "Write to Data bits is disabled. ECC check on Read Data is disabled. Read Returns ECC bits" },
]
let Memss_ROM = [
	{ name: "MEMSS_ROM_CPU1", displayName: "ROM CPU1" },
	{ name: "MEMSS_ROM_CPU2", displayName: "ROM CPU2" },
	{ name: "MEMSS_ROM_CPU3", displayName: "ROM CPU3" },
]
let Memss_ROMTestMode = [
	{ name: "MEMSS_ROM_TEST_NORMAL", displayName: "Normal mode of operation" },
	{ name: "MEMSS_ROM_TEST_ECC_DISABLED", displayName: "ECC check on Read Data is disabled." },
	{ name: "MEMSS_ROM_TEST_READ_ECC", displayName: "ECC check on Read Data is disabled. Read Returns ECC bits." },
]
module.exports = {
	Memss_RAM: Memss_RAM,
	Memss_RAMTestMode: Memss_RAMTestMode,
	Memss_ROM: Memss_ROM,
	Memss_ROMTestMode: Memss_ROMTestMode,
}
