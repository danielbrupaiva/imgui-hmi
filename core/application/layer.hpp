#pragma once

#include "application.hpp"

namespace Core::Application {

class OpenGLApplication;

class ILayer {
public:
    virtual ~ILayer() = default;
    explicit ILayer(std::string_view tagName = "Layer") : m_tagName(tagName) {}
    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;
    virtual void OnUpdate(double deltaTime_ms) = 0;
    virtual void OnRender() = 0;

    [[nodiscard]] const std::string& GetName() const { return m_tagName; }

private:
    std::string m_tagName;
};
}

