#pragma once
#include "Entity.h"
#include "Signature.h"
#include <array>
#include <cassert>
#include <queue>

class EntityManager {
  private:
    std::queue<Entity> _entityAvailable{};
    std::array<Signature, MAX_ENTITIES> _signatures{};
    std::vector<Entity> _livingEntities{};
    uint32_t _livingEntity{};

  public:
    EntityManager() {
        for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
            _entityAvailable.push(entity);
    }

    Entity CreateEntity() {
        assert(_livingEntity < MAX_ENTITIES && "Too many entities in existence.");

        Entity id = _entityAvailable.front();
        _entityAvailable.pop();

        _livingEntities.push_back(id);
        _livingEntity++;

        return id;
    }

    void DestroyEntity(Entity entity) {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        _signatures[entity].reset();
        _entityAvailable.push(entity);

        for (size_t i = 0; i < _livingEntities.size(); i++) {
            if (_livingEntities[i] == entity) {
                _livingEntities[i] = _livingEntities.back();
                _livingEntities.pop_back();
                break;
            }
        }
        _livingEntity--;
    }

    void SetSignature(Entity entity, Signature signature) {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        _signatures[entity] = signature;
    }

    Signature GetSignature(Entity entity) {
        assert(entity < MAX_ENTITIES && "Entity out of range.");

        return _signatures[entity];
    }

    const std::vector<Entity> &GetLivingEntities() const { return _livingEntities; }
};
