/********************************************************************
 * Copyright (C) 2025 Texas Instruments Incorporated.
 *
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

#ifndef SDLR_LCM_H_
#define SDLR_LCM_H_

/* SDL LCM Register features timeouts */

#define SDL_LCM_SELF_TEST_TIMEOUT       300U
#define SDL_LCM_ERROR_FORCE_TIMEOUT     5U
#define SDL_LCM_PARITY_TIMEOUT          10U

/* SDL_LCM_Register_Offsets LCM Register Offsets */

#define SDL_LCM_REVISION         0x0U        /* IP Revision tie-off value */
#define SDL_LCM_CONTROL          0x8U        /* LCM Control configuration */
#define SDL_LCM_STATUS           0x20U       /* LCM status register */
#define SDL_LCM_STATUS_CLEAR     0x28U       /* LCM Status clear register */
#define SDL_LCM_PARITY_TEST      0x68U       /* Enabling the parity test feature */
#define SDL_LCM_LOCK             0x70U       /* LCM lock configuration */
#define SDL_LCM_COMMIT           0x78U       /* LCM commit configuration */

/* SDL_LCM_REVISION Bit Fields in LCM_REVISION Register */

#define SDL_LCM_REVISION_MINOR_S             0U             /* Minor Revision shift */
#define SDL_LCM_REVISION_MINOR_M             0x3FU          /* Minor Revision mask */
#define SDL_LCM_REVISION_CUSTOM_S            6U             /* Custom Module shift */
#define SDL_LCM_REVISION_CUSTOM_M            0xC0U          /* Custom Module mask */
#define SDL_LCM_REVISION_MAJOR_S             8U             /* Major Revision shift */
#define SDL_LCM_REVISION_MAJOR_M             0x700U         /* Major Revision mask */
#define SDL_LCM_REVISION_FUNC_S              16U            /* Functional Release shift */
#define SDL_LCM_REVISION_FUNC_M              0xFFF0000U     /* Functional Release mask */
#define SDL_LCM_REVISION_SCHEME_S            30U            /* Scheme shift */
#define SDL_LCM_REVISION_SCHEME_M            0xC0000000U    /* Scheme mask */

/* SDL_LCM_CONTROL Bit Fields in LCM_CONTROL Register */

#define SDL_LCM_CONTROL_CMPEN                0x1U        /* Enable/disable lockstep compare */
#define SDL_LCM_CONTROL_STEN                 0x10000U    /* Self-test enable */
#define SDL_LCM_CONTROL_CMP1_ERR_FORCE       0x80000U    /* Force error on comparator-1 */
#define SDL_LCM_CONTROL_CMP2_ERR_FORCE       0x200000U   /* Force error on comparator-2 */

/* SDL_LCM_STATUS Bit Fields in LCM_STATUS Register */

#define SDL_LCM_STATUS_LSEN                  0x1U        /* Lockstep config status */
#define SDL_LCM_STATUS_CMP_FAIL              0x2U        /* Lockstep compare fail */
#define SDL_LCM_STATUS_DBGCON                0x100U      /* Debugger connected */
#define SDL_LCM_STATUS_STPASS                0x10000U    /* Self-test pass status */
#define SDL_LCM_STATUS_STDONE                0x20000U    /* Self-test done status */
#define SDL_LCM_STATUS_STACTIVE              0x40000U    /* Self-test active */
#define SDL_LCM_STATUS_CMP1_ERR_FORCE_PASS   0x80000U    /* Comparator-1 error force fail */
#define SDL_LCM_STATUS_CMP1_ERR_FORCE_DONE   0x100000U   /* Comparator-1 error force done */
#define SDL_LCM_STATUS_CMP2_ERR_FORCE_PASS   0x200000U   /* Comparator-2 error force fail */
#define SDL_LCM_STATUS_CMP2_ERR_FORCE_DONE   0x400000U   /* Comparator-2 error force done */

/* SDL_LCM_STATUS_CLEAR Bit Fields in LCM_STATUS_CLEAR Register */

#define SDL_LCM_STATUS_CLEAR_CMP_FAIL              0x2U        /* Clear compare fail */
#define SDL_LCM_STATUS_CLEAR_STPASS                0x10000U    /* Clear self-test pass */
#define SDL_LCM_STATUS_CLEAR_STDONE                0x20000U    /* Clear self-test done */
#define SDL_LCM_STATUS_CLEAR_CMP1_ERR_FORCE_PASS   0x80000U    /* Clear comparator-1 fail */
#define SDL_LCM_STATUS_CLEAR_CMP1_ERR_FORCE_DONE   0x100000U   /* Clear comparator-1 done */
#define SDL_LCM_STATUS_CLEAR_CMP2_ERR_FORCE_PASS   0x200000U   /* Clear comparator-2 fail */
#define SDL_LCM_STATUS_CLEAR_CMP2_ERR_FORCE_DONE   0x400000U   /* Clear comparator-2 done */

/* SDL_LCM_PARITY_TEST Bit Fields in LCM_PARITY_TEST Register */

#define SDL_LCM_PARITY_TEST_TESTEN_S   0U        /* Parity test enable shift */
#define SDL_LCM_PARITY_TEST_TESTEN_M   0xFU      /* Parity test enable mask */
#define SDL_LCM_PARITY_TEST_KEY        0xAU      /* Parity test enable */

/* SDL_LCM_LOCK Bit Fields in LCM_LOCK Register */

#define SDL_LCM_LOCK_LCM_CONTROL        0x4U         /* Lock config for LCM_CONTROL */
#define SDL_LCM_LOCK_LCM_STATUS_CLEAR   0x400U       /* Lock config for STATUS_CLEAR */
#define SDL_LCM_LOCK_PARITY_TEST        0x4000000U   /* Lock config for PARITY_TEST */

/* SDL_LCM_COMMIT Bit Fields in LCM_COMMIT Register */

#define SDL_LCM_COMMIT_LCM_CONTROL        0x4U         /* Commit config for LCM_CONTROL */
#define SDL_LCM_COMMIT_LCM_STATUS_CLEAR   0x400U       /* Commit config for STATUS_CLEAR */
#define SDL_LCM_COMMIT_PARITY_TEST        0x4000000U   /* Commit config for PARITY_TEST */

#endif /*SDLR_LCM_H_*/
