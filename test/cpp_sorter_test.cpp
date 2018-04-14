////
//// Created by josh reuben on 13/04/2018.
////
#include <algorithm>

#include "../include/cpp_sorter.h"
#include "gtest/gtest.h"

TEST(cpp_sorter_test, null_term_str_sort) // NOLINT
{
    char arr[] = "abcdefghab";
    char eq[]  = "aabbcdefgh";
    size_t sz = sizeof(arr)/sizeof(arr[0]) - 1; // we need it, to avoid terminating \0 in "" definition case

    array_sort(arr, sz);
    for(int i=0; i<sz; i++)
        EXPECT_EQ(arr[i], eq[i]);
}
