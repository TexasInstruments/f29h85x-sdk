//###########################################################################
//
// FILE:   pin_map.h
//
// TITLE:  Definitions of pin mux info for gpio.c.
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

#ifndef __PIN_MAP_H__
#define __PIN_MAP_H__

//*****************************************************************************
// 0x00000003 = MUX register value
// 0x0000000C = GMUX register value
// 0x0000FF00 = Shift amount within mux registers
// 0xFFFF0000 = Offset of MUX register
//*****************************************************************************


#define GPIO_0_GPIO0                    0x000C0000U
#define GPIO_0_EPWM1_A                  0x000C0001U
#define GPIO_0_EMIF1_A13                0x000C0002U
#define GPIO_0_EMIF1_D0                 0x000C0003U
#define GPIO_0_MCAND_TX                 0x000C0005U
#define GPIO_0_I2CA_SDA                 0x000C0006U
#define GPIO_0_UARTE_TX                 0x000C0007U
#define GPIO_0_OUTPUTXBAR9              0x000C0009U
#define GPIO_0_ESC_TX0_DATA0            0x000C000AU
#define GPIO_0_ESC_GPI0                 0x000C000BU
#define GPIO_0_FSITXA_D0                0x000C000DU

#define GPIO_1_GPIO1                    0x000C0200U
#define GPIO_1_EPWM1_B                  0x000C0201U
#define GPIO_1_EMIF1_A14                0x000C0202U
#define GPIO_1_EMIF1_D3                 0x000C0203U
#define GPIO_1_MCAND_RX                 0x000C0205U
#define GPIO_1_I2CA_SCL                 0x000C0206U
#define GPIO_1_UARTE_RX                 0x000C0207U
#define GPIO_1_OUTPUTXBAR10             0x000C0209U
#define GPIO_1_ESC_TX1_DATA0            0x000C020AU
#define GPIO_1_ESC_GPI1                 0x000C020BU
#define GPIO_1_FSITXA_D1                0x000C020DU

#define GPIO_2_GPIO2                    0x000C0400U
#define GPIO_2_EPWM2_A                  0x000C0401U
#define GPIO_2_EMIF1_A15                0x000C0402U
#define GPIO_2_EMIF1_D4                 0x000C0403U
#define GPIO_2_UARTA_TX                 0x000C0405U
#define GPIO_2_I2CB_SDA                 0x000C0406U
#define GPIO_2_MCANF_TX                 0x000C0407U
#define GPIO_2_OUTPUTXBAR1              0x000C0409U
#define GPIO_2_ESC_RX1_ERR              0x000C040AU
#define GPIO_2_ESC_GPI2                 0x000C040BU
#define GPIO_2_FSITXA_CLK               0x000C040DU

#define GPIO_3_GPIO3                    0x000C0600U
#define GPIO_3_EPWM2_B                  0x000C0601U
#define GPIO_3_EMIF1_A16                0x000C0602U
#define GPIO_3_EMIF1_D5                 0x000C0603U
#define GPIO_3_UARTA_RX                 0x000C0605U
#define GPIO_3_I2CB_SCL                 0x000C0606U
#define GPIO_3_MCANF_RX                 0x000C0607U
#define GPIO_3_OUTPUTXBAR2              0x000C0609U
#define GPIO_3_ESC_GPI3                 0x000C060BU
#define GPIO_3_FSIRXA_D0                0x000C060DU

#define GPIO_4_GPIO4                    0x000C0800U
#define GPIO_4_EPWM3_A                  0x000C0801U
#define GPIO_4_EMIF1_A17                0x000C0802U
#define GPIO_4_EMIF1_D9                 0x000C0803U
#define GPIO_4_MCANC_TX                 0x000C0805U
#define GPIO_4_UARTF_TX                 0x000C0807U
#define GPIO_4_OUTPUTXBAR3              0x000C0809U
#define GPIO_4_ESC_GPI4                 0x000C080BU
#define GPIO_4_FSIRXA_D1                0x000C080DU
#define GPIO_4_ERRORSTS                 0x000C080FU

#define GPIO_5_GPIO5                    0x000C0A00U
#define GPIO_5_EPWM3_B                  0x000C0A01U
#define GPIO_5_EMIF1_A18                0x000C0A02U
#define GPIO_5_EMIF1_D10                0x000C0A03U
#define GPIO_5_MCANC_RX                 0x000C0A05U
#define GPIO_5_UARTF_RX                 0x000C0A07U
#define GPIO_5_OUTPUTXBAR11             0x000C0A09U
#define GPIO_5_OUTPUTXBAR3              0x000C0A0AU
#define GPIO_5_ESC_GPI5                 0x000C0A0BU
#define GPIO_5_FSIRXA_CLK               0x000C0A0DU

#define GPIO_6_GPIO6                    0x000C0C00U
#define GPIO_6_EPWM4_A                  0x000C0C01U
#define GPIO_6_EMIF1_DQM0               0x000C0C02U
#define GPIO_6_EMIF1_CLK                0x000C0C03U
#define GPIO_6_MCANB_TX                 0x000C0C05U
#define GPIO_6_LINA_TX                  0x000C0C06U
#define GPIO_6_OUTPUTXBAR4              0x000C0C09U
#define GPIO_6_SYNCOUT                  0x000C0C0AU
#define GPIO_6_ESC_GPI6                 0x000C0C0BU
#define GPIO_6_FSITXB_D0                0x000C0C0DU

#define GPIO_7_GPIO7                    0x000C0E00U
#define GPIO_7_EPWM4_B                  0x000C0E01U
#define GPIO_7_EMIF1_DQM1               0x000C0E02U
#define GPIO_7_EMIF1_CAS                0x000C0E03U
#define GPIO_7_MCANB_RX                 0x000C0E05U
#define GPIO_7_LINA_RX                  0x000C0E06U
#define GPIO_7_OUTPUTXBAR5              0x000C0E09U
#define GPIO_7_ESC_GPI7                 0x000C0E0BU
#define GPIO_7_FSITXB_D1                0x000C0E0DU

#define GPIO_8_GPIO8                    0x000C1000U
#define GPIO_8_EPWM5_A                  0x000C1001U
#define GPIO_8_EMIF1_RAS                0x000C1002U
#define GPIO_8_EPWM4_B                  0x000C1003U
#define GPIO_8_MCANC_TX                 0x000C1005U
#define GPIO_8_SPIE_PICO                0x000C1006U
#define GPIO_8_UARTD_TX                 0x000C1007U
#define GPIO_8_OUTPUTXBAR12             0x000C1009U
#define GPIO_8_ADCSOCAO                 0x000C100AU
#define GPIO_8_ESC_GPO0                 0x000C100BU
#define GPIO_8_FSITXB_CLK               0x000C100DU
#define GPIO_8_FSITXA_D1                0x000C100EU
#define GPIO_8_FSIRXA_D0                0x000C100FU

#define GPIO_9_GPIO9                    0x000C1200U
#define GPIO_9_EPWM5_B                  0x000C1201U
#define GPIO_9_EMIF1_D11                0x000C1202U
#define GPIO_9_SPIE_POCI                0x000C1206U
#define GPIO_9_UARTD_RX                 0x000C1207U
#define GPIO_9_OUTPUTXBAR6              0x000C1209U
#define GPIO_9_ESC_TX0_CLK              0x000C120AU
#define GPIO_9_ESC_GPO1                 0x000C120BU
#define GPIO_9_FSIRXB_D0                0x000C120DU
#define GPIO_9_FSITXA_D0                0x000C120EU
#define GPIO_9_FSIRXA_CLK               0x000C120FU

#define GPIO_10_GPIO10                  0x000C1400U
#define GPIO_10_EPWM8_A                 0x000C1401U
#define GPIO_10_PMBUSA_SCL              0x000C1402U
#define GPIO_10_ADCSOCBO                0x000C1403U
#define GPIO_10_MCANC_RX                0x000C1405U
#define GPIO_10_UARTC_TX                0x000C1406U
#define GPIO_10_I2CA_SCL                0x000C1407U
#define GPIO_10_SENT2                   0x000C1409U
#define GPIO_10_ESC_GPI19               0x000C140DU
#define GPIO_10_ADCA_EXTMUXSEL2         0x000C140EU
#define GPIO_10_OUTPUTXBAR13            0x000C140FU

#define GPIO_11_GPIO11                  0x000C1600U
#define GPIO_11_EPWM6_B                 0x000C1601U
#define GPIO_11_EMIF1_D15               0x000C1602U
#define GPIO_11_EPWM7_B                 0x000C1603U
#define GPIO_11_SPIE_PTE                0x000C1606U
#define GPIO_11_SD4_D1                  0x000C1607U
#define GPIO_11_PMBUSA_ALERT            0x000C1609U
#define GPIO_11_ESC_TX0_DATA1           0x000C160AU
#define GPIO_11_ESC_GPO3                0x000C160BU
#define GPIO_11_FSIRXB_CLK              0x000C160DU
#define GPIO_11_FSIRXA_D1               0x000C160EU
#define GPIO_11_OUTPUTXBAR7             0x000C160FU

#define GPIO_12_GPIO12                  0x000C1800U
#define GPIO_12_EPWM7_A                 0x000C1801U
#define GPIO_12_EMIF1_A1                0x000C1802U
#define GPIO_12_ADCSOCAO                0x000C1803U
#define GPIO_12_SPIE_CLK                0x000C1806U
#define GPIO_12_SD4_C2                  0x000C1807U
#define GPIO_12_PMBUSA_CTL              0x000C1809U
#define GPIO_12_ESC_TX0_DATA2           0x000C180AU
#define GPIO_12_ESC_GPO4                0x000C180BU
#define GPIO_12_FSIRXC_D0               0x000C180DU
#define GPIO_12_FSIRXA_D0               0x000C180EU
#define GPIO_12_OUTPUTXBAR14            0x000C180FU

#define GPIO_13_GPIO13                  0x000C1A00U
#define GPIO_13_EPWM7_B                 0x000C1A01U
#define GPIO_13_EMIF1_CS0N              0x000C1A02U
#define GPIO_13_EMIF1_D9                0x000C1A03U
#define GPIO_13_UARTC_RX                0x000C1A06U
#define GPIO_13_SD4_D2                  0x000C1A07U
#define GPIO_13_PMBUSA_SDA              0x000C1A09U
#define GPIO_13_ESC_TX0_DATA3           0x000C1A0AU
#define GPIO_13_ESC_GPO5                0x000C1A0BU
#define GPIO_13_FSIRXC_D1               0x000C1A0DU
#define GPIO_13_FSIRXA_CLK              0x000C1A0EU
#define GPIO_13_OUTPUTXBAR15            0x000C1A0FU

#define GPIO_14_GPIO14                  0x000C1C00U
#define GPIO_14_EPWM6_A                 0x000C1C01U
#define GPIO_14_EMIF1_D17               0x000C1C02U
#define GPIO_14_EPWM18_A                0x000C1C03U
#define GPIO_14_EMIF1_D13               0x000C1C05U
#define GPIO_14_LINA_TX                 0x000C1C06U
#define GPIO_14_OUTPUTXBAR3             0x000C1C07U
#define GPIO_14_PMBUSA_SCL              0x000C1C09U
#define GPIO_14_ESC_PHY1_LINKSTATUS     0x000C1C0AU
#define GPIO_14_ESC_GPO6                0x000C1C0BU
#define GPIO_14_FSIRXC_CLK              0x000C1C0DU
#define GPIO_14_SD4_C1                  0x000C1C0EU
#define GPIO_14_OUTPUTXBAR8             0x000C1C0FU

