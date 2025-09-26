#pragma once

#include "core.hpp"
#include "layer.hpp"

namespace Core::Application {

class ImGuiLayer : public ILayer {
public:
    ~ImGuiLayer() override = default;

    explicit ImGuiLayer() : ILayer("ImGuiLayer") {
        logger.debug("ImGuiLayer created");
    };

    void OnAttach() override {
        logger.debug("ImGuiLayer attached");
    }

    void OnDetach() override {
        logger.debug("ImGuiLayer detached");
    }

    void OnUpdate(double deltaTime_ms) override {
        logger.debug("ImGuiLayer updated: {} ms", deltaTime_ms * 1000.0);
    }

    void OnRender() override {
        logger.debug("ImGuiLayer rendered");
    };
};

}