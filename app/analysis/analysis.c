
#include <app/analysis/analysis.h>
#include <stdio.h>

static uint16_t max_task_id = 0;

static uint16_t task_run_time[20] = {};

void analysis_clear() {
    max_task_id = 0;
    for (uint16_t i = 0; i < 20; ++i)   task_run_time[i] = 0;
}

void analysis_runtask(uint16_t task_id) {
    if (max_task_id < task_id)      max_task_id = task_id;
    task_run_time[task_id]++;
}

void analysis_printout() {
    printf("analysis: [");
    for (uint16_t i = 0; i < max_task_id - 1; ++i) {
        printf("%d, ", task_run_time[i]);
    }
    printf("%d]\n", task_run_time[max_task_id - 1]);
}


