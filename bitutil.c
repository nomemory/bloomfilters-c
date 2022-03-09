#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "bitutil.h"

#define BITS_IN_BYTE 8

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
    vect->bytes = malloc(num_bits / BITS_IN_BYTE + 1);
    if (NULL==vect->bytes) {
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
inline void bit_vect_free(bit_vect *vect) {
    free(vect->bytes);
    free(vect);
}
/**
 * @brief Gets the value associated with the bith at index position
 * 
 * Memory (vect->bytes) is organized like this:
 * 
 * [0][0][0][0][0][0][0][0] <-- uint8_t (1 byte)
 * [0][0][0][0][0][0][0][0]
 * [0][0][0][0][0][0][0][x]
 * ...
 * [0][0][0][0][0][0][0][0]
 * 
 * To get to position 'x' we need to calculate the byte_offset (row) and the the bit_offset 
 * (index on the row)
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
    size_t byte_offset = bit_idx / BITS_IN_BYTE;
    size_t bit_offset = bit_idx & (BITS_IN_BYTE-1);
    uint8_t byte = vect->bytes[byte_offset];
    return (byte>>bit_offset) & ((uint8_t)1);
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
    size_t byte_offset = bit_idx / BITS_IN_BYTE;
    size_t bit_offset = bit_idx & (BITS_IN_BYTE-1);
    uint8_t *byte = &(vect->bytes[byte_offset]);
    if (val) {
        // Sets the the `bit_idx` to 1 (true)
        *byte |= ((uint8_t)1) << bit_offset;
    }else {
        // Sets the bit `bit_idx` to 0 (false)
        *byte &= ~(((uint8_t)1) << bit_offset);
    }
}
/**
 * @brief Sets the bit_idx inside the vect to 1 (true)
 */
inline void bit_vect_set1(bit_vect *vect, size_t bit_idx) {
    bit_vect_set(vect, bit_idx, true);
}

/**
 * @brief Sets the bit_idx inside the vect to 0 (true)
 */
inline void bit_vect_set0(bit_vect *vect, size_t bit_idx) {
    bit_vect_set(vect, bit_idx, false);
}
int main() {
    bit_vect *vect = bit_vect_new(1<<6);
    
    bit_vect_set(vect, 33, true);
    printf("%d\n", bit_vect_get(vect, 33));

    bit_vect_set(vect, 33, false);
    printf("%d\n", bit_vect_get(vect, 33));


    printf("%d\n", bit_vect_get(vect, 35));

    bit_vect_set(vect, 35, true);
    printf("%d\n", bit_vect_get(vect, 35));
}
