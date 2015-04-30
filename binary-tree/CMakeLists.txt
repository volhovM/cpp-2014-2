cmake_minimum_required(VERSION 2.8)

project(SET)

include_directories(${SET_SOURCE_DIR})

add_executable(set_testing
               set_testing.cpp
               set.h
               set.cpp
               gtest/gtest-all.cc
               gtest/gtest.h
               gtest/gtest_main.cc)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -O3 -pedantic")
endif()

target_link_libraries(set_testing -lgmp -lgmpxx -lpthread)
