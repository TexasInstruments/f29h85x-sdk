/**
*   @file  updateSysCfg.c
*
*   @brief
*      This utility updates the size of the image into the CPU1 syscfg file
*
*  \par
*  NOTE:
*      (C) Copyright 2025 Texas Instruments, Inc.
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
/**************************************************************************
*************************** Include Files ********************************
**************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**************************************************************************
************************ Update Image Size in Syscfg file *****************
**************************************************************************/
//
//  Defines
//
//
//  Maximum no of lines in the syscfg file
//
#define MAX_NUM_LINES       (4096U)
//
//  Maximum size of each line
//
#define MAX_LINE_SIZE       (256U)

/**
*  @b Description
*  @n
*      Entry point into the Update App size in syscfg file utility
*
*  @param[in] argc
*      Number of arguments
*  @param[in] argv
*      Command Line arguments
*
*  @retval
*      Success -   0
*  @retval
*      Error   -   <0
*/
int32_t main(int32_t argc, char* argv[])
{
    FILE    *sysCfgFile = NULL;
    FILE    *appImage   = NULL;
    uint32_t lineCount  = 0U;
    uint32_t i          = 0U;
    uint32_t cpuId;
    uint32_t appImgSize;
    uint8_t  lines[MAX_NUM_LINES][MAX_LINE_SIZE];
    //
    //  Check number of arguments
    //
    if(4U != argc)
    {
        printf("Error: Insufficient arguments\n");
        return -1;
    }
    //
    //  Open syscfg file in read mode and read all the lines
    //
    sysCfgFile = fopen(argv[1], "r");
    if(NULL == sysCfgFile)
    {
        printf("Error: Syscfg file open in read mode\n");
        return -1;
    }
    while(fgets(lines[lineCount], MAX_LINE_SIZE, sysCfgFile))
    {
        lineCount++;
        if(lineCount >= MAX_NUM_LINES)
        {
            printf("Error: Syscfg file has more than %d lines\n", MAX_NUM_LINES);
            return -1;
        }
    }
    fclose(sysCfgFile);
    //
    //  Open syscfg file in write mode and skip CPU2/3 size
    //
    sysCfgFile = fopen(argv[1], "w");
    if(NULL == sysCfgFile)
    {
        printf("Error: Syscfg file open in write mode\n");
        return -1;
    }
    //
    //  Get CPU ID
    //
    cpuId = atoi(argv[3]);
    for(i = 0U; i < lineCount; i++)
    {
        if(cpuId == 2U)
        {
            if((strstr(lines[i], "const cpu2") == NULL) && (strstr(lines[i], "cpu2.appsize") == NULL))
            {
                fprintf(sysCfgFile, "%s", lines[i]);
            }
        }
        else if(cpuId == 3U)
        {
            if ((strstr(lines[i], "const cpu3") == NULL) && (strstr(lines[i], "cpu3.appsize") == NULL))
            {
                fprintf(sysCfgFile, "%s", lines[i]);
            }
        }
    }
    fclose(sysCfgFile);
    //
    //  Get the size of the App binary
    //
    appImage = fopen(argv[2], "rb");
    if(NULL == appImage)
    {
        printf("Error: App binary file open in read binary mode\n");
        return -1;
    }
    fseek(appImage, 0U, SEEK_END);
    appImgSize = ftell(appImage);
    fclose(appImage);
    //
    //  Append syscfg file with the app binary size
    //
    sysCfgFile = fopen(argv[1], "a");
    if(NULL == sysCfgFile)
    {
        printf("Error: Syscfg file open in append mode\n");
        return -1;
    }
    if(cpuId == 2U)
    {
        fprintf(sysCfgFile, "const cpu2  = scripting.addModule(\"/driverlib/cpu2.js\");\n");
        fprintf(sysCfgFile, "cpu2.appsize = %d;\n", appImgSize);
    }
    else
    {
        fprintf(sysCfgFile, "const cpu3  = scripting.addModule(\"/driverlib/cpu3.js\");\n");
        fprintf(sysCfgFile, "cpu3.appsize = %d;\n", appImgSize);
    }
    fclose(sysCfgFile);

    return 0;
}
