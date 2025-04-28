ifeq ($(OS),Windows_NT)
	TOOLS_PATH		    ?=	C:/ti
	CCS_PATH		    ?=	$(TOOLS_PATH)/ccs2011/ccs
	CGT29X_PATH		    ?=	$(CCS_PATH)/tools/compiler/ti-cgt-c29_1.0.0LTS
	COMPILER 		     = 	$(CGT29X_PATH)/bin/c29clang.exe
	LINKER 			     = 	$(CGT29X_PATH)/bin/c29clang.exe
	CG_TOOL_OBJCOPY	     =  $(CGT29X_PATH)/bin/c29objcopy.exe
	AR 				     = 	$(CGT29X_PATH)/bin/c29ar.exe
	SYSCFG_ROOT 	    ?= 	$(CCS_PATH)/utils/sysconfig_1.23.0
	SYSCFG_CLI_PATH     ?=  $(SYSCFG_ROOT)
	SYSCFG_NODE          =  $(CCS_PATH)/tools/node/node
	SYSCFG_SDKPRODUCT    =  $(C29SDK_ROOT)/.metadata/sdk.json
	SYSCFG 			    ?= 	$(SYSCFG_ROOT)/sysconfig_cli.bat
	PYTHON			     =   py

	CYGWIN_PATH		?=	$(CCS_PATH)/utils/cygwin
	MKDIR			=	$(CYGWIN_PATH)/mkdir -p
	RMDIR			=	$(CYGWIN_PATH)/rm -rf
	RM				=	$(CYGWIN_PATH)/rm -f
	RENAME			=	$(CYGWIN_PATH)/mv
	DELETE			=	$(CYGWIN_PATH)/rm

	SHELL			=	cmd.exe
else
	TOOLS_PATH		?=	$(HOME)/ti
	CCS_PATH		?=	$(TOOLS_PATH)/ccs2011/ccs
	CGT29X_PATH		?=	$(CCS_PATH)/tools/compiler/ti-cgt-c29_1.0.0LTS
	COMPILER 		= 	$(CGT29X_PATH)/bin/c29clang
	LINKER 			= 	$(CGT29X_PATH)/bin/c29clang
	CG_TOOL_OBJCOPY	=   $(CGT29X_PATH)/bin/c29objcopy
	AR 				= 	$(CGT29X_PATH)/bin/c29ar
	SYSCFG_ROOT 	?= 	$(CCS_PATH)/utils/sysconfig_1.23.0
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
BOARD ?= SOM
DEVICE_TYPE ?= GP
DEBUG_OPTION ?= DBG_SOC_DEFAULT
ENC_SBL_ENABLED ?= no
DEBUG_TIFS ?= no
ALGORITHM?=RSA4k

ifeq ($(ALGORITHM),RSA4k)
        SIGNING_KEY=$(C29SDK_ROOT)/tools/boot/signing/mcu_custMpk.pem
endif
ifeq ($(ALGORITHM),ECDSA256R1)
        SIGNING_KEY=$(C29SDK_ROOT)/tools/boot/signing/mcu_custMpk_secp256r1.pem
endif
ifeq ($(ALGORITHM),ECDSA384R1)
        SIGNING_KEY=$(C29SDK_ROOT)/tools/boot/signing/mcu_custMpk_secp384r1.pem
endif
ifeq ($(ALGORITHM),ECDSA521R1)
        SIGNING_KEY=$(C29SDK_ROOT)/tools/boot/signing/mcu_custMpk_secp521r1.pem
endif
ifeq ($(ALGORITHM),BRAINPOOL512)
        SIGNING_KEY=$(C29SDK_ROOT)/tools/boot/signing/mcu_custMpk_brainpool512.pem
endif

INCLUDES_common := \
-I ".." \
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

CFLAGS_debug := \
	-O1 -DDEBUG

CFLAGS_debug_O0 := \
	-O0 -DDEBUG \

CFLAGS_security := \
	-DSOC_F29H85X

LFLAGS_common := -Wl,--entry_point="code_start",--stack_size=0x2000,--heap_size=0x400,-i"$(CGT29X_PATH)\lib",--reread_libs,--diag_suppress=10325-D,--diag_suppress=10063-D

ifeq ($(CONFIG),FLASH)
	CFLAGS_common += -D_FLASH
	LFLAGS_common += -Wl,--define=_FLASH
endif

ifeq ($(BOARD),LAUNCHXL)
	CFLAGS_common += -D_LAUNCHXL_F29H85X
endif

ARFLAGS := r

comma=,

LIBS_PATH = \
	$(C29SDK_ROOT)/source/driverlib/ccs \
	$(C29SDK_ROOT)/source/calibration/hrpwm/lib \
	$(C29SDK_ROOT)/source/security/ccs \
	$(C29SDK_ROOT)/source/kernel/nortos/ccs \
	$(C29SDK_ROOT)/source/flash_api/lib \

LIBS = \
	driverlib.lib \
	sfo.lib \
	security_drivers.lib \
	dpl_nortos.lib \
	F29H85x_NWFlashAPI_v21.00.00.00.lib \

ASM_SRCS += \
	$(C29SDK_ROOT)/examples/device_support/source/codestartbranch.asm

ASM_SRCS_FREERTOS += \
	$(C29SDK_ROOT)/source/kernel/freertos/Source/portable/CCS/C2000_C29x/portasm.asm

C_SRCS_common += \
	$(Target).c \
	bitfield_structs.c \

C_SRCS_PATH_common = \
	.. \
	$(C29SDK_ROOT)/source/bitfields \
	$(C29SDK_ROOT)/source/kernel/freertos/Source\
	$(C29SDK_ROOT)/source/kernel/freertos/Source/portable/CCS/C2000_C29x\
	$(C29SDK_ROOT)/source/kernel/freertos/Source/portable/MemMang\

C_SRCS_nosyscfg += \
	device.c \

C_SRCS_FREERTOS += \
	tasks.c\
	queue.c\
	list.c\
	timers.c\
	event_groups.c\
	stream_buffer.c\
	heap_4.c\
	port.c\

C_SRCS_PATH_nosyscfg = \
	$(C29SDK_ROOT)/examples/device_support/source \

C_SRCS_syscfg += \
	board.c \
	device.c \
	ti_drivers_config.c \
	ti_dpl_config.c \

C_SRCS_syscfg_SSU += \
	ssu_config.c \

C_SRCS_syscfg_CLB += \
	clb_config.c \

C_SRCS_syscfg_FREERTOS += \
	c2000_freertos.c \

C_SRCS_PATH_syscfg = \
	syscfg \

SYSCFG_GEN_FILES_common = \
	syscfg/clocktree.h \
	syscfg/board.c syscfg/board.h \
	syscfg/device.c syscfg/device.h \
	syscfg/peripheral_frame_mapping.h \
	syscfg/ti_dpl_config.c syscfg/ti_dpl_config.h \
	syscfg/ti_drivers_config.c syscfg/ti_drivers_config.h \

SYSCFG_GEN_FILES_SSU = \
	syscfg/ssu_config.c syscfg/ssu_config.h \

SYSCFG_GEN_FILES_CLB = \
	syscfg/clb_config.c syscfg/clb_config.h \

SYSCFG_GEN_FILES_FREERTOS = \
	syscfg/c2000_freertos.c syscfg/c2000_freertos.h \
