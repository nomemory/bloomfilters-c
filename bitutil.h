/**
 * @file bitutil.h
 * @author nomemory
 * @brief A file containing macros for bit manipulation on array of bits
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef BITUTIL_H

#include <stdlib.h>
#include <stdint.h>

typedef struct bit_vect {
    uint8_t *bytes;
    size_t size;
} bit_vect;

bit_vect *bit_vect_new(size_t num_bits);
inline void bit_vect_free(bit_vect *vect);
bool bit_vect_get(bit_vect *vect, size_t bit_idx);
void bit_vect_set(bit_vect *vect, size_t bit_idx, bool val);
inline void bit_vect_set1(bit_vect *vect, size_t bit_idx);
inline void bit_vect_set0(bit_vect *vect, size_t bit_idx);

#define BITUTIL_H
#endif
