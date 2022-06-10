
#include <ImC/nv.h>
#include <ImC/target_spec.h>
#include <ImC/scheduler.h>
#include <ImC/target.h>
#include <ImC/task.h>
#include <ImC/analysis/io.h>
#include <ImC/analysis/time_meas.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <tasked_app/tasked_app.h>

/* ar_regist, bc_regist, cem_regist, crc_regist,
 * cuckoo_regist, dijkstra_regist, rsa_regist, sort_regist */

__nv uint16_t first_run = 1;

int main()
{
    power_on_init();
    clock_sys_init();
    dma_init();
    // __uart_init();
    // timer_init();

    if (first_run == 1) {
        ar_regist();
        first_run = 0;
        P1OUT |= BIT4; __delay_cycles(5); P1OUT &= ~BIT4;
    }

    scheduler_main();

    P1OUT |= BIT5; __delay_cycles(5); P1OUT &= ~BIT5;
    first_run = 1;
}

void error_detected() {
    GPIO_setOutputHighOnPin(LED_RED_PORT, LED_RED_PIN);
}


