cmake_minimum_required(VERSION 2.8)
project(PriorityQueue)
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB HEADER_LIST "${CMAKE_SOURCE_DIR}/include/*.hpp")
install(FILES ${HEADER_LIST} DESTINATION include/PriorityQueue)

# Unit test
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_subdirectory(lib/gtest)
add_subdirectory(src)
enable_testing()
add_test(NAME normal_test COMMAND tests)