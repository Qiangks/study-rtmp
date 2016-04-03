//
// Created by chnvideo on 2016/4/2.
//

#include <stdlib.h>
#include "logger.hpp"
#include "utility.hpp"

void srs_random_generate(char* bytes, int size)
{
    static bool _random_initialized = false;
    if (!_random_initialized) {
        srand(0);
        _random_initialized = true;
        log_trace("srand initialized the random.");
    }

    for (int i = 0; i < size; i++) {
        // the common value in [0x0f, 0xf0]
        bytes[i] = 0x0f + (rand() % (256 - 0x0f - 0x0f));
    }
}

bool srs_is_little_endian()
{
    // convert to network(big-endian) order, if not equals,
    // the system is little-endian, so need to convert the int64
    static int little_endian_check = -1;

    if(little_endian_check == -1) {
        union {
            int32_t i;
            int8_t c;
        } little_check_union;

        little_check_union.i = 0x01;
        little_endian_check = little_check_union.c;
    }

    return (little_endian_check == 1);
}