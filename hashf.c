#include "hashf.h"

uint32_t djb2(const void *buff, size_t length) {
    uint32_t hash = DJB2_INIT;
    const uint8_t *data = buff;
    for(size_t i = 0; i < length; i++) {
         hash = ((hash << 5) + hash) + data[i]; 
    }
    return hash;
}
uint32_t sdbm(const void *buff, size_t length) {
    uint32_t hash = 0;
    const uint8_t *data = buff;
    for(size_t i = 0; i < length; i++) {
        hash = data[i] + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}
