/* some utility macros and functions, usful for testing */
#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <gtest/gtest.h>
#include <cstddef>

/* assert two arrays of length l have equal elements */
#define ASSERT_ARRAYS_EQ(a, b, l) {\
    for(size_t k = 0; k < l; ++k) {\
        ASSERT_EQ(a[k], b[k]);\
    }\
}

/* assert two matrices of sizes w x h have equal elements */
#define ASSERT_MATRICES_EQ(a, b, w, h) {\
    for(size_t p = 0; p < w; ++p) {\
        ASSERT_ARRAYS_EQ(a[p], b[p], h);\
    }\
}


#endif /* TEST_UTILS_HPP */