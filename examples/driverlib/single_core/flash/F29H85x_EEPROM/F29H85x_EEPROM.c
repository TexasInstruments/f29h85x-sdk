//#############################################################################
//
//
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

//#############################################################################

#include <F29H85x_EEPROM_Config.h>

// ==== Global Config + State Variables ==== //

//
// Page Mode-Only State
//
uint8_t Bank_Status[WRITE_SIZE_BYTES] = {0};
uint8_t Page_Status[WRITE_SIZE_BYTES] = {0};
uint8_t *Bank_Pointer;
uint8_t *Page_Pointer;
uint8_t Bank_Counter = 0;
uint8_t Page_Counter = 0;
uint32_t Bank_Size;
uint32_t status_buffer_len = WRITE_SIZE_BYTES;

//
// Both
//
uint8_t Erase_Blank_Check = 1;
uint8_t Empty_EEPROM = 1;
uint32_t WE_Protection_A_Mask;
uint32_t WE_Protection_B_Mask;
uint32_t NUM_EEPROM_SECTORS;
uint32_t FIRST_AND_LAST_SECTOR[2] = {0,0};

//
// The length passed to the blank check function, proper computation
// requires a division, so the below is a placeholder value.
// It is properly set in main()
//
uint32_t BLANK_CHECK_LEN = FLASH_SECTOR_SIZE;

//
// Precompute and cache the length passed to the blank check function
// The number of bytes must be divided by 4 because the length is
// treated as a 32-bit length
//
uint32_t VERIFY_LEN = WRITE_SIZE_BYTES / 4;

void Fill_Buffer(uint8_t* buffer, int buffer_len, uint8_t value)
{
    //
    // Fill the buffer array with the specified value
    //
    uint8_t i;
    for (i = 0; i < buffer_len; i++)
    {
        buffer[i] = value;
    }
}

int EEPROM_Config_Check(void) {
    //
    // If not using the data bank, return an error.
    // EEPROM emulation is only valid in the data bank.
    //
    if (FLASH_BANK_SELECT != C29FlashBankFR4RP0StartAddress)
    {
        return 0xFFFF;
    }

    //
    // Compute and cache the total number of flash sectors being used for emulation
    //
    uint32_t NUM_EEPROM_SECTORS_1 = FIRST_AND_LAST_SECTOR[1] - FIRST_AND_LAST_SECTOR[0] + 1;
    NUM_EEPROM_SECTORS = NUM_EEPROM_SECTORS_1;

    //
    // Make sure we have chosen at least 1 sector
    // and that the number of sectors is not more than those available on the device
    //
    if (NUM_EEPROM_SECTORS > NUM_FLASH_SECTORS || NUM_EEPROM_SECTORS == 0)
    {
        return 0xEEEE;
    }

    //
    // If using more than one sector
    //
    if (NUM_EEPROM_SECTORS > 1)
    {
        //
        // Make sure the chosen sectors are in the correct order and not duplicates
        //
        if (FIRST_AND_LAST_SECTOR[1] <= FIRST_AND_LAST_SECTOR[0])
        {
            return 0xEEEE;
        }

        //
        // Check to make sure sectors are in range for the device
        //
        if (FIRST_AND_LAST_SECTOR[1] > NUM_FLASH_SECTORS - 1 || FIRST_AND_LAST_SECTOR[1] < 1)
        {
            return 0xEEEE;
        }
    }

    //
    // If using a single sector, make sure it is in range
    //
    else if (FIRST_AND_LAST_SECTOR[0] > NUM_FLASH_SECTORS - 1 || FIRST_AND_LAST_SECTOR[1] > NUM_FLASH_SECTORS - 1)
    {
        return 0xEEEE;
    }

#ifdef PAGE_MODE
    //
    // Compute the total size of an EEPROM bank in bytes
    //
    Bank_Size = WRITE_SIZE_BYTES*2 + ((EEPROM_PAGE_DATA_SIZE + WRITE_SIZE_BYTES*2) * NUM_EEPROM_PAGES);

    //
    // Compute the total number of bytes available in the chosen memory range
    //
    uint32_t Available_Words = NUM_EEPROM_SECTORS * FLASH_SECTOR_SIZE;

    //
    // Ensure the EEPROM emulation will fit into the chosen memory range
    //
    if (Bank_Size * NUM_EEPROM_BANKS > Available_Words)
    {
        return 0xCCCC;
    }

#endif

    //
    // WARNINGS (Not Fatal)
    //
    uint8_t Warning_Flags = 0;

#ifdef PAGE_MODE
    //
    // Notify if there is extra space/room for another EEPROM bank.
    // If so, user should adjust NUM_EEPROM_BANKS and NUM_EEPROM_PAGES
    //
    if (Available_Words - (Bank_Size * NUM_EEPROM_BANKS ) >= Bank_Size)
    {
        Warning_Flags += 1;
    }

    //
    // If page data size is less than 64 bits, issue a warning.
    // 64-bit mode could be used to achieve the same effect
    // with better spatial efficiency
    //
    if (DATA_SIZE <= WRITE_SIZE_BYTES)
    {
        Warning_Flags += 2;
    }

#endif

    //
    // If both sectors > 31 (using mask B)
    //
    if (FIRST_AND_LAST_SECTOR[0] > 31 && FIRST_AND_LAST_SECTOR[1] > 31)
    {
        //
        // If not using the full 8 sectors, issue warning
        // These unused sectors will still be erased when the unit is full
        //
        if (NUM_EEPROM_SECTORS < 8)
        {
            Warning_Flags += 4;
        }

        //
        // If the sectors aren't a multiple of 8, issue a warning.
        // As each bit in mask B protects 8 sectors, there will be unused sectors
        // that are erased when the unit is full
        //
        else if ((FIRST_AND_LAST_SECTOR[0] % 8) != 0 || (FIRST_AND_LAST_SECTOR[1] + 1) % 8 != 0)
        {
            Warning_Flags += 4;
        }

    }

    //
    // If only the end sector > 31 (using mask B), issue a warning if not a multiple of 8
    // for the same reasons as stated above
    //
    else if (FIRST_AND_LAST_SECTOR[1] > 31 && (FIRST_AND_LAST_SECTOR[1] + 1) % 8 != 0)
    {
        Warning_Flags += 4;
    }

    return Warning_Flags;
}

