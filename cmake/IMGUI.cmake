option(OPENGL3 "OPENGL3" ON)
message("${BoldYellow}-- OPENGL3: ${OPENGL3}${ColourReset}")
#---------------------
option(VULKAN "VULKAN" OFF)
message("${BoldYellow}-- VULKAN: ${VULKAN}${ColourReset}")
#---------------------
option(GLFW "GLFW" ON)
message("${BoldYellow}-- GLFW: ${GLFW}${ColourReset}")
#---------------------
include(FetchContent)
#---------------------
FetchContent_Declare(
        imgui
#        SOURCE_DIR $ENV{VENDOR_FOLDER}/imgui
        GIT_REPOSITORY https://github.com/danielbrupaiva/imgui.git
        GIT_TAG cmake_v1.91.9b
)
FetchContent_MakeAvailable(imgui)
FetchContent_GetProperties(imgui)
#---------------------
target_link_libraries(${PROJECT_NAME} PUBLIC imgui)