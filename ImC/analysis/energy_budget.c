
#include <ImC/nv.h>
#include "ImC/analysis/energy_budget.h"

static __nv uint16_t energy_budget = 0;

void malloc_budget(uint16_t budget) {
    energy_budget = budget;
}

bool use_budget(uint16_t budget) {
    if (energy_budget >= budget) {
        energy_budget -= budget;
        return true;
    }
    else {
        return false;
    }
}

uint16_t get_budget(uint16_t budget) {
    return budget;
}
