
#ifndef IMC_ANALYSIS_UART2TARGET_H_
#define IMC_ANALYSIS_UART2TARGET_H_

#include <msp430.h>
#include <ImC/target_spec.h>
#include <ImC/target.h>
#include <stdint.h>
#include <stdbool.h>

#if WORKING_FREQUENCY_IN_MHZ == 1
#define CLK_PRESCALAR_USED          8
#define FIRST_MODE_REG_USED         0
#define SECOND_MODE_REG_USED        214
#define OVER_SAMP_USED              0
#elif WORKING_FREQUENCY_IN_MHZ == 2
#define CLK_PRESCALAR_USED          17
#define FIRST_MODE_REG_USED         0
#define SECOND_MODE_REG_USED        74
#define OVER_SAMP_USED              0
#elif WORKING_FREQUENCY_IN_MHZ == 4
#define CLK_PRESCALAR_USED          2
#define FIRST_MODE_REG_USED         2
#define SECOND_MODE_REG_USED        187
#define OVER_SAMP_USED              1
#elif WORKING_FREQUENCY_IN_MHZ == 8
#define CLK_PRESCALAR_USED          4
#define FIRST_MODE_REG_USED         5
#define SECOND_MODE_REG_USED        85
#define OVER_SAMP_USED              1
#else
#error "WORKING FREQUENCY ILLEGAL!"
#endif

void uart2target_init();

#endif /* IMC_ANALYSIS_UART2TARGET_H_ */
