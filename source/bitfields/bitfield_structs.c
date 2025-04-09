//###########################################################################
//
// FILE:    bitfield_structs.c
//
// TITLE:  Peripheral Bitfield struct definitions.
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

#include "bitfield_structs.h"

//
// Define Global Peripheral Variables:
//

__attribute__((noinit, location(ADCGLOBAL_BASE))) volatile struct ADC_GLOBAL_REGS AdcGlobalRegs;

__attribute__((noinit, location(ADCA_BASE))) volatile struct ADC_REGS AdcaRegs;

__attribute__((noinit, location(ADCB_BASE))) volatile struct ADC_REGS AdcbRegs;

__attribute__((noinit, location(ADCC_BASE))) volatile struct ADC_REGS AdccRegs;

__attribute__((noinit, location(ADCD_BASE))) volatile struct ADC_REGS AdcdRegs;

__attribute__((noinit, location(ADCE_BASE))) volatile struct ADC_REGS AdceRegs;

__attribute__((noinit, location(ADCARESULT_BASE))) volatile struct ADC_RESULT_REGS AdcaResultRegs;

__attribute__((noinit, location(ADCBRESULT_BASE))) volatile struct ADC_RESULT_REGS AdcbResultRegs;

__attribute__((noinit, location(ADCCRESULT_BASE))) volatile struct ADC_RESULT_REGS AdccResultRegs;

__attribute__((noinit, location(ADCDRESULT_BASE))) volatile struct ADC_RESULT_REGS AdcdResultRegs;

__attribute__((noinit, location(ADCERESULT_BASE))) volatile struct ADC_RESULT_REGS AdceResultRegs;

__attribute__((noinit, location(ADCSAFETYCHECKINTEVT1_BASE))) volatile struct ADC_SAFECHECK_INTEVT_REGS AdcSafetyCheckIntEvt1Regs;

__attribute__((noinit, location(ADCSAFETYCHECKINTEVT2_BASE))) volatile struct ADC_SAFECHECK_INTEVT_REGS AdcSafetyCheckIntEvt2Regs;

__attribute__((noinit, location(ADCSAFETYCHECKINTEVT3_BASE))) volatile struct ADC_SAFECHECK_INTEVT_REGS AdcSafetyCheckIntEvt3Regs;

__attribute__((noinit, location(ADCSAFETYCHECK1_BASE))) volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck1Regs;

__attribute__((noinit, location(ADCSAFETYCHECK2_BASE))) volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck2Regs;

__attribute__((noinit, location(ADCSAFETYCHECK3_BASE))) volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck3Regs;

__attribute__((noinit, location(ADCSAFETYCHECK4_BASE))) volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck4Regs;

__attribute__((noinit, location(ADCSAFETYCHECK5_BASE))) volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck5Regs;

__attribute__((noinit, location(ADCSAFETYCHECK6_BASE))) volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck6Regs;

__attribute__((noinit, location(ADCSAFETYCHECK7_BASE))) volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck7Regs;

__attribute__((noinit, location(ADCSAFETYCHECK8_BASE))) volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck8Regs;

__attribute__((noinit, location(ADCSAFETYCHECK9_BASE))) volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck9Regs;

__attribute__((noinit, location(ADCSAFETYCHECK10_BASE))) volatile struct ADC_SAFECHECK_REGS AdcSafetyCheck10Regs;

__attribute__((noinit, location(ANALOGSUBSYS_BASE))) volatile struct ANALOG_SUBSYS_REGS AnalogSubsysRegs;

__attribute__((noinit, location(C29CPUDIAG_BASE))) volatile struct C29_DIAG_REGS C29cpuDiagRegs;

__attribute__((noinit, location(C29CPURTINTSTACK_BASE))) volatile struct C29_RTINT_STACK C29CpuRtintStackRegs;

__attribute__((noinit, location(C29CPUSECCALLSTACK_BASE))) volatile struct C29_SECCALL_STACK C29CpuSecCallStackRegs;

__attribute__((noinit, location(C29CPUSECURE_BASE))) volatile struct C29_SECURE_REGS C29CpuSecureRegs;

__attribute__((noinit, location(C29CPUSELFTEST_BASE))) volatile struct C29_SELFTEST_REGS C29cpuSelfTestRegs;

__attribute__((noinit, location(CLB1_DATAEXCH_BASE))) volatile struct CLB_DATA_EXCHANGE_REGS Clb1DataExchRegs;

__attribute__((noinit, location(CLB2_DATAEXCH_BASE))) volatile struct CLB_DATA_EXCHANGE_REGS Clb2DataExchRegs;

__attribute__((noinit, location(CLB3_DATAEXCH_BASE))) volatile struct CLB_DATA_EXCHANGE_REGS Clb3DataExchRegs;

__attribute__((noinit, location(CLB4_DATAEXCH_BASE))) volatile struct CLB_DATA_EXCHANGE_REGS Clb4DataExchRegs;

__attribute__((noinit, location(CLB5_DATAEXCH_BASE))) volatile struct CLB_DATA_EXCHANGE_REGS Clb5DataExchRegs;

__attribute__((noinit, location(CLB6_DATAEXCH_BASE))) volatile struct CLB_DATA_EXCHANGE_REGS Clb6DataExchRegs;

__attribute__((noinit, location(CLB1_LOGICCFG_BASE))) volatile struct CLB_LOGIC_CONFIG_REGS Clb1LogicCfgRegs;

__attribute__((noinit, location(CLB2_LOGICCFG_BASE))) volatile struct CLB_LOGIC_CONFIG_REGS Clb2LogicCfgRegs;

__attribute__((noinit, location(CLB3_LOGICCFG_BASE))) volatile struct CLB_LOGIC_CONFIG_REGS Clb3LogicCfgRegs;

__attribute__((noinit, location(CLB4_LOGICCFG_BASE))) volatile struct CLB_LOGIC_CONFIG_REGS Clb4LogicCfgRegs;

__attribute__((noinit, location(CLB5_LOGICCFG_BASE))) volatile struct CLB_LOGIC_CONFIG_REGS Clb5LogicCfgRegs;

