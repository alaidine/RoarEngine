#pragma once

#include "Component.h"
#include "ECS.h"
#include "Renderer.h"

namespace Roar {

class RenderSystem : public System {
  public:
    RenderSystem();
    ~RenderSystem();

    void Init();
    void Update(Scene &scene);
};

} // namespace Roar
