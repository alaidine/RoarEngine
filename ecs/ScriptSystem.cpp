#include "ScriptSystem.h"

namespace Roar {

ScriptSystem::ScriptSystem() {}

ScriptSystem::~ScriptSystem() {}

void ScriptSystem::Init() {}

void ScriptSystem::Update(float dt) {
    for (auto const &entity : mEntities) {
        Roar::Scripting::OnUpdateEntity(entity, dt);
    }
}

} // namespace Roar
