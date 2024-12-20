export C29SDK_ROOT?=$(abspath ../..)
include $(C29SDK_ROOT)/imports.mak

PROFILE?=debug

CFLAGS := $(CFLAGS_common) $(CFLAGS_$(PROFILE))
INCLUDES := $(INCLUDES_common)

FILES := \
	adc.c \
	asysctl.c \
	bootrom.c \
	clb.c \
	cmpss.c \
	cputimer.c \
	dac.c \
	dcc.c \
	dlt.c \
	ecap.c \
	epg.c \
	epwm.c \
	eqep.c \
	erad.c \
	erroraggregator.c \
	escss.c \
	esm.c \
	flash.c \
	fsi.c \
	gpio.c \
	hrcap.c \
	hrpwm.c \
	i2c.c \
	interrupt.c \
	ipc.c \
	lin.c \
	mcan.c \
	memss.c \
	pmbus.c \
	rtdma.c \
	sdfm.c \
	sent.c \
	spi.c \
	ssu.c \
	sysctl.c \
	uart.c \
	xbar.c

LIBDIR := ccs
LIBNAME := driverlib.lib
OBJDIR := obj/
OBJS := $(FILES:%.c=%.o)
DEPS := $(FILES:%.c=%.d)

vpath %.o $(OBJDIR)
vpath %.c $(FILES)
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