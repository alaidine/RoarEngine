#pragma once
    #include "../Core.hpp"
    #include "System.hpp"
    #include "../Component/Component.hpp"
    #define TARGET_FPS 100

extern Core _core;

void DrawMissiles(Position pos, AnimationComponent anim, Sprite sprite, Texture2D player) {
   
    anim._frameCounter++;

    if (anim._frameCounter >= (TARGET_FPS / anim._frameSpeed))
    {
        anim._frameCounter = 0;
        anim._current_frame++;
        if (anim._current_frame > 4) anim._current_frame = 0;
        anim.rect.x = anim._animationRectangle[anim._current_frame].x;
        anim.rect.y = anim._animationRectangle[anim._current_frame].y;
        anim.rect.height = anim._animationRectangle[anim._current_frame].height;
        anim.rect.width = anim._animationRectangle[anim._current_frame].width;
    }

    pos.position.x += 5;

    float frameWidth = anim.rect.width;
    float frameHeight = anim.rect.height;
    Rectangle sourceRec = { anim.rect.x, anim.rect.y, frameWidth, frameHeight };
    Rectangle rec = { (float)pos.position.x, (float)pos.position.y, frameWidth * 2.0f, frameHeight * 2.0f };
    Rectangle destRec = { (float)pos.position.x, (float)pos.position.y, frameWidth * 2.0f, frameHeight * 2.0f };
    Vector2 origin = { 0.0f, 0.0f };

    DrawTexturePro(player, sourceRec, destRec, origin, 0.0f, sprite.color);

}
class MissileSystem : public System {
    public:
        void Update() override {
            Texture2D player;
            for (auto const& entity: _entities) {
                auto& pos = _core.GetComponent<Position>(entity);
                auto& anim = _core.GetComponent<AnimationComponent>(entity);
                auto& sprite = _core.GetComponent<Sprite>(entity);
                DrawMissiles(pos, anim, sprite, player);
            }
        }
};