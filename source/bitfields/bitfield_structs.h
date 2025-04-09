//###########################################################################
//
// FILE:    bitfield_structs.h
//
// TITLE:  Peripheral Bitfield struct extern defintions.
//
//###########################################################################
// //
//	Copyright: Copyright (C) Texas Instruments Incorporated
//	All rights reserved not granted herein.
//
//  Redistribution and use in source and binary forms, with or without 
//  modification, are permitted provided that the following conditions 
//  are met:
//
//  Redistributions of source code must retain the above copyright 
//  notice, this list of conditions and the following disclaimer.
//
//  Redistributions in binary form must reproduce the above copyright
//  notice, this list of conditions and the following disclaimer in the 
//  documentation and/or other materials provided with the   
//  distribution.
//
//  Neither the name of Texas Instruments Incorporated nor the names of
//  its contributors may be used to endorse or promote products derived
//  from this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
//  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
//  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
//  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
//  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

//###########################################################################

#undef IDLE

//
// Include peripheral header files and memorymap
//
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "hwbf_adc.h"
#include "hwbf_aes.h"
#include "hwbf_asysctl.h"
#include "hwbf_clb.h"
#include "hwbf_clb_xbar.h"
#include "hwbf_cmpss.h"
#include "hwbf_cpu.h"
#include "hwbf_cputimer.h"
#include "hwbf_dac.h"
#include "hwbf_dcc.h"
#include "hwbf_debugss.h"
#include "hwbf_debug_controller.h"
#include "hwbf_dlt.h"
#include "hwbf_ecap.h"
#include "hwbf_ecat_ss.h"
#include "hwbf_edc.h"
#include "hwbf_elt.h"
#include "hwbf_emif.h"
#include "hwbf_epg.h"
#include "hwbf_epwm.h"
#include "hwbf_epwm_xbar.h"
#include "hwbf_eqep.h"
#include "hwbf_erad.h"
#include "hwbf_error_aggregator.h"
#include "hwbf_esm_cpu.h"
#include "hwbf_esm_safety_aggregator.h"
#include "hwbf_esm_sys.h"
#include "hwbf_fri.h"
#include "hwbf_fsi.h"
#include "hwbf_gpio.h"
#include "hwbf_hrpwmcal.h"
#include "hwbf_i2c.h"
#include "hwbf_icl_xbar.h"
#include "hwbf_input_xbar.h"
#include "hwbf_ipc.h"
#include "hwbf_lcm.h"
#include "hwbf_lin.h"
#include "hwbf_lpost.h"
#include "hwbf_mdl_xbar.h"
#include "hwbf_memss.h"
#include "hwbf_output_xbar.h"
#include "hwbf_pbist.h"
#include "hwbf_pipe.h"
#include "hwbf_pmbus.h"
#include "hwbf_rtdma.h"
#include "hwbf_sdfm.h"
#include "hwbf_sent.h"
#include "hwbf_spi.h"
#include "hwbf_ssu.h"
#include "hwbf_syncbridgempu.h"
#include "hwbf_sysctl.h"
#include "hwbf_tmu.h"
#include "hwbf_uart.h"
#include "hwbf_vmt.h"
#include "hwbf_wadi.h"
#include "hwbf_xbar.h"
#include "hwbf_xint.h"
//
// Extern Global Peripheral Variables:
//

extern volatile struct ADC_GLOBAL_REGS AdcGlobalRegs;

extern volatile struct ADC_REGS AdcaRegs;

extern volatile struct ADC_REGS AdcbRegs;

extern volatile struct ADC_REGS AdccRegs;

extern volatile struct ADC_REGS AdcdRegs;

extern volatile struct ADC_REGS AdceRegs;

extern volatile struct ADC_RESULT_REGS AdcaResultRegs;

extern volatile struct ADC_RESULT_REGS AdcbResultRegs;

extern volatile struct ADC_RESULT_REGS AdccResultRegs;

extern volatile struct ADC_RESULT_REGS AdcdResultRegs;

extern volatile struct ADC_RESULT_REGS AdceResultRegs;

extern volatile struct ADC_SAFECHECK_INTEVT_REGS AdcSafetyCheckIntEvt1Regs;

extern volatile struct ADC_SAFECHECK_INTEVT_REGS AdcSafetyCheckIntEvt2Regs;

extern volatile struct ADC_SAFECHECK_INTEVT_REGS AdcSafetyCheckIntEvt3Regs;

