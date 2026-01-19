#pragma once
#include "Scene.h"
#include "System.h"

extern Scene _core;

class CameraSystem : public System {
  public:
    void Update() override {
        float followSpeed = 0.1f;

        for (auto e : _entities) {
            if (!_core.HasComponent<CameraComponent>(e))
                continue;

            auto &cam = _core.GetComponent<CameraComponent>(e);

            Vector2 diff = {cam.target.x - cam.position.x, cam.target.y - cam.position.y};

            cam.position.x += diff.x * followSpeed;
            cam.position.y += diff.y * followSpeed;

            // sync vers Raylib
            cam.camera.target = cam.position;
            cam.camera.offset = cam.offset;
            cam.camera.zoom = cam.zoom;
            cam.camera.rotation = cam.rotation;

            std::cout << "Cam poisition " << cam.camera.target.x << std::endl;
        }
    }
};

class CameraFollowSystem : public System {
  public:
    void Update() override {
        Entity player = -1;

        // 1) Trouver le joueur (recherche globale)
        auto players = _core.GetEntitiesWith<LocalPlayerTag, Position>();
        if (players.empty())
            return;

        player = *players.begin();
        auto &playerPos = _core.GetComponent<Position>(player);

        // 2) Appliquer la cible aux caméras
        for (auto e : _entities) {
            auto &cam = _core.GetComponent<CameraComponent>(e);
            if (!cam.mainCamera)
                continue;

            cam.target = playerPos.position;
        }
    }
};
