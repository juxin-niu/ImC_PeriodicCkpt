
#ifndef TASKED_APP_TASKED_CEM_H_
#define TASKED_APP_TASKED_CEM_H_


#include <stdint.h>

#define CEM_NIL                         0 // like NULL, but for indexes, not real pointers

#define CEM_DICT_SIZE                   192
#define CEM_BLOCK_SIZE                  96

#define CEM_NUM_LETTERS_IN_SAMPLE       2
#define CEM_LETTER_MASK                 0x000F
#define CEM_LETTER_SIZE_BITS            8
#define CEM_NUM_LETTERS                 (CEM_LETTER_MASK + 1)

typedef uint16_t cem_index_t;
typedef uint16_t cem_letter_t;
typedef uint16_t cem_sample_t;

// NOTE: can't use pointers, since need to ChSync, etc
typedef struct {
    cem_letter_t letter; // 'letter' of the alphabet
    cem_index_t sibling; // this node is a member of the parent's children list
    cem_index_t child;   // link-list of children
} cem_node_t;


#endif /* TASKED_APP_TASKED_CEM_H_ */