extern volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck1Regs;

extern volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck2Regs;

extern volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck3Regs;

extern volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck4Regs;

extern volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck5Regs;

extern volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck6Regs;

extern volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck7Regs;

extern volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck8Regs;

extern volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck9Regs;

extern volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck10Regs;

extern volatile struct ANALOG_SUBSYS_REGS AnalogSubsysRegs;

extern volatile struct C29_DIAG_REGS C29cpuDiagRegs;

extern volatile struct C29_RTINT_STACK C29CpuRtintStackRegs;

extern volatile struct C29_SECCALL_STACK C29CpuSecCallStackRegs;

extern volatile struct C29_SECURE_REGS C29CpuSecureRegs;

extern volatile struct C29_SELFTEST_REGS C29cpuSelfTestRegs;

extern volatile struct CLB_DATA_EXCHANGE_REGS Clb1DataExchRegs;

extern volatile struct CLB_DATA_EXCHANGE_REGS Clb2DataExchRegs;

extern volatile struct CLB_DATA_EXCHANGE_REGS Clb3DataExchRegs;

extern volatile struct CLB_DATA_EXCHANGE_REGS Clb4DataExchRegs;

extern volatile struct CLB_DATA_EXCHANGE_REGS Clb5DataExchRegs;

extern volatile struct CLB_DATA_EXCHANGE_REGS Clb6DataExchRegs;

extern volatile struct CLB_LOGIC_CONFIG_REGS Clb1LogicCfgRegs;

extern volatile struct CLB_LOGIC_CONFIG_REGS Clb2LogicCfgRegs;

extern volatile struct CLB_LOGIC_CONFIG_REGS Clb3LogicCfgRegs;

extern volatile struct CLB_LOGIC_CONFIG_REGS Clb4LogicCfgRegs;

extern volatile struct CLB_LOGIC_CONFIG_REGS Clb5LogicCfgRegs;

extern volatile struct CLB_LOGIC_CONFIG_REGS Clb6LogicCfgRegs;

extern volatile struct CLB_LOGIC_CONTROL_REGS Clb1LogicCtrlRegs;

extern volatile struct CLB_LOGIC_CONTROL_REGS Clb2LogicCtrlRegs;

extern volatile struct CLB_LOGIC_CONTROL_REGS Clb3LogicCtrlRegs;

extern volatile struct CLB_LOGIC_CONTROL_REGS Clb4LogicCtrlRegs;

extern volatile struct CLB_LOGIC_CONTROL_REGS Clb5LogicCtrlRegs;

extern volatile struct CLB_LOGIC_CONTROL_REGS Clb6LogicCtrlRegs;

extern volatile struct CLB_XBAR_REGS ClbXbarRegs;

extern volatile struct CMPSS_REGS Cmpss1Regs;

extern volatile struct CMPSS_REGS Cmpss2Regs;

extern volatile struct CMPSS_REGS Cmpss3Regs;

extern volatile struct CMPSS_REGS Cmpss4Regs;

extern volatile struct CMPSS_REGS Cmpss5Regs;

extern volatile struct CMPSS_REGS Cmpss6Regs;

extern volatile struct CMPSS_REGS Cmpss7Regs;

extern volatile struct CMPSS_REGS Cmpss8Regs;

extern volatile struct CMPSS_REGS Cmpss9Regs;

extern volatile struct CMPSS_REGS Cmpss10Regs;

extern volatile struct CMPSS_REGS Cmpss11Regs;

extern volatile struct CMPSS_REGS Cmpss12Regs;

extern volatile struct CPU1_IPC_RCV_REGS Cpu1IpcrcvRegs;

extern volatile struct CPU1_IPC_SEND_REGS Cpu1IpcsendRegs;

extern volatile struct CPU2_IPC_RCV_REGS Cpu2IpcrcvRegs;

extern volatile struct CPU2_IPC_SEND_REGS Cpu2IpcsendRegs;

extern volatile struct CPU3_IPC_RCV_REGS Cpu3IpcrcvRegs;

extern volatile struct CPU3_IPC_SEND_REGS Cpu3IpcsendRegs;

extern volatile struct CPUTIMER_REGS CpuTimer0Regs;

extern volatile struct CPUTIMER_REGS CpuTimer1Regs;

extern volatile struct CPUTIMER_REGS CpuTimer2Regs;