void EEPROM_Erase()
{
    Set_Protection_Masks();
    Erase_Bank();
    RESET_BANK_POINTER;
    RESET_PAGE_POINTER;
}

uint64_t Configure_Protection_Masks(uint32_t* Sector_Numbers, uint32_t Num_EEPROM_Sectors)
{
    uint64_t Protection_Mask_Sectors = 0;

    //
    // If we are using more than one sector
    //
    if (Num_EEPROM_Sectors > 1)
    {
        uint64_t Unshifted_Sectors;
        uint8_t Shift_Amount;

        //
        // If all sectors use Mask A
        //
        if (Sector_Numbers[0] < 32 && Sector_Numbers[1] < 32)
        {
            //
            // Shift 1 out to 1 bit past the number of sectors
            //
            Unshifted_Sectors = (uint64_t) 1 << Num_EEPROM_Sectors;

            //
            // Subtract 1 --> now we have all 1s for the number of sectors we want
            //
            Unshifted_Sectors -= 1;

            //
            // Shift over by start location and OR with master
            //
            Protection_Mask_Sectors |= (Unshifted_Sectors << Sector_Numbers[0]);
        }
        //
        // If all sectors use Mask B
        //
        else if (Sector_Numbers[0] > 31 && Sector_Numbers[1] > 31)
        {
            //
            // Subtract 32 because these use a different mask, rebase to 0
            // We divide by 8 because each bit here protects 8 sectors
            //
            Shift_Amount = ((Sector_Numbers[1] - 32) / 8) - ((Sector_Numbers[0] - 32) / 8) + 1;
           
            //
            // Then perform the same operations as for mask A
            //
            Unshifted_Sectors = (uint64_t) 1 << Shift_Amount;
            Unshifted_Sectors -= 1;
            Protection_Mask_Sectors |= (Unshifted_Sectors << ((Sector_Numbers[0] - 32)/8));
            Protection_Mask_Sectors = Protection_Mask_Sectors << 32;
        }
        //
        // If a mix of masks A and B
        //
        else
        {
            //
            // Configure mask B first, in the same manner as above
            //
            Shift_Amount = ((Sector_Numbers[1] - 32)/8) + 1;
            Unshifted_Sectors = (uint64_t) 1 << Shift_Amount;
            Unshifted_Sectors -= 1;
            Protection_Mask_Sectors |= Unshifted_Sectors;

            //
            // Zero out the bottom half so we can configure Mask A
            //
            Protection_Mask_Sectors = Protection_Mask_Sectors << 32;

            //
            // Configure Mask A and OR into main mask
            //
            Unshifted_Sectors = (uint64_t) 1 << ((32 - Sector_Numbers[0]) + 1);
            Unshifted_Sectors -= 1;
            Protection_Mask_Sectors |= (Unshifted_Sectors << Sector_Numbers[0]);
        }
    }
    //
    // If using only 1 sector
    //
    else
    {
        //
        // Mask A
        //
        if(Sector_Numbers[0] < 32)
        {
            //
            // Shift the bit over to the corresponding sector, then OR it in
            //
            Protection_Mask_Sectors |= ((uint64_t) 1 << Sector_Numbers[0]);
        }
        //
        // Mask B
        //
        else
        {
            //
            // Shift the bit over to the corresponding sector, then OR it in
            // Subtraction and division are to account for the rebase and number of sectors protected by each bit
            // See above comments for more detail
            //
            Protection_Mask_Sectors |= ((uint64_t) 1 << ((Sector_Numbers[0] - 32)/8));
            Protection_Mask_Sectors = Protection_Mask_Sectors << 32;
        }
    }

    return Protection_Mask_Sectors;
}

