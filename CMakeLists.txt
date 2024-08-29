cmake_minimum_required(VERSION 3.22)
#---------------------
if (CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(FATAL_ERROR "-- In-source builds are not allowed.")
endif ()
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
#---------------------
message("${BoldGreen}-- Copy external resources to build folder ${ColourReset}")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/images/logo.png
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/images/morpheus.png
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
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/App/resources)
#---------------------