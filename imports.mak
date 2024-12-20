ifeq ($(OS),Windows_NT)
	TOOLS_PATH		?=	C:/ti
	CCS_PATH		?=	$(TOOLS_PATH)/ccs2001/ccs
	CGT29X_PATH		?=	$(CCS_PATH)/tools/compiler/ti-cgt-c29_1.0.0LTS
	COMPILER 		= 	$(CGT29X_PATH)/bin/c29clang.exe
	LINKER 			= 	$(CGT29X_PATH)/bin/c29clang.exe
	CG_TOOL_OBJCOPY	=   $(CGT29X_PATH)/bin/c29objcopy.exe
	AR 				= 	$(CGT29X_PATH)/bin/c29ar.exe
	SYSCFG_ROOT 	?= 	$(CCS_PATH)/utils/sysconfig_1.22.0
	SYSCFG 			?= 	$(SYSCFG_ROOT)/sysconfig_cli.bat
	PYTHON			= py

	CYGWIN_PATH		?=	$(CCS_PATH)/utils/cygwin
	MKDIR			=	$(CYGWIN_PATH)/mkdir -p
	RMDIR			=	$(CYGWIN_PATH)/rm -rf
	RM				=	$(CYGWIN_PATH)/rm -f
	RENAME			=	$(CYGWIN_PATH)/mv
	DELETE			=	$(CYGWIN_PATH)/rm

	SHELL			=	cmd.exe
else
	TOOLS_PATH		?=	$(HOME)/ti
	CCS_PATH		?=	$(TOOLS_PATH)/ccs2001/ccs
	CGT29X_PATH		?=	$(CCS_PATH)/tools/compiler/ti-cgt-c29_1.0.0LTS
	COMPILER 		= 	$(CGT29X_PATH)/bin/c29clang
	LINKER 			= 	$(CGT29X_PATH)/bin/c29clang
	CG_TOOL_OBJCOPY	=   $(CGT29X_PATH)/bin/c29objcopy
	AR 				= 	$(CGT29X_PATH)/bin/c29ar
	SYSCFG_ROOT 	?= 	$(CCS_PATH)/utils/sysconfig_1.22.0
	SYSCFG 			?= 	$(SYSCFG_ROOT)/sysconfig_cli.sh

	CHECK_PYTHON3 = $(shell command -v python3 2>/dev/null)
ifeq ($(CHECK_PYTHON3), )
	PYTHON := python
else
	PYTHON := python3
endif

	MKDIR			=	mkdir -p
	RMDIR			=	rm -rf
	RM				=	rm -f
	RENAME			=	mv
	DELETE			=	rm
endif

CONFIG ?= RAM
DEVICE_TYPE ?= GP
DEBUG_OPTION ?= DBG_SOC_DEFAULT
ENC_SBL_ENABLED ?= no
DEBUG_TIFS ?= no

INCLUDES_common := \
-I "$(C29SDK_ROOT)/examples/device_support/include" \
-I "$(C29SDK_ROOT)/source" \
-I "$(C29SDK_ROOT)/source/security" \
-I "$(C29SDK_ROOT)/source/driverlib" \
-I "$(C29SDK_ROOT)/source/bitfields" \
-I "$(C29SDK_ROOT)/source/rtlibs/dcl" \
-I "$(C29SDK_ROOT)/source/rtlibs/dsp/fpu/fpu32/fft" \
-I "$(C29SDK_ROOT)/source/rtlibs/iqmath" \
-I "$(C29SDK_ROOT)/source/kernel/freertos/Source/include" \
-I "$(C29SDK_ROOT)/source/kernel/freertos/Source/portable/CCS/C2000_C29x" \
-I "$(C29SDK_ROOT)/source/flash_api/include/FlashAPI" \
-I "$(CGT29X_PATH)/include/c" \


INCLUDES_syscfg := \
-I "../ccs/syscfg"

CMD_SRCS_RAM := \
$(C29SDK_ROOT)/examples/device_support/cmd/f29h85x_ram_lnk.cmd

CMD_SRCS_FLASH := \
$(C29SDK_ROOT)/examples/device_support/cmd/f29h85x_flash_lnk.cmd

CFLAGS_common := \
	-g -c -w

ifeq ($(CONFIG),FLASH)
	CFLAGS_common += -D_FLASH
endif

CFLAGS_debug := \
	-O1 -DDEBUG

CFLAGS_debug_O0 := \
	-O0 -DDEBUG \

LFLAGS_common := -Wl,--entry_point="code_start",--stack_size=0x2000,--heap_size=0x400,-i"$(CGT29X_PATH)\lib",--reread_libs,--diag_suppress=10325-D,--diag_suppress=10063-D

ARFLAGS := r

LIB = -Wl,-l$(C29SDK_ROOT)/source/driverlib/ccs/driverlib.lib -l$(C29SDK_ROOT)/source/calibration/hrpwm/lib/sfo.lib

ASM_SRCS += \
$(C29SDK_ROOT)/examples/device_support/source/codestartbranch.asm

C_SRCS_common += \
../$(Target).c \
$(C29SDK_ROOT)/source/bitfields/bitfield_structs.c \
$(ASM_SRCS) \

C_SRCS_syscfg += \
.\syscfg\board.c \
.\syscfg\device.c \

C_SRCS_syscfg_CLB += \
.\syscfg\clb_config.c \

C_SRCS_nosyscfg += \
$(C29SDK_ROOT)/examples/device_support/source/device.c \