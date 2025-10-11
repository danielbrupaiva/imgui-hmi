from conan import ConanFile

class ImguiHMI(ConanFile):
    name = "imgui-hmi"
    version = "0.1"
    license = "MIT"
    url = "https://github.com/your-repo/imgui-hmi"
    description = "C++ HMI project using ImGui and OpenGL"
    settings = "os", "arch", "compiler", "build_type"

    # Dependencies
    requires = [
        # "opengl/system",
        "fakeit/2.4.1",
        "catch2/3.10.0",
        "spdlog/1.15.3",
        "glad/0.1.36",
        "glm/1.0.1",
        "glfw/3.4",
        "stb/cci.20240531",
        "sqlite3/3.50.4",
        "cppzmq/4.11.0",
        "open62541pp/0.17.0",
        "libmodbus/3.1.10"
    ]

    # Generators for CMake
    generators = "CMakeDeps", "CMakeToolchain"

    def layout(self):
        # Use cmake-layout
        self.folders.source = "."
        self.folders.build = "build"

    def build(self):
        # For clarity, specify paths for OpenGL in sysroot
        opengl_include = "/opt/sysroots/beagleplay/usr/include"
        opengl_lib = "/opt/sysroots/beagleplay/usr/lib"

        self.output.info(f"Using OpenGL includes: {opengl_include}")
        self.output.info(f"Using OpenGL libs: {opengl_lib}")

    def system_requirements(self):
        # Skip all system package installation
        self.output.info("Skipping opengl/system installation, using sysroot")
