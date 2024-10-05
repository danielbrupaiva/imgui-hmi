#---------------------
# GLFW
#---------------------
if (GLFW)
    message("${BoldYellow}-- GLFW: ${GLFW}${ColourReset}")
    if (NOT BUILD_FROM_SRC)
        find_package(glfw3 REQUIRED)
    elseif (NOT glfw3_FOUND OR BUILD_FROM_SRC)
        message("${BoldYellow}-- GLFW NOT FOUND${ColourReset}")
        message("${BoldYellow}-- BUILDING FROM SRC${ColourReset}")
        set(GLFW_VULKAN_STATIC ON CACHE BOOL "" FORCE)
        set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_WAYLAND ON CACHE BOOL "" FORCE)

        FetchContent_Declare(
                glfw
                GIT_REPOSITORY https://github.com/glfw/glfw.git
                GIT_TAG 3.4
        )
        FetchContent_MakeAvailable(glfw)
        FetchContent_GetProperties(glfw)
    endif ()
    target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
endif ()