#define GPIO_15_GPIO15                  0x000C1E00U
#define GPIO_15_EPWM8_B                 0x000C1E01U
#define GPIO_15_PMBUSA_CTL              0x000C1E03U
#define GPIO_15_I2CA_SDA                0x000C1E05U
#define GPIO_15_LINA_RX                 0x000C1E06U
#define GPIO_15_OUTPUTXBAR4             0x000C1E07U
#define GPIO_15_SENT1                   0x000C1E09U
#define GPIO_15_ESC_GPO7                0x000C1E0AU
#define GPIO_15_ESC_GPI20               0x000C1E0DU
#define GPIO_15_ADCA_EXTMUXSEL3         0x000C1E0EU
#define GPIO_15_OUTPUTXBAR16            0x000C1E0FU

#define GPIO_16_GPIO16                  0x00100000U
#define GPIO_16_EPWM9_A                 0x00100001U
#define GPIO_16_EMIF1_D29               0x00100002U
#define GPIO_16_EMIF1_BA0               0x00100003U
#define GPIO_16_SPIA_PICO               0x00100005U
#define GPIO_16_MCAND_TX                0x00100007U
#define GPIO_16_ESC_RX1_CLK             0x0010000AU
#define GPIO_16_SD1_D1                  0x0010000BU
#define GPIO_16_FSIRXD_D1               0x0010000DU
#define GPIO_16_FSIRXC_CLK              0x0010000EU
#define GPIO_16_OUTPUTXBAR7             0x0010000FU

#define GPIO_17_GPIO17                  0x00100200U
#define GPIO_17_EPWM9_B                 0x00100201U
#define GPIO_17_EMIF1_DQM3              0x00100202U
#define GPIO_17_EMIF1_BA1               0x00100203U
#define GPIO_17_SPIA_POCI               0x00100205U
#define GPIO_17_MCAND_RX                0x00100207U
#define GPIO_17_ESC_RX1_DV              0x0010020AU
#define GPIO_17_SD1_C1                  0x0010020BU
#define GPIO_17_FSIRXD_CLK              0x0010020DU
#define GPIO_17_UARTC_TX                0x0010020EU
#define GPIO_17_OUTPUTXBAR8             0x0010020FU

#define GPIO_18_GPIO18                  0x00100400U
#define GPIO_18_EPWM15_A                0x00100401U
#define GPIO_18_PMBUSA_ALERT            0x00100403U
#define GPIO_18_I2CA_SCL                0x00100405U
#define GPIO_18_UARTC_RX                0x00100406U
#define GPIO_18_SENT4                   0x00100409U
#define GPIO_18_ESC_GPI21               0x0010040DU
#define GPIO_18_ADCB_EXTMUXSEL0         0x0010040EU

#define GPIO_19_GPIO19                  0x00100600U
#define GPIO_19_EPWM10_B                0x00100601U
#define GPIO_19_EMIF1_CS3N              0x00100602U
#define GPIO_19_ADCSOCBO                0x00100603U
#define GPIO_19_SPIA_PTE                0x00100605U
#define GPIO_19_UARTE_RX                0x00100606U
#define GPIO_19_MCANC_TX                0x00100607U
#define GPIO_19_PMBUSA_ALERT            0x00100609U
#define GPIO_19_ESC_TX1_DATA3           0x0010060AU
#define GPIO_19_SD1_C2                  0x0010060BU

#define GPIO_20_GPIO20                  0x00100800U
#define GPIO_20_EPWM11_A                0x00100801U
#define GPIO_20_EMIF1_BA0               0x00100802U
#define GPIO_20_EMIF1_DQM2              0x00100803U
#define GPIO_20_SPIC_PICO               0x00100806U
#define GPIO_20_MCANB_RX                0x00100807U
#define GPIO_20_ESC_TX1_DATA2           0x0010080AU
#define GPIO_20_SD1_D3                  0x0010080BU

#define GPIO_21_GPIO21                  0x00100A00U
#define GPIO_21_EPWM11_B                0x00100A01U
#define GPIO_21_EMIF1_BA1               0x00100A02U
#define GPIO_21_SPIC_POCI               0x00100A06U
#define GPIO_21_MCANB_TX                0x00100A07U
#define GPIO_21_ESC_TX1_DATA1           0x00100A0AU
#define GPIO_21_SD1_C3                  0x00100A0BU

#define GPIO_22_GPIO22                  0x00100C00U
#define GPIO_22_EPWM12_A                0x00100C01U
#define GPIO_22_PMBUSA_SDA              0x00100C03U
#define GPIO_22_I2CB_SDA                0x00100C05U
#define GPIO_22_UARTB_TX                0x00100C06U
#define GPIO_22_MCANC_TX                0x00100C07U
#define GPIO_22_SENT5                   0x00100C09U
#define GPIO_22_ESC_GPO2                0x00100C0AU
#define GPIO_22_ESC_GPI22               0x00100C0DU
#define GPIO_22_ADCB_EXTMUXSEL1         0x00100C0EU

#define GPIO_23_GPIO23                  0x00100E00U
#define GPIO_23_EPWM12_B                0x00100E01U
#define GPIO_23_PMBUSA_SCL              0x00100E03U
#define GPIO_23_I2CB_SCL                0x00100E05U
#define GPIO_23_UARTB_RX                0x00100E06U
#define GPIO_23_MCANC_RX                0x00100E07U
#define GPIO_23_SENT6                   0x00100E09U
#define GPIO_23_ESC_PHY_RESETN          0x00100E0AU
#define GPIO_23_ESC_GPI23               0x00100E0DU
#define GPIO_23_ADCC_EXTMUXSEL0         0x00100E0EU

#define GPIO_24_GPIO24                  0x00101000U
#define GPIO_24_EPWM13_A                0x00101001U
#define GPIO_24_EMIF1_DQM0              0x00101002U
#define GPIO_24_SPIB_PICO               0x00101005U
#define GPIO_24_LINB_TX                 0x00101006U
#define GPIO_24_MCANE_TX                0x00101007U
#define GPIO_24_ESC_RX0_CLK             0x0010100AU
#define GPIO_24_SD2_D1                  0x0010100BU
#define GPIO_24_ESC_GPI24               0x0010100DU
#define GPIO_24_EPWM2_A                 0x0010100EU
#define GPIO_24_OUTPUTXBAR1             0x0010100FU

#define GPIO_25_GPIO25                  0x00101200U
#define GPIO_25_EPWM13_B                0x00101201U
#define GPIO_25_EMIF1_DQM1              0x00101202U
#define GPIO_25_SPIB_POCI               0x00101205U
#define GPIO_25_LINB_RX                 0x00101206U
#define GPIO_25_MCANE_RX                0x00101207U
#define GPIO_25_PMBUSA_SDA              0x00101209U
#define GPIO_25_ESC_RX0_DV              0x0010120AU
#define GPIO_25_SD2_C1                  0x0010120BU
#define GPIO_25_FSITXA_D1               0x0010120DU
#define GPIO_25_EPWM2_B                 0x0010120EU
#define GPIO_25_OUTPUTXBAR2             0x0010120FU

#define GPIO_26_GPIO26                  0x00101400U
#define GPIO_26_EPWM14_A                0x00101401U
#define GPIO_26_EMIF1_DQM2              0x00101402U
#define GPIO_26_SPIB_CLK                0x00101405U
#define GPIO_26_UARTE_TX                0x00101406U
#define GPIO_26_MCANE_TX                0x00101407U
#define GPIO_26_PMBUSA_CTL              0x00101409U
#define GPIO_26_ESC_RX0_ERR             0x0010140AU
#define GPIO_26_SD2_D2                  0x0010140BU
#define GPIO_26_FSITXA_D0               0x0010140DU
#define GPIO_26_ESC_MDIO_CLK            0x0010140EU
#define GPIO_26_OUTPUTXBAR3             0x0010140FU

#define GPIO_27_GPIO27                  0x00101600U
#define GPIO_27_EPWM14_B                0x00101601U
#define GPIO_27_EMIF1_DQM3              0x00101602U
#define GPIO_27_SPIB_PTE                0x00101605U
#define GPIO_27_UARTA_TX                0x00101606U
#define GPIO_27_EPWM4_A                 0x00101609U
#define GPIO_27_ESC_RX0_DATA0           0x0010160AU
#define GPIO_27_SD2_C2                  0x0010160BU
#define GPIO_27_FSITXA_CLK              0x0010160DU
#define GPIO_27_ESC_MDIO_DATA           0x0010160EU
#define GPIO_27_OUTPUTXBAR4             0x0010160FU

#define GPIO_28_GPIO28                  0x00101800U
#define GPIO_28_EPWM15_A                0x00101801U
#define GPIO_28_EMIF1_CS4N              0x00101802U
#define GPIO_28_EMIF1_CS2N              0x00101803U
#define GPIO_28_UARTA_RX                0x00101806U
#define GPIO_28_EPWM4_B                 0x00101809U
#define GPIO_28_ESC_RX0_DATA1           0x0010180AU
#define GPIO_28_SD2_D3                  0x0010180BU
#define GPIO_28_OUTPUTXBAR5             0x0010180FU

#define GPIO_29_GPIO29                  0x00101A00U
#define GPIO_29_EPWM15_B                0x00101A01U
#define GPIO_29_PMBUSA_SDA              0x00101A02U
#define GPIO_29_UARTE_RX                0x00101A06U
#define GPIO_29_I2CA_SDA                0x00101A07U
#define GPIO_29_SENT3                   0x00101A09U
#define GPIO_29_ESC_LATCH0              0x00101A0AU
#define GPIO_29_ESC_I2C_SDA             0x00101A0DU
#define GPIO_29_ADCC_EXTMUXSEL1         0x00101A0EU
#define GPIO_29_OUTPUTXBAR6             0x00101A0FU

#define GPIO_30_GPIO30                  0x00101C00U
#define GPIO_30_EPWM16_A                0x00101C01U
#define GPIO_30_EMIF1_CLK               0x00101C02U
#define GPIO_30_EMIF1_CS4N              0x00101C03U
#define GPIO_30_MCANC_RX                0x00101C05U
#define GPIO_30_SPID_PICO               0x00101C06U
#define GPIO_30_EMIF1_A12               0x00101C07U
#define GPIO_30_ESC_LATCH1              0x00101C0AU
#define GPIO_30_SD2_D4                  0x00101C0BU
#define GPIO_30_ESC_I2C_SCL             0x00101C0DU
#define GPIO_30_ESC_SYNC1               0x00101C0EU
#define GPIO_30_OUTPUTXBAR7             0x00101C0FU

