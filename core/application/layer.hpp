#pragma once

namespace Core::Application {
class ILayer {
public:
    virtual ~ILayer() = default;
    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;
    virtual void OnUpdate(double deltaTime) = 0;
    virtual void OnRender() = 0;
};
}

