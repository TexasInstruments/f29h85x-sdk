/*
 *  Copyright (c) 2025 Texas Instruments Incorporated
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
 */

/**
 *  \file   dthe_sm3.c
 *
 *  \brief  This file contains the implementation of Dthe sha driver
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <string.h>
#include <stdint.h>
#include <security/drivers/crypto/dthe/dthe_sm3.h>

/* ========================================================================== */
/*                           Global variables                                */
/* ========================================================================== */
/** \brief Flag to check SHA in Progress */
DTHE_SM3_CryptoStateMachine_t  gDTHESM3InProgress = DTHE_SM3_CRYPTO_STATEMACHINE_NEW;

/** \brief sm3 Digest Count */
uint32_t              gDTHESM3digestCount;

/** \brief This is the Block Size for the SM3 in words */
#define DTHE_SM3_BLOCK_SIZE                  (16ULL)

/** \brief This is the Data Shift Size for the SM3 */
#define DTHE_SM3_SHIFT_SIZE                  (4U)

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void DTHE_SM3_pollInput_buff_available(const CSL_EIP52_SM3Regs* ptrSM3Regs);
static void DTHE_SM3_setHashMode(CSL_EIP52_SM3Regs* ptrSM3Regs, uint32_t hash_session);
static void DTHE_SM3_setHashLength_lower(CSL_EIP52_SM3Regs* ptrSM3Regs, uint32_t length);
static void DTHE_SM3_setHashLength_upper(CSL_EIP52_SM3Regs* ptrSM3Regs, uint32_t length);
static void DTHE_SM3_set_autoctrl(CSL_EIP52_SM3Regs* ptrSM3Regs, uint32_t auto_trigger);
static void DTHE_SM3_writeDataBlock(CSL_EIP52_SM3Regs* ptrSM3Regs, const uint32_t* ptrDataBlock, uint64_t blockSize);
static void DTHE_SM3_set_data_available(CSL_EIP52_SM3Regs* ptrSM3Regs, uint32_t all_input_available);
static void DTHE_SM3_pollOutputReady (const CSL_EIP52_SM3Regs* ptrSM3Regs);
static void DTHE_SM3_setHashDigest(CSL_EIP52_SM3Regs* ptrSM3Regs, const uint32_t* ptrDigest);
static void DTHE_SM3_getHashDigest(const CSL_EIP52_SM3Regs* ptrSM3Regs, uint32_t* ptrDigest);
static void DTHE_SM3_set_output_buff_available(CSL_EIP52_SM3Regs* ptrSM3Regs, uint32_t output_buffer_available);
static void DTHE_SM3_set_length (CSL_EIP52_SM3Regs* ptrSM3Regs, uint64_t length);


/* ========================================================================== */
/*                        Internal  Function Definitions                      */
/* ========================================================================== */


/**
 * \brief  wait until input buffer available for writing by host
 * checking the rfd_in field (6th bit) in the SM3_IO_BUF_CTRL_STAT register 
 * Indicates whether the widebus SM3 hash engine is ready to receive new data.
 * When asserted high the widebus SM3 hash engine is ready to receive new data.
 * 
 * \param ptrSM3Regs Pointer to the EIP52 SM3 Registers
 * 
 * 
*/
static void DTHE_SM3_pollInput_buff_available(const CSL_EIP52_SM3Regs* ptrSM3Regs)
{
    uint32_t     done = 0UL;

    /* Loop around till the condition is met: */
    while (done == 0UL)
    {
        done = CSL_FEXTR (ptrSM3Regs->SM3_IO_BUF_CTRL_STAT, 6U, 6U);
    }

    return;
}


/**
 * \brief  to indicate start of new hash session
 * When set to ‘1’, it indicates that the registered SM3 hash engine
 * must start processing a new hash session
 * This bit is automatically cleared when hash processing is started.
 * So when a new hash session is started with this bit set for the first block of a message, 
 * there is no need to update the new_hash bit for sequential blocks of the same message.
 * 
 * \param ptrSM3Regs       Pointer to the EIP52 SM3 Registers
 * \param hash_session     flag to start a new hash session
 * 
 * 
*/
static void DTHE_SM3_setHashMode(CSL_EIP52_SM3Regs* ptrSM3Regs, uint32_t hash_session)
{
    ptrSM3Regs->SM3_MODE_IN = hash_session;

    return;
}


