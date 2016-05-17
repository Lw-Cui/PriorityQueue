add_executable(tests test.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
target_link_libraries(tests gtest gtest_main)