#include "RenderSystem.h"
#include "Renderer.h"

RenderSystem::RenderSystem() {}

RenderSystem::~RenderSystem() {}

void RenderSystem::Init() {}

void RenderSystem::Update(Scene &scene, float dt) {
    for (auto const &entity : mEntities) {
        auto &rectangleShape = scene.GetComponent<RectangleShape>(entity);
        auto &transform = scene.GetComponent<Transform2D>(entity);

        DrawRectangleV(Vector2{transform.pos.x, transform.pos.y}, Vector2{transform.size.x, transform.size.y},
                       Color{rectangleShape.color[0], rectangleShape.color[1], rectangleShape.color[2], rectangleShape.color[3]});
    }
}
