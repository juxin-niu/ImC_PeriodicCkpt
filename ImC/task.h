
#ifndef IMC_TASK_H_
#define IMC_TASK_H_

#include <stdint.h>

typedef uint8_t TASKID;
typedef TASKID (*TASKFUNC)();
typedef void (*TASKREGFUNC)();

#define __SHARED_VAR(...) \
        typedef struct { __VA_ARGS__ } FRAM_data_t  __attribute__ ((aligned (2))); \
        static __nv FRAM_data_t __persistent_vars; \

#define __GET(item) __persistent_vars.item

#define __TASK_ENTRY(name, ...) \
    static TASKID name() { \
        __VA_ARGS__ \
    }

#define __TASK(id, name, ...) \
    static TASKID name() { \
        __VA_ARGS__ \
    }

#define TASK_FINISH  (TASKID)0

#endif /* IMC_TASK_H_ */
