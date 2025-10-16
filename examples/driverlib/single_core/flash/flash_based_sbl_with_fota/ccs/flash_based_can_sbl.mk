export C29SDK_ROOT?=$(abspath ../../../../../..)
include $(C29SDK_ROOT)/imports.mak

# For BANKMODE1_NONSECURE config, use "Make -f flash_based_can_sbl.mk all"
# For BANKMODE3_NONSECURE config, use "Make -f flash_based_can_sbl.mk all BANKMODE=3 APP=NONSECURE"
# For BANKMODE1_SECURE_CP config, use "Make -f flash_based_can_sbl.mk all BANKMODE=1 APP=SECURE"
# For BANKMODE3_SECURE_CP config, use "Make -f flash_based_can_sbl.mk all BANKMODE=3 APP=SECURE"

BANKMODE ?= 1
APP ?= NONSECURE

all: 
	$(MAKE) -C $(CURDIR) -f makefile_can_led_blinky all
	$(MAKE) -C $(CURDIR) -f makefile_can_sbl all BANKMODE=$(BANKMODE) APP=$(APP)


clean:
	$(MAKE) -C $(CURDIR) -f makefile_can_led_blinky clean
	$(MAKE) -C $(CURDIR) -f makefile_can_sbl clean BANKMODE=$(BANKMODE) APP=$(APP)
