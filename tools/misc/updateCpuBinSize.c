/**
*   @file  updateCpuBinSize.c
*
*   @brief
*      This utility updates the size of the image into the C file
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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**************************************************************************
************************ Update Image Size in Syscfg file *****************
**************************************************************************/
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
    long appImgSize = 0;

    if (argc < 4)
    {
        return 1; // Not enough arguments
    }

    // Get the size of the CPU application
    FILE *file = fopen(argv[2], "rb");
    if (file == NULL)
    {
        appImgSize = 0;
    }
    else
    {
        fseek(file, 0, SEEK_END);
        appImgSize = ftell(file);
        fclose(file);
    }

    // Get CPU id
    int cpuId = atoi(argv[3]);

    // Open CPU app section file in write mode
    FILE *cpuAppSecFile = fopen(argv[1], "w");
    if (cpuAppSecFile == NULL)
    {
        return 1; // File could not be opened
    }

    // Add the CPU application section to the file
    fprintf(cpuAppSecFile, "#include <stdint.h>\n\n");

    if (cpuId == 2)
    {
        fprintf(cpuAppSecFile, "__attribute__((retain, section(\"cpu2app\"))) const uint8_t cpu2App[%ld] = {0U};\n", appImgSize);
    }
    else
    {
        fprintf(cpuAppSecFile, "__attribute__((retain, section(\"cpu3app\"))) const uint8_t cpu3App[%ld] = {0U};\n", appImgSize);
    }

    fclose(cpuAppSecFile);
    return 0;
}
