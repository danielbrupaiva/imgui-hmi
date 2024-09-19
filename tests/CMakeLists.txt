cmake_minimum_required(VERSION 3.11)
#---------------------
set(PROJECT_NAME tests)
project(${PROJECT_NAME} LANGUAGES CXX)
#---------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#---------------------
if (CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(FATAL_ERROR "-- In-source builds are not allowed.")
endif ()
#---------------------
set(SOURCES
        main.cpp
        tc_utils_math.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})
#---------------------
include_directories(
        $ENV{APP_FOLDER}
)
include(core)
#---------------------
include(catch2)
#---------------------
include(fakeit)