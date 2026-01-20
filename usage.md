# ECS Framework - Extended Documentation

A comprehensive Entity Component System (ECS) framework with networking capabilities, physics integration, and plugin architecture built on Raylib.

## Table of Contents
- [Core Architecture](#core-architecture)
- [Component Reference](#component-reference)
- [System Reference](#system-reference)
- [Physics Integration](#physics-integration)
- [Plugin System](#plugin-system)
- [Advanced Examples](#advanced-examples)
- [Core Concepts](#core-concepts)
- [Getting Started](#getting-started)
- [Entity Management](#entity-management)
- [Component System](#component-system)
- [System Architecture](#system-architecture)
- [Networking](#networking)
- [Input Management](#input-management)
- [Examples](#examples)
- [Best Practices](#best-practices)
- [Performance Tips](#performance-tips)
- [API Reference](#api-reference)

---

## Core Concepts

### What is ECS?

The **Entity Component System (ECS)** is an architectural pattern that follows **composition over inheritance**.

- **Entities**: Unique identifiers (just numbers)
- **Components**: Pure data containers
- **Systems**: Logic that operates on entities with specific components

```cpp
// Entity: Just an ID
Entity player = _core.CreateEntity();

// Components: Pure data
struct Position {
    Vector2 position;
};

struct Velocity {
    Vector2 velocity;
};

// System: Logic
class MovementSystem : public System {
    void Update() override {
        for (auto entity : _entities) {
            auto& pos = _core.GetComponent<Position>(entity);
            auto& vel = _core.GetComponent<Velocity>(entity);

            pos.position.x += vel.velocity.x * GetFrameTime();
            pos.position.y += vel.velocity.y * GetFrameTime();
        }
    }
};

---

## Core Architecture

### Scene Management

The `Scene` class is the central coordinator of the ECS framework.

```cpp
#include "Scene.h"

// Global scene instance
Scene _core;

int main() {
    // Initialize scene
    _core.Init();
    
    // Your game code...
    
    return 0;
}
```

#### Scene Methods

| Method | Description | Example |
|--------|-------------|---------|
| `Init()` | Initialize all managers | `_core.Init();` |
| `CreateEntity()` | Create entity with auto ID | `Entity e = _core.CreateEntity();` |
| `DestroyEntity(Entity)` | Destroy entity and components | `_core.DestroyEntity(player);` |
| `GetEntitiesWith<T...>()` | Query entities by components | `auto players = _core.GetEntitiesWith<Position, Sprite>();` |
| `UpdateAllSystem()` | Update all systems in order | `_core.UpdateAllSystem();` |

---

## Component Reference

### Position Component

```cpp
struct Position {
    Vector2 position;
};

// Usage
Position pos;
pos.position = {100.0f, 200.0f};
_core.AddComponent(entity, pos);
```

### Getting Started

```cpp
#include "Scene.h"
#include "Component.h"
#include "System.h"

// Global scene instance
Scene _core;

int main() {
    _core.Init();

    _core.RegisterComponent<Position>();
    _core.RegisterComponent<Velocity>();
    _core.RegisterComponent<Sprite>();

    auto movementSystem = _core.RegisterSystem<MovementSystem>();

    Signature movementSignature;
    movementSignature.set(_core.GetComponentType<Position>());
    movementSignature.set(_core.GetComponentType<Velocity>());
    _core.SetSystemSignature<MovementSystem>(movementSignature);

    InitWindow(800, 600, "ECS Game");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        _core.UpdateAllSystem();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
```

### Defining Components

```cpp
struct Position {
    Vector2 position;
};

struct Velocity {
    Vector2 velocity;
    float maxSpeed;
};

struct Health {
    int current;
    int max;
};
```

### Velocity Component

```cpp
struct Velocity {
    Vector2 velocity;
};

// Example: Moving entity
auto& vel = _core.GetComponent<Velocity>(entity);
vel.velocity = {5.0f, 0.0f};  // 5 pixels/frame to the right
```

### Sprite Component

```cpp
struct Sprite {
    Texture2D texture;      // Texture to render
    Rectangle source;       // Source rectangle in texture
    Vector2 origin;         // Origin point for rotation
    float scale;            // Scale multiplier
    float rotation;         // Rotation in degrees
    Color color;            // Tint color
};

// Example: Create a sprite
Texture2D tex = LoadTexture("player.png");
Sprite sprite;
sprite.texture = tex;
sprite.source = {0, 0, 32, 32};     // 32x32 sprite
sprite.origin = {16, 16};            // Center origin
sprite.scale = 2.0f;                 // Double size
sprite.rotation = 0.0f;
sprite.color = WHITE;

_core.AddComponent(entity, sprite);
```

### Collider Component

```cpp
struct Collider {
    Rectangle rect;    // Collision rectangle
    int layer;        // What layer I am on
    int mask;         // Which layers I collide with
};

// Layer definitions
enum Layer {
    LAYER_WORLD = 1 << 0,   // 0001
    LAYER_PLAYER = 1 << 1,  // 0010
    LAYER_ENEMY = 1 << 2,   // 0100
    LAYER_PIECE = 1 << 3,   // 1000
};

// Example: Player collider
Collider col;
col.rect = {x, y, 32, 32};
col.layer = LAYER_PLAYER;
col.mask = LAYER_WORLD | LAYER_ENEMY | LAYER_PIECE;  // Collide with these
_core.AddComponent(entity, col);
```

### Animation Component

```cpp
struct AnimationComponent {
    Rectangle rect;                        // Current frame rectangle
    std::array<Rectangle, 5> _animationRectangle;  // Frame definitions
    int _current_frame;                    // Current frame index
    int _frameCounter;                     // Frame timing counter
    int _frameSpeed;                       // Frames before switching
};

// Example: Setup animation
AnimationComponent anim;
anim._current_frame = 0;
anim._frameCounter = 0;
anim._frameSpeed = 8;  // Change frame every 8 ticks

// Define frames
anim._animationRectangle[0] = {0, 0, 32, 32};
anim._animationRectangle[1] = {32, 0, 32, 32};
anim._animationRectangle[2] = {64, 0, 32, 32};
anim._animationRectangle[3] = {96, 0, 32, 32};
anim._animationRectangle[4] = {128, 0, 32, 32};

anim.rect = anim._animationRectangle[0];
```

### Character Controller Component

```cpp
struct CharacterControllerComponent {
    Vector2 position;
    Vector2 velocity;
    float moveSpeed;
    float jumpforce;
    float gravity;
    bool isJumped;
    bool isGrounded;
    Collider collider;
};

// Example: Platform character
CharacterControllerComponent controller;
controller.position = {100, 100};
controller.velocity = {0, 0};
controller.moveSpeed = 200.0f;
controller.jumpforce = 400.0f;
controller.gravity = 800.0f;
controller.isGrounded = false;
controller.collider.rect = {100, 100, 32, 48};
controller.collider.layer = LAYER_PLAYER;
controller.collider.mask = LAYER_WORLD;
```

### Camera Component

```cpp
struct CameraComponent {
    Vector2 position;      // Camera position
    Vector2 target;        // Where camera looks
    Vector2 offset;        // Screen offset
    float zoom;            // Zoom level
    float rotation;        // Camera rotation
    bool mainCamera;       // Is this the main camera?
    Camera2D camera;       // Raylib camera
};

// Example: Create camera
CameraComponent cam;
cam.position = {0, 0};
cam.target = {0, 0};
cam.offset = {GAME_WIDTH/2.0f, GAME_HEIGHT/2.0f};
cam.zoom = 1.0f;
cam.rotation = 0.0f;
cam.mainCamera = true;

cam.camera.target = cam.position;
cam.camera.offset = cam.offset;
cam.camera.zoom = cam.zoom;
cam.camera.rotation = cam.rotation;
```

### Network Components

```cpp
struct NetworkedClient {
    uint32_t client_id;
    bool is_local;
};

struct LocalPlayerTag {};
struct RemotePlayerTag {};

// Example: Local player
_core.AddComponent(player, NetworkedClient{client_id, true});
_core.AddComponent(player, LocalPlayerTag{});

// Remote player
_core.AddComponent(remote, NetworkedClient{other_id, false});
_core.AddComponent(remote, RemotePlayerTag{});
```

### Input Component

```cpp
struct InputController {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool fire = false;
};

// Used by InputControllerSystem to handle player input
```

### Score Component

```cpp
struct Score {
    int score;
};

// Example
_core.AddComponent(player, Score{0});

// Later: increment score
auto& score = _core.GetComponent<Score>(player);
score.score += 10;
```

---

## System Reference

### Velocity System

Applies velocity to position for all entities with both components.

```cpp
class VelocitySystem : public System {
public:
    void Update() override {
        float dt = GetFrameTime();
        
        for (auto const& entity : _entities) {
            auto& pos = _core.GetComponent<Position>(entity);
            auto& vel = _core.GetComponent<Velocity>(entity);
            
            pos.position.x += vel.velocity.x * dt;
            pos.position.y += vel.velocity.y * dt;
        }
    }
};

// Setup
auto velocitySystem = _core.RegisterSystem<VelocitySystem>();
Signature velocitySig;
velocitySig.set(_core.GetComponentType<Position>());
velocitySig.set(_core.GetComponentType<Velocity>());
_core.SetSystemSignature<VelocitySystem>(velocitySig);
```

### Collision System

Handles collision detection and response between entities.

```cpp
class CollisionSystem : public System {
public:
    void Update() override {
        // Update collider positions
        for (Entity entity : _entities) {
            auto& pos = _core.GetComponent<Position>(entity);
            auto& collider = _core.GetComponent<Collider>(entity);
            
            collider.rect.x = pos.position.x;
            collider.rect.y = pos.position.y;
            
            // Check screen bounds for players
            if (collider.layer & LAYER_PLAYER) {
                check_map_collision(pos, collider);
            }
        }
        
        // Check all collision pairs
        for (auto itA = _entities.begin(); itA != _entities.end(); ++itA) {
            auto itB = itA;
            ++itB;
            
            for (; itB != _entities.end(); ++itB) {
                Entity a = *itA;
                Entity b = *itB;
                
                auto& colA = _core.GetComponent<Collider>(a);
                auto& colB = _core.GetComponent<Collider>(b);
                
                // Check layer masks
                if ((colA.mask & colB.layer) == 0 && 
                    (colB.mask & colA.layer) == 0)
                    continue;
                
                // Check collision
                if (CheckCollisionRecs(colA.rect, colB.rect)) {
                    handleCollision(a, b, colA, colB);
                }
            }
        }
    }
};

// Collision handler example
void handleCollision(Entity a, Entity b, Collider& colA, Collider& colB) {
    // Player vs Enemy
    if ((colA.layer == LAYER_PLAYER && colB.layer == LAYER_ENEMY) ||
        (colB.layer == LAYER_PLAYER && colA.layer == LAYER_ENEMY)) {
        std::cout << "Player hit enemy!" << std::endl;
    }
    
    // Player vs Pickup
    if (colA.layer == LAYER_PIECE && colB.layer == LAYER_PLAYER) {
        _core.DestroyEntity(a);  // Destroy pickup
        
        // Increment player score
        if (_core.HasComponent<Score>(b)) {
            auto& score = _core.GetComponent<Score>(b);
            score.score += 10;
        }
    }
}

// Screen bounds check
void check_map_collision(Position& pos, Collider& collider) {
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
```

### Input Controller System

Handles player input using configurable keybindings.

```cpp
class InputControllerSystem : public System {
private:
    InputManager gInput;
    
public:
    void SetupPlayerKeybinds(Entity player) {
        auto& input = _core.GetComponent<InputController>(player);
        
        gInput.add("Up", KEY_W, [&]() { input.up = true; });
        gInput.add("Down", KEY_S, [&]() { input.down = true; });
        gInput.add("Left", KEY_A, [&]() { input.left = true; });
        gInput.add("Right", KEY_D, [&]() { input.right = true; });
        gInput.add("Fire", KEY_SPACE, [&]() { input.fire = true; });
    }
    
    void Update() override {
        int key = GetKeyPressed();
        gInput.handleKey(key);
        
        for (auto entity : _entities) {
            auto& input = _core.GetComponent<InputController>(entity);
            auto& velocity = _core.GetComponent<Velocity>(entity);
            auto& cooldown = _core.GetComponent<playerCooldown>(entity);
            
            // Reset velocity
            velocity.velocity = {0, 0};
            
            // Apply input
            if (input.up)    velocity.velocity.y -= 5.0f;
            if (input.down)  velocity.velocity.y += 5.0f;
            if (input.left)  velocity.velocity.x -= 5.0f;
            if (input.right) velocity.velocity.x += 5.0f;
            
            // Handle shooting
            if (input.fire && !cooldown.canFire) {
                cooldown.canFire = true;
                SpawnProjectile(entity);
            }
            
            if (!input.fire)
                cooldown.canFire = false;
            
            // Clear input for next frame
            input = {};
        }
    }
};
```

### Renderer System

Handles rendering of all sprites with camera support.

```cpp
class RendererSystem : public System {
public:
    CameraComponent* GetMainCamera() {
        auto cameras = _core.GetEntitiesWith<CameraComponent>();
        
        for (Entity e : cameras) {
            auto& cam = _core.GetComponent<CameraComponent>(e);
            if (cam.mainCamera)
                return &cam;
        }
        return nullptr;
    }
    
    void Update() override {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        
        // Start camera mode if available
        CameraComponent* cam = GetMainCamera();
        if (cam) {
            BeginMode2D(cam->camera);
        }
        
        // Render all sprites
        for (auto& entity : _entities) {
            if (!_core.HasComponent<Position>(entity) || 
                !_core.HasComponent<Sprite>(entity))
                continue;
                
            auto& pos = _core.GetComponent<Position>(entity);
            auto& sprite = _core.GetComponent<Sprite>(entity);
            
            Rectangle src = sprite.source;
            Rectangle dst = {
                pos.position.x, 
                pos.position.y,
                src.width * sprite.scale,
                src.height * sprite.scale
            };
            
            Vector2 origin = sprite.origin;
            
            if (sprite.texture.id == 0) {
                // No texture, draw colored rectangle
                DrawRectangleRec(dst, sprite.color);
            } else {
                // Draw texture
                DrawTexturePro(
                    sprite.texture,
                    src,
                    dst,
                    origin,
                    sprite.rotation,
                    sprite.color
                );
            }
        }
        
        if (cam)
            EndMode2D();
        
        // UI elements (not affected by camera)
        for (auto& entity : _entities) {
            if (!_core.HasComponent<Score>(entity))
                continue;
                
            auto& score = _core.GetComponent<Score>(entity);
            DrawText(
                TextFormat("Score: %d", score.score),
                10, 10, 20, BLACK
            );
        }
        
        EndDrawing();
    }
};
```

### Camera Systems

```cpp
class CameraSystem : public System {
public:
    void Update() override {
        float followSpeed = 0.1f;
        
        for (auto e : _entities) {
            if (!_core.HasComponent<CameraComponent>(e))
                continue;
            
            auto& cam = _core.GetComponent<CameraComponent>(e);
            
            // Smooth follow
            Vector2 diff = {
                cam.target.x - cam.position.x,
                cam.target.y - cam.position.y
            };
            
            cam.position.x += diff.x * followSpeed;
            cam.position.y += diff.y * followSpeed;
            
            // Sync to Raylib camera
            cam.camera.target = cam.position;
            cam.camera.offset = cam.offset;
            cam.camera.zoom = cam.zoom;
            cam.camera.rotation = cam.rotation;
        }
    }
};

class CameraFollowSystem : public System {
public:
    void Update() override {
        // Find the player
        auto players = _core.GetEntitiesWith<LocalPlayerTag, Position>();
        if (players.empty())
            return;
        
        Entity player = *players.begin();
        auto& playerPos = _core.GetComponent<Position>(player);
        
        // Update all main cameras to follow player
        for (auto e : _entities) {
            auto& cam = _core.GetComponent<CameraComponent>(e);
            
            if (!cam.mainCamera)
                continue;
            
            cam.target = playerPos.position;
        }
    }
};
```

### Missile System

```cpp
class MissileSystem : public System {
public:
    void Update() override {
        for (auto& entity : _entities) {
            auto& pos = _core.GetComponent<Position>(entity);
            auto& anim = _core.GetComponent<AnimationComponent>(entity);
            
            // Animate
            AnimateMissile(pos, anim);
            
            // Move forward
            pos.position.x += 5;
            
            // Destroy if off-screen
            if (pos.position.x > GAME_WIDTH) {
                _core.DestroyEntity(entity);
                break;
            }
        }
    }
    
private:
    void AnimateMissile(Position& pos, AnimationComponent& anim) {
        anim._frameCounter++;
        
        if (anim._frameCounter >= (TARGET_FPS / anim._frameSpeed)) {
            anim._frameCounter = 0;
            anim._current_frame++;
            
            if (anim._current_frame > 4)
                anim._current_frame = 0;
            
            anim.rect = anim._animationRectangle[anim._current_frame];
        }
    }
};
```

---

## Physics Integration

### Physics Core

Combine collision and velocity systems for physics simulation.

```cpp
class PhysicsEngine {
private:
    CollisionSystem& _collisionSystem;
    VelocitySystem& _velocitySystem;
    
public:
    PhysicsEngine(CollisionSystem& col, VelocitySystem& vel)
        : _collisionSystem(col), _velocitySystem(vel) {}
    
    void UpdateAll() {
        _velocitySystem.Update();
        _collisionSystem.Update();
    }
};

// Usage in main loop
PhysicsEngine physics(collisionSystem, velocitySystem);

while (!WindowShouldClose()) {
    physics.UpdateAll();
    // Other systems...
}
```

### Box2D Integration

Interface for physics plugins.

```cpp
namespace Roar {
namespace Physics {

class IPhysics : public IPlugin {
public:
    virtual void InitDemo(uint32_t width, uint32_t height) = 0;
    virtual void UpdateDemo() = 0;
    virtual void CleanupDemo() = 0;
    
    virtual void Startup() = 0;
    virtual void Step() = 0;
    virtual void Shutdown() = 0;
};

} // namespace Physics
} // namespace Roar

// Usage
auto registry = Roar::GetRegistry();
auto physics = registry->GetSystem<Roar::Physics::IPhysics>("Box2DPhysics");

if (physics) {
    physics->InitDemo(800, 600);
    
    // In game loop
    physics->Step();
    physics->UpdateDemo();
}
```

---

## Plugin System

### Plugin Interface

```cpp
namespace Roar {

class IPlugin {
public:
    virtual ~IPlugin() = default;
    virtual const char* GetID() const = 0;
};

} // namespace Roar
```

### Creating a Plugin

```cpp
// MyPlugin.h
#pragma once
#include "IPlugin.h"

namespace Roar {

class MyCustomPlugin : public IPlugin {
public:
    const char* GetID() const override { 
        return "MyCustomPlugin"; 
    }
    
    void DoSomething() {
        // Plugin functionality
    }
};

} // namespace Roar

// MyPlugin.cpp
#include "MyPlugin.h"

extern "C" {
    PLUGIN_EXPORT Roar::IPlugin* CreatePlugin() {
        return new Roar::MyCustomPlugin();
    }
}
```

### Plugin Registry

```cpp
using namespace Roar;

// Get registry instance
PluginRegistry* registry = GetRegistry();

// Load all plugins from directory
registry->LoadAll("./plugins");

// Or load specific plugins
registry->LoadLibs({"NetworkPlugin", "PhysicsPlugin"});

// Get a plugin
auto network = registry->GetSystem<INetwork>("NetlibNetwork");
if (network) {
    INetClient* client = network->NewClient();
    // Use client...
}

// Cleanup
registry->Shutdown();
```

### Using the Plugin System

```cpp
// Add plugin to load list
Roar::PluginSystem::AddPlugin("MyPlugin");
Roar::PluginSystem::AddPlugin("NetworkPlugin");

// Startup - loads all registered plugins
Roar::PluginSystem::Startup();

// Get and use plugins
auto registry = Roar::GetRegistry();
auto myPlugin = registry->GetSystem<MyCustomPlugin>("MyCustomPlugin");

if (myPlugin) {
    myPlugin->DoSomething();
}

// Shutdown when done
Roar::PluginSystem::Shutdown();
```

---

## Advanced Examples

### Complete Game Setup

```cpp
#include "Scene.h"
#include "Prefab.h"
#include "AllSystems.h"

Scene _core;

void SetupGame() {
    _core.Init();
    
    // Register all components
    _core.RegisterComponent<Position>();
    _core.RegisterComponent<Velocity>();
    _core.RegisterComponent<Sprite>();
    _core.RegisterComponent<Collider>();
    _core.RegisterComponent<InputController>();
    _core.RegisterComponent<AnimationComponent>();
    _core.RegisterComponent<CameraComponent>();
    _core.RegisterComponent<Score>();
    _core.RegisterComponent<LocalPlayerTag>();
    _core.RegisterComponent<playerCooldown>();
    
    // Register systems
    auto inputSystem = _core.RegisterSystem<InputControllerSystem>();
    auto velocitySystem = _core.RegisterSystem<VelocitySystem>();
    auto collisionSystem = _core.RegisterSystem<CollisionSystem>();
    auto cameraFollowSystem = _core.RegisterSystem<CameraFollowSystem>();
    auto cameraSystem = _core.RegisterSystem<CameraSystem>();
    auto missileSystem = _core.RegisterSystem<MissileSystem>();
    auto renderSystem = _core.RegisterSystem<RendererSystem>();
    
    // Set system signatures
    Signature inputSig;
    inputSig.set(_core.GetComponentType<InputController>());
    inputSig.set(_core.GetComponentType<Velocity>());
    _core.SetSystemSignature<InputControllerSystem>(inputSig);
    
    Signature velocitySig;
    velocitySig.set(_core.GetComponentType<Position>());
    velocitySig.set(_core.GetComponentType<Velocity>());
    _core.SetSystemSignature<VelocitySystem>(velocitySig);
    
    Signature collisionSig;
    collisionSig.set(_core.GetComponentType<Position>());
    collisionSig.set(_core.GetComponentType<Collider>());
    _core.SetSystemSignature<CollisionSystem>(collisionSig);
    
    // Set update order
    inputSystem->order = 0;
    velocitySystem->order = 1;
    collisionSystem->order = 2;
    cameraFollowSystem->order = 3;
    cameraSystem->order = 4;
    missileSystem->order = 5;
    renderSystem->order = 100;  // Render last
    
    // Create game entities
    Entity player = Prefab::MakePlayer(_core, 100, 100);
    inputSystem->SetupPlayerKeybinds(player);
    
    Entity camera = Prefab::MakeCamera(_core);
    
    // Create some enemies
    for (int i = 0; i < 5; i++) {
        Prefab::MakeEnemy(_core, 200 + i * 100, 100);
    }
}

int main() {
    InitWindow(GAME_WIDTH, GAME_HEIGHT, "ECS Game");
    SetTargetFPS(60);
    
    SetupGame();
    
    while (!WindowShouldClose()) {
        _core.UpdateAllSystem();
    }
    
    CloseWindow();
    return 0;
}
```

### Prefab Factory Pattern

```cpp
namespace Prefab {

Entity MakePlayer(Scene& core, float x, float y) {
    Entity player = core.CreateEntity();
    
    // Position
    core.AddComponent(player, Position{{x, y}});
    
    // Sprite
    Texture2D tex = LoadTexture("player.png");
    core.AddComponent(player, Sprite{
        tex,
        {0, 0, 32, 32},     // source
        {16, 16},            // origin
        2.0f,                // scale
        0.0f,                // rotation
        WHITE                // color
    });
    
    // Input
    core.AddComponent(player, InputController{});
    core.AddComponent(player, Velocity{{0, 0}});
    core.AddComponent(player, playerCooldown{false});
    
    // Collision
    Collider col;
    col.rect = {x, y, 32, 32};
    col.layer = LAYER_PLAYER;
    col.mask = LAYER_WORLD | LAYER_ENEMY | LAYER_PIECE;
    core.AddComponent(player, col);
    
    // Tags
    core.AddComponent(player, LocalPlayerTag{});
    core.AddComponent(player, Score{0});
    
    return player;
}

Entity MakeEnemy(Scene& core, float x, float y) {
    Entity enemy = core.CreateEntity();
    
    core.AddComponent(enemy, Position{{x, y}});
    
    Texture2D tex = LoadTexture("enemy.png");
    core.AddComponent(enemy, Sprite{
        tex, {0, 0, 32, 32}, {16, 16}, 2.0f, 0.0f, RED
    });
    
    // Simple AI: move left
    core.AddComponent(enemy, Velocity{{-2.0f, 0.0f}});
    
    Collider col;
    col.rect = {x, y, 32, 32};
    col.layer = LAYER_ENEMY;
    col.mask = LAYER_PLAYER;
    core.AddComponent(enemy, col);
    
    core.AddComponent(enemy, EnemyTag{true});
    
    return enemy;
}

Entity MakeMissile(Scene& core) {
    Entity missile = core.CreateEntity();
    
    // Start offscreen, will be positioned when fired
    core.AddComponent(missile, Position{{-100, -100}});
    
    Texture2D tex = LoadTexture("missile.png");
    core.AddComponent(missile, Sprite{
        tex, {0, 0, 16, 8}, {8, 4}, 2.0f, 0.0f, YELLOW
    });
    
    // Animation
    AnimationComponent anim;
    anim._current_frame = 0;
    anim._frameCounter = 0;
    anim._frameSpeed = 8;
    
    for (int i = 0; i < 5; i++) {
        anim._animationRectangle[i] = {i * 16.0f, 0, 16, 8};
    }
    anim.rect = anim._animationRectangle[0];
    core.AddComponent(missile, anim);
    
    // Collision
    Collider col;
    col.rect = {0, 0, 16, 8};
    col.layer = LAYER_PLAYER;  // Player's projectile
    col.mask = LAYER_ENEMY;
    core.AddComponent(missile, col);
    
    core.AddComponent(missile, MissileTag{});
    
    return missile;
}

Entity MakeCamera(Scene& core) {
    Entity camera = core.CreateEntity();
    
    CameraComponent cam;
    cam.position = {GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f};
    cam.target = cam.position;
    cam.offset = {GAME_WIDTH / 2.0f, GAME_HEIGHT / 2.0f};
    cam.zoom = 1.0f;
    cam.rotation = 0.0f;
    cam.mainCamera = true;
    
    cam.camera.target = cam.position;
    cam.camera.offset = cam.offset;
    cam.camera.zoom = cam.zoom;
    cam.camera.rotation = cam.rotation;
    
    core.AddComponent(camera, cam);
    
    return camera;
}

void MakeMap(Scene& core) {
    // Ground
    MakeGround(core, 0, GAME_HEIGHT - 50, GAME_WIDTH, 50, DARKGRAY);
    
    // Platforms
    MakeGround(core, 100, 400, 200, 20, GRAY);
    MakeGround(core, 400, 300, 200, 20, GRAY);
    MakeGround(core, 600, 200, 200, 20, GRAY);
    
    // Collectibles
    for (int i = 0; i < 10; i++) {
        float x = 50 + i * 70;
        float y = 350;
        MakePiece(core, x, y);
    }
}

Entity MakeGround(Scene& core, float x, float y, float w, float h, Color color) {
    Entity ground = core.CreateEntity();
    
    core.AddComponent(ground, Position{{x, y}});
    
    core.AddComponent(ground, Sprite{
        {0},              // No texture
        {0, 0, w, h},
        {0, 0},
        1.0f,
        0.0f,
        color
    });
    
    Collider col;
    col.rect = {x, y, w, h};
    col.layer = LAYER_WORLD;
    col.mask = LAYER_PLAYER;
    core.AddComponent(ground, col);
    
    return ground;
}



Entity MakePiece(Scene& core, float x, float y) {
    Entity piece = core.CreateEntity();
    
    core.AddComponent(piece, Position{{x, y}});
    
    core.AddComponent(piece, Sprite{
        {0},
        {0, 0, 16, 16},
        {8, 8},
        1.0f,
        0.0f,
    })
}
```

