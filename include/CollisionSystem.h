#pragma once
#include "Scene.h"
#include "System.h"

extern Scene _core;

void check_map_collision(Position &pos, Collider &collider) {
    float screenW = (float)GetScreenWidth();
    float screenH = (float)GetScreenHeight();

    if (pos.position.x + collider.rect.width > screenW)
        pos.position.x = screenW - collider.rect.width;

    if (pos.position.x <= 0)
        pos.position.x = 0;

    if (pos.position.y + collider.rect.height > screenH)
        pos.position.y = screenH - collider.rect.height;

    if (pos.position.y <= 0)
        pos.position.y = 0;

    collider.rect.x = pos.position.x;
    collider.rect.y = pos.position.y;
}

void handleCollision(Entity a, Entity b, Collider &colA, Collider &colB) {
    if ((colA.layer == LAYER_PLAYER && colB.layer == LAYER_ENEMY) || (colB.layer == LAYER_PLAYER && colA.layer == LAYER_ENEMY))
        std::cout << "Player hit enemy" << std::endl;

    if ((colA.layer == LAYER_PLAYER && colB.layer == LAYER_WORLD))
        std::cout << "do something" << std::endl;
    if ((colA.layer == LAYER_PIECE && colB.layer == LAYER_PLAYER)) {
        _core.DestroyEntity(a);
        return;
    }
}

class CollisionSystem : public System {
  public:
    void Update() override {
        for (Entity entity : _entities) {
            auto &pos = _core.GetComponent<Position>(entity);
            auto &collider = _core.GetComponent<Collider>(entity);

            collider.rect.x = pos.position.x;
            collider.rect.y = pos.position.y;

            if (collider.layer & LAYER_PLAYER)
                check_map_collision(pos, collider);
        }

        for (auto itA = _entities.begin(); itA != _entities.end(); ++itA) {
            auto itB = itA;
            ++itB;

            for (; itB != _entities.end(); ++itB) {
                Entity a = *itA;
                Entity b = *itB;

                auto &colA = _core.GetComponent<Collider>(a);
                auto &colB = _core.GetComponent<Collider>(b);

                if ((colA.mask & colB.layer) == 0 && (colB.mask & colA.layer) == 0)
                    continue;
                DrawRectangleRec(colA.rect, PINK);
                DrawRectangleRec(colB.rect, BLACK);
                if (CheckCollisionRecs(colA.rect, colB.rect)) {
                    handleCollision(a, b, colA, colB);
                }
            }
        }
    }
};
