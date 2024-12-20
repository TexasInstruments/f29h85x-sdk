export C29SDK_ROOT?=$(abspath ../../..)
include $(C29SDK_ROOT)/imports.mak

PROFILE?=debug

CFLAGS 		:= $(CFLAGS_common) $(CFLAGS_$(PROFILE))
INCLUDES 	:= $(INCLUDES_common)

FILES := \
	ClockP_nortos_c29.c					\
	CpuIdP_c29.c						\
	HwiP_c29_pipe.c						\
	HwiP_c29_pipe_handlers_nortos.c		\
	CacheP_null.c						\
	ClockP_nortos.c						\
	CycleCounterP.c						\
	DebugP_log.c						\
	DebugP_nortos.c						\
	printf.c							\
	SemaphoreP_nortos.c					\
	TimerP.c

ASMFILES := HwiP_c29_pipe_asm.S

LIBDIR 	:= ccs
LIBNAME := dpl_nortos.lib
OBJDIR 	:= obj/
OBJS 	:= $(FILES:%.c=%.o)
OBJS 	+= $(ASMFILES:%.S=%.o)
DEPS 	:= $(FILES:%.c=%.d)

vpath %.o 	$(OBJDIR)
vpath %.c 	dpl/c29 dpl/common
vpath %.S 	dpl/c29
vpath %.lib	$(LIBDIR)

$(OBJDIR)%.o %.o: %.c
	@echo  Compiling: $(LIBNAME): $<
	$(COMPILER) -c $(CFLAGS) $(INCLUDES) -MMD -o $(OBJDIR)/$@ $<

$(OBJDIR)%.o %.o: %.S
	@echo  Compiling: $(LIBNAME): $<
	$(COMPILER) -c $(CFLAGS) $(INCLUDES) -MMD -o $(OBJDIR)/$@ $<

all: $(LIBDIR)/$(LIBNAME)

$(LIBDIR)/$(LIBNAME): $(OBJS) | $(LIBDIR)
	@echo  .
	@echo  Archiving: $(LIBNAME) to $@ ...
	$(AR) $(ARFLAGS) $@ $(addprefix $(OBJDIR),$(OBJS))
	@echo  Archiving: $(LIBNAME) Done !!!
	@echo  .

clean:
	@echo  Cleaning: $(LIBNAME) ...
	$(RMDIR) $(OBJDIR)
	$(RM) $(LIBDIR)/$(LIBNAME)

$(OBJS): | $(OBJDIR)

$(LIBDIR) $(OBJDIR):
	$(MKDIR) $@