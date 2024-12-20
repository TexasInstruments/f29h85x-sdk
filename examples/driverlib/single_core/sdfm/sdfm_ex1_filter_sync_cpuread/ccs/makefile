export C29SDK_ROOT?=$(abspath ../../../../../..)
include $(C29SDK_ROOT)/imports.mak

Target = sdfm_ex1_filter_sync_cpuread
PROFILE?=debug

CMD_SRCS += $(CMD_SRCS_$(CONFIG))

CFLAGS := $(CFLAGS_common) $(CFLAGS_$(PROFILE))
INCLUDES := $(INCLUDES_common)
C_SRCS := $(C_SRCS_common)
LFLAGS := $(LFLAGS_common)

INCLUDES += $(INCLUDES_syscfg)
C_SRCS += $(C_SRCS_syscfg)

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

OBJS  += \
"./syscfg/board.o" \
"./syscfg/device.o"

OBJS  += \
"./$(Target).o" \
"./bitfield_structs.o" \
"./codestartbranch.o" \
$(CMD_SRCS)

"./$(Target).o": ../$(Target).c
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(COMPILER) $(CFLAGS) $(INCLUDES) "$<"
	@echo 'Finished building: $<'
	@echo ' '

"./bitfield_structs.o": $(C29SDK_ROOT)/source/bitfields/bitfield_structs.c
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(COMPILER) $(CFLAGS) $(INCLUDES) "$<"
	@echo 'Finished building: $<'
	@echo ' '

"./codestartbranch.o": $(ASM_SRCS)
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
	$(LINKER) $(INCLUDES) -Wl,-m=$(Target).map $(LFLAGS) -o $@ $(OBJS) $(LIB)
	@echo 'Finished building target: $@'
ifeq ($(CONFIG),FLASH)
	@echo 'Post build steps'
	$(CG_TOOL_OBJCOPY) --remove-section=cert -O binary $(Target).out $(Target).bin
	$(PYTHON) $(C29SDK_ROOT)/tools/boot/signing/mcu_rom_image_gen.py --image-bin $(Target).bin --core C29 --swrv 1 --loadaddr 0x10001000 --sign-key $(C29SDK_ROOT)/tools/boot/signing/mcu_gpkey.pem --out-image $(Target)_cert.bin --device f29h85x --boot FLASH --img_integ no
	$(CG_TOOL_OBJCOPY) --update-section cert=C29-cert-pad.bin $(Target).out $(Target)_cert.out
	$(DELETE) $(Target).out C29-cert-pad.bin
	$(RENAME) $(Target)_cert.out $(Target).out
else
	@echo 'Post build steps'
	$(CG_TOOL_OBJCOPY) -O binary $(Target).out $(Target).bin
	$(PYTHON) $(C29SDK_ROOT)/tools/boot/signing/mcu_rom_image_gen.py --image-bin $(Target).bin --core C29 --swrv 1 --loadaddr 0x200E1000 --sign-key $(C29SDK_ROOT)/tools/boot/signing/mcu_gpkey.pem --out-image $(Target)_cert.bin --device f29h85x --boot RAM --img_integ no
	$(DELETE) C29-cert-pad.bin
endif
	@echo ' '

clean:
	-$(RM) $(Target).out $(Target).bin $(Target)_cert.bin
	-$(RM) $(Target).map
	-$(RM) "./$(Target).o" "./syscfg/board.o" "./bitfield_structs.o" "./device.o" "./codestartbranch.o"
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