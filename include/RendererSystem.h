#pragma once
#include "Keybinds.h"
#include "Scene.h"
#include <raylib.h>

extern Scene _core;

// class PlayerRender

class RendererSystem : public System {
  public:
    CameraComponent *GetMainCamera() {
        auto cameras = _core.GetEntitiesWith<CameraComponent>();

        for (Entity e : cameras) {
            auto &cam = _core.GetComponent<CameraComponent>(e);
            if (cam.mainCamera)
                return &cam;
        }
        return nullptr;
    }

    void Update() override {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);

        CameraComponent *cam = GetMainCamera();
        if (cam) {
            std::cout << "got a cam" << std::endl;
            BeginMode2D(cam->camera);
        }

        for (auto &entity : _entities) {
            if (!_core.HasComponent<Position>(entity) || !_core.HasComponent<Sprite>(entity))
                continue;
            auto &pos = _core.GetComponent<Position>(entity);
            auto &sprite = _core.GetComponent<Sprite>(entity);

            Rectangle src = sprite.source;

            Rectangle dst = {pos.position.x, pos.position.y, src.width * sprite.scale, src.height * sprite.scale};

            Vector2 origin = sprite.origin;
            if (sprite.texture.id == 0)
                DrawRectangleRec(dst, sprite.color);
            else
                DrawTexturePro(sprite.texture, src, dst, origin, sprite.rotation, sprite.color);
            std::cout << "sprite pos x in render system " << pos.position.x << std::endl;
        }

        if (cam)
            EndMode2D();

        for (auto &entity : _entities) {
            if (!_core.HasComponent<Score>(entity))
                continue;
            auto &score = _core.GetComponent<Score>(entity);
            DrawText(TextFormat("Score: %d", score.score), 10, 10, 20, BLACK);
        }

        EndDrawing();
    }
};
