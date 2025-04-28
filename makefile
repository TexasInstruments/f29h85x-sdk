
#
# Makefile to build driverlib and all examples
#

include imports.mak

# debug, release
PROFILE?=debug

all:
	$(MAKE) -C . -f makefile driverlib PROFILE=$(PROFILE)
	$(MAKE) -C . -f makefile examples-all PROFILE=$(PROFILE)

clean:
	$(MAKE) -C . -f makefile driverlib-clean PROFILE=$(PROFILE)
	$(MAKE) -C . -f makefile examples-clean-all PROFILE=$(PROFILE)

driverlib:
	$(MAKE) -C source/driverlib -f makefile all PROFILE=$(PROFILE)

driverlib-clean:
	$(MAKE) -C source/driverlib -f makefile clean PROFILE=$(PROFILE)

examples-all:
	$(MAKE) -C . -f makefile examples PROFILE=$(PROFILE)

examples-clean-all:
	$(MAKE) -C . -f makefile examples-clean PROFILE=$(PROFILE)


BUILD_EXAMPLE_ALL =
BUILD_EXAMPLE_ALL += adc_ex1_soc_software
BUILD_EXAMPLE_ALL += adc_ex2_soc_epwm
BUILD_EXAMPLE_ALL += adc_ex3_temp_sensor
BUILD_EXAMPLE_ALL += adc_ex4_software_sync
BUILD_EXAMPLE_ALL += adc_ex5_soc_continuous
BUILD_EXAMPLE_ALL += adc_ex6_continuous_dma
BUILD_EXAMPLE_ALL += adc_ex7_ppb_offset
BUILD_EXAMPLE_ALL += adc_ex8_ppb_limits
BUILD_EXAMPLE_ALL += adc_ex9_ppb_delay
BUILD_EXAMPLE_ALL += adc_ex10_multiple_soc_epwm
BUILD_EXAMPLE_ALL += adc_ex11_burst_mode_epwm
BUILD_EXAMPLE_ALL += adc_ex12_burst_mode_oversampling
BUILD_EXAMPLE_ALL += adc_ex13_soc_oversampling
BUILD_EXAMPLE_ALL += adc_ex14_ppb_pwm_trip
BUILD_EXAMPLE_ALL += adc_ex15_trigger_repeater_oversampling
BUILD_EXAMPLE_ALL += adc_ex16_trigger_repeater_undersampling
BUILD_EXAMPLE_ALL += adc_ex17_safety_checker
BUILD_EXAMPLE_ALL += clb_academy_lab
BUILD_EXAMPLE_ALL += clb_ecap_academy_lab
BUILD_EXAMPLE_ALL += clb_ex1_combinatorial_logic
BUILD_EXAMPLE_ALL += clb_ex2_gpio_input_filter
BUILD_EXAMPLE_ALL += clb_ex3_auxiliary_pwm
BUILD_EXAMPLE_ALL += clb_ex4_pwm_protection
BUILD_EXAMPLE_ALL += cmpss_ex1_asynch
BUILD_EXAMPLE_ALL += cmpss_ex2_digital_filter
BUILD_EXAMPLE_ALL += buffdac_ex1_enable
BUILD_EXAMPLE_ALL += buffdac_ex2_random
BUILD_EXAMPLE_ALL += dcc_ex1_single_shot_verification
BUILD_EXAMPLE_ALL += dcc_ex2_single_shot_measurement
BUILD_EXAMPLE_ALL += dcc_ex3_continuous_monitoring_of_clock
BUILD_EXAMPLE_ALL += dlt_ex1_datalog_tag
BUILD_EXAMPLE_ALL += dlt_ex2_dma_fsi_export
BUILD_EXAMPLE_ALL += dlt_ex3_datalog_erad
BUILD_EXAMPLE_ALL += ecap_academy_lab
BUILD_EXAMPLE_ALL += ecap_ex1_apwm
BUILD_EXAMPLE_ALL += ecap_ex2_capture_pwm
BUILD_EXAMPLE_ALL += ecap_ex3_apwm_phase_shift
BUILD_EXAMPLE_ALL += emif_ex1_16bit_sdram_syscfg
BUILD_EXAMPLE_ALL += emif_ex2_16bit_asram_syscfg
BUILD_EXAMPLE_ALL += emif_ex3_32bit_sdram_syscfg
BUILD_EXAMPLE_ALL += empty_driverlib_project
BUILD_EXAMPLE_ALL += epg_ex1_generate_clocks
BUILD_EXAMPLE_ALL += epg_ex2_generate_two_offset_clocks
BUILD_EXAMPLE_ALL += epg_ex3_generate_two_offset_clocks_with_siggen
BUILD_EXAMPLE_ALL += epg_ex4_generate_serial_data
BUILD_EXAMPLE_ALL += epg_ex5_generate_serial_data_shift_mode
BUILD_EXAMPLE_ALL += epwm_ex1_trip_zone
BUILD_EXAMPLE_ALL += epwm_ex2_updown_aq
BUILD_EXAMPLE_ALL += epwm_ex3_synchronization
BUILD_EXAMPLE_ALL += epwm_ex4_digital_compare
BUILD_EXAMPLE_ALL += epwm_ex5_digital_compare_event_filter
BUILD_EXAMPLE_ALL += epwm_ex6_valley_switching
BUILD_EXAMPLE_ALL += epwm_ex7_edge_filter
BUILD_EXAMPLE_ALL += epwm_ex8_deadband
BUILD_EXAMPLE_ALL += epwm_ex9_dma
BUILD_EXAMPLE_ALL += epwm_ex10_chopper
BUILD_EXAMPLE_ALL += epwm_ex11_configure_signal
BUILD_EXAMPLE_ALL += epwm_ex12_monoshot_mode
BUILD_EXAMPLE_ALL += epwm_ex13_up_aq
BUILD_EXAMPLE_ALL += epwm_ex15_xcmp_multiple_edges
BUILD_EXAMPLE_ALL += epwm_ex16_event_detection
BUILD_EXAMPLE_ALL += eqep_academy_lab
BUILD_EXAMPLE_ALL += eqep_ex2_freq_cal_interrupt
BUILD_EXAMPLE_ALL += eqep_ex5_speed_dir_motor
BUILD_EXAMPLE_ALL += erad_ex1_profile_function_no_syscfg
BUILD_EXAMPLE_ALL += erad_ex2_profile_function_syscfg
BUILD_EXAMPLE_ALL += erad_ex3_bus_monitor_no_syscfg
BUILD_EXAMPLE_ALL += erad_ex4_bus_monitor_syscfg
BUILD_EXAMPLE_ALL += erad_ex5_stack_overflow_detect_no_syscfg
BUILD_EXAMPLE_ALL += erad_ex6_stack_overflow_detect_syscfg
BUILD_EXAMPLE_ALL += erad_ex1_profile_interrupts
BUILD_EXAMPLE_ALL += erad_ex2_stack_overflow
BUILD_EXAMPLE_ALL += esm_ex1_tmuromparity_test
BUILD_EXAMPLE_ALL += esm_ex2_safetyaggregator
BUILD_EXAMPLE_ALL += flash_based_UART_SBL_with_FOTA
BUILD_EXAMPLE_ALL += F29H85x_EEPROM
BUILD_EXAMPLE_ALL += F29H85x_EEPROM_PingPong
BUILD_EXAMPLE_ALL += flash_bankmode_fota
BUILD_EXAMPLE_ALL += flash_mode0_128_program
BUILD_EXAMPLE_ALL += flash_mode0_512_program
BUILD_EXAMPLE_ALL += flash_mode1_128_program
BUILD_EXAMPLE_ALL += flash_mode1_512_program
BUILD_EXAMPLE_ALL += uart_flash_kernel
BUILD_EXAMPLE_ALL += fsi_academy_lab
BUILD_EXAMPLE_ALL += fsi_ex1_loopback_cpucontrol
BUILD_EXAMPLE_ALL += fsi_ex2_periodic_frame
BUILD_EXAMPLE_ALL += gpio_ex1_toggle
BUILD_EXAMPLE_ALL += gpio_ex2_interrupt
BUILD_EXAMPLE_ALL += hrcap_ex1_capture
BUILD_EXAMPLE_ALL += hrpwm_ex1_duty_sfo
BUILD_EXAMPLE_ALL += hrpwm_ex3_prd_updown_sfo
BUILD_EXAMPLE_ALL += hrpwm_ex8_xcmp_multiple_edges
BUILD_EXAMPLE_ALL += i2c_ex1_loopback
BUILD_EXAMPLE_ALL += i2c_ex2_eeprom
BUILD_EXAMPLE_ALL += i2c_ex3_external_loopback
BUILD_EXAMPLE_ALL += i2c_ex7_clock_stretching_controller_tx
BUILD_EXAMPLE_ALL += i2c_ex7_clock_stretching_target_rx
BUILD_EXAMPLE_ALL += interrupt_ex1_int_rtint_latency
BUILD_EXAMPLE_ALL += interrupt_ex2_int_rtint_nesting
BUILD_EXAMPLE_ALL += launchxl_ex1_led_blinky
BUILD_EXAMPLE_ALL += led_ex1_blinky
BUILD_EXAMPLE_ALL += lin_ex1_loopback_interrupts
BUILD_EXAMPLE_ALL += lin_ex2_sci_loopback
BUILD_EXAMPLE_ALL += lin_ex3_sci_dma
BUILD_EXAMPLE_ALL += lin_ex4_loopback_polling
BUILD_EXAMPLE_ALL += lin_ex5_sci_dma_single_buffer
BUILD_EXAMPLE_ALL += lpm_ex1_idlewake_gpio
BUILD_EXAMPLE_ALL += lpm_ex2_idlewake_watchdog
BUILD_EXAMPLE_ALL += lpm_ex3_standbywake_gpio
BUILD_EXAMPLE_ALL += lpm_ex4_standbywake_watchdog
BUILD_EXAMPLE_ALL += mcan_ex1_loopback_interrupts
BUILD_EXAMPLE_ALL += mcan_ex2_loopback_polling
BUILD_EXAMPLE_ALL += mcan_ex3_loopback_interrupts_fifo
BUILD_EXAMPLE_ALL += mcan_ex4_transmit
BUILD_EXAMPLE_ALL += mcan_ex5_receive
BUILD_EXAMPLE_ALL += mcan_ex6_transmit_syscfg
BUILD_EXAMPLE_ALL += rtdma_academy_lab
BUILD_EXAMPLE_ALL += rtdma_ex1_mem_transfer
BUILD_EXAMPLE_ALL += rtdma_ex2_mem_transfer_mpu
BUILD_EXAMPLE_ALL += sdfm_ex1_filter_sync_cpuread
BUILD_EXAMPLE_ALL += sdfm_ex4_pwm_sync_cpuread
BUILD_EXAMPLE_ALL += sent_ex1_single_sensor
BUILD_EXAMPLE_ALL += spi_ex1_loopback
BUILD_EXAMPLE_ALL += spi_ex2_loopback_fifo_interrupts
BUILD_EXAMPLE_ALL += spi_ex3_external_loopback
BUILD_EXAMPLE_ALL += spi_ex4_external_loopback_fifo_interrupts
BUILD_EXAMPLE_ALL += spi_ex5_loopback_dma
BUILD_EXAMPLE_ALL += sysctl_ex1_missing_clock_detection
BUILD_EXAMPLE_ALL += sysctl_ex2_xclkout
BUILD_EXAMPLE_ALL += system_integration_lab
BUILD_EXAMPLE_ALL += timer_academy_lab
BUILD_EXAMPLE_ALL += timer_ex1_cputimers
BUILD_EXAMPLE_ALL += timer_ex2_cputimers_syscfg
BUILD_EXAMPLE_ALL += uart_academy_lab
BUILD_EXAMPLE_ALL += uart_ex1_loopback
BUILD_EXAMPLE_ALL += uart_ex2_loopback_fifo_interrupts
BUILD_EXAMPLE_ALL += uart_ex3_loopback_dma
BUILD_EXAMPLE_ALL += uart_ex4_echoback
BUILD_EXAMPLE_ALL += wadi_ex1_duty_freq_capture
BUILD_EXAMPLE_ALL += watchdog_ex1_service
BUILD_EXAMPLE_ALL += xbar_ex1_input_output
BUILD_EXAMPLE_ALL += xbar_ex2_output_pulse_stretch
BUILD_EXAMPLE_ALL += dcl_df11
BUILD_EXAMPLE_ALL += dcl_df13
BUILD_EXAMPLE_ALL += dcl_df22
BUILD_EXAMPLE_ALL += dcl_df23
BUILD_EXAMPLE_ALL += dcl_gsm
BUILD_EXAMPLE_ALL += dcl_nlpid
BUILD_EXAMPLE_ALL += dcl_pi
BUILD_EXAMPLE_ALL += dcl_pi2
BUILD_EXAMPLE_ALL += dcl_pid
BUILD_EXAMPLE_ALL += control+rtos_demo
BUILD_EXAMPLE_ALL += freertos_ex1_two_tasks_syscfg
BUILD_EXAMPLE_ALL += freertos_ex2_interrupt_semaphore_syscfg
BUILD_EXAMPLE_ALL += freertos_port_validation_tests