/**
 * \brief The function is used to set the length of the block to be processed for the hash operation
 * ptr_length_block[0U] ----> lower 32 bits of message length
 * ptr_length_block[1U] ----> upper 32 bits of message length
 * 
 * \param ptrSM3Regs       Pointer to the EIP52 SM3 Registers
 * \param ptr_length_block       Pointer to the length Registers
 * 
 * 
*/
static void DTHE_SM3_setHashLength_lower(CSL_EIP52_SM3Regs* ptrSM3Regs, uint32_t length)
{
    ptrSM3Regs->SM3_LENGTH_IN_0 = length;

    return;
}

static void DTHE_SM3_setHashLength_upper(CSL_EIP52_SM3Regs* ptrSM3Regs, uint32_t length)
{
  ptrSM3Regs->SM3_LENGTH_IN_1 = length;

  return;
}


/**
 * \brief Enable register for the different dma request lines and the automatic trigger of the core.
 * When set to 1, dma requests or sm3_intr will assert to request new push or pop of data.
 * 
 * \param ptrSM3Regs       Pointer to the EIP52 SM3 Registers
 * \param  auto_trigger       Flag which is used to enable(1)/disable(0) the auto_ctrl
 * 
 * 
*/
static void DTHE_SM3_set_autoctrl(CSL_EIP52_SM3Regs* ptrSM3Regs, uint32_t auto_trigger)
{
    CSL_FINSR(ptrSM3Regs->SM3_SYSCONFIG, 0U, 0U, auto_trigger);

    return;
}


/**
 * \brief The function is used write the data block.
 * 
 * \param ptrSM3Regs       Pointer to the EIP52 SM3 Registers
 * \param ptrDataBlock     Pointer to the data block to be written
 * \param blockSize        Block Size. This is selected on the basis of the algorithm.
 * 
 * 
*/
static void DTHE_SM3_writeDataBlock(CSL_EIP52_SM3Regs* ptrSM3Regs, const uint32_t* ptrDataBlock, uint64_t blockSize)
{
    uint64_t index;

    for (index = 0ULL; index < blockSize; index = index + 1ULL)
    {
        ptrSM3Regs->SM3_DATA_IN[index] = ptrDataBlock[index];
    }

    return;
}


/**
 * \brief Data input available ; Pad message as 1(indicates it is the last message)
 * Length is available ; mode is available
 * 
 * \param ptrSM3Regs       Pointer to the EIP52 SM3 Registers
 * \param all_input_available - indicates all the inputs available
 * 
 * 
*/
static void DTHE_SM3_set_data_available(CSL_EIP52_SM3Regs* ptrSM3Regs, uint32_t all_input_available)
{
   ptrSM3Regs->SM3_IO_BUF_CTRL_STAT = all_input_available;

   return;
}


/**
 * \brief The function is used to poll until the SHA IP block is ready with the results
 * When this bit reads '1', this indicates that the widebus SM3 hash engine has placed the
 * result of the latest hash operation in the output buffer registers.
 * 
 * \param ptrSM3Regs       Pointer to the EIP52 SM3 Registers
 * 
 * 
*/
static void DTHE_SM3_pollOutputReady (const CSL_EIP52_SM3Regs* ptrSM3Regs)
{
    uint32_t     done = 0UL;

    /* Loop around till the condition is met: */
    while (done == 0UL)
    {
        done = CSL_FEXTR (ptrSM3Regs->SM3_IO_BUF_CTRL_STAT, 0U, 0U);
    }
    return;
}

