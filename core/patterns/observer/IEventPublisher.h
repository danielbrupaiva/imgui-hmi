//
// Created by daniel on 8/24/25.
//

#pragma once

#include <iostream>
#include <memory>

#include "IEventListener.h"

namespace Core {

    template<typename Event>
    class IEventPublisher {
    public:
        virtual ~IEventPublisher() = default;
        virtual void subscribe(std::string_view topic, std::shared_ptr<IEventListener<Event>> listener) = 0;
        virtual void unsubscribe(std::shared_ptr<IEventListener<Event>> listener) = 0;
        virtual void publish(const Event& event) = 0;
    };

}
