#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "bloom.h"
#include "hashf.h"

/**
 * @brief Allocates memory on the heap for a new bloom_filter.
 * 
 * @param size The size of the internal bit_vec 
 * @param num_functions The number of hash functions used
 * @param ... The hash functions as varargs
 * 
 * Example:
 * 
 * // uint32_t djb2(const void *buff, size_t length);
 * // uint32_t sdbm(const void *buff, size_t length);
 * 
 * bloom_filter *f = bloom_filter(1024, 2, djb2, sdbm);
 * 
 * @return bloom_filter* A dynamically allocated bloom_filter
 */
bloom_filter *bloom_filter_new(size_t size, size_t num_functions, ...) {
    va_list argp;
    bloom_filter *filter = malloc(sizeof(*filter));
    if (NULL==filter) {
        fprintf(stderr, "Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    filter->num_items = 0;
    filter->vect = bit_vect_new(size);
    filter->num_functions = num_functions;
    filter->hash_functions = malloc(sizeof(hash32_func)*num_functions);
    if (NULL==filter->hash_functions) {
        fprintf(stderr, "Out of memory.\n");
        exit(EXIT_FAILURE);    
    }
    va_start(argp, num_functions);
    for(unsigned i = 0; i < num_functions; i++) {
        filter->hash_functions[i] = va_arg(argp, hash32_func);
    }
    va_end(argp);
    return filter;
}
/**
 * @brief Allocates memory on the heap for a new bloom_filter
 * 
 * The bloom filter uses 2 default hash functions (from hash.h): djb2 and sdbm.
 * 
 * @param size The size of the internal bit_vect
 * @return bloom_filter* A dynamically allocated bloom_filter
 */
bloom_filter *bloom_filter_new_default(size_t size) {
    return bloom_filter_new(size, 2, djb2, sdbm);
} 
/**
 * @brief Frees the memory assoaciated with the bloom filter (including the internal bit_vect)
 * 
 * @param filter 
 */
void bloom_filter_free(bloom_filter *filter) {
    bit_vect_free(filter->vect);
    free(filter->hash_functions);
    free(filter);
}
/**
 * @brief Adds an element to the bloom_filter
 * 
 * @param filter The bloom filter 
 * @param data The element to be added as a const void* pointer
 * @param length The length of the element (data is read using uint8_t)
 */
void bloom_filter_put(bloom_filter *filter, const void *data, size_t length){
    for(unsigned i = 0; i < filter->num_functions; i++) {
        uint32_t cur_hash = filter->hash_functions[i](data, length);
        bit_vect_set1(filter->vect, cur_hash % filter->vect->size);
        filter->num_items++;
    }
}
/**
 * @brief Adds a string (const char *str) to the bloom filter
 * 
 * @param filter The bloom filter
 * @param str The string that is being added
 */
void bloom_filter_put_str(bloom_filter *filter, const char *str) {
    bloom_filter_put(filter, str, strlen(str));
}
/**
 * @brief Checks if an element is found or not in the bloom filter
 * 
 * @param filter The bloom filter
 * @param data The element to be checked for
 * @param lentgth The length of the element (data is read using uint8_t)
 * @return true 
 * @return false 
 */
bool bloom_filter_test(bloom_filter *filter, const void *data, size_t lentgth) {
    for(unsigned i = 0; i < filter->num_functions; i++) {
        uint32_t cur_hash = filter->hash_functions[i](data, lentgth);
        if (!bit_vect_get(filter->vect, cur_hash % filter->vect->size)) {
            return false;
        }
    }
    return true;
}
/**
 * @brief Checks if a string element is found or not in the bloom filter
 * 
 * @param filter  The bloom filter
 * @param str The string that is being checked for
 * @return true 
 * @return false 
 */
bool bloom_filter_test_str(bloom_filter *filter, const char *str) {
    return bloom_filter_test(filter, str, strlen(str));
}
