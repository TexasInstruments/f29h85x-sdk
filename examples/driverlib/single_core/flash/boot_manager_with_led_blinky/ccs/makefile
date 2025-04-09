export C29SDK_ROOT?=$(abspath ../../../../../..)
include $(C29SDK_ROOT)/imports.mak

all: 
	$(MAKE) -C $(CURDIR) -f makefile_led_ex1_blinky_cpu1 all
	$(MAKE) -C $(CURDIR) -f makefile_ex4_uart_boot_manager all

clean:
	$(MAKE) -C $(CURDIR) -f makefile_led_ex1_blinky_cpu1 clean
	$(MAKE) -C $(CURDIR) -f makefile_ex4_uart_boot_manager clean