#pragma once

#include <memory>

#include "logger.hpp"

// Macro to disable copy and move semantics for a class
#define DISABLE_COPY_AND_MOVE(ClassName)         \
    ClassName(const ClassName&) = delete;        \
    ClassName& operator=(const ClassName&) = delete; \
    ClassName(ClassName&&) noexcept = delete;    \
    ClassName& operator=(ClassName&&) noexcept = delete;

namespace Core {

    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}