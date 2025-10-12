if(NOT DEFINED CROSS_COMPILER)
    set(CROSS_COMPILER ON)
    message("${BoldYellow}-- TOOLCHAIN LOADED${ColourReset}")
    option(CROSS_COMPILER "Enable cross compiler?" ON)
    message("${BoldYellow}-- CROSS COMPILE: ${CROSS_COMPILER} ${ColourReset}")

    set(CMAKE_SYSTEM_NAME Linux)
    set(CMAKE_SYSTEM_PROCESSOR arm)
    # define target sysroot
    # set ssysroots folder getting form eviroment variable
    set(TARGET_SYSROOT /opt/sysroots/beagleplay)
    message("${BoldGreen}-- TARGET_SYSROOT: ${TARGET_SYSROOT} ${ColourReset}")
    set(CMAKE_SYSROOT ${TARGET_SYSROOT})
    message("${BoldGreen}-- CMAKE_SYSROOT: ${CMAKE_SYSROOT} ${ColourReset}")
    # define compiler work (used by custom toolchain)
    set(TARGET_ARCHITECTURE aarch64-linux-gnu)
    message("${BoldGreen}-- TARGET_ARCHITECTURE: ${TARGET_ARCHITECTURE} ${ColourReset}")
    set(CMAKE_C_COMPILER_WORKS ON)
    set(CMAKE_C_COMPILER /opt/toolchains/aarch64-none-linux-gnu-12.3/bin/aarch64-none-linux-gnu-gcc)
    message("${BoldGreen}-- CMAKE_C_COMPILER: ${CMAKE_C_COMPILER} ${ColourReset}")
    set(CMAKE_CXX_COMPILER_WORKS ON)
    set(CMAKE_CXX_COMPILER /opt/toolchains/aarch64-none-linux-gnu-12.3/bin/aarch64-none-linux-gnu-g++)
    message("${BoldGreen}-- CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER} ${ColourReset}")
    # define C/CXX flags
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${CMAKE_SYSROOT}/usr/include -I${CMAKE_SYSROOT}/usr/lib -I${CMAKE_SYSROOT}/usr/include/${TARGET_ARCHITECTURE} -I${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}")
    message("${BoldGreen}-- CMAKE_C_FLAGS: ${CMAKE_C_FLAGS} ${ColourReset}")
    set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})
    message("${BoldGreen}-- CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS} ${ColourReset}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}")
    message("${BoldGreen}-- CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS} ${ColourReset}")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

    find_package(PkgConfig REQUIRED)
    # Set environment variables for pkg-config
    set(ENV{PKG_CONFIG_SYSROOT_DIR} ${CMAKE_SYSROOT})
    message("${BoldGreen}-- PKG_CONFIG_SYSROOT_DIR: $ENV{PKG_CONFIG_SYSROOT_DIR} ${ColourReset}")

    set(ENV{PKG_CONFIG_LIBDIR} ${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu/pkgconfig)
    message("${BoldGreen}-- PKG_CONFIG_LIBDIR: $ENV{PKG_CONFIG_LIBDIR} ${ColourReset}")

    set(ENV{PKG_CONFIG_PATH} "${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/pkgconfig")
    message("${BoldGreen}-- PKG_CONFIG_PATH: $ENV{PKG_CONFIG_PATH} ${ColourReset}")

    # where is the target environment located
    set(CMAKE_FIND_ROOT_PATH ${CMAKE_SYSROOT})
    # adjust the default behavior of the FIND_XXX() commands:
    # search for programs in the build host directories
    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    # search headers and libraries in the target environment
    # for libraries and headers in the target directories
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

    set(THREADS_PTHREAD_ARG "2" CACHE STRING "" FORCE)
    set(CMAKE_THREAD_LIBS_INIT "-lpthread")
    set(CMAKE_HAVE_THREADS_LIBRARY ON)
    set(CMAKE_USE_WIN32_THREADS_INIT OFF)
    set(CMAKE_USE_PTHREADS_INIT ON)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    set(Threads_FOUND TRUE)

    set(X11_LIBRARIES ${X11_X11_LIB})
    set(X11_X11_INCLUDE_PATH ${CMAKE_SYSROOT}/usr/include/X11)
    set(X11_X11_LIB ${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/libX11.so)

    set(GL_INC_DIR ${CMAKE_SYSROOT}/usr/include)
    set(GL_LIB_DIR ${CMAKE_SYSROOT}:${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/:${CMAKE_SYSROOT}/usr:${CMAKE_SYSROOT}/usr/lib)

    set(OPENGL_INCLUDE_DIR ${GL_INC_DIR})
    set(OPENGL_opengl_LIBRARY ${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/libOpenGL.so)
    set(OPENGL_glx_LIBRARY ${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/libGLX.so)

    set(EGL_INCLUDE_DIR ${GL_INC_DIR})
    set(EGL_LIBRARY ${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/libEGL.so)

    set(GLESv2_INCLUDE_DIR ${GL_INC_DIR})
    set(GLESv2_LIBRARY ${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/libGLESv2.so)
    set(GLIB_LIBRARY ${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/libGLESv2.so)

    set(Libdrm_INCLUDE_DIR ${GL_INC_DIR})
    set(Libdrm_LIBRARY ${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/libdrm.so)

    set(gbm_INCLUDE_DIR ${GL_INC_DIR})
    set(gbm_LIBRARY ${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/libgbm.so)

endif()