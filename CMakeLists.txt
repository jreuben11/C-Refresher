cmake_minimum_required(VERSION 3.10)
project(language_features)

set(CMAKE_CXX_STANDARD 17)
if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)
if(EXISTS ${CMAKE_SOURCE_DIR}/.conan/conanbuildinfo.cmake)
    include(${CMAKE_SOURCE_DIR}/.conan/conanbuildinfo.cmake)
else()
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
endif()
conan_basic_setup()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(language_features main.cpp include/cpp_sorter.h test/cpp_sorter_test.cpp)
target_link_libraries(language_features gtest gtest_main)
target_link_libraries(language_features ${CONAN_LIBS})

#Set(BOOST_ROOT /usr/local/Cellar/boost/1.66.0)
#SET(BOOST_INCLUDEDIR /usr/local/Cellar/boost/1.66.0/include)
#SET(BOOST_LIBRARYDIR /usr/local/Cellar/boost/1.66.0/lib)
##find_package(Boost 1.66.0 REQUIRED COMPONENTS program_options regex)

#Set(BOOST_ROOT /Users/joshreuben/.conan/data/Boost/1.64.0/conan/stable/package/3ab6cde607dc70d7668599938a90459fece3b7cd/1.66.0)
#SET(BOOST_INCLUDEDIR /Users/joshreuben/.conan/data/Boost/1.64.0/conan/stable/package/3ab6cde607dc70d7668599938a90459fece3b7cd/include)
#SET(BOOST_LIBRARYDIR /Users/joshreuben/.conan/data/Boost/1.64.0/conan/stable/package/3ab6cde607dc70d7668599938a90459fece3b7cd/lib)
#find_package(Boost 1.64.0 REQUIRED)
#find_package(Boost 1.64.0 COMPONENTS program_options regex)
#
#if(Boost_FOUND)
#include_directories(${BOOST_ROOT})
#include_directories(${Boost_INCLUDE_DIRS})
#link_directories(${Boost_LIBRARY_DIRS})
## target_link_libraries(language_features ${Boost_LIBRARIES})
#target_link_libraries(language_features
#        ${Boost_FILESYSTEM_LIBRARY}
#        ${Boost_SYSTEM_LIBRARY}
#        ${Boost_REGEX_LIBRARY}
#        )
#ENDIF()
