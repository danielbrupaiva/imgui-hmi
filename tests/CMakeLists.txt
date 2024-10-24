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
        #        tc_image.cpp
        tc_utils_math.cpp
        tc_button.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})
#---------------------
include_directories(
        $ENV{APP_FOLDER}
        $ENV{APP_FOLDER}/widgets
        $ENV{APP_FOLDER}/screens
        $ENV{APP_FOLDER}/imgui
        $ENV{APP_FOLDER}/backend
)
include(core)
#---------------------
include(catch2)
#---------------------
include(fakeit)
#---------------------
message("${BoldGreen}-- Copy external resources to build folder ${ColourReset}")
message("${BoldGreen}-- Resources folder: ${CMAKE_CURRENT_BINARY_DIR}/resources ${ColourReset}")

file(COPY $ENV{RESOURCES_FOLDER}/images/morpheus.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)
#---------------------