__attribute__((noinit, location(CLB6_LOGICCFG_BASE))) volatile struct CLB_LOGIC_CONFIG_REGS Clb6LogicCfgRegs;

__attribute__((noinit, location(CLB1_LOGICCTRL_BASE))) volatile struct CLB_LOGIC_CONTROL_REGS Clb1LogicCtrlRegs;

__attribute__((noinit, location(CLB2_LOGICCTRL_BASE))) volatile struct CLB_LOGIC_CONTROL_REGS Clb2LogicCtrlRegs;

__attribute__((noinit, location(CLB3_LOGICCTRL_BASE))) volatile struct CLB_LOGIC_CONTROL_REGS Clb3LogicCtrlRegs;

__attribute__((noinit, location(CLB4_LOGICCTRL_BASE))) volatile struct CLB_LOGIC_CONTROL_REGS Clb4LogicCtrlRegs;

__attribute__((noinit, location(CLB5_LOGICCTRL_BASE))) volatile struct CLB_LOGIC_CONTROL_REGS Clb5LogicCtrlRegs;

__attribute__((noinit, location(CLB6_LOGICCTRL_BASE))) volatile struct CLB_LOGIC_CONTROL_REGS Clb6LogicCtrlRegs;

__attribute__((noinit, location(CLBXBAR_BASE))) volatile struct CLB_XBAR_REGS ClbXbarRegs;

__attribute__((noinit, location(CMPSS1_BASE))) volatile struct CMPSS_REGS Cmpss1Regs;

__attribute__((noinit, location(CMPSS2_BASE))) volatile struct CMPSS_REGS Cmpss2Regs;

__attribute__((noinit, location(CMPSS3_BASE))) volatile struct CMPSS_REGS Cmpss3Regs;

__attribute__((noinit, location(CMPSS4_BASE))) volatile struct CMPSS_REGS Cmpss4Regs;

__attribute__((noinit, location(CMPSS5_BASE))) volatile struct CMPSS_REGS Cmpss5Regs;

__attribute__((noinit, location(CMPSS6_BASE))) volatile struct CMPSS_REGS Cmpss6Regs;

__attribute__((noinit, location(CMPSS7_BASE))) volatile struct CMPSS_REGS Cmpss7Regs;

__attribute__((noinit, location(CMPSS8_BASE))) volatile struct CMPSS_REGS Cmpss8Regs;

__attribute__((noinit, location(CMPSS9_BASE))) volatile struct CMPSS_REGS Cmpss9Regs;

__attribute__((noinit, location(CMPSS10_BASE))) volatile struct CMPSS_REGS Cmpss10Regs;

__attribute__((noinit, location(CMPSS11_BASE))) volatile struct CMPSS_REGS Cmpss11Regs;

__attribute__((noinit, location(CMPSS12_BASE))) volatile struct CMPSS_REGS Cmpss12Regs;

__attribute__((noinit, location(CPU1IPCRCV_BASE))) volatile struct CPU1_IPC_RCV_REGS Cpu1IpcrcvRegs;

__attribute__((noinit, location(CPU1IPCSEND_BASE))) volatile struct CPU1_IPC_SEND_REGS Cpu1IpcsendRegs;

__attribute__((noinit, location(CPU2IPCRCV_BASE))) volatile struct CPU2_IPC_RCV_REGS Cpu2IpcrcvRegs;

__attribute__((noinit, location(CPU2IPCSEND_BASE))) volatile struct CPU2_IPC_SEND_REGS Cpu2IpcsendRegs;

__attribute__((noinit, location(CPU3IPCRCV_BASE))) volatile struct CPU3_IPC_RCV_REGS Cpu3IpcrcvRegs;

__attribute__((noinit, location(CPU3IPCSEND_BASE))) volatile struct CPU3_IPC_SEND_REGS Cpu3IpcsendRegs;

__attribute__((noinit, location(CPUTIMER0_BASE))) volatile struct CPUTIMER_REGS CpuTimer0Regs;

__attribute__((noinit, location(CPUTIMER1_BASE))) volatile struct CPUTIMER_REGS CpuTimer1Regs;

__attribute__((noinit, location(CPUTIMER2_BASE))) volatile struct CPUTIMER_REGS CpuTimer2Regs;

__attribute__((noinit, location(CPUPERCFG_BASE))) volatile struct CPU_PER_CFG_REGS CpuPerCfgRegs;

__attribute__((noinit, location(CPUSYS_BASE))) volatile struct CPU_SYS_REGS CpuSysRegs;

__attribute__((noinit, location(DACA_BASE))) volatile struct DAC_REGS DacaRegs;

__attribute__((noinit, location(DACB_BASE))) volatile struct DAC_REGS DacbRegs;

__attribute__((noinit, location(DCC1_BASE))) volatile struct DCC_REGS Dcc1Regs;

__attribute__((noinit, location(DCC2_BASE))) volatile struct DCC_REGS Dcc2Regs;

__attribute__((noinit, location(DCC3_BASE))) volatile struct DCC_REGS Dcc3Regs;

__attribute__((noinit, location(DEVCFG_BASE))) volatile struct DEV_CFG_REGS DevCfgRegs;

__attribute__((noinit, location(EPWM1DE_BASE))) volatile struct DE_REGS EPwm1DeRegs;

__attribute__((noinit, location(EPWM2DE_BASE))) volatile struct DE_REGS EPwm2DeRegs;

__attribute__((noinit, location(EPWM3DE_BASE))) volatile struct DE_REGS EPwm3DeRegs;

__attribute__((noinit, location(EPWM4DE_BASE))) volatile struct DE_REGS EPwm4DeRegs;

__attribute__((noinit, location(EPWM5DE_BASE))) volatile struct DE_REGS EPwm5DeRegs;

__attribute__((noinit, location(EPWM6DE_BASE))) volatile struct DE_REGS EPwm6DeRegs;

__attribute__((noinit, location(EPWM7DE_BASE))) volatile struct DE_REGS EPwm7DeRegs;

__attribute__((noinit, location(EPWM8DE_BASE))) volatile struct DE_REGS EPwm8DeRegs;

__attribute__((noinit, location(EPWM9DE_BASE))) volatile struct DE_REGS EPwm9DeRegs;