#define GPIO_31_GPIO31                  0x00101E00U
#define GPIO_31_EPWM16_B                0x00101E01U
#define GPIO_31_EMIF1_WEN               0x00101E02U
#define GPIO_31_EMIF1_RNW               0x00101E03U
#define GPIO_31_MCANC_TX                0x00101E05U
#define GPIO_31_SPID_POCI               0x00101E06U
#define GPIO_31_I2CA_SDA                0x00101E07U
#define GPIO_31_ESC_RX1_DATA0           0x00101E0AU
#define GPIO_31_SD2_C4                  0x00101E0BU
#define GPIO_31_FSITXD_D0               0x00101E0DU
#define GPIO_31_OUTPUTXBAR8             0x00101E0FU

#define GPIO_32_GPIO32                  0x008C0000U
#define GPIO_32_EMIF1_CS0N              0x008C0002U
#define GPIO_32_EMIF1_OEN               0x008C0003U
#define GPIO_32_SPIA_PICO               0x008C0005U
#define GPIO_32_SPID_CLK                0x008C0006U
#define GPIO_32_I2CA_SDA                0x008C0007U
#define GPIO_32_OUTPUTXBAR9             0x008C0009U
#define GPIO_32_ESC_RX0_DATA0           0x008C000AU

#define GPIO_33_GPIO33                  0x008C0200U
#define GPIO_33_EMIF1_RNW               0x008C0202U
#define GPIO_33_EMIF1_BA0               0x008C0203U
#define GPIO_33_SPIA_POCI               0x008C0205U
#define GPIO_33_SPID_PTE                0x008C0206U
#define GPIO_33_I2CA_SCL                0x008C0207U
#define GPIO_33_OUTPUTXBAR10            0x008C0209U
#define GPIO_33_ESC_LED_ERR             0x008C020AU

#define GPIO_34_GPIO34                  0x008C0400U
#define GPIO_34_EPWM18_A                0x008C0401U
#define GPIO_34_EMIF1_CS2N              0x008C0402U
#define GPIO_34_EMIF1_BA1               0x008C0403U
#define GPIO_34_SPIA_CLK                0x008C0405U
#define GPIO_34_UARTF_TX                0x008C0406U
#define GPIO_34_I2CB_SDA                0x008C0407U
#define GPIO_34_OUTPUTXBAR11            0x008C0409U
#define GPIO_34_ESC_LATCH0              0x008C040AU
#define GPIO_34_EPWM3_B                 0x008C040DU
#define GPIO_34_ESC_SYNC0               0x008C040EU
#define GPIO_34_OUTPUTXBAR1             0x008C040FU

#define GPIO_35_GPIO35                  0x008C0600U
#define GPIO_35_EPWM18_B                0x008C0601U
#define GPIO_35_EMIF1_CS3N              0x008C0602U
#define GPIO_35_EMIF1_A0                0x008C0603U
#define GPIO_35_SPIA_PTE                0x008C0605U
#define GPIO_35_UARTF_RX                0x008C0606U
#define GPIO_35_I2CB_SCL                0x008C0607U
#define GPIO_35_OUTPUTXBAR12            0x008C0609U
#define GPIO_35_ESC_LATCH1              0x008C060AU
#define GPIO_35_ESC_SYNC1               0x008C060EU

#define GPIO_36_GPIO36                  0x008C0800U
#define GPIO_36_EMIF1_WAIT              0x008C0802U
#define GPIO_36_EMIF1_A1                0x008C0803U
#define GPIO_36_UARTC_TX                0x008C0805U
#define GPIO_36_MCANC_RX                0x008C0806U
#define GPIO_36_OUTPUTXBAR13            0x008C0809U
#define GPIO_36_SD1_D1                  0x008C080BU
#define GPIO_36_EMIF1_WEN               0x008C080EU

#define GPIO_37_GPIO37                  0x008C0A00U
#define GPIO_37_EPWM18_A                0x008C0A01U
#define GPIO_37_EMIF1_OEN               0x008C0A02U
#define GPIO_37_EMIF1_A2                0x008C0A03U
#define GPIO_37_UARTC_RX                0x008C0A05U
#define GPIO_37_MCANC_TX                0x008C0A06U
#define GPIO_37_OUTPUTXBAR14            0x008C0A09U
#define GPIO_37_ESC_RX1_DATA1           0x008C0A0AU
#define GPIO_37_SD1_D2                  0x008C0A0BU
#define GPIO_37_EMIF1_D24               0x008C0A0EU
#define GPIO_37_OUTPUTXBAR2             0x008C0A0FU

#define GPIO_38_GPIO38                  0x008C0C00U
#define GPIO_38_EPWM18_B                0x008C0C01U
#define GPIO_38_EMIF1_A0                0x008C0C02U
#define GPIO_38_EMIF1_A3                0x008C0C03U
#define GPIO_38_UARTA_TX                0x008C0C05U
#define GPIO_38_SPIE_PICO               0x008C0C06U
#define GPIO_38_OUTPUTXBAR15            0x008C0C09U
#define GPIO_38_ESC_RX0_DATA1           0x008C0C0AU
#define GPIO_38_SD1_D3                  0x008C0C0BU
#define GPIO_38_FSITXD_D1               0x008C0C0DU
#define GPIO_38_EMIF1_CS2N              0x008C0C0EU

#define GPIO_39_GPIO39                  0x008C0E00U
#define GPIO_39_EMIF1_A1                0x008C0E02U
#define GPIO_39_EMIF1_A4                0x008C0E03U
#define GPIO_39_UARTA_RX                0x008C0E05U
#define GPIO_39_OUTPUTXBAR16            0x008C0E09U
#define GPIO_39_ESC_MDIO_DATA           0x008C0E0AU
#define GPIO_39_SD1_D4                  0x008C0E0BU
#define GPIO_39_FSIRXD_CLK              0x008C0E0DU
#define GPIO_39_ESC_LED_RUN             0x008C0E0FU

#define GPIO_40_GPIO40                  0x008C1000U
#define GPIO_40_EPWM13_A                0x008C1001U
#define GPIO_40_EMIF1_A2                0x008C1002U
#define GPIO_40_MCANB_RX                0x008C1005U
#define GPIO_40_I2CB_SDA                0x008C1006U
#define GPIO_40_OUTPUTXBAR9             0x008C1009U
#define GPIO_40_ESC_GPO2                0x008C100AU
#define GPIO_40_SD4_C3                  0x008C100BU
#define GPIO_40_EPWM1_A                 0x008C100EU
#define GPIO_40_SD2_C1                  0x008C100FU

#define GPIO_41_GPIO41                  0x008C1200U
#define GPIO_41_EPWM13_B                0x008C1201U
#define GPIO_41_EMIF1_A3                0x008C1202U
#define GPIO_41_EPWM18_A                0x008C1203U
#define GPIO_41_MCANB_TX                0x008C1205U
#define GPIO_41_SPIE_POCI               0x008C1206U
#define GPIO_41_I2CB_SCL                0x008C1207U
#define GPIO_41_OUTPUTXBAR10            0x008C1209U
#define GPIO_41_ESC_RX0_DATA2           0x008C120AU
#define GPIO_41_SD4_D3                  0x008C120BU
#define GPIO_41_FSIRXD_CLK              0x008C120DU
#define GPIO_41_EPWM1_B                 0x008C120EU
#define GPIO_41_SD2_D1                  0x008C120FU

#define GPIO_42_GPIO42                  0x008C1400U
#define GPIO_42_EPWM14_A                0x008C1401U
#define GPIO_42_EMIF1_A2                0x008C1402U
#define GPIO_42_EMIF1_A13               0x008C1403U
#define GPIO_42_UARTA_TX                0x008C1405U
#define GPIO_42_SPIE_CLK                0x008C1406U
#define GPIO_42_I2CA_SDA                0x008C1407U
#define GPIO_42_OUTPUTXBAR13            0x008C1409U
#define GPIO_42_SD4_C3                  0x008C140AU
#define GPIO_42_SD4_C4                  0x008C140BU
#define GPIO_42_FSIRXD_D0               0x008C140DU
#define GPIO_42_ADCE_EXTMUXSEL2         0x008C140EU

#define GPIO_43_GPIO43                  0x008C1600U
#define GPIO_43_EPWM14_B                0x008C1601U
#define GPIO_43_EMIF1_A4                0x008C1602U
#define GPIO_43_EMIF1_D13               0x008C1603U
#define GPIO_43_UARTA_RX                0x008C1605U
#define GPIO_43_SPIE_PTE                0x008C1606U
#define GPIO_43_I2CA_SCL                0x008C1607U
#define GPIO_43_OUTPUTXBAR14            0x008C1609U
#define GPIO_43_SD4_D4                  0x008C160BU
#define GPIO_43_FSIRXD_D1               0x008C160DU
#define GPIO_43_ADCE_EXTMUXSEL3         0x008C160EU

#define GPIO_44_GPIO44                  0x008C1800U
#define GPIO_44_EMIF1_A4                0x008C1802U
#define GPIO_44_SPID_POCI               0x008C1805U
#define GPIO_44_MCANB_RX                0x008C1806U
#define GPIO_44_UARTB_TX                0x008C1807U
#define GPIO_44_OUTPUTXBAR14            0x008C1809U
#define GPIO_44_ESC_TX1_CLK             0x008C180AU
#define GPIO_44_SD3_C4                  0x008C180BU
#define GPIO_44_FSIRXD_CLK              0x008C180DU

#define GPIO_45_GPIO45                  0x008C1A00U
#define GPIO_45_EMIF1_A5                0x008C1A02U
#define GPIO_45_SPID_PTE                0x008C1A05U
#define GPIO_45_MCANB_TX                0x008C1A06U
#define GPIO_45_UARTB_RX                0x008C1A07U
#define GPIO_45_OUTPUTXBAR15            0x008C1A09U
#define GPIO_45_ESC_TX1_ENA             0x008C1A0AU
#define GPIO_45_SD3_D4                  0x008C1A0BU
#define GPIO_45_FSIRXD_D0               0x008C1A0DU

#define GPIO_46_GPIO46                  0x008C1C00U
#define GPIO_46_EPWM4_A                 0x008C1C01U
#define GPIO_46_EMIF1_A6                0x008C1C02U
#define GPIO_46_EPWM14_A                0x008C1C03U
#define GPIO_46_UARTC_TX                0x008C1C05U
#define GPIO_46_MCANE_TX                0x008C1C07U
#define GPIO_46_ESC_MDIO_CLK            0x008C1C0AU
#define GPIO_46_SD3_C4                  0x008C1C0BU

#define GPIO_47_GPIO47                  0x008C1E00U
#define GPIO_47_EPWM4_B                 0x008C1E01U
#define GPIO_47_EMIF1_A7                0x008C1E02U
#define GPIO_47_EPWM14_B                0x008C1E03U
#define GPIO_47_UARTC_RX                0x008C1E05U
#define GPIO_47_MCANE_RX                0x008C1E07U
#define GPIO_47_ESC_MDIO_DATA           0x008C1E0AU
#define GPIO_47_SD4_C3                  0x008C1E0BU

#define GPIO_48_GPIO48                  0x00900000U
#define GPIO_48_EMIF1_A8                0x00900002U
#define GPIO_48_UARTD_TX                0x00900005U
#define GPIO_48_OUTPUTXBAR3             0x00900009U
#define GPIO_48_ESC_PHY_CLK             0x0090000AU
#define GPIO_48_SD1_D1                  0x0090000BU
#define GPIO_48_EPWM3_A                 0x0090000DU
#define GPIO_48_SD2_C2                  0x0090000FU

