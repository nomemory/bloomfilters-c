#include <stdio.h>
#include <stdlib.h>

#include "bloom.h"

int main(void) {
    bloom_filter *filter = bloom_filter_new_default(1024);
    bloom_filter_put_str(filter, "abc");
    printf("%d\n", bloom_filter_test_str(filter, "abc"));
    printf("%d\n", bloom_filter_test_str(filter, "bcd"));
    printf("%d\n", bloom_filter_test_str(filter, "0"));
    printf("%d\n", bloom_filter_test_str(filter, "1"));
    bloom_filter_put_str(filter, "2");
    printf("%d\n", bloom_filter_test_str(filter, "2"));
    
    return EXIT_SUCCESS;
}
