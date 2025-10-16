export C29SDK_ROOT?=$(abspath ../..)
include $(C29SDK_ROOT)/imports.mak

export C29SDL_ROOT?=$(abspath .)

PROFILE?=debug

INCLUDES_sdl := -I "$(C29SDL_ROOT)"

FILES_PATH_common = \
	dcc \
	err_aggr \
	esm \
	include \
	lcm \
	sic \
	sysctl \
	memss \
	stack \
	pipe \

CFLAGS := $(CFLAGS_common) $(CFLAGS_$(PROFILE))
INCLUDES := $(INCLUDES_common) $(INCLUDES_sdl)

FILES_common := \
	sdl_dcc.c \
	sdl_edc.c \
	sdl_err_aggr.c \
	sdl_esm_priv.c \
	sdl_esm_safety_aggr.c \
	sdl_esm.c \
	sdl_ip_esm.c \
	sdl_lcm.c \
	sdl_sic.c \
	sdl_sysctl.c \
	sdl_memss.c \
	sdl_stack.c \
	sdl_pipe.c \

ASMFILES_common := \
    sdl_sic_s.asm \

FILES := $(FILES_common) $(FILES_$(PROFILE))
ASMFILES := $(ASMFILES_common) $(ASMFILES_$(PROFILE))
FILES_PATH := $(FILES_PATH_common) $(FILES_PATH_$(PROFILE))

LIBDIR := $(C29SDL_ROOT)/ccs/
LIBNAME := sdl_$(PROFILE).lib
OBJDIR := obj/
OBJS := $(FILES:%.c=%.o)
OBJS += $(ASMFILES:%.asm=%.o)
DEPS := $(FILES:%.c=%.d)

vpath %.o $(OBJDIR)
vpath %.c $(FILES_PATH)
vpath %.asm $(FILES_PATH)
vpath %.lib $(LIBDIR)

$(OBJDIR)%.o %.o: %.c
	@echo  Compiling: $(LIBNAME): $<
	$(COMPILER) -c $(CFLAGS) $(INCLUDES) -MMD -o $(OBJDIR)/$@ $<

$(OBJDIR)/%.o %.o: %.asm
	@echo  Compiling: $(LIBNAME): $<
	$(COMPILER) -c $(CFLAGS) $(INCLUDES) -o $(OBJDIR)/$@ $<

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