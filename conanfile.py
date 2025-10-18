from conan import ConanFile
from conan.tools.cmake import cmake_layout
class ImguiHMI(ConanFile):
    name = "imgui-hmi"
    version = "0.1"
    license = "MIT"
    url = "https://github.com/your-repo/imgui-hmi"
    description = "C++ HMI project using ImGui and OpenGL"
    settings = "os", "arch", "compiler", "build_type"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("fakeit/2.4.1")
        self.requires("catch2/3.10.0")
        self.requires("spdlog/1.15.3")
        self.requires("opengl-registry/20240721")
        self.requires("glad/0.1.36")
        self.requires("glm/1.0.1")
        self.requires("glfw/3.4")
        self.requires("stb/cci.20240531")
        #self.requires("sqlite3/3.50.4")
        # self.requires("cppzmq/4.11.0")
        #self.requires("open62541pp/0.17.0")
        #self.requires("libmodbus/3.1.10")
    def build_requirements(self):
        self.tool_requires("cmake/3.27.9")
    # Generators for CMake
    def layout(self):
        # Use cmake-layout
        self.folders.source = "."
        self.folders.build = "build"