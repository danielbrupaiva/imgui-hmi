#pragma once

#include "core.hpp"
#include "application.hpp"

class ImGuiHMI : public Core::Application::Application {
public:
    ~ImGuiHMI() override = default;
    explicit ImGuiHMI(const Core::Application::ApplicationSpecification& specification = Core::Application::ApplicationSpecification())
            : Application(specification) {
        logger.debug("IMGUI HMI Application created");
    }

    void Run() override {
        Application::Run();
    }

    void Stop() override {
        Application::Stop();
    }

    void OnUpdate(float ts) override {
        Application::OnUpdate(ts);
    }

    void OnRender() override {
        Application::OnRender();
    }
};