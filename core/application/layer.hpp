#pragma once

namespace Core::Application {
class ILayer {
public:
    virtual ~ILayer() = default;
    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;
    virtual void OnUpdate(float deltaTime) = 0;
    virtual void OnRender() = 0;
};
}