extern volatile struct CPU_PER_CFG_REGS CpuPerCfgRegs;

extern volatile struct CPU_SYS_REGS CpuSysRegs;

extern volatile struct DAC_REGS DacaRegs;

extern volatile struct DAC_REGS DacbRegs;

extern volatile struct DCC_REGS Dcc1Regs;

extern volatile struct DCC_REGS Dcc2Regs;

extern volatile struct DCC_REGS Dcc3Regs;

extern volatile struct DEV_CFG_REGS DevCfgRegs;

extern volatile struct DE_REGS EPwm1DeRegs;

extern volatile struct DE_REGS EPwm2DeRegs;

extern volatile struct DE_REGS EPwm3DeRegs;

extern volatile struct DE_REGS EPwm4DeRegs;

extern volatile struct DE_REGS EPwm5DeRegs;

extern volatile struct DE_REGS EPwm6DeRegs;

extern volatile struct DE_REGS EPwm7DeRegs;

extern volatile struct DE_REGS EPwm8DeRegs;

extern volatile struct DE_REGS EPwm9DeRegs;

extern volatile struct DE_REGS EPwm10DeRegs;

extern volatile struct DE_REGS EPwm11DeRegs;

extern volatile struct DE_REGS EPwm12DeRegs;

extern volatile struct DE_REGS EPwm13DeRegs;

extern volatile struct DE_REGS EPwm14DeRegs;

extern volatile struct DE_REGS EPwm15DeRegs;

extern volatile struct DE_REGS EPwm16DeRegs;

extern volatile struct DE_REGS EPwm17DeRegs;

extern volatile struct DE_REGS EPwm18DeRegs;

extern volatile struct DE_REGS EPwm1DeXlinkRegs;

extern volatile struct DE_REGS EPwm2DeXlinkRegs;

extern volatile struct DE_REGS EPwm3DeXlinkRegs;

extern volatile struct DE_REGS EPwm4DeXlinkRegs;

extern volatile struct DE_REGS EPwm5DeXlinkRegs;

extern volatile struct DE_REGS EPwm6DeXlinkRegs;

extern volatile struct DE_REGS EPwm7DeXlinkRegs;

extern volatile struct DE_REGS EPwm8DeXlinkRegs;

extern volatile struct DE_REGS EPwm9DeXlinkRegs;

extern volatile struct DE_REGS EPwm10DeXlinkRegs;

extern volatile struct DE_REGS EPwm11DeXlinkRegs;

extern volatile struct DE_REGS EPwm12DeXlinkRegs;

extern volatile struct DE_REGS EPwm13DeXlinkRegs;

extern volatile struct DE_REGS EPwm14DeXlinkRegs;

extern volatile struct DE_REGS EPwm15DeXlinkRegs;

extern volatile struct DE_REGS EPwm16DeXlinkRegs;

extern volatile struct DE_REGS EPwm17DeXlinkRegs;

extern volatile struct DE_REGS EPwm18DeXlinkRegs;

extern volatile struct DLT_CORE_REGS cpuDltRegs;

extern volatile struct DLT_FIFO_REGS CPU1DLTFifoRegs;

extern volatile struct DLT_FIFO_REGS CPU2DLTFifoRegs;

extern volatile struct DLT_FIFO_REGS CPU3DLTFifoRegs;

extern volatile struct ECAP_REGS ECap1Regs;

extern volatile struct ECAP_REGS ECap2Regs;

extern volatile struct ECAP_REGS ECap3Regs;

extern volatile struct ECAP_REGS ECap4Regs;

extern volatile struct ECAP_REGS ECap5Regs;

extern volatile struct ECAP_REGS ECap6Regs;

extern volatile struct ECAP_SIGNAL_MONITORING ECap1SignalMonitoringRegs;

extern volatile struct ECAP_SIGNAL_MONITORING ECap2SignalMonitoringRegs;

extern volatile struct ECAP_SIGNAL_MONITORING ECap3SignalMonitoringRegs;

extern volatile struct ECAP_SIGNAL_MONITORING ECap4SignalMonitoringRegs;

extern volatile struct ECAP_SIGNAL_MONITORING ECap5SignalMonitoringRegs;

extern volatile struct ECAP_SIGNAL_MONITORING ECap6SignalMonitoringRegs;

extern volatile struct EMIF_REGS EMIF1Regs;

extern volatile struct EPG_MUX_REGS EPGMuxRegs;

extern volatile struct EPG_REGS EPGRegs;