void ClearFSMStatus(void)
{
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_StatusType  oReturnCheck;

    //
    // Wait for FSM to finish previous operation
    //
    while (Fapi_checkFsmForReady(FLASH_BANK_SELECT, u32UserFlashConfig) != Fapi_Status_FsmReady);

    oFlashStatus = Fapi_getFsmStatus(FLASH_BANK_SELECT, u32UserFlashConfig);

    //
    // Clear the status register
    //
    oReturnCheck = Fapi_issueAsyncCommand(FLASH_BANK_SELECT, u32UserFlashConfig, Fapi_ClearStatus);
    
    //
    // Wait for the status to clear
    //
    while (Fapi_getFsmStatus(FLASH_BANK_SELECT, u32UserFlashConfig) != 0);

    if (oReturnCheck != Fapi_Status_Success)
    {
        Sample_Error();
    }
}

void EEPROM_GetValidBank(uint8_t ReadFlag)
{
    // 
    // Start search from the beginning of the active bank's flash sectors
    //
    RESET_BANK_POINTER;
    RESET_PAGE_POINTER;

    uint8_t i;
    for (i = 0; i < NUM_EEPROM_BANKS; i++)
    {
        //
        // Check the first status byte to see if bank is in use or full
        //
        uint8_t Bank_in_Use = *(Bank_Pointer);
        uint8_t Bank_Full = *(Bank_Pointer + WRITE_SIZE_BYTES);

        // 
        // If we have found an unused (empty) bank,
        // then update the bank counter
        //
        if (Bank_in_Use == EMPTY_BANK)
        {
            Bank_Counter = i;
            return;
        }

        //
        // If we have found a used bank with blank pages
        //
        if (Bank_in_Use == CURRENT_BANK && Bank_Full != CURRENT_BANK)
        {
            //
            // Update the bank counter
            // 
            Bank_Counter = i;

            //
            // Set the page pointer to the start of the bank.
            // It will be adjusted to the open page in the loop after this
            //
            Page_Pointer = Bank_Pointer + WRITE_SIZE_BYTES*2;
            break;
        }

        //
        // If the current bank is full
        //
        if (Bank_in_Use == CURRENT_BANK && Bank_Full == CURRENT_BANK)
        {
            //
            // Move to the next bank and continue the loop
            //
            Bank_Pointer += Bank_Size;
        }
    }

    //
    // Find the current page
    //
    for (i = 0; i < NUM_EEPROM_PAGES; i++)
    {
        //
        // Check the status fields to see if page is in use or full
        //
        uint8_t Page_in_Use = *(Page_Pointer);
        uint8_t Page_Full = *(Page_Pointer + WRITE_SIZE_BYTES);

        //
        // If we've found a blank page, we can break out
        //
        if (Page_in_Use == BLANK_PAGE)
        {
            Page_Counter = i;
            break;
        }

        //
        // If we have found the current page in use, set the page counter
        // to the current number of pages in use for this EEPROM bank
        // and break the loop
        //
        if (Page_in_Use == CURRENT_PAGE && Page_Full != CURRENT_PAGE)
        {
            Page_Counter = i + 1;
            break;
        }

        //
        // Go to the next page
        //
        Page_Pointer += WRITE_SIZE_BYTES*2 + EEPROM_PAGE_DATA_SIZE;
    }

    //
    // If we've filled all banks and pages, erase the EEPROM unit
    //
    if ((!ReadFlag) && (Bank_Counter == NUM_EEPROM_BANKS - 1) && (Page_Counter == NUM_EEPROM_PAGES))
    {
        //
        // Mark page as used for completeness
        //
        EEPROM_UpdatePageStatus();

        //
        // Mark bank as used for completeness
        //
        EEPROM_UpdateBankStatus();

        //
        // Erase the bank
        //
        EEPROM_Erase();
    }
}

