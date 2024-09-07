cmake_minimum_required(VERSION 3.22)
#---------------------
if (CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(FATAL_ERROR "-- In-source builds are not allowed.")
endif ()
#---------------------
set(PROJECT_NAME Core)
project(${PROJECT_NAME} C CXX)
message("${BoldGreen}-- ${PROJECT_NAME} BUILD ${ColourReset}")
#---------------------
set(SOURCES
        logger.hpp
        utils.hpp
        spec.hpp
        glfw.hpp glfw.cpp
        imgui.hpp
        widgets/i_widget.hpp
        widgets/image.hpp
)
#---------------------
add_library(${PROJECT_NAME} STATIC
        widgets/button.hpp)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#---------------------
include(spdlog)
include(IMGUI)
include(stb)
#---------------------