extern volatile struct EPWM_REGS EPwm1Regs;

extern volatile struct EPWM_REGS EPwm2Regs;

extern volatile struct EPWM_REGS EPwm3Regs;

extern volatile struct EPWM_REGS EPwm4Regs;

extern volatile struct EPWM_REGS EPwm5Regs;

extern volatile struct EPWM_REGS EPwm6Regs;

extern volatile struct EPWM_REGS EPwm7Regs;

extern volatile struct EPWM_REGS EPwm8Regs;

extern volatile struct EPWM_REGS EPwm9Regs;

extern volatile struct EPWM_REGS EPwm10Regs;

extern volatile struct EPWM_REGS EPwm11Regs;

extern volatile struct EPWM_REGS EPwm12Regs;

extern volatile struct EPWM_REGS EPwm13Regs;

extern volatile struct EPWM_REGS EPwm14Regs;

extern volatile struct EPWM_REGS EPwm15Regs;

extern volatile struct EPWM_REGS EPwm16Regs;

extern volatile struct EPWM_REGS EPwm17Regs;

extern volatile struct EPWM_REGS EPwm18Regs;

extern volatile struct EPWM_REGS EPwm1XlinkRegs;

extern volatile struct EPWM_REGS EPwm2XlinkRegs;

extern volatile struct EPWM_REGS EPwm3XlinkRegs;

extern volatile struct EPWM_REGS EPwm4XlinkRegs;

extern volatile struct EPWM_REGS EPwm5XlinkRegs;

extern volatile struct EPWM_REGS EPwm6XlinkRegs;

extern volatile struct EPWM_REGS EPwm7XlinkRegs;

extern volatile struct EPWM_REGS EPwm8XlinkRegs;

extern volatile struct EPWM_REGS EPwm9XlinkRegs;

extern volatile struct EPWM_REGS EPwm10XlinkRegs;

extern volatile struct EPWM_REGS EPwm11XlinkRegs;

extern volatile struct EPWM_REGS EPwm12XlinkRegs;

extern volatile struct EPWM_REGS EPwm13XlinkRegs;

extern volatile struct EPWM_REGS EPwm14XlinkRegs;

extern volatile struct EPWM_REGS EPwm15XlinkRegs;

extern volatile struct EPWM_REGS EPwm16XlinkRegs;

extern volatile struct EPWM_REGS EPwm17XlinkRegs;

extern volatile struct EPWM_REGS EPwm18XlinkRegs;

extern volatile struct EPWM_XBAR_REGS EPwmXbarRegs;

extern volatile struct EPWM_XCMP_REGS EPwm1XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm2XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm3XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm4XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm5XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm6XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm7XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm8XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm9XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm10XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm11XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm12XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm13XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm14XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm15XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm16XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm17XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm18XcmpRegs;

extern volatile struct EPWM_XCMP_REGS EPwm1XcmpXlinkRegs;

extern volatile struct EPWM_XCMP_REGS EPwm2XcmpXlinkRegs;

extern volatile struct EPWM_XCMP_REGS EPwm3XcmpXlinkRegs;

extern volatile struct EPWM_XCMP_REGS EPwm4XcmpXlinkRegs;

extern volatile struct EPWM_XCMP_REGS EPwm5XcmpXlinkRegs;

extern volatile struct EPWM_XCMP_REGS EPwm6XcmpXlinkRegs;

extern volatile struct EPWM_XCMP_REGS EPwm7XcmpXlinkRegs;

extern volatile struct EPWM_XCMP_REGS EPwm8XcmpXlinkRegs;

extern volatile struct EPWM_XCMP_REGS EPwm9XcmpXlinkRegs;

extern volatile struct EPWM_XCMP_REGS EPwm10XcmpXlinkRegs;

extern volatile struct EPWM_XCMP_REGS EPwm11XcmpXlinkRegs;

extern volatile struct EPWM_XCMP_REGS EPwm12XcmpXlinkRegs;

extern volatile struct EPWM_XCMP_REGS EPwm13XcmpXlinkRegs;

extern volatile struct EPWM_XCMP_REGS EPwm14XcmpXlinkRegs;

extern volatile struct EPWM_XCMP_REGS EPwm15XcmpXlinkRegs;

extern volatile struct EPWM_XCMP_REGS EPwm16XcmpXlinkRegs;

extern volatile struct EPWM_XCMP_REGS EPwm17XcmpXlinkRegs;

