
#ifndef TASKED_APP_TASKED_APP_H_
#define TASKED_APP_TASKED_APP_H_

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

void sort_regist();
void crc_regist();
void dijkstra_regist();
void cem_regist();
void bc_regist();
void rsa_regist();
void cuckoo_regist();
void ar_regist();

extern void error_detected();

#endif /* TASKED_APP_TASKED_APP_H_ */
