#pragma once

#include "core.hpp"
#include "application.hpp"

class ImGuiHMI : public Core::Application::OpenGLApplication {
public:
    ~ImGuiHMI() = default;
    explicit ImGuiHMI(const Core::Application::ApplicationSpecification& specification = Core::Application::ApplicationSpecification())
            : OpenGLApplication(specification) {
        logger.debug("IMGUI HMI Application created");
    }

    void Run() override {
        OpenGLApplication::Run();
    }

    void Stop() override {
        OpenGLApplication::Stop();
    }

    void Update(double deltaTime_ms) override {
        OpenGLApplication::Update(deltaTime_ms);
    }

    void Render() override {
        OpenGLApplication::Render();
    }

};