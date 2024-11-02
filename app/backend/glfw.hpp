#pragma once

#include <memory>
#include "spec.hpp"
#include "imgui.h"
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

namespace App
{
class GLFW
{
	// Custom deleter for Window
	struct WindowDeleter
	{
		void operator()(GLFWwindow *window) const
		{
			if (window) { glfwDestroyWindow(window); }
			glfwTerminate();
		};
	};
	std::unique_ptr<GLFWwindow, WindowDeleter> m_window;
	Spec& m_spec;

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
	~GLFW() = default;
	explicit GLFW(Spec &spec)
		: m_window{nullptr}, m_spec{spec}
	{
		init();
	}
	// Prevent copying
	GLFW(const GLFW &) = delete;
	GLFW &operator=(const GLFW &) = delete;

	[[nodiscard]] inline GLFWwindow *get_window() const
	{ return m_window.get(); }
	[[nodiscard]] bool is_close() const
	{ return glfwWindowShouldClose(m_window.get()); };
	inline void close() const
	{ glfwSetWindowShouldClose(m_window.get(), GLFW_TRUE); };

private:
	int8_t init();
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
}