examples: $(BUILD_EXAMPLE_ALL)

adc_ex1_soc_software:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex1_soc_software/ccs -f makefile all

adc_ex2_soc_epwm:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex2_soc_epwm/ccs -f makefile all

adc_ex3_temp_sensor:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex3_temp_sensor/ccs -f makefile all

adc_ex4_software_sync:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex4_software_sync/ccs -f makefile all

adc_ex5_soc_continuous:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex5_soc_continuous/ccs -f makefile all

adc_ex6_continuous_dma:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex6_continuous_dma/ccs -f makefile all

adc_ex7_ppb_offset:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex7_ppb_offset/ccs -f makefile all

adc_ex8_ppb_limits:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex8_ppb_limits/ccs -f makefile all

adc_ex9_ppb_delay:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex9_ppb_delay/ccs -f makefile all

adc_ex10_multiple_soc_epwm:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex10_multiple_soc_epwm/ccs -f makefile all

adc_ex11_burst_mode_epwm:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex11_burst_mode_epwm/ccs -f makefile all

adc_ex12_burst_mode_oversampling:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex12_burst_mode_oversampling/ccs -f makefile all

adc_ex13_soc_oversampling:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex13_soc_oversampling/ccs -f makefile all

adc_ex14_ppb_pwm_trip:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex14_ppb_pwm_trip/ccs -f makefile all

adc_ex15_trigger_repeater_oversampling:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex15_trigger_repeater_oversampling/ccs -f makefile all

adc_ex16_trigger_repeater_undersampling:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex16_trigger_repeater_undersampling/ccs -f makefile all

adc_ex17_safety_checker:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex17_safety_checker/ccs -f makefile all

clb_academy_lab:
	$(MAKE) -C examples/driverlib/single_core/clb/clb_academy_lab/ccs -f makefile all

clb_ecap_academy_lab:
	$(MAKE) -C examples/driverlib/single_core/clb/clb_ecap_academy_lab/ccs -f makefile all

clb_ex1_combinatorial_logic:
	$(MAKE) -C examples/driverlib/single_core/clb/clb_ex1_combinatorial_logic/ccs -f makefile all

clb_ex2_gpio_input_filter:
	$(MAKE) -C examples/driverlib/single_core/clb/clb_ex2_gpio_input_filter/ccs -f makefile all

clb_ex3_auxiliary_pwm:
	$(MAKE) -C examples/driverlib/single_core/clb/clb_ex3_auxiliary_pwm/ccs -f makefile all

clb_ex4_pwm_protection:
	$(MAKE) -C examples/driverlib/single_core/clb/clb_ex4_pwm_protection/ccs -f makefile all

cmpss_ex1_asynch:
	$(MAKE) -C examples/driverlib/single_core/cmpss/cmpss_ex1_asynch/ccs -f makefile all

cmpss_ex2_digital_filter:
	$(MAKE) -C examples/driverlib/single_core/cmpss/cmpss_ex2_digital_filter/ccs -f makefile all

buffdac_ex1_enable:
	$(MAKE) -C examples/driverlib/single_core/dac/buffdac_ex1_enable/ccs -f makefile all

buffdac_ex2_random:
	$(MAKE) -C examples/driverlib/single_core/dac/buffdac_ex2_random/ccs -f makefile all

dcc_ex1_single_shot_verification:
	$(MAKE) -C examples/driverlib/single_core/dcc/dcc_ex1_single_shot_verification/ccs -f makefile all

dcc_ex2_single_shot_measurement:
	$(MAKE) -C examples/driverlib/single_core/dcc/dcc_ex2_single_shot_measurement/ccs -f makefile all

dcc_ex3_continuous_monitoring_of_clock:
	$(MAKE) -C examples/driverlib/single_core/dcc/dcc_ex3_continuous_monitoring_of_clock/ccs -f makefile all

dlt_ex1_datalog_tag:
	$(MAKE) -C examples/driverlib/single_core/dlt/dlt_ex1_datalog_tag/ccs -f makefile all

dlt_ex2_dma_fsi_export:
	$(MAKE) -C examples/driverlib/single_core/dlt/dlt_ex2_dma_fsi_export/ccs -f makefile all

dlt_ex3_datalog_erad:
	$(MAKE) -C examples/driverlib/single_core/dlt/dlt_ex3_datalog_erad/ccs -f makefile all

ecap_academy_lab:
	$(MAKE) -C examples/driverlib/single_core/ecap/ecap_academy_lab/ccs -f makefile all

ecap_ex1_apwm:
	$(MAKE) -C examples/driverlib/single_core/ecap/ecap_ex1_apwm/ccs -f makefile all

ecap_ex2_capture_pwm:
	$(MAKE) -C examples/driverlib/single_core/ecap/ecap_ex2_capture_pwm/ccs -f makefile all

ecap_ex3_apwm_phase_shift:
	$(MAKE) -C examples/driverlib/single_core/ecap/ecap_ex3_apwm_phase_shift/ccs -f makefile all

emif_ex1_16bit_sdram_syscfg:
	$(MAKE) -C examples/driverlib/single_core/emif/emif_ex1_16bit_sdram_syscfg/ccs -f makefile all

emif_ex2_16bit_asram_syscfg:
	$(MAKE) -C examples/driverlib/single_core/emif/emif_ex2_16bit_asram_syscfg/ccs -f makefile all

emif_ex3_32bit_sdram_syscfg:
	$(MAKE) -C examples/driverlib/single_core/emif/emif_ex3_32bit_sdram_syscfg/ccs -f makefile all

empty_driverlib_project:
	$(MAKE) -C examples/driverlib/single_core/empty_projects/empty_driverlib_project/ccs -f makefile all

epg_ex1_generate_clocks:
	$(MAKE) -C examples/driverlib/single_core/epg/epg_ex1_generate_clocks/ccs -f makefile all

epg_ex2_generate_two_offset_clocks:
	$(MAKE) -C examples/driverlib/single_core/epg/epg_ex2_generate_two_offset_clocks/ccs -f makefile all

