#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "bitutil.h"

#define BITS_IN_BYTE 8
#define BITS_IN_TYPE(type) (BITS_IN_BYTE * (sizeof(type)))

/**
 * @brief Allocates dynamic memory for a new bit_vect structure on the heap
 * 
 * @param num_bits The number of bits contained in the bit_vect
 * @return bit_vect* 
 */
bit_vect *bit_vect_new(size_t num_bits) {
    bit_vect *vect = malloc(sizeof(*vect));
    if (NULL==vect) {
        fprintf(stderr, "Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    size_t mem_size = num_bits / BITS_IN_TYPE(uint32_t);
    if (!(num_bits%BITS_IN_TYPE(uint32_t))) {
        mem_size++;
    }
    vect->mem = calloc(mem_size, sizeof(*(vect->mem)));
    if (NULL==vect->mem) {
        fprintf(stderr, "Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    vect->size = num_bits;
    return vect;
}
/**
 * @brief Frees the memory associated with a bit_vect structure allocated on the heap
 * 
 * @param vect The memory that will be de-allocated
 */
void bit_vect_free(bit_vect *vect){
    free(vect->mem);
    free(vect);
}
/**
 * @brief Gets the value associated with the bith at index position
 * 
 * @param vect The bit_vect were we keep the bits
 * @param bit_idx The bit we would like to retrieve
 * @return true If the bit is 1
 * @return false If the bit is 0
 */
bool bit_vect_get(bit_vect *vect, size_t bit_idx) {
    if (bit_idx>=vect->size) {
        fprintf(stderr, "Out of bounds bit_idx=%zu, vect->size=%zu\n", 
                            bit_idx, vect->size);
        exit(EXIT_FAILURE);                            
    }
    size_t chunk_offset = bit_idx / BITS_IN_TYPE(uint32_t);
    size_t bit_offset = bit_idx & (BITS_IN_TYPE(uint32_t)-1);
    uint32_t byte = vect->mem[chunk_offset];
    return (byte>>bit_offset) & 1;
}
/**
 * @brief Sets the bit_idx to 1 or 0. 
 * 
 * @param vect The bit_vect were we keep the bits
 * @param bit_idx The index of the bit we want to modify
 * @param val 0 (false) or 1 (true)
 */
void bit_vect_set(bit_vect *vect, size_t bit_idx, bool val) {
    if (bit_idx>=vect->size) {
        fprintf(stderr, "Out of bounds bit_idx=%zu, vect->size=%zu\n", 
                            bit_idx, vect->size);
        exit(EXIT_FAILURE);                            
    }
    size_t chunk_offset = bit_idx /  BITS_IN_TYPE(uint32_t);
    size_t bit_offset = bit_idx & (BITS_IN_TYPE(uint32_t)-1);
    uint32_t *byte = &(vect->mem[chunk_offset]);
    if (val) {
        // Sets the the `bit_idx` to 1 (true)
        *byte |= ((uint32_t)1) << bit_offset;
    }else {
        // Sets the bit `bit_idx` to 0 (false)
        *byte &= ~(1 << bit_offset);
    }
}
/**
 * @brief Sets the bit_idx inside the vect to 1 (true)
 */
void bit_vect_set1(bit_vect *vect, size_t bit_idx) {
    bit_vect_set(vect, bit_idx, true);
}

/**
 * @brief Sets the bit_idx inside the vect to 0 (true)
 */
void bit_vect_set0(bit_vect *vect, size_t bit_idx) {
    bit_vect_set(vect, bit_idx, false);
}
