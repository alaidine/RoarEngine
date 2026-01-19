#include "Prefab.h"

namespace Prefab {

Entity MakeEnemy(Scene &_core, float posX, float posY) {
    Entity e = _core.CreateEntity();

    // Position
    _core.AddComponent(e, Position{Vector2{posX, posY}});

    // Collider
    _core.AddComponent(e, Collider{
                              Rectangle{posX, posY, 40, 40}, // taille du collider
                              LAYER_ENEMY,                   // layer de l'entité
                              LAYER_PLAYER                   // ce avec quoi il collide
                          });

    // AnimationComponent minimal (utile si ton système s'attend à ça)
    _core.AddComponent(e, AnimationComponent{Rectangle{0, 0, 40, 40},
                                             {Rectangle{0, 0, 40, 40}, Rectangle{0, 0, 40, 40}, Rectangle{0, 0, 40, 40},
                                              Rectangle{0, 0, 40, 40}, Rectangle{0, 0, 40, 40}},
                                             0,
                                             0,
                                             8});

    // Sprite pour le rendre visible si pas de texture
    _core.AddComponent(e, Sprite{
                              {}, // texture vide
                              Rectangle{0, 0, 40, 40},
                              Vector2{0, 0},
                              1.0f,
                              0.0f,
                              GREEN // couleur visible
                          });

    return e;
}

Entity MakeMilssile(Scene &_core) {
    Entity e = _core.CreateEntity();
    _core.AddComponent(e, AnimationComponent{
                              Rectangle{0, 0, 0, 0},
                              {Rectangle{0, 128, 25, 22}, Rectangle{25, 128, 31, 22}, Rectangle{56, 128, 40, 22},
                               Rectangle{96, 128, 55, 22}, Rectangle{151, 128, 72, 22}},
                              0,
                              0,
                              8,
                          });
    _core.AddComponent(e, Position{Vector2{0, 0}});
    _core.AddComponent(e, Tag{false});
    _core.AddComponent(e, MissileTag{});
    return e;
}

Entity MakePlayer(Scene &_core, float x, float y) {
    Entity e = _core.CreateEntity();
    Texture2D texture = LoadTexture("resources/sprites/player_r-9c_war-head.png");
    _core.AddComponent(e, Position{Vector2{x, y}});
    _core.AddComponent(e, InputController{});
    _core.AddComponent(e, AnimationComponent{
                              Rectangle{0, 30, 32, 22},
                          });
    _core.AddComponent(e, Tag{true});
    _core.AddComponent(e, Sprite{Texture2D{}, Rectangle{0, 30, 32, 33}, Vector2{0.0f, 0.0f}, 2.0f, 0.0f, WHITE});
    _core.AddComponent(e, playerCooldown{false});
    _core.AddComponent(e, Collider{
                              Rectangle{0, 30, 32, 22},
                              LAYER_PLAYER,
                              LAYER_WORLD | LAYER_ENEMY,
                          });
    _core.AddComponent(e, Velocity{0.0f, 0.0f});
    _core.AddComponent(e, LocalPlayerTag{});
    // _core.AddComponent(e, CameraComponent{
    //     {0.0f, 0.0f},
    //     {0.0f, 0.0f},
    //     {GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f},
    //     1.0f,
    //     0.0f,
    //     true,
    // });
    return e;
}

Entity MakeCamera(Scene &core) {
    Entity e = core.CreateEntity();

    Camera2D cam{};
    cam.target = {0.0f, 0.0f};
    cam.offset = {GAME_WIDTH * 0.5f, GAME_HEIGHT * 0.5f};
    cam.rotation = 0.0f;
    cam.zoom = 1.0f;

    core.AddComponent(e, CameraComponent{{0.0f, 0.0f}, {0.0f, 0.0f}, cam.offset, 1.0f, 0.0f, true, cam});

    return e;
}

Entity MakeCharacterController(Scene &_core, float x, float y) {
    Entity e = _core.CreateEntity();

    Texture2D texture = LoadTexture("resources/sprites/player_r-9c_war-head.png");

    _core.AddComponent(e, Position{Vector2{x, y}});

    _core.AddComponent(e, Sprite{texture, Rectangle{0, 30, 32, 33}, Vector2{0.0f, 0.0f}, 2.0f, 0.0f, WHITE});
    _core.AddComponent(e, AnimationComponent{
                              Rectangle{0, 30, 32, 22},
                          });
    _core.AddComponent(e, CharacterControllerComponent{
                              Vector2{x, y},       // position
                              Vector2{0.0f, 0.0f}, // velocity
                              200.0f,              // moveSpeed
                              450.0f,              // jumpforce
                              1200.0f,             // gravity
                              false,               // isJumped
                              false,               // isGrounded
                              Collider{Rectangle{x, y, 32.0f * 2.0f, 33.0f * 2.0f}, LAYER_PLAYER, LAYER_WORLD | LAYER_PIECE}});
    _core.AddComponent(e, Score{
                              0,
                          });
    _core.AddComponent(e, LocalPlayerTag{});
    return e;
}

Entity MakeGround(Scene &_core, float x, float y, float w, float h, Color color) {
    Entity e = _core.CreateEntity();

    _core.AddComponent(e, Position{Vector2{x, y}});

    _core.AddComponent(e, Collider{Rectangle{x, y, w, h}, LAYER_WORLD, LAYER_PLAYER});

    // Sprite "debug" rouge
    _core.AddComponent(e, Sprite{
                              Texture2D{}, // texture vide
                              Rectangle{0, 0, w, h},
                              Vector2{0.0f, 0.0f},
                              1.0f,
                              0.0f,
                              color,
                          });
    return e;
}

Entity MakePiece(Scene &_core, float x, float y) {
    Entity e = _core.CreateEntity();

    _core.AddComponent(e, Position{Vector2{x, y}});

    _core.AddComponent(e, Collider{Rectangle{0, 0, 40, 40}, LAYER_PIECE, LAYER_PLAYER});

    _core.AddComponent(e, Sprite{{}, Rectangle{0, 0, 40, 40}, Vector2{0.0f, 0.0f}, 1.0f, 0.0f, YELLOW});

    return e;
}

void MakeMap(Scene &_core) {
    // SOL
    MakeGround(_core, 0.0f, 400.0f, 1600.0f, 50.0f, DARKGRAY);

    // Plateformes
    MakeGround(_core, 200.0f, 320.0f, 120.0f, 20.0f, GRAY);
    MakeGround(_core, 400.0f, 260.0f, 120.0f, 20.0f, GRAY);
    MakeGround(_core, 650.0f, 220.0f, 150.0f, 20.0f, GRAY);

    // Mur
    MakeGround(_core, 900.0f, 300.0f, 40.0f, 150.0f, DARKGRAY);

    // Plateforme haute
    MakeGround(_core, 1050.0f, 180.0f, 200.0f, 20.0f, GRAY);
}

} // namespace Prefab