epg_ex3_generate_two_offset_clocks_with_siggen:
	$(MAKE) -C examples/driverlib/single_core/epg/epg_ex3_generate_two_offset_clocks_with_siggen/ccs -f makefile all

epg_ex4_generate_serial_data:
	$(MAKE) -C examples/driverlib/single_core/epg/epg_ex4_generate_serial_data/ccs -f makefile all

epg_ex5_generate_serial_data_shift_mode:
	$(MAKE) -C examples/driverlib/single_core/epg/epg_ex5_generate_serial_data_shift_mode/ccs -f makefile all

epwm_ex1_trip_zone:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex1_trip_zone/ccs -f makefile all

epwm_ex2_updown_aq:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex2_updown_aq/ccs -f makefile all

epwm_ex3_synchronization:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex3_synchronization/ccs -f makefile all

epwm_ex4_digital_compare:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex4_digital_compare/ccs -f makefile all

epwm_ex5_digital_compare_event_filter:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex5_digital_compare_event_filter/ccs -f makefile all

epwm_ex6_valley_switching:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex6_valley_switching/ccs -f makefile all

epwm_ex7_edge_filter:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex7_edge_filter/ccs -f makefile all

epwm_ex8_deadband:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex8_deadband/ccs -f makefile all

epwm_ex9_dma:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex9_dma/ccs -f makefile all

epwm_ex10_chopper:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex10_chopper/ccs -f makefile all

epwm_ex11_configure_signal:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex11_configure_signal/ccs -f makefile all

epwm_ex12_monoshot_mode:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex12_monoshot_mode/ccs -f makefile all

epwm_ex13_up_aq:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex13_up_aq/ccs -f makefile all

epwm_ex15_xcmp_multiple_edges:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex15_xcmp_multiple_edges/ccs -f makefile all

epwm_ex16_event_detection:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex16_event_detection/ccs -f makefile all

eqep_academy_lab:
	$(MAKE) -C examples/driverlib/single_core/eqep/eqep_academy_lab/ccs -f makefile all

eqep_ex2_freq_cal_interrupt:
	$(MAKE) -C examples/driverlib/single_core/eqep/eqep_ex2_freq_cal_interrupt/ccs -f makefile all

eqep_ex5_speed_dir_motor:
	$(MAKE) -C examples/driverlib/single_core/eqep/eqep_ex5_speed_dir_motor/ccs -f makefile all

erad_ex1_profile_function_no_syscfg:
	$(MAKE) -C examples/driverlib/single_core/erad/application_owned_examples/erad_ex1_profile_function_no_syscfg/ccs -f makefile all

erad_ex2_profile_function_syscfg:
	$(MAKE) -C examples/driverlib/single_core/erad/application_owned_examples/erad_ex2_profile_function_syscfg/ccs -f makefile all

erad_ex3_bus_monitor_no_syscfg:
	$(MAKE) -C examples/driverlib/single_core/erad/application_owned_examples/erad_ex3_bus_monitor_no_syscfg/ccs -f makefile all

erad_ex4_bus_monitor_syscfg:
	$(MAKE) -C examples/driverlib/single_core/erad/application_owned_examples/erad_ex4_bus_monitor_syscfg/ccs -f makefile all

erad_ex5_stack_overflow_detect_no_syscfg:
	$(MAKE) -C examples/driverlib/single_core/erad/application_owned_examples/erad_ex5_stack_overflow_detect_no_syscfg/ccs -f makefile all

erad_ex6_stack_overflow_detect_syscfg:
	$(MAKE) -C examples/driverlib/single_core/erad/application_owned_examples/erad_ex6_stack_overflow_detect_syscfg/ccs -f makefile all

erad_ex1_profile_interrupts:
	$(MAKE) -C examples/driverlib/single_core/erad/debugger_owned_examples/erad_ex1_profile_interrupts/ccs -f makefile all

erad_ex2_stack_overflow:
	$(MAKE) -C examples/driverlib/single_core/erad/debugger_owned_examples/erad_ex2_stack_overflow/ccs -f makefile all

esm_ex1_tmuromparity_test:
	$(MAKE) -C examples/driverlib/single_core/esm/esm_ex1_tmuromparity_test/ccs -f makefile all

esm_ex2_safetyaggregator:
	$(MAKE) -C examples/driverlib/single_core/esm/esm_ex2_safetyaggregator/ccs -f makefile all

flash_based_UART_SBL_with_FOTA:
	$(MAKE) -C examples/driverlib/single_core/flash/flash_based_UART_SBL_with_FOTA/ccs -f makefile all

F29H85x_EEPROM:
	$(MAKE) -C examples/driverlib/single_core/flash/F29H85x_EEPROM/ccs -f makefile all

F29H85x_EEPROM_PingPong:
	$(MAKE) -C examples/driverlib/single_core/flash/F29H85x_EEPROM_PingPong/ccs -f makefile all

flash_bankmode_fota:
	$(MAKE) -C examples/driverlib/single_core/flash/flash_bankmode_fota/ccs -f makefile all

flash_mode0_128_program:
	$(MAKE) -C examples/driverlib/single_core/flash/flash_mode0_128_program/ccs -f makefile all

flash_mode0_512_program:
	$(MAKE) -C examples/driverlib/single_core/flash/flash_mode0_512_program/ccs -f makefile all

flash_mode1_128_program:
	$(MAKE) -C examples/driverlib/single_core/flash/flash_mode1_128_program/ccs -f makefile all

flash_mode1_512_program:
	$(MAKE) -C examples/driverlib/single_core/flash/flash_mode1_512_program/ccs -f makefile all

uart_flash_kernel:
	$(MAKE) -C examples/driverlib/single_core/flash/uart_flash_kernel/ccs -f makefile all

fsi_academy_lab:
	$(MAKE) -C examples/driverlib/single_core/fsi/fsi_academy_lab/ccs -f makefile all

fsi_ex1_loopback_cpucontrol:
	$(MAKE) -C examples/driverlib/single_core/fsi/fsi_ex1_loopback_cpucontrol/ccs -f makefile all

fsi_ex2_periodic_frame:
	$(MAKE) -C examples/driverlib/single_core/fsi/fsi_ex2_periodic_frame/ccs -f makefile all

gpio_ex1_toggle:
	$(MAKE) -C examples/driverlib/single_core/gpio/gpio_ex1_toggle/ccs -f makefile all

gpio_ex2_interrupt:
	$(MAKE) -C examples/driverlib/single_core/gpio/gpio_ex2_interrupt/ccs -f makefile all

hrcap_ex1_capture:
	$(MAKE) -C examples/driverlib/single_core/hrcap/hrcap_ex1_capture/ccs -f makefile all

hrpwm_ex1_duty_sfo:
	$(MAKE) -C examples/driverlib/single_core/hrpwm/hrpwm_ex1_duty_sfo/ccs -f makefile all

hrpwm_ex3_prd_updown_sfo:
	$(MAKE) -C examples/driverlib/single_core/hrpwm/hrpwm_ex3_prd_updown_sfo/ccs -f makefile all

hrpwm_ex8_xcmp_multiple_edges:
	$(MAKE) -C examples/driverlib/single_core/hrpwm/hrpwm_ex8_xcmp_multiple_edges/ccs -f makefile all

i2c_ex1_loopback:
	$(MAKE) -C examples/driverlib/single_core/i2c/i2c_ex1_loopback/ccs -f makefile all

i2c_ex2_eeprom:
	$(MAKE) -C examples/driverlib/single_core/i2c/i2c_ex2_eeprom/ccs -f makefile all

i2c_ex3_external_loopback:
	$(MAKE) -C examples/driverlib/single_core/i2c/i2c_ex3_external_loopback/ccs -f makefile all

i2c_ex7_clock_stretching_controller_tx:
	$(MAKE) -C examples/driverlib/single_core/i2c/i2c_ex7_clock_stretching_controller_tx/ccs -f makefile all

i2c_ex7_clock_stretching_target_rx:
	$(MAKE) -C examples/driverlib/single_core/i2c/i2c_ex7_clock_stretching_target_rx/ccs -f makefile all

interrupt_ex1_int_rtint_latency:
	$(MAKE) -C examples/driverlib/single_core/interrupt/interrupt_ex1_int_rtint_latency/ccs -f makefile all

interrupt_ex2_int_rtint_nesting:
	$(MAKE) -C examples/driverlib/single_core/interrupt/interrupt_ex2_int_rtint_nesting/ccs -f makefile all

launchxl_ex1_led_blinky:
	$(MAKE) -C examples/driverlib/single_core/launchxl_f29h85x/launchxl_ex1_led_blinky/ccs -f makefile all BOARD=LAUNCHXL

led_ex1_blinky:
	$(MAKE) -C examples/driverlib/single_core/led/led_ex1_blinky/ccs -f makefile all

lin_ex1_loopback_interrupts:
	$(MAKE) -C examples/driverlib/single_core/lin/lin_ex1_loopback_interrupts/ccs -f makefile all

lin_ex2_sci_loopback:
	$(MAKE) -C examples/driverlib/single_core/lin/lin_ex2_sci_loopback/ccs -f makefile all

lin_ex3_sci_dma:
	$(MAKE) -C examples/driverlib/single_core/lin/lin_ex3_sci_dma/ccs -f makefile all

lin_ex4_loopback_polling:
	$(MAKE) -C examples/driverlib/single_core/lin/lin_ex4_loopback_polling/ccs -f makefile all

lin_ex5_sci_dma_single_buffer:
	$(MAKE) -C examples/driverlib/single_core/lin/lin_ex5_sci_dma_single_buffer/ccs -f makefile all

lpm_ex1_idlewake_gpio:
	$(MAKE) -C examples/driverlib/single_core/lpm/lpm_ex1_idlewake_gpio/ccs -f makefile all