void Erase_Bank()
{
    Fapi_StatusType  oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;

    //
    // Clear the status of the previous flash operation
    //
    ClearFSMStatus();

    //
    // Enable program/erase protection for select sectors
    //
    Fapi_setupBankSectorEnable((uint32_t*) FLASH_BANK_SELECT, u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTA, WE_Protection_A_Mask);
    Fapi_setupBankSectorEnable((uint32_t*) FLASH_BANK_SELECT, u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTB, WE_Protection_B_Mask);

    //
    // Erase the flash bank
    //
    oReturnCheck = Fapi_issueBankEraseCommand((uint32_t*) FLASH_BANK_SELECT, 0, u32UserFlashConfig);

    //
    // Wait for completion and check for any programming errors
    //
    while(Fapi_checkFsmForReady((uint32_t) FLASH_BANK_SELECT, u32UserFlashConfig) == Fapi_Status_FsmBusy);

    if (oReturnCheck != Fapi_Status_Success)
        Sample_Error();

    oFlashStatus = Fapi_getFsmStatus((uint32_t) FLASH_BANK_SELECT, u32UserFlashConfig);
    if (oFlashStatus != 3)
    {
        FMSTAT_Fail();
    }

    //
    // If configured to, perform a blank check to ensure proper erasure
    //
    if (Erase_Blank_Check)
    {
        uint32_t address = FLASH_BANK_SELECT + FIRST_AND_LAST_SECTOR[0] * FLASH_SECTOR_SIZE;
        Fapi_FlashStatusWordType oFlashStatusWord;
        oReturnCheck = Fapi_doBlankCheck((uint32_t*) address, BLANK_CHECK_LEN, &oFlashStatusWord, 0, u32UserFlashConfig);

        if (oReturnCheck != Fapi_Status_Success)
        {
            Sample_Error();
        }
    }
}

void EEPROM_Read(uint8_t* Read_Buffer)
{
    //
    // If we haven't written any data yet, don't allow a read
    //
    if (Empty_EEPROM)
    {
        Sample_Error();
    }

#ifdef PAGE_MODE
    //
    // Get the current page data
    //
    EEPROM_GetValidBank(1);

    //
    // Skip over the page status bytes
    //
    Page_Pointer += WRITE_SIZE_BYTES*2;

    uint32_t i;
    for (i = 0; i < DATA_SIZE; i++)
    {
        //
        // Read page data from flash
        //
        Read_Buffer[i] = *(Page_Pointer++);
    }
#else

    //
    // Move pointer back 64 bits to read most recent data
    //
    Bank_Pointer -= WRITE_SIZE_BYTES;
    uint32_t i;
    for (i = 0; i < WRITE_SIZE_BYTES; i++)
    {
        //
        // Read page data from flash
        //
        Read_Buffer[i] = *(Bank_Pointer++);
    }

#endif
}

