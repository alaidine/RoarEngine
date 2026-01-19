#pragma once 
    #include "Scene.h"
    #include "System.h"
    #include "Keybinds.h"

extern Scene _core;

void updateCollider(Collider& c, Position& pos)
{
    c.rect.x = pos.position.x;
    c.rect.y = pos.position.y;
}

void resolveCollisionX(Entity player, CharacterControllerComponent& c, int& score)
{
    auto others = _core.GetEntitiesWith<Collider>();

    for (auto& other: others ) {
        if (other == player)
        continue;
        
        auto& otherCol = _core.GetComponent<Collider>(other);
        
        if ((c.collider.mask & otherCol.layer) == 0)
            continue;
        
        if (!CheckCollisionRecs(c.collider.rect, otherCol.rect))
            continue;
        
        if (c.veloctity.x > 0.0f) {
            std::cout << "hit enemy" << std::endl;
            c.position.x = otherCol.rect.x - c.collider.rect.width;
            if (otherCol.layer == LAYER_PIECE) {
                _core.DestroyEntity(other);
                score++;
            }
        }
        else if (c.veloctity.x < 0.0f) {
            std::cout << "hit enemy" << std::endl;
            c.position.x = otherCol.rect.x + otherCol.rect.width;
            if (otherCol.layer == LAYER_PIECE) {
                _core.DestroyEntity(other);
                score++;
            }
            
        }
        c.veloctity.x = 0.0f;
        c.collider.rect.x = c.position.x;
    }
}

void resolveCollisionY(Entity player, CharacterControllerComponent& c, int score)
{
    c.isGrounded = false;
    auto others = _core.GetEntitiesWith<Collider>();

    for (Entity other: others ) {
        if (other == player)
            continue;
        
        auto& otherCol = _core.GetComponent<Collider>(other);

        if ((c.collider.mask & otherCol.layer) == 0)
            continue;
        
        if (!CheckCollisionRecs(c.collider.rect, otherCol.rect))
            continue;
        
        if (c.veloctity.y > 0.0f) {
           
            c.position.y = otherCol.rect.y - c.collider.rect.height;
            c.isGrounded = true;
            if (otherCol.layer == LAYER_PIECE) {
                _core.DestroyEntity(other);
                score++;
            }
        }
        else if (c.veloctity.y < 0.0f) {
            c.position.y = otherCol.rect.y + otherCol.rect.height;
            if (otherCol.layer == LAYER_PIECE) {
                _core.DestroyEntity(other);
                score++;
            }
           
        }
        
        c.veloctity.y = 0.0f;
        c.collider.rect.y = c.position.y;
    }
}

void Jump(CharacterControllerComponent& c)
{
    c.veloctity.y -= c.jumpforce;
    c.isGrounded = false;
}

class CharacterControllerSystem : public System {
    private:
        InputManager input;
        bool collectPiece = false;
    public:
        void Update() override {
            float dt = GetFrameTime();

            for (auto& entity: _entities) {
                auto& c = _core.GetComponent<CharacterControllerComponent>(entity);
                auto& pos = _core.GetComponent<Position>(entity);
                auto& score = _core.GetComponent<Score>(entity);

                c.veloctity.x = 0.0f;

                if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_W))
                    c.veloctity.x += c.moveSpeed;
                if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_D))
                    c.veloctity.x -= c.moveSpeed;
                
                int key = GetKeyPressed();
                input.add("JUMP", KEY_SPACE, [&c](){
                    Jump(c);
                });
                input.handleKey(key);



                // if (IsKeyPressed(KEY_TAB))
                //     showmenu = !showmenu;
                // if (showmenu)
                //     input.drawKeybindMenu();
                // if (c.isGrounded && IsKeyPressed(KEY_SPACE)) {
                //     c.veloctity.y -= c.jumpforce;
                //     c.isGrounded = false;
                // }

                if (!c.isGrounded) {
                    c.veloctity.y += c.gravity * dt;
                }
                c.position.x += c.veloctity.x * dt;
                c.collider.rect.x = c.position.x;
                resolveCollisionX(entity, c, score.score);

                c.position.y += c.veloctity.y * dt;
                c.collider.rect.y = c.position.y;
                resolveCollisionY(entity, c, score.score);
                pos.position.x = c.position.x;
                pos.position.y = c.position.y;
            }
        }
};
