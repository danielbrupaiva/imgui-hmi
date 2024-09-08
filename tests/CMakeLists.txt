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
        tc_image.cpp
        tc_button.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})
#---------------------
include(FetchContent)
#---------------------
FetchContent_Declare(Catch2                                     # name of the content
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git   # the repository
        GIT_TAG v3.4.0                                   # the tag
)
FetchContent_MakeAvailable(Catch2)
FetchContent_GetProperties(Catch2)
#---------------------
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(${PROJECT_NAME})
#---------------------
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain)
include(core)

#---------------------
message("${BoldGreen}-- Copy external resources to build folder ${ColourReset}")
file(COPY $ENV{RESOURCES_FOLDER}/images/morpheus.jpg
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)
#---------------------