extern volatile struct EPWM_XCMP_REGS EPwm18XcmpXlinkRegs;

extern volatile struct EQEP_REGS EQep1Regs;

extern volatile struct EQEP_REGS EQep2Regs;

extern volatile struct EQEP_REGS EQep3Regs;

extern volatile struct EQEP_REGS EQep4Regs;

extern volatile struct EQEP_REGS EQep5Regs;

extern volatile struct EQEP_REGS EQep6Regs;

extern volatile struct ERAD_REGS EradRegs;

extern volatile struct ERROR_AGGREGATOR_CONFIG_REGS ErrorAggregatorRegs;

extern volatile struct ESCSS_CONFIG_REGS EscssaConfigRegs;

extern volatile struct ESCSS_REGS EscssRegs;

extern volatile struct ESM_CPU_REGS EsmCpu1Regs;

extern volatile struct ESM_CPU_REGS EsmCpu2Regs;

extern volatile struct ESM_CPU_REGS EsmCpu3Regs;

extern volatile struct ESM_SAFETYAGG_REGS EsmSafetyAggRegs;

extern volatile struct ESM_SYSTEM_REGS EsmSystemRegs;

extern volatile struct FRI_CTRL_REGS Fri1Regs;

extern volatile struct FSI_RX_REGS FsiRxaRegs;

extern volatile struct FSI_RX_REGS FsiRxbRegs;

extern volatile struct FSI_RX_REGS FsiRxcRegs;

extern volatile struct FSI_RX_REGS FsiRxdRegs;

extern volatile struct FSI_TX_REGS FsiTxaRegs;

extern volatile struct FSI_TX_REGS FsiTxbRegs;

extern volatile struct FSI_TX_REGS FsiTxcRegs;

extern volatile struct FSI_TX_REGS FsiTxdRegs;

extern volatile struct GPIO_CTRL_REGS GpioCtrlRegs;

extern volatile struct GPIO_DATA_READ_REGS GpioDataReadRegs;

extern volatile struct GPIO_DATA_REGS GpioDataRegs;

extern volatile struct HRCAP_REGS HRCap5Regs;

extern volatile struct HRCAP_REGS HRCap6Regs;

extern volatile struct HRPWMCAL_REGS Hrpwmcal1Regs;

extern volatile struct HRPWMCAL_REGS Hrpwmcal2Regs;

extern volatile struct HRPWMCAL_REGS Hrpwmcal3Regs;

extern volatile struct HSM_ERROR_AGGREGATOR_CONFIG_REGS HSMErrorAggregatorRegs;

extern volatile struct I2C_REGS I2caRegs;

extern volatile struct I2C_REGS I2cbRegs;

extern volatile struct ICL_XBAR_REGS IclXbarRegs;

extern volatile struct INPUT_XBAR_REGS InputXbarRegs;

extern volatile struct IPC_COUNTER_REGS IpcCounterRegs;

extern volatile struct LCM_REGS LCMCPURegs;

extern volatile struct LCM_REGS LCMDMARegs;

extern volatile struct LIN_REGS LinaRegs;

extern volatile struct LIN_REGS LinbRegs;

extern volatile struct MDL_XBAR_REGS MdlXbarRegs;

extern volatile struct MEMSS_C_CONFIG_REGS MemssCCfgRegs;

extern volatile struct MEMSS_L_CONFIG_REGS MemssLCfgRegs;

extern volatile struct MEMSS_MISCI_REGS MemssMisciRegs;

extern volatile struct MEMSS_M_CONFIG_REGS MemssMCfgRegs;

extern volatile struct MINDB_LUT_REGS EPwm1MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm2MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm3MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm4MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm5MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm6MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm7MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm8MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm9MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm10MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm11MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm12MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm13MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm14MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm15MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm16MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm17MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm18MinDbLutRegs;

extern volatile struct MINDB_LUT_REGS EPwm1MinDbLutXlinkRegs;

extern volatile struct MINDB_LUT_REGS EPwm2MinDbLutXlinkRegs;

extern volatile struct MINDB_LUT_REGS EPwm3MinDbLutXlinkRegs;

extern volatile struct MINDB_LUT_REGS EPwm4MinDbLutXlinkRegs;

extern volatile struct MINDB_LUT_REGS EPwm5MinDbLutXlinkRegs;

extern volatile struct MINDB_LUT_REGS EPwm6MinDbLutXlinkRegs;