__attribute__((noinit, location(EPWM10DE_BASE))) volatile struct DE_REGS EPwm10DeRegs;

__attribute__((noinit, location(EPWM11DE_BASE))) volatile struct DE_REGS EPwm11DeRegs;

__attribute__((noinit, location(EPWM12DE_BASE))) volatile struct DE_REGS EPwm12DeRegs;

__attribute__((noinit, location(EPWM13DE_BASE))) volatile struct DE_REGS EPwm13DeRegs;

__attribute__((noinit, location(EPWM14DE_BASE))) volatile struct DE_REGS EPwm14DeRegs;

__attribute__((noinit, location(EPWM15DE_BASE))) volatile struct DE_REGS EPwm15DeRegs;

__attribute__((noinit, location(EPWM16DE_BASE))) volatile struct DE_REGS EPwm16DeRegs;

__attribute__((noinit, location(EPWM17DE_BASE))) volatile struct DE_REGS EPwm17DeRegs;

__attribute__((noinit, location(EPWM18DE_BASE))) volatile struct DE_REGS EPwm18DeRegs;

__attribute__((noinit, location(EPWM1DEXLINK_BASE))) volatile struct DE_REGS EPwm1DeXlinkRegs;

__attribute__((noinit, location(EPWM2DEXLINK_BASE))) volatile struct DE_REGS EPwm2DeXlinkRegs;

__attribute__((noinit, location(EPWM3DEXLINK_BASE))) volatile struct DE_REGS EPwm3DeXlinkRegs;

__attribute__((noinit, location(EPWM4DEXLINK_BASE))) volatile struct DE_REGS EPwm4DeXlinkRegs;

__attribute__((noinit, location(EPWM5DEXLINK_BASE))) volatile struct DE_REGS EPwm5DeXlinkRegs;

__attribute__((noinit, location(EPWM6DEXLINK_BASE))) volatile struct DE_REGS EPwm6DeXlinkRegs;

__attribute__((noinit, location(EPWM7DEXLINK_BASE))) volatile struct DE_REGS EPwm7DeXlinkRegs;

__attribute__((noinit, location(EPWM8DEXLINK_BASE))) volatile struct DE_REGS EPwm8DeXlinkRegs;

__attribute__((noinit, location(EPWM9DEXLINK_BASE))) volatile struct DE_REGS EPwm9DeXlinkRegs;

__attribute__((noinit, location(EPWM10DEXLINK_BASE))) volatile struct DE_REGS EPwm10DeXlinkRegs;

__attribute__((noinit, location(EPWM11DEXLINK_BASE))) volatile struct DE_REGS EPwm11DeXlinkRegs;

__attribute__((noinit, location(EPWM12DEXLINK_BASE))) volatile struct DE_REGS EPwm12DeXlinkRegs;

__attribute__((noinit, location(EPWM13DEXLINK_BASE))) volatile struct DE_REGS EPwm13DeXlinkRegs;

__attribute__((noinit, location(EPWM14DEXLINK_BASE))) volatile struct DE_REGS EPwm14DeXlinkRegs;

__attribute__((noinit, location(EPWM15DEXLINK_BASE))) volatile struct DE_REGS EPwm15DeXlinkRegs;

__attribute__((noinit, location(EPWM16DEXLINK_BASE))) volatile struct DE_REGS EPwm16DeXlinkRegs;

__attribute__((noinit, location(EPWM17DEXLINK_BASE))) volatile struct DE_REGS EPwm17DeXlinkRegs;

__attribute__((noinit, location(EPWM18DEXLINK_BASE))) volatile struct DE_REGS EPwm18DeXlinkRegs;

__attribute__((noinit, location(CPUDLT_BASE))) volatile struct DLT_CORE_REGS cpuDltRegs;

__attribute__((noinit, location(CPU1DLTFIFO_BASE))) volatile struct DLT_FIFO_REGS CPU1DLTFifoRegs;

__attribute__((noinit, location(CPU2DLTFIFO_BASE))) volatile struct DLT_FIFO_REGS CPU2DLTFifoRegs;

__attribute__((noinit, location(CPU3DLTFIFO_BASE))) volatile struct DLT_FIFO_REGS CPU3DLTFifoRegs;

__attribute__((noinit, location(ECAP1_BASE))) volatile struct ECAP_REGS ECap1Regs;

__attribute__((noinit, location(ECAP2_BASE))) volatile struct ECAP_REGS ECap2Regs;

__attribute__((noinit, location(ECAP3_BASE))) volatile struct ECAP_REGS ECap3Regs;

__attribute__((noinit, location(ECAP4_BASE))) volatile struct ECAP_REGS ECap4Regs;

__attribute__((noinit, location(ECAP5_BASE))) volatile struct ECAP_REGS ECap5Regs;

__attribute__((noinit, location(ECAP6_BASE))) volatile struct ECAP_REGS ECap6Regs;

__attribute__((noinit, location(ECAP1SIGNALMONITORING_BASE))) volatile struct ECAP_SIGNAL_MONITORING ECap1SignalMonitoringRegs;

__attribute__((noinit, location(ECAP2SIGNALMONITORING_BASE))) volatile struct ECAP_SIGNAL_MONITORING ECap2SignalMonitoringRegs;

__attribute__((noinit, location(ECAP3SIGNALMONITORING_BASE))) volatile struct ECAP_SIGNAL_MONITORING ECap3SignalMonitoringRegs;

__attribute__((noinit, location(ECAP4SIGNALMONITORING_BASE))) volatile struct ECAP_SIGNAL_MONITORING ECap4SignalMonitoringRegs;

__attribute__((noinit, location(ECAP5SIGNALMONITORING_BASE))) volatile struct ECAP_SIGNAL_MONITORING ECap5SignalMonitoringRegs;

__attribute__((noinit, location(ECAP6SIGNALMONITORING_BASE))) volatile struct ECAP_SIGNAL_MONITORING ECap6SignalMonitoringRegs;

__attribute__((noinit, location(EMIF1_BASE))) volatile struct EMIF_REGS EMIF1Regs;

__attribute__((noinit, location(EPGMUX_BASE))) volatile struct EPG_MUX_REGS EPGMuxRegs;

