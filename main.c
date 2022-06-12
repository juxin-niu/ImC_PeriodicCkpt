
#include <ImC/nv.h>
#include <ImC/target_spec.h>
#include <ImC/scheduler.h>
#include <ImC/target.h>
#include <ImC/task.h>
#include <ImC/analysis/io.h>
#include <ImC/analysis/time_meas.h>
#include <ImC/analysis/hamming8.h>
#include <ImC/analysis/uart2target.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <tasked_app/tasked_app.h>

/* ar_regist, bc_regist, cem_regist, crc_regist,
 * cuckoo_regist, dijkstra_regist, rsa_regist, sort_regist */

__nv uint16_t first_run = 1;
__nv bool scheduler_done = 0;

int main()
{
    power_on_init();
    clock_sys_init();
    dma_init();
    uart2target_init();

    if (first_run == 1) {
        ar_regist();
        first_run = 0;
    }

    while (1) {
        if (scheduler_done != true) {
            EUSCI_A_UART_transmitData(UART_BASEADDR, hamming_enc(0x0));
            scheduler_done = scheduler_main();
        }
        else {
            EUSCI_A_UART_transmitData(UART_BASEADDR, hamming_enc(0x1));
            scheduler_done = 0;
        }

    }

}

void error_detected() {
    GPIO_setOutputHighOnPin(LED_RED_PORT, LED_RED_PIN);
}


