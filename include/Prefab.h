#pragma once
#include "Scene.h"

namespace Prefab {
Entity MakePlayer(Scene &_core, float posX, float posY);
Entity MakeEnemy(Scene &_core, float posX, float posY);
Entity MakeMilssile(Scene &_core);
Entity MakeCamera(Scene &_core);
Entity MakeCharacterController(Scene &_core, float x, float y);
Entity MakeGround(Scene &_core, float x, float y, float w, float h, Color color);
Entity MakePiece(Scene &_core, float x, float y);
void MakeMap(Scene &_core);

inline Entity MakeClient(Scene &_core, float x, float y, uint32_t client_id, bool is_local, Texture2D &playerTexture) {
    Entity e = _core.CreateEntity();

    PlayerSprite sprite;
    sprite.texture = playerTexture;

    _core.AddComponent(e, Position{Vector2{x, y}});
    _core.AddComponent(e, sprite);
    _core.AddComponent(e, AnimationComponent{
                              Rectangle{0, 30, 32, 22},
                              {},
                              0,
                              0,
                              8,
                          });
    _core.AddComponent(e, Tag{true});
    _core.AddComponent(e, Sprite{playerTexture, Rectangle{0, 30, 32, 33}, Vector2{0.0f, 0.0f}, 2.0f, 0.0f, RED});
    _core.AddComponent(e, NetworkedClient{client_id, is_local});

    if (is_local) {
        _core.AddComponent(e, InputController{});
        _core.AddComponent(e, playerCooldown{false});
        _core.AddComponent(e, LocalPlayerTag{});
    } else {
        _core.AddComponent(e, RemotePlayerTag{});
    }

    return e;
}
} // namespace Prefab