#define GPIO_49_GPIO49                  0x00900200U
#define GPIO_49_EMIF1_A9                0x00900202U
#define GPIO_49_EMIF1_A5                0x00900203U
#define GPIO_49_UARTD_RX                0x00900205U
#define GPIO_49_OUTPUTXBAR4             0x00900209U
#define GPIO_49_ESC_TX1_DATA2           0x0090020AU
#define GPIO_49_SD1_C1                  0x0090020BU
#define GPIO_49_FSITXA_D0               0x0090020DU
#define GPIO_49_SD2_D1                  0x0090020FU

#define GPIO_50_GPIO50                  0x00900400U
#define GPIO_50_EPWM15_A                0x00900401U
#define GPIO_50_EMIF1_A10               0x00900402U
#define GPIO_50_EMIF1_A6                0x00900403U
#define GPIO_50_SPIC_PICO               0x00900406U
#define GPIO_50_MCANF_TX                0x00900407U
#define GPIO_50_ESC_TX1_DATA1           0x0090040AU
#define GPIO_50_SD1_D2                  0x0090040BU
#define GPIO_50_FSITXA_D1               0x0090040DU
#define GPIO_50_ESC_GPI25               0x0090040EU
#define GPIO_50_SD2_D2                  0x0090040FU

#define GPIO_51_GPIO51                  0x00900600U
#define GPIO_51_EPWM15_B                0x00900601U
#define GPIO_51_EMIF1_A11               0x00900602U
#define GPIO_51_EMIF1_A7                0x00900603U
#define GPIO_51_SPIC_POCI               0x00900606U
#define GPIO_51_MCANF_RX                0x00900607U
#define GPIO_51_ESC_TX1_CLK             0x0090060AU
#define GPIO_51_SD1_C2                  0x0090060BU
#define GPIO_51_FSITXA_CLK              0x0090060DU
#define GPIO_51_ESC_GPI26               0x0090060EU
#define GPIO_51_SD2_D3                  0x0090060FU

#define GPIO_52_GPIO52                  0x00900800U
#define GPIO_52_EPWM16_A                0x00900801U
#define GPIO_52_EMIF1_A12               0x00900802U
#define GPIO_52_EMIF1_A8                0x00900803U
#define GPIO_52_UARTD_TX                0x00900805U
#define GPIO_52_SPIC_CLK                0x00900806U
#define GPIO_52_ESC_TX1_ENA             0x0090080AU
#define GPIO_52_SD1_D3                  0x0090080BU
#define GPIO_52_FSIRXA_D0               0x0090080DU
#define GPIO_52_SD2_D4                  0x0090080FU

#define GPIO_53_GPIO53                  0x00900A00U
#define GPIO_53_EPWM16_B                0x00900A01U
#define GPIO_53_EMIF1_D31               0x00900A02U
#define GPIO_53_EMIF1_A9                0x00900A03U
#define GPIO_53_UARTD_RX                0x00900A05U
#define GPIO_53_SPIC_PTE                0x00900A06U
#define GPIO_53_ESC_PHY0_LINKSTATUS     0x00900A0AU
#define GPIO_53_SD1_C3                  0x00900A0BU
#define GPIO_53_FSIRXA_D1               0x00900A0DU
#define GPIO_53_ESC_GPI28               0x00900A0EU
#define GPIO_53_SD1_C1                  0x00900A0FU

#define GPIO_54_GPIO54                  0x00900C00U
#define GPIO_54_EMIF1_D30               0x00900C02U
#define GPIO_54_EMIF1_A10               0x00900C03U
#define GPIO_54_SPIA_PICO               0x00900C05U
#define GPIO_54_ESC_PHY_CLK             0x00900C0AU
#define GPIO_54_SD1_D4                  0x00900C0BU
#define GPIO_54_FSIRXA_CLK              0x00900C0DU
#define GPIO_54_ESC_GPI29               0x00900C0EU
#define GPIO_54_SD1_C2                  0x00900C0FU

#define GPIO_55_GPIO55                  0x00900E00U
#define GPIO_55_EPWM16_B                0x00900E01U
#define GPIO_55_EMIF1_D29               0x00900E02U
#define GPIO_55_EMIF1_D0                0x00900E03U
#define GPIO_55_SPIA_POCI               0x00900E05U
#define GPIO_55_EMIF1_WAIT              0x00900E06U
#define GPIO_55_ESC_PHY0_LINKSTATUS     0x00900E0AU
#define GPIO_55_SD1_C4                  0x00900E0BU
#define GPIO_55_FSITXB_D0               0x00900E0DU
#define GPIO_55_SD1_C3                  0x00900E0FU

#define GPIO_56_GPIO56                  0x00901000U
#define GPIO_56_EPWM17_A                0x00901001U
#define GPIO_56_EMIF1_D28               0x00901002U
#define GPIO_56_EMIF1_D1                0x00901003U
#define GPIO_56_SPIA_CLK                0x00901005U
#define GPIO_56_MCAND_TX                0x00901006U
#define GPIO_56_I2CA_SDA                0x00901007U
#define GPIO_56_ESC_PDI_UC_IRQ          0x0090100AU
#define GPIO_56_SD2_D1                  0x0090100BU
#define GPIO_56_FSITXB_CLK              0x0090100DU
#define GPIO_56_ESC_GPI30               0x0090100EU
#define GPIO_56_SD1_C4                  0x0090100FU

#define GPIO_57_GPIO57                  0x00901200U
#define GPIO_57_EPWM17_B                0x00901201U
#define GPIO_57_EMIF1_D27               0x00901202U
#define GPIO_57_EMIF1_D2                0x00901203U
#define GPIO_57_SPIA_PTE                0x00901205U
#define GPIO_57_MCAND_RX                0x00901206U
#define GPIO_57_I2CA_SCL                0x00901207U
#define GPIO_57_ESC_MDIO_DATA           0x0090120AU
#define GPIO_57_SD2_C1                  0x0090120BU
#define GPIO_57_FSITXB_D1               0x0090120DU
#define GPIO_57_ESC_GPI31               0x0090120EU
#define GPIO_57_SD3_D3                  0x0090120FU

#define GPIO_58_GPIO58                  0x00901400U
#define GPIO_58_EPWM13_A                0x00901401U
#define GPIO_58_EMIF1_D26               0x00901402U
#define GPIO_58_EPWM8_A                 0x00901403U
#define GPIO_58_SPIA_PICO               0x00901405U
#define GPIO_58_MCANC_RX                0x00901407U
#define GPIO_58_SENT1                   0x00901409U
#define GPIO_58_ESC_LED_LINK0_ACTIVE    0x0090140AU
#define GPIO_58_SD2_D2                  0x0090140BU
#define GPIO_58_FSIRXB_D0               0x0090140DU
#define GPIO_58_ESC_TX0_DATA3           0x0090140EU
#define GPIO_58_SD2_C2                  0x0090140FU

#define GPIO_59_GPIO59                  0x00901600U
#define GPIO_59_EPWM5_A                 0x00901601U
#define GPIO_59_EMIF1_D25               0x00901602U
#define GPIO_59_EPWM8_B                 0x00901603U
#define GPIO_59_SPIA_POCI               0x00901605U
#define GPIO_59_MCANC_TX                0x00901607U
#define GPIO_59_SENT2                   0x00901609U
#define GPIO_59_ESC_LED_LINK1_ACTIVE    0x0090160AU
#define GPIO_59_SD2_C2                  0x0090160BU
#define GPIO_59_FSIRXB_D1               0x0090160DU
#define GPIO_59_ESC_TX0_ENA             0x0090160EU
#define GPIO_59_SD2_C3                  0x0090160FU

#define GPIO_60_GPIO60                  0x00901800U
#define GPIO_60_EPWM3_B                 0x00901801U
#define GPIO_60_EMIF1_D24               0x00901802U
#define GPIO_60_EMIF1_D0                0x00901803U
#define GPIO_60_SPIA_CLK                0x00901805U
#define GPIO_60_OUTPUTXBAR3             0x00901806U
#define GPIO_60_SENT3                   0x00901809U
#define GPIO_60_ESC_LED_ERR             0x0090180AU
#define GPIO_60_ESC_LATCH0              0x0090180BU
#define GPIO_60_FSIRXB_CLK              0x0090180DU
#define GPIO_60_SD2_C4                  0x0090180FU

#define GPIO_61_GPIO61                  0x00901A00U
#define GPIO_61_EPWM17_B                0x00901A01U
#define GPIO_61_EMIF1_D23               0x00901A02U
#define GPIO_61_EMIF1_D6                0x00901A03U
#define GPIO_61_SPIA_PTE                0x00901A05U
#define GPIO_61_MCANC_RX                0x00901A07U
#define GPIO_61_OUTPUTXBAR4             0x00901A09U
#define GPIO_61_ESC_LED_RUN             0x00901A0AU
#define GPIO_61_SD2_C3                  0x00901A0BU
#define GPIO_61_FSITXD_CLK              0x00901A0DU
#define GPIO_61_ESC_LATCH1              0x00901A0EU

#define GPIO_62_GPIO62                  0x00901C00U
#define GPIO_62_EPWM17_A                0x00901C01U
#define GPIO_62_EMIF1_D22               0x00901C02U
#define GPIO_62_EMIF1_D7                0x00901C03U
#define GPIO_62_MCANC_RX                0x00901C06U
#define GPIO_62_MCANC_TX                0x00901C07U
#define GPIO_62_SENT4                   0x00901C09U
#define GPIO_62_ESC_LED_STATE_RUN       0x00901C0AU
#define GPIO_62_SD2_D4                  0x00901C0BU
#define GPIO_62_FSITXD_D0               0x00901C0DU
#define GPIO_62_ESC_MDIO_CLK            0x00901C0EU

#define GPIO_63_GPIO63                  0x00901E00U
#define GPIO_63_EPWM9_A                 0x00901E01U
#define GPIO_63_EMIF1_D21               0x00901E02U
#define GPIO_63_EMIF1_RNW               0x00901E03U
#define GPIO_63_SPIB_PICO               0x00901E05U
#define GPIO_63_MCANC_TX                0x00901E06U
#define GPIO_63_SENT5                   0x00901E09U
#define GPIO_63_ESC_RX1_DATA0           0x00901E0AU
#define GPIO_63_SD1_D1                  0x00901E0BU
#define GPIO_63_FSITXD_D1               0x00901E0DU
#define GPIO_63_ADCD_EXTMUXSEL0         0x00901E0EU
#define GPIO_63_SD2_C4                  0x00901E0FU

#define GPIO_64_GPIO64                  0x010C0000U
#define GPIO_64_EPWM9_B                 0x010C0001U
#define GPIO_64_EMIF1_D20               0x010C0002U
#define GPIO_64_EMIF1_WAIT              0x010C0003U
#define GPIO_64_SPIB_POCI               0x010C0005U
#define GPIO_64_MCANA_TX                0x010C0006U
#define GPIO_64_UARTF_TX                0x010C0007U
#define GPIO_64_SENT6                   0x010C0009U
#define GPIO_64_ESC_RX1_DATA1           0x010C000AU
#define GPIO_64_SD1_C1                  0x010C000BU
#define GPIO_64_FSITXD_CLK              0x010C000DU
#define GPIO_64_ADCD_EXTMUXSEL1         0x010C000EU

