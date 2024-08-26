#pragma once

#include <memory>
#include "spec.hpp"
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

namespace App{

class GLFW : public std::enable_shared_from_this<GLFW> {

    Spec& m_spec;
    GLFWwindow* m_window;

    /*
     * WindowHints
     * Code from glfwpp lib at glfwpp/windows.h
     * */
    static constexpr int dontCare = GLFW_DONT_CARE;
    enum class ClientApi;
    enum class ContextCreationApi;
    enum class ContextRobustness;
    enum class ContextReleaseBehavior;
    enum class OpenGlProfile;

    struct WindowHints;

public:
    ~GLFW(){
        shutdown();
    }
    explicit GLFW(App::Spec& spec): m_spec{spec}, m_window{nullptr}
    {
        init();
    }
    // Prevent copying
    GLFW(const GLFW &) = delete;
    explicit GLFW(const GLFWwindow &mWindow);
    GLFW &operator=(const GLFW &) = delete;

    std::shared_ptr<GLFW> get() { return shared_from_this(); };

    [[nodiscard]] inline GLFWwindow* get_window() const { return m_window; }
    inline bool is_close() { return glfwWindowShouldClose(m_window); };
    inline void close() { glfwSetWindowShouldClose(m_window, GLFW_TRUE); };

private:
    int8_t init();
    void shutdown();
    static void glfw_error_callback(int errorCode_, const char *what_);

    /*
     * ErrorHandler
     * Code from glfwpp lib at glfwpp/error.h
     * */
#define GLFWPP_ERROR_CLASS(NAME, BASE)                \
    class NAME : public BASE                          \
    {                                                 \
    public:                                           \
        explicit NAME(const char* message) noexcept : \
            BASE(message) {}                          \
                                                      \
        const char* what() const noexcept             \
        {                                             \
            return BASE::what();                      \
        }                                             \
    };

    GLFWPP_ERROR_CLASS(Error, std::runtime_error);
    GLFWPP_ERROR_CLASS(APIUnavailableError, Error);
    GLFWPP_ERROR_CLASS(VersionUnavailableError, Error);
    GLFWPP_ERROR_CLASS(PlatformError, Error);
    GLFWPP_ERROR_CLASS(FormatUnavailableError, Error);

};

} //App namespace