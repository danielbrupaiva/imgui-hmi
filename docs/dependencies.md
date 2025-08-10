[Back](../README.md)
# Dependencies
## Install project dependencies

### OpenGL

### Vulkan 
    
      $ sudo apt install -y libvulkan1 mesa-vulkan-drivers vulkan-tools vulkan-validationlayers-dev spirv-tools
      $ git clone https://github.com/KhronosGroup/Vulkan-Headers.git
      $ cd Vulkan-Headers
      $ cmake -S . -B build && cmake --build build && sudo cmake --install build

### [GLFW3](https://www.glfw.org/docs/3.3/build_guide.html)

        $ cd ~  
        $ git clone -b 3.3-stable https://github.com/glfw/glfw.git
        $ cd glfw
        $ cmake -S . -B build && cmake --build build && sudo cmake --install build

### [POSTGRESQL](postgresql.md)

### PQXX (NOTE install postgres first)

    $ git clone -b 7.8.1 https://github.com/jtv/libpqxx.git
    $ cd libpqxx
    $ sudo su
    $ cmake -S . -B build -DCMAKE_CXX_STANDARD=20 -DBUILD_DOC=OFF -DBUILD_TEST=OFF -DSKIP_BUILD_TEST=ON
    $ cmake --build build
    $ sudo cmake --install build

### SPDLOG

    $ git clone -b v1.13.0 https://github.com/gabime/spdlog.git
    $ cd spdlog
    $ sudo su
    $ cmake -S . -B build
    $ cmake --build build
    $ sudo cmake --install build

### CATCH2

    $ git clone -b v3.4.0 https://github.com/catchorg/Catch2.git
    $ cd Catch2
    $ sudo su
    $ cmake -S . -B build
    $ cmake --build build
    $ sudo cmake --install build

### LIBMODBUS
  
    $ git clone -b v3.1.10 --recursive https://github.com/stephane/libmodbus.git
    $ cd libmodbus
    $ sudo ./autogen.sh
    $ sudo ./configure 
    $ sudo make install    