#define GPIO_65_GPIO65                  0x010C0200U
#define GPIO_65_EPWM10_A                0x010C0201U
#define GPIO_65_EMIF1_D19               0x010C0202U
#define GPIO_65_EMIF1_WEN               0x010C0203U
#define GPIO_65_SPIB_CLK                0x010C0205U
#define GPIO_65_MCANA_RX                0x010C0206U
#define GPIO_65_UARTF_RX                0x010C0207U
#define GPIO_65_ESC_RX1_DATA2           0x010C020AU
#define GPIO_65_SD1_D2                  0x010C020BU
#define GPIO_65_FSITXB_CLK              0x010C020DU
#define GPIO_65_ADCD_EXTMUXSEL2         0x010C020EU
#define GPIO_65_ESC_GPI13               0x010C020FU

#define GPIO_66_GPIO66                  0x010C0400U
#define GPIO_66_EPWM10_B                0x010C0401U
#define GPIO_66_EMIF1_D18               0x010C0402U
#define GPIO_66_EMIF1_OEN               0x010C0403U
#define GPIO_66_SPIB_PTE                0x010C0405U
#define GPIO_66_I2CB_SDA                0x010C0406U
#define GPIO_66_ESC_RX1_DATA3           0x010C040AU
#define GPIO_66_SD1_C2                  0x010C040BU
#define GPIO_66_FSITXB_D1               0x010C040DU
#define GPIO_66_ADCD_EXTMUXSEL3         0x010C040EU
#define GPIO_66_ESC_GPI14               0x010C040FU

#define GPIO_67_GPIO67                  0x010C0600U
#define GPIO_67_EPWM17_A                0x010C0601U
#define GPIO_67_EMIF1_D17               0x010C0602U
#define GPIO_67_LINB_TX                 0x010C0605U
#define GPIO_67_MCAND_TX                0x010C0606U
#define GPIO_67_SD1_D3                  0x010C060BU
#define GPIO_67_FSITXB_CLK              0x010C060DU

#define GPIO_68_GPIO68                  0x010C0800U
#define GPIO_68_EPWM17_B                0x010C0801U
#define GPIO_68_EMIF1_D16               0x010C0802U
#define GPIO_68_EMIF1_D4                0x010C0803U
#define GPIO_68_LINB_RX                 0x010C0805U
#define GPIO_68_MCAND_RX                0x010C0806U
#define GPIO_68_EMIF1_D13               0x010C0807U
#define GPIO_68_ESC_PHY1_LINKSTATUS     0x010C080AU
#define GPIO_68_SD1_C3                  0x010C080BU
#define GPIO_68_FSIRXB_D1               0x010C080DU
#define GPIO_68_ESC_GPI15               0x010C080FU

#define GPIO_69_GPIO69                  0x010C0A00U
#define GPIO_69_EPWM11_A                0x010C0A01U
#define GPIO_69_EMIF1_D15               0x010C0A02U
#define GPIO_69_SPIC_PICO               0x010C0A05U
#define GPIO_69_I2CB_SCL                0x010C0A06U
#define GPIO_69_ESC_RX1_CLK             0x010C0A0AU
#define GPIO_69_SD1_D4                  0x010C0A0BU
#define GPIO_69_FSITXB_D0               0x010C0A0DU

#define GPIO_70_GPIO70                  0x010C0C00U
#define GPIO_70_EPWM11_B                0x010C0C01U
#define GPIO_70_EMIF1_D14               0x010C0C02U
#define GPIO_70_SPIC_POCI               0x010C0C05U
#define GPIO_70_MCANC_RX                0x010C0C06U
#define GPIO_70_UARTB_TX                0x010C0C07U
#define GPIO_70_ESC_RX1_DV              0x010C0C0AU
#define GPIO_70_SD1_C4                  0x010C0C0BU
#define GPIO_70_FSIRXB_D0               0x010C0C0DU
#define GPIO_70_ESC_GPI16               0x010C0C0FU

#define GPIO_71_GPIO71                  0x010C0E00U
#define GPIO_71_EPWM12_A                0x010C0E01U
#define GPIO_71_EPWM11_A                0x010C0E02U
#define GPIO_71_EMIF1_D5                0x010C0E03U
#define GPIO_71_SPIC_CLK                0x010C0E05U
#define GPIO_71_MCANC_TX                0x010C0E06U
#define GPIO_71_UARTB_RX                0x010C0E07U
#define GPIO_71_EMIF1_D13               0x010C0E09U
#define GPIO_71_ESC_RX1_ERR             0x010C0E0AU
#define GPIO_71_SD3_D1                  0x010C0E0BU
#define GPIO_71_FSITXC_CLK              0x010C0E0DU
#define GPIO_71_FSITXB_D0               0x010C0E0EU

#define GPIO_72_GPIO72                  0x010C1000U
#define GPIO_72_EPWM12_B                0x010C1001U
#define GPIO_72_EMIF1_D12               0x010C1002U
#define GPIO_72_SPIC_PTE                0x010C1005U
#define GPIO_72_MCANB_RX                0x010C1006U
#define GPIO_72_UARTA_TX                0x010C1007U
#define GPIO_72_OUTPUTXBAR8             0x010C1009U
#define GPIO_72_ESC_TX1_DATA3           0x010C100AU
#define GPIO_72_SD3_D2                  0x010C100BU
#define GPIO_72_FSITXC_D0               0x010C100DU
#define GPIO_72_SD3_C1                  0x010C100EU

#define GPIO_73_GPIO73                  0x010C1200U
#define GPIO_73_EPWM5_B                 0x010C1201U
#define GPIO_73_EMIF1_D11               0x010C1202U
#define GPIO_73_XCLKOUT                 0x010C1203U
#define GPIO_73_MCANB_TX                0x010C1206U
#define GPIO_73_UARTA_RX                0x010C1207U
#define GPIO_73_OUTPUTXBAR6             0x010C1209U
#define GPIO_73_ESC_TX1_DATA2           0x010C120AU
#define GPIO_73_SD4_D4                  0x010C120BU
#define GPIO_73_FSITXC_CLK              0x010C120DU
#define GPIO_73_SD2_D2                  0x010C120EU

#define GPIO_74_GPIO74                  0x010C1400U
#define GPIO_74_EPWM8_A                 0x010C1401U
#define GPIO_74_EMIF1_D10               0x010C1402U
#define GPIO_74_MCANC_TX                0x010C1406U
#define GPIO_74_ESC_TX1_DATA1           0x010C140AU
#define GPIO_74_SD1_D4                  0x010C140BU
#define GPIO_74_FSITXA_D0               0x010C140DU
#define GPIO_74_SD2_C2                  0x010C140EU

#define GPIO_75_GPIO75                  0x010C1600U
#define GPIO_75_EPWM8_B                 0x010C1601U
#define GPIO_75_EMIF1_D9                0x010C1602U
#define GPIO_75_SPID_CLK                0x010C1605U
#define GPIO_75_MCANC_RX                0x010C1606U
#define GPIO_75_OUTPUTXBAR16            0x010C1609U
#define GPIO_75_ESC_TX1_DATA0           0x010C160AU
#define GPIO_75_SD2_D3                  0x010C160EU

#define GPIO_76_GPIO76                  0x010C1800U
#define GPIO_76_EPWM9_A                 0x010C1801U
#define GPIO_76_EMIF1_D8                0x010C1802U
#define GPIO_76_UARTD_TX                0x010C1805U
#define GPIO_76_MCANE_TX                0x010C1807U
#define GPIO_76_SD4_D4                  0x010C1809U
#define GPIO_76_ESC_PHY_RESETN          0x010C180AU
#define GPIO_76_SD3_C1                  0x010C180BU
#define GPIO_76_FSIRXC_D0               0x010C180DU
#define GPIO_76_SD2_C3                  0x010C180EU
#define GPIO_76_ESC_GPI17               0x010C180FU

#define GPIO_77_GPIO77                  0x010C1A00U
#define GPIO_77_EPWM9_B                 0x010C1A01U
#define GPIO_77_EMIF1_D7                0x010C1A02U
#define GPIO_77_UARTD_RX                0x010C1A05U
#define GPIO_77_MCANE_RX                0x010C1A07U
#define GPIO_77_SD1_D4                  0x010C1A09U
#define GPIO_77_ESC_RX0_CLK             0x010C1A0AU
#define GPIO_77_SD3_D1                  0x010C1A0BU
#define GPIO_77_FSITXB_D0               0x010C1A0DU
#define GPIO_77_SD2_D4                  0x010C1A0EU

#define GPIO_78_GPIO78                  0x010C1C00U
#define GPIO_78_EPWM10_A                0x010C1C01U
#define GPIO_78_EMIF1_D6                0x010C1C02U
#define GPIO_78_EPWM11_A                0x010C1C03U
#define GPIO_78_MCANF_TX                0x010C1C07U
#define GPIO_78_SD4_D4                  0x010C1C09U
#define GPIO_78_ESC_RX0_DV              0x010C1C0AU
#define GPIO_78_SD3_C2                  0x010C1C0BU
#define GPIO_78_FSITXC_D1               0x010C1C0DU
#define GPIO_78_SD2_C4                  0x010C1C0EU
#define GPIO_78_ESC_GPI18               0x010C1C0FU

#define GPIO_79_GPIO79                  0x010C1E00U
#define GPIO_79_EPWM10_B                0x010C1E01U
#define GPIO_79_EMIF1_D5                0x010C1E02U
#define GPIO_79_ERRORSTS                0x010C1E05U
#define GPIO_79_ESC_RX0_ERR             0x010C1E0AU
#define GPIO_79_SD3_D2                  0x010C1E0BU
#define GPIO_79_FSITXC_D0               0x010C1E0DU
#define GPIO_79_SD2_D1                  0x010C1E0EU

#define GPIO_80_GPIO80                  0x01100000U
#define GPIO_80_EPWM11_A                0x01100001U
#define GPIO_80_EMIF1_D4                0x01100002U
#define GPIO_80_ERRORSTS                0x01100005U
#define GPIO_80_SD1_D4                  0x01100009U
#define GPIO_80_ESC_RX0_DATA0           0x0110000AU
#define GPIO_80_SD3_C3                  0x0110000BU
#define GPIO_80_SD2_C1                  0x0110000EU

#define GPIO_81_GPIO81                  0x01100200U
#define GPIO_81_EPWM11_B                0x01100201U
#define GPIO_81_EMIF1_D3                0x01100202U
#define GPIO_81_ESC_RX0_DATA1           0x0110020AU
#define GPIO_81_SD3_D3                  0x0110020BU

#define GPIO_82_GPIO82                  0x01100400U
#define GPIO_82_EPWM12_A                0x01100401U
#define GPIO_82_EMIF1_D2                0x01100402U
#define GPIO_82_ESC_RX0_DATA2           0x0110040AU
#define GPIO_82_SD3_C2                  0x0110040BU

#define GPIO_83_GPIO83                  0x01100600U
#define GPIO_83_EPWM12_B                0x01100601U
#define GPIO_83_EMIF1_D1                0x01100602U
#define GPIO_83_ESC_RX0_DATA3           0x0110060AU
#define GPIO_83_SD3_D2                  0x0110060BU

