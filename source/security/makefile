export C29SDK_ROOT?=$(abspath ../..)
include $(C29SDK_ROOT)/imports.mak

PROFILE?=debug

CFLAGS 		:= $(CFLAGS_common) $(CFLAGS_$(PROFILE)) -DSOC_F29H85X -D_F29H85x
INCLUDES 	:= $(INCLUDES_common)
INCLUDES 	+= -I $(C29SDK_ROOT)/source/security
INCLUDES 	+= -I $(C29SDK_ROOT)/source/kernel/nortos/dpl/c29
INCLUDES 	+= -I $(C29SDK_ROOT)/source

FILES := \
	hsmclient_loadhsmrt.c	\
	hsmclient_utils.c		\
	hsmclient_wait_for_boot_notify.c	\
	hsmclient.c 			\
	sipc_notify_cfg.c		\
	sipc_notify_src.c 		\
	soc.c

LIBDIR 	:= ccs
LIBNAME := security_drivers.lib
OBJDIR 	:= obj/
OBJS 	:= $(FILES:%.c=%.o)
DEPS 	:= $(FILES:%.c=%.d)

vpath %.o $(OBJDIR)
vpath %.c drivers/hsmclient/soc/f29h85x								\
		  drivers/hsmclient/utils 									\
		  drivers/hsmclient drivers/secure_ipc_notify/soc/f29h85x 	\
		  drivers/secure_ipc_notify 								\
		  drivers/soc/f29h85x
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