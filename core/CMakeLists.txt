cmake_minimum_required(VERSION 3.11)
#---------------------
if (CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(FATAL_ERROR "-- In-source builds are not allowed.")
endif ()
#---------------------
set(PROJECT_NAME core)
project(${PROJECT_NAME} LANGUAGES CXX)
#---------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#---------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
#---------------------
set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/core.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/application/glfw/glfw.cpp
)
#---------------------
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/backend
        ${CMAKE_CURRENT_SOURCE_DIR}/database
        ${CMAKE_CURRENT_SOURCE_DIR}/application
        ${CMAKE_CURRENT_SOURCE_DIR}/application/glfw
        ${CMAKE_CURRENT_SOURCE_DIR}/application/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/network
        ${CMAKE_CURRENT_SOURCE_DIR}/patterns
        ${CMAKE_CURRENT_SOURCE_DIR}/utils
)
#---------------------
add_library(${PROJECT_NAME} STATIC
        core.hpp
        core.cpp
)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/application
        ${CMAKE_CURRENT_SOURCE_DIR}/application/glfw
        ${CMAKE_CURRENT_SOURCE_DIR}/application/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/database
        ${CMAKE_CURRENT_SOURCE_DIR}/network
        ${CMAKE_CURRENT_SOURCE_DIR}/patterns
        ${CMAKE_CURRENT_SOURCE_DIR}/utils
)
#---------------------

include(IMGUI)

find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

find_package(SQLite3 REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC SQLite::SQLite3)

include(bcrypt)
#---------------------