//#############################################################################
//
// FILE:   aci_main.c
//
//
//#############################################################################

//
// Included Files
//
#include "inc/hw_types.h"
#include "stdio.h"
#include "cpu.h"
#include "aci_main.h"
#include "board.h"
#include "math.h"

#define SIGNAL_CHAIN 1      //Comment out this line to execute internal model
#define PROFILE_MODULES     //Comment out this line to get total cycle count

//*****************************************************************************
// globals
//*****************************************************************************
// The global pass, fail values
int16_t pass = 0U, fail = 0U;
// The absolute error between the result and expected values
float32_t tolerance = 1.0e-4;

//
// Set simulation parameters
//

//
// Initialize ACI model system simulation defaults
//
ACI_Const aci1Const = ACI_CONST_DEFAULTS;
ACIFE_Const fe1Const = ACIFE_CONST_DEFAULTS;
ACISE_Const se1Const = ACISE_CONST_DEFAULTS;

//
// PU (per unit radians) = (angle in radians) / (2*pi)
//
_iq idRef      = _IQ(0.4F);              // Id reference (pu)
_iq speedRef   = _IQ(0.5F);          // Speed reference (pu)
_iq T           = _IQ(SAMPLING_PERIOD); // Samping period (sec)

ACI aci1 = ACI_DEFAULTS;
ACIFE fe1 = ACIFE_DEFAULTS;
ACISE se1 = ACISE_DEFAULTS;

PARK park1 = PARK_DEFAULTS;
IPARK ipark1 = IPARK_DEFAULTS;

PIDREG3 pid1Id = PIDREG3_DEFAULTS;

PIDREG3 pid1Iq = PIDREG3_DEFAULTS;
PIDREG3 pid1Spd = PIDREG3_DEFAULTS;

CLARKE clarke1 = CLARKE_DEFAULTS;
ICLARKE iclarke1 = ICLARKE_DEFAULTS;

SVGEN svgen1 = SVGEN_DEFAULTS;

// 
// Data logging buffers for two channels (or graphs):
//
_iq	DLogCh1[DLOG_NUMBER_SAMPLES];
_iq	DLogCh2[DLOG_NUMBER_SAMPLES];
_iq Ia;
_iq Ib;

volatile int32_t ctrlLoopCount = 0;

//
// Global variables
//
//extern uint32_t PWM_HALF_MAX;
_iq speedEndOfTest = 0;

int32_t timer_count_rtint_entry, timer_overhead, timer_count_ADC_read, timer_count_clarke, timer_count_park, timer_count_3pid, timer_count_inv_park, timer_count_aci_mod, timer_count_inv_clarke, timer_count_flux_est, timer_count_speed_est, timer_count_svgen, timer_count_pwm_write, timer_count_full_signal_chain;
int32_t rtint_entry_count_buf[DLOG_NUMBER_SAMPLES], ADC_read_count_buf[DLOG_NUMBER_SAMPLES], clarke_count_buf[DLOG_NUMBER_SAMPLES], park_count_buf[DLOG_NUMBER_SAMPLES], pid3_count_buf[DLOG_NUMBER_SAMPLES], inv_park_count_buf[DLOG_NUMBER_SAMPLES], inv_clarke_count_buf[DLOG_NUMBER_SAMPLES], aci_mod_count_buf[DLOG_NUMBER_SAMPLES], flux_est_count_buf[DLOG_NUMBER_SAMPLES], speed_est_count_buf[DLOG_NUMBER_SAMPLES], svgen_count_buf[DLOG_NUMBER_SAMPLES], pwm_write_count_buf[DLOG_NUMBER_SAMPLES], full_signal_chain_count_buf[DLOG_NUMBER_SAMPLES];
float32_t temp_store_buf1[DLOG_NUMBER_SAMPLES], temp_store_buf2[DLOG_NUMBER_SAMPLES], temp_store_buf3[DLOG_NUMBER_SAMPLES], temp_store_buf4[DLOG_NUMBER_SAMPLES];
int32_t rtint_entry_count, ADC_read_count, clarke_count, park_count, pid3_count, inv_park_count, inv_clarke_count, aci_mod_count, flux_est_count, speed_est_count, svgen_count, pwm_write_count, full_signal_chain_count;
uint32_t part1_count_end, part2_count_start, part2_count_end, part3_count_start;


