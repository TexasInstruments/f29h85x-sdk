export C29SDK_ROOT?=$(abspath ../../../../../..)
include $(C29SDK_ROOT)/imports.mak

Target = freertos_port_validation_tests
PROFILE?=debug

CMD_SRCS_RAM := \
$(C29SDK_ROOT)/examples/kernel/freertos/single_core/freertos_port_validation_tests/f29h85x_port_val_ram.cmd

CMD_SRCS_FLASH := \
$(C29SDK_ROOT)/examples/kernel/freertos/single_core/freertos_port_validation_tests/f29h85x_port_val_flash.cmd


CMD_SRCS += $(CMD_SRCS_$(CONFIG))

CFLAGS      := $(CFLAGS_common) $(CFLAGS_$(PROFILE))
INCLUDES    := $(INCLUDES_common)
C_SRCS      := $(C_SRCS_common)
C_SRCS_PATH := $(C_SRCS_PATH_common)
LFLAGS      := $(LFLAGS_common)

ASM_SRCS    += $(ASM_SRCS_FREERTOS)
C_SRCS      += $(C_SRCS_FREERTOS)
S_SRCS      += $(S_SRCS_FREERTOS)

INCLUDES += \
-I "$(C29SDK_ROOT)/examples/kernel/freertos/single_core/freertos_port_validation_tests/include" \

C_SRCS_PATH += \
	$(C29SDK_ROOT)/examples/kernel/freertos/single_core/freertos_port_validation_tests/Minimal\

C_SRCS_PORTVAL := \
	main.c\
    TestRunner.c\
    IntQueueTimer.c\
    RegTests.c\
	AbortDelay.c\
	BlockQ.c\
	blocktim.c\
	countsem.c\
	death.c\
	dynamic.c\
	EventGroupsDemo.c\
	flop.c\
	GenQTest.c\
	integer.c\
	IntQueue.c\
	IntSemTest.c\
	MessageBufferAMP.c\
	MessageBufferDemo.c\
	PollQ.c\
	QPeek.c\
	QueueOverwrite.c\
	QueueSet.c\
	QueueSetPolling.c\
	recmutex.c\
	semtest.c\
	StaticAllocation.c\
	StreamBufferDemo.c\
	StreamBufferInterrupt.c\
	TaskNotifyArray.c\
	TaskNotify.c\
	TimerDemo.c\

TEMP	:= $(C_SRCS)
C_SRCS	= $(filter-out $(Target).c, $(TEMP))
C_SRCS  += $(C_SRCS_PORTVAL)

SYSCFG_FLAG  = false
C_SRCS      += $(C_SRCS_nosyscfg)
C_SRCS_PATH += $(C_SRCS_PATH_nosyscfg)

OBJDIR   := obj/$(BOARD)/$(CONFIG)/
BINDIR   := $(BOARD)/$(CONFIG)
OBJS     := $(C_SRCS:%.c=%.o)
ASM_OBJS := $(ASM_SRCS:%.S=%.o)
S_OBJS   := $(S_SRCS:%.S=%.o)
DEPS     := $(C_SRCS:%.c=%.d)

vpath %.o $(OBJDIR)
vpath %.c $(C_SRCS_PATH)
vpath %.S $(C_SRCS_PATH) $(S_SRCS_PATH_common)
vpath %.lib $(LIBS_PATH)
vpath %.a $(LIBS_PATH)

$(OBJS): | $(OBJDIR) $(BINDIR)

$(OBJDIR):
	$(MKDIR) $@

$(BINDIR):
	$(MKDIR) $@

$(OBJDIR)/%.o %.o: %.c
	@echo  Compiling: $<
	$(COMPILER) -c $(CFLAGS) $(INCLUDES) -MMD -o $(OBJDIR)/$@ $<

$(OBJDIR)/%.o %.o: %.S
	@echo  Compiling: $<
	$(COMPILER) -c $(CFLAGS) $(INCLUDES) -o $(OBJDIR)/$@ $< -l$(C29SDK_ROOT)/source/driverlib/ccs/driverlib.lib

# All Target
all: $(Target).out

SYSCFG_FLAG ?= true

ifeq ($(SYSCFG_FLAG), true)
	SYSTEM_COMMAND := syscfg $(SYSCFG_GEN_FILES) $(OBJS) $(S_OBJS) $(CMD_SRCS) $(LIBS)
else
	SYSTEM_COMMAND := $(OBJS) $(S_OBJS) $(CMD_SRCS) $(LIBS)
endif

$(Target).out:  $(SYSTEM_COMMAND)
	@echo  .
	@echo  Linking: $(Target) $@ ...
	$(LINKER) $(INCLUDES) $(LFLAGS) $(addprefix -Wl$(comma)-i, $(LIBS_PATH)) -Wl,-m=$(BINDIR)/$(Target).map -o $(BINDIR)/$@ $(addprefix $(OBJDIR), $(OBJS)) $(ASM_OBJS) $(addprefix $(OBJDIR), $(S_OBJS)) $(addprefix -l,$(LIBS)) $(CMD_SRCS)
	@echo  Linking: $(Target) $@ Done !!!
	@echo  .

ifeq ($(CONFIG),FLASH)
	@echo 'Post build steps'
	$(CG_TOOL_OBJCOPY) --remove-section=cert -O binary $(BINDIR)/$(Target).out $(BINDIR)/$(Target).bin
	$(PYTHON) $(C29SDK_ROOT)/tools/boot/signing/mcu_rom_image_gen.py --image-bin $(BINDIR)/$(Target).bin --core C29 --swrv 1 --loadaddr 0x10001000 --sign-key $(C29SDK_ROOT)/tools/boot/signing/mcu_gpkey.pem --out-image $(BINDIR)/$(Target)_cert.bin --device f29h85x --boot FLASH --img_integ no
	$(CG_TOOL_OBJCOPY) --update-section cert=C29-cert-pad.bin $(BINDIR)/$(Target).out $(BINDIR)/$(Target)_cert.out
	$(DELETE) $(BINDIR)/$(Target).out C29-cert-pad.bin
	$(RENAME) $(BINDIR)/$(Target)_cert.out $(BINDIR)/$(Target).out
else
	@echo 'Post build steps'
	$(CG_TOOL_OBJCOPY) -O binary $(BINDIR)/$(Target).out $(BINDIR)/$(Target).bin
	$(PYTHON) $(C29SDK_ROOT)/tools/boot/signing/mcu_rom_image_gen.py --image-bin $(BINDIR)/$(Target).bin --core C29 --swrv 1 --loadaddr 0x200E1000 --sign-key $(C29SDK_ROOT)/tools/boot/signing/mcu_gpkey.pem --out-image $(BINDIR)/$(Target)_cert.bin --device f29h85x --boot RAM --img_integ no
	$(DELETE) C29-cert-pad.bin
endif
	@echo ' '

clean:
	-$(RM) $(Target).out $(Target).bin $(Target)_cert.bin $(Target).map
	-$(RMDIR) $(OBJDIR) $(BINDIR) syscfg obj
	-@echo 'Finished clean for $(Target)'
	-@echo ' '

