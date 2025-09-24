cmake_minimum_required(VERSION 3.22)
#---------------------
if (CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(FATAL_ERROR "-- In-source builds are not allowed.")
endif ()
#---------------------
set(PROJECT_NAME imgui-hmi)
set(CMAKE_CXX_STANDARD 20)
project(${PROJECT_NAME} C CXX)
message("${BoldGreen}-- ${PROJECT_NAME} BUILD ${ColourReset}")
#---------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(options)
#---------------------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/app)
#---------------------
if(NOT DEFINED CROSS_COMPILER OR "${CROSS_COMPILER}" STREQUAL "OFF")
    enable_testing()
    add_subdirectory(tests)
endif()