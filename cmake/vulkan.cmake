#---------------------
# Vulkan
#---------------------
if (VULKAN)
    message("${BoldYellow}-- VULKAN: ${VULKAN}${ColourReset}")
    if (CROSS_COMPILER)
        message("${BoldYellow}-- CROSS_COMPILER: ${CROSS_COMPILER}${ColourReset}")
    endif ()
    find_package(VulkanHeaders REQUIRED CONFIG)
    message(STATUS "Vulkan Headers Version: ${VulkanHeaders_VERSION}")
    target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Headers)
    find_package(Vulkan REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan)
endif ()