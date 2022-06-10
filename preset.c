
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


__nv TASKREGFUNC testbench_regfunc[8] =
    {ar_regist, bc_regist, cem_regist, crc_regist, cuckoo_regist, dijkstra_regist, rsa_regist, sort_regist};

__nv const uint16_t run_time = 1;
__nv uint16_t testbench_regist[8] = {};
__nv uint16_t testbench_run[8] = {};

void onpower_onetime_time_measure()
{
    for (uint16_t i = 0; i < 8; ++i) {

        if (testbench_regist[i] == 0) {
            (* testbench_regfunc[i] )();
            testbench_regist[i] = 1;
        }

        while (testbench_run[i] != run_time) {
            timer_start_count();
            if (scheduler_main())   testbench_run[i]++;
            timer_end_count();
            printf("Testbench %d for runtime %d, %ld cycles.\n",
                   i, testbench_run[i],
                   timer_get_cycles() );
        }
    }

    GPIO_setOutputHighOnPin(LED_GREEN_PORT, LED_GREEN_PIN);
    for (uint16_t i = 0; i < 8; ++i) {
        testbench_regist[i] = 0;
        testbench_run[i] = 0;
    }
}