void avg_count_cal();

//void aci_ctrlLoop_ISR1(void);

//
// Main
//
int main(void)
{
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Board Initialization
    //
    Board_init();

    int i = 0;

    //
    // Print start of benchmarking test
    //
    printf("ACI Benchmark Test:\n");

    //
    // Initialize data logging buffers
    //
    for(i = 0; i < DLOG_NUMBER_SAMPLES; i++) 
    {
      DLogCh1[i] = 0;
      DLogCh2[i] = 0;
    }

    //
    // Initialize control loop execution count
    //
    ctrlLoopCount = 0;

    _iq Ia = 520;
    _iq Ib = 250;

    //
    // Initialize the ACI module
    //
    ACI_Const_calc(&aci1Const);

    aci1.K1 = _IQ(aci1Const.K1);
    aci1.K2 = _IQ(aci1Const.K2);
    aci1.K3 = _IQ(aci1Const.K3);
    aci1.K4 = _IQ(aci1Const.K4);
    aci1.K5 = _IQ(aci1Const.K5);
    aci1.K6 = _IQ(aci1Const.K6);
    aci1.K7 = _IQ(aci1Const.K7);
    aci1.K8 = _IQ(aci1Const.K8);
    aci1.K9 = _IQ(aci1Const.K9);
    aci1.K10 = _IQ(aci1Const.K10);
    aci1.base_rpm = 120*BASE_FREQ/P_VALUE;
    aci1.load_torque = _IQ(TL_VALUE/BASE_TORQUE);

    //
    // Initialize the ACI_FE module
    //
    ACIFE_Const_calc(&fe1Const);
 	
    fe1.K1_fe = _IQ(fe1Const.K1);
    fe1.K2_fe = _IQ(fe1Const.K2);
    fe1.K3_fe = _IQ(fe1Const.K3);
    fe1.K4_fe = _IQ(fe1Const.K4);
    fe1.K5_fe = _IQ(fe1Const.K5);
    fe1.K6_fe = _IQ(fe1Const.K6);
    fe1.K7_fe = _IQ(fe1Const.K7);
    fe1.K8_fe = _IQ(fe1Const.K8);
    fe1.Kp_fe = _IQ(0.055F);
    fe1.Ki_fe = _IQ(0.002F);
 
    //
    // Initialize the ACI_SE module
    //
    ACISE_Const_calc(&se1Const);
 	
    se1.K1_se = _IQ(se1Const.K1);
    se1.K2_se = _IQ(se1Const.K2);
    se1.K3_se = _IQ(se1Const.K3);
    se1.K4_se = _IQ(se1Const.K4);
    se1.base_rpm_se = 120*BASE_FREQ/P_VALUE;

    //
    // Initialize the PID_REG3 module for Id
    //
    pid1Id.Kp_reg3 = _IQ(0.0541F);
    pid1Id.Ki_reg3 = _IQ(0.5F);
    pid1Id.Kd_reg3 = _IQ(0.2F);
    pid1Id.Kc_reg3 = _IQ(0.1F);
    pid1Id.pid_out_max = _IQ(0.71F);
    pid1Id.pid_out_min = _IQ(-0.71F);
 
    //
    // Initialize the PID_REG3 module for Iq
    //
    pid1Iq.Kp_reg3 = _IQ(0.0541F);
    pid1Iq.Ki_reg3 = _IQ(0.5F);
    pid1Iq.Kd_reg3 = _IQ(0.2F);
    pid1Iq.Kc_reg3 = _IQ(0.1F);
    pid1Iq.pid_out_max = _IQ(0.71F);
    pid1Iq.pid_out_min = _IQ(-0.71F);

    //
    // Initialize the PID_REG3 module for speed
    //
    pid1Spd.Kp_reg3 = _IQ(7.2F);
    pid1Spd.Ki_reg3 = _IQ(0.05F);
    pid1Spd.Kd_reg3 = _IQ(0.2F);
    pid1Spd.Kc_reg3 = _IQ(0.9F);
    pid1Spd.pid_out_max = _IQ(1.0F);
    pid1Spd.pid_out_min = _IQ(-1.0F);

    // Timer overhead compute
    uint32_t tstart_gen0 = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    timer_overhead = tstart_gen0 - CPUTimer_getTimerCount(CPUTIMER0_BASE);
    printf("\n Timer overhead = %d cycles\n",timer_overhead);

    //
    // Enable PIPE Global Interrupt (for INTs and RTINTs) and INT enable in CPU.
    //
    ENINT;
    Interrupt_enableGlobal();

    //
    // Execute Control Loop ISR for the specified number of times
    //
    while(ctrlLoopCount < DLOG_NUMBER_SAMPLES)
    {       
        //aci_ctrlLoop_ISR1();
    }

    Interrupt_disableGlobal();

    avg_count_cal();

    #ifdef PROFILE_MODULES

    //printf(" RTINT entry cycles = %d\n ADC read cycles = %d\n Clarke cycles = %d\n Park cycles = %d\n Inverse Park cycles = %d\n PID3 cycles = %d\n Flux est cycles = %d\n Speed est cycles = %d\n SVGEN cycles = %d\n PWM write cycles = %d\n",timer_count_rtint_entry,timer_count_ADC_read,timer_count_clarke,timer_count_park,timer_count_inv_park,timer_count_3pid,timer_count_flux_est,timer_count_speed_est,timer_count_svgen,timer_count_pwm_write);

    printf(" RTINT entry cycles = %d\n ADC read cycles = %d\n Clarke cycles = %d\n Park cycles = %d\n Inverse Park cycles = %d\n PID3 cycles = %d\n Flux est cycles = %d\n Speed est cycles = %d\n SVGEN cycles = %d\n PWM write cycles = %d\n",rtint_entry_count,ADC_read_count,clarke_count,park_count,inv_park_count,pid3_count,flux_est_count,speed_est_count,svgen_count,pwm_write_count);

    //printf(" Total cycle count for complete signal chain execution = %d\n",(rtint_entry_count+ADC_read_count+clarke_count+park_count+inv_park_count+pid3_count+flux_est_count+speed_est_count+svgen_count+pwm_write_count)-(9*timer_overhead));
    
    #else

    printf(" Total cycle count for complete signal chain execution = %d\n",(full_signal_chain_count-timer_overhead));


    #endif

    //
    // Calculate end of test speed by averaging last few samples
    //
    speedEndOfTest = 0;
    for (i=0; i<100; i++)
    {
        speedEndOfTest += DLogCh2[DLOG_NUMBER_SAMPLES-1-i];
    }
    speedEndOfTest = speedEndOfTest/100;

    printf("\n\nMotor Speed at end of test (expected 0.5) : %lf \n", speedEndOfTest);

    if(fabsf(speedEndOfTest-0.5f)<tolerance)
    {
        pass++;
    } else {
        fail++;
    }

    printf("Completed ACI signal chain test, Pass_count = %d, Fail_count = %d \n", pass, fail);

    //return 0;

    while(1)
    {
       
    }
}

__attribute__((interrupt("RTINT"))) void aci_ctrlLoop_ISR(void)
//{

//}
//void aci_ctrlLoop_ISR1(void)
{
    timer_count_rtint_entry = (PWM_PERIOD_MAX - HWREGH(EPWM1_BASE + EPWM_O_TBCTR)) - ADC_SAMPLE_CYCLE_COUNT ;
    rtint_entry_count_buf[ctrlLoopCount] = timer_count_rtint_entry;

    ADC_clearInterruptStatus(ADCA_BASE, ADC_INT_NUMBER1);

    #ifndef PROFILE_MODULES
    __builtin_instrumentation_label("Signal_chian_Start");
    uint32_t tstart_gen0 = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    #endif

    //#ifdef PROFILE_MODULES

    #if SIGNAL_CHAIN == 1
    ////////////////////// READ ADC CONVERT TO FLOAT //////////////////////////
    #ifdef PROFILE_MODULES
    __builtin_instrumentation_label("ADC_Start");
    uint32_t tstart_gen1 = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    #endif
    _iq Ia_dummy = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);    // dummy ADC read to include the numbers in total count
    _iq Ib_dummy = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);    // dummy ADC read to include the numbers in total count
    //
    //  Convert the ADC measurement to phase currents
    //
    Ia = ADJUST_Ia_INPUT(Ia);               
    Ib = ADJUST_Ib_INPUT(Ib);
    #ifdef PROFILE_MODULES
    timer_count_ADC_read = tstart_gen1 - CPUTimer_getTimerCount(CPUTIMER0_BASE);
    ADC_read_count_buf[ctrlLoopCount] = timer_count_ADC_read;
    __builtin_instrumentation_label("ADC_Stop");
    #endif

    ////////////////////// CLARKE TRANSFORM ///////////////////////////////////
    #ifdef PROFILE_MODULES
    __builtin_instrumentation_label("Clarke_Start");
    uint32_t tstart_gen2 = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    #endif
    clarke1.As = Ia; // Phase A curr.
    clarke1.Bs = Ib; // Phase B curr.
    Clarke_calc(&clarke1);

    //
    // Apply ADC derived phase current to park transform
    //
    _iq ialpha = clarke1.Alpha;
    _iq ibeta = clarke1.Beta;

    #ifdef PROFILE_MODULES
    timer_count_clarke = tstart_gen2 - CPUTimer_getTimerCount(CPUTIMER0_BASE);
    clarke_count_buf[ctrlLoopCount] = timer_count_clarke;
    __builtin_instrumentation_label("Clarke_Stop");
    #endif
    
    #else
    //
    // Apply ACI model derived phase current to park transform
    //
    _iq ialpha = aci1.ialfa;
    _iq ibeta = aci1.ibeta;
    #endif

    ////////////////////// PARK TRANSFORM /////////////////////////////////////
    #ifdef PROFILE_MODULES
    __builtin_instrumentation_label("Park_Start");
    uint32_t tstart_gen3 = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    #endif
    park1.ds = ialpha;
    park1.qs = ibeta;
    park1.ang = fe1.theta_r_fe;  
    PARK_calc(&park1);
    #ifdef PROFILE_MODULES
    timer_count_park = tstart_gen3 - CPUTimer_getTimerCount(CPUTIMER0_BASE);
    park_count_buf[ctrlLoopCount] = timer_count_park;
    __builtin_instrumentation_label("Park_Stop");
    #endif

    ////////////////////// 3 PIDs /////////////////////////////////////////////
    #ifdef PROFILE_MODULES
    __builtin_instrumentation_label("PID3_Start");
    uint32_t tstart_gen4 = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    #endif
    // PID Speed
    pid1Spd.pid_ref_reg3 = speedRef;
    pid1Spd.pid_fdb_reg3 = se1.wr_hat_se;
    PIDREG3_calc(&pid1Spd);
    
    // PID Iq
    pid1Iq.pid_ref_reg3 = pid1Spd.pid_out_reg3;
    pid1Iq.pid_fdb_reg3 = park1.qe;
    PIDREG3_calc(&pid1Iq);

    // PID Id
    pid1Id.pid_ref_reg3 = idRef;
    pid1Id.pid_fdb_reg3 = park1.de;
    PIDREG3_calc(&pid1Id);
    
    #ifdef PROFILE_MODULES
    timer_count_3pid = tstart_gen4 - CPUTimer_getTimerCount(CPUTIMER0_BASE);
    pid3_count_buf[ctrlLoopCount] = timer_count_3pid;
    __builtin_instrumentation_label("PID3_Stop");
    #endif

    ////////////////////// Inverse Park ///////////////////////////////////////
    #ifdef PROFILE_MODULES
    __builtin_instrumentation_label("InvPark_Start");
    uint32_t tstart_gen5 = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    #endif
    ipark1.de = pid1Id.pid_out_reg3;
    ipark1.qe = pid1Iq.pid_out_reg3;
    ipark1.ang = fe1.theta_r_fe;
    IPARK_calc(&ipark1);
    #ifdef PROFILE_MODULES
    timer_count_inv_park = tstart_gen5 - CPUTimer_getTimerCount(CPUTIMER0_BASE);
    inv_park_count_buf[ctrlLoopCount] = timer_count_inv_park;
    __builtin_instrumentation_label("InvPark_Stop");
    #endif

    ////////////////////// ACI MOTOR MODEL ////////////////////////////////////
    #ifdef PROFILE_MODULES
    __builtin_instrumentation_label("ACI_Motor_Start");
    uint32_t tstart_gen6 = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    #else
    part1_count_end = tstart_gen0 - CPUTimer_getTimerCount(CPUTIMER0_BASE);
    part2_count_start = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    #endif
    aci1.ualfa = ipark1.ds;
    aci1.ubeta = ipark1.qs;
    ACI_calc(&aci1);
    #ifdef PROFILE_MODULES
    timer_count_aci_mod = tstart_gen6 - CPUTimer_getTimerCount(CPUTIMER0_BASE);
    __builtin_instrumentation_label("ACI_Motor_Stop");
    #endif

    //
    // Save computed values to log buffer for plotting
    //
    DLogCh1[ctrlLoopCount] = aci1.ialfa;     // Current Plot
    DLogCh2[ctrlLoopCount] = se1.wr_hat_se;  // Speed   Plot

    #if SIGNAL_CHAIN == 1
    //
    // Output modeled phase current to DAC so it can be
    // routed to ADC to complete the loop
    //
    ////////////////////// INVERSE CLARK TRANSFORM ////////////////////////////
    #ifdef PROFILE_MODULES
    __builtin_instrumentation_label("InvClarke_Start");
    uint32_t tstart_gen7 = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    #endif
    iclarke1.Alpha = aci1.ialfa;
    iclarke1.Beta = aci1.ibeta;
    IClarke_calc(&iclarke1);
    //
    // Adjust the phase current values (between -1.0 abd 1.0) to a DAC value
    // that can be output and read correctly by ADC
    //
    
    //DAC_setShadowValue(DACA_BASE, ADJUST_Ia_OUTPUT(iclarke1.As));  //ADC-DAC loopback disabled
    //DAC_setShadowValue(DACB_BASE, ADJUST_Ib_OUTPUT(iclarke1.Bs));  //ADC-DAC loopback disabled
    Ia = ADJUST_Ia_OUTPUT(iclarke1.As);
    Ib = ADJUST_Ib_OUTPUT(iclarke1.Bs);
    #ifdef PROFILE_MODULES
    timer_count_inv_clarke = tstart_gen7 - CPUTimer_getTimerCount(CPUTIMER0_BASE);
    __builtin_instrumentation_label("InvClarke_Stop");
    #else
    part2_count_end = part2_count_start - CPUTimer_getTimerCount(CPUTIMER0_BASE);
    part3_count_start = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    #endif

    #endif

    ////////////////////// FLUX ESTIMATION ////////////////////////////////////
    // Feedback Control:
    #ifdef PROFILE_MODULES
    __builtin_instrumentation_label("Flux_Start");
    uint32_t tstart_gen8 = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    #endif
    fe1.u_ds_fe = ipark1.ds;
    fe1.u_qs_fe = ipark1.qs;
    fe1.i_ds_fe = aci1.ialfa;
    fe1.i_qs_fe = aci1.ibeta;
    ACIFE_calc(&fe1);
    #ifdef PROFILE_MODULES
    timer_count_flux_est = tstart_gen8 - CPUTimer_getTimerCount(CPUTIMER0_BASE);
    flux_est_count_buf[ctrlLoopCount] = timer_count_flux_est;
    __builtin_instrumentation_label("Flux_Stop");
    #endif
    
    ////////////////////// SPEED ESTIMATION ///////////////////////////////////
    #ifdef PROFILE_MODULES
    __builtin_instrumentation_label("Speed_Start");
    uint32_t tstart_gen9 = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    #endif
    se1.i_ds_se = ipark1.ds;
    se1.i_qs_se = ipark1.qs;
    se1.psi_dr_se = fe1.psi_dr_fe;
    se1.psi_qr_se = fe1.psi_qr_fe;
    se1.theta_r_se = fe1.theta_r_fe;
    ACISE_calc(&se1);
    #ifdef PROFILE_MODULES
    timer_count_speed_est = tstart_gen9 - CPUTimer_getTimerCount(CPUTIMER0_BASE);
    speed_est_count_buf[ctrlLoopCount] = timer_count_speed_est;
    __builtin_instrumentation_label("Speed_Stop");
    #endif

    #if SIGNAL_CHAIN == 1
    ////////////////////// SVGEN //////////////////////////////////////////////
    #ifdef PROFILE_MODULES
    __builtin_instrumentation_label("SVGEN_Start");
    uint32_t tstart_gen10 = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    #endif
    svgen1.Ualpha = ipark1.ds;
    svgen1.Ubeta  = ipark1.qs;
    SVGEN_calc(&svgen1);
    #ifdef PROFILE_MODULES
    timer_count_svgen = tstart_gen10 - CPUTimer_getTimerCount(CPUTIMER0_BASE);
    svgen_count_buf[ctrlLoopCount] = timer_count_svgen;
    __builtin_instrumentation_label("SVGEN_Stop");
    #endif

    //
    // Write to the three PWMs. The writes simulate a real execution where
    // PWMs control the 3 phase voltage.
    //

    ////////////////////// Write 3 PWMs ///////////////////////////////////////
    #ifdef PROFILE_MODULES
    __builtin_instrumentation_label("PWM_Start");
    #endif
    uint32_t tstart_gen11 = CPUTimer_getTimerCount(CPUTIMER0_BASE);
    uint32_t Ua = _IQmpy(PWM_HALF_MAX,svgen1.Ta)+ PWM_HALF_MAX;
    uint32_t Ub = _IQmpy(PWM_HALF_MAX,svgen1.Tb)+ PWM_HALF_MAX;
    uint32_t Uc = _IQmpy(PWM_HALF_MAX,svgen1.Tc)+ PWM_HALF_MAX;
    PWM_setUa(Ua);
    PWM_setUb(Ub);
    PWM_setUc(Uc);
    #ifdef PROFILE_MODULES
    timer_count_pwm_write = tstart_gen11 - CPUTimer_getTimerCount(CPUTIMER0_BASE);
    pwm_write_count_buf[ctrlLoopCount] = timer_count_pwm_write;
    __builtin_instrumentation_label("PWM_Stop");
    #endif

    #ifndef PROFILE_MODULES
    timer_count_full_signal_chain = part3_count_start - CPUTimer_getTimerCount(CPUTIMER0_BASE) + timer_count_rtint_entry + ADC_SAMPLE_CYCLE_COUNT + part1_count_end;
    full_signal_chain_count_buf[ctrlLoopCount] = timer_count_full_signal_chain;
    __builtin_instrumentation_label("Signal_chian_Stop");
    #endif

    #endif

    ctrlLoopCount++;

}