void EEPROM_Write_Page(uint8_t* Write_Buffer)
{
    //
    // Set pointers to the most recently used page, erasing the unit if necessary.
    // If no data has been written yet, this will return a blank page.
    //
    EEPROM_GetValidBank(0);

    //
    // If our new page is in the middle of a bank,
    // mark the previous page as dirty and increment the pointer to a blank one
    //
    EEPROM_UpdatePageStatus();

    //
    // If we switched to a new EEPROM bank, mark it as current.
    // If our EEPROM bank is full, mark it as used and adjust the
    // bank and page pointers
    //
    EEPROM_UpdateBankStatus();

    //
    // Write our data to the page and mark it as current
    //
    EEPROM_UpdatePageData(Write_Buffer);
}

void EEPROM_Write_Buffer(uint8_t* address, uint8_t* write_buffer)
{
    Fapi_StatusType oReturnCheck;
    Fapi_FlashStatusType  oFlashStatus;
    Fapi_FlashStatusWordType oFlashStatusWord;

    //
    // Clear the status of the previous Flash operation
    //
    ClearFSMStatus();

    //
    // Enable program/erase protection for select sectors
    //
    Fapi_setupBankSectorEnable((uint32_t*) FLASH_BANK_SELECT, u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTA, WE_Protection_A_Mask);
    Fapi_setupBankSectorEnable((uint32_t*) FLASH_BANK_SELECT, u32UserFlashConfig, FLASH_NOWRAPPER_O_CMDWEPROTB, WE_Protection_B_Mask);

    //
    // Program data to flash
    //
    oReturnCheck = Fapi_issueProgrammingCommand((uint32_t*) address, (uint8_t*) write_buffer, WRITE_SIZE_BYTES, 0, 0, Fapi_AutoEccGeneration, u32UserFlashConfig);

    //
    //  Wait for completion and check for any programming errors
    //
    while (Fapi_checkFsmForReady((uint32_t) address, u32UserFlashConfig) == Fapi_Status_FsmBusy);

    if (oReturnCheck != Fapi_Status_Success)
    {
        Sample_Error();
    }

    oFlashStatus = Fapi_getFsmStatus((uint32_t) address, u32UserFlashConfig);
    if (oFlashStatus != 3)
    {
        FMSTAT_Fail();
    }

    //
    // Verify the correct data was written
    //
    oReturnCheck = Fapi_doVerify((uint32_t*) address, VERIFY_LEN, (uint32_t*) write_buffer, &oFlashStatusWord, 0, u32UserFlashConfig);
    if (oReturnCheck != Fapi_Status_Success)
    {
        Sample_Error();
    }
}

void EEPROM_UpdateBankStatus()
{
    Fapi_StatusType oReturnCheck;

    uint8_t Current_Bank_Status = *(Bank_Pointer);

    //
    // If the current bank is empty
    //
    if (Current_Bank_Status == EMPTY_BANK)
    {
        //
        // Fill the bank status buffer
        //
        Fill_Buffer(Bank_Status, status_buffer_len, CURRENT_BANK);

        //
        // Write the buffer to the start of the bank status in flash, 
        // marking the bank as current
        //
        EEPROM_Write_Buffer(Bank_Pointer, Bank_Status);

        //
        // Reset the page counter and page pointer
        //
        Page_Counter = 0;
        Page_Pointer = Bank_Pointer + WRITE_SIZE_BYTES*2;
    }

    //
    // If the current bank is full
    //
    else if (Current_Bank_Status == CURRENT_BANK && Page_Counter == NUM_EEPROM_PAGES)
    {
        //
        // Fill the bank status buffer
        //
        Fill_Buffer(Bank_Status, status_buffer_len, CURRENT_BANK);

        //
        // Write the buffer to the end of the bank status in flash, 
        // marking the bank as used/full
        //
        EEPROM_Write_Buffer(Bank_Pointer + WRITE_SIZE_BYTES, Bank_Status);

        //
        // Increment the bank pointer to the next EEPROM bank
        //
        Bank_Pointer += Bank_Size;

        //
        // If all banks and pages have been used, the new bank pointer is invalid.
        // The function returns early and the flash will be erased in EEPROM_GetValidBank()
        // This if statement only applies when this function is called from EEPROM_GetValidBank()
        //
        if (Bank_Counter == NUM_EEPROM_BANKS - 1 && Page_Counter == NUM_EEPROM_PAGES)
        {
            return;
        }

        //
        // If the pointer is valid, mark the new bank as current and set the page pointer
        //
        Fill_Buffer(Bank_Status, status_buffer_len, CURRENT_BANK);
        EEPROM_Write_Buffer(Bank_Pointer, Bank_Status);
        Page_Counter = 0;
        Page_Pointer = Bank_Pointer + WRITE_SIZE_BYTES*2;

    }
}

