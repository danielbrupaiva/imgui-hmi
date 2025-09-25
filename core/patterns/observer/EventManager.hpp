//
// Created by daniel on 8/24/25.
//

#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <mutex>
#include <atomic>
#include <algorithm>

#include "IEventPublisher.hpp"

namespace Core {

    template<typename EventType>
    class EventManager : public IEventPublisher<EventType> {
    public:
        void subscribe(std::shared_ptr<IEventListener<EventType>> listener)  {
            std::lock_guard<std::mutex> lock(mutex);
            listeners.emplace_back(listener);
        }

        void unsubscribe(std::shared_ptr<IEventListener<EventType>> listener) override {
            std::lock_guard<std::mutex> lock(mutex);

            if (!listener) throw std::invalid_argument("Listener cannot be null");

            std::erase_if(listeners, [&listener](const std::weak_ptr<IEventListener<EventType>>& wptr) {
                auto sptr = wptr.lock();
                return !sptr || sptr == listener;
            });
        }

        void publish(const EventType& event) override {
            std::lock_guard<std::mutex> lock(mutex);
            std::for_each(listeners.begin(),
                          listeners.end(),
                          [&event](const std::weak_ptr<IEventListener<EventType>>& wptr) {
                              auto sptr = wptr.lock();
                              if (!sptr) {
                                  throw std::runtime_error("Expired listener found during publish");
                              }
                              sptr->onEvent(event);
                          });
        }

    private:
        std::vector<std::weak_ptr<IEventListener<EventType>>> listeners;
        std::mutex mutex;
    };

} // Core

