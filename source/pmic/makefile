export C29SDK_ROOT?=$(abspath ../..)
include $(C29SDK_ROOT)/imports.mak

PROFILE?=debug
PMIC?=tps653860xx

CFLAGS 		:= $(CFLAGS_common) $(CFLAGS_$(PROFILE)) -D$(PMIC)
INCLUDES 	:= $(INCLUDES_common)
INCLUDES 	+= -I $(C29SDK_ROOT)/source/kernel/dpl
INCLUDES 	+= -I $(C29SDK_ROOT)/source/pmic
INCLUDES 	+= -I $(C29SDK_ROOT)/source/pmic/$(PMIC)/pmic-lld/include

FILES := \
	pmic_$(PMIC).c		\
    pmic_lld.c 			\
    pmic.c 				\
    pmic_core.c 		\
    pmic_io.c 			\
    pmic_power.c 		\
    pmic_wdg.c 			\
    pmic_irq.c 			\
    pmic_gpio.c 		\
    pmic_esm.c 			\

ifeq ($(PMIC), tps653860xx)
	FILES += pmic_common.c pmic_fsm.c pmic_timer.c
endif

LIBDIR 	:= ccs
LIBNAME := pmic_$(PMIC).lib
OBJDIR 	:= obj/
OBJS 	:= $(FILES:%.c=%.o)
DEPS 	:= $(FILES:%.c=%.d)

vpath %.o $(OBJDIR)
vpath %.c $(PMIC)/pmic-lld/src
vpath %.lib $(LIBDIR)

$(OBJDIR)%.o %.o: %.c
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