
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

__nv bool rlt = false;

int main()
{
    power_on_init();
    clock_sys_init();
    dma_init();

    __uart_init();
    __timer_init();

    GPIO_setOutputHighOnPin(LED_GREEN_PORT, LED_GREEN_PIN);



//    sort_regist();
//    crc_regist();
//    dijkstra_regist();
//    crc_regist();
//    cem_regist();
//    bc_regist();
//    rsa_regist();
    ar_regist();

    while (1) {
        rlt = scheduler_main();
    }

    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN2);

}

void error_detected() {
    GPIO_setOutputHighOnPin(LED_RED_PORT, LED_RED_PIN);
}
