export C29SDK_ROOT?=$(abspath ../../../../../..)
include $(C29SDK_ROOT)/imports.mak

Target = epg_ex3_generate_two_offset_clocks_with_siggen
PROFILE?=debug

CMD_SRCS += $(CMD_SRCS_$(CONFIG))

CFLAGS      := $(CFLAGS_common) $(CFLAGS_$(PROFILE))
INCLUDES    := $(INCLUDES_common)
C_SRCS      := $(C_SRCS_common)
C_SRCS_PATH := $(C_SRCS_PATH_common)
LFLAGS      := $(LFLAGS_common)

SYSCFG_FLAG  = false
C_SRCS      += $(C_SRCS_nosyscfg)
C_SRCS_PATH += $(C_SRCS_PATH_nosyscfg)

OBJDIR   := obj/
OBJS     := $(C_SRCS:%.c=%.o)
ASM_OBJS := $(ASM_SRCS:%.S=%.o)
DEPS     := $(C_SRCS:%.c=%.d)

vpath %.o $(OBJDIR)
vpath %.c $(C_SRCS_PATH)
vpath %.S $(C_SRCS_PATH)
vpath %.lib $(LIBS_PATH)
vpath %.a $(LIBS_PATH)

$(OBJS): | $(OBJDIR)

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
	$(LINKER) $(INCLUDES) $(LFLAGS) $(addprefix -Wl$(comma)-i, $(LIBS_PATH)) -Wl,-m=$(Target).map -o $@ $(addprefix $(OBJDIR), $(OBJS)) $(ASM_OBJS) $(addprefix -l,$(LIBS)) $(CMD_SRCS)
	@echo  Linking: $(Target) $@ Done !!!
	@echo  .

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
	-$(RM) $(Target).out $(Target).bin $(Target)_cert.bin $(Target).map
	-$(RMDIR) $(OBJDIR) syscfg
	-@echo 'Finished clean for $(Target)'
	-@echo ' '

