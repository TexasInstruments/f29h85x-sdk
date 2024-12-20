export C29SDK_ROOT?=$(abspath ../../../../../..)
include $(C29SDK_ROOT)/imports.mak

CMD_SRCS += $(C29SDK_ROOT)/examples/device_support/cmd/f29h85x_ram_lnk_hsm.cmd

Target = ex3_uart_flash_kernel
PROFILE?=debug

CFLAGS := $(CFLAGS_common) $(CFLAGS_$(PROFILE))
LFLAGS := $(LFLAGS_common)
INCLUDES_PATH := $(INCLUDES_common) $(INCLUDES_syscfg)
INCLUDES = $(addprefix -I , $(INCLUDES_PATH) $(INCLUDES_PATH_common))
FILES_PATH = $(FILES_PATH_common) $(C_SRCS_PATH_common)
LIBS = $(LIB) $(LIBRARIES_common)
OBJS = $(CMD_SRCS)

APP_FLAG?=-DDFU_CPU1_APP

ifeq ($(APP),KP)
APP_FLAG=-DKP_APP
endif
ifeq ($(APP),CP)
APP_FLAG=-DCP_APP
DEVICE_TYPE=HS
DEBUG_TIFS=yes
ENC_SBL_ENABLED=yes
endif

ifeq ($(DEVICE_TYPE),HS)
DEBUG_COMMAND=
IMG_INTEG_CMD=--img_integ yes
else
DEBUG_COMMAND=--debug DBG_SOC_DEFAULT
IMG_INTEG_CMD=--img_integ no
endif
ifeq ($(DEBUG_TIFS), yes)
DEBUG_COMMAND=
else
DEBUG_COMMAND=--debug $(DEBUG_OPTION)
endif
ifeq ($(ENC_SBL_ENABLED), yes)
ENC_SBL_OPTION=--sbl-enc --enc-key $(C29SDK_ROOT)/tools/boot/signing/mcu_custMek.key --kd-salt $(C29SDK_ROOT)/tools/boot/signing/kd_salt.txt
else
ENC_SBL_OPTION=
endif

# Path to recognize all C-source files exhaustively
FILES_PATH_common = \
	.. \

# Addintional include path (-i) for the compiler
INCLUDES_PATH_common = \
	.. \
	${C29SDK_ROOT}/source \
	${C29SDK_ROOT}/source/flash_api/include/FlashAPI \
	${C29SDK_ROOT}/source/flash_api/include/Constants \

# Addintional library path (-l) for the compiler
LIBRARIES_common = \
	${C29SDK_ROOT}/source/flash_api/lib/F29H85x_NWFlashAPI_v21.00.00.00.lib \
	${C29SDK_ROOT}/source/driverlib/ccs/driverlib.lib \
	${C29SDK_ROOT}/source/kernel/nortos/ccs/dpl_nortos.lib \
	${C29SDK_ROOT}/source/security/ccs/security_drivers.lib \

OBJDIR := $(abspath)

build-syscfg: ../$(Target).syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	$(SYSCFG) -s "$(C29SDK_ROOT)/.metadata/sdk.json" --script "../$(Target).syscfg" -o "syscfg" --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-syscfg ../$(Target).syscfg
syscfg/board.h: build-syscfg
syscfg/board.cmd.genlibs: build-syscfg
syscfg/pinmux.csv: build-syscfg

"./syscfg/board.o": ./syscfg/board.c
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	$(COMPILER) $(CFLAGS) $(INCLUDES) -MMD -MP -MF"syscfg/$(basename $(<F)).d" -MT"$(@)" -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

"./syscfg/device.o": ./syscfg/device.c
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	$(COMPILER) $(CFLAGS) $(INCLUDES) -MMD -MP -MF"syscfg/$(basename $(<F)).d" -MT"$(@)" -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

"./syscfg/ti_drivers_config.o": ./syscfg/ti_drivers_config.c
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	$(COMPILER) $(CFLAGS) $(INCLUDES) -MMD -MP -MF"syscfg/$(basename $(<F)).d" -MT"$(@)" -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

"./syscfg/ti_dpl_config.o": ./syscfg/ti_dpl_config.c
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	$(COMPILER) $(CFLAGS) $(INCLUDES) -MMD -MP -MF"syscfg/$(basename $(<F)).d" -MT"$(@)" -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

OBJS  += \
"./syscfg/board.o" \
"./syscfg/device.o" \
"./syscfg/ti_drivers_config.o"  \
"./syscfg/ti_dpl_config.o"      \

syscfg-gui:
	$(SYSCFG_ROOT)/nw/nw $(SYSCFG_ROOT) --product $(C29SDK_ROOT)/.metadata/sdk.json --device F29H85x --context CPU1 --part F29H85x_256ZEX --package 256ZEX --output generated/  ../$(Target).syscfg

