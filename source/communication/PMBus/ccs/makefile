export C29SDK_ROOT?=$(abspath ../../c29_sdk/mcu_sdk_f29h85x)
include $(C29SDK_ROOT)/imports.mak
PMBUS_ROOT?=$(abspath ../../c29_sdk/mcu_sdk_f29h85x/source/communication/PMBus/)
PMBUS_SRC_CONTROLLER?=$(abspath ../source)
PMBUS_SRC_TARGET?=$(abspath ../source/target)

PROFILE?=debug
OBJDIR=$(PROFILE)
Target=$(abspath ../lib)/F29H85x_PMBus_Communication_Stack.lib

CFLAGS := $(CFLAGS_common) $(CFLAGS_$(PROFILE))
CFLAGS += -D__PMBUS_SW_VERSION__=0x01020000U

ifeq ($(PROFILE), debug)
	CFLAGS += $(CFLAGS_debug)
endif

INCLUDES := $(INCLUDES_common)
INCLUDES += -I "$(PMBUS_ROOT)/include"

C_SRCS := $(PMBUS_SRC_CONTROLLER)/pmbus_stack_config.c $(PMBUS_SRC_CONTROLLER)/pmbus_stack_handler.c 
C_SRCS += $(PMBUS_SRC_TARGET)/pmbus_stack_handler_extended_command.c $(PMBUS_SRC_TARGET)/pmbus_stack_handler_target_block_write_process_call.c  $(PMBUS_SRC_TARGET)/pmbus_stack_handler_target_idle.c $(PMBUS_SRC_TARGET)/pmbus_stack_handler_target_read_block.c $(PMBUS_SRC_TARGET)/pmbus_stack_handler_target_read_wait_for_eom.c $(PMBUS_SRC_TARGET)/pmbus_stack_handler_target_receive_byte_wait_for_eom.c
LFLAGS := $(LFLAGS_common)
OBJ = $(addprefix $(OBJDIR)/, $(notdir $(C_SRCS:.c=.o)))

all: $(Target)

$(Target): $(OBJDIR) $(OBJ)
	@echo : $(INCLUDES)
	@echo 'Building target: $@'
	@echo 'Invoking: Archiver'
	$(AR) $(ARFLAGS) $(Target) $(OBJ)
	@echo 'Finished building target: $@'
	@echo ' '

$(OBJDIR):
	@echo 'Creating folder $(OBJDIR)'
	mkdir $(OBJDIR)

$(OBJDIR)/%.o : $(PMBUS_SRC_CONTROLLER)/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(COMPILER) $(CFLAGS) $(INCLUDES) "$<" -o "$@"
	@echo 'Finished building: $<'
	@echo ' '

$(OBJDIR)/%.o : $(PMBUS_SRC_TARGET)/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	$(COMPILER) $(CFLAGS) $(INCLUDES) "$<" -o "$@"
	@echo 'Finished building: $<'
	@echo ' '







