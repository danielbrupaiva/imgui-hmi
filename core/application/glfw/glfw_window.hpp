#pragma once

#include "core.hpp"
#include "window.hpp"

#include "glfw_error_handler.hpp"
#include "glfw_window_hint.hpp"

//https://www.glfw.org/documentation.html
//https://www.glfw.org/docs/latest/window_guide.html
namespace Core::Application {
class GLFW : public IWindow {
public:
	~GLFW() {
        Destroy();
    };

    explicit GLFW(const WindowSpecification& specification = WindowSpecification())
        : m_handle{nullptr}, m_specification{specification} {
    }

    DISABLE_COPY_AND_MOVE(GLFW);

	[[nodiscard]] inline GLFWwindow* get_window() const
	{ return m_handle; }

    void Destroy() final {
        if (m_handle) {
            glfwDestroyWindow(m_handle);
        }
        m_handle = nullptr;
        logger.debug("GLFW window destroyed");
    }

    void Update() final {
        glfwSwapBuffers(m_handle);
    }

    [[nodiscard]] bool ShouldClose() const final {
        return glfwWindowShouldClose(m_handle) != 0;
    }

    void Close() final {
        glfwSetWindowShouldClose(m_handle, GLFW_TRUE);
    };

    bool Create() final {

        m_handle = glfwCreateWindow(m_specification.width,
                                    m_specification.height,
                                    m_specification.title.c_str(),
                                    m_specification.fullscreen ? glfwGetPrimaryMonitor() : nullptr,
                                    nullptr);

        if (nullptr == m_handle) { throw Error("GLFW window not created"); }

        glfwMakeContextCurrent(m_handle);

        glfwSwapInterval(m_specification.vsync ? 1 : 0); // Enable vsync

        return true;
    }

    glm::vec2 GetFramebufferSize() override {
        int width, height;
        glfwGetFramebufferSize(m_handle, &width, &height);
        return { width, height };
    };

    [[nodiscard]] inline const WindowSpecification &GetSpecification() const { return m_specification; }

private:

    GLFWwindow* m_handle;
    WindowSpecification m_specification;
};
}