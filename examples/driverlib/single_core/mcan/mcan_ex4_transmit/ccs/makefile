export C29SDK_ROOT?=$(abspath ../../../../../..)
include $(C29SDK_ROOT)/imports.mak

Target = mcan_ex4_transmit
PROFILE?=debug

CMD_SRCS += $(CMD_SRCS_$(CONFIG))

CFLAGS := $(CFLAGS_common) $(CFLAGS_$(PROFILE))
INCLUDES := $(INCLUDES_common)
C_SRCS := $(C_SRCS_common)
LFLAGS := $(LFLAGS_common)

C_SRCS += $(C_SRCS_nosyscfg)

OBJS  += \
"./device.o"

"./device.o": $(C29SDK_ROOT)/examples/device_support/source/device.c
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(COMPILER) $(CFLAGS) $(INCLUDES) "$<"
	@echo 'Finished building: $<'
	@echo ' '

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