lpm_ex2_idlewake_watchdog:
	$(MAKE) -C examples/driverlib/single_core/lpm/lpm_ex2_idlewake_watchdog/ccs -f makefile all

lpm_ex3_standbywake_gpio:
	$(MAKE) -C examples/driverlib/single_core/lpm/lpm_ex3_standbywake_gpio/ccs -f makefile all

lpm_ex4_standbywake_watchdog:
	$(MAKE) -C examples/driverlib/single_core/lpm/lpm_ex4_standbywake_watchdog/ccs -f makefile all

mcan_ex1_loopback_interrupts:
	$(MAKE) -C examples/driverlib/single_core/mcan/mcan_ex1_loopback_interrupts/ccs -f makefile all

mcan_ex2_loopback_polling:
	$(MAKE) -C examples/driverlib/single_core/mcan/mcan_ex2_loopback_polling/ccs -f makefile all

mcan_ex3_loopback_interrupts_fifo:
	$(MAKE) -C examples/driverlib/single_core/mcan/mcan_ex3_loopback_interrupts_fifo/ccs -f makefile all

mcan_ex4_transmit:
	$(MAKE) -C examples/driverlib/single_core/mcan/mcan_ex4_transmit/ccs -f makefile all

mcan_ex5_receive:
	$(MAKE) -C examples/driverlib/single_core/mcan/mcan_ex5_receive/ccs -f makefile all

mcan_ex6_transmit_syscfg:
	$(MAKE) -C examples/driverlib/single_core/mcan/mcan_ex6_transmit_syscfg/ccs -f makefile all

rtdma_academy_lab:
	$(MAKE) -C examples/driverlib/single_core/rtdma/rtdma_academy_lab/ccs -f makefile all

rtdma_ex1_mem_transfer:
	$(MAKE) -C examples/driverlib/single_core/rtdma/rtdma_ex1_mem_transfer/ccs -f makefile all

rtdma_ex2_mem_transfer_mpu:
	$(MAKE) -C examples/driverlib/single_core/rtdma/rtdma_ex2_mem_transfer_mpu/ccs -f makefile all

sdfm_ex1_filter_sync_cpuread:
	$(MAKE) -C examples/driverlib/single_core/sdfm/sdfm_ex1_filter_sync_cpuread/ccs -f makefile all

sdfm_ex4_pwm_sync_cpuread:
	$(MAKE) -C examples/driverlib/single_core/sdfm/sdfm_ex4_pwm_sync_cpuread/ccs -f makefile all

sent_ex1_single_sensor:
	$(MAKE) -C examples/driverlib/single_core/sent/sent_ex1_single_sensor/ccs -f makefile all

spi_ex1_loopback:
	$(MAKE) -C examples/driverlib/single_core/spi/spi_ex1_loopback/ccs -f makefile all

spi_ex2_loopback_fifo_interrupts:
	$(MAKE) -C examples/driverlib/single_core/spi/spi_ex2_loopback_fifo_interrupts/ccs -f makefile all

spi_ex3_external_loopback:
	$(MAKE) -C examples/driverlib/single_core/spi/spi_ex3_external_loopback/ccs -f makefile all

spi_ex4_external_loopback_fifo_interrupts:
	$(MAKE) -C examples/driverlib/single_core/spi/spi_ex4_external_loopback_fifo_interrupts/ccs -f makefile all

spi_ex5_loopback_dma:
	$(MAKE) -C examples/driverlib/single_core/spi/spi_ex5_loopback_dma/ccs -f makefile all

sysctl_ex1_missing_clock_detection:
	$(MAKE) -C examples/driverlib/single_core/sysctl/sysctl_ex1_missing_clock_detection/ccs -f makefile all

sysctl_ex2_xclkout:
	$(MAKE) -C examples/driverlib/single_core/sysctl/sysctl_ex2_xclkout/ccs -f makefile all

system_integration_lab:
	$(MAKE) -C examples/driverlib/single_core/system_integration/system_integration_lab/ccs -f makefile all

timer_academy_lab:
	$(MAKE) -C examples/driverlib/single_core/timer/timer_academy_lab/ccs -f makefile all

timer_ex1_cputimers:
	$(MAKE) -C examples/driverlib/single_core/timer/timer_ex1_cputimers/ccs -f makefile all

timer_ex2_cputimers_syscfg:
	$(MAKE) -C examples/driverlib/single_core/timer/timer_ex2_cputimers_syscfg/ccs -f makefile all

uart_academy_lab:
	$(MAKE) -C examples/driverlib/single_core/uart/uart_academy_lab/ccs -f makefile all

uart_ex1_loopback:
	$(MAKE) -C examples/driverlib/single_core/uart/uart_ex1_loopback/ccs -f makefile all

uart_ex2_loopback_fifo_interrupts:
	$(MAKE) -C examples/driverlib/single_core/uart/uart_ex2_loopback_fifo_interrupts/ccs -f makefile all

uart_ex3_loopback_dma:
	$(MAKE) -C examples/driverlib/single_core/uart/uart_ex3_loopback_dma/ccs -f makefile all

uart_ex4_echoback:
	$(MAKE) -C examples/driverlib/single_core/uart/uart_ex4_echoback/ccs -f makefile all

wadi_ex1_duty_freq_capture:
	$(MAKE) -C examples/driverlib/single_core/wadi/wadi_ex1_duty_freq_capture/ccs -f makefile all

watchdog_ex1_service:
	$(MAKE) -C examples/driverlib/single_core/watchdog/watchdog_ex1_service/ccs -f makefile all

xbar_ex1_input_output:
	$(MAKE) -C examples/driverlib/single_core/xbar/xbar_ex1_input_output/ccs -f makefile all

xbar_ex2_output_pulse_stretch:
	$(MAKE) -C examples/driverlib/single_core/xbar/xbar_ex2_output_pulse_stretch/ccs -f makefile all

dcl_df11:
	$(MAKE) -C examples/rtlibs/dcl/dcl_df11/ccs -f makefile all

dcl_df13:
	$(MAKE) -C examples/rtlibs/dcl/dcl_df13/ccs -f makefile all

dcl_df22:
	$(MAKE) -C examples/rtlibs/dcl/dcl_df22/ccs -f makefile all

dcl_df23:
	$(MAKE) -C examples/rtlibs/dcl/dcl_df23/ccs -f makefile all

dcl_gsm:
	$(MAKE) -C examples/rtlibs/dcl/dcl_gsm/ccs -f makefile all

dcl_nlpid:
	$(MAKE) -C examples/rtlibs/dcl/dcl_nlpid/ccs -f makefile all

dcl_pi:
	$(MAKE) -C examples/rtlibs/dcl/dcl_pi/ccs -f makefile all

dcl_pi2:
	$(MAKE) -C examples/rtlibs/dcl/dcl_pi2/ccs -f makefile all

dcl_pid:
	$(MAKE) -C examples/rtlibs/dcl/dcl_pid/ccs -f makefile all

control+rtos_demo:
	$(MAKE) -C examples/kernel/freertos/single_core/control+rtos_demo/ccs -f makefile all

freertos_ex1_two_tasks_syscfg:
	$(MAKE) -C examples/kernel/freertos/single_core/freertos_ex1_two_tasks_syscfg/ccs -f makefile all

freertos_ex2_interrupt_semaphore_syscfg:
	$(MAKE) -C examples/kernel/freertos/single_core/freertos_ex2_interrupt_semaphore_syscfg/ccs -f makefile all

freertos_port_validation_tests:
	$(MAKE) -C examples/kernel/freertos/single_core/freertos_port_validation_tests/ccs -f makefile all

