#pragma once
#include <array>
#include <cstdint>
#include <raylib.h>
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define GAME_WIDTH 800
#define GAME_HEIGHT 600

#define TARGET_FPS 100

using ComponentType = std::uint8_t;

const ComponentType MAX_COMPONENTS = 32;

enum Layer {
    LAYER_WORLD = 1 << 0,
    LAYER_PLAYER = 1 << 1,
    LAYER_ENEMY = 1 << 2,
    LAYER_PIECE = 1 << 3,
};

struct Gravity {
    float force;
};

struct Position {
    Vector2 position;
};

struct Velocity {
    Vector2 velocity;
};

struct Sprite {
    Texture2D texture;
    Rectangle source;
    Vector2 origin;

    float scale;
    float rotation;

    Color color;
};

struct PlayerSprite {
    Texture2D texture;
};

struct EnemySprite {
    Texture2D texture;
};

struct Collider {
    Rectangle rect;

    int layer; // I am (ex: player)
    int mask;  // which what i collision
};

struct AnimationComponent {
    Rectangle rect;

    std::array<Rectangle, 5> _animationRectangle;

    int _current_frame;
    int _frameCounter;
    int _frameSpeed;
};

struct InputController {};

struct Tag {
    bool isPlayer;
};

struct EnemyTag {
    bool isEnemy;
};

struct MissileTag {};

struct playerCooldown {
    bool canFire;
};

struct CameraComponent {
    Vector2 position;
    Vector2 target;
    Vector2 offset;

    float zoom;
    float rotation;

    bool mainCamera;

    Camera2D camera;
};

// Networked client component for multiplayer
struct NetworkedClient {
    uint32_t client_id;
    bool is_local;
};

// Tag to identify local player entity
struct LocalPlayerTag {};

// Tag to identify remote player entities
struct RemotePlayerTag {};

struct CharacterControllerComponent {
    Vector2 position;
    Vector2 veloctity;

    float moveSpeed;
    float jumpforce;
    float gravity;

    bool isJumped;
    bool isGrounded;

    Collider collider;
};

struct Score {
    int score;
};
