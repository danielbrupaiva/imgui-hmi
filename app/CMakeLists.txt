cmake_minimum_required(VERSION 3.22)
#---------------------
if (CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(FATAL_ERROR "-- In-source builds are not allowed.")
endif ()
#---------------------
set(PROJECT_NAME imgui-hmi)
project(${PROJECT_NAME} LANGUAGES CXX)
#---------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
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
        screens/screen_manager.hpp
        screens/screen_1.hpp
        screens/screen_2.hpp
        screens/screen_3.hpp
        screens/screen_4.hpp
        screens/screen_5.hpp
)
#---------------------
include_directories(
        $ENV{APP_FOLDER}
        $ENV{APP_FOLDER}/screens
)
#---------------------
include(core)
#---------------------
# TODO: add compile option at cmake option during compilation (the hash bellow is a dev hash key only)
add_compile_definitions(HASH="5fe11e9cfd6b6d1013865f687d0891bac8083ddfcdb83a5fcad89c2ed67b555e")

#---------------------
message("${BoldGreen}-- Copy external resources to build folder ${ColourReset}")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/images/logo.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/images/morpheus.jpg
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/images/tux.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/profile.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/restricted_person.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/verify_person.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/maintenance_person.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/add_person.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/delete_person.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/view.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/hidden.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/login.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/logout.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/hammer.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/hammer_cristal.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/hammer_red.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/close_reject.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/warning.png
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/danger.png
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources)
#---------------------