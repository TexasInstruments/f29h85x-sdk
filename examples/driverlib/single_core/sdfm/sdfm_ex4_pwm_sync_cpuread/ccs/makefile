export C29SDK_ROOT?=$(abspath ../../../../../..)
include $(C29SDK_ROOT)/imports.mak

Target = sdfm_ex4_pwm_sync_cpuread
PROFILE?=debug

CMD_SRCS += $(CMD_SRCS_$(CONFIG))

CFLAGS      := $(CFLAGS_common) $(CFLAGS_$(PROFILE))
INCLUDES    := $(INCLUDES_common)
C_SRCS      := $(C_SRCS_common)
C_SRCS_PATH := $(C_SRCS_PATH_common)
LFLAGS      := $(LFLAGS_common)

INCLUDES         += $(INCLUDES_syscfg)
C_SRCS           += $(C_SRCS_syscfg)
C_SRCS_PATH      += $(C_SRCS_PATH_syscfg)
SYSCFG_GEN_FILES += $(SYSCFG_GEN_FILES_common)

$(SYSCFG_GEN_FILES): syscfg

syscfg: ../$(Target).syscfg
	@echo Generating SysConfig files ...
	$(SYSCFG) -s "$(C29SDK_ROOT)/.metadata/sdk.json" --script "../$(Target).syscfg" -o "syscfg" --compiler ticlang

OBJDIR   := obj/$(BOARD)/$(CONFIG)/
BINDIR   := $(BOARD)/$(CONFIG)
OBJS     := $(C_SRCS:%.c=%.o)
ASM_OBJS := $(ASM_SRCS:%.S=%.o)
DEPS     := $(C_SRCS:%.c=%.d)

vpath %.o $(OBJDIR)
vpath %.c $(C_SRCS_PATH)
vpath %.S $(C_SRCS_PATH)
vpath %.lib $(LIBS_PATH)
vpath %.a $(LIBS_PATH)

$(OBJS): | $(OBJDIR) $(BINDIR)

$(BINDIR):
	$(MKDIR) $@

$(OBJDIR):
	$(MKDIR) $@
 
$(OBJDIR)/%.o %.o: %.c
	@echo  Compiling: $<
	$(COMPILER) -c $(CFLAGS) $(INCLUDES) -MMD -o $(OBJDIR)/$@ $<

$(OBJDIR)/%.o %.o: %.S
	@echo  Compiling: $<
	$(COMPILER) -c $(CFLAGS) -o $(OBJDIR)/$@ $<

# All Target
all: $(Target).out

SYSCFG_FLAG ?= true

ifeq ($(SYSCFG_FLAG), true)
	SYSTEM_COMMAND := syscfg $(SYSCFG_GEN_FILES) $(OBJS) $(CMD_SRCS) $(LIBS)
else
	SYSTEM_COMMAND := $(OBJS) $(CMD_SRCS) $(LIBS)
endif

$(Target).out:  $(SYSTEM_COMMAND)
	@echo  .
	@echo  Linking: $(Target) $@ ...
	$(LINKER) $(INCLUDES) $(LFLAGS) $(addprefix -Wl$(comma)-i, $(LIBS_PATH)) -Wl,-m=$(BINDIR)/$(Target).map -o $(BINDIR)/$@ $(addprefix $(OBJDIR), $(OBJS)) $(ASM_OBJS) $(addprefix -l,$(LIBS)) $(CMD_SRCS)
	@echo  Linking: $(Target) $@ Done !!!
	@echo  .

ifeq ($(CONFIG),FLASH)
	@echo 'Post build steps'
	$(CG_TOOL_OBJCOPY) --remove-section=cert -O binary  $(BINDIR)/$(Target).out  $(BINDIR)/$(Target).bin
	$(PYTHON) $(C29SDK_ROOT)/tools/boot/signing/mcu_rom_image_gen.py --image-bin  $(BINDIR)/$(Target).bin --core C29 --swrv 1 --loadaddr 0x10001000 --sign-key $(C29SDK_ROOT)/tools/boot/signing/mcu_gpkey.pem --out-image  $(BINDIR)/$(Target)_cert.bin --device f29h85x --boot FLASH --img_integ no
	$(CG_TOOL_OBJCOPY) --update-section cert=C29-cert-pad.bin  $(BINDIR)/$(Target).out  $(BINDIR)/$(Target)_cert.out
	$(DELETE)  $(BINDIR)/$(Target).out C29-cert-pad.bin
	$(RENAME)  $(BINDIR)/$(Target)_cert.out  $(BINDIR)/$(Target).out
else
	@echo 'Post build steps'
	$(CG_TOOL_OBJCOPY) -O binary  $(BINDIR)/$(Target).out  $(BINDIR)/$(Target).bin
	$(PYTHON) $(C29SDK_ROOT)/tools/boot/signing/mcu_rom_image_gen.py --image-bin  $(BINDIR)/$(Target).bin --core C29 --swrv 1 --loadaddr 0x200E1000 --sign-key $(C29SDK_ROOT)/tools/boot/signing/mcu_gpkey.pem --out-image  $(BINDIR)/$(Target)_cert.bin --device f29h85x --boot RAM --img_integ no
	$(DELETE) C29-cert-pad.bin
endif
	@echo ' '

clean:
	-$(RM) $(Target).out $(Target).bin $(Target)_cert.bin $(Target).map
	-$(RMDIR) $(OBJDIR) $(BINDIR) syscfg obj
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
	python $(X509_PATH)/c29_appimage_x509_cert_gen.py --bin $(BINDIR)/$(Target).out --key $(APPIMAGE_KEY_PATH) --enc y --enckey $(ENC_KEY_PATH) --kd-salt $(KD_SALT) --output $(BINDIR)/$(Target)_signed
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
	python $(X509_PATH)/c29_rom_image_gen.py --sbl-enc --enc-key $(ENC_KEY_PATH) --image-bin $(BINDIR)/$(Target).out --core $(CORE) --swrv $(SWRV) --loadaddr $(LOADADDR) --sign-key $(APPIMAGE_KEY_PATH) --kd-salt $(KD_SALT) --out-image $@ $(DEBUG_FLAG) $(DEBUG_OPTIONS)
	@echo 'Finished building target: $@'

rom_hsfs: $(Target)_rom_hsfs

$(Target)_rom_hsfs: $(Target).out
	@echo 'Key Path: $(APPIMAGE_KEY_PATH)'
	@echo 'Software Revision: $(SWRV)'
	@echo 'Core: $(CORE)'
	@echo 'SBL Run Address: $(LOADADDR)'
	python $(X509_PATH)/c29_rom_image_gen.py --image-bin $(BINDIR)/$(Target).out --core $(CORE) --swrv $(SWRV) --loadaddr $(LOADADDR) --sign-key $(APPIMAGE_KEY_PATH) --out-image $@ $(DEBUG_FLAG) $(DEBUG_OPTIONS)
	@echo 'Finished building target: $@'