
#include <ImC/target_spec.h>
#include "scheduler.h"
#include <stdbool.h>
#include <stdio.h>

#define GET_TASK(id)            scheduler_task_queue[id]
#define GET_TASK_BCTYPE(id)     scheduler_task_bakcup[id]
#define GET_TASK_PTR(id)        scheduler_task_funcque[id]

__nv uint16_t scheduler_backbuf[BACKUP_BUF_SIZE];
__nv TASKFUNC scheduler_task_funcque[TASK_QUE_SIZE];
__nv bool scheduler_task_bakcup[TASK_QUE_SIZE];

__nv void* scheduler_backup_src = 0;
__nv uint16_t scheduler_backup_size = 0;

__nv TASKID cur_task_id = 0;
__nv TASKID next_task_id = 0;
__nv bool task_running = 0;
__nv bool is_first_run = true;


static void undo();

inline bool do_scheduler()
{
    while (cur_task_id != TASK_FINISH) {
        // Power failure: Nothing need to do.
        if (task_running == false && GET_TASK_BCTYPE(cur_task_id) == true) {

        // Power failure: Nothing need to do.
#if TASKED_APP_ENERGY_BUDGET_MODE
        if (use_budget(12) == false)    { return false;}
#endif /* ENERGY_BUDGET_MODE */

            HWREG16(DMA_BASE + DMA_CHANNEL_0 + OFS_DMA0CTL) |= DMAREQ;

            // Power failure: Nothing need to do.
#if TASKED_APP_ENERGY_BUDGET_MODE
        if (use_budget(9 + cur_task_id) == false) {scheduler_backbuf[1] = 0xDCBA; /* wrong bakcup. */ return false;}
#endif /* ENERGY_BUDGET_MODE */

        }
        task_running = true;

        // Power failure: Need to undo. Ensure program execution is atomic.
#if TASKED_APP_ENERGY_BUDGET_MODE
        if (use_budget(17) == false)    {return false;}
#endif /* ENERGY_BUDGET_MODE */

        next_task_id = (* GET_TASK_PTR(cur_task_id) )();

        // Power failure: Need to undo. Otherwise current task is equivalent to being executed twice.
#if TASKED_APP_ENERGY_BUDGET_MODE
        if (use_budget(13 + cur_task_id) == false)    { return false;}
#endif /* ENERGY_BUDGET_MODE */

        task_running = false;

        // Power failure: Need to undo. Otherwise current task is equivalent to being executed twice.
#if TASKED_APP_ENERGY_BUDGET_MODE
        if (use_budget(10 + cur_task_id) == false)    { return false;}
#endif /* ENERGY_BUDGET_MODE */

        cur_task_id = next_task_id;

        // Power failure: Nothing need to do.
#if TASKED_APP_ENERGY_BUDGET_MODE
        if (use_budget(9) == false)    { return false;}
#endif /* ENERGY_BUDGET_MODE */

    }
    return true;
}

bool scheduler_main()
{
    if (is_first_run == false) {

        if (cur_task_id != next_task_id) {
            cur_task_id = next_task_id;
        }
        else if ( task_running == true && GET_TASK_BCTYPE(cur_task_id) == true ) {
            undo();
        }

    } else {
        cur_task_id = (* GET_TASK_PTR(0) )();
        next_task_id = cur_task_id;
        is_first_run = false;
    }

#if TASKED_APP_ENERGY_BUDGET_MODE
    malloc_budget(100 - cur_task_id);
#endif /* ENERGY_BUDGET_MODE */

    // Prologue prepare
    HWREG16(DMA_BASE + DMA_CHANNEL_0 + OFS_DMA0CTL) &= ~DMAEN;
    __data16_write_addr((unsigned short)(DMA_BASE + DMA_CHANNEL_0 + OFS_DMA0SA), (unsigned long)scheduler_backup_src);
    __data16_write_addr((unsigned short)(DMA_BASE + DMA_CHANNEL_0 + OFS_DMA0DA), (unsigned long)scheduler_backbuf);
    HWREG16(DMA_BASE + DMA_CHANNEL_0 + OFS_DMA0SZ) = scheduler_backup_size;
    HWREG16(DMA_BASE + DMA_CHANNEL_0 + OFS_DMA0CTL) |= DMAEN;

    // Scheduler
    if (do_scheduler() == true) {
        is_first_run = true;
        return true;
    } else {
        return false;
    }
}

static void undo()
{
    HWREG16(DMA_BASE + DMA_CHANNEL_0 + OFS_DMA0CTL) &= ~DMAEN;
    __data16_write_addr((unsigned short)(DMA_BASE + DMA_CHANNEL_0 + OFS_DMA0SA), (unsigned long)scheduler_backbuf);
    __data16_write_addr((unsigned short)(DMA_BASE + DMA_CHANNEL_0 + OFS_DMA0DA), (unsigned long)scheduler_backup_src);
    HWREG16(DMA_BASE + DMA_CHANNEL_0 + OFS_DMA0SZ) = scheduler_backup_size;
    HWREG16(DMA_BASE + DMA_CHANNEL_0 + OFS_DMA0CTL) |= DMAEN;
    HWREG16(DMA_BASE + DMA_CHANNEL_0 + OFS_DMA0CTL) |= DMAREQ;
}

void task_regist(TASKID id, TASKFUNC name, bool backup)
{
    GET_TASK_PTR(id) = name;
    GET_TASK_BCTYPE(id) = backup;
}

void war_regist(void* src, uint16_t size)
{
    scheduler_backup_src = src;
    scheduler_backup_size = size;
}
