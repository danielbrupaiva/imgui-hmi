#---------------------
# OPEN GL
#---------------------
if (OPENGL3)
    message("${BoldYellow}-- OPENGL3: ${OPENGL3}${ColourReset}")
    if (CROSS_COMPILER)
        message("${BoldYellow}-- CROSS_COMPILER: ${CROSS_COMPILER}${ColourReset}")

        set(GL_INC_DIR ${CMAKE_SYSROOT}/usr/include)
        set(GL_LIB_DIR ${CMAKE_SYSROOT}:${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/:${CMAKE_SYSROOT}/usr:${CMAKE_SYSROOT}/usr/lib)

        set(OPENGL_INCLUDE_DIR ${GL_INC_DIR})
        set(OPENGL_opengl_LIBRARY ${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/libOpenGL.so)
        set(OPENGL_glx_LIBRARY ${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/libGLX.so)

        set(EGL_INCLUDE_DIR ${GL_INC_DIR})
        set(EGL_LIBRARY ${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/libEGL.so)

        set(GLESv2_INCLUDE_DIR ${GL_INC_DIR})
        set(GLIB_LIBRARY ${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/libGLESv2.so)

        set(GLESv2_INCLUDE_DIR ${GL_INC_DIR})
        set(GLESv2_LIBRARY ${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/libGLESv2.so)

        set(Libdrm_INCLUDE_DIR ${GL_INC_DIR})
        set(Libdrm_LIBRARY ${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/libdrm.so)

        set(gbm_INCLUDE_DIR ${GL_INC_DIR})
        set(gbm_LIBRARY ${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/libgbm.so)
    endif ()

    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL)
endif ()