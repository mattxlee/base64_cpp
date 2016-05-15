cmake_minimum_required(VERSION 2.8.4)

project(base64_test)

add_definitions(-std=c++11)

include_directories("./include" "./googletest/googletest" "./googletest/googletest/include")

file(GLOB base64_src "./src/*.cpp")
file(GLOB test_src "./test/*.cpp")

file(GLOB googletest_src "./googletest/googletest/src/gtest-all.cc" "./googletest/googletest/src/gtest_main.cc")

add_executable(base64_test ${base64_src} ${test_src} ${googletest_src})
