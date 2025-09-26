#pragma once

#include "core.hpp"
#include "application.hpp"

class ImGuiHMI : public Core::Application::OpenGLApplication, public std::enable_shared_from_this<ImGuiHMI> {
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

    void OnUpdate(double deltaTime_ms) override {
        OpenGLApplication::OnUpdate(deltaTime_ms);
    }

    void OnRender() override {
        OpenGLApplication::OnRender();
    }

    static std::shared_ptr<ImGuiHMI> CreateApplication(const Core::Application::ApplicationSpecification& specification = Core::Application::ApplicationSpecification()) {
        return std::make_shared<ImGuiHMI>(specification);
    }

    std::shared_ptr<ImGuiHMI> Get() {  return this->shared_from_this(); }
};