void EEPROM_UpdatePageStatus()
{
    Fapi_StatusType oReturnCheck;

    uint8_t Current_Page_Status = *(Page_Pointer);

    //
    // If our current page is blank, we don't need to mark it as used
    //
    if (Current_Page_Status == BLANK_PAGE)
    {
        return;
    }

    //
    // Otherwise, fill the bank status buffer
    //
    Fill_Buffer(Page_Status, status_buffer_len, CURRENT_PAGE);

    //
    // And write it to the end of the page status in flash, 
    // marking the page as used
    //
    EEPROM_Write_Buffer(Page_Pointer + WRITE_SIZE_BYTES, Page_Status);

    //
    // Increment the page pointer to the next page
    //
    Page_Pointer += EEPROM_PAGE_DATA_SIZE + WRITE_SIZE_BYTES*2;
}

void EEPROM_UpdatePageData(uint8_t* Write_Buffer)
{
    uint32_t i, Page_Offset;

    //
    // Program the Write_Buffer to flash in 64-bit increments
    //
    for(i = 0; i < EEPROM_PAGE_DATA_SIZE / WRITE_SIZE_BYTES; i++)
    {
        Page_Offset = WRITE_SIZE_BYTES*2 + (WRITE_SIZE_BYTES*i);
        EEPROM_Write_Buffer(Page_Pointer + Page_Offset, Write_Buffer + (i*WRITE_SIZE_BYTES));
    }

    //
    // Mark the page with our new data as current
    //
    Fill_Buffer(Page_Status, status_buffer_len, CURRENT_PAGE);
    EEPROM_Write_Buffer(Page_Pointer, Page_Status);

    Empty_EEPROM = 0;
}

void EEPROM_64_Bit_Mode_Check_EOS()
{
    uint8_t* End_Address = (uint8_t*) END_OF_SECTOR;

    //
    // If the EEPROM unit is full, then erase it
    //
    if (Bank_Pointer > End_Address - WRITE_SIZE_BYTES)
    {
        EEPROM_Erase();
    }
}

void EEPROM_Write_64_Bits(uint8_t Num_Bytes, uint8_t* Write_Buffer)
{
    //
    // Check and make sure we're still within our allocated memory range.
    // If not, erase and reset the pointers
    //
    EEPROM_64_Bit_Mode_Check_EOS();

    //
    // Pad the unused bits in the data buffer with 1s
    //
    uint8_t i;
    for (i = Num_Bytes; i < WRITE_SIZE_BYTES; i++)
    {
        Write_Buffer[i] = 0xFF;
    }

    //
    // Program the 64-bit data to flash
    //
    EEPROM_Write_Buffer(Bank_Pointer, Write_Buffer);

    //
    // Mark the EEPROM as containing data (we can safely read now)
    //
    Empty_EEPROM = 0;

    //
    // Update the pointer to the next empty set of 64 bits
    //
    Bank_Pointer += WRITE_SIZE_BYTES;
}

void Set_Protection_Masks()
{
    //
    // Compute the combined protectionmasks, then xor them to disable  
    // protection for writable/erasable sectors
    //
    uint64_t WE_Protection_AB_Mask = Configure_Protection_Masks(FIRST_AND_LAST_SECTOR, NUM_EEPROM_SECTORS);
    WE_Protection_A_Mask = 0xFFFFFFFF ^ (uint32_t)WE_Protection_AB_Mask;
    WE_Protection_B_Mask = 0x00000FFF ^ WE_Protection_AB_Mask >> 32;
}

void Sample_Error()
{
    //
    //  Error code will be in the status parameter
    //
    asm(" EMUSTOP0");
}

void Example_Done() {

    asm(" EMUSTOP0");

}

void FMSTAT_Fail(void)
{
    asm(" EMUSTOP0");
    for (;;);
}
