
#include <tasked_app/tasked_app.h>
#include <tasked_app/tasked_sort.h>

__SHARED_VAR(
uint16_t sorted[SORT_LENGTH];
uint16_t inner_index;
uint16_t outer_index;
)

__TASK_ENTRY(init,

__GET(outer_index) = 0;
__GET(inner_index) = 1;
for (uint16_t temp = 0; temp < SORT_LENGTH; ++temp)
    __GET(sorted[temp]) = raw[temp];
return 1;

)

__TASK(1, inner_loop,

uint16_t temp;
uint16_t val_outer = __GET(sorted[__GET(outer_index)]);
uint16_t val_inner = __GET(sorted[__GET(inner_index)]);
if (val_outer > val_inner)
{
   temp = val_outer;
   val_outer = val_inner;
   val_inner = temp;
}
__GET(sorted[__GET(outer_index)]) = val_outer;
__GET(sorted[__GET(inner_index)]) = val_inner;

++__GET(inner_index);
if (__GET(inner_index) < SORT_LENGTH)
    return 1;
else
    return 2;

)

__TASK(2, outer_loop,

++__GET(outer_index);
__GET(inner_index) = __GET(outer_index) + 1;
if (__GET(outer_index) < SORT_LENGTH - 1)
    return 1;
else {
    if (TASKED_APP_SELF_CHECK_MODE) {
        __GET(inner_index) = 0;
        return 3;
    } else
        return TASK_FINISH;
}

)


__TASK(3, finish,

while (__GET(inner_index) != SORT_LENGTH - 1) {
    uint16_t a1 = __GET(sorted[__GET(inner_index)]);
    uint16_t a2 = __GET(sorted[__GET(inner_index) + 1]);
    if (a1 >= a2) {
        error_detected();
        while (1) {}
    }
    __GET(inner_index)++;
}

return TASK_FINISH;

)



void sort_regist()
{
    task_regist(0, init,       false);
    task_regist(1, inner_loop, true );
    task_regist(2, outer_loop, true );
    task_regist(3, finish,     false);

    WAR_REGIST(SORT_LENGTH + 2);
}