__attribute__((noinit, location(EPG_BASE))) volatile struct EPG_REGS EPGRegs;

__attribute__((noinit, location(EPWM1_BASE))) volatile struct EPWM_REGS EPwm1Regs;

__attribute__((noinit, location(EPWM2_BASE))) volatile struct EPWM_REGS EPwm2Regs;

__attribute__((noinit, location(EPWM3_BASE))) volatile struct EPWM_REGS EPwm3Regs;

__attribute__((noinit, location(EPWM4_BASE))) volatile struct EPWM_REGS EPwm4Regs;

__attribute__((noinit, location(EPWM5_BASE))) volatile struct EPWM_REGS EPwm5Regs;

__attribute__((noinit, location(EPWM6_BASE))) volatile struct EPWM_REGS EPwm6Regs;

__attribute__((noinit, location(EPWM7_BASE))) volatile struct EPWM_REGS EPwm7Regs;

__attribute__((noinit, location(EPWM8_BASE))) volatile struct EPWM_REGS EPwm8Regs;

__attribute__((noinit, location(EPWM9_BASE))) volatile struct EPWM_REGS EPwm9Regs;

__attribute__((noinit, location(EPWM10_BASE))) volatile struct EPWM_REGS EPwm10Regs;

__attribute__((noinit, location(EPWM11_BASE))) volatile struct EPWM_REGS EPwm11Regs;

__attribute__((noinit, location(EPWM12_BASE))) volatile struct EPWM_REGS EPwm12Regs;

__attribute__((noinit, location(EPWM13_BASE))) volatile struct EPWM_REGS EPwm13Regs;

__attribute__((noinit, location(EPWM14_BASE))) volatile struct EPWM_REGS EPwm14Regs;

__attribute__((noinit, location(EPWM15_BASE))) volatile struct EPWM_REGS EPwm15Regs;

__attribute__((noinit, location(EPWM16_BASE))) volatile struct EPWM_REGS EPwm16Regs;

__attribute__((noinit, location(EPWM17_BASE))) volatile struct EPWM_REGS EPwm17Regs;

__attribute__((noinit, location(EPWM18_BASE))) volatile struct EPWM_REGS EPwm18Regs;

__attribute__((noinit, location(EPWM1XLINK_BASE))) volatile struct EPWM_REGS EPwm1XlinkRegs;

__attribute__((noinit, location(EPWM2XLINK_BASE))) volatile struct EPWM_REGS EPwm2XlinkRegs;

__attribute__((noinit, location(EPWM3XLINK_BASE))) volatile struct EPWM_REGS EPwm3XlinkRegs;

__attribute__((noinit, location(EPWM4XLINK_BASE))) volatile struct EPWM_REGS EPwm4XlinkRegs;

__attribute__((noinit, location(EPWM5XLINK_BASE))) volatile struct EPWM_REGS EPwm5XlinkRegs;

__attribute__((noinit, location(EPWM6XLINK_BASE))) volatile struct EPWM_REGS EPwm6XlinkRegs;

__attribute__((noinit, location(EPWM7XLINK_BASE))) volatile struct EPWM_REGS EPwm7XlinkRegs;

__attribute__((noinit, location(EPWM8XLINK_BASE))) volatile struct EPWM_REGS EPwm8XlinkRegs;

__attribute__((noinit, location(EPWM9XLINK_BASE))) volatile struct EPWM_REGS EPwm9XlinkRegs;

__attribute__((noinit, location(EPWM10XLINK_BASE))) volatile struct EPWM_REGS EPwm10XlinkRegs;

__attribute__((noinit, location(EPWM11XLINK_BASE))) volatile struct EPWM_REGS EPwm11XlinkRegs;

__attribute__((noinit, location(EPWM12XLINK_BASE))) volatile struct EPWM_REGS EPwm12XlinkRegs;

__attribute__((noinit, location(EPWM13XLINK_BASE))) volatile struct EPWM_REGS EPwm13XlinkRegs;

__attribute__((noinit, location(EPWM14XLINK_BASE))) volatile struct EPWM_REGS EPwm14XlinkRegs;

__attribute__((noinit, location(EPWM15XLINK_BASE))) volatile struct EPWM_REGS EPwm15XlinkRegs;

__attribute__((noinit, location(EPWM16XLINK_BASE))) volatile struct EPWM_REGS EPwm16XlinkRegs;

__attribute__((noinit, location(EPWM17XLINK_BASE))) volatile struct EPWM_REGS EPwm17XlinkRegs;

__attribute__((noinit, location(EPWM18XLINK_BASE))) volatile struct EPWM_REGS EPwm18XlinkRegs;

__attribute__((noinit, location(EPWMXBAR_BASE))) volatile struct EPWM_XBAR_REGS EPwmXbarRegs;