extern volatile struct MINDB_LUT_REGS EPwm7MinDbLutXlinkRegs;

extern volatile struct MINDB_LUT_REGS EPwm8MinDbLutXlinkRegs;

extern volatile struct MINDB_LUT_REGS EPwm9MinDbLutXlinkRegs;

extern volatile struct MINDB_LUT_REGS EPwm10MinDbLutXlinkRegs;

extern volatile struct MINDB_LUT_REGS EPwm11MinDbLutXlinkRegs;

extern volatile struct MINDB_LUT_REGS EPwm12MinDbLutXlinkRegs;

extern volatile struct MINDB_LUT_REGS EPwm13MinDbLutXlinkRegs;

extern volatile struct MINDB_LUT_REGS EPwm14MinDbLutXlinkRegs;

extern volatile struct MINDB_LUT_REGS EPwm15MinDbLutXlinkRegs;

extern volatile struct MINDB_LUT_REGS EPwm16MinDbLutXlinkRegs;

extern volatile struct MINDB_LUT_REGS EPwm17MinDbLutXlinkRegs;

extern volatile struct MINDB_LUT_REGS EPwm18MinDbLutXlinkRegs;

extern volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar1flagsRegs;

extern volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar2flagsRegs;

extern volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar3flagsRegs;

extern volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar4flagsRegs;

extern volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar5flagsRegs;

extern volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar6flagsRegs;

extern volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar7flagsRegs;

extern volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar8flagsRegs;

extern volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar9flagsRegs;

extern volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar10flagsRegs;

extern volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar11flagsRegs;

extern volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar12flagsRegs;

extern volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar13flagsRegs;

extern volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar14flagsRegs;

extern volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar15flagsRegs;

extern volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar16flagsRegs;

extern volatile struct OUTPUTXBAR_REGS OutputXbarRegs;

extern volatile struct PIPE_REGS PipeRegs;

extern volatile struct PMBUS_REGS PmbusaRegs;

extern volatile struct RTDMA_CH_REGS Rtdma1Ch1Regs;

extern volatile struct RTDMA_CH_REGS Rtdma1Ch2Regs;

extern volatile struct RTDMA_CH_REGS Rtdma1Ch3Regs;

extern volatile struct RTDMA_CH_REGS Rtdma1Ch4Regs;

extern volatile struct RTDMA_CH_REGS Rtdma1Ch5Regs;

extern volatile struct RTDMA_CH_REGS Rtdma1Ch6Regs;

extern volatile struct RTDMA_CH_REGS Rtdma1Ch7Regs;

extern volatile struct RTDMA_CH_REGS Rtdma1Ch8Regs;

extern volatile struct RTDMA_CH_REGS Rtdma1Ch9Regs;

extern volatile struct RTDMA_CH_REGS Rtdma1Ch10Regs;

extern volatile struct RTDMA_CH_REGS Rtdma2Ch1Regs;

extern volatile struct RTDMA_CH_REGS Rtdma2Ch2Regs;

extern volatile struct RTDMA_CH_REGS Rtdma2Ch3Regs;

extern volatile struct RTDMA_CH_REGS Rtdma2Ch4Regs;

extern volatile struct RTDMA_CH_REGS Rtdma2Ch5Regs;

extern volatile struct RTDMA_CH_REGS Rtdma2Ch6Regs;

extern volatile struct RTDMA_CH_REGS Rtdma2Ch7Regs;

extern volatile struct RTDMA_CH_REGS Rtdma2Ch8Regs;

extern volatile struct RTDMA_CH_REGS Rtdma2Ch9Regs;

extern volatile struct RTDMA_CH_REGS Rtdma2Ch10Regs;

extern volatile struct RTDMA_DIAG_REGS Rtdma1DiagRegs;

extern volatile struct RTDMA_DIAG_REGS Rtdma2DiagRegs;

extern volatile struct RTDMA_MPU_REGS Rtdma1MPURegs;

extern volatile struct RTDMA_MPU_REGS Rtdma2MPURegs;

extern volatile struct RTDMA_REGS Rtdma1Regs;

extern volatile struct RTDMA_REGS Rtdma2Regs;

extern volatile struct RTDMA_SELFTEST_REGS Rtdma1SelfTestRegs;

extern volatile struct RTDMA_SELFTEST_REGS Rtdma2SelfTestRegs;

extern volatile struct SDFM_REGS Sdfm1Regs;