BUILD_EXAMPLE_CLEAN_ALL =
BUILD_EXAMPLE_CLEAN_ALL += adc_ex1_soc_software_clean
BUILD_EXAMPLE_CLEAN_ALL += adc_ex2_soc_epwm_clean
BUILD_EXAMPLE_CLEAN_ALL += adc_ex3_temp_sensor_clean
BUILD_EXAMPLE_CLEAN_ALL += adc_ex4_software_sync_clean
BUILD_EXAMPLE_CLEAN_ALL += adc_ex5_soc_continuous_clean
BUILD_EXAMPLE_CLEAN_ALL += adc_ex6_continuous_dma_clean
BUILD_EXAMPLE_CLEAN_ALL += adc_ex7_ppb_offset_clean
BUILD_EXAMPLE_CLEAN_ALL += adc_ex8_ppb_limits_clean
BUILD_EXAMPLE_CLEAN_ALL += adc_ex9_ppb_delay_clean
BUILD_EXAMPLE_CLEAN_ALL += adc_ex10_multiple_soc_epwm_clean
BUILD_EXAMPLE_CLEAN_ALL += adc_ex11_burst_mode_epwm_clean
BUILD_EXAMPLE_CLEAN_ALL += adc_ex12_burst_mode_oversampling_clean
BUILD_EXAMPLE_CLEAN_ALL += adc_ex13_soc_oversampling_clean
BUILD_EXAMPLE_CLEAN_ALL += adc_ex14_ppb_pwm_trip_clean
BUILD_EXAMPLE_CLEAN_ALL += adc_ex15_trigger_repeater_oversampling_clean
BUILD_EXAMPLE_CLEAN_ALL += adc_ex16_trigger_repeater_undersampling_clean
BUILD_EXAMPLE_CLEAN_ALL += adc_ex17_safety_checker_clean
BUILD_EXAMPLE_CLEAN_ALL += clb_academy_lab_clean
BUILD_EXAMPLE_CLEAN_ALL += clb_ecap_academy_lab_clean
BUILD_EXAMPLE_CLEAN_ALL += clb_ex1_combinatorial_logic_clean
BUILD_EXAMPLE_CLEAN_ALL += clb_ex2_gpio_input_filter_clean
BUILD_EXAMPLE_CLEAN_ALL += clb_ex3_auxiliary_pwm_clean
BUILD_EXAMPLE_CLEAN_ALL += clb_ex4_pwm_protection_clean
BUILD_EXAMPLE_CLEAN_ALL += cmpss_ex1_asynch_clean
BUILD_EXAMPLE_CLEAN_ALL += cmpss_ex2_digital_filter_clean
BUILD_EXAMPLE_CLEAN_ALL += buffdac_ex1_enable_clean
BUILD_EXAMPLE_CLEAN_ALL += buffdac_ex2_random_clean
BUILD_EXAMPLE_CLEAN_ALL += dcc_ex1_single_shot_verification_clean
BUILD_EXAMPLE_CLEAN_ALL += dcc_ex2_single_shot_measurement_clean
BUILD_EXAMPLE_CLEAN_ALL += dcc_ex3_continuous_monitoring_of_clock_clean
BUILD_EXAMPLE_CLEAN_ALL += dlt_ex1_datalog_tag_clean
BUILD_EXAMPLE_CLEAN_ALL += dlt_ex2_dma_fsi_export_clean
BUILD_EXAMPLE_CLEAN_ALL += dlt_ex3_datalog_erad_clean
BUILD_EXAMPLE_CLEAN_ALL += ecap_academy_lab_clean
BUILD_EXAMPLE_CLEAN_ALL += ecap_ex1_apwm_clean
BUILD_EXAMPLE_CLEAN_ALL += ecap_ex2_capture_pwm_clean
BUILD_EXAMPLE_CLEAN_ALL += ecap_ex3_apwm_phase_shift_clean
BUILD_EXAMPLE_CLEAN_ALL += emif_ex1_16bit_sdram_syscfg_clean
BUILD_EXAMPLE_CLEAN_ALL += emif_ex2_16bit_asram_syscfg_clean
BUILD_EXAMPLE_CLEAN_ALL += emif_ex3_32bit_sdram_syscfg_clean
BUILD_EXAMPLE_CLEAN_ALL += empty_driverlib_project_clean
BUILD_EXAMPLE_CLEAN_ALL += epg_ex1_generate_clocks_clean
BUILD_EXAMPLE_CLEAN_ALL += epg_ex2_generate_two_offset_clocks_clean
BUILD_EXAMPLE_CLEAN_ALL += epg_ex3_generate_two_offset_clocks_with_siggen_clean
BUILD_EXAMPLE_CLEAN_ALL += epg_ex4_generate_serial_data_clean
BUILD_EXAMPLE_CLEAN_ALL += epg_ex5_generate_serial_data_shift_mode_clean
BUILD_EXAMPLE_CLEAN_ALL += epwm_ex1_trip_zone_clean
BUILD_EXAMPLE_CLEAN_ALL += epwm_ex2_updown_aq_clean
BUILD_EXAMPLE_CLEAN_ALL += epwm_ex3_synchronization_clean
BUILD_EXAMPLE_CLEAN_ALL += epwm_ex4_digital_compare_clean
BUILD_EXAMPLE_CLEAN_ALL += epwm_ex5_digital_compare_event_filter_clean
BUILD_EXAMPLE_CLEAN_ALL += epwm_ex6_valley_switching_clean
BUILD_EXAMPLE_CLEAN_ALL += epwm_ex7_edge_filter_clean
BUILD_EXAMPLE_CLEAN_ALL += epwm_ex8_deadband_clean
BUILD_EXAMPLE_CLEAN_ALL += epwm_ex9_dma_clean
BUILD_EXAMPLE_CLEAN_ALL += epwm_ex10_chopper_clean
BUILD_EXAMPLE_CLEAN_ALL += epwm_ex11_configure_signal_clean
BUILD_EXAMPLE_CLEAN_ALL += epwm_ex12_monoshot_mode_clean
BUILD_EXAMPLE_CLEAN_ALL += epwm_ex13_up_aq_clean
BUILD_EXAMPLE_CLEAN_ALL += epwm_ex15_xcmp_multiple_edges_clean
BUILD_EXAMPLE_CLEAN_ALL += epwm_ex16_event_detection_clean
BUILD_EXAMPLE_CLEAN_ALL += eqep_academy_lab_clean
BUILD_EXAMPLE_CLEAN_ALL += eqep_ex2_freq_cal_interrupt_clean
BUILD_EXAMPLE_CLEAN_ALL += eqep_ex5_speed_dir_motor_clean
BUILD_EXAMPLE_CLEAN_ALL += erad_ex1_profile_function_no_syscfg_clean
BUILD_EXAMPLE_CLEAN_ALL += erad_ex2_profile_function_syscfg_clean
BUILD_EXAMPLE_CLEAN_ALL += erad_ex3_bus_monitor_no_syscfg_clean
BUILD_EXAMPLE_CLEAN_ALL += erad_ex4_bus_monitor_syscfg_clean
BUILD_EXAMPLE_CLEAN_ALL += erad_ex5_stack_overflow_detect_no_syscfg_clean
BUILD_EXAMPLE_CLEAN_ALL += erad_ex6_stack_overflow_detect_syscfg_clean
BUILD_EXAMPLE_CLEAN_ALL += erad_ex1_profile_interrupts_clean
BUILD_EXAMPLE_CLEAN_ALL += erad_ex2_stack_overflow_clean
BUILD_EXAMPLE_CLEAN_ALL += esm_ex1_tmuromparity_test_clean
BUILD_EXAMPLE_CLEAN_ALL += esm_ex2_safetyaggregator_clean
BUILD_EXAMPLE_CLEAN_ALL += flash_based_UART_SBL_with_FOTA_clean
BUILD_EXAMPLE_CLEAN_ALL += F29H85x_EEPROM_clean
BUILD_EXAMPLE_CLEAN_ALL += F29H85x_EEPROM_PingPong_clean
BUILD_EXAMPLE_CLEAN_ALL += flash_bankmode_fota_clean
BUILD_EXAMPLE_CLEAN_ALL += flash_mode0_128_program_clean
BUILD_EXAMPLE_CLEAN_ALL += flash_mode0_512_program_clean
BUILD_EXAMPLE_CLEAN_ALL += flash_mode1_128_program_clean
BUILD_EXAMPLE_CLEAN_ALL += flash_mode1_512_program_clean
BUILD_EXAMPLE_CLEAN_ALL += uart_flash_kernel_clean
BUILD_EXAMPLE_CLEAN_ALL += fsi_academy_lab_clean
BUILD_EXAMPLE_CLEAN_ALL += fsi_ex1_loopback_cpucontrol_clean
BUILD_EXAMPLE_CLEAN_ALL += fsi_ex2_periodic_frame_clean
BUILD_EXAMPLE_CLEAN_ALL += gpio_ex1_toggle_clean
BUILD_EXAMPLE_CLEAN_ALL += gpio_ex2_interrupt_clean
BUILD_EXAMPLE_CLEAN_ALL += hrcap_ex1_capture_clean
BUILD_EXAMPLE_CLEAN_ALL += hrpwm_ex1_duty_sfo_clean
BUILD_EXAMPLE_CLEAN_ALL += hrpwm_ex3_prd_updown_sfo_clean
BUILD_EXAMPLE_CLEAN_ALL += hrpwm_ex8_xcmp_multiple_edges_clean
BUILD_EXAMPLE_CLEAN_ALL += i2c_ex1_loopback_clean
BUILD_EXAMPLE_CLEAN_ALL += i2c_ex2_eeprom_clean
BUILD_EXAMPLE_CLEAN_ALL += i2c_ex3_external_loopback_clean
BUILD_EXAMPLE_CLEAN_ALL += i2c_ex7_clock_stretching_controller_tx_clean
BUILD_EXAMPLE_CLEAN_ALL += i2c_ex7_clock_stretching_target_rx_clean
BUILD_EXAMPLE_CLEAN_ALL += interrupt_ex1_int_rtint_latency_clean
BUILD_EXAMPLE_CLEAN_ALL += interrupt_ex2_int_rtint_nesting_clean
BUILD_EXAMPLE_CLEAN_ALL += launchxl_ex1_led_blinky_clean
BUILD_EXAMPLE_CLEAN_ALL += led_ex1_blinky_clean
BUILD_EXAMPLE_CLEAN_ALL += lin_ex1_loopback_interrupts_clean
BUILD_EXAMPLE_CLEAN_ALL += lin_ex2_sci_loopback_clean
BUILD_EXAMPLE_CLEAN_ALL += lin_ex3_sci_dma_clean
BUILD_EXAMPLE_CLEAN_ALL += lin_ex4_loopback_polling_clean
BUILD_EXAMPLE_CLEAN_ALL += lin_ex5_sci_dma_single_buffer_clean
BUILD_EXAMPLE_CLEAN_ALL += lpm_ex1_idlewake_gpio_clean
BUILD_EXAMPLE_CLEAN_ALL += lpm_ex2_idlewake_watchdog_clean
BUILD_EXAMPLE_CLEAN_ALL += lpm_ex3_standbywake_gpio_clean
BUILD_EXAMPLE_CLEAN_ALL += lpm_ex4_standbywake_watchdog_clean
BUILD_EXAMPLE_CLEAN_ALL += mcan_ex1_loopback_interrupts_clean
BUILD_EXAMPLE_CLEAN_ALL += mcan_ex2_loopback_polling_clean
BUILD_EXAMPLE_CLEAN_ALL += mcan_ex3_loopback_interrupts_fifo_clean
BUILD_EXAMPLE_CLEAN_ALL += mcan_ex4_transmit_clean
BUILD_EXAMPLE_CLEAN_ALL += mcan_ex5_receive_clean
BUILD_EXAMPLE_CLEAN_ALL += mcan_ex6_transmit_syscfg_clean
BUILD_EXAMPLE_CLEAN_ALL += rtdma_academy_lab_clean
BUILD_EXAMPLE_CLEAN_ALL += rtdma_ex1_mem_transfer_clean
BUILD_EXAMPLE_CLEAN_ALL += rtdma_ex2_mem_transfer_mpu_clean
BUILD_EXAMPLE_CLEAN_ALL += sdfm_ex1_filter_sync_cpuread_clean
BUILD_EXAMPLE_CLEAN_ALL += sdfm_ex4_pwm_sync_cpuread_clean
BUILD_EXAMPLE_CLEAN_ALL += sent_ex1_single_sensor_clean
BUILD_EXAMPLE_CLEAN_ALL += spi_ex1_loopback_clean
BUILD_EXAMPLE_CLEAN_ALL += spi_ex2_loopback_fifo_interrupts_clean
BUILD_EXAMPLE_CLEAN_ALL += spi_ex3_external_loopback_clean
BUILD_EXAMPLE_CLEAN_ALL += spi_ex4_external_loopback_fifo_interrupts_clean
BUILD_EXAMPLE_CLEAN_ALL += spi_ex5_loopback_dma_clean
BUILD_EXAMPLE_CLEAN_ALL += sysctl_ex1_missing_clock_detection_clean
BUILD_EXAMPLE_CLEAN_ALL += sysctl_ex2_xclkout_clean
BUILD_EXAMPLE_CLEAN_ALL += system_integration_lab_clean
BUILD_EXAMPLE_CLEAN_ALL += timer_academy_lab_clean
BUILD_EXAMPLE_CLEAN_ALL += timer_ex1_cputimers_clean
BUILD_EXAMPLE_CLEAN_ALL += timer_ex2_cputimers_syscfg_clean
BUILD_EXAMPLE_CLEAN_ALL += uart_academy_lab_clean
BUILD_EXAMPLE_CLEAN_ALL += uart_ex1_loopback_clean
BUILD_EXAMPLE_CLEAN_ALL += uart_ex2_loopback_fifo_interrupts_clean
BUILD_EXAMPLE_CLEAN_ALL += uart_ex3_loopback_dma_clean
BUILD_EXAMPLE_CLEAN_ALL += uart_ex4_echoback_clean
BUILD_EXAMPLE_CLEAN_ALL += wadi_ex1_duty_freq_capture_clean
BUILD_EXAMPLE_CLEAN_ALL += watchdog_ex1_service_clean
BUILD_EXAMPLE_CLEAN_ALL += xbar_ex1_input_output_clean
BUILD_EXAMPLE_CLEAN_ALL += xbar_ex2_output_pulse_stretch_clean
BUILD_EXAMPLE_CLEAN_ALL += dcl_df11_clean
BUILD_EXAMPLE_CLEAN_ALL += dcl_df13_clean
BUILD_EXAMPLE_CLEAN_ALL += dcl_df22_clean
BUILD_EXAMPLE_CLEAN_ALL += dcl_df23_clean
BUILD_EXAMPLE_CLEAN_ALL += dcl_gsm_clean
BUILD_EXAMPLE_CLEAN_ALL += dcl_nlpid_clean
BUILD_EXAMPLE_CLEAN_ALL += dcl_pi_clean
BUILD_EXAMPLE_CLEAN_ALL += dcl_pi2_clean
BUILD_EXAMPLE_CLEAN_ALL += dcl_pid_clean
BUILD_EXAMPLE_CLEAN_ALL += control+rtos_demo_clean
BUILD_EXAMPLE_CLEAN_ALL += freertos_ex1_two_tasks_syscfg_clean
BUILD_EXAMPLE_CLEAN_ALL += freertos_ex2_interrupt_semaphore_syscfg_clean
BUILD_EXAMPLE_CLEAN_ALL += freertos_port_validation_tests_clean

