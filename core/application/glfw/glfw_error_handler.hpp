#pragma once

#include <iostream>
#include <cassert>

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

namespace Core::Application {

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

    /*
    * Error types
    * */
    GLFWPP_ERROR_CLASS(Error, std::runtime_error);
    GLFWPP_ERROR_CLASS(APIUnavailableError, Error);
    GLFWPP_ERROR_CLASS(VersionUnavailableError, Error);
    GLFWPP_ERROR_CLASS(PlatformError, Error);
    GLFWPP_ERROR_CLASS(FormatUnavailableError, Error);

    /*
    * ErrorHandler
    * Code from glfwpp lib at glfwpp/error.h
    * */
    static void glfw_error_callback(int errorCode_, const char *what_) {
        // Error handling philosophy as per http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2019/p0709r4.pdf (section 1.1)

        // Application programmer errors. See the GLFW docs and fix the code.
        assert(errorCode_ != GLFW_NOT_INITIALIZED);
        assert(errorCode_ != GLFW_NO_CURRENT_CONTEXT);
        assert(errorCode_ != GLFW_NO_WINDOW_CONTEXT);
        assert(errorCode_ != GLFW_INVALID_VALUE);

        // These errors should never occur
    #if GLFW_VERSION_MAJOR >= 3 && GLFW_VERSION_MINOR >= 3
        assert(errorCode_ != GLFW_NO_ERROR);
    #endif
        assert(errorCode_ != GLFW_INVALID_ENUM);

        // Allocation failure must be treated separately
        if (errorCode_ == GLFW_OUT_OF_MEMORY) {
            throw std::bad_alloc();
        }

        switch (errorCode_) {
            case GLFW_API_UNAVAILABLE:
                throw APIUnavailableError(what_);
            case GLFW_VERSION_UNAVAILABLE:
                throw VersionUnavailableError(what_);
            case GLFW_PLATFORM_ERROR:
                throw PlatformError(what_);
            case GLFW_FORMAT_UNAVAILABLE:
                throw FormatUnavailableError(what_);
            default:
                // There should be no other error possible
                assert(false);
        }
    };
}