C_SRCS += $(foreach dir, $(FILES_PATH), $(wildcard $(dir)/*.c))
ASM_SRCS = $(foreach dir, $(FILES_PATH), $(wildcard $(dir)/*.asm))
vpath %.c $(FILES_PATH)
vpath %.asm $(FILES_PATH)

OBJS += $(notdir $(C_SRCS:%.c=%.o))
OBJS += $(notdir $(ASM_SRCS:%.asm=%.o))

CFLAGS		+= $(APP_FLAG)
CFLAGS      += -DSOC_F29H85X

OBJS_CLEAN = $(filter-out $(CMD_SRCS), $(OBJS))

$(OBJDIR)/%.o %.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(COMPILER) $(CFLAGS) $(INCLUDES) "$<"
	@echo 'Finished building: $<'
	@echo ' '

$(OBJDIR)/%.o %.o: %.asm
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(COMPILER) $(CFLAGS) $(INCLUDES) "$<"
	@echo 'Finished building: $<'
	@echo ' '

# All Target
all: $(Target).out

$(Target).out: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	$(LINKER) $(INCLUDES) -Wl,-m=$(Target).map $(LFLAGS) -o $@ $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo 'Post build steps'
	@echo 'Creating bin file'
	$(CG_TOOL_OBJCOPY) --strip-all -O binary $(Target).out $(Target).bin
	@echo 'Finished building bin file: $(Target).bin'
	@echo 'Creating certificate appended binary'
ifeq ($(OS),Windows_NT)
	$(PYTHON) $(C29SDK_ROOT)/tools/boot/signing/mcu_rom_image_gen.py $(ENC_SBL_OPTION) --image-bin $(Target).bin --core C29 --swrv 1 --loadaddr 0x200E1000 --sign-key $(C29SDK_ROOT)/tools/boot/signing/mcu_custMpk.pem --out-image $(Target).cert.bin --device f29h85x --boot RAM $(IMG_INTEG_CMD) $(DEBUG_COMMAND)
	del C29-cert-pad.bin
else
	$(PYTHON) $(C29SDK_ROOT)/tools/boot/signing/mcu_rom_image_gen.py $(ENC_SBL_OPTION) --image-bin $(Target).bin --core C29 --swrv 1 --loadaddr 0x200E1000 --sign-key $(C29SDK_ROOT)/tools/boot/signing/mcu_custMpk.pem --out-image $(Target).cert.bin --device f29h85x --boot RAM $(IMG_INTEG_CMD) $(DEBUG_COMMAND)
	rm C29-cert-pad.bin
endif
	@echo 'Finished building certificate appended binary: $(Target).cert.bin'
	@echo ' '

clean:
	-$(RM) $(Target).out
	-$(RM) $(Target).map
	-$(RM) $(OBJS_CLEAN)
	-$(RMDIR) syscfg
	-@echo 'Finished clean for $(Target)'
	-@echo ' '

# x509 certificate signed target
X509_PATH ?= $(C29SDK_ROOT)/tools/boot/signing
APPIMAGE_KEY_PATH ?= $(X509_PATH)/c29_custMpk.pem
ENC_KEY_PATH ?= $(X509_PATH)/c29_custMek.key
KD_SALT ?= $(X509_PATH)/kd_salt.txt
SWRV ?= 1
CORE ?= C29
LOADADDR ?= 0x0
ENC ?= y
DEBUG_FLAG ?=
DEBUG_OPTION ?=

image_signed: $(Target)_signed

$(Target)_signed: $(Target).out
	@echo 'Key Path: $(APPIMAGE_KEY_PATH)'
	@echo 'Encryption Key Path: $(ENC_KEY_PATH)'
	@echo 'KD Path: $(KD_SALT)'
	@echo 'Encryption: y'
	python $(X509_PATH)/c29_appimage_x509_cert_gen.py --bin $(Target).out --key $(APPIMAGE_KEY_PATH) --enc y --enckey $(ENC_KEY_PATH) --kd-salt $(KD_SALT) --output $(Target)_signed
	@echo 'Finished building target: $@'
	@echo ' '

rom_hsse: $(Target)_rom_hsse

$(Target)_rom_hsse: $(Target).out
	@echo 'Key Path: $(APPIMAGE_KEY_PATH)'
	@echo 'Encryption Key Path: $(ENC_KEY_PATH)'
	@echo 'KD Path: $(KD_SALT)'
	@echo 'Encryption: y'
	@echo 'Software Revision: $(SWRV)'
	@echo 'Core: $(CORE)'
	@echo 'SBL Run Address: $(LOADADDR)'
	python $(X509_PATH)/c29_rom_image_gen.py --sbl-enc --enc-key $(ENC_KEY_PATH) --image-bin $(Target).out --core $(CORE) --swrv $(SWRV) --loadaddr $(LOADADDR) --sign-key $(APPIMAGE_KEY_PATH) --kd-salt $(KD_SALT) --out-image $@ $(DEBUG_FLAG) $(DEBUG_OPTIONS)
	@echo 'Finished building target: $@'

rom_hsfs: $(Target)_rom_hsfs

$(Target)_rom_hsfs: $(Target).out
	@echo 'Key Path: $(APPIMAGE_KEY_PATH)'
	@echo 'Software Revision: $(SWRV)'
	@echo 'Core: $(CORE)'
	@echo 'SBL Run Address: $(LOADADDR)'
	python $(X509_PATH)/c29_rom_image_gen.py --image-bin $(Target).out --core $(CORE) --swrv $(SWRV) --loadaddr $(LOADADDR) --sign-key $(APPIMAGE_KEY_PATH) --out-image $@ $(DEBUG_FLAG) $(DEBUG_OPTIONS)
	@echo 'Finished building target: $@'