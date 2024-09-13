cmake_minimum_required(VERSION 3.22)
#---------------------
if (CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(FATAL_ERROR "-- In-source builds are not allowed.")
endif ()
#---------------------
set(PROJECT_NAME App)
set(CMAKE_CXX_STANDARD 20)
project(${PROJECT_NAME} C CXX)
#---------------------
# define C/CXX flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
message("${BoldGreen}-- CMAKE_C_FLAGS: ${CMAKE_C_FLAGS} ${ColourReset}")
set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})
message("${BoldGreen}-- CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS} ${ColourReset}")
#---------------------
message("${BoldGreen}-- ${PROJECT_NAME} BUILD ${ColourReset}")
#---------------------
add_executable(${PROJECT_NAME}
        main.cpp
        globals.hpp
        backend/glfw.hpp
        backend/glfw.cpp
        imgui/imgui.hpp
        imgui/spec.hpp
        widgets/i_widget.hpp
        widgets/image.hpp
        widgets/button.hpp
        screens/screen_manager.hpp
        screens/i_screen.hpp
        screens/screen_1.hpp
        screens/screen_2.hpp
        screens/screen_3.hpp
        screens/screen_4.hpp
        screens/screen_5.hpp
)
#---------------------
include_directories(
        $ENV{APP_FOLDER}
        $ENV{APP_FOLDER}/backend
        $ENV{APP_FOLDER}/imgui
        $ENV{APP_FOLDER}/screens
        $ENV{APP_FOLDER}/widgets
)
#---------------------
include(core)