examples-clean: $(BUILD_EXAMPLE_CLEAN_ALL)

adc_ex1_soc_software_clean:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex1_soc_software/ccs -f makefile clean

adc_ex2_soc_epwm_clean:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex2_soc_epwm/ccs -f makefile clean

adc_ex3_temp_sensor_clean:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex3_temp_sensor/ccs -f makefile clean

adc_ex4_software_sync_clean:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex4_software_sync/ccs -f makefile clean

adc_ex5_soc_continuous_clean:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex5_soc_continuous/ccs -f makefile clean

adc_ex6_continuous_dma_clean:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex6_continuous_dma/ccs -f makefile clean

adc_ex7_ppb_offset_clean:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex7_ppb_offset/ccs -f makefile clean

adc_ex8_ppb_limits_clean:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex8_ppb_limits/ccs -f makefile clean

adc_ex9_ppb_delay_clean:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex9_ppb_delay/ccs -f makefile clean

adc_ex10_multiple_soc_epwm_clean:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex10_multiple_soc_epwm/ccs -f makefile clean

adc_ex11_burst_mode_epwm_clean:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex11_burst_mode_epwm/ccs -f makefile clean

adc_ex12_burst_mode_oversampling_clean:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex12_burst_mode_oversampling/ccs -f makefile clean

adc_ex13_soc_oversampling_clean:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex13_soc_oversampling/ccs -f makefile clean

adc_ex14_ppb_pwm_trip_clean:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex14_ppb_pwm_trip/ccs -f makefile clean

adc_ex15_trigger_repeater_oversampling_clean:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex15_trigger_repeater_oversampling/ccs -f makefile clean

adc_ex16_trigger_repeater_undersampling_clean:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex16_trigger_repeater_undersampling/ccs -f makefile clean

adc_ex17_safety_checker_clean:
	$(MAKE) -C examples/driverlib/single_core/adc/adc_ex17_safety_checker/ccs -f makefile clean

clb_academy_lab_clean:
	$(MAKE) -C examples/driverlib/single_core/clb/clb_academy_lab/ccs -f makefile clean

clb_ecap_academy_lab_clean:
	$(MAKE) -C examples/driverlib/single_core/clb/clb_ecap_academy_lab/ccs -f makefile clean

clb_ex1_combinatorial_logic_clean:
	$(MAKE) -C examples/driverlib/single_core/clb/clb_ex1_combinatorial_logic/ccs -f makefile clean

clb_ex2_gpio_input_filter_clean:
	$(MAKE) -C examples/driverlib/single_core/clb/clb_ex2_gpio_input_filter/ccs -f makefile clean

clb_ex3_auxiliary_pwm_clean:
	$(MAKE) -C examples/driverlib/single_core/clb/clb_ex3_auxiliary_pwm/ccs -f makefile clean

clb_ex4_pwm_protection_clean:
	$(MAKE) -C examples/driverlib/single_core/clb/clb_ex4_pwm_protection/ccs -f makefile clean

cmpss_ex1_asynch_clean:
	$(MAKE) -C examples/driverlib/single_core/cmpss/cmpss_ex1_asynch/ccs -f makefile clean

cmpss_ex2_digital_filter_clean:
	$(MAKE) -C examples/driverlib/single_core/cmpss/cmpss_ex2_digital_filter/ccs -f makefile clean

buffdac_ex1_enable_clean:
	$(MAKE) -C examples/driverlib/single_core/dac/buffdac_ex1_enable/ccs -f makefile clean

buffdac_ex2_random_clean:
	$(MAKE) -C examples/driverlib/single_core/dac/buffdac_ex2_random/ccs -f makefile clean

dcc_ex1_single_shot_verification_clean:
	$(MAKE) -C examples/driverlib/single_core/dcc/dcc_ex1_single_shot_verification/ccs -f makefile clean

dcc_ex2_single_shot_measurement_clean:
	$(MAKE) -C examples/driverlib/single_core/dcc/dcc_ex2_single_shot_measurement/ccs -f makefile clean

dcc_ex3_continuous_monitoring_of_clock_clean:
	$(MAKE) -C examples/driverlib/single_core/dcc/dcc_ex3_continuous_monitoring_of_clock/ccs -f makefile clean

dlt_ex1_datalog_tag_clean:
	$(MAKE) -C examples/driverlib/single_core/dlt/dlt_ex1_datalog_tag/ccs -f makefile clean

dlt_ex2_dma_fsi_export_clean:
	$(MAKE) -C examples/driverlib/single_core/dlt/dlt_ex2_dma_fsi_export/ccs -f makefile clean

dlt_ex3_datalog_erad_clean:
	$(MAKE) -C examples/driverlib/single_core/dlt/dlt_ex3_datalog_erad/ccs -f makefile clean

ecap_academy_lab_clean:
	$(MAKE) -C examples/driverlib/single_core/ecap/ecap_academy_lab/ccs -f makefile clean

ecap_ex1_apwm_clean:
	$(MAKE) -C examples/driverlib/single_core/ecap/ecap_ex1_apwm/ccs -f makefile clean

ecap_ex2_capture_pwm_clean:
	$(MAKE) -C examples/driverlib/single_core/ecap/ecap_ex2_capture_pwm/ccs -f makefile clean

ecap_ex3_apwm_phase_shift_clean:
	$(MAKE) -C examples/driverlib/single_core/ecap/ecap_ex3_apwm_phase_shift/ccs -f makefile clean

emif_ex1_16bit_sdram_syscfg_clean:
	$(MAKE) -C examples/driverlib/single_core/emif/emif_ex1_16bit_sdram_syscfg/ccs -f makefile clean

