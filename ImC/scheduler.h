
#ifndef IMC_SCHEDULER_H_
#define IMC_SCHEDULER_H_

#include <ImC/nv.h>
#include <ImC/task.h>
#include <stdbool.h>

#define TASK_QUE_SIZE       12
#define BACKUP_BUF_SIZE     280

#define BACKUP_USE_DMA
//!    -BACKUP_USE_CPU
//!    -BACKUP_USE_DMA

void task_regist(TASKID id, TASKFUNC name, bool backup);
void war_regist(void* src, uint16_t size);

#define WAR_REGIST(size) war_regist((void*)&__persistent_vars, size)

bool scheduler_main();

#endif /* IMC_SCHEDULER_H_ */