extern volatile struct SDFM_REGS Sdfm2Regs;

extern volatile struct SDFM_REGS Sdfm3Regs;

extern volatile struct SDFM_REGS Sdfm4Regs;

extern volatile struct SECAP_HANDLER_REGS c29debugssRegs;

extern volatile struct SENT_CFG Sent1CsentRegs;

extern volatile struct SENT_CFG Sent2CsentRegs;

extern volatile struct SENT_CFG Sent3CsentRegs;

extern volatile struct SENT_CFG Sent4CsentRegs;

extern volatile struct SENT_CFG Sent5CsentRegs;

extern volatile struct SENT_CFG Sent6CsentRegs;

extern volatile struct SENT_MEM Sent1MemRegs;

extern volatile struct SENT_MEM Sent2MemRegs;

extern volatile struct SENT_MEM Sent3MemRegs;

extern volatile struct SENT_MEM Sent4MemRegs;

extern volatile struct SENT_MEM Sent5MemRegs;

extern volatile struct SENT_MEM Sent6MemRegs;

extern volatile struct SENT_MTPG Sent1MtpgRegs;

extern volatile struct SENT_MTPG Sent2MtpgRegs;

extern volatile struct SENT_MTPG Sent3MtpgRegs;

extern volatile struct SENT_MTPG Sent4MtpgRegs;

extern volatile struct SENT_MTPG Sent5MtpgRegs;

extern volatile struct SENT_MTPG Sent6MtpgRegs;

extern volatile struct SPI_REGS SpiaRegs;

extern volatile struct SPI_REGS SpibRegs;

extern volatile struct SPI_REGS SpicRegs;

extern volatile struct SPI_REGS SpidRegs;

extern volatile struct SPI_REGS SpieRegs;

extern volatile struct SSU_CPU1_AP_REGS SsuCpu1ApRegs;

extern volatile struct SSU_CPU1_CFG_REGS SsuCpu1CfgRegs;

extern volatile struct SSU_CPU2_AP_REGS SsuCpu2ApRegs;

extern volatile struct SSU_CPU2_CFG_REGS SsuCpu2CfgRegs;

extern volatile struct SSU_CPU3_AP_REGS SsuCpu3ApRegs;

extern volatile struct SSU_CPU3_CFG_REGS SsuCpu3CfgRegs;

extern volatile struct SSU_GEN_REGS SsuGenRegs;

extern volatile struct SYNCBRIDGEMPU_REGS SyncBridgeMpuRegs;

extern volatile struct UART_REGS UartaRegs;

extern volatile struct UART_REGS UartbRegs;

extern volatile struct UART_REGS UartcRegs;

extern volatile struct UART_REGS UartdRegs;

extern volatile struct UART_REGS UarteRegs;

extern volatile struct UART_REGS UartfRegs;

extern volatile struct UART_REGS_WRITE UartaWriteRegs;

extern volatile struct UART_REGS_WRITE UartbWriteRegs;

extern volatile struct UART_REGS_WRITE UartcWriteRegs;

extern volatile struct UART_REGS_WRITE UartdWriteRegs;

extern volatile struct UART_REGS_WRITE UarteWriteRegs;

extern volatile struct UART_REGS_WRITE UartfWriteRegs;

extern volatile struct WADI_CONFIG_REGS Wadi1Blk1ConfigRegs;

extern volatile struct WADI_CONFIG_REGS Wadi1Blk2ConfigRegs;

extern volatile struct WADI_CONFIG_REGS Wadi1Blk3ConfigRegs;

extern volatile struct WADI_CONFIG_REGS Wadi1Blk4ConfigRegs;

extern volatile struct WADI_CONFIG_REGS Wadi2Blk1ConfigRegs;

extern volatile struct WADI_CONFIG_REGS Wadi2Blk2ConfigRegs;

extern volatile struct WADI_CONFIG_REGS Wadi2Blk3ConfigRegs;

extern volatile struct WADI_CONFIG_REGS Wadi2Blk4ConfigRegs;

extern volatile struct WADI_OPER_SSS_REGS Wadi1OperSssRegs;

extern volatile struct WADI_OPER_SSS_REGS Wadi2OperSssRegs;

extern volatile struct WD_REGS WdRegs;

extern volatile struct XBAR_REGS XbarRegs;

extern volatile struct XINT_REGS XintRegs;



//===========================================================================
// End of file.
//===========================================================================


