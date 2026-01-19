#pragma once
#include "Component.h"
#include "Scene.h"
#include "System.h"

extern Scene _core;

class GravitySystem : public System {
  public:
    void Update() override {
        float dt = GetFrameTime();

        for (auto const &entity : _entities) {
            auto &pos = _core.GetComponent<Position>(entity);
            auto &gravity = _core.GetComponent<Gravity>(entity);

            pos.position.y += gravity.force * dt;

            if (pos.position.y >= GetScreenHeight() - 50)
                pos.position.y = GetScreenHeight() - 50;
            std::cout << "Gravity system" << std::endl;
        }
    }
};
