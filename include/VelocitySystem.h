#pragma once
#include "Scene.h"
#include "System.h"
#include "raylib.h"

extern Scene _core;

class VelocitySystem : public System {
  public:
    void Update() override {
        float dt = GetFrameTime();

        for (auto const &entity : _entities) {
            auto &pos = _core.GetComponent<Position>(entity);
            auto &v = _core.GetComponent<Velocity>(entity);
            pos.position.x += v.velocity.x * dt;
            pos.position.y += v.velocity.x * dt;
        }
    }
};
