cmake_minimum_required(VERSION 3.22)
#---------------------
if(CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(FATAL_ERROR "-- In-source builds are not allowed.")
endif()
#---------------------
set(PROJECT_NAME cpp_template)
set(CMAKE_CXX_STANDARD 20)
project(${PROJECT_NAME} C CXX)
message("${BoldGreen}-- ${PROJECT_NAME} BUILD ${ColourReset}")
#---------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/_cmake)
include(options)
#---------------------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/App)
#---------------------
enable_testing()
add_subdirectory(tests)