void avg_count_cal()
{
    int k = 0;
    //
    // Calculate end of test by averaging last few samples
    //
    rtint_entry_count = 0; 
    ADC_read_count = 0;
    clarke_count = 0;
    park_count = 0;
    pid3_count = 0;
    inv_park_count = 0;
    //aci_mod_count = 0;
    //inv_clarke_count = 0;
    flux_est_count = 0;
    speed_est_count = 0;
    svgen_count = 0;
    pwm_write_count = 0;
    full_signal_chain_count = 0;

    for (k=0; k<100; k++)
    {
        rtint_entry_count += rtint_entry_count_buf[k+500];
        ADC_read_count += ADC_read_count_buf[k+500];
        clarke_count += clarke_count_buf[k+500];
        park_count += park_count_buf[k+500];
        pid3_count += pid3_count_buf[k+500];
        inv_park_count += inv_park_count_buf[k+500];
        //aci_mod_count += aci_mod_count_buf[k+500];
        //inv_clarke_count += inv_clarke_count_buf[k+500];
        flux_est_count += flux_est_count_buf[k+500];
        speed_est_count += speed_est_count_buf[k+500];
        svgen_count += svgen_count_buf[k+500];
        pwm_write_count += pwm_write_count_buf[k+500];
        full_signal_chain_count += full_signal_chain_count_buf[k+500];
    }
    rtint_entry_count = rtint_entry_count/100;
    ADC_read_count = ADC_read_count/100;
    clarke_count = clarke_count/100;
    park_count = park_count/100;
    pid3_count = pid3_count/100;
    inv_park_count = inv_park_count/100;
    //aci_mod_count = aci_mod_count/100;
    //inv_clarke_count = inv_clarke_count/100;
    flux_est_count = flux_est_count/100;
    speed_est_count = speed_est_count/100;
    svgen_count = svgen_count/100;
    pwm_write_count = pwm_write_count/100;
    full_signal_chain_count = full_signal_chain_count/100;
}

// void INT_CPU_OVF_ISR()
// {
//     ESTOP0;
// }



//
// End of File
//