/**
 * \brief to write the digest in registers
 * 
 * \param ptrSM3Regs       Pointer to the EIP52 SM3 Registers
 * \param  ptrDigest       Pointer to the digest populated by the API
 * 
 * 
*/
static void DTHE_SM3_setHashDigest(CSL_EIP52_SM3Regs* ptrSM3Regs, const uint32_t* ptrDigest)
{
    uint32_t index;

    for (index = 0UL; index < 8UL; index++)
    {
        ptrSM3Regs->SM3_DIGEST_IN[index] = ptrDigest[index];
    }

    return;
}

/**
 * \brief to read the digest out registers
 * 
 * \param ptrSM3Regs       Pointer to the EIP52 SM3 Registers
 * \param  ptrDigest       Pointer to the digest populated by the API
 * 
 * 
*/
static void DTHE_SM3_getHashDigest(const CSL_EIP52_SM3Regs* ptrSM3Regs, uint32_t* ptrDigest)
{
    uint32_t index;

    for (index = 0UL; index < 8UL; index++)
    {
        ptrDigest[index] = ptrSM3Regs->SM3_DIGEST_OUT[index];
    }

    return;
}


/**
 * \brief set the length of the data
 * 
 * \param ptrSM3Regs       Pointer to the EIP52 SM3 Registers
 * \param length           total length of data in bytes
 * 
 * 
 */
static void DTHE_SM3_set_length (CSL_EIP52_SM3Regs* ptrSM3Regs, uint64_t length)
{
    uint32_t upper_hash_length, lower_hash_length;

    /* Write the length of the data: */
    lower_hash_length = (uint32_t)(0xFFFFFFFFUL & (8ULL*length));  /*in bits*/
    DTHE_SM3_setHashLength_lower(ptrSM3Regs, lower_hash_length);

    /*set the upper hash length if the data length size is more than 2^32*/
    if (length > (0xffffffffU))
    {
        upper_hash_length = (uint32_t)(0xFFFFFFFFUL & (8ULL*(length>>32ULL)));
        DTHE_SM3_setHashLength_upper(ptrSM3Regs, upper_hash_length);
    }

    return;
}


/**
 * \brief to make the output buffer available again after reading the output digest data
 * After retrieving all desired result data from the output buffer, the Host must write a '1' to
 * this bit to clear it. This makes the output buffer available again for writing by the widebus
 * SM3 hash engine.
 * 
 * \param ptrSM3Regs       Pointer to the EIP52 SM3 Registers
 * \param output_buffer_available  flag to set the bit
 * 
 * 
*/
static void DTHE_SM3_set_output_buff_available(CSL_EIP52_SM3Regs* ptrSM3Regs, uint32_t output_buffer_available)
{
    CSL_FINSR(ptrSM3Regs->SM3_IO_BUF_CTRL_STAT, 0U, 0U, output_buffer_available);

    return;
}


/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

DTHE_SM3_Return_t DTHE_SM3_open(DTHE_Handle handle)
{
    DTHE_SM3_Return_t status  = DTHE_SM3_RETURN_FAILURE;
    DTHE_Config     *config = (DTHE_Config *)NULL;
    DTHE_Attrs      *attrs  = (DTHE_Attrs *)NULL;
    CSL_EIP52_SM3Regs     *ptrSm3Regs;

    if((DTHE_Handle)NULL != handle)
    {
        config              = (DTHE_Config *)(uintptr_t)handle;
        attrs               = config->attrs;
        ptrSm3Regs          = (CSL_EIP52_SM3Regs *)attrs->sm3BaseAddr;
        gDTHESM3InProgress  = DTHE_SM3_CRYPTO_STATEMACHINE_NEW;

        /* Disable all interrupts */
        DTHE_SM3_set_autoctrl(ptrSm3Regs, 0U);

        status = DTHE_SM3_RETURN_SUCCESS;
    }

    return (status);
}

DTHE_SM3_Return_t DTHE_SM3_close(DTHE_Handle handle)
{
    DTHE_SM3_Return_t   status  = DTHE_SM3_RETURN_FAILURE;
    DTHE_Config         *config = (DTHE_Config *)NULL;
    DTHE_Attrs          *attrs  = (DTHE_Attrs *)NULL;
    CSL_EIP52_SM3Regs   *ptrSm3Regs;

    if((DTHE_Handle)NULL != handle)
    {
        config              = (DTHE_Config *)(uintptr_t)handle;
        attrs               = config->attrs;
        ptrSm3Regs          = (CSL_EIP52_SM3Regs *)attrs->sm3BaseAddr;
        if(gDTHESM3InProgress == DTHE_SM3_CRYPTO_STATEMACHINE_NEW)
        {
            /* Disable all interrupts */
            DTHE_SM3_set_autoctrl(ptrSm3Regs, 0U);

            gDTHESM3InProgress = DTHE_SM3_CRYPTO_STATEMACHINE_NEW;
            gDTHESM3digestCount = 0U;

            status = DTHE_SM3_RETURN_SUCCESS;
        }
        else
        {
            status  = DTHE_SM3_RETURN_FAILURE;
        }
    }

    return (status);
}


DTHE_SM3_Return_t DTHE_SM3_compute(DTHE_Handle handle, DTHE_SM3_Params* ptrSm3Params, DTHE_SM3_LastBlockState_t isLastBlock)
{
    DTHE_SM3_Return_t       status       = DTHE_SM3_RETURN_FAILURE;
    uint64_t                index        = 0ULL;
    uint64_t                numBlocks    = 0ULL;
    uint64_t                blockSize    = 0ULL;
    uint64_t                dataLenWords = 0ULL;
    uint64_t                dataLenBytes = 0ULL;
    uint32_t                numPartialWords, numPartialBlocks = 0U;
    uint8_t                 shiftSize;

    DTHE_Config             *config = (DTHE_Config *)NULL;
    DTHE_Attrs              *attrs  = (DTHE_Attrs *)NULL;
    CSL_EIP52_SM3Regs       *ptrSm3Regs;

    if(((DTHE_Handle)NULL != handle) && ((DTHE_SM3_Params *)NULL != ptrSm3Params))
    {
        status = DTHE_SM3_RETURN_SUCCESS;
        
        /* Proceed only if initial checks pass */
        config              = (DTHE_Config *)(uintptr_t)handle;
        attrs               = config->attrs;
        ptrSm3Regs          = (CSL_EIP52_SM3Regs *)attrs->sm3BaseAddr;
        dataLenBytes        = ptrSm3Params->dataLenBytes;

        /* Check if SM3 hardware is available for this platform */
        if(ptrSm3Regs == NULL)
        {
            /* Error: DTHE SM3 is not enabled for this platform. */
            status = DTHE_SM3_RETURN_FAILURE;
        }

        /* Sanity Checking: Any data buffer except the last block should be aligned as per
         * the SM3 block Size. For SM3 this is 64byte aligned */
        if((DTHE_SM3_LAST_BLOCK_FALSE == isLastBlock) && 
           ((dataLenBytes % (DTHE_SM3_BLOCK_SIZE * 4ULL)) != 0ULL))
        {
            /* Error: Ensure that the data length is a word multiple. */
            status = DTHE_SM3_RETURN_FAILURE;
        }
    }
     
    /* Perform the SHA Computation */
    if (DTHE_SM3_RETURN_SUCCESS == status)
    {
        /*wait until input buffer available for writing by host*/
        DTHE_SM3_pollInput_buff_available(ptrSm3Regs);

        if(gDTHESM3InProgress == DTHE_SM3_CRYPTO_STATEMACHINE_INPROGRESS)
        {
            /* set the hash mode as RESUME */
            DTHE_SM3_setHashMode(ptrSm3Regs, 0U);
        }
        else
        {
            /* set the hash mode as NEW */
            DTHE_SM3_setHashMode(ptrSm3Regs, 1U);
        }

        if(gDTHESM3InProgress == DTHE_SM3_CRYPTO_STATEMACHINE_INPROGRESS)
        {
            /* set the length value as expected size */ 
            DTHE_SM3_setHashDigest(ptrSm3Regs, &ptrSm3Params->digest[0U]);
        }

        /* set the length value as expected size */ 
        DTHE_SM3_set_length (ptrSm3Regs, dataLenBytes);

        /* Determine the data length in words: */
        dataLenWords = dataLenBytes/4ULL;
        
        /* Compute the number of blocks: */
        blockSize = DTHE_SM3_BLOCK_SIZE;
        numBlocks = dataLenWords / DTHE_SM3_BLOCK_SIZE;

        if((dataLenBytes % 64ULL) != 0ULL)
        {
            /*Last block is partial*/
            numBlocks++;
        }

        /* Compute the number of partial words which need to be handled separately */
        numPartialWords =  dataLenBytes % (4ULL);
        numPartialBlocks = dataLenWords % DTHE_SM3_BLOCK_SIZE;

        /* write the data input to the input buffer: */
        blockSize = DTHE_SM3_BLOCK_SIZE;
        shiftSize = DTHE_SM3_SHIFT_SIZE;

        /* check the block size */
        if (dataLenWords <= DTHE_SM3_BLOCK_SIZE)
        {
            /*write the data block*/
            DTHE_SM3_writeDataBlock(ptrSm3Regs, &ptrSm3Params->ptrDataBuffer[0U], blockSize);
            if(gDTHESM3InProgress == DTHE_SM3_CRYPTO_STATEMACHINE_INPROGRESS)
            {
                /* set the digest in + input available in */
                DTHE_SM3_set_data_available(ptrSm3Regs, 0x1BEU);
            }
            else
            {
                /* set the input available */
                DTHE_SM3_set_data_available(ptrSm3Regs, 0x13EU);
            }
        }
        else
        {
            /* write first block */
            DTHE_SM3_writeDataBlock(ptrSm3Regs, &ptrSm3Params->ptrDataBuffer[0U], blockSize);
            
            /* write data in ava and ctrl valid */
            DTHE_SM3_set_data_available(ptrSm3Regs, 0x126U);

            /*intermediate blocks*/
            for (index = 1ULL; index < (numBlocks-1ULL); index++)
            {
                /* wait until input buffer available for writing by host */
                DTHE_SM3_pollInput_buff_available(ptrSm3Regs);
                /* write the input data */
                DTHE_SM3_writeDataBlock(ptrSm3Regs, &ptrSm3Params->ptrDataBuffer[index << shiftSize], blockSize);
                /* set only teh data in and in ava bit */
                DTHE_SM3_set_data_available(ptrSm3Regs, 0x006U);
            }

            /*check for the partial data blocks*/

            /*wait until input buffer available for writing by host*/
            DTHE_SM3_pollInput_buff_available(ptrSm3Regs);

            if((numPartialWords != 0U) || (numPartialBlocks != 0U) )
            {
                /* Update blockSize to match the number of partial blocks for the last data block */
                blockSize = numPartialBlocks;

                /*Increment by one to include additional partial word, padding is done by HW based on message bit length*/
                if(numPartialWords != 0U)
                {
                    blockSize++;
                }
            }
            
            /*Write last msg data block to DATA_IN register*/

            /*write the input data*/
            DTHE_SM3_writeDataBlock(ptrSm3Regs, &ptrSm3Params->ptrDataBuffer[index << shiftSize], blockSize);
            /*set only ctrl stat data*/
            DTHE_SM3_set_data_available(ptrSm3Regs, 0x01EU);
        }

        /* Poll till the hash results are available: */
        DTHE_SM3_pollOutputReady (ptrSm3Regs);

        /* Get the digest value: */
        DTHE_SM3_getHashDigest(ptrSm3Regs, &ptrSm3Params->digest[0U]);

        /*indicate finished reading output data*/
        DTHE_SM3_set_output_buff_available(ptrSm3Regs, 1U);

        if( isLastBlock == DTHE_SM3_LAST_BLOCK_TRUE )
        {
            /* Sm3 Computation is in progress: */
            gDTHESM3InProgress = DTHE_SM3_CRYPTO_STATEMACHINE_NEW;
        }
        else
        {
            /* Sm3 Computation is in progress: */
            gDTHESM3InProgress = DTHE_SM3_CRYPTO_STATEMACHINE_INPROGRESS;
        }
    }

   return (status);
}