emif_ex2_16bit_asram_syscfg_clean:
	$(MAKE) -C examples/driverlib/single_core/emif/emif_ex2_16bit_asram_syscfg/ccs -f makefile clean

emif_ex3_32bit_sdram_syscfg_clean:
	$(MAKE) -C examples/driverlib/single_core/emif/emif_ex3_32bit_sdram_syscfg/ccs -f makefile clean

empty_driverlib_project_clean:
	$(MAKE) -C examples/driverlib/single_core/empty_projects/empty_driverlib_project/ccs -f makefile clean

epg_ex1_generate_clocks_clean:
	$(MAKE) -C examples/driverlib/single_core/epg/epg_ex1_generate_clocks/ccs -f makefile clean

epg_ex2_generate_two_offset_clocks_clean:
	$(MAKE) -C examples/driverlib/single_core/epg/epg_ex2_generate_two_offset_clocks/ccs -f makefile clean

epg_ex3_generate_two_offset_clocks_with_siggen_clean:
	$(MAKE) -C examples/driverlib/single_core/epg/epg_ex3_generate_two_offset_clocks_with_siggen/ccs -f makefile clean

epg_ex4_generate_serial_data_clean:
	$(MAKE) -C examples/driverlib/single_core/epg/epg_ex4_generate_serial_data/ccs -f makefile clean

epg_ex5_generate_serial_data_shift_mode_clean:
	$(MAKE) -C examples/driverlib/single_core/epg/epg_ex5_generate_serial_data_shift_mode/ccs -f makefile clean

epwm_ex1_trip_zone_clean:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex1_trip_zone/ccs -f makefile clean

epwm_ex2_updown_aq_clean:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex2_updown_aq/ccs -f makefile clean

epwm_ex3_synchronization_clean:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex3_synchronization/ccs -f makefile clean

epwm_ex4_digital_compare_clean:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex4_digital_compare/ccs -f makefile clean

epwm_ex5_digital_compare_event_filter_clean:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex5_digital_compare_event_filter/ccs -f makefile clean

epwm_ex6_valley_switching_clean:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex6_valley_switching/ccs -f makefile clean

epwm_ex7_edge_filter_clean:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex7_edge_filter/ccs -f makefile clean

epwm_ex8_deadband_clean:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex8_deadband/ccs -f makefile clean

epwm_ex9_dma_clean:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex9_dma/ccs -f makefile clean

epwm_ex10_chopper_clean:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex10_chopper/ccs -f makefile clean

epwm_ex11_configure_signal_clean:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex11_configure_signal/ccs -f makefile clean

epwm_ex12_monoshot_mode_clean:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex12_monoshot_mode/ccs -f makefile clean

epwm_ex13_up_aq_clean:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex13_up_aq/ccs -f makefile clean

epwm_ex15_xcmp_multiple_edges_clean:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex15_xcmp_multiple_edges/ccs -f makefile clean

epwm_ex16_event_detection_clean:
	$(MAKE) -C examples/driverlib/single_core/epwm/epwm_ex16_event_detection/ccs -f makefile clean

eqep_academy_lab_clean:
	$(MAKE) -C examples/driverlib/single_core/eqep/eqep_academy_lab/ccs -f makefile clean

eqep_ex2_freq_cal_interrupt_clean:
	$(MAKE) -C examples/driverlib/single_core/eqep/eqep_ex2_freq_cal_interrupt/ccs -f makefile clean

eqep_ex5_speed_dir_motor_clean:
	$(MAKE) -C examples/driverlib/single_core/eqep/eqep_ex5_speed_dir_motor/ccs -f makefile clean

erad_ex1_profile_function_no_syscfg_clean:
	$(MAKE) -C examples/driverlib/single_core/erad/application_owned_examples/erad_ex1_profile_function_no_syscfg/ccs -f makefile clean

erad_ex2_profile_function_syscfg_clean:
	$(MAKE) -C examples/driverlib/single_core/erad/application_owned_examples/erad_ex2_profile_function_syscfg/ccs -f makefile clean

erad_ex3_bus_monitor_no_syscfg_clean:
	$(MAKE) -C examples/driverlib/single_core/erad/application_owned_examples/erad_ex3_bus_monitor_no_syscfg/ccs -f makefile clean

erad_ex4_bus_monitor_syscfg_clean:
	$(MAKE) -C examples/driverlib/single_core/erad/application_owned_examples/erad_ex4_bus_monitor_syscfg/ccs -f makefile clean

erad_ex5_stack_overflow_detect_no_syscfg_clean:
	$(MAKE) -C examples/driverlib/single_core/erad/application_owned_examples/erad_ex5_stack_overflow_detect_no_syscfg/ccs -f makefile clean

erad_ex6_stack_overflow_detect_syscfg_clean:
	$(MAKE) -C examples/driverlib/single_core/erad/application_owned_examples/erad_ex6_stack_overflow_detect_syscfg/ccs -f makefile clean

erad_ex1_profile_interrupts_clean:
	$(MAKE) -C examples/driverlib/single_core/erad/debugger_owned_examples/erad_ex1_profile_interrupts/ccs -f makefile clean

erad_ex2_stack_overflow_clean:
	$(MAKE) -C examples/driverlib/single_core/erad/debugger_owned_examples/erad_ex2_stack_overflow/ccs -f makefile clean

esm_ex1_tmuromparity_test_clean:
	$(MAKE) -C examples/driverlib/single_core/esm/esm_ex1_tmuromparity_test/ccs -f makefile clean

esm_ex2_safetyaggregator_clean:
	$(MAKE) -C examples/driverlib/single_core/esm/esm_ex2_safetyaggregator/ccs -f makefile clean

flash_based_UART_SBL_with_FOTA_clean:
	$(MAKE) -C examples/driverlib/single_core/flash/flash_based_UART_SBL_with_FOTA/ccs -f makefile clean

F29H85x_EEPROM_clean:
	$(MAKE) -C examples/driverlib/single_core/flash/F29H85x_EEPROM/ccs -f makefile clean

F29H85x_EEPROM_PingPong_clean:
	$(MAKE) -C examples/driverlib/single_core/flash/F29H85x_EEPROM_PingPong/ccs -f makefile clean

flash_bankmode_fota_clean:
	$(MAKE) -C examples/driverlib/single_core/flash/flash_bankmode_fota/ccs -f makefile clean

flash_mode0_128_program_clean:
	$(MAKE) -C examples/driverlib/single_core/flash/flash_mode0_128_program/ccs -f makefile clean

flash_mode0_512_program_clean:
	$(MAKE) -C examples/driverlib/single_core/flash/flash_mode0_512_program/ccs -f makefile clean

flash_mode1_128_program_clean:
	$(MAKE) -C examples/driverlib/single_core/flash/flash_mode1_128_program/ccs -f makefile clean

flash_mode1_512_program_clean:
	$(MAKE) -C examples/driverlib/single_core/flash/flash_mode1_512_program/ccs -f makefile clean

uart_flash_kernel_clean:
	$(MAKE) -C examples/driverlib/single_core/flash/uart_flash_kernel/ccs -f makefile clean

fsi_academy_lab_clean:
	$(MAKE) -C examples/driverlib/single_core/fsi/fsi_academy_lab/ccs -f makefile clean

fsi_ex1_loopback_cpucontrol_clean:
	$(MAKE) -C examples/driverlib/single_core/fsi/fsi_ex1_loopback_cpucontrol/ccs -f makefile clean

fsi_ex2_periodic_frame_clean:
	$(MAKE) -C examples/driverlib/single_core/fsi/fsi_ex2_periodic_frame/ccs -f makefile clean

gpio_ex1_toggle_clean:
	$(MAKE) -C examples/driverlib/single_core/gpio/gpio_ex1_toggle/ccs -f makefile clean

gpio_ex2_interrupt_clean:
	$(MAKE) -C examples/driverlib/single_core/gpio/gpio_ex2_interrupt/ccs -f makefile clean

hrcap_ex1_capture_clean:
	$(MAKE) -C examples/driverlib/single_core/hrcap/hrcap_ex1_capture/ccs -f makefile clean

hrpwm_ex1_duty_sfo_clean:
	$(MAKE) -C examples/driverlib/single_core/hrpwm/hrpwm_ex1_duty_sfo/ccs -f makefile clean

hrpwm_ex3_prd_updown_sfo_clean:
	$(MAKE) -C examples/driverlib/single_core/hrpwm/hrpwm_ex3_prd_updown_sfo/ccs -f makefile clean

hrpwm_ex8_xcmp_multiple_edges_clean:
	$(MAKE) -C examples/driverlib/single_core/hrpwm/hrpwm_ex8_xcmp_multiple_edges/ccs -f makefile clean

i2c_ex1_loopback_clean:
	$(MAKE) -C examples/driverlib/single_core/i2c/i2c_ex1_loopback/ccs -f makefile clean

i2c_ex2_eeprom_clean:
	$(MAKE) -C examples/driverlib/single_core/i2c/i2c_ex2_eeprom/ccs -f makefile clean

i2c_ex3_external_loopback_clean:
	$(MAKE) -C examples/driverlib/single_core/i2c/i2c_ex3_external_loopback/ccs -f makefile clean

i2c_ex7_clock_stretching_controller_tx_clean:
	$(MAKE) -C examples/driverlib/single_core/i2c/i2c_ex7_clock_stretching_controller_tx/ccs -f makefile clean

i2c_ex7_clock_stretching_target_rx_clean:
	$(MAKE) -C examples/driverlib/single_core/i2c/i2c_ex7_clock_stretching_target_rx/ccs -f makefile clean

interrupt_ex1_int_rtint_latency_clean:
	$(MAKE) -C examples/driverlib/single_core/interrupt/interrupt_ex1_int_rtint_latency/ccs -f makefile clean

