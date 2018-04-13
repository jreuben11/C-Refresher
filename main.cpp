#include <iostream>
#include <gtest/gtest.h>
#include "cpp_sorter.h"

int main(int argc, char **argv) {
    int a[] = {1,2,3,4};
    array_sort(a, sizeof(a));
    std::cout << "Running tests" << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "tests complete" << std::endl;
    return RUN_ALL_TESTS();

}