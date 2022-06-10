
#ifndef IMC_SCHEDULER_H_
#define IMC_SCHEDULER_H_

#include <ImC/nv.h>
#include <ImC/task.h>
#include <ImC/analysis/energy_budget.h>
#include <stdbool.h>

#define TASKED_APP_SELF_CHECK_MODE         1

#define TASK_QUE_SIZE       20
#define BACKUP_BUF_SIZE     128

void task_regist(TASKID id, TASKFUNC name, bool backup);
void war_regist(void* src, uint16_t size);

#define WAR_REGIST(size) war_regist((void*)&__persistent_vars, size)

bool scheduler_main();

#endif /* IMC_SCHEDULER_H_ */
