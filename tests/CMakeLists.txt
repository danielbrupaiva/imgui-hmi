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
        tc_sqlite.cpp
        tc_uuid.cpp
        tc_user_manager.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})
#---------------------
include(core)
#---------------------
find_package(Catch2)
target_link_libraries(${PROJECT_NAME} PUBLIC Catch2::Catch2WithMain)
#---------------------
find_package(fakeit)
target_link_libraries(${PROJECT_NAME} PUBLIC fakeit::fakeit)
#---------------------
message("${BoldGreen}-- Copy external resources to build folder ${ColourReset}")
message("${BoldGreen}-- Resources folder: ${CMAKE_CURRENT_BINARY_DIR}/resources ${ColourReset}")

file(COPY $ENV{RESOURCES_FOLDER}/images/morpheus.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)
#---------------------
