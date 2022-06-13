
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

enum {
    TASK_NONE = 0x01, TASK_RDY = 0x02,
    TASK_RUN =0x04, TASK_DONE = 0x08
};


__nv uint16_t first_run = 1;

__nv TASKREGFUNC testbench_regfunc[8] =
    {ar_regist, bc_regist, cem_regist, crc_regist,
     cuckoo_regist, dijkstra_regist, rsa_regist, sort_regist};

const uint16_t testbench_runtime[8] = {1, 1, 1, 1, 1, 1, 1, 1};

__nv uint8_t hamming_scode[8] = {};
__nv uint8_t hamming_ecode[8] = {};
__nv uint16_t testbench_state[9];
__nv uint16_t testbench_id;

int main()
{
    power_on_init();
    clock_sys_init();
    dma_init();
    uart2target_init();

    if (first_run == 1) {
        testbench_id = 0;
        for (uint16_t i = 0; i < 8; ++i) {
            hamming_scode[i] = hamming_enc(2 * i);
            hamming_ecode[i] = hamming_enc(2 * i + 1);
            testbench_state[i] = TASK_NONE;
        }
        first_run = 0;
    }

    while (1) {
        switch(testbench_state[testbench_id])
        {
        case TASK_NONE:
            (* testbench_regfunc[testbench_id] )();
            testbench_state[testbench_id] = TASK_RDY;
            break;
        case TASK_RDY:
            testbench_state[testbench_id] = TASK_RUN;
            EUSCI_A_UART_transmitData(UART_BASEADDR, hamming_scode[testbench_id]);
            /* NO BREAK! */
        case TASK_RUN:
            scheduler_main();
            testbench_state[testbench_id] = TASK_DONE;
            EUSCI_A_UART_transmitData(UART_BASEADDR, hamming_ecode[testbench_id]);
            /* NO BREAK! */
        case TASK_DONE:
            testbench_id++;
            if (testbench_id >= 8)  testbench_id = 0;
            testbench_state[testbench_id] = TASK_NONE;
            break;
        default:    P1OUT |= BIT0; break;
        }
    }
}

void error_detected() {
    GPIO_setOutputHighOnPin(LED_RED_PORT, LED_RED_PIN);
}


