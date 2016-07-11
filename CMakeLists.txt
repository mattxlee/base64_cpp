cmake_minimum_required(VERSION 2.8.4)

project(base64_test)

add_definitions(-std=c++11)

include_directories("./include" "./googletest/googletest" "./googletest/googletest/include")

file(GLOB base64_src "./src/*.cc")
file(GLOB test_src "./test/*.cc")

add_library(base64_cpp ${base64_src})

file(GLOB googletest_src "./googletest/googletest/src/gtest-all.cc" "./googletest/googletest/src/gtest_main.cc")

add_executable(base64_test ${base64_src} ${test_src} ${googletest_src})

target_link_libraries(base64_test pthread)

file(GLOB base64_inc "./include/*.h")

install(FILES ${base64_inc} DESTINATION include/base64_cpp)

install(TARGETS base64_cpp DESTINATION lib)