#define GPIO_84_GPIO84                  0x01100800U
#define GPIO_84_EPWM12_B                0x01100801U
#define GPIO_84_EMIF1_D1                0x01100802U
#define GPIO_84_EMIF1_CS4N              0x01100803U
#define GPIO_84_SPIC_PICO               0x01100805U
#define GPIO_84_UARTA_TX                0x01100806U
#define GPIO_84_MCANF_RX                0x01100807U
#define GPIO_84_ESC_TX0_ENA             0x0110080AU
#define GPIO_84_SD3_C2                  0x0110080BU
#define GPIO_84_FSITXC_D1               0x0110080DU
#define GPIO_84_ESC_RX0_DATA3           0x0110080EU
#define GPIO_84_ESC_GPO24               0x0110080FU

#define GPIO_85_GPIO85                  0x01100A00U
#define GPIO_85_EPWM13_A                0x01100A01U
#define GPIO_85_EMIF1_D0                0x01100A02U
#define GPIO_85_UARTA_RX                0x01100A06U
#define GPIO_85_EMIF1_DQM2              0x01100A09U
#define GPIO_85_ESC_TX0_CLK             0x01100A0AU
#define GPIO_85_SD3_D3                  0x01100A0BU

#define GPIO_86_GPIO86                  0x01100C00U
#define GPIO_86_EPWM13_B                0x01100C01U
#define GPIO_86_EMIF1_A13               0x01100C02U
#define GPIO_86_EMIF1_CAS               0x01100C03U
#define GPIO_86_UARTD_TX                0x01100C06U
#define GPIO_86_ESC_PHY0_LINKSTATUS     0x01100C0AU
#define GPIO_86_SD3_C3                  0x01100C0BU

#define GPIO_87_GPIO87                  0x01100E00U
#define GPIO_87_EPWM14_A                0x01100E01U
#define GPIO_87_EMIF1_A14               0x01100E02U
#define GPIO_87_EMIF1_RAS               0x01100E03U
#define GPIO_87_UARTD_RX                0x01100E06U
#define GPIO_87_EMIF1_DQM3              0x01100E09U
#define GPIO_87_ESC_TX0_DATA0           0x01100E0AU
#define GPIO_87_SD3_D4                  0x01100E0BU

#define GPIO_88_GPIO88                  0x01101000U
#define GPIO_88_EPWM14_B                0x01101001U
#define GPIO_88_EMIF1_A15               0x01101002U
#define GPIO_88_EMIF1_DQM0              0x01101003U
#define GPIO_88_EMIF1_DQM1              0x01101009U
#define GPIO_88_ESC_TX0_DATA1           0x0110100AU
#define GPIO_88_SD3_C4                  0x0110100BU

#define GPIO_89_GPIO89                  0x01101200U
#define GPIO_89_EPWM15_A                0x01101201U
#define GPIO_89_EMIF1_A16               0x01101202U
#define GPIO_89_EMIF1_DQM1              0x01101203U
#define GPIO_89_SPID_PTE                0x01101205U
#define GPIO_89_EMIF1_CAS               0x01101209U
#define GPIO_89_ESC_TX0_DATA2           0x0110120AU
#define GPIO_89_SD1_D3                  0x0110120BU
#define GPIO_89_SD4_D1                  0x0110120EU

#define GPIO_90_GPIO90                  0x01101400U
#define GPIO_90_EPWM15_B                0x01101401U
#define GPIO_90_EMIF1_A17               0x01101402U
#define GPIO_90_EMIF1_DQM2              0x01101403U
#define GPIO_90_SPID_CLK                0x01101405U
#define GPIO_90_EMIF1_RAS               0x01101409U
#define GPIO_90_ESC_TX0_DATA3           0x0110140AU
#define GPIO_90_SD1_C3                  0x0110140BU
#define GPIO_90_SD4_C1                  0x0110140EU

#define GPIO_91_GPIO91                  0x01101600U
#define GPIO_91_EPWM16_A                0x01101601U
#define GPIO_91_EMIF1_A18               0x01101602U
#define GPIO_91_EMIF1_DQM3              0x01101603U
#define GPIO_91_SPID_PICO               0x01101605U
#define GPIO_91_I2CA_SDA                0x01101606U
#define GPIO_91_MCAND_TX                0x01101607U
#define GPIO_91_EMIF1_DQM2              0x01101609U
#define GPIO_91_SD4_D2                  0x0110160BU
#define GPIO_91_OUTPUTXBAR9             0x0110160EU

#define GPIO_92_GPIO92                  0x01101800U
#define GPIO_92_EPWM16_B                0x01101801U
#define GPIO_92_EMIF1_A19               0x01101802U
#define GPIO_92_EMIF1_BA1               0x01101803U
#define GPIO_92_SPID_POCI               0x01101805U
#define GPIO_92_I2CA_SCL                0x01101806U
#define GPIO_92_MCAND_RX                0x01101807U
#define GPIO_92_EMIF1_DQM0              0x01101809U
#define GPIO_92_FSIRXD_CLK              0x0110180AU
#define GPIO_92_SD4_C2                  0x0110180BU
#define GPIO_92_OUTPUTXBAR10            0x0110180EU

#define GPIO_93_GPIO93                  0x01101A00U
#define GPIO_93_EPWM17_A                0x01101A01U
#define GPIO_93_EMIF1_A20               0x01101A02U
#define GPIO_93_EMIF1_BA0               0x01101A03U
#define GPIO_93_SPID_CLK                0x01101A05U
#define GPIO_93_ESC_TX1_CLK             0x01101A0AU
#define GPIO_93_SD4_D3                  0x01101A0BU
#define GPIO_93_OUTPUTXBAR11            0x01101A0EU

#define GPIO_94_GPIO94                  0x01101C00U
#define GPIO_94_EPWM17_B                0x01101C01U
#define GPIO_94_EMIF1_A21               0x01101C02U
#define GPIO_94_SPID_PTE                0x01101C05U
#define GPIO_94_EMIF1_BA1               0x01101C09U
#define GPIO_94_ESC_TX1_ENA             0x01101C0AU
#define GPIO_94_SD4_C3                  0x01101C0BU
#define GPIO_94_OUTPUTXBAR12            0x01101C0EU

#define GPIO_95_GPIO95                  0x01101E00U
#define GPIO_95_EPWM18_A                0x01101E01U
#define GPIO_95_ESC_GPO10               0x01101E0AU
#define GPIO_95_SD1_D1                  0x01101E0BU
#define GPIO_95_OUTPUTXBAR13            0x01101E0EU

#define GPIO_96_GPIO96                  0x018C0000U
#define GPIO_96_EPWM18_B                0x018C0001U
#define GPIO_96_ESC_GPO11               0x018C000AU
#define GPIO_96_SD1_C1                  0x018C000BU
#define GPIO_96_OUTPUTXBAR14            0x018C000EU

#define GPIO_97_GPIO97                  0x018C0200U
#define GPIO_97_ESC_GPI17               0x018C020AU
#define GPIO_97_SD1_D2                  0x018C020BU
#define GPIO_97_OUTPUTXBAR15            0x018C020EU

#define GPIO_98_GPIO98                  0x018C0400U
#define GPIO_98_ESC_GPI18               0x018C040AU
#define GPIO_98_SD1_C2                  0x018C040BU
#define GPIO_98_OUTPUTXBAR16            0x018C040EU

#define GPIO_99_GPIO99                  0x018C0600U
#define GPIO_99_EPWM8_A                 0x018C0601U
#define GPIO_99_EMIF1_DQM3              0x018C0602U
#define GPIO_99_EMIF1_D17               0x018C0603U
#define GPIO_99_ESC_GPI21               0x018C060AU
#define GPIO_99_SD4_D4                  0x018C060BU

#define GPIO_100_GPIO100                0x018C0800U
#define GPIO_100_EPWM9_A                0x018C0801U
#define GPIO_100_EMIF1_BA1              0x018C0802U
#define GPIO_100_EMIF1_D24              0x018C0803U
#define GPIO_100_SPIC_PICO              0x018C0805U
#define GPIO_100_SPIA_PICO              0x018C0806U
#define GPIO_100_SD1_D1                 0x018C0809U
#define GPIO_100_ESC_GPI0               0x018C080AU
#define GPIO_100_SD4_C4                 0x018C080BU
#define GPIO_100_FSITXA_D0              0x018C080DU
#define GPIO_100_FSIRXD_D1              0x018C080EU

#define GPIO_101_GPIO101                0x018C0A00U
#define GPIO_101_EPWM18_A               0x018C0A01U
#define GPIO_101_EMIF1_A5               0x018C0A02U
#define GPIO_101_SPIC_POCI              0x018C0A05U
#define GPIO_101_ESC_GPI1               0x018C0A0AU
#define GPIO_101_FSITXA_D1              0x018C0A0DU

#define GPIO_103_GPIO103                0x018C0E00U
#define GPIO_103_EPWM8_B                0x018C0E01U
#define GPIO_103_EMIF1_BA0              0x018C0E02U
#define GPIO_103_EMIF1_D3               0x018C0E03U
#define GPIO_103_SPIC_PTE               0x018C0E05U
#define GPIO_103_ESC_GPI3               0x018C0E0AU
#define GPIO_103_SD4_C4                 0x018C0E0BU
#define GPIO_103_FSIRXA_D0              0x018C0E0DU
#define GPIO_103_ESC_GPO25              0x018C0E0FU

#define GPIO_105_GPIO105                0x018C1200U
#define GPIO_105_EPWM18_B               0x018C1201U
#define GPIO_105_I2CA_SCL               0x018C1205U
#define GPIO_105_ESC_GPI5               0x018C120AU
#define GPIO_105_SD3_C1                 0x018C120BU
#define GPIO_105_FSIRXA_CLK             0x018C120DU

#define GPIO_127_GPIO127                0x01901E00U
#define GPIO_127_EPWM18_A               0x01901E01U
#define GPIO_127_EMIF1_D18              0x01901E02U
#define GPIO_127_EMIF1_A11              0x01901E03U
#define GPIO_127_SPID_POCI              0x01901E05U
#define GPIO_127_ESC_GPI27              0x01901E0AU
#define GPIO_127_SD1_C3                 0x01901E0BU
#define GPIO_127_FSIRXC_D1              0x01901E0DU
#define GPIO_127_ESC_SYNC0              0x01901E0EU
#define GPIO_127_ESC_GPO26              0x01901E0FU

#define GPIO_219_GPIO219                0x03101600U
#define GPIO_219_ERRORSTS               0x03101601U
#define GPIO_219_EMIF1_A19              0x03101602U
#define GPIO_219_EPWM18_B               0x03101603U
#define GPIO_219_OUTPUTXBAR1            0x03101609U
#define GPIO_219_XCLKOUT                0x0310160AU
#define GPIO_219_SD2_C1                 0x0310160BU
#define GPIO_219_ESC_GPI8               0x0310160DU
#define GPIO_219_ESC_TX0_ENA            0x0310160EU
#define GPIO_219_ESC_GPO27              0x0310160FU

#define GPIO_220_GPIO220                0x03101800U
#define GPIO_220_EPWM6_A                0x03101801U
#define GPIO_220_EMIF1_A20              0x03101802U
#define GPIO_220_SPID_POCI              0x03101805U
#define GPIO_220_MCANC_TX               0x03101806U
#define GPIO_220_OUTPUTXBAR2            0x03101809U
#define GPIO_220_SD3_D3                 0x0310180BU
#define GPIO_220_ESC_GPI9               0x0310180DU
#define GPIO_220_ESC_GPO28              0x0310180FU

#define GPIO_221_GPIO221                0x03101A00U
#define GPIO_221_EPWM6_B                0x03101A01U
#define GPIO_221_EMIF1_A21              0x03101A02U
#define GPIO_221_EMIF1_CAS              0x03101A03U
#define GPIO_221_SPID_PTE               0x03101A05U
#define GPIO_221_MCANC_RX               0x03101A06U
#define GPIO_221_OUTPUTXBAR3            0x03101A09U
#define GPIO_221_SD3_C3                 0x03101A0BU
#define GPIO_221_ESC_GPI10              0x03101A0DU
#define GPIO_221_ESC_GPO29              0x03101A0FU

#define GPIO_222_GPIO222                0x03101C00U
#define GPIO_222_TDI                    0x03101C01U
#define GPIO_222_EPWM7_A                0x03101C02U
#define GPIO_222_SPID_PICO              0x03101C05U
#define GPIO_222_UARTB_TX               0x03101C06U
#define GPIO_222_I2CB_SCL               0x03101C07U
#define GPIO_222_OUTPUTXBAR4            0x03101C09U
#define GPIO_222_SPIC_CLK               0x03101C0AU
#define GPIO_222_SD3_D4                 0x03101C0BU
#define GPIO_222_ESC_GPI11              0x03101C0DU
#define GPIO_222_ESC_GPO30              0x03101C0FU

#define GPIO_223_GPIO223                0x03101E00U
#define GPIO_223_TDO                    0x03101E01U
#define GPIO_223_EPWM7_B                0x03101E02U
#define GPIO_223_SPID_CLK               0x03101E05U
#define GPIO_223_UARTB_RX               0x03101E06U
#define GPIO_223_I2CB_SDA               0x03101E07U
#define GPIO_223_OUTPUTXBAR5            0x03101E09U
#define GPIO_223_SPIC_PTE               0x03101E0AU
#define GPIO_223_SD3_C4                 0x03101E0BU
#define GPIO_223_ESC_GPI12              0x03101E0DU
#define GPIO_223_ESC_GPO31              0x03101E0FU

#define GPIO_160_AIO160                 0x028C0000U
#define GPIO_160_SD3_C2                 0x028C000BU

#define GPIO_161_AIO161                 0x028C0200U
#define GPIO_161_SD3_D2                 0x028C020BU

#define GPIO_162_AIO162                 0x028C0400U
#define GPIO_162_SD2_C2                 0x028C040BU

#define GPIO_163_AIO163                 0x028C0600U
#define GPIO_163_SD2_D2                 0x028C060BU

#define GPIO_164_AIO164                 0x028C0800U
#define GPIO_164_SD2_C3                 0x028C080BU

#define GPIO_165_AIO165                 0x028C0A00U
#define GPIO_165_SD2_D3                 0x028C0A0BU

#define GPIO_224_GPIO224                0x038C0000U
#define GPIO_224_EPWM12_A               0x038C0001U
#define GPIO_224_EPWM12_B               0x038C0002U
#define GPIO_224_SPIB_POCI              0x038C0005U
#define GPIO_224_MCAND_RX               0x038C0006U
#define GPIO_224_OUTPUTXBAR5            0x038C0009U
#define GPIO_224_SD4_D2                 0x038C000BU
#define GPIO_224_ADCA_EXTMUXSEL0        0x038C000EU
#define GPIO_224_ESC_GPO8               0x038C000FU

#define GPIO_225_GPIO225                0x038C0200U
#define GPIO_225_EPWM11_B               0x038C0201U
#define GPIO_225_SPIB_PICO              0x038C0205U
#define GPIO_225_I2CB_SDA               0x038C0206U
#define GPIO_225_UARTF_TX               0x038C0207U
#define GPIO_225_OUTPUTXBAR4            0x038C0209U
#define GPIO_225_SD4_C1                 0x038C020BU
#define GPIO_225_ADCA_EXTMUXSEL1        0x038C020EU
#define GPIO_225_ESC_GPO9               0x038C020FU

#define GPIO_226_GPIO226                0x038C0400U
#define GPIO_226_EPWM10_A               0x038C0401U
#define GPIO_226_SPIA_PTE               0x038C0405U
#define GPIO_226_MCAND_TX               0x038C0406U
#define GPIO_226_UARTF_RX               0x038C0407U
#define GPIO_226_OUTPUTXBAR1            0x038C0409U
#define GPIO_226_SD1_C3                 0x038C040AU
#define GPIO_226_SD1_D3                 0x038C040BU
#define GPIO_226_ADCA_EXTMUXSEL2        0x038C040EU
#define GPIO_226_ESC_GPO10              0x038C040FU

#define GPIO_227_GPIO227                0x038C0600U
#define GPIO_227_EPWM14_B               0x038C0601U
#define GPIO_227_SPIA_CLK               0x038C0605U
#define GPIO_227_OUTPUTXBAR4            0x038C0609U
#define GPIO_227_SD2_C2                 0x038C060BU
#define GPIO_227_ADCA_EXTMUXSEL3        0x038C060EU

#define GPIO_228_GPIO228                0x038C0800U
#define GPIO_228_EPWM18_A               0x038C0801U
#define GPIO_228_EPWM13_A               0x038C0802U
#define GPIO_228_SPIB_POCI              0x038C0805U
#define GPIO_228_LINB_TX                0x038C0806U
#define GPIO_228_OUTPUTXBAR1            0x038C0809U
#define GPIO_228_SENT4                  0x038C080AU
#define GPIO_228_SD2_D1                 0x038C080BU

#define GPIO_229_GPIO229                0x038C0A00U
#define GPIO_229_EPWM17_B               0x038C0A01U
#define GPIO_229_EPWM12_B               0x038C0A02U
#define GPIO_229_SPIB_PICO              0x038C0A05U
#define GPIO_229_MCANA_RX               0x038C0A06U
#define GPIO_229_SENT3                  0x038C0A0AU
#define GPIO_229_SD1_C4                 0x038C0A0BU

#define GPIO_166_AIO166                 0x028C0C00U
#define GPIO_166_SD4_C1                 0x028C0C0BU

#define GPIO_167_AIO167                 0x028C0E00U
#define GPIO_167_SD4_D1                 0x028C0E0BU

#define GPIO_168_AIO168                 0x028C1000U
#define GPIO_168_SD3_C3                 0x028C100BU

#define GPIO_169_AIO169                 0x028C1200U
#define GPIO_169_SD3_D3                 0x028C120BU

#define GPIO_170_AIO170                 0x028C1400U
#define GPIO_170_SD3_C4                 0x028C140BU

#define GPIO_171_AIO171                 0x028C1600U
#define GPIO_171_SD3_D4                 0x028C160BU

#define GPIO_172_AIO172                 0x028C1800U
#define GPIO_172_SD1_C1                 0x028C180BU

#define GPIO_173_AIO173                 0x028C1A00U
#define GPIO_173_SD1_D1                 0x028C1A0BU

#define GPIO_174_AIO174                 0x028C1C00U
#define GPIO_174_SD2_C4                 0x028C1C0BU

#define GPIO_175_AIO175                 0x028C1E00U
#define GPIO_175_SD2_D4                 0x028C1E0BU

#define GPIO_230_GPIO230                0x038C0C00U
#define GPIO_230_EPWM11_A               0x038C0C01U
#define GPIO_230_SYNCOUT                0x038C0C03U
#define GPIO_230_I2CB_SCL               0x038C0C06U
#define GPIO_230_OUTPUTXBAR3            0x038C0C09U
#define GPIO_230_SD4_D1                 0x038C0C0BU
#define GPIO_230_ADCB_EXTMUXSEL0        0x038C0C0EU

#define GPIO_231_GPIO231                0x038C0E00U
#define GPIO_231_EPWM10_B               0x038C0E01U
#define GPIO_231_SPIA_PICO              0x038C0E05U
#define GPIO_231_MCAND_RX               0x038C0E06U
#define GPIO_231_OUTPUTXBAR2            0x038C0E09U
#define GPIO_231_SD1_C3                 0x038C0E0BU
#define GPIO_231_ADCB_EXTMUXSEL1        0x038C0E0EU

#define GPIO_232_GPIO232                0x038C1000U
#define GPIO_232_EPWM14_A               0x038C1001U
#define GPIO_232_EPWM8_B                0x038C1002U
#define GPIO_232_SPIA_POCI              0x038C1005U
#define GPIO_232_OUTPUTXBAR3            0x038C1009U
#define GPIO_232_SENT6                  0x038C100AU
#define GPIO_232_SD3_D1                 0x038C100BU
#define GPIO_232_ESC_PHY0_LINKSTATUS    0x038C100DU
#define GPIO_232_ADCB_EXTMUXSEL2        0x038C100EU
#define GPIO_232_ESC_GPO11              0x038C100FU

#define GPIO_233_GPIO233                0x038C1200U
#define GPIO_233_EPWM18_B               0x038C1201U
#define GPIO_233_EPWM13_B               0x038C1202U
#define GPIO_233_LINB_RX                0x038C1206U
#define GPIO_233_OUTPUTXBAR2            0x038C1209U
#define GPIO_233_SENT5                  0x038C120AU
#define GPIO_233_SD2_C1                 0x038C120BU
#define GPIO_233_ESC_PHY1_LINKSTATUS    0x038C120DU
#define GPIO_233_ADCB_EXTMUXSEL3        0x038C120EU
#define GPIO_233_ESC_GPO12              0x038C120FU

#define GPIO_234_GPIO234                0x038C1400U
#define GPIO_234_EPWM17_A               0x038C1401U
#define GPIO_234_EPWM12_A               0x038C1402U
#define GPIO_234_SPIB_PTE               0x038C1405U
#define GPIO_234_MCANA_TX               0x038C1406U
#define GPIO_234_SENT2                  0x038C140AU
#define GPIO_234_SD1_D4                 0x038C140BU
#define GPIO_234_ESC_GPO13              0x038C140FU

#define GPIO_235_GPIO235                0x038C1600U
#define GPIO_235_EPWM9_B                0x038C1601U
#define GPIO_235_SPIB_CLK               0x038C1605U
#define GPIO_235_MCANA_RX               0x038C1606U
#define GPIO_235_SENT1                  0x038C160AU
#define GPIO_235_SD1_C1                 0x038C160BU
#define GPIO_235_ESC_GPO14              0x038C160FU

#define GPIO_176_AIO176                 0x02900000U
#define GPIO_176_SD4_C2                 0x0290000BU

#define GPIO_177_AIO177                 0x02900200U
#define GPIO_177_SD4_D2                 0x0290020BU

#define GPIO_178_AIO178                 0x02900400U
#define GPIO_178_SD4_C3                 0x0290040BU

#define GPIO_179_AIO179                 0x02900600U
#define GPIO_179_SD4_D3                 0x0290060BU