__attribute__((noinit, location(EPWM1XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm1XcmpRegs;

__attribute__((noinit, location(EPWM2XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm2XcmpRegs;

__attribute__((noinit, location(EPWM3XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm3XcmpRegs;

__attribute__((noinit, location(EPWM4XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm4XcmpRegs;

__attribute__((noinit, location(EPWM5XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm5XcmpRegs;

__attribute__((noinit, location(EPWM6XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm6XcmpRegs;

__attribute__((noinit, location(EPWM7XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm7XcmpRegs;

__attribute__((noinit, location(EPWM8XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm8XcmpRegs;

__attribute__((noinit, location(EPWM9XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm9XcmpRegs;

__attribute__((noinit, location(EPWM10XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm10XcmpRegs;

__attribute__((noinit, location(EPWM11XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm11XcmpRegs;

__attribute__((noinit, location(EPWM12XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm12XcmpRegs;

__attribute__((noinit, location(EPWM13XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm13XcmpRegs;

__attribute__((noinit, location(EPWM14XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm14XcmpRegs;

__attribute__((noinit, location(EPWM15XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm15XcmpRegs;

__attribute__((noinit, location(EPWM16XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm16XcmpRegs;

__attribute__((noinit, location(EPWM17XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm17XcmpRegs;

__attribute__((noinit, location(EPWM18XCMP_BASE))) volatile struct EPWM_XCMP_REGS EPwm18XcmpRegs;

__attribute__((noinit, location(EPWM1XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm1XcmpXlinkRegs;

__attribute__((noinit, location(EPWM2XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm2XcmpXlinkRegs;

__attribute__((noinit, location(EPWM3XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm3XcmpXlinkRegs;

__attribute__((noinit, location(EPWM4XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm4XcmpXlinkRegs;

__attribute__((noinit, location(EPWM5XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm5XcmpXlinkRegs;

__attribute__((noinit, location(EPWM6XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm6XcmpXlinkRegs;

__attribute__((noinit, location(EPWM7XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm7XcmpXlinkRegs;

__attribute__((noinit, location(EPWM8XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm8XcmpXlinkRegs;

__attribute__((noinit, location(EPWM9XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm9XcmpXlinkRegs;

__attribute__((noinit, location(EPWM10XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm10XcmpXlinkRegs;

__attribute__((noinit, location(EPWM11XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm11XcmpXlinkRegs;

__attribute__((noinit, location(EPWM12XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm12XcmpXlinkRegs;

__attribute__((noinit, location(EPWM13XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm13XcmpXlinkRegs;

__attribute__((noinit, location(EPWM14XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm14XcmpXlinkRegs;

__attribute__((noinit, location(EPWM15XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm15XcmpXlinkRegs;

__attribute__((noinit, location(EPWM16XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm16XcmpXlinkRegs;

__attribute__((noinit, location(EPWM17XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm17XcmpXlinkRegs;

__attribute__((noinit, location(EPWM18XCMPXLINK_BASE))) volatile struct EPWM_XCMP_REGS EPwm18XcmpXlinkRegs;

__attribute__((noinit, location(EQEP1_BASE))) volatile struct EQEP_REGS EQep1Regs;

__attribute__((noinit, location(EQEP2_BASE))) volatile struct EQEP_REGS EQep2Regs;

__attribute__((noinit, location(EQEP3_BASE))) volatile struct EQEP_REGS EQep3Regs;

__attribute__((noinit, location(EQEP4_BASE))) volatile struct EQEP_REGS EQep4Regs;

__attribute__((noinit, location(EQEP5_BASE))) volatile struct EQEP_REGS EQep5Regs;

__attribute__((noinit, location(EQEP6_BASE))) volatile struct EQEP_REGS EQep6Regs;

__attribute__((noinit, location(ERAD_BASE))) volatile struct ERAD_REGS EradRegs;

__attribute__((noinit, location(ERRORAGGREGATOR_BASE))) volatile struct ERROR_AGGREGATOR_CONFIG_REGS ErrorAggregatorRegs;

__attribute__((noinit, location(ESC_SS_CONFIG_BASE))) volatile struct ESCSS_CONFIG_REGS EscssaConfigRegs;

__attribute__((noinit, location(ESC_SS_BASE))) volatile struct ESCSS_REGS EscssRegs;

__attribute__((noinit, location(ESMCPU1_BASE))) volatile struct ESM_CPU_REGS EsmCpu1Regs;

__attribute__((noinit, location(ESMCPU2_BASE))) volatile struct ESM_CPU_REGS EsmCpu2Regs;

__attribute__((noinit, location(ESMCPU3_BASE))) volatile struct ESM_CPU_REGS EsmCpu3Regs;

__attribute__((noinit, location(ESMSAFETYAGG_BASE))) volatile struct ESM_SAFETYAGG_REGS EsmSafetyAggRegs;

__attribute__((noinit, location(ESMSYSTEM_BASE))) volatile struct ESM_SYSTEM_REGS EsmSystemRegs;

__attribute__((noinit, location(FRI1_BASE))) volatile struct FRI_CTRL_REGS Fri1Regs;

__attribute__((noinit, location(FSIRXA_BASE))) volatile struct FSI_RX_REGS FsiRxaRegs;

__attribute__((noinit, location(FSIRXB_BASE))) volatile struct FSI_RX_REGS FsiRxbRegs;

__attribute__((noinit, location(FSIRXC_BASE))) volatile struct FSI_RX_REGS FsiRxcRegs;

__attribute__((noinit, location(FSIRXD_BASE))) volatile struct FSI_RX_REGS FsiRxdRegs;

__attribute__((noinit, location(FSITXA_BASE))) volatile struct FSI_TX_REGS FsiTxaRegs;

__attribute__((noinit, location(FSITXB_BASE))) volatile struct FSI_TX_REGS FsiTxbRegs;

__attribute__((noinit, location(FSITXC_BASE))) volatile struct FSI_TX_REGS FsiTxcRegs;

__attribute__((noinit, location(FSITXD_BASE))) volatile struct FSI_TX_REGS FsiTxdRegs;

__attribute__((noinit, location(GPIOCTRL_BASE))) volatile struct GPIO_CTRL_REGS GpioCtrlRegs;

__attribute__((noinit, location(GPIODATAREAD_BASE))) volatile struct GPIO_DATA_READ_REGS GpioDataReadRegs;

__attribute__((noinit, location(GPIODATA_BASE))) volatile struct GPIO_DATA_REGS GpioDataRegs;

__attribute__((noinit, location(HRCAP5_BASE))) volatile struct HRCAP_REGS HRCap5Regs;

__attribute__((noinit, location(HRCAP6_BASE))) volatile struct HRCAP_REGS HRCap6Regs;

__attribute__((noinit, location(HRPWMCAL1_BASE))) volatile struct HRPWMCAL_REGS Hrpwmcal1Regs;

__attribute__((noinit, location(HRPWMCAL2_BASE))) volatile struct HRPWMCAL_REGS Hrpwmcal2Regs;

__attribute__((noinit, location(HRPWMCAL3_BASE))) volatile struct HRPWMCAL_REGS Hrpwmcal3Regs;

__attribute__((noinit, location(HSMERRORAGGREGATOR_BASE))) volatile struct HSM_ERROR_AGGREGATOR_CONFIG_REGS HSMErrorAggregatorRegs;

__attribute__((noinit, location(I2CA_BASE))) volatile struct I2C_REGS I2caRegs;

__attribute__((noinit, location(I2CB_BASE))) volatile struct I2C_REGS I2cbRegs;

__attribute__((noinit, location(ICLXBAR_BASE))) volatile struct ICL_XBAR_REGS IclXbarRegs;

__attribute__((noinit, location(INPUTXBAR_BASE))) volatile struct INPUT_XBAR_REGS InputXbarRegs;

__attribute__((noinit, location(IPCCOUNTER_BASE))) volatile struct IPC_COUNTER_REGS IpcCounterRegs;

__attribute__((noinit, location(LCM_CPU_BASE))) volatile struct LCM_REGS LCMCPURegs;

__attribute__((noinit, location(LCM_DMA_BASE))) volatile struct LCM_REGS LCMDMARegs;

__attribute__((noinit, location(LINA_BASE))) volatile struct LIN_REGS LinaRegs;

__attribute__((noinit, location(LINB_BASE))) volatile struct LIN_REGS LinbRegs;

__attribute__((noinit, location(MDLXBAR_BASE))) volatile struct MDL_XBAR_REGS MdlXbarRegs;

__attribute__((noinit, location(MEMSSCCFG_BASE))) volatile struct MEMSS_C_CONFIG_REGS MemssCCfgRegs;

__attribute__((noinit, location(MEMSSLCFG_BASE))) volatile struct MEMSS_L_CONFIG_REGS MemssLCfgRegs;

__attribute__((noinit, location(MEMSSMISCI_BASE))) volatile struct MEMSS_MISCI_REGS MemssMisciRegs;

__attribute__((noinit, location(MEMSSMCFG_BASE))) volatile struct MEMSS_M_CONFIG_REGS MemssMCfgRegs;

__attribute__((noinit, location(EPWM1MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm1MinDbLutRegs;

__attribute__((noinit, location(EPWM2MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm2MinDbLutRegs;

__attribute__((noinit, location(EPWM3MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm3MinDbLutRegs;

__attribute__((noinit, location(EPWM4MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm4MinDbLutRegs;

__attribute__((noinit, location(EPWM5MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm5MinDbLutRegs;

__attribute__((noinit, location(EPWM6MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm6MinDbLutRegs;

__attribute__((noinit, location(EPWM7MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm7MinDbLutRegs;

__attribute__((noinit, location(EPWM8MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm8MinDbLutRegs;

__attribute__((noinit, location(EPWM9MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm9MinDbLutRegs;

__attribute__((noinit, location(EPWM10MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm10MinDbLutRegs;

__attribute__((noinit, location(EPWM11MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm11MinDbLutRegs;

__attribute__((noinit, location(EPWM12MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm12MinDbLutRegs;

__attribute__((noinit, location(EPWM13MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm13MinDbLutRegs;

__attribute__((noinit, location(EPWM14MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm14MinDbLutRegs;

__attribute__((noinit, location(EPWM15MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm15MinDbLutRegs;

__attribute__((noinit, location(EPWM16MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm16MinDbLutRegs;

__attribute__((noinit, location(EPWM17MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm17MinDbLutRegs;

__attribute__((noinit, location(EPWM18MINDBLUT_BASE))) volatile struct MINDB_LUT_REGS EPwm18MinDbLutRegs;

__attribute__((noinit, location(EPWM1MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm1MinDbLutXlinkRegs;

__attribute__((noinit, location(EPWM2MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm2MinDbLutXlinkRegs;

__attribute__((noinit, location(EPWM3MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm3MinDbLutXlinkRegs;

__attribute__((noinit, location(EPWM4MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm4MinDbLutXlinkRegs;

__attribute__((noinit, location(EPWM5MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm5MinDbLutXlinkRegs;

__attribute__((noinit, location(EPWM6MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm6MinDbLutXlinkRegs;

__attribute__((noinit, location(EPWM7MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm7MinDbLutXlinkRegs;

__attribute__((noinit, location(EPWM8MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm8MinDbLutXlinkRegs;

__attribute__((noinit, location(EPWM9MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm9MinDbLutXlinkRegs;

__attribute__((noinit, location(EPWM10MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm10MinDbLutXlinkRegs;

__attribute__((noinit, location(EPWM11MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm11MinDbLutXlinkRegs;

__attribute__((noinit, location(EPWM12MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm12MinDbLutXlinkRegs;

__attribute__((noinit, location(EPWM13MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm13MinDbLutXlinkRegs;

__attribute__((noinit, location(EPWM14MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm14MinDbLutXlinkRegs;

__attribute__((noinit, location(EPWM15MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm15MinDbLutXlinkRegs;

__attribute__((noinit, location(EPWM16MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm16MinDbLutXlinkRegs;

__attribute__((noinit, location(EPWM17MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm17MinDbLutXlinkRegs;

__attribute__((noinit, location(EPWM18MINDBLUTXLINK_BASE))) volatile struct MINDB_LUT_REGS EPwm18MinDbLutXlinkRegs;

__attribute__((noinit, location(OUTPUTXBAR1_FLAGS_BASE))) volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar1flagsRegs;

__attribute__((noinit, location(OUTPUTXBAR2_FLAGS_BASE))) volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar2flagsRegs;

__attribute__((noinit, location(OUTPUTXBAR3_FLAGS_BASE))) volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar3flagsRegs;

__attribute__((noinit, location(OUTPUTXBAR4_FLAGS_BASE))) volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar4flagsRegs;

__attribute__((noinit, location(OUTPUTXBAR5_FLAGS_BASE))) volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar5flagsRegs;

__attribute__((noinit, location(OUTPUTXBAR6_FLAGS_BASE))) volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar6flagsRegs;

__attribute__((noinit, location(OUTPUTXBAR7_FLAGS_BASE))) volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar7flagsRegs;

__attribute__((noinit, location(OUTPUTXBAR8_FLAGS_BASE))) volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar8flagsRegs;

__attribute__((noinit, location(OUTPUTXBAR9_FLAGS_BASE))) volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar9flagsRegs;

__attribute__((noinit, location(OUTPUTXBAR10_FLAGS_BASE))) volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar10flagsRegs;

__attribute__((noinit, location(OUTPUTXBAR11_FLAGS_BASE))) volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar11flagsRegs;

__attribute__((noinit, location(OUTPUTXBAR12_FLAGS_BASE))) volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar12flagsRegs;

__attribute__((noinit, location(OUTPUTXBAR13_FLAGS_BASE))) volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar13flagsRegs;

__attribute__((noinit, location(OUTPUTXBAR14_FLAGS_BASE))) volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar14flagsRegs;

__attribute__((noinit, location(OUTPUTXBAR15_FLAGS_BASE))) volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar15flagsRegs;

__attribute__((noinit, location(OUTPUTXBAR16_FLAGS_BASE))) volatile struct OUTPUTXBAR_FLAG_REGS Outputxbar16flagsRegs;

__attribute__((noinit, location(OUTPUTXBAR_BASE))) volatile struct OUTPUTXBAR_REGS OutputXbarRegs;

__attribute__((noinit, location(PIPE_BASE))) volatile struct PIPE_REGS PipeRegs;

__attribute__((noinit, location(PMBUSA_BASE))) volatile struct PMBUS_REGS PmbusaRegs;

__attribute__((noinit, location(RTDMA1CH1_BASE))) volatile struct RTDMA_CH_REGS Rtdma1Ch1Regs;

__attribute__((noinit, location(RTDMA1CH2_BASE))) volatile struct RTDMA_CH_REGS Rtdma1Ch2Regs;

__attribute__((noinit, location(RTDMA1CH3_BASE))) volatile struct RTDMA_CH_REGS Rtdma1Ch3Regs;

__attribute__((noinit, location(RTDMA1CH4_BASE))) volatile struct RTDMA_CH_REGS Rtdma1Ch4Regs;

__attribute__((noinit, location(RTDMA1CH5_BASE))) volatile struct RTDMA_CH_REGS Rtdma1Ch5Regs;

__attribute__((noinit, location(RTDMA1CH6_BASE))) volatile struct RTDMA_CH_REGS Rtdma1Ch6Regs;

__attribute__((noinit, location(RTDMA1CH7_BASE))) volatile struct RTDMA_CH_REGS Rtdma1Ch7Regs;

__attribute__((noinit, location(RTDMA1CH8_BASE))) volatile struct RTDMA_CH_REGS Rtdma1Ch8Regs;

__attribute__((noinit, location(RTDMA1CH9_BASE))) volatile struct RTDMA_CH_REGS Rtdma1Ch9Regs;

__attribute__((noinit, location(RTDMA1CH10_BASE))) volatile struct RTDMA_CH_REGS Rtdma1Ch10Regs;

__attribute__((noinit, location(RTDMA2CH1_BASE))) volatile struct RTDMA_CH_REGS Rtdma2Ch1Regs;

__attribute__((noinit, location(RTDMA2CH2_BASE))) volatile struct RTDMA_CH_REGS Rtdma2Ch2Regs;

__attribute__((noinit, location(RTDMA2CH3_BASE))) volatile struct RTDMA_CH_REGS Rtdma2Ch3Regs;

__attribute__((noinit, location(RTDMA2CH4_BASE))) volatile struct RTDMA_CH_REGS Rtdma2Ch4Regs;

__attribute__((noinit, location(RTDMA2CH5_BASE))) volatile struct RTDMA_CH_REGS Rtdma2Ch5Regs;

__attribute__((noinit, location(RTDMA2CH6_BASE))) volatile struct RTDMA_CH_REGS Rtdma2Ch6Regs;

__attribute__((noinit, location(RTDMA2CH7_BASE))) volatile struct RTDMA_CH_REGS Rtdma2Ch7Regs;

__attribute__((noinit, location(RTDMA2CH8_BASE))) volatile struct RTDMA_CH_REGS Rtdma2Ch8Regs;

__attribute__((noinit, location(RTDMA2CH9_BASE))) volatile struct RTDMA_CH_REGS Rtdma2Ch9Regs;

__attribute__((noinit, location(RTDMA2CH10_BASE))) volatile struct RTDMA_CH_REGS Rtdma2Ch10Regs;

__attribute__((noinit, location(RTDMA1_DIAG_BASE))) volatile struct RTDMA_DIAG_REGS Rtdma1DiagRegs;

__attribute__((noinit, location(RTDMA2_DIAG_BASE))) volatile struct RTDMA_DIAG_REGS Rtdma2DiagRegs;

__attribute__((noinit, location(RTDMA1_MPU_BASE))) volatile struct RTDMA_MPU_REGS Rtdma1MPURegs;

__attribute__((noinit, location(RTDMA2_MPU_BASE))) volatile struct RTDMA_MPU_REGS Rtdma2MPURegs;

__attribute__((noinit, location(RTDMA1_BASE))) volatile struct RTDMA_REGS Rtdma1Regs;

__attribute__((noinit, location(RTDMA2_BASE))) volatile struct RTDMA_REGS Rtdma2Regs;

__attribute__((noinit, location(RTDMA1_SELFTEST_BASE))) volatile struct RTDMA_SELFTEST_REGS Rtdma1SelfTestRegs;

__attribute__((noinit, location(RTDMA2_SELFTEST_BASE))) volatile struct RTDMA_SELFTEST_REGS Rtdma2SelfTestRegs;

__attribute__((noinit, location(SDFM1_BASE))) volatile struct SDFM_REGS Sdfm1Regs;

__attribute__((noinit, location(SDFM2_BASE))) volatile struct SDFM_REGS Sdfm2Regs;

__attribute__((noinit, location(SDFM3_BASE))) volatile struct SDFM_REGS Sdfm3Regs;

__attribute__((noinit, location(SDFM4_BASE))) volatile struct SDFM_REGS Sdfm4Regs;

__attribute__((noinit, location(C29DEBUGSS_BASE))) volatile struct SECAP_HANDLER_REGS c29debugssRegs;

__attribute__((noinit, location(SENT1_BASE))) volatile struct SENT_CFG Sent1CsentRegs;

__attribute__((noinit, location(SENT2_BASE))) volatile struct SENT_CFG Sent2CsentRegs;

__attribute__((noinit, location(SENT3_BASE))) volatile struct SENT_CFG Sent3CsentRegs;

__attribute__((noinit, location(SENT4_BASE))) volatile struct SENT_CFG Sent4CsentRegs;

__attribute__((noinit, location(SENT5_BASE))) volatile struct SENT_CFG Sent5CsentRegs;

__attribute__((noinit, location(SENT6_BASE))) volatile struct SENT_CFG Sent6CsentRegs;

__attribute__((noinit, location(SENT1_BASE + 0x400U))) volatile struct SENT_MEM Sent1MemRegs;

__attribute__((noinit, location(SENT2_BASE + 0x400U))) volatile struct SENT_MEM Sent2MemRegs;

__attribute__((noinit, location(SENT3_BASE + 0x400U))) volatile struct SENT_MEM Sent3MemRegs;

__attribute__((noinit, location(SENT4_BASE + 0x400U))) volatile struct SENT_MEM Sent4MemRegs;

__attribute__((noinit, location(SENT5_BASE + 0x400U))) volatile struct SENT_MEM Sent5MemRegs;

__attribute__((noinit, location(SENT6_BASE + 0x400U))) volatile struct SENT_MEM Sent6MemRegs;

__attribute__((noinit, location(SENT1_BASE + 0x800U))) volatile struct SENT_MTPG Sent1MtpgRegs;

__attribute__((noinit, location(SENT2_BASE + 0x800U))) volatile struct SENT_MTPG Sent2MtpgRegs;

__attribute__((noinit, location(SENT3_BASE + 0x800U))) volatile struct SENT_MTPG Sent3MtpgRegs;

__attribute__((noinit, location(SENT4_BASE + 0x800U))) volatile struct SENT_MTPG Sent4MtpgRegs;

__attribute__((noinit, location(SENT5_BASE + 0x800U))) volatile struct SENT_MTPG Sent5MtpgRegs;

__attribute__((noinit, location(SENT6_BASE + 0x800U))) volatile struct SENT_MTPG Sent6MtpgRegs;

__attribute__((noinit, location(SPIA_BASE))) volatile struct SPI_REGS SpiaRegs;

__attribute__((noinit, location(SPIB_BASE))) volatile struct SPI_REGS SpibRegs;

__attribute__((noinit, location(SPIC_BASE))) volatile struct SPI_REGS SpicRegs;

__attribute__((noinit, location(SPID_BASE))) volatile struct SPI_REGS SpidRegs;

__attribute__((noinit, location(SPIE_BASE))) volatile struct SPI_REGS SpieRegs;

__attribute__((noinit, location(SSUCPU1AP_BASE))) volatile struct SSU_CPU1_AP_REGS SsuCpu1ApRegs;

__attribute__((noinit, location(SSUCPU1CFG_BASE))) volatile struct SSU_CPU1_CFG_REGS SsuCpu1CfgRegs;

__attribute__((noinit, location(SSUCPU2AP_BASE))) volatile struct SSU_CPU2_AP_REGS SsuCpu2ApRegs;

__attribute__((noinit, location(SSUCPU2CFG_BASE))) volatile struct SSU_CPU2_CFG_REGS SsuCpu2CfgRegs;

__attribute__((noinit, location(SSUCPU3AP_BASE))) volatile struct SSU_CPU3_AP_REGS SsuCpu3ApRegs;

__attribute__((noinit, location(SSUCPU3CFG_BASE))) volatile struct SSU_CPU3_CFG_REGS SsuCpu3CfgRegs;

__attribute__((noinit, location(SSUGEN_BASE))) volatile struct SSU_GEN_REGS SsuGenRegs;

__attribute__((noinit, location(SYNCBRIDGEMPU_BASE))) volatile struct SYNCBRIDGEMPU_REGS SyncBridgeMpuRegs;

__attribute__((noinit, location(UARTA_BASE))) volatile struct UART_REGS UartaRegs;

__attribute__((noinit, location(UARTB_BASE))) volatile struct UART_REGS UartbRegs;

__attribute__((noinit, location(UARTC_BASE))) volatile struct UART_REGS UartcRegs;

__attribute__((noinit, location(UARTD_BASE))) volatile struct UART_REGS UartdRegs;

__attribute__((noinit, location(UARTE_BASE))) volatile struct UART_REGS UarteRegs;

__attribute__((noinit, location(UARTF_BASE))) volatile struct UART_REGS UartfRegs;

__attribute__((noinit, location(WADI1BLK1CONFIG_BASE))) volatile struct WADI_CONFIG_REGS Wadi1Blk1ConfigRegs;

__attribute__((noinit, location(WADI1BLK2CONFIG_BASE))) volatile struct WADI_CONFIG_REGS Wadi1Blk2ConfigRegs;

__attribute__((noinit, location(WADI1BLK3CONFIG_BASE))) volatile struct WADI_CONFIG_REGS Wadi1Blk3ConfigRegs;

__attribute__((noinit, location(WADI1BLK4CONFIG_BASE))) volatile struct WADI_CONFIG_REGS Wadi1Blk4ConfigRegs;

__attribute__((noinit, location(WADI2BLK1CONFIG_BASE))) volatile struct WADI_CONFIG_REGS Wadi2Blk1ConfigRegs;

__attribute__((noinit, location(WADI2BLK2CONFIG_BASE))) volatile struct WADI_CONFIG_REGS Wadi2Blk2ConfigRegs;

__attribute__((noinit, location(WADI2BLK3CONFIG_BASE))) volatile struct WADI_CONFIG_REGS Wadi2Blk3ConfigRegs;

__attribute__((noinit, location(WADI2BLK4CONFIG_BASE))) volatile struct WADI_CONFIG_REGS Wadi2Blk4ConfigRegs;

__attribute__((noinit, location(WADI1OPERSSS_BASE))) volatile struct WADI_OPER_SSS_REGS Wadi1OperSssRegs;

__attribute__((noinit, location(WADI2OPERSSS_BASE))) volatile struct WADI_OPER_SSS_REGS Wadi2OperSssRegs;

__attribute__((noinit, location(WD_BASE))) volatile struct WD_REGS WdRegs;

__attribute__((noinit, location(XBAR_BASE))) volatile struct XBAR_REGS XbarRegs;

__attribute__((noinit, location(XINT_BASE))) volatile struct XINT_REGS XintRegs;



//===========================================================================
// End of file.
//===========================================================================


