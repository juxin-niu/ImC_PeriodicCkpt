
#ifndef TASKED_APP_TASKED_CUCKOO_H_
#define TASKED_APP_TASKED_CUCKOO_H_

#include <stdint.h>

#define CUCKOO_NUM_BUCKETS          256                             // must be a power of 2
#define CUCKOO_NUM_INSERTS          (CUCKOO_NUM_BUCKETS / 2)        // shoot for 25% occupancy
#define CUCKOO_NUM_LOOKUPS          CUCKOO_NUM_INSERTS
#define CUCKOO_MAX_RELOCATIONS      8
#define CUCKOO_BUFFER_SIZE          128

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

#endif /* TASKED_APP_TASKED_CUCKOO_H_ */