#define GPIO_180_AIO180                 0x02900800U
#define GPIO_180_SD1_C2                 0x0290080BU

#define GPIO_181_AIO181                 0x02900A00U
#define GPIO_181_SD1_D2                 0x02900A0BU

#define GPIO_182_AIO182                 0x02900C00U
#define GPIO_182_SD3_C1                 0x02900C0BU

#define GPIO_183_AIO183                 0x02900E00U
#define GPIO_183_SD3_D1                 0x02900E0BU

#define GPIO_184_AIO184                 0x02901000U
#define GPIO_184_SD3_C2                 0x0290100BU

#define GPIO_185_AIO185                 0x02901200U
#define GPIO_185_SD3_D2                 0x0290120BU

#define GPIO_236_GPIO236                0x038C1800U
#define GPIO_236_EPWM12_B               0x038C1801U
#define GPIO_236_EPWM8_A                0x038C1802U
#define GPIO_236_LINA_RX                0x038C1806U
#define GPIO_236_OUTPUTXBAR6            0x038C1809U
#define GPIO_236_SD4_C2                 0x038C180BU
#define GPIO_236_ESC_I2C_SDA            0x038C180DU
#define GPIO_236_ADCC_EXTMUXSEL0        0x038C180EU

#define GPIO_237_GPIO237                0x038C1A00U
#define GPIO_237_EPWM14_A               0x038C1A01U
#define GPIO_237_EPWM8_B                0x038C1A02U
#define GPIO_237_EPWM17_B               0x038C1A03U
#define GPIO_237_LINA_TX                0x038C1A06U
#define GPIO_237_I2CA_SDA               0x038C1A07U
#define GPIO_237_OUTPUTXBAR7            0x038C1A09U
#define GPIO_237_SD4_D3                 0x038C1A0BU
#define GPIO_237_ESC_I2C_SCL            0x038C1A0DU
#define GPIO_237_ADCC_EXTMUXSEL1        0x038C1A0EU

#define GPIO_238_GPIO238                0x038C1C00U
#define GPIO_238_EPWM15_B               0x038C1C01U
#define GPIO_238_OUTPUTXBAR6            0x038C1C09U
#define GPIO_238_SD1_D3                 0x038C1C0AU
#define GPIO_238_SD2_C3                 0x038C1C0BU
#define GPIO_238_ESC_SYNC0              0x038C1C0DU
#define GPIO_238_ADCC_EXTMUXSEL2        0x038C1C0EU
#define GPIO_238_ESC_GPO15              0x038C1C0FU

#define GPIO_239_GPIO239                0x038C1E00U
#define GPIO_239_EPWM16_B               0x038C1E01U
#define GPIO_239_LINB_TX                0x038C1E06U
#define GPIO_239_I2CA_SCL               0x038C1E07U
#define GPIO_239_OUTPUTXBAR8            0x038C1E09U
#define GPIO_239_SD2_C4                 0x038C1E0BU
#define GPIO_239_ESC_SYNC1              0x038C1E0DU
#define GPIO_239_ADCC_EXTMUXSEL3        0x038C1E0EU
#define GPIO_239_ESC_GPO16              0x038C1E0FU

#define GPIO_186_AIO186                 0x02901400U
#define GPIO_186_SD1_C1                 0x0290140BU

#define GPIO_187_AIO187                 0x02901600U
#define GPIO_187_SD1_D1                 0x0290160BU

#define GPIO_188_AIO188                 0x02901800U
#define GPIO_188_SD1_C2                 0x0290180BU

#define GPIO_189_AIO189                 0x02901A00U
#define GPIO_189_SD1_D2                 0x02901A0BU

#define GPIO_190_AIO190                 0x02901C00U
#define GPIO_190_SD1_C3                 0x02901C0BU

#define GPIO_191_AIO191                 0x02901E00U
#define GPIO_191_SD1_D3                 0x02901E0BU

#define GPIO_192_AIO192                 0x030C0000U
#define GPIO_192_SD1_C3                 0x030C000BU

#define GPIO_193_AIO193                 0x030C0200U
#define GPIO_193_SD1_D3                 0x030C020BU

#define GPIO_194_AIO194                 0x030C0400U
#define GPIO_194_SD1_C4                 0x030C040BU

#define GPIO_195_AIO195                 0x030C0600U
#define GPIO_195_SD1_D4                 0x030C060BU

#define GPIO_240_GPIO240                0x03900000U
#define GPIO_240_EPWM14_B               0x03900001U
#define GPIO_240_SPID_PICO              0x03900005U
#define GPIO_240_SD4_C3                 0x0390000BU
#define GPIO_240_ESC_LED_RUN            0x0390000DU
#define GPIO_240_ADCD_EXTMUXSEL0        0x0390000EU

#define GPIO_241_GPIO241                0x03900200U
#define GPIO_241_EPWM8_A                0x03900201U
#define GPIO_241_SPID_CLK               0x03900205U
#define GPIO_241_SD4_D4                 0x0390020BU
#define GPIO_241_ESC_LED_ERR            0x0390020DU
#define GPIO_241_ADCD_EXTMUXSEL1        0x0390020EU
#define GPIO_241_ESC_GPO17              0x0390020FU

#define GPIO_242_GPIO242                0x03900400U
#define GPIO_242_SD1_D4                 0x03900406U
#define GPIO_242_I2CA_SDA               0x03900407U
#define GPIO_242_OUTPUTXBAR9            0x03900409U
#define GPIO_242_SENT1                  0x0390040AU
#define GPIO_242_SD2_D2                 0x0390040BU
#define GPIO_242_ESC_LED_STATE_RUN      0x0390040DU
#define GPIO_242_ADCD_EXTMUXSEL2        0x0390040EU
#define GPIO_242_ESC_GPO18              0x0390040FU

#define GPIO_243_GPIO243                0x03900600U
#define GPIO_243_EPWM8_B                0x03900601U
#define GPIO_243_SENT2                  0x0390060AU
#define GPIO_243_SD2_D4                 0x0390060BU
#define GPIO_243_ESC_LED_LINK0_ACTIVE   0x0390060DU
#define GPIO_243_ADCD_EXTMUXSEL3        0x0390060EU
#define GPIO_243_ESC_GPO19              0x0390060FU

#define GPIO_244_GPIO244                0x03900800U
#define GPIO_244_SPIC_PTE               0x03900805U
#define GPIO_244_SENT5                  0x0390080AU
#define GPIO_244_SD4_C4                 0x0390080BU
#define GPIO_244_ESC_LED_LINK1_ACTIVE   0x0390080DU

#define GPIO_245_GPIO245                0x03900A00U
#define GPIO_245_SPIC_POCI              0x03900A05U
#define GPIO_245_SENT6                  0x03900A0AU
#define GPIO_245_SD3_C1                 0x03900A0BU
#define GPIO_245_ESC_PHY_RESETN         0x03900A0DU

#define GPIO_196_AIO196                 0x030C0800U
#define GPIO_196_SD4_C4                 0x030C080BU

#define GPIO_197_AIO197                 0x030C0A00U
#define GPIO_197_SD4_D4                 0x030C0A0BU

#define GPIO_198_AIO198                 0x030C0C00U
#define GPIO_198_SD1_C4                 0x030C0C0BU

#define GPIO_199_AIO199                 0x030C0E00U
#define GPIO_199_SD1_D4                 0x030C0E0BU

#define GPIO_200_AIO200                 0x030C1000U
#define GPIO_200_SD2_C1                 0x030C100BU

#define GPIO_201_AIO201                 0x030C1200U
#define GPIO_201_SD2_D1                 0x030C120BU

#define GPIO_202_AIO202                 0x030C1400U
#define GPIO_202_SD2_C1                 0x030C140BU

#define GPIO_203_AIO203                 0x030C1600U
#define GPIO_203_SD2_D1                 0x030C160BU

#define GPIO_204_AIO204                 0x030C1800U
#define GPIO_204_SD3_C3                 0x030C180BU

#define GPIO_205_AIO205                 0x030C1A00U
#define GPIO_205_SD3_D3                 0x030C1A0BU

#define GPIO_246_GPIO246                0x03900C00U
#define GPIO_246_EPWM16_A               0x03900C01U
#define GPIO_246_SPID_PTE               0x03900C05U
#define GPIO_246_MCANC_RX               0x03900C06U
#define GPIO_246_OUTPUTXBAR7            0x03900C09U
#define GPIO_246_SD1_D1                 0x03900C0BU
#define GPIO_246_ADCE_EXTMUXSEL0        0x03900C0EU
#define GPIO_246_ESC_GPO20              0x03900C0FU

#define GPIO_247_GPIO247                0x03900E00U
#define GPIO_247_EPWM15_A               0x03900E01U
#define GPIO_247_ERRORSTS               0x03900E02U
#define GPIO_247_SPID_POCI              0x03900E05U
#define GPIO_247_MCANC_RX               0x03900E06U
#define GPIO_247_LINA_TX                0x03900E07U
#define GPIO_247_OUTPUTXBAR5            0x03900E09U
#define GPIO_247_SD2_D3                 0x03900E0BU
#define GPIO_247_ADCE_EXTMUXSEL1        0x03900E0EU
#define GPIO_247_ESC_GPO21              0x03900E0FU

#define GPIO_248_GPIO248                0x03901000U
#define GPIO_248_EMIF1_SDCKE            0x03901002U
#define GPIO_248_SPIC_PICO              0x03901005U
#define GPIO_248_SENT3                  0x0390100AU
#define GPIO_248_SD1_C2                 0x0390100BU
#define GPIO_248_ESC_LED_RUN            0x0390100DU
#define GPIO_248_ADCE_EXTMUXSEL2        0x0390100EU
#define GPIO_248_ESC_GPO22              0x0390100FU

#define GPIO_249_GPIO249                0x03901200U
#define GPIO_249_SPIC_CLK               0x03901205U
#define GPIO_249_SENT4                  0x0390120AU
#define GPIO_249_SD1_D2                 0x0390120BU
#define GPIO_249_ESC_PHY0_LINKSTATUS    0x0390120DU
#define GPIO_249_ADCE_EXTMUXSEL3        0x0390120EU
#define GPIO_249_ESC_GPO23              0x0390120FU

#define GPIO_206_AIO206                 0x030C1C00U
#define GPIO_206_SD3_C4                 0x030C1C0BU

#define GPIO_207_AIO207                 0x030C1E00U
#define GPIO_207_SD3_D4                 0x030C1E0BU

#define GPIO_208_AIO208                 0x03100000U
#define GPIO_208_SD2_C2                 0x0310000BU

#define GPIO_209_AIO209                 0x03100200U
#define GPIO_209_SD2_D2                 0x0310020BU

#define GPIO_210_AIO210                 0x03100400U
#define GPIO_210_SD2_C3                 0x0310040BU

#define GPIO_211_AIO211                 0x03100600U
#define GPIO_211_SD2_D3                 0x0310060BU

#define GPIO_212_AIO212                 0x03100800U
#define GPIO_212_SD2_C4                 0x0310080BU

#define GPIO_213_AIO213                 0x03100A00U
#define GPIO_213_SD2_D4                 0x03100A0BU

#endif // PIN_MAP_H
