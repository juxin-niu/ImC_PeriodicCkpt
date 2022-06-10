
#ifndef TASKED_APP_TASKED_CEM_H_
#define TASKED_APP_TASKED_CEM_H_


#include <stdint.h>

#define CEM_NIL                         0 // like NULL, but for indexes, not real pointers

#define CEM_DICT_SIZE                   128
#define CEM_BLOCK_SIZE                  64

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

uint16_t cem_check[CEM_DICT_SIZE][3] = {
    {0, 0, 16}, {1, 0, 17}, {2, 0, 19}, {3, 0, 21}, {4, 0, 0}, {5, 0, 0}, {6, 0, 0}, {7, 0, 0},
    {8, 0, 0}, {9, 0, 0}, {10, 0, 0}, {11, 0, 0}, {12, 0, 0}, {13, 0, 0}, {14, 0, 0}, {15, 0, 0},
    {1, 18, 24}, {0, 0, 25}, {2, 20, 26}, {0, 0, 27}, {3, 22, 28}, {0, 0, 29}, {0, 0, 23},
    {0, 0, 30}, {1, 0, 32}, {0, 0, 33}, {2, 0, 34}, {0, 0, 35}, {3, 0, 36}, {0, 0, 37}, {0, 0, 31},
    {0, 0, 38}, {1, 0, 40}, {0, 0, 41}, {2, 0, 42}, {0, 0, 43}, {3, 0, 44}, {0, 0, 45}, {0, 0, 39},
    {0, 0, 46}, {1, 0, 48}, {0, 0, 49}, {2, 0, 50}, {0, 0, 51}, {3, 0, 52}, {0, 0, 53}, {0, 0, 47},
    {0, 0, 54}, {1, 0, 56}, {0, 0, 57}, {2, 0, 58}, {0, 0, 59}, {3, 0, 60}, {0, 0, 61}, {0, 0, 55},
    {0, 0, 62}, {1, 0, 64}, {0, 0, 65}, {2, 0, 66}, {0, 0, 67}, {3, 0, 68}, {0, 0, 69}, {0, 0, 63},
    {0, 0, 70}, {1, 0, 72}, {0, 0, 73}, {2, 0, 74}, {0, 0, 75}, {3, 0, 76}, {0, 0, 77}, {0, 0, 71},
    {0, 0, 78}, {1, 0, 0}, {0, 0, 0}, {2, 0, 0}, {0, 0, 0}, {3, 0, 0}, {0, 0, 0}, {0, 0, 79},
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
    {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0},
    {0, 0, 0}

};

#endif /* TASKED_APP_TASKED_CEM_H_ */
