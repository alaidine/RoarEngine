#pragma once

#include "Component.h"
#include "ECS.h"
#include "Renderer.h"

class RenderSystem : public System {
  public:
    RenderSystem();
    ~RenderSystem();

    void Init();
    void Update(Scene &scene, float dt);
};
