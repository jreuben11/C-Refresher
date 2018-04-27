cmake_minimum_required(VERSION 3.10)
project(language_features)

set(CMAKE_CXX_STANDARD 17)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
#    add_definitions(-D__GLIBCXX__)
endif (APPLE)

if(EXISTS ${CMAKE_SOURCE_DIR}/.conan/conanbuildinfo.cmake)
    include(${CMAKE_SOURCE_DIR}/.conan/conanbuildinfo.cmake)
else()
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
endif()
conan_basic_setup()

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable(${PROJECT_NAME} main.cpp TimerExample.cpp include/cpp_sorter.h test/cpp_sorter_test.cpp src/proj_structure/linkage/file1.cpp src/proj_structure/linkage/file2.cpp src/proj_structure/linkage/file0.h src/proj_structure/linkage/file3.cpp src/proj_structure/basics/types.cpp src/proj_structure/basics/userdefinedtypes.cpp)
target_link_libraries(${PROJECT_NAME} gtest gtest_main)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

#Set(BOOST_ROOT /usr/local/Cellar/boost/1.66.0)
find_package(Boost 1.66.0 REQUIRED COMPONENTS system filesystem regex)

#Set(BOOST_ROOT /Users/joshreuben/.conan/data/Boost/1.64.0/conan/stable/package/3ab6cde607dc70d7668599938a90459fece3b7cd/1.66.0)
#SET(BOOST_INCLUDEDIR /Users/joshreuben/.conan/data/Boost/1.64.0/conan/stable/package/3ab6cde607dc70d7668599938a90459fece3b7cd/include)
#SET(BOOST_LIBRARYDIR /Users/joshreuben/.conan/data/Boost/1.64.0/conan/stable/package/3ab6cde607dc70d7668599938a90459fece3b7cd/lib)
#find_package(Boost 1.64.0 REQUIRED)
#find_package(Boost 1.64.0 COMPONENTS program_options regex)
#
if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${BOOST_ROOT})
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
    target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
    #target_link_libraries(language_features
    #        ${Boost_FILESYSTEM_LIBRARY}
    #        ${Boost_SYSTEM_LIBRARY}
    #        ${Boost_REGEX_LIBRARY}
    #        )
else()
    message(STATUS "Boost NOT FOUND")
ENDIF()
message(STATUS "FINISHED")