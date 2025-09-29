# Prevent multiple inclusion
if(NOT DEFINED CROSS_COMPILER)
  set(CROSS_COMPILER ON)
  message("${BoldYellow}-- TOOLCHAIN LOADED${ColourReset}")
  option(CROSS_COMPILER "Enable cross compiler?" ON)
  message("${BoldYellow}-- CROSS COMPILE: ${CROSS_COMPILER} ${ColourReset}")

  set(CMAKE_SYSTEM_NAME Linux)
  set(CMAKE_SYSTEM_PROCESSOR aarch64)
  # Force standard to avoid missing feature detection
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS ON)
  # Don’t try to run target binaries on the host
  set(CMAKE_CROSSCOMPILING TRUE)
  set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
  # define target sysroot
  set(TARGET_SYSROOT $ENV{SYSROOTS_FOLDER}/rpi4})
  message("${BoldGreen}-- TARGET_SYSROOT: ${TARGET_SYSROOT} ${ColourReset}")
  set(CMAKE_SYSROOT ${TARGET_SYSROOT})
  message("${BoldGreen}-- CMAKE_SYSROOT: ${CMAKE_SYSROOT} ${ColourReset}")
  # define compiler work (used by custom toolchain)
  set(TARGET_ARCHITECTURE aarch64-linux-gnu)
  message("${BoldGreen}-- TARGET_ARCHITECTURE: ${TARGET_ARCHITECTURE} ${ColourReset}")
  set(CMAKE_C_COMPILER_WORKS ON)
  set(CMAKE_C_COMPILER /usr/bin/${TARGET_ARCHITECTURE}-gcc)
  message("${BoldGreen}-- CMAKE_C_COMPILER: ${CMAKE_C_COMPILER} ${ColourReset}")
  set(CMAKE_CXX_COMPILER_WORKS ON)
  set(CMAKE_CXX_COMPILER /usr/bin/${TARGET_ARCHITECTURE}-g++)
  message("${BoldGreen}-- CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER} ${ColourReset}")
  # define C/CXX flags
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${CMAKE_SYSROOT}/usr/include -I${CMAKE_SYSROOT}/usr/lib -I${CMAKE_SYSROOT}/usr/include/${TARGET_ARCHITECTURE} -I${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}")
  message("${BoldGreen}-- CMAKE_C_FLAGS: ${CMAKE_C_FLAGS} ${ColourReset}")
  set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})
  message("${BoldGreen}-- CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS} ${ColourReset}")
  #set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}")
  #message("${BoldGreen}-- CMAKE_EXE_LINKER_FLAGS: ${CMAKE_EXE_LINKER_FLAGS} ${ColourReset}")
  #set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
  #set(CMAKE_MODULE_LINKER_FLAGS "")
  set(CMAKE_SHARED_LINKER_FLAGS "")
  set(CMAKE_MODULE_LINKER_FLAGS "")
  set(CMAKE_EXE_LINKER_FLAGS "")

  find_package(PkgConfig REQUIRED)
  # Set environment variables for pkg-config
  set(ENV{PKG_CONFIG_SYSROOT_DIR} ${CMAKE_SYSROOT})
  message("${BoldGreen}-- PKG_CONFIG_SYSROOT_DIR: $ENV{PKG_CONFIG_SYSROOT_DIR} ${ColourReset}")

  set(ENV{PKG_CONFIG_LIBDIR} ${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu/pkgconfig)
  message("${BoldGreen}-- PKG_CONFIG_LIBDIR: $ENV{PKG_CONFIG_LIBDIR} ${ColourReset}")

  set(ENV{PKG_CONFIG_PATH} "${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/pkgconfig")
  message("${BoldGreen}-- PKG_CONFIG_PATH: $ENV{PKG_CONFIG_PATH} ${ColourReset}")

  set(QT_COMPILER_FLAGS "-march=armv8-a -mabi=lp64")
  set(QT_COMPILER_FLAGS_RELEASE "-O2 -pipe -DNDEBUG")
  set(QT_LINKER_FLAGS "-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed")

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

  set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
  set(CMAKE_BUILD_RPATH ${TARGET_SYSROOT})

  include(CMakeInitializeConfigs)

  function(cmake_initialize_per_config_variable _PREFIX _DOCSTRING)
    if (_PREFIX MATCHES "CMAKE_(C|CXX|ASM)_FLAGS")
      set(CMAKE_${CMAKE_MATCH_1}_FLAGS_INIT "${QT_COMPILER_FLAGS}")

      foreach (config DEBUG RELEASE MINSIZEREL RELWITHDEBINFO)
        if (DEFINED QT_COMPILER_FLAGS_${config})
          set(CMAKE_${CMAKE_MATCH_1}_FLAGS_${config}_INIT "${QT_COMPILER_FLAGS_${config}}")
        endif()
      endforeach()
    endif()


    if (_PREFIX MATCHES "CMAKE_(SHARED|MODULE|EXE)_LINKER_FLAGS")
      foreach (config SHARED MODULE EXE)
        set(CMAKE_${config}_LINKER_FLAGS_INIT "${QT_LINKER_FLAGS}")
      endforeach()
    endif()

    _cmake_initialize_per_config_variable(${ARGV})
  endfunction()


  set(X11_X11_LIB ${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/libX11.so)
  set(X11_LIBRARIES ${X11_X11_LIB})
  set(X11_X11_INCLUDE_PATH ${CMAKE_SYSROOT}/usr/include/X11)

  set(X11_XCB_INCLUDE_PATH ${CMAKE_SYSROOT}/usr/include/X11)
  set(X11_XCB_LIB ${CMAKE_SYSROOT}/usr/lib/${TARGET_ARCHITECTURE}/libX11-xcb.so)

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

  set(Wayland_FOUND TRUE)
  set(Wayland_CLIENT_INCLUDE_DIR ${CMAKE_SYSROOT}/usr/include)
  set(Wayland_CLIENT_LIBRARY ${CMAKE_SYSROOT}/usr/lib/aarch64-linux-gnu/libwayland-client.so)

endif()