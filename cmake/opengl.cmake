#---------------------
# OPEN GL
#---------------------
if (OPENGL3)
    message("${BoldYellow}-- OPENGL3: ${OPENGL3}${ColourReset}")
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL)
endif ()