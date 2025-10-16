/********************************************************************
*
* ESM BASEADDRESS. header file
*
* Copyright (C) 2025 Texas Instruments Incorporated.
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/
#ifndef SDLR_BASEADDRESS_H_
#define SDLR_BASEADDRESS_H_

#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// The following are defines for the base address of the memories and
// peripherals.
//
//*****************************************************************************
#define SDL_CPU1_ROM_BASE                        0x00000000U
#define SDL_CPU2_ROM_BASE                        0x00000000U
#define SDL_CPU3_ROM_BASE                        0x00000000U
#define SDL_M0_RAM_BASE                          0x20000000U
#define SDL_LDA7_RAM_BASE                        0x200E0000U
#define SDL_LDA6_RAM_BASE                        0x200E4000U
#define SDL_LDA5_RAM_BASE                        0x200E8000U
#define SDL_LDA4_RAM_BASE                        0x200EC000U
#define SDL_LDA3_RAM_BASE                        0x200F0000U
#define SDL_LDA2_RAM_BASE                        0x200F4000U
#define SDL_LDA1_RAM_BASE                        0x200F8000U
#define SDL_LDA0_RAM_BASE                        0x200FC000U
#define SDL_LPA0_RAM_BASE                        0x20100000U
#define SDL_LPA1_RAM_BASE                        0x20108000U
#define SDL_CPA0_RAM_BASE                        0x20110000U
#define SDL_CPA1_RAM_BASE                        0x20118000U
#define SDL_CDA0_RAM_BASE                        0x20120000U
#define SDL_CDA1_RAM_BASE                        0x20124000U
#define SDL_CDA2_RAM_BASE                        0x20128000U
#define SDL_CDA3_RAM_BASE                        0x2012C000U
#define SDL_CDA4_RAM_BASE                        0x20130000U
#define SDL_CDA5_RAM_BASE                        0x20134000U
#define SDL_CDA6_RAM_BASE                        0x20138000U
#define SDL_CDA7_RAM_BASE                        0x2013C000U
#define SDL_CDA8_RAM_BASE                        0x20140000U
#define SDL_CDA9_RAM_BASE                        0x20144000U
#define SDL_CDA10_RAM_BASE                       0x20148000U
#define SDL_CDA11_RAM_BASE                       0x2014C000U
#define SDL_C29CPURTINTSTACK_BASE                0x30008000U
#define SDL_C29CPUSECCALLSTACK_BASE              0x3000C000U
#define SDL_C29CPUSECURE_BASE                    0x3000D000U
#define SDL_C29CPUDIAG_BASE                      0x3000E000U
#define SDL_C29CPUSELFTEST_BASE                  0x3000F000U
#define SDL_CPUDLT_BASE                          0x30010000U
#define SDL_C29DEBUGSS_BASE                      0x30018000U
#define SDL_PIPE_BASE                            0x30020000U
#define SDL_ERAD_BASE                            0x30030000U
#define SDL_LCM_CPU_BASE                         0x30032000U
#define SDL_SSUGEN_BASE                          0x30080000U
#define SDL_SSUCPU1CFG_BASE                      0x30081000U
#define SDL_SSUCPU2CFG_BASE                      0x30082000U
#define SDL_SSUCPU3CFG_BASE                      0x30083000U
#define SDL_SSUCPU1AP_BASE                       0x30087000U
#define SDL_SSUCPU2AP_BASE                       0x30088000U
#define SDL_SSUCPU3AP_BASE                       0x30089000U
#define SDL_FLASHCONTROLLER1_BASE                0x30100000U
#define SDL_FLASHCONTROLLER2_BASE                0x30110000U
#define SDL_HSMERRORAGGREGATOR_BASE              0x30120000U
#define SDL_DEVCFG_BASE                          0x30180000U
#define SDL_ANALOGSUBSYS_BASE                    0x30182000U
#define SDL_GPIOCTRL_BASE                        0x30190000U
#define SDL_IPCCOUNTERREGS_BASE                  0x301B0000U
#define SDL_RTDMA1_BASE                          0x301C0000U
#define SDL_RTDMA1_DIAG_BASE                     0x301C0800U
#define SDL_RTDMA1_SELFTEST_BASE                 0x301C0C00U
#define SDL_RTDMA1_MPU_BASE                      0x301C1000U
#define SDL_RTDMA2_BASE                          0x301C8000U
#define SDL_RTDMA2_DIAG_BASE                     0x301C8800U
#define SDL_RTDMA2_SELFTEST_BASE                 0x301C8C00U
#define SDL_RTDMA2_MPU_BASE                      0x301C9000U
#define SDL_FRI1_BASE                            0x301D0000U
#define SDL_MEMSSLCFG_BASE                       0x301D8000U
#define SDL_MEMSSCCFG_BASE                       0x301D8400U
#define SDL_MEMSSMCFG_BASE                       0x301D8800U
#define SDL_MEMSSROMCFG_BASE                     0x301D8C00U
#define SDL_MEMSSMISCI_BASE                      0x301D8E00U
#define SDL_MEMSSROMPATCH_BASE                   0x301D9000U
#define SDL_SYNCBRIDGEMPU_BASE                   0x301E0000U
#define SDL_INPUTXBAR_BASE                       0x301E8000U
#define SDL_EPWMXBAR_BASE                        0x301E9000U
#define SDL_CLBXBAR_BASE                         0x301EA000U
#define SDL_OUTPUTXBAR_BASE                      0x301EB000U
#define SDL_MDLXBAR_BASE                         0x301EC000U
#define SDL_ICLXBAR_BASE                         0x301ED000U
#define SDL_LCM_DMA_BASE                         0x301F4000U
#define SDL_CPUSYS_BASE                          0x30200000U
#define SDL_CPUPERCFG_BASE                       0x30208000U
#define SDL_WD_BASE                              0x30208C00U
#define SDL_CPUTIMER0_BASE                       0x30218000U
#define SDL_CPUTIMER1_BASE                       0x30219000U
#define SDL_CPUTIMER2_BASE                       0x3021A000U
#define SDL_CPU1IPCSEND_BASE                     0x30220000U
#define SDL_CPU2IPCSEND_BASE                     0x30228000U
#define SDL_CPU3IPCSEND_BASE                     0x30230000U
#define SDL_CPU1IPCRCV_BASE                      0x30240000U
#define SDL_CPU2IPCRCV_BASE                      0x30248000U
#define SDL_CPU3IPCRCV_BASE                      0x30250000U
#define SDL_GPIODATA_BASE                        0x30268000U
#define SDL_GPIODATAREAD_BASE                    0x30269000U
#define SDL_XINT_BASE                            0x30270000U
#define SDL_DTHE_BASE                            0x30280000U
#define SDL_CRCS_BASE                            0x30281000U
#define SDL_CRCP_BASE                            0x30282000U
#define SDL_SHAS_BASE                            0x30284000U
#define SDL_SHAP_BASE                            0x30285000U
#define SDL_AESS_BASE                            0x30286000U
#define SDL_AESP_BASE                            0x30287000U
#define SDL_SM4_BASE                             0x30288000U
#define SDL_SM3_BASE                             0x30289000U
#define SDL_TRNG_BASE                            0x3028A000U
#define SDL_PKE_BASE                             0x30290000U
#define SDL_ESC_SS_BASE                          0x30388000U
#define SDL_ESC_SS_CONFIG_BASE                   0x30388200U
#define SDL_ADCARESULT_BASE                      0x303C0000U
#define SDL_ADCBRESULT_BASE                      0x303C1000U
#define SDL_ADCCRESULT_BASE                      0x303C2000U
#define SDL_ADCDRESULT_BASE                      0x303C3000U
#define SDL_ADCERESULT_BASE                      0x303C4000U
#define SDL_EMIF1_BASE                           0x30800000U

#define SDL_RTDMA1CH1_BASE_FRAME(i)              (0x60000000U + ((i) * 0x400000U))
#define SDL_RTDMA1CH2_BASE_FRAME(i)              (0x60001000U + ((i) * 0x400000U))
#define SDL_RTDMA1CH3_BASE_FRAME(i)              (0x60002000U + ((i) * 0x400000U))
#define SDL_RTDMA1CH4_BASE_FRAME(i)              (0x60003000U + ((i) * 0x400000U))
#define SDL_RTDMA1CH5_BASE_FRAME(i)              (0x60004000U + ((i) * 0x400000U))
#define SDL_RTDMA1CH6_BASE_FRAME(i)              (0x60005000U + ((i) * 0x400000U))
#define SDL_RTDMA1CH7_BASE_FRAME(i)              (0x60006000U + ((i) * 0x400000U))
#define SDL_RTDMA1CH8_BASE_FRAME(i)              (0x60007000U + ((i) * 0x400000U))
#define SDL_RTDMA1CH9_BASE_FRAME(i)              (0x60008000U + ((i) * 0x400000U))
#define SDL_RTDMA1CH10_BASE_FRAME(i)             (0x60009000U + ((i) * 0x400000U))
#define SDL_RTDMA2CH1_BASE_FRAME(i)              (0x60010000U + ((i) * 0x400000U))
#define SDL_RTDMA2CH2_BASE_FRAME(i)              (0x60011000U + ((i) * 0x400000U))
#define SDL_RTDMA2CH3_BASE_FRAME(i)              (0x60012000U + ((i) * 0x400000U))
#define SDL_RTDMA2CH4_BASE_FRAME(i)              (0x60013000U + ((i) * 0x400000U))
#define SDL_RTDMA2CH5_BASE_FRAME(i)              (0x60014000U + ((i) * 0x400000U))
#define SDL_RTDMA2CH6_BASE_FRAME(i)              (0x60015000U + ((i) * 0x400000U))
#define SDL_RTDMA2CH7_BASE_FRAME(i)              (0x60016000U + ((i) * 0x400000U))
#define SDL_RTDMA2CH8_BASE_FRAME(i)              (0x60017000U + ((i) * 0x400000U))
#define SDL_RTDMA2CH9_BASE_FRAME(i)              (0x60018000U + ((i) * 0x400000U))
#define SDL_RTDMA2CH10_BASE_FRAME(i)             (0x60019000U + ((i) * 0x400000U))
#define SDL_MCANA_DRIVER_BASE_FRAME(i)           (0x60020000U + ((i) * 0x400000U))
#define SDL_MCANSSA_BASE_FRAME(i)                (0x60024000U + ((i) * 0x400000U))
#define SDL_MCANA_BASE_FRAME(i)                  (0x60024600U + ((i) * 0x400000U))
#define SDL_MCANA_ERROR_BASE_FRAME(i)            (0x60024800U + ((i) * 0x400000U))
#define SDL_MCANB_DRIVER_BASE_FRAME(i)           (0x60028000U + ((i) * 0x400000U))
#define SDL_MCANBSS_BASE_FRAME(i)                (0x6002C000U + ((i) * 0x400000U))
#define SDL_MCANB_BASE_FRAME(i)                  (0x6002C600U + ((i) * 0x400000U))
#define SDL_MCANB_ERROR_BASE_FRAME(i)            (0x6002C800U + ((i) * 0x400000U))
#define SDL_MCANC_DRIVER_BASE_FRAME(i)           (0x60030000U + ((i) * 0x400000U))
#define SDL_MCANCSS_BASE_FRAME(i)                (0x60034000U + ((i) * 0x400000U))
#define SDL_MCANC_BASE_FRAME(i)                  (0x60034600U + ((i) * 0x400000U))
#define SDL_MCANC_ERROR_BASE_FRAME(i)            (0x60034800U + ((i) * 0x400000U))
#define SDL_MCAND_DRIVER_BASE_FRAME(i)           (0x60038000U + ((i) * 0x400000U))
#define SDL_MCANDSS_BASE_FRAME(i)                (0x6003C000U + ((i) * 0x400000U))
#define SDL_MCAND_BASE_FRAME(i)                  (0x6003C600U + ((i) * 0x400000U))
#define SDL_MCAND_ERROR_BASE_FRAME(i)            (0x6003C800U + ((i) * 0x400000U))
#define SDL_MCANE_DRIVER_BASE_FRAME(i)           (0x60040000U + ((i) * 0x400000U))
#define SDL_MCANESS_BASE_FRAME(i)                (0x60044000U + ((i) * 0x400000U))
#define SDL_MCANE_BASE_FRAME(i)                  (0x60044600U + ((i) * 0x400000U))
#define SDL_MCANE_ERROR_BASE_FRAME(i)            (0x60044800U + ((i) * 0x400000U))
#define SDL_MCANF_DRIVER_BASE_FRAME(i)           (0x60048000U + ((i) * 0x400000U))
#define SDL_MCANFSS_BASE_FRAME(i)                (0x6004C000U + ((i) * 0x400000U))
#define SDL_MCANF_BASE_FRAME(i)                  (0x6004C600U + ((i) * 0x400000U))
#define SDL_MCANF_ERROR_BASE_FRAME(i)            (0x6004C800U + ((i) * 0x400000U))
#define SDL_LINA_BASE_FRAME(i)                   (0x60060000U + ((i) * 0x400000U))
#define SDL_LINB_BASE_FRAME(i)                   (0x60061000U + ((i) * 0x400000U))
#define SDL_SENT1_BASE_FRAME(i)                  (0x60068000U + ((i) * 0x400000U))
#define SDL_SENT2_BASE_FRAME(i)                  (0x60069000U + ((i) * 0x400000U))
#define SDL_SENT3_BASE_FRAME(i)                  (0x6006A000U + ((i) * 0x400000U))
#define SDL_SENT4_BASE_FRAME(i)                  (0x6006B000U + ((i) * 0x400000U))
#define SDL_SENT5_BASE_FRAME(i)                  (0x6006C000U + ((i) * 0x400000U))
#define SDL_SENT6_BASE_FRAME(i)                  (0x6006D000U + ((i) * 0x400000U))
#define SDL_UARTA_WRITE_BASE_FRAME(i)            (0x60070000U + ((i) * 0x400000U))
#define SDL_UARTA_BASE_FRAME(i)                  (0x60070000U + ((i) * 0x400000U))
#define SDL_UARTB_WRITE_BASE_FRAME(i)            (0x60072000U + ((i) * 0x400000U))
#define SDL_UARTB_BASE_FRAME(i)                  (0x60072000U + ((i) * 0x400000U))
#define SDL_UARTC_WRITE_BASE_FRAME(i)            (0x60074000U + ((i) * 0x400000U))
#define SDL_UARTC_BASE_FRAME(i)                  (0x60074000U + ((i) * 0x400000U))
#define SDL_UARTD_WRITE_BASE_FRAME(i)            (0x60076000U + ((i) * 0x400000U))
#define SDL_UARTD_BASE_FRAME(i)                  (0x60076000U + ((i) * 0x400000U))
#define SDL_UARTE_WRITE_BASE_FRAME(i)            (0x60078000U + ((i) * 0x400000U))
#define SDL_UARTE_BASE_FRAME(i)                  (0x60078000U + ((i) * 0x400000U))
#define SDL_UARTF_WRITE_BASE_FRAME(i)            (0x6007A000U + ((i) * 0x400000U))
#define SDL_UARTF_BASE_FRAME(i)                  (0x6007A000U + ((i) * 0x400000U))
#define SDL_DCC1_BASE_FRAME(i)                   (0x60080000U + ((i) * 0x400000U))
#define SDL_DCC2_BASE_FRAME(i)                   (0x60081000U + ((i) * 0x400000U))
#define SDL_DCC3_BASE_FRAME(i)                   (0x60082000U + ((i) * 0x400000U))
#define SDL_ERRORAGGREGATOR_BASE_FRAME(i)        (0x6008C000U + ((i) * 0x400000U))
#define SDL_ESMCPU1_BASE_FRAME(i)                (0x60090000U + ((i) * 0x400000U))
#define SDL_ESMCPU2_BASE_FRAME(i)                (0x60091000U + ((i) * 0x400000U))
#define SDL_ESMCPU3_BASE_FRAME(i)                (0x60092000U + ((i) * 0x400000U))
#define SDL_ESMSYSTEM_BASE_FRAME(i)              (0x6009F000U + ((i) * 0x400000U))
#define SDL_ESMSAFETYAGG_BASE_FRAME(i)           (0x600A0000U + ((i) * 0x400000U))
#define SDL_WADI1BLK1CONFIG_BASE_FRAME(i)        (0x600B0000U + ((i) * 0x400000U))
#define SDL_WADI1BLK2CONFIG_BASE_FRAME(i)        (0x600B0100U + ((i) * 0x400000U))
#define SDL_WADI1BLK3CONFIG_BASE_FRAME(i)        (0x600B0200U + ((i) * 0x400000U))
#define SDL_WADI1BLK4CONFIG_BASE_FRAME(i)        (0x600B0300U + ((i) * 0x400000U))
#define SDL_WADI1OPERSSS_BASE_FRAME(i)           (0x600B1000U + ((i) * 0x400000U))
#define SDL_WADI2BLK1CONFIG_BASE_FRAME(i)        (0x600B2000U + ((i) * 0x400000U))
#define SDL_WADI2BLK2CONFIG_BASE_FRAME(i)        (0x600B2100U + ((i) * 0x400000U))
#define SDL_WADI2BLK3CONFIG_BASE_FRAME(i)        (0x600B2200U + ((i) * 0x400000U))
#define SDL_WADI2BLK4CONFIG_BASE_FRAME(i)        (0x600B2300U + ((i) * 0x400000U))
#define SDL_WADI2OPERSSS_BASE_FRAME(i)           (0x600B3000U + ((i) * 0x400000U))
#define SDL_OUTPUTXBAR1_FLAGS_BASE_FRAME(i)      (0x600C0000U + ((i) * 0x400000U))
#define SDL_OUTPUTXBAR2_FLAGS_BASE_FRAME(i)      (0x600C1000U + ((i) * 0x400000U))
#define SDL_OUTPUTXBAR3_FLAGS_BASE_FRAME(i)      (0x600C2000U + ((i) * 0x400000U))
#define SDL_OUTPUTXBAR4_FLAGS_BASE_FRAME(i)      (0x600C3000U + ((i) * 0x400000U))
#define SDL_OUTPUTXBAR5_FLAGS_BASE_FRAME(i)      (0x600C4000U + ((i) * 0x400000U))
#define SDL_OUTPUTXBAR6_FLAGS_BASE_FRAME(i)      (0x600C5000U + ((i) * 0x400000U))
#define SDL_OUTPUTXBAR7_FLAGS_BASE_FRAME(i)      (0x600C6000U + ((i) * 0x400000U))
#define SDL_OUTPUTXBAR8_FLAGS_BASE_FRAME(i)      (0x600C7000U + ((i) * 0x400000U))
#define SDL_OUTPUTXBAR9_FLAGS_BASE_FRAME(i)      (0x600C8000U + ((i) * 0x400000U))
#define SDL_OUTPUTXBAR10_FLAGS_BASE_FRAME(i)     (0x600C9000U + ((i) * 0x400000U))
#define SDL_OUTPUTXBAR11_FLAGS_BASE_FRAME(i)     (0x600CA000U + ((i) * 0x400000U))
#define SDL_OUTPUTXBAR12_FLAGS_BASE_FRAME(i)     (0x600CB000U + ((i) * 0x400000U))
#define SDL_OUTPUTXBAR13_FLAGS_BASE_FRAME(i)     (0x600CC000U + ((i) * 0x400000U))
#define SDL_OUTPUTXBAR14_FLAGS_BASE_FRAME(i)     (0x600CD000U + ((i) * 0x400000U))
#define SDL_OUTPUTXBAR15_FLAGS_BASE_FRAME(i)     (0x600CE000U + ((i) * 0x400000U))
#define SDL_OUTPUTXBAR16_FLAGS_BASE_FRAME(i)     (0x600CF000U + ((i) * 0x400000U))
#define SDL_XBAR_BASE_FRAME(i)                   (0x600E0000U + ((i) * 0x400000U))
#define SDL_CPU1DLTFIFO_BASE_FRAME(i)            (0x600F8000U + ((i) * 0x400000U))
#define SDL_CPU2DLTFIFO_BASE_FRAME(i)            (0x600FA000U + ((i) * 0x400000U))
#define SDL_CPU3DLTFIFO_BASE_FRAME(i)            (0x600FC000U + ((i) * 0x400000U))
#define SDL_EPWM1_BASE_FRAME(i)                  (0x70000000U + ((i) * 0x400000U))
#define SDL_EPWM1XCMP_BASE_FRAME(i)              (0x70000400U + ((i) * 0x400000U))
#define SDL_EPWM1DE_BASE_FRAME(i)                (0x70000800U + ((i) * 0x400000U))
#define SDL_EPWM1MINDBLUT_BASE_FRAME(i)          (0x70000C00U + ((i) * 0x400000U))
#define SDL_EPWM2_BASE_FRAME(i)                  (0x70001000U + ((i) * 0x400000U))
#define SDL_EPWM2XCMP_BASE_FRAME(i)              (0x70001400U + ((i) * 0x400000U))
#define SDL_EPWM2DE_BASE_FRAME(i)                (0x70001800U + ((i) * 0x400000U))
#define SDL_EPWM2MINDBLUT_BASE_FRAME(i)          (0x70001C00U + ((i) * 0x400000U))
#define SDL_EPWM3_BASE_FRAME(i)                  (0x70002000U + ((i) * 0x400000U))
#define SDL_EPWM3XCMP_BASE_FRAME(i)              (0x70002400U + ((i) * 0x400000U))
#define SDL_EPWM3DE_BASE_FRAME(i)                (0x70002800U + ((i) * 0x400000U))
#define SDL_EPWM3MINDBLUT_BASE_FRAME(i)          (0x70002C00U + ((i) * 0x400000U))
#define SDL_EPWM4_BASE_FRAME(i)                  (0x70003000U + ((i) * 0x400000U))
#define SDL_EPWM4XCMP_BASE_FRAME(i)              (0x70003400U + ((i) * 0x400000U))
#define SDL_EPWM4DE_BASE_FRAME(i)                (0x70003800U + ((i) * 0x400000U))
#define SDL_EPWM4MINDBLUT_BASE_FRAME(i)          (0x70003C00U + ((i) * 0x400000U))
#define SDL_EPWM5_BASE_FRAME(i)                  (0x70004000U + ((i) * 0x400000U))
#define SDL_EPWM5XCMP_BASE_FRAME(i)              (0x70004400U + ((i) * 0x400000U))
#define SDL_EPWM5DE_BASE_FRAME(i)                (0x70004800U + ((i) * 0x400000U))
#define SDL_EPWM5MINDBLUT_BASE_FRAME(i)          (0x70004C00U + ((i) * 0x400000U))
#define SDL_EPWM6_BASE_FRAME(i)                  (0x70005000U + ((i) * 0x400000U))
#define SDL_EPWM6XCMP_BASE_FRAME(i)              (0x70005400U + ((i) * 0x400000U))
#define SDL_EPWM6DE_BASE_FRAME(i)                (0x70005800U + ((i) * 0x400000U))
#define SDL_EPWM6MINDBLUT_BASE_FRAME(i)          (0x70005C00U + ((i) * 0x400000U))
#define SDL_EPWM7_BASE_FRAME(i)                  (0x70006000U + ((i) * 0x400000U))
#define SDL_EPWM7XCMP_BASE_FRAME(i)              (0x70006400U + ((i) * 0x400000U))
#define SDL_EPWM7DE_BASE_FRAME(i)                (0x70006800U + ((i) * 0x400000U))
#define SDL_EPWM7MINDBLUT_BASE_FRAME(i)          (0x70006C00U + ((i) * 0x400000U))
#define SDL_EPWM8_BASE_FRAME(i)                  (0x70007000U + ((i) * 0x400000U))
#define SDL_EPWM8XCMP_BASE_FRAME(i)              (0x70007400U + ((i) * 0x400000U))
#define SDL_EPWM8DE_BASE_FRAME(i)                (0x70007800U + ((i) * 0x400000U))
#define SDL_EPWM8MINDBLUT_BASE_FRAME(i)          (0x70007C00U + ((i) * 0x400000U))
#define SDL_EPWM9_BASE_FRAME(i)                  (0x70008000U + ((i) * 0x400000U))
#define SDL_EPWM9XCMP_BASE_FRAME(i)              (0x70008400U + ((i) * 0x400000U))
#define SDL_EPWM9DE_BASE_FRAME(i)                (0x70008800U + ((i) * 0x400000U))
#define SDL_EPWM9MINDBLUT_BASE_FRAME(i)          (0x70008C00U + ((i) * 0x400000U))
#define SDL_EPWM10_BASE_FRAME(i)                 (0x70009000U + ((i) * 0x400000U))
#define SDL_EPWM10XCMP_BASE_FRAME(i)             (0x70009400U + ((i) * 0x400000U))
#define SDL_EPWM10DE_BASE_FRAME(i)               (0x70009800U + ((i) * 0x400000U))
#define SDL_EPWM10MINDBLUT_BASE_FRAME(i)         (0x70009C00U + ((i) * 0x400000U))
#define SDL_EPWM11_BASE_FRAME(i)                 (0x7000A000U + ((i) * 0x400000U))
#define SDL_EPWM11XCMP_BASE_FRAME(i)             (0x7000A400U + ((i) * 0x400000U))
#define SDL_EPWM11DE_BASE_FRAME(i)               (0x7000A800U + ((i) * 0x400000U))
#define SDL_EPWM11MINDBLUT_BASE_FRAME(i)         (0x7000AC00U + ((i) * 0x400000U))
#define SDL_EPWM12_BASE_FRAME(i)                 (0x7000B000U + ((i) * 0x400000U))
#define SDL_EPWM12XCMP_BASE_FRAME(i)             (0x7000B400U + ((i) * 0x400000U))
#define SDL_EPWM12DE_BASE_FRAME(i)               (0x7000B800U + ((i) * 0x400000U))
#define SDL_EPWM12MINDBLUT_BASE_FRAME(i)         (0x7000BC00U + ((i) * 0x400000U))
#define SDL_EPWM13_BASE_FRAME(i)                 (0x7000C000U + ((i) * 0x400000U))
#define SDL_EPWM13XCMP_BASE_FRAME(i)             (0x7000C400U + ((i) * 0x400000U))
#define SDL_EPWM13DE_BASE_FRAME(i)               (0x7000C800U + ((i) * 0x400000U))
#define SDL_EPWM13MINDBLUT_BASE_FRAME(i)         (0x7000CC00U + ((i) * 0x400000U))
#define SDL_EPWM14_BASE_FRAME(i)                 (0x7000D000U + ((i) * 0x400000U))
#define SDL_EPWM14XCMP_BASE_FRAME(i)             (0x7000D400U + ((i) * 0x400000U))
#define SDL_EPWM14DE_BASE_FRAME(i)               (0x7000D800U + ((i) * 0x400000U))
#define SDL_EPWM14MINDBLUT_BASE_FRAME(i)         (0x7000DC00U + ((i) * 0x400000U))
#define SDL_EPWM15_BASE_FRAME(i)                 (0x7000E000U + ((i) * 0x400000U))
#define SDL_EPWM15XCMP_BASE_FRAME(i)             (0x7000E400U + ((i) * 0x400000U))
#define SDL_EPWM15DE_BASE_FRAME(i)               (0x7000E800U + ((i) * 0x400000U))
#define SDL_EPWM15MINDBLUT_BASE_FRAME(i)         (0x7000EC00U + ((i) * 0x400000U))
#define SDL_EPWM16_BASE_FRAME(i)                 (0x7000F000U + ((i) * 0x400000U))
#define SDL_EPWM16XCMP_BASE_FRAME(i)             (0x7000F400U + ((i) * 0x400000U))
#define SDL_EPWM16DE_BASE_FRAME(i)               (0x7000F800U + ((i) * 0x400000U))
#define SDL_EPWM16MINDBLUT_BASE_FRAME(i)         (0x7000FC00U + ((i) * 0x400000U))
#define SDL_EPWM17_BASE_FRAME(i)                 (0x70010000U + ((i) * 0x400000U))
#define SDL_EPWM17XCMP_BASE_FRAME(i)             (0x70010400U + ((i) * 0x400000U))
#define SDL_EPWM17DE_BASE_FRAME(i)               (0x70010800U + ((i) * 0x400000U))
#define SDL_EPWM17MINDBLUT_BASE_FRAME(i)         (0x70010C00U + ((i) * 0x400000U))
#define SDL_EPWM18_BASE_FRAME(i)                 (0x70011000U + ((i) * 0x400000U))
#define SDL_EPWM18XCMP_BASE_FRAME(i)             (0x70011400U + ((i) * 0x400000U))
#define SDL_EPWM18DE_BASE_FRAME(i)               (0x70011800U + ((i) * 0x400000U))
#define SDL_EPWM18MINDBLUT_BASE_FRAME(i)         (0x70011C00U + ((i) * 0x400000U))
#define SDL_EPWM1XLINK_BASE_FRAME(i)             (0x70040000U + ((i) * 0x400000U))
#define SDL_EPWM1XCMPXLINK_BASE_FRAME(i)         (0x70040400U + ((i) * 0x400000U))
#define SDL_EPWM1DEXLINK_BASE_FRAME(i)           (0x70040800U + ((i) * 0x400000U))
#define SDL_EPWM1MINDBLUTXLINK_BASE_FRAME(i)     (0x70040C00U + ((i) * 0x400000U))
#define SDL_EPWM2XLINK_BASE_FRAME(i)             (0x70041000U + ((i) * 0x400000U))
#define SDL_EPWM2XCMPXLINK_BASE_FRAME(i)         (0x70041400U + ((i) * 0x400000U))
#define SDL_EPWM2DEXLINK_BASE_FRAME(i)           (0x70041800U + ((i) * 0x400000U))
#define SDL_EPWM2MINDBLUTXLINK_BASE_FRAME(i)     (0x70041C00U + ((i) * 0x400000U))
#define SDL_EPWM3XLINK_BASE_FRAME(i)             (0x70042000U + ((i) * 0x400000U))
#define SDL_EPWM3XCMPXLINK_BASE_FRAME(i)         (0x70042400U + ((i) * 0x400000U))
#define SDL_EPWM3DEXLINK_BASE_FRAME(i)           (0x70042800U + ((i) * 0x400000U))
#define SDL_EPWM3MINDBLUTXLINK_BASE_FRAME(i)     (0x70042C00U + ((i) * 0x400000U))
#define SDL_EPWM4XLINK_BASE_FRAME(i)             (0x70043000U + ((i) * 0x400000U))
#define SDL_EPWM4XCMPXLINK_BASE_FRAME(i)         (0x70043400U + ((i) * 0x400000U))
#define SDL_EPWM4DEXLINK_BASE_FRAME(i)           (0x70043800U + ((i) * 0x400000U))
#define SDL_EPWM4MINDBLUTXLINK_BASE_FRAME(i)     (0x70043C00U + ((i) * 0x400000U))
#define SDL_EPWM5XLINK_BASE_FRAME(i)             (0x70044000U + ((i) * 0x400000U))
#define SDL_EPWM5XCMPXLINK_BASE_FRAME(i)         (0x70044400U + ((i) * 0x400000U))
#define SDL_EPWM5DEXLINK_BASE_FRAME(i)           (0x70044800U + ((i) * 0x400000U))
#define SDL_EPWM5MINDBLUTXLINK_BASE_FRAME(i)     (0x70044C00U + ((i) * 0x400000U))
#define SDL_EPWM6XLINK_BASE_FRAME(i)             (0x70045000U + ((i) * 0x400000U))
#define SDL_EPWM6XCMPXLINK_BASE_FRAME(i)         (0x70045400U + ((i) * 0x400000U))
#define SDL_EPWM6DEXLINK_BASE_FRAME(i)           (0x70045800U + ((i) * 0x400000U))
#define SDL_EPWM6MINDBLUTXLINK_BASE_FRAME(i)     (0x70045C00U + ((i) * 0x400000U))
#define SDL_EPWM7XLINK_BASE_FRAME(i)             (0x70046000U + ((i) * 0x400000U))
#define SDL_EPWM7XCMPXLINK_BASE_FRAME(i)         (0x70046400U + ((i) * 0x400000U))
#define SDL_EPWM7DEXLINK_BASE_FRAME(i)           (0x70046800U + ((i) * 0x400000U))
#define SDL_EPWM7MINDBLUTXLINK_BASE_FRAME(i)     (0x70046C00U + ((i) * 0x400000U))
#define SDL_EPWM8XLINK_BASE_FRAME(i)             (0x70047000U + ((i) * 0x400000U))
#define SDL_EPWM8XCMPXLINK_BASE_FRAME(i)         (0x70047400U + ((i) * 0x400000U))
#define SDL_EPWM8DEXLINK_BASE_FRAME(i)           (0x70047800U + ((i) * 0x400000U))
#define SDL_EPWM8MINDBLUTXLINK_BASE_FRAME(i)     (0x70047C00U + ((i) * 0x400000U))
#define SDL_EPWM9XLINK_BASE_FRAME(i)             (0x70048000U + ((i) * 0x400000U))
#define SDL_EPWM9XCMPXLINK_BASE_FRAME(i)         (0x70048400U + ((i) * 0x400000U))
#define SDL_EPWM9DEXLINK_BASE_FRAME(i)           (0x70048800U + ((i) * 0x400000U))
#define SDL_EPWM9MINDBLUTXLINK_BASE_FRAME(i)     (0x70048C00U + ((i) * 0x400000U))
#define SDL_EPWM10XLINK_BASE_FRAME(i)            (0x70049000U + ((i) * 0x400000U))
#define SDL_EPWM10XCMPXLINK_BASE_FRAME(i)        (0x70049400U + ((i) * 0x400000U))
#define SDL_EPWM10DEXLINK_BASE_FRAME(i)          (0x70049800U + ((i) * 0x400000U))
#define SDL_EPWM10MINDBLUTXLINK_BASE_FRAME(i)    (0x70049C00U + ((i) * 0x400000U))
#define SDL_EPWM11XLINK_BASE_FRAME(i)            (0x7004A000U + ((i) * 0x400000U))
#define SDL_EPWM11XCMPXLINK_BASE_FRAME(i)        (0x7004A400U + ((i) * 0x400000U))
#define SDL_EPWM11DEXLINK_BASE_FRAME(i)          (0x7004A800U + ((i) * 0x400000U))
#define SDL_EPWM11MINDBLUTXLINK_BASE_FRAME(i)    (0x7004AC00U + ((i) * 0x400000U))
#define SDL_EPWM12XLINK_BASE_FRAME(i)            (0x7004B000U + ((i) * 0x400000U))
#define SDL_EPWM12XCMPXLINK_BASE_FRAME(i)        (0x7004B400U + ((i) * 0x400000U))
#define SDL_EPWM12DEXLINK_BASE_FRAME(i)          (0x7004B800U + ((i) * 0x400000U))
#define SDL_EPWM12MINDBLUTXLINK_BASE_FRAME(i)    (0x7004BC00U + ((i) * 0x400000U))
#define SDL_EPWM13XLINK_BASE_FRAME(i)            (0x7004C000U + ((i) * 0x400000U))
#define SDL_EPWM13XCMPXLINK_BASE_FRAME(i)        (0x7004C400U + ((i) * 0x400000U))
#define SDL_EPWM13DEXLINK_BASE_FRAME(i)          (0x7004C800U + ((i) * 0x400000U))
#define SDL_EPWM13MINDBLUTXLINK_BASE_FRAME(i)    (0x7004CC00U + ((i) * 0x400000U))
#define SDL_EPWM14XLINK_BASE_FRAME(i)            (0x7004D000U + ((i) * 0x400000U))
#define SDL_EPWM14XCMPXLINK_BASE_FRAME(i)        (0x7004D400U + ((i) * 0x400000U))
#define SDL_EPWM14DEXLINK_BASE_FRAME(i)          (0x7004D800U + ((i) * 0x400000U))
#define SDL_EPWM14MINDBLUTXLINK_BASE_FRAME(i)    (0x7004DC00U + ((i) * 0x400000U))
#define SDL_EPWM15XLINK_BASE_FRAME(i)            (0x7004E000U + ((i) * 0x400000U))
#define SDL_EPWM15XCMPXLINK_BASE_FRAME(i)        (0x7004E400U + ((i) * 0x400000U))
#define SDL_EPWM15DEXLINK_BASE_FRAME(i)          (0x7004E800U + ((i) * 0x400000U))
#define SDL_EPWM15MINDBLUTXLINK_BASE_FRAME(i)    (0x7004EC00U + ((i) * 0x400000U))
#define SDL_EPWM16XLINK_BASE_FRAME(i)            (0x7004F000U + ((i) * 0x400000U))
#define SDL_EPWM16XCMPXLINK_BASE_FRAME(i)        (0x7004F400U + ((i) * 0x400000U))
#define SDL_EPWM16DEXLINK_BASE_FRAME(i)          (0x7004F800U + ((i) * 0x400000U))
#define SDL_EPWM16MINDBLUTXLINK_BASE_FRAME(i)    (0x7004FC00U + ((i) * 0x400000U))
#define SDL_EPWM17XLINK_BASE_FRAME(i)            (0x70050000U + ((i) * 0x400000U))
#define SDL_EPWM17XCMPXLINK_BASE_FRAME(i)        (0x70050400U + ((i) * 0x400000U))
#define SDL_EPWM17DEXLINK_BASE_FRAME(i)          (0x70050800U + ((i) * 0x400000U))
#define SDL_EPWM17MINDBLUTXLINK_BASE_FRAME(i)    (0x70050C00U + ((i) * 0x400000U))
#define SDL_EPWM18XLINK_BASE_FRAME(i)            (0x70051000U + ((i) * 0x400000U))
#define SDL_EPWM18XCMPXLINK_BASE_FRAME(i)        (0x70051400U + ((i) * 0x400000U))
#define SDL_EPWM18DEXLINK_BASE_FRAME(i)          (0x70051800U + ((i) * 0x400000U))
#define SDL_EPWM18MINDBLUTXLINK_BASE_FRAME(i)    (0x70051C00U + ((i) * 0x400000U))
#define SDL_HRPWMCAL1_BASE_FRAME(i)              (0x70080000U + ((i) * 0x400000U))
#define SDL_HRPWMCAL2_BASE_FRAME(i)              (0x70081000U + ((i) * 0x400000U))
#define SDL_HRPWMCAL3_BASE_FRAME(i)              (0x70082000U + ((i) * 0x400000U))
#define SDL_EQEP1_BASE_FRAME(i)                  (0x70088000U + ((i) * 0x400000U))
#define SDL_EQEP2_BASE_FRAME(i)                  (0x70089000U + ((i) * 0x400000U))
#define SDL_EQEP3_BASE_FRAME(i)                  (0x7008A000U + ((i) * 0x400000U))
#define SDL_EQEP4_BASE_FRAME(i)                  (0x7008B000U + ((i) * 0x400000U))
#define SDL_EQEP5_BASE_FRAME(i)                  (0x7008C000U + ((i) * 0x400000U))
#define SDL_EQEP6_BASE_FRAME(i)                  (0x7008D000U + ((i) * 0x400000U))
#define SDL_SDFM1_BASE_FRAME(i)                  (0x70090000U + ((i) * 0x400000U))
#define SDL_SDFM2_BASE_FRAME(i)                  (0x70091000U + ((i) * 0x400000U))
#define SDL_SDFM3_BASE_FRAME(i)                  (0x70092000U + ((i) * 0x400000U))
#define SDL_SDFM4_BASE_FRAME(i)                  (0x70093000U + ((i) * 0x400000U))
#define SDL_ADCA_BASE_FRAME(i)                   (0x700A0000U + ((i) * 0x400000U))
#define SDL_ADCB_BASE_FRAME(i)                   (0x700A1000U + ((i) * 0x400000U))
#define SDL_ADCC_BASE_FRAME(i)                   (0x700A2000U + ((i) * 0x400000U))
#define SDL_ADCD_BASE_FRAME(i)                   (0x700A3000U + ((i) * 0x400000U))
#define SDL_ADCE_BASE_FRAME(i)                   (0x700A4000U + ((i) * 0x400000U))
#define SDL_ADCSAFETYCHECK1_BASE_FRAME(i)        (0x700B0000U + ((i) * 0x400000U))
#define SDL_ADCSAFETYCHECK2_BASE_FRAME(i)        (0x700B1000U + ((i) * 0x400000U))
#define SDL_ADCSAFETYCHECK3_BASE_FRAME(i)        (0x700B2000U + ((i) * 0x400000U))
#define SDL_ADCSAFETYCHECK4_BASE_FRAME(i)        (0x700B3000U + ((i) * 0x400000U))
#define SDL_ADCSAFETYCHECK5_BASE_FRAME(i)        (0x700B4000U + ((i) * 0x400000U))
#define SDL_ADCSAFETYCHECK6_BASE_FRAME(i)        (0x700B5000U + ((i) * 0x400000U))
#define SDL_ADCSAFETYCHECK7_BASE_FRAME(i)        (0x700B6000U + ((i) * 0x400000U))
#define SDL_ADCSAFETYCHECK8_BASE_FRAME(i)        (0x700B7000U + ((i) * 0x400000U))
#define SDL_ADCSAFETYCHECK9_BASE_FRAME(i)        (0x700B8000U + ((i) * 0x400000U))
#define SDL_ADCSAFETYCHECK10_BASE_FRAME(i)       (0x700B9000U + ((i) * 0x400000U))
#define SDL_ADCSAFETYCHECKINTEVT1_BASE_FRAME(i)  (0x700C0000U + ((i) * 0x400000U))
#define SDL_ADCSAFETYCHECKINTEVT2_BASE_FRAME(i)  (0x700C1000U + ((i) * 0x400000U))
#define SDL_ADCSAFETYCHECKINTEVT3_BASE_FRAME(i)  (0x700C2000U + ((i) * 0x400000U))
#define SDL_ADCGLOBAL_BASE_FRAME(i)              (0x700C8000U + ((i) * 0x400000U))
#define SDL_DACA_BASE_FRAME(i)                   (0x700D0000U + ((i) * 0x400000U))
#define SDL_DACB_BASE_FRAME(i)                   (0x700D1000U + ((i) * 0x400000U))
#define SDL_CMPSS1_BASE_FRAME(i)                 (0x700E0000U + ((i) * 0x400000U))
#define SDL_CMPSS2_BASE_FRAME(i)                 (0x700E1000U + ((i) * 0x400000U))
#define SDL_CMPSS3_BASE_FRAME(i)                 (0x700E2000U + ((i) * 0x400000U))
#define SDL_CMPSS4_BASE_FRAME(i)                 (0x700E3000U + ((i) * 0x400000U))
#define SDL_CMPSS5_BASE_FRAME(i)                 (0x700E4000U + ((i) * 0x400000U))
#define SDL_CMPSS6_BASE_FRAME(i)                 (0x700E5000U + ((i) * 0x400000U))
#define SDL_CMPSS7_BASE_FRAME(i)                 (0x700E6000U + ((i) * 0x400000U))
#define SDL_CMPSS8_BASE_FRAME(i)                 (0x700E7000U + ((i) * 0x400000U))
#define SDL_CMPSS9_BASE_FRAME(i)                 (0x700E8000U + ((i) * 0x400000U))
#define SDL_CMPSS10_BASE_FRAME(i)                (0x700E9000U + ((i) * 0x400000U))
#define SDL_CMPSS11_BASE_FRAME(i)                (0x700EA000U + ((i) * 0x400000U))
#define SDL_CMPSS12_BASE_FRAME(i)                (0x700EB000U + ((i) * 0x400000U))
#define SDL_ECAP1_BASE_FRAME(i)                  (0x70100000U + ((i) * 0x400000U))
#define SDL_ECAP1SIGNALMONITORING_BASE_FRAME(i)  (0x70100080U + ((i) * 0x400000U))
#define SDL_ECAP2_BASE_FRAME(i)                  (0x70101000U + ((i) * 0x400000U))
#define SDL_ECAP2SIGNALMONITORING_BASE_FRAME(i)  (0x70101080U + ((i) * 0x400000U))
#define SDL_ECAP3_BASE_FRAME(i)                  (0x70102000U + ((i) * 0x400000U))
#define SDL_ECAP3SIGNALMONITORING_BASE_FRAME(i)  (0x70102080U + ((i) * 0x400000U))
#define SDL_ECAP4_BASE_FRAME(i)                  (0x70103000U + ((i) * 0x400000U))
#define SDL_ECAP4SIGNALMONITORING_BASE_FRAME(i)  (0x70103080U + ((i) * 0x400000U))
#define SDL_ECAP5_BASE_FRAME(i)                  (0x70104000U + ((i) * 0x400000U))
#define SDL_HRCAP5_BASE_FRAME(i)                 (0x70104040U + ((i) * 0x400000U))
#define SDL_ECAP5SIGNALMONITORING_BASE_FRAME(i)  (0x70104080U + ((i) * 0x400000U))
#define SDL_ECAP6_BASE_FRAME(i)                  (0x70105000U + ((i) * 0x400000U))
#define SDL_HRCAP6_BASE_FRAME(i)                 (0x70105040U + ((i) * 0x400000U))
#define SDL_ECAP6SIGNALMONITORING_BASE_FRAME(i)  (0x70105080U + ((i) * 0x400000U))
#define SDL_CLB1_BASE_FRAME(i)                   (0x70120000U + ((i) * 0x400000U))
#define SDL_CLB1_LOGICCFG_BASE_FRAME(i)          (0x70120000U + ((i) * 0x400000U))
#define SDL_CLB1_LOGICCTRL_BASE_FRAME(i)         (0x70120200U + ((i) * 0x400000U))
#define SDL_CLB1_DATAEXCH_BASE_FRAME(i)          (0x70120300U + ((i) * 0x400000U))
#define SDL_CLB2_BASE_FRAME(i)                   (0x70121000U + ((i) * 0x400000U))
#define SDL_CLB2_LOGICCFG_BASE_FRAME(i)          (0x70121000U + ((i) * 0x400000U))
#define SDL_CLB2_LOGICCTRL_BASE_FRAME(i)         (0x70121200U + ((i) * 0x400000U))
#define SDL_CLB2_DATAEXCH_BASE_FRAME(i)          (0x70121300U + ((i) * 0x400000U))
#define SDL_CLB3_BASE_FRAME(i)                   (0x70122000U + ((i) * 0x400000U))
#define SDL_CLB3_LOGICCFG_BASE_FRAME(i)          (0x70122000U + ((i) * 0x400000U))
#define SDL_CLB3_LOGICCTRL_BASE_FRAME(i)         (0x70122200U + ((i) * 0x400000U))
#define SDL_CLB3_DATAEXCH_BASE_FRAME(i)          (0x70122300U + ((i) * 0x400000U))
#define SDL_CLB4_BASE_FRAME(i)                   (0x70123000U + ((i) * 0x400000U))
#define SDL_CLB4_LOGICCFG_BASE_FRAME(i)          (0x70123000U + ((i) * 0x400000U))
#define SDL_CLB4_LOGICCTRL_BASE_FRAME(i)         (0x70123200U + ((i) * 0x400000U))
#define SDL_CLB4_DATAEXCH_BASE_FRAME(i)          (0x70123300U + ((i) * 0x400000U))
#define SDL_CLB5_BASE_FRAME(i)                   (0x70124000U + ((i) * 0x400000U))
#define SDL_CLB5_LOGICCFG_BASE_FRAME(i)          (0x70124000U + ((i) * 0x400000U))
#define SDL_CLB5_LOGICCTRL_BASE_FRAME(i)         (0x70124200U + ((i) * 0x400000U))
#define SDL_CLB5_DATAEXCH_BASE_FRAME(i)          (0x70124300U + ((i) * 0x400000U))
#define SDL_CLB6_BASE_FRAME(i)                   (0x70125000U + ((i) * 0x400000U))
#define SDL_CLB6_LOGICCFG_BASE_FRAME(i)          (0x70125000U + ((i) * 0x400000U))
#define SDL_CLB6_LOGICCTRL_BASE_FRAME(i)         (0x70125200U + ((i) * 0x400000U))
#define SDL_CLB6_DATAEXCH_BASE_FRAME(i)          (0x70125300U + ((i) * 0x400000U))
#define SDL_PMBUSA_BASE_FRAME(i)                 (0x70148000U + ((i) * 0x400000U))
#define SDL_I2CA_BASE_FRAME(i)                   (0x70150000U + ((i) * 0x400000U))
#define SDL_I2CB_BASE_FRAME(i)                   (0x70151000U + ((i) * 0x400000U))
#define SDL_SPIA_BASE_FRAME(i)                   (0x70158000U + ((i) * 0x400000U))
#define SDL_SPIB_BASE_FRAME(i)                   (0x70159000U + ((i) * 0x400000U))
#define SDL_SPIC_BASE_FRAME(i)                   (0x7015A000U + ((i) * 0x400000U))
#define SDL_SPID_BASE_FRAME(i)                   (0x7015B000U + ((i) * 0x400000U))
#define SDL_SPIE_BASE_FRAME(i)                   (0x7015C000U + ((i) * 0x400000U))
#define SDL_FSITXA_BASE_FRAME(i)                 (0x70180000U + ((i) * 0x400000U))
#define SDL_FSITXB_BASE_FRAME(i)                 (0x70181000U + ((i) * 0x400000U))
#define SDL_FSITXC_BASE_FRAME(i)                 (0x70182000U + ((i) * 0x400000U))
#define SDL_FSITXD_BASE_FRAME(i)                 (0x70183000U + ((i) * 0x400000U))
#define SDL_FSIRXA_BASE_FRAME(i)                 (0x70188000U + ((i) * 0x400000U))
#define SDL_FSIRXB_BASE_FRAME(i)                 (0x70189000U + ((i) * 0x400000U))
#define SDL_FSIRXC_BASE_FRAME(i)                 (0x7018A000U + ((i) * 0x400000U))
#define SDL_FSIRXD_BASE_FRAME(i)                 (0x7018B000U + ((i) * 0x400000U))
#define SDL_EPG_BASE_FRAME(i)                    (0x701C0000U + ((i) * 0x400000U))
#define SDL_EPGMUX_BASE_FRAME(i)                 (0x701C0200U + ((i) * 0x400000U))


#ifndef SDL_RTDMA1CH1_BASE
    #define SDL_RTDMA1CH1_BASE                   SDL_RTDMA1CH1_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA1CH2_BASE
    #define SDL_RTDMA1CH2_BASE                   SDL_RTDMA1CH2_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA1CH3_BASE
    #define SDL_RTDMA1CH3_BASE                   SDL_RTDMA1CH3_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA1CH4_BASE
    #define SDL_RTDMA1CH4_BASE                   SDL_RTDMA1CH4_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA1CH5_BASE
    #define SDL_RTDMA1CH5_BASE                   SDL_RTDMA1CH5_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA1CH6_BASE
    #define SDL_RTDMA1CH6_BASE                   SDL_RTDMA1CH6_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA1CH7_BASE
    #define SDL_RTDMA1CH7_BASE                   SDL_RTDMA1CH7_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA1CH8_BASE
    #define SDL_RTDMA1CH8_BASE                   SDL_RTDMA1CH8_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA1CH9_BASE
    #define SDL_RTDMA1CH9_BASE                   SDL_RTDMA1CH9_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA1CH10_BASE
    #define SDL_RTDMA1CH10_BASE                  SDL_RTDMA1CH10_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA2CH1_BASE
    #define SDL_RTDMA2CH1_BASE                   SDL_RTDMA2CH1_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA2CH2_BASE
    #define SDL_RTDMA2CH2_BASE                   SDL_RTDMA2CH2_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA2CH3_BASE
    #define SDL_RTDMA2CH3_BASE                   SDL_RTDMA2CH3_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA2CH4_BASE
    #define SDL_RTDMA2CH4_BASE                   SDL_RTDMA2CH4_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA2CH5_BASE
    #define SDL_RTDMA2CH5_BASE                   SDL_RTDMA2CH5_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA2CH6_BASE
    #define SDL_RTDMA2CH6_BASE                   SDL_RTDMA2CH6_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA2CH7_BASE
    #define SDL_RTDMA2CH7_BASE                   SDL_RTDMA2CH7_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA2CH8_BASE
    #define SDL_RTDMA2CH8_BASE                   SDL_RTDMA2CH8_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA2CH9_BASE
    #define SDL_RTDMA2CH9_BASE                   SDL_RTDMA2CH9_BASE_FRAME(0U)
#endif
#ifndef SDL_RTDMA2CH10_BASE
    #define SDL_RTDMA2CH10_BASE                  SDL_RTDMA2CH10_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANA_DRIVER_BASE
    #define SDL_MCANA_DRIVER_BASE                SDL_MCANA_DRIVER_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANSSA_BASE
    #define SDL_MCANSSA_BASE                     SDL_MCANSSA_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANA_BASE
    #define SDL_MCANA_BASE                       SDL_MCANA_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANA_ERROR_BASE
    #define SDL_MCANA_ERROR_BASE                 SDL_MCANA_ERROR_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANB_DRIVER_BASE
    #define SDL_MCANB_DRIVER_BASE                SDL_MCANB_DRIVER_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANBSS_BASE
    #define SDL_MCANBSS_BASE                     SDL_MCANBSS_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANB_BASE
    #define SDL_MCANB_BASE                       SDL_MCANB_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANB_ERROR_BASE
    #define SDL_MCANB_ERROR_BASE                 SDL_MCANB_ERROR_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANC_DRIVER_BASE
    #define SDL_MCANC_DRIVER_BASE                SDL_MCANC_DRIVER_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANCSS_BASE
    #define SDL_MCANCSS_BASE                     SDL_MCANCSS_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANC_BASE
    #define SDL_MCANC_BASE                       SDL_MCANC_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANC_ERROR_BASE
    #define SDL_MCANC_ERROR_BASE                 SDL_MCANC_ERROR_BASE_FRAME(0U)
#endif
#ifndef SDL_MCAND_DRIVER_BASE
    #define SDL_MCAND_DRIVER_BASE                SDL_MCAND_DRIVER_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANDSS_BASE
    #define SDL_MCANDSS_BASE                     SDL_MCANDSS_BASE_FRAME(0U)
#endif
#ifndef SDL_MCAND_BASE
    #define SDL_MCAND_BASE                       SDL_MCAND_BASE_FRAME(0U)
#endif
#ifndef SDL_MCAND_ERROR_BASE
    #define SDL_MCAND_ERROR_BASE                 SDL_MCAND_ERROR_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANE_DRIVER_BASE
    #define SDL_MCANE_DRIVER_BASE                SDL_MCANE_DRIVER_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANESS_BASE
    #define SDL_MCANESS_BASE                     SDL_MCANESS_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANE_BASE
    #define SDL_MCANE_BASE                       SDL_MCANE_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANE_ERROR_BASE
    #define SDL_MCANE_ERROR_BASE                 SDL_MCANE_ERROR_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANF_DRIVER_BASE
    #define SDL_MCANF_DRIVER_BASE                SDL_MCANF_DRIVER_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANFSS_BASE
    #define SDL_MCANFSS_BASE                     SDL_MCANFSS_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANF_BASE
    #define SDL_MCANF_BASE                       SDL_MCANF_BASE_FRAME(0U)
#endif
#ifndef SDL_MCANF_ERROR_BASE
    #define SDL_MCANF_ERROR_BASE                 SDL_MCANF_ERROR_BASE_FRAME(0U)
#endif
#ifndef SDL_LINA_BASE
    #define SDL_LINA_BASE                        SDL_LINA_BASE_FRAME(0U)
#endif
#ifndef SDL_LINB_BASE
    #define SDL_LINB_BASE                        SDL_LINB_BASE_FRAME(0U)
#endif
#ifndef SDL_SENT1_BASE
    #define SDL_SENT1_BASE                       SDL_SENT1_BASE_FRAME(0U)
#endif
#ifndef SDL_SENT2_BASE
    #define SDL_SENT2_BASE                       SDL_SENT2_BASE_FRAME(0U)
#endif
#ifndef SDL_SENT3_BASE
    #define SDL_SENT3_BASE                       SDL_SENT3_BASE_FRAME(0U)
#endif
#ifndef SDL_SENT4_BASE
    #define SDL_SENT4_BASE                       SDL_SENT4_BASE_FRAME(0U)
#endif
#ifndef SDL_SENT5_BASE
    #define SDL_SENT5_BASE                       SDL_SENT5_BASE_FRAME(0U)
#endif
#ifndef SDL_SENT6_BASE
    #define SDL_SENT6_BASE                       SDL_SENT6_BASE_FRAME(0U)
#endif
#ifndef SDL_UARTA_WRITE_BASE
    #define SDL_UARTA_WRITE_BASE                 SDL_UARTA_WRITE_BASE_FRAME(0U)
#endif
#ifndef SDL_UARTA_BASE
    #define SDL_UARTA_BASE                       SDL_UARTA_BASE_FRAME(0U)
#endif
#ifndef SDL_UARTB_WRITE_BASE
    #define SDL_UARTB_WRITE_BASE                 SDL_UARTB_WRITE_BASE_FRAME(0U)
#endif
#ifndef SDL_UARTB_BASE
    #define SDL_UARTB_BASE                       SDL_UARTB_BASE_FRAME(0U)
#endif
#ifndef SDL_UARTC_WRITE_BASE
    #define SDL_UARTC_WRITE_BASE                 SDL_UARTC_WRITE_BASE_FRAME(0U)
#endif
#ifndef SDL_UARTC_BASE
    #define SDL_UARTC_BASE                       SDL_UARTC_BASE_FRAME(0U)
#endif
#ifndef SDL_UARTD_WRITE_BASE
    #define SDL_UARTD_WRITE_BASE                 SDL_UARTD_WRITE_BASE_FRAME(0U)
#endif
#ifndef SDL_UARTD_BASE
    #define SDL_UARTD_BASE                       SDL_UARTD_BASE_FRAME(0U)
#endif
#ifndef SDL_UARTE_WRITE_BASE
    #define SDL_UARTE_WRITE_BASE                 SDL_UARTE_WRITE_BASE_FRAME(0U)
#endif
#ifndef SDL_UARTE_BASE
    #define SDL_UARTE_BASE                       SDL_UARTE_BASE_FRAME(0U)
#endif
#ifndef SDL_UARTF_WRITE_BASE
    #define SDL_UARTF_WRITE_BASE                 SDL_UARTF_WRITE_BASE_FRAME(0U)
#endif
#ifndef SDL_UARTF_BASE
    #define SDL_UARTF_BASE                       SDL_UARTF_BASE_FRAME(0U)
#endif
#ifndef SDL_DCC1_BASE
    #define SDL_DCC1_BASE                        SDL_DCC1_BASE_FRAME(0U)
#endif
#ifndef SDL_DCC2_BASE
    #define SDL_DCC2_BASE                        SDL_DCC2_BASE_FRAME(0U)
#endif
#ifndef SDL_DCC3_BASE
    #define SDL_DCC3_BASE                        SDL_DCC3_BASE_FRAME(0U)
#endif
#ifndef SDL_ERRORAGGREGATOR_BASE
    #define SDL_ERRORAGGREGATOR_BASE             SDL_ERRORAGGREGATOR_BASE_FRAME(0U)
#endif
#ifndef SDL_ESMCPU1_BASE
    #define SDL_ESMCPU1_BASE                     SDL_ESMCPU1_BASE_FRAME(0U)
#endif
#ifndef SDL_ESMCPU2_BASE
    #define SDL_ESMCPU2_BASE                     SDL_ESMCPU2_BASE_FRAME(0U)
#endif
#ifndef SDL_ESMCPU3_BASE
    #define SDL_ESMCPU3_BASE                     SDL_ESMCPU3_BASE_FRAME(0U)
#endif
#ifndef SDL_ESMSYSTEM_BASE
    #define SDL_ESMSYSTEM_BASE                   SDL_ESMSYSTEM_BASE_FRAME(0U)
#endif
#ifndef SDL_ESMSAFETYAGG_BASE
    #define SDL_ESMSAFETYAGG_BASE                SDL_ESMSAFETYAGG_BASE_FRAME(0U)
#endif
#ifndef SDL_WADI1BLK1CONFIG_BASE
    #define SDL_WADI1BLK1CONFIG_BASE             SDL_WADI1BLK1CONFIG_BASE_FRAME(0U)
#endif
#ifndef SDL_WADI1BLK2CONFIG_BASE
    #define SDL_WADI1BLK2CONFIG_BASE             SDL_WADI1BLK2CONFIG_BASE_FRAME(0U)
#endif
#ifndef SDL_WADI1BLK3CONFIG_BASE
    #define SDL_WADI1BLK3CONFIG_BASE             SDL_WADI1BLK3CONFIG_BASE_FRAME(0U)
#endif
#ifndef SDL_WADI1BLK4CONFIG_BASE
    #define SDL_WADI1BLK4CONFIG_BASE             SDL_WADI1BLK4CONFIG_BASE_FRAME(0U)
#endif
#ifndef SDL_WADI1OPERSSS_BASE
    #define SDL_WADI1OPERSSS_BASE                SDL_WADI1OPERSSS_BASE_FRAME(0U)
#endif
#ifndef SDL_WADI2BLK1CONFIG_BASE
    #define SDL_WADI2BLK1CONFIG_BASE             SDL_WADI2BLK1CONFIG_BASE_FRAME(0U)
#endif
#ifndef SDL_WADI2BLK2CONFIG_BASE
    #define SDL_WADI2BLK2CONFIG_BASE             SDL_WADI2BLK2CONFIG_BASE_FRAME(0U)
#endif
#ifndef SDL_WADI2BLK3CONFIG_BASE
    #define SDL_WADI2BLK3CONFIG_BASE             SDL_WADI2BLK3CONFIG_BASE_FRAME(0U)
#endif
#ifndef SDL_WADI2BLK4CONFIG_BASE
    #define SDL_WADI2BLK4CONFIG_BASE             SDL_WADI2BLK4CONFIG_BASE_FRAME(0U)
#endif
#ifndef SDL_WADI2OPERSSS_BASE
    #define SDL_WADI2OPERSSS_BASE                SDL_WADI2OPERSSS_BASE_FRAME(0U)
#endif
#ifndef SDL_OUTPUTXBAR1_FLAGS_BASE
    #define SDL_OUTPUTXBAR1_FLAGS_BASE           SDL_OUTPUTXBAR1_FLAGS_BASE_FRAME(0U)
#endif
#ifndef SDL_OUTPUTXBAR2_FLAGS_BASE
    #define SDL_OUTPUTXBAR2_FLAGS_BASE           SDL_OUTPUTXBAR2_FLAGS_BASE_FRAME(0U)
#endif
#ifndef SDL_OUTPUTXBAR3_FLAGS_BASE
    #define SDL_OUTPUTXBAR3_FLAGS_BASE           SDL_OUTPUTXBAR3_FLAGS_BASE_FRAME(0U)
#endif
#ifndef SDL_OUTPUTXBAR4_FLAGS_BASE
    #define SDL_OUTPUTXBAR4_FLAGS_BASE           SDL_OUTPUTXBAR4_FLAGS_BASE_FRAME(0U)
#endif
#ifndef SDL_OUTPUTXBAR5_FLAGS_BASE
    #define SDL_OUTPUTXBAR5_FLAGS_BASE           SDL_OUTPUTXBAR5_FLAGS_BASE_FRAME(0U)
#endif
#ifndef SDL_OUTPUTXBAR6_FLAGS_BASE
    #define SDL_OUTPUTXBAR6_FLAGS_BASE           SDL_OUTPUTXBAR6_FLAGS_BASE_FRAME(0U)
#endif
#ifndef SDL_OUTPUTXBAR7_FLAGS_BASE
    #define SDL_OUTPUTXBAR7_FLAGS_BASE           SDL_OUTPUTXBAR7_FLAGS_BASE_FRAME(0U)
#endif
#ifndef SDL_OUTPUTXBAR8_FLAGS_BASE
    #define SDL_OUTPUTXBAR8_FLAGS_BASE           SDL_OUTPUTXBAR8_FLAGS_BASE_FRAME(0U)
#endif
#ifndef SDL_OUTPUTXBAR9_FLAGS_BASE
    #define SDL_OUTPUTXBAR9_FLAGS_BASE           SDL_OUTPUTXBAR9_FLAGS_BASE_FRAME(0U)
#endif
#ifndef SDL_OUTPUTXBAR10_FLAGS_BASE
    #define SDL_OUTPUTXBAR10_FLAGS_BASE          SDL_OUTPUTXBAR10_FLAGS_BASE_FRAME(0U)
#endif
#ifndef SDL_OUTPUTXBAR11_FLAGS_BASE
    #define SDL_OUTPUTXBAR11_FLAGS_BASE          SDL_OUTPUTXBAR11_FLAGS_BASE_FRAME(0U)
#endif
#ifndef SDL_OUTPUTXBAR12_FLAGS_BASE
    #define SDL_OUTPUTXBAR12_FLAGS_BASE          SDL_OUTPUTXBAR12_FLAGS_BASE_FRAME(0U)
#endif
#ifndef SDL_OUTPUTXBAR13_FLAGS_BASE
    #define SDL_OUTPUTXBAR13_FLAGS_BASE          SDL_OUTPUTXBAR13_FLAGS_BASE_FRAME(0U)
#endif
#ifndef SDL_OUTPUTXBAR14_FLAGS_BASE
    #define SDL_OUTPUTXBAR14_FLAGS_BASE          SDL_OUTPUTXBAR14_FLAGS_BASE_FRAME(0U)
#endif
#ifndef SDL_OUTPUTXBAR15_FLAGS_BASE
    #define SDL_OUTPUTXBAR15_FLAGS_BASE          SDL_OUTPUTXBAR15_FLAGS_BASE_FRAME(0U)
#endif
#ifndef SDL_OUTPUTXBAR16_FLAGS_BASE
    #define SDL_OUTPUTXBAR16_FLAGS_BASE          SDL_OUTPUTXBAR16_FLAGS_BASE_FRAME(0U)
#endif
#ifndef SDL_XBAR_BASE
    #define SDL_XBAR_BASE                        SDL_XBAR_BASE_FRAME(0U)
#endif
#ifndef SDL_CPU1DLTFIFO_BASE
    #define SDL_CPU1DLTFIFO_BASE                 SDL_CPU1DLTFIFO_BASE_FRAME(0U)
#endif
#ifndef SDL_CPU2DLTFIFO_BASE
    #define SDL_CPU2DLTFIFO_BASE                 SDL_CPU2DLTFIFO_BASE_FRAME(0U)
#endif
#ifndef SDL_CPU3DLTFIFO_BASE
    #define SDL_CPU3DLTFIFO_BASE                 SDL_CPU3DLTFIFO_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM1_BASE
    #define SDL_EPWM1_BASE                       SDL_EPWM1_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM1XCMP_BASE
    #define SDL_EPWM1XCMP_BASE                   SDL_EPWM1XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM1DE_BASE
    #define SDL_EPWM1DE_BASE                     SDL_EPWM1DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM1MINDBLUT_BASE
    #define SDL_EPWM1MINDBLUT_BASE               SDL_EPWM1MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM2_BASE
    #define SDL_EPWM2_BASE                       SDL_EPWM2_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM2XCMP_BASE
    #define SDL_EPWM2XCMP_BASE                   SDL_EPWM2XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM2DE_BASE
    #define SDL_EPWM2DE_BASE                     SDL_EPWM2DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM2MINDBLUT_BASE
    #define SDL_EPWM2MINDBLUT_BASE               SDL_EPWM2MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM3_BASE
    #define SDL_EPWM3_BASE                       SDL_EPWM3_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM3XCMP_BASE
    #define SDL_EPWM3XCMP_BASE                   SDL_EPWM3XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM3DE_BASE
    #define SDL_EPWM3DE_BASE                     SDL_EPWM3DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM3MINDBLUT_BASE
    #define SDL_EPWM3MINDBLUT_BASE               SDL_EPWM3MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM4_BASE
    #define SDL_EPWM4_BASE                       SDL_EPWM4_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM4XCMP_BASE
    #define SDL_EPWM4XCMP_BASE                   SDL_EPWM4XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM4DE_BASE
    #define SDL_EPWM4DE_BASE                     SDL_EPWM4DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM4MINDBLUT_BASE
    #define SDL_EPWM4MINDBLUT_BASE               SDL_EPWM4MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM5_BASE
    #define SDL_EPWM5_BASE                       SDL_EPWM5_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM5XCMP_BASE
    #define SDL_EPWM5XCMP_BASE                   SDL_EPWM5XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM5DE_BASE
    #define SDL_EPWM5DE_BASE                     SDL_EPWM5DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM5MINDBLUT_BASE
    #define SDL_EPWM5MINDBLUT_BASE               SDL_EPWM5MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM6_BASE
    #define SDL_EPWM6_BASE                       SDL_EPWM6_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM6XCMP_BASE
    #define SDL_EPWM6XCMP_BASE                   SDL_EPWM6XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM6DE_BASE
    #define SDL_EPWM6DE_BASE                     SDL_EPWM6DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM6MINDBLUT_BASE
    #define SDL_EPWM6MINDBLUT_BASE               SDL_EPWM6MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM7_BASE
    #define SDL_EPWM7_BASE                       SDL_EPWM7_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM7XCMP_BASE
    #define SDL_EPWM7XCMP_BASE                   SDL_EPWM7XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM7DE_BASE
    #define SDL_EPWM7DE_BASE                     SDL_EPWM7DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM7MINDBLUT_BASE
    #define SDL_EPWM7MINDBLUT_BASE               SDL_EPWM7MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM8_BASE
    #define SDL_EPWM8_BASE                       SDL_EPWM8_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM8XCMP_BASE
    #define SDL_EPWM8XCMP_BASE                   SDL_EPWM8XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM8DE_BASE
    #define SDL_EPWM8DE_BASE                     SDL_EPWM8DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM8MINDBLUT_BASE
    #define SDL_EPWM8MINDBLUT_BASE               SDL_EPWM8MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM9_BASE
    #define SDL_EPWM9_BASE                       SDL_EPWM9_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM9XCMP_BASE
    #define SDL_EPWM9XCMP_BASE                   SDL_EPWM9XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM9DE_BASE
    #define SDL_EPWM9DE_BASE                     SDL_EPWM9DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM9MINDBLUT_BASE
    #define SDL_EPWM9MINDBLUT_BASE               SDL_EPWM9MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM10_BASE
    #define SDL_EPWM10_BASE                      SDL_EPWM10_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM10XCMP_BASE
    #define SDL_EPWM10XCMP_BASE                  SDL_EPWM10XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM10DE_BASE
    #define SDL_EPWM10DE_BASE                    SDL_EPWM10DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM10MINDBLUT_BASE
    #define SDL_EPWM10MINDBLUT_BASE              SDL_EPWM10MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM11_BASE
    #define SDL_EPWM11_BASE                      SDL_EPWM11_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM11XCMP_BASE
    #define SDL_EPWM11XCMP_BASE                  SDL_EPWM11XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM11DE_BASE
    #define SDL_EPWM11DE_BASE                    SDL_EPWM11DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM11MINDBLUT_BASE
    #define SDL_EPWM11MINDBLUT_BASE              SDL_EPWM11MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM12_BASE
    #define SDL_EPWM12_BASE                      SDL_EPWM12_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM12XCMP_BASE
    #define SDL_EPWM12XCMP_BASE                  SDL_EPWM12XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM12DE_BASE
    #define SDL_EPWM12DE_BASE                    SDL_EPWM12DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM12MINDBLUT_BASE
    #define SDL_EPWM12MINDBLUT_BASE              SDL_EPWM12MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM13_BASE
    #define SDL_EPWM13_BASE                      SDL_EPWM13_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM13XCMP_BASE
    #define SDL_EPWM13XCMP_BASE                  SDL_EPWM13XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM13DE_BASE
    #define SDL_EPWM13DE_BASE                    SDL_EPWM13DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM13MINDBLUT_BASE
    #define SDL_EPWM13MINDBLUT_BASE              SDL_EPWM13MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM14_BASE
    #define SDL_EPWM14_BASE                      SDL_EPWM14_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM14XCMP_BASE
    #define SDL_EPWM14XCMP_BASE                  SDL_EPWM14XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM14DE_BASE
    #define SDL_EPWM14DE_BASE                    SDL_EPWM14DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM14MINDBLUT_BASE
    #define SDL_EPWM14MINDBLUT_BASE              SDL_EPWM14MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM15_BASE
    #define SDL_EPWM15_BASE                      SDL_EPWM15_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM15XCMP_BASE
    #define SDL_EPWM15XCMP_BASE                  SDL_EPWM15XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM15DE_BASE
    #define SDL_EPWM15DE_BASE                    SDL_EPWM15DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM15MINDBLUT_BASE
    #define SDL_EPWM15MINDBLUT_BASE              SDL_EPWM15MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM16_BASE
    #define SDL_EPWM16_BASE                      SDL_EPWM16_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM16XCMP_BASE
    #define SDL_EPWM16XCMP_BASE                  SDL_EPWM16XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM16DE_BASE
    #define SDL_EPWM16DE_BASE                    SDL_EPWM16DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM16MINDBLUT_BASE
    #define SDL_EPWM16MINDBLUT_BASE              SDL_EPWM16MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM17_BASE
    #define SDL_EPWM17_BASE                      SDL_EPWM17_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM17XCMP_BASE
    #define SDL_EPWM17XCMP_BASE                  SDL_EPWM17XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM17DE_BASE
    #define SDL_EPWM17DE_BASE                    SDL_EPWM17DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM17MINDBLUT_BASE
    #define SDL_EPWM17MINDBLUT_BASE              SDL_EPWM17MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM18_BASE
    #define SDL_EPWM18_BASE                      SDL_EPWM18_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM18XCMP_BASE
    #define SDL_EPWM18XCMP_BASE                  SDL_EPWM18XCMP_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM18DE_BASE
    #define SDL_EPWM18DE_BASE                    SDL_EPWM18DE_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM18MINDBLUT_BASE
    #define SDL_EPWM18MINDBLUT_BASE              SDL_EPWM18MINDBLUT_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM1XLINK_BASE
    #define SDL_EPWM1XLINK_BASE                  SDL_EPWM1XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM1XCMPXLINK_BASE
    #define SDL_EPWM1XCMPXLINK_BASE              SDL_EPWM1XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM1DEXLINK_BASE
    #define SDL_EPWM1DEXLINK_BASE                SDL_EPWM1DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM1MINDBLUTXLINK_BASE
    #define SDL_EPWM1MINDBLUTXLINK_BASE          SDL_EPWM1MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM2XLINK_BASE
    #define SDL_EPWM2XLINK_BASE                  SDL_EPWM2XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM2XCMPXLINK_BASE
    #define SDL_EPWM2XCMPXLINK_BASE              SDL_EPWM2XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM2DEXLINK_BASE
    #define SDL_EPWM2DEXLINK_BASE                SDL_EPWM2DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM2MINDBLUTXLINK_BASE
    #define SDL_EPWM2MINDBLUTXLINK_BASE          SDL_EPWM2MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM3XLINK_BASE
    #define SDL_EPWM3XLINK_BASE                  SDL_EPWM3XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM3XCMPXLINK_BASE
    #define SDL_EPWM3XCMPXLINK_BASE              SDL_EPWM3XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM3DEXLINK_BASE
    #define SDL_EPWM3DEXLINK_BASE                SDL_EPWM3DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM3MINDBLUTXLINK_BASE
    #define SDL_EPWM3MINDBLUTXLINK_BASE          SDL_EPWM3MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM4XLINK_BASE
    #define SDL_EPWM4XLINK_BASE                  SDL_EPWM4XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM4XCMPXLINK_BASE
    #define SDL_EPWM4XCMPXLINK_BASE              SDL_EPWM4XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM4DEXLINK_BASE
    #define SDL_EPWM4DEXLINK_BASE                SDL_EPWM4DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM4MINDBLUTXLINK_BASE
    #define SDL_EPWM4MINDBLUTXLINK_BASE          SDL_EPWM4MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM5XLINK_BASE
    #define SDL_EPWM5XLINK_BASE                  SDL_EPWM5XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM5XCMPXLINK_BASE
    #define SDL_EPWM5XCMPXLINK_BASE              SDL_EPWM5XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM5DEXLINK_BASE
    #define SDL_EPWM5DEXLINK_BASE                SDL_EPWM5DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM5MINDBLUTXLINK_BASE
    #define SDL_EPWM5MINDBLUTXLINK_BASE          SDL_EPWM5MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM6XLINK_BASE
    #define SDL_EPWM6XLINK_BASE                  SDL_EPWM6XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM6XCMPXLINK_BASE
    #define SDL_EPWM6XCMPXLINK_BASE              SDL_EPWM6XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM6DEXLINK_BASE
    #define SDL_EPWM6DEXLINK_BASE                SDL_EPWM6DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM6MINDBLUTXLINK_BASE
    #define SDL_EPWM6MINDBLUTXLINK_BASE          SDL_EPWM6MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM7XLINK_BASE
    #define SDL_EPWM7XLINK_BASE                  SDL_EPWM7XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM7XCMPXLINK_BASE
    #define SDL_EPWM7XCMPXLINK_BASE              SDL_EPWM7XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM7DEXLINK_BASE
    #define SDL_EPWM7DEXLINK_BASE                SDL_EPWM7DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM7MINDBLUTXLINK_BASE
    #define SDL_EPWM7MINDBLUTXLINK_BASE          SDL_EPWM7MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM8XLINK_BASE
    #define SDL_EPWM8XLINK_BASE                  SDL_EPWM8XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM8XCMPXLINK_BASE
    #define SDL_EPWM8XCMPXLINK_BASE              SDL_EPWM8XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM8DEXLINK_BASE
    #define SDL_EPWM8DEXLINK_BASE                SDL_EPWM8DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM8MINDBLUTXLINK_BASE
    #define SDL_EPWM8MINDBLUTXLINK_BASE          SDL_EPWM8MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM9XLINK_BASE
    #define SDL_EPWM9XLINK_BASE                  SDL_EPWM9XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM9XCMPXLINK_BASE
    #define SDL_EPWM9XCMPXLINK_BASE              SDL_EPWM9XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM9DEXLINK_BASE
    #define SDL_EPWM9DEXLINK_BASE                SDL_EPWM9DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM9MINDBLUTXLINK_BASE
    #define SDL_EPWM9MINDBLUTXLINK_BASE          SDL_EPWM9MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM10XLINK_BASE
    #define SDL_EPWM10XLINK_BASE                 SDL_EPWM10XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM10XCMPXLINK_BASE
    #define SDL_EPWM10XCMPXLINK_BASE             SDL_EPWM10XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM10DEXLINK_BASE
    #define SDL_EPWM10DEXLINK_BASE               SDL_EPWM10DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM10MINDBLUTXLINK_BASE
    #define SDL_EPWM10MINDBLUTXLINK_BASE         SDL_EPWM10MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM11XLINK_BASE
    #define SDL_EPWM11XLINK_BASE                 SDL_EPWM11XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM11XCMPXLINK_BASE
    #define SDL_EPWM11XCMPXLINK_BASE             SDL_EPWM11XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM11DEXLINK_BASE
    #define SDL_EPWM11DEXLINK_BASE               SDL_EPWM11DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM11MINDBLUTXLINK_BASE
    #define SDL_EPWM11MINDBLUTXLINK_BASE         SDL_EPWM11MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM12XLINK_BASE
    #define SDL_EPWM12XLINK_BASE                 SDL_EPWM12XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM12XCMPXLINK_BASE
    #define SDL_EPWM12XCMPXLINK_BASE             SDL_EPWM12XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM12DEXLINK_BASE
    #define SDL_EPWM12DEXLINK_BASE               SDL_EPWM12DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM12MINDBLUTXLINK_BASE
    #define SDL_EPWM12MINDBLUTXLINK_BASE         SDL_EPWM12MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM13XLINK_BASE
    #define SDL_EPWM13XLINK_BASE                 SDL_EPWM13XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM13XCMPXLINK_BASE
    #define SDL_EPWM13XCMPXLINK_BASE             SDL_EPWM13XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM13DEXLINK_BASE
    #define SDL_EPWM13DEXLINK_BASE               SDL_EPWM13DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM13MINDBLUTXLINK_BASE
    #define SDL_EPWM13MINDBLUTXLINK_BASE         SDL_EPWM13MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM14XLINK_BASE
    #define SDL_EPWM14XLINK_BASE                 SDL_EPWM14XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM14XCMPXLINK_BASE
    #define SDL_EPWM14XCMPXLINK_BASE             SDL_EPWM14XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM14DEXLINK_BASE
    #define SDL_EPWM14DEXLINK_BASE               SDL_EPWM14DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM14MINDBLUTXLINK_BASE
    #define SDL_EPWM14MINDBLUTXLINK_BASE         SDL_EPWM14MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM15XLINK_BASE
    #define SDL_EPWM15XLINK_BASE                 SDL_EPWM15XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM15XCMPXLINK_BASE
    #define SDL_EPWM15XCMPXLINK_BASE             SDL_EPWM15XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM15DEXLINK_BASE
    #define SDL_EPWM15DEXLINK_BASE               SDL_EPWM15DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM15MINDBLUTXLINK_BASE
    #define SDL_EPWM15MINDBLUTXLINK_BASE         SDL_EPWM15MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM16XLINK_BASE
    #define SDL_EPWM16XLINK_BASE                 SDL_EPWM16XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM16XCMPXLINK_BASE
    #define SDL_EPWM16XCMPXLINK_BASE             SDL_EPWM16XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM16DEXLINK_BASE
    #define SDL_EPWM16DEXLINK_BASE               SDL_EPWM16DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM16MINDBLUTXLINK_BASE
    #define SDL_EPWM16MINDBLUTXLINK_BASE         SDL_EPWM16MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM17XLINK_BASE
    #define SDL_EPWM17XLINK_BASE                 SDL_EPWM17XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM17XCMPXLINK_BASE
    #define SDL_EPWM17XCMPXLINK_BASE             SDL_EPWM17XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM17DEXLINK_BASE
    #define SDL_EPWM17DEXLINK_BASE               SDL_EPWM17DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM17MINDBLUTXLINK_BASE
    #define SDL_EPWM17MINDBLUTXLINK_BASE         SDL_EPWM17MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM18XLINK_BASE
    #define SDL_EPWM18XLINK_BASE                 SDL_EPWM18XLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM18XCMPXLINK_BASE
    #define SDL_EPWM18XCMPXLINK_BASE             SDL_EPWM18XCMPXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM18DEXLINK_BASE
    #define SDL_EPWM18DEXLINK_BASE               SDL_EPWM18DEXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_EPWM18MINDBLUTXLINK_BASE
    #define SDL_EPWM18MINDBLUTXLINK_BASE         SDL_EPWM18MINDBLUTXLINK_BASE_FRAME(0U)
#endif
#ifndef SDL_HRPWMCAL1_BASE
    #define SDL_HRPWMCAL1_BASE                   SDL_HRPWMCAL1_BASE_FRAME(0U)
#endif
#ifndef SDL_HRPWMCAL2_BASE
    #define SDL_HRPWMCAL2_BASE                   SDL_HRPWMCAL2_BASE_FRAME(0U)
#endif
#ifndef SDL_HRPWMCAL3_BASE
    #define SDL_HRPWMCAL3_BASE                   SDL_HRPWMCAL3_BASE_FRAME(0U)
#endif
#ifndef SDL_EQEP1_BASE
    #define SDL_EQEP1_BASE                       SDL_EQEP1_BASE_FRAME(0U)
#endif
#ifndef SDL_EQEP2_BASE
    #define SDL_EQEP2_BASE                       SDL_EQEP2_BASE_FRAME(0U)
#endif
#ifndef SDL_EQEP3_BASE
    #define SDL_EQEP3_BASE                       SDL_EQEP3_BASE_FRAME(0U)
#endif
#ifndef SDL_EQEP4_BASE
    #define SDL_EQEP4_BASE                       SDL_EQEP4_BASE_FRAME(0U)
#endif
#ifndef SDL_EQEP5_BASE
    #define SDL_EQEP5_BASE                       SDL_EQEP5_BASE_FRAME(0U)
#endif
#ifndef SDL_EQEP6_BASE
    #define SDL_EQEP6_BASE                       SDL_EQEP6_BASE_FRAME(0U)
#endif
#ifndef SDL_SDFM1_BASE
    #define SDL_SDFM1_BASE                       SDL_SDFM1_BASE_FRAME(0U)
#endif
#ifndef SDL_SDFM2_BASE
    #define SDL_SDFM2_BASE                       SDL_SDFM2_BASE_FRAME(0U)
#endif
#ifndef SDL_SDFM3_BASE
    #define SDL_SDFM3_BASE                       SDL_SDFM3_BASE_FRAME(0U)
#endif
#ifndef SDL_SDFM4_BASE
    #define SDL_SDFM4_BASE                       SDL_SDFM4_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCA_BASE
    #define SDL_ADCA_BASE                        SDL_ADCA_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCB_BASE
    #define SDL_ADCB_BASE                        SDL_ADCB_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCC_BASE
    #define SDL_ADCC_BASE                        SDL_ADCC_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCD_BASE
    #define SDL_ADCD_BASE                        SDL_ADCD_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCE_BASE
    #define SDL_ADCE_BASE                        SDL_ADCE_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCSAFETYCHECK1_BASE
    #define SDL_ADCSAFETYCHECK1_BASE             SDL_ADCSAFETYCHECK1_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCSAFETYCHECK2_BASE
    #define SDL_ADCSAFETYCHECK2_BASE             SDL_ADCSAFETYCHECK2_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCSAFETYCHECK3_BASE
    #define SDL_ADCSAFETYCHECK3_BASE             SDL_ADCSAFETYCHECK3_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCSAFETYCHECK4_BASE
    #define SDL_ADCSAFETYCHECK4_BASE             SDL_ADCSAFETYCHECK4_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCSAFETYCHECK5_BASE
    #define SDL_ADCSAFETYCHECK5_BASE             SDL_ADCSAFETYCHECK5_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCSAFETYCHECK6_BASE
    #define SDL_ADCSAFETYCHECK6_BASE             SDL_ADCSAFETYCHECK6_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCSAFETYCHECK7_BASE
    #define SDL_ADCSAFETYCHECK7_BASE             SDL_ADCSAFETYCHECK7_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCSAFETYCHECK8_BASE
    #define SDL_ADCSAFETYCHECK8_BASE             SDL_ADCSAFETYCHECK8_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCSAFETYCHECK9_BASE
    #define SDL_ADCSAFETYCHECK9_BASE             SDL_ADCSAFETYCHECK9_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCSAFETYCHECK10_BASE
    #define SDL_ADCSAFETYCHECK10_BASE            SDL_ADCSAFETYCHECK10_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCSAFETYCHECKINTEVT1_BASE
    #define SDL_ADCSAFETYCHECKINTEVT1_BASE       SDL_ADCSAFETYCHECKINTEVT1_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCSAFETYCHECKINTEVT2_BASE
    #define SDL_ADCSAFETYCHECKINTEVT2_BASE       SDL_ADCSAFETYCHECKINTEVT2_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCSAFETYCHECKINTEVT3_BASE
    #define SDL_ADCSAFETYCHECKINTEVT3_BASE       SDL_ADCSAFETYCHECKINTEVT3_BASE_FRAME(0U)
#endif
#ifndef SDL_ADCGLOBAL_BASE
    #define SDL_ADCGLOBAL_BASE                   SDL_ADCGLOBAL_BASE_FRAME(0U)
#endif
#ifndef SDL_DACA_BASE
    #define SDL_DACA_BASE                        SDL_DACA_BASE_FRAME(0U)
#endif
#ifndef SDL_DACB_BASE
    #define SDL_DACB_BASE                        SDL_DACB_BASE_FRAME(0U)
#endif
#ifndef SDL_CMPSS1_BASE
    #define SDL_CMPSS1_BASE                      SDL_CMPSS1_BASE_FRAME(0U)
#endif
#ifndef SDL_CMPSS2_BASE
    #define SDL_CMPSS2_BASE                      SDL_CMPSS2_BASE_FRAME(0U)
#endif
#ifndef SDL_CMPSS3_BASE
    #define SDL_CMPSS3_BASE                      SDL_CMPSS3_BASE_FRAME(0U)
#endif
#ifndef SDL_CMPSS4_BASE
    #define SDL_CMPSS4_BASE                      SDL_CMPSS4_BASE_FRAME(0U)
#endif
#ifndef SDL_CMPSS5_BASE
    #define SDL_CMPSS5_BASE                      SDL_CMPSS5_BASE_FRAME(0U)
#endif
#ifndef SDL_CMPSS6_BASE
    #define SDL_CMPSS6_BASE                      SDL_CMPSS6_BASE_FRAME(0U)
#endif
#ifndef SDL_CMPSS7_BASE
    #define SDL_CMPSS7_BASE                      SDL_CMPSS7_BASE_FRAME(0U)
#endif
#ifndef SDL_CMPSS8_BASE
    #define SDL_CMPSS8_BASE                      SDL_CMPSS8_BASE_FRAME(0U)
#endif
#ifndef SDL_CMPSS9_BASE
    #define SDL_CMPSS9_BASE                      SDL_CMPSS9_BASE_FRAME(0U)
#endif
#ifndef SDL_CMPSS10_BASE
    #define SDL_CMPSS10_BASE                     SDL_CMPSS10_BASE_FRAME(0U)
#endif
#ifndef SDL_CMPSS11_BASE
    #define SDL_CMPSS11_BASE                     SDL_CMPSS11_BASE_FRAME(0U)
#endif
#ifndef SDL_CMPSS12_BASE
    #define SDL_CMPSS12_BASE                     SDL_CMPSS12_BASE_FRAME(0U)
#endif
#ifndef SDL_ECAP1_BASE
    #define SDL_ECAP1_BASE                       SDL_ECAP1_BASE_FRAME(0U)
#endif
#ifndef SDL_ECAP1SIGNALMONITORING_BASE
    #define SDL_ECAP1SIGNALMONITORING_BASE       SDL_ECAP1SIGNALMONITORING_BASE_FRAME(0U)
#endif
#ifndef SDL_ECAP2_BASE
    #define SDL_ECAP2_BASE                       SDL_ECAP2_BASE_FRAME(0U)
#endif
#ifndef SDL_ECAP2SIGNALMONITORING_BASE
    #define SDL_ECAP2SIGNALMONITORING_BASE       SDL_ECAP2SIGNALMONITORING_BASE_FRAME(0U)
#endif
#ifndef SDL_ECAP3_BASE
    #define SDL_ECAP3_BASE                       SDL_ECAP3_BASE_FRAME(0U)
#endif
#ifndef SDL_ECAP3SIGNALMONITORING_BASE
    #define SDL_ECAP3SIGNALMONITORING_BASE       SDL_ECAP3SIGNALMONITORING_BASE_FRAME(0U)
#endif
#ifndef SDL_ECAP4_BASE
    #define SDL_ECAP4_BASE                       SDL_ECAP4_BASE_FRAME(0U)
#endif
#ifndef SDL_ECAP4SIGNALMONITORING_BASE
    #define SDL_ECAP4SIGNALMONITORING_BASE       SDL_ECAP4SIGNALMONITORING_BASE_FRAME(0U)
#endif
#ifndef SDL_ECAP5_BASE
    #define SDL_ECAP5_BASE                       SDL_ECAP5_BASE_FRAME(0U)
#endif
#ifndef SDL_HRCAP5_BASE
    #define SDL_HRCAP5_BASE                      SDL_HRCAP5_BASE_FRAME(0U)
#endif
#ifndef SDL_ECAP5SIGNALMONITORING_BASE
    #define SDL_ECAP5SIGNALMONITORING_BASE       SDL_ECAP5SIGNALMONITORING_BASE_FRAME(0U)
#endif
#ifndef SDL_ECAP6_BASE
    #define SDL_ECAP6_BASE                       SDL_ECAP6_BASE_FRAME(0U)
#endif
#ifndef SDL_HRCAP6_BASE
    #define SDL_HRCAP6_BASE                      SDL_HRCAP6_BASE_FRAME(0U)
#endif
#ifndef SDL_ECAP6SIGNALMONITORING_BASE
    #define SDL_ECAP6SIGNALMONITORING_BASE       SDL_ECAP6SIGNALMONITORING_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB1_BASE
    #define SDL_CLB1_BASE                        SDL_CLB1_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB1_LOGICCFG_BASE
    #define SDL_CLB1_LOGICCFG_BASE               SDL_CLB1_LOGICCFG_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB1_LOGICCTRL_BASE
    #define SDL_CLB1_LOGICCTRL_BASE              SDL_CLB1_LOGICCTRL_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB1_DATAEXCH_BASE
    #define SDL_CLB1_DATAEXCH_BASE               SDL_CLB1_DATAEXCH_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB2_BASE
    #define SDL_CLB2_BASE                        SDL_CLB2_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB2_LOGICCFG_BASE
    #define SDL_CLB2_LOGICCFG_BASE               SDL_CLB2_LOGICCFG_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB2_LOGICCTRL_BASE
    #define SDL_CLB2_LOGICCTRL_BASE              SDL_CLB2_LOGICCTRL_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB2_DATAEXCH_BASE
    #define SDL_CLB2_DATAEXCH_BASE               SDL_CLB2_DATAEXCH_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB3_BASE
    #define SDL_CLB3_BASE                        SDL_CLB3_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB3_LOGICCFG_BASE
    #define SDL_CLB3_LOGICCFG_BASE               SDL_CLB3_LOGICCFG_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB3_LOGICCTRL_BASE
    #define SDL_CLB3_LOGICCTRL_BASE              SDL_CLB3_LOGICCTRL_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB3_DATAEXCH_BASE
    #define SDL_CLB3_DATAEXCH_BASE               SDL_CLB3_DATAEXCH_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB4_BASE
    #define SDL_CLB4_BASE                        SDL_CLB4_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB4_LOGICCFG_BASE
    #define SDL_CLB4_LOGICCFG_BASE               SDL_CLB4_LOGICCFG_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB4_LOGICCTRL_BASE
    #define SDL_CLB4_LOGICCTRL_BASE              SDL_CLB4_LOGICCTRL_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB4_DATAEXCH_BASE
    #define SDL_CLB4_DATAEXCH_BASE               SDL_CLB4_DATAEXCH_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB5_BASE
    #define SDL_CLB5_BASE                        SDL_CLB5_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB5_LOGICCFG_BASE
    #define SDL_CLB5_LOGICCFG_BASE               SDL_CLB5_LOGICCFG_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB5_LOGICCTRL_BASE
    #define SDL_CLB5_LOGICCTRL_BASE              SDL_CLB5_LOGICCTRL_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB5_DATAEXCH_BASE
    #define SDL_CLB5_DATAEXCH_BASE               SDL_CLB5_DATAEXCH_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB6_BASE
    #define SDL_CLB6_BASE                        SDL_CLB6_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB6_LOGICCFG_BASE
    #define SDL_CLB6_LOGICCFG_BASE               SDL_CLB6_LOGICCFG_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB6_LOGICCTRL_BASE
    #define SDL_CLB6_LOGICCTRL_BASE              SDL_CLB6_LOGICCTRL_BASE_FRAME(0U)
#endif
#ifndef SDL_CLB6_DATAEXCH_BASE
    #define SDL_CLB6_DATAEXCH_BASE               SDL_CLB6_DATAEXCH_BASE_FRAME(0U)
#endif
#ifndef SDL_PMBUSA_BASE
    #define SDL_PMBUSA_BASE                      SDL_PMBUSA_BASE_FRAME(0U)
#endif
#ifndef SDL_I2CA_BASE
    #define SDL_I2CA_BASE                        SDL_I2CA_BASE_FRAME(0U)
#endif
#ifndef SDL_I2CB_BASE
    #define SDL_I2CB_BASE                        SDL_I2CB_BASE_FRAME(0U)
#endif
#ifndef SDL_SPIA_BASE
    #define SDL_SPIA_BASE                        SDL_SPIA_BASE_FRAME(0U)
#endif
#ifndef SDL_SPIB_BASE
    #define SDL_SPIB_BASE                        SDL_SPIB_BASE_FRAME(0U)
#endif
#ifndef SDL_SPIC_BASE
    #define SDL_SPIC_BASE                        SDL_SPIC_BASE_FRAME(0U)
#endif
#ifndef SDL_SPID_BASE
    #define SDL_SPID_BASE                        SDL_SPID_BASE_FRAME(0U)
#endif
#ifndef SDL_SPIE_BASE
    #define SDL_SPIE_BASE                        SDL_SPIE_BASE_FRAME(0U)
#endif
#ifndef SDL_FSITXA_BASE
    #define SDL_FSITXA_BASE                      SDL_FSITXA_BASE_FRAME(0U)
#endif
#ifndef SDL_FSITXB_BASE
    #define SDL_FSITXB_BASE                      SDL_FSITXB_BASE_FRAME(0U)
#endif
#ifndef SDL_FSITXC_BASE
    #define SDL_FSITXC_BASE                      SDL_FSITXC_BASE_FRAME(0U)
#endif
#ifndef SDL_FSITXD_BASE
    #define SDL_FSITXD_BASE                      SDL_FSITXD_BASE_FRAME(0U)
#endif
#ifndef SDL_FSIRXA_BASE
    #define SDL_FSIRXA_BASE                      SDL_FSIRXA_BASE_FRAME(0U)
#endif
#ifndef SDL_FSIRXB_BASE
    #define SDL_FSIRXB_BASE                      SDL_FSIRXB_BASE_FRAME(0U)
#endif
#ifndef SDL_FSIRXC_BASE
    #define SDL_FSIRXC_BASE                      SDL_FSIRXC_BASE_FRAME(0U)
#endif
#ifndef SDL_FSIRXD_BASE
    #define SDL_FSIRXD_BASE                      SDL_FSIRXD_BASE_FRAME(0U)
#endif
#ifndef SDL_EPG_BASE
    #define SDL_EPG_BASE                         SDL_EPG_BASE_FRAME(0U)
#endif
#ifndef SDL_EPGMUX_BASE
    #define SDL_EPGMUX_BASE                      SDL_EPGMUX_BASE_FRAME(0U)
#endif

#define SDL_BASE_ADDR_MASK                       0xFF3FFFFFU


#ifdef __cplusplus
}
#endif
#endif /* SDLR_BASEADDRESS_H_ */
