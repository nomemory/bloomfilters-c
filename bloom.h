#ifndef BLOOM_H
#define BLOOM_H

#include <stdint.h>
#include <stdbool.h>

#include "bitutil.h"

#define HASH32_NUM_FUNCTIONS 2

typedef uint32_t (*hash32_func)(const void *data, size_t length);

typedef struct bloom_filter_s {
    bit_vect *vect;
    hash32_func *hash_functions;
    size_t num_functions;
    size_t num_items;
} bloom_filter;

bloom_filter *bloom_filter_new(size_t size, size_t num_functions, ...);
bloom_filter *bloom_filter_new_default(size_t size);
void bloom_filter_free(bloom_filter *filter);
void bloom_filter_put(bloom_filter *filter, const void *data, size_t length);
void bloom_filter_put_str(bloom_filter *filter, const char *str);
bool bloom_filter_test(bloom_filter *filter, const void *data, size_t lentgth);
bool bloom_filter_test_str(bloom_filter *filter, const char *str);
#endif
