
#ifndef TASKED_APP_TASKED_CUCKOO_H_
#define TASKED_APP_TASKED_CUCKOO_H_

#include <stdint.h>

#define CUCKOO_NUM_BUCKETS          64                          // must be a power of 2
#define CUCKOO_NUM_INSERTS          (CUCKOO_NUM_BUCKETS / 4)    // shoot for 25% occupancy
#define CUCKOO_NUM_LOOKUPS          CUCKOO_NUM_INSERTS
#define CUCKOO_MAX_RELOCATIONS      8
#define CUCKOO_BUFFER_SIZE          32

typedef uint16_t cuckoo_value_t;
typedef uint16_t cuckoo_hash_t;
typedef uint16_t cuckoo_fingerprint_t;
typedef uint16_t cuckoo_index_t;               // bucket index

typedef struct {
    uint16_t insert_count;
    uint16_t inserted_count;
} cuckoo_insert_count_t;

typedef struct {
    uint16_t lookup_count;
    uint16_t member_count;
} cuckoo_lookup_count_t;


typedef enum{
    CUCKOO_Insert,
    CUCKOO_Add,
    CUCKOO_Lookup,
    CUCKOO_Lookup_Search
} TaskName;

// seeds the pseudo-random sequence of keys
static const cuckoo_value_t cuckoo_init_key = 0x0001;

uint16_t cuckoo_checkrlt[CUCKOO_NUM_BUCKETS] = {
    32128, 0, 0, 31939, 0, 0, 0, 0, 29690, 0, -31488,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 31638, 0, 0, 0,
    0, 0, 29276, 28327, 0, 32223, 0, 31453, 0, 0, 0,
    0, 0, -32409, 0, 0, -30614, 0, 0, 0, 30958, 0, 0,
    0, 0, 0, 0, 0, 28342, 0, -30984, 0, 29946, 0, 0, 0, 0, -32129
};

#endif /* TASKED_APP_TASKED_CUCKOO_H_ */
