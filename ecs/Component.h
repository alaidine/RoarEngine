#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORM_DEPTH_ZERO_TO_ONE
#define GML_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>

#include <filesystem>

namespace Roar {

struct TransformComponent {
    glm::vec2 pos;
    glm::vec2 size;
};

struct RectangleComponent {
    unsigned char color[4];
};

struct ScriptComponent {
    std::string name;
};

} // namespace Roar
