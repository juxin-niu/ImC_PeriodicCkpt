
#ifndef IMC_ANALYSIS_ENERGY_BUDGET_H_
#define IMC_ANALYSIS_ENERGY_BUDGET_H_

#include <stdint.h>
#include <stdbool.h>

void malloc_budget(uint16_t budget);

bool use_budget(uint16_t budget);

uint16_t get_budget(uint16_t budget);


#endif /* IMC_ANALYSIS_ENERGY_BUDGET_H_ */
