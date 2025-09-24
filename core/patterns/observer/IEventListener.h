//
// Created by daniel on 8/24/25.
//
#pragma once

namespace Core {
    template<typename Event>
    class IEventListener {
    public:
        virtual ~IEventListener() = default;
        virtual void onEvent(const Event& event) = 0;
    };

} // Core
