
#include <app/app_api.h>
#include <scheduling/scheduler.h>

#include <board/driverlib_include.h>
#include <board/led_button.h>
#include <board/nv.h>
#include <board/target.h>
#include <board/uart2target.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef void (*TASKMAIN_FUNC)();
typedef void (*TASKREGIST_FUNC)();

__nv uint16_t first_run = 1;

enum {
    TASK_NONE = 0x00, TASK_RDY = 0x01, TASK_RUN = 0x02, TASK_DONE = 0x04
};

const uint8_t status_code[8][2] = {
    {0, 15}, {51, 60}, {85, 90}, {102, 105},
    {150, 153}, {165, 170}, {195, 204}, {240, 255}
};

__nv uint16_t testbench_state[8] = {/* TASK_NONE */};
__nv uint16_t testbench_id = 0;

void integrated_main();
void scheduler_based_main();

int main()
{
    power_on_init();
    clock_sys_init();
    dma_init();
    uart2target_init();

    if (first_run == 1) {
        testbench_id = 0;

        // Wait until pressing left button.
        turn_on_green_led;
        left_button_init;
        while (!check_button_press) {/* empty */}
        left_button_disable;
        turn_off_green_led;
        first_run = 0;
    }

    integrated_main();
}


void integrated_main()
{
    static const TASKMAIN_FUNC main_func[8] = {
        ar_main, bc_main, cem_main, crc_main, cuckoo_main,
        dijkstra_main, rsa_main, sort_main
    };

    while (1) {
        if (testbench_id >= 8)  testbench_id = 0; // Redundancy.
        switch(testbench_state[testbench_id])
        {
        case TASK_NONE:
        case TASK_RDY:
            /* transmitData after state_change ensures that
             * the same signal will not be sent twice,
             * which ensures the correctness of self-synchronization.  */
            testbench_state[testbench_id] = TASK_RUN;
            EUSCI_A_UART_transmitData(UART_BASEADDR, status_code[testbench_id][0]);
            /* NO BREAK! */
        case TASK_RUN:
            (* main_func[testbench_id] )();
            testbench_state[testbench_id] = TASK_DONE;
            EUSCI_A_UART_transmitData(UART_BASEADDR, status_code[testbench_id][1]);
            /* NO BREAK! */
        case TASK_DONE:
            testbench_id++;
            if (testbench_id >= 8)  testbench_id = 0;
            testbench_state[testbench_id] = TASK_RDY;
            break;
        }
    }

}

void scheduler_based_main()
{

    static const TASKREGIST_FUNC testbench_regfunc[8] = {
        ar_regist, bc_regist, cem_regist, crc_regist, cuckoo_regist,
        dijkstra_regist, rsa_regist, sort_regist
    };

    while (1) {
        switch(testbench_state[testbench_id])
        {
        case TASK_NONE:
            (* testbench_regfunc[testbench_id] )();
            testbench_state[testbench_id] = TASK_RDY;
            break;
        case TASK_RDY:
            /* transmitData after state_change ensures that
             * the same signal will not be sent twice,
             * which ensures the correctness of self-synchronization.  */
            testbench_state[testbench_id] = TASK_RUN;
            EUSCI_A_UART_transmitData(UART_BASEADDR, status_code[testbench_id][0]);
            /* NO BREAK! */
        case TASK_RUN:
            scheduler_main();
            testbench_state[testbench_id] = TASK_DONE;
            EUSCI_A_UART_transmitData(UART_BASEADDR, status_code[testbench_id][1]);
            /* NO BREAK! */
        case TASK_DONE:
            testbench_id++;
            if (testbench_id >= 8)  testbench_id = 0;
            testbench_state[testbench_id] = TASK_NONE;
            break;
        }
    }
}
