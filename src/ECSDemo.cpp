#include "Scene.h"
#include "InputControllerSystem.h"
#include "MissileSystem.h"
#include "GravitySystem.h"
#include "CollisionSystem.h"
#include "VelocitySystem.h"
#include "PhysicCore.h"
#include "RendererSystem.h"
#include "CameraSystem.h"
#include "CharacterController.h"
#include "Builder.h"
#include "Prefab.h"
#include <stdlib.h>
#include <time.h>

Scene _core;

int main() {
    _core.Init();

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "TEST");
    
    MiniBuilder::RegisterComponentBuilder registerTest;
    registerTest.RegisterComponents<Position, Gravity, Velocity, Sprite, InputController, PlayerSprite, AnimationComponent, Tag, MissileTag, playerCooldown, Collider, EnemySprite, LocalPlayerTag, CameraComponent, CharacterControllerComponent, Score>(_core);

 
    auto inputControllerSystem = _core.RegisterSystem<InputControllerSystem>();
    inputControllerSystem->order = 1;

    auto characterControllerSystem = _core.RegisterSystem<CharacterControllerSystem>();
    characterControllerSystem->order = 2;

    auto velocitySystem = _core.RegisterSystem<VelocitySystem>();
    velocitySystem->order = 3;

    auto colliderSystem = _core.RegisterSystem<CollisionSystem>();
    colliderSystem->order = 4;

    auto missileSystem = _core.RegisterSystem<MissileSystem>();
    missileSystem->order = 5;

    auto cameraFollowSystem = _core.RegisterSystem<CameraFollowSystem>();
    cameraFollowSystem->order = 6;

    auto cameraSystem = _core.RegisterSystem<CameraSystem>();
    cameraSystem->order = 7;

    auto renderSystem = _core.RegisterSystem<RendererSystem>();
    renderSystem->order = 8;


    Signature gravitySignature;
    Signature inputControllerSignature;
    Signature missileSystemSignature;
    Signature colliderSystemSignature;
    Signature velocitySystemSignature;
    Signature RenderSignature;
    Signature cameraSignature;
    Signature cameraFollowSignature;
    Signature characterControllerSignature;
    
    MiniBuilder::SystemBuilder inputControllerBuilder(inputControllerSignature);
    inputControllerBuilder.BuildSignature<InputControllerSystem, Position, InputController, PlayerSprite>(_core);
    
    MiniBuilder::SystemBuilder missileSystemBuilder(missileSystemSignature);
    missileSystemBuilder.BuildSignature<MissileSystem ,Position, AnimationComponent, MissileTag>(_core);
    
    MiniBuilder::SystemBuilder colliderSystemBuilder(colliderSystemSignature);
    colliderSystemBuilder.BuildSignature<CollisionSystem, Position, Collider>(_core);
    
    MiniBuilder::SystemBuilder velocitySystemBuilder(velocitySystemSignature);
    velocitySystemBuilder.BuildSignature<VelocitySystem, Position, Velocity>(_core);

    MiniBuilder::SystemBuilder rendererBuilder(RenderSignature);
    rendererBuilder.BuildSignature<RendererSystem, Position, Sprite>(_core);

    MiniBuilder::SystemBuilder cameraBuilder(cameraSignature);
    cameraBuilder.BuildSignature<CameraSystem, CameraComponent>(_core);

    MiniBuilder::SystemBuilder cameraFollowBuilder(cameraFollowSignature);
    cameraFollowBuilder.BuildSignature<CameraFollowSystem, CameraComponent>(_core);

    MiniBuilder::SystemBuilder characterControllerBuilder(characterControllerSignature);
    characterControllerBuilder.BuildSignature<CharacterControllerSystem, CharacterControllerComponent>(_core);

    Entity camera = Prefab::MakeCamera(_core);
    // Entity player = Prefab::MakePlayer(_core, (float)screenWidth/2, (float)screenHeight/2);
    Entity player = Prefab::MakeCharacterController(_core, 0, 400);
    for (int i = 0; i < 10; ++i) {
        float x = GetRandomValue(50, 750);
        float y = GetRandomValue(50, 400);
        Prefab::MakePiece(_core, x, y);
    }

    Prefab::MakeMap(_core);


    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose()) {
        _core.UpdateAllSystem();
    }
    
    CloseWindow();

    return 0;
}
