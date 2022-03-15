#ifndef HASHF_H
#define HASHF_H

#define DJB2_INIT 5381

#include <stdlib.h>
#include <stdint.h>

uint32_t djb2(const void *buff, size_t length);
uint32_t sdbm(const void *buff, size_t length);

#endif
