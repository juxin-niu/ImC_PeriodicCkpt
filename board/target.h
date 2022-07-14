
#ifndef BOARD_TARGET_H_
#define BOARD_TARGET_H_

#include <profile.h>

#define WORKING_FREQUENCY_IN_MHZ   PROFILE_WORKING_FREQUENCY

void power_on_init();
void clock_sys_init();
void dma_init();

#endif /* BOARD_TARGET_H_ */
