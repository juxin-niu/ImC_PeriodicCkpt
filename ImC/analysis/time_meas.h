
#ifndef IMC_ANALYSIS_TIME_MEAS_H_
#define IMC_ANALYSIS_TIME_MEAS_H_

#include <ImC/target_spec.h>
#include <stdint.h>

#define COUNTER_BASEADDR    TIMER_A2_BASE
#define TA2_CLOCKDIV        TIMER_A_CLOCKSOURCE_DIVIDER_64
//!                         TIMER_A_CLOCKSOURCE_DIVIDER_1
//!                         TIMER_A_CLOCKSOURCE_DIVIDER_10
//!                         TIMER_A_CLOCKSOURCE_DIVIDER_64

void timer_init();

void timer_start_count();

void timer_end_count();

uint32_t timer_get_cycles();

#endif /* IMC_ANALYSIS_TIME_MEAS_H_ */