interrupt_ex2_int_rtint_nesting_clean:
	$(MAKE) -C examples/driverlib/single_core/interrupt/interrupt_ex2_int_rtint_nesting/ccs -f makefile clean

launchxl_ex1_led_blinky_clean:
	$(MAKE) -C examples/driverlib/single_core/launchxl_f29h85x/launchxl_ex1_led_blinky/ccs -f makefile clean

led_ex1_blinky_clean:
	$(MAKE) -C examples/driverlib/single_core/led/led_ex1_blinky/ccs -f makefile clean

lin_ex1_loopback_interrupts_clean:
	$(MAKE) -C examples/driverlib/single_core/lin/lin_ex1_loopback_interrupts/ccs -f makefile clean

lin_ex2_sci_loopback_clean:
	$(MAKE) -C examples/driverlib/single_core/lin/lin_ex2_sci_loopback/ccs -f makefile clean

lin_ex3_sci_dma_clean:
	$(MAKE) -C examples/driverlib/single_core/lin/lin_ex3_sci_dma/ccs -f makefile clean

lin_ex4_loopback_polling_clean:
	$(MAKE) -C examples/driverlib/single_core/lin/lin_ex4_loopback_polling/ccs -f makefile clean

lin_ex5_sci_dma_single_buffer_clean:
	$(MAKE) -C examples/driverlib/single_core/lin/lin_ex5_sci_dma_single_buffer/ccs -f makefile clean

lpm_ex1_idlewake_gpio_clean:
	$(MAKE) -C examples/driverlib/single_core/lpm/lpm_ex1_idlewake_gpio/ccs -f makefile clean

lpm_ex2_idlewake_watchdog_clean:
	$(MAKE) -C examples/driverlib/single_core/lpm/lpm_ex2_idlewake_watchdog/ccs -f makefile clean

lpm_ex3_standbywake_gpio_clean:
	$(MAKE) -C examples/driverlib/single_core/lpm/lpm_ex3_standbywake_gpio/ccs -f makefile clean

lpm_ex4_standbywake_watchdog_clean:
	$(MAKE) -C examples/driverlib/single_core/lpm/lpm_ex4_standbywake_watchdog/ccs -f makefile clean

mcan_ex1_loopback_interrupts_clean:
	$(MAKE) -C examples/driverlib/single_core/mcan/mcan_ex1_loopback_interrupts/ccs -f makefile clean

mcan_ex2_loopback_polling_clean:
	$(MAKE) -C examples/driverlib/single_core/mcan/mcan_ex2_loopback_polling/ccs -f makefile clean

mcan_ex3_loopback_interrupts_fifo_clean:
	$(MAKE) -C examples/driverlib/single_core/mcan/mcan_ex3_loopback_interrupts_fifo/ccs -f makefile clean

mcan_ex4_transmit_clean:
	$(MAKE) -C examples/driverlib/single_core/mcan/mcan_ex4_transmit/ccs -f makefile clean

mcan_ex5_receive_clean:
	$(MAKE) -C examples/driverlib/single_core/mcan/mcan_ex5_receive/ccs -f makefile clean

mcan_ex6_transmit_syscfg_clean:
	$(MAKE) -C examples/driverlib/single_core/mcan/mcan_ex6_transmit_syscfg/ccs -f makefile clean

rtdma_academy_lab_clean:
	$(MAKE) -C examples/driverlib/single_core/rtdma/rtdma_academy_lab/ccs -f makefile clean

rtdma_ex1_mem_transfer_clean:
	$(MAKE) -C examples/driverlib/single_core/rtdma/rtdma_ex1_mem_transfer/ccs -f makefile clean

rtdma_ex2_mem_transfer_mpu_clean:
	$(MAKE) -C examples/driverlib/single_core/rtdma/rtdma_ex2_mem_transfer_mpu/ccs -f makefile clean

sdfm_ex1_filter_sync_cpuread_clean:
	$(MAKE) -C examples/driverlib/single_core/sdfm/sdfm_ex1_filter_sync_cpuread/ccs -f makefile clean

sdfm_ex4_pwm_sync_cpuread_clean:
	$(MAKE) -C examples/driverlib/single_core/sdfm/sdfm_ex4_pwm_sync_cpuread/ccs -f makefile clean

sent_ex1_single_sensor_clean:
	$(MAKE) -C examples/driverlib/single_core/sent/sent_ex1_single_sensor/ccs -f makefile clean

spi_ex1_loopback_clean:
	$(MAKE) -C examples/driverlib/single_core/spi/spi_ex1_loopback/ccs -f makefile clean

spi_ex2_loopback_fifo_interrupts_clean:
	$(MAKE) -C examples/driverlib/single_core/spi/spi_ex2_loopback_fifo_interrupts/ccs -f makefile clean

spi_ex3_external_loopback_clean:
	$(MAKE) -C examples/driverlib/single_core/spi/spi_ex3_external_loopback/ccs -f makefile clean

spi_ex4_external_loopback_fifo_interrupts_clean:
	$(MAKE) -C examples/driverlib/single_core/spi/spi_ex4_external_loopback_fifo_interrupts/ccs -f makefile clean

spi_ex5_loopback_dma_clean:
	$(MAKE) -C examples/driverlib/single_core/spi/spi_ex5_loopback_dma/ccs -f makefile clean

sysctl_ex1_missing_clock_detection_clean:
	$(MAKE) -C examples/driverlib/single_core/sysctl/sysctl_ex1_missing_clock_detection/ccs -f makefile clean

sysctl_ex2_xclkout_clean:
	$(MAKE) -C examples/driverlib/single_core/sysctl/sysctl_ex2_xclkout/ccs -f makefile clean

system_integration_lab_clean:
	$(MAKE) -C examples/driverlib/single_core/system_integration/system_integration_lab/ccs -f makefile clean

timer_academy_lab_clean:
	$(MAKE) -C examples/driverlib/single_core/timer/timer_academy_lab/ccs -f makefile clean

timer_ex1_cputimers_clean:
	$(MAKE) -C examples/driverlib/single_core/timer/timer_ex1_cputimers/ccs -f makefile clean

timer_ex2_cputimers_syscfg_clean:
	$(MAKE) -C examples/driverlib/single_core/timer/timer_ex2_cputimers_syscfg/ccs -f makefile clean

uart_academy_lab_clean:
	$(MAKE) -C examples/driverlib/single_core/uart/uart_academy_lab/ccs -f makefile clean

uart_ex1_loopback_clean:
	$(MAKE) -C examples/driverlib/single_core/uart/uart_ex1_loopback/ccs -f makefile clean

uart_ex2_loopback_fifo_interrupts_clean:
	$(MAKE) -C examples/driverlib/single_core/uart/uart_ex2_loopback_fifo_interrupts/ccs -f makefile clean

uart_ex3_loopback_dma_clean:
	$(MAKE) -C examples/driverlib/single_core/uart/uart_ex3_loopback_dma/ccs -f makefile clean

uart_ex4_echoback_clean:
	$(MAKE) -C examples/driverlib/single_core/uart/uart_ex4_echoback/ccs -f makefile clean

wadi_ex1_duty_freq_capture_clean:
	$(MAKE) -C examples/driverlib/single_core/wadi/wadi_ex1_duty_freq_capture/ccs -f makefile clean

watchdog_ex1_service_clean:
	$(MAKE) -C examples/driverlib/single_core/watchdog/watchdog_ex1_service/ccs -f makefile clean

xbar_ex1_input_output_clean:
	$(MAKE) -C examples/driverlib/single_core/xbar/xbar_ex1_input_output/ccs -f makefile clean

xbar_ex2_output_pulse_stretch_clean:
	$(MAKE) -C examples/driverlib/single_core/xbar/xbar_ex2_output_pulse_stretch/ccs -f makefile clean

dcl_df11_clean:
	$(MAKE) -C examples/rtlibs/dcl/dcl_df11/ccs -f makefile clean

dcl_df13_clean:
	$(MAKE) -C examples/rtlibs/dcl/dcl_df13/ccs -f makefile clean

dcl_df22_clean:
	$(MAKE) -C examples/rtlibs/dcl/dcl_df22/ccs -f makefile clean

dcl_df23_clean:
	$(MAKE) -C examples/rtlibs/dcl/dcl_df23/ccs -f makefile clean

dcl_gsm_clean:
	$(MAKE) -C examples/rtlibs/dcl/dcl_gsm/ccs -f makefile clean

dcl_nlpid_clean:
	$(MAKE) -C examples/rtlibs/dcl/dcl_nlpid/ccs -f makefile clean

dcl_pi_clean:
	$(MAKE) -C examples/rtlibs/dcl/dcl_pi/ccs -f makefile clean

dcl_pi2_clean:
	$(MAKE) -C examples/rtlibs/dcl/dcl_pi2/ccs -f makefile clean

dcl_pid_clean:
	$(MAKE) -C examples/rtlibs/dcl/dcl_pid/ccs -f makefile clean

control+rtos_demo_clean:
	$(MAKE) -C examples/kernel/freertos/single_core/control+rtos_demo/ccs -f makefile clean

freertos_ex1_two_tasks_syscfg_clean:
	$(MAKE) -C examples/kernel/freertos/single_core/freertos_ex1_two_tasks_syscfg/ccs -f makefile clean

freertos_ex2_interrupt_semaphore_syscfg_clean:
	$(MAKE) -C examples/kernel/freertos/single_core/freertos_ex2_interrupt_semaphore_syscfg/ccs -f makefile clean

freertos_port_validation_tests_clean:
	$(MAKE) -C examples/kernel/freertos/single_core/freertos_port_validation_tests/ccs -f makefile clean
