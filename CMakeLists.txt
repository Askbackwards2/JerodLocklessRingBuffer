cmake_minimum_required(VERSION 3.10)
project(JerodLocklessRingBuffer)

set(CMAKE_CXX_STANDARD 20)

# Add test executable
add_executable(RingBufferTestRun src/RingBufferTest.cpp)

enable_testing()
add_test(NAME RingBufferTest COMMAND RingBufferTestRun)
