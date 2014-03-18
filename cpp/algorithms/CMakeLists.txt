set(CMAKE_LEGACY_CYGWIN_WIN32 0)

PROJECT(Algorithms CXX)
SET(CMAKE_BUILD_TYPE Release)
cmake_minimum_required(VERSION 2.8)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ggdb ")
endif()

# build the commons library
ADD_LIBRARY(commons SHARED Commons)
SET_TARGET_PROPERTIES(commons PROPERTIES LINKER_LANGUAGE CXX)

# build the sort library
ADD_LIBRARY(sort SHARED Sort)
TARGET_LINK_LIBRARIES(sort commons)
SET_TARGET_PROPERTIES(sort PROPERTIES LINKER_LANGUAGE CXX)

# test sort.
ADD_EXECUTABLE(testsort TestSort.cpp)
SET_TARGET_PROPERTIES(testsort PROPERTIES COMPILE_FLAGS -std=c++11)
TARGET_LINK_LIBRARIES(testsort sort)
TARGET_LINK_LIBRARIES(testsort commons)

# Test commons.
ADD_EXECUTABLE(testcommons TestCommons.cpp)
TARGET_LINK_LIBRARIES(testcommons boost_unit_test_framework-mt)

# other executables. 
ADD_EXECUTABLE(binarysearch BinarySearch.cpp)
TARGET_LINK_LIBRARIES(binarysearch commons)

ADD_EXECUTABLE(fibonacci Fibonacci.cpp)
ADD_EXECUTABLE(containers Containers.cpp)
SET_TARGET_PROPERTIES(containers PROPERTIES COMPILE_FLAGS -std=c++11) 
ADD_EXECUTABLE(binarysearchtree BinarySearchTree.cpp)
ADD_EXECUTABLE(queuestack QueueStack.cpp)


