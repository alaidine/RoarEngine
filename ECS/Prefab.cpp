#include "Prefab.hpp"

namespace Prefab {
    Entity MakePlayer(Core& _core, float posX, float posY) {
        Entity e = _core.CreateEntity();
        _core.AddComponent(e, Position{Vector2{posX, posY}});
        // _core.AddComponent(e, Gravity{9.81});
        _core.AddComponent(e, Sprite{RED});
        _core.AddComponent(e, Velocity{4});
        _core.AddComponent(e, InputController{});
        
        return e;
    }

    Entity MakeEnemy(Core& _core, float posX, float posY) {
        Entity e = _core.CreateEntity();
        _core.AddComponent(e, Position{Vector2{posX, posY}});
        _core.AddComponent(e, Gravity{9.81});
        _core.AddComponent(e, Sprite{GREEN});
        _core.AddComponent(e, Velocity{4});
        
        return e;
    }

    Entity MakeMilssile(Core& _core) {
        Entity e = _core.CreateEntity();
        _core.AddComponent(e, AnimationComponent{
            Rectangle{0, 0, 0, 0},
            {
                Rectangle{ 0, 128, 25, 22 },
                Rectangle{ 25, 128, 31, 22 },
                Rectangle{ 56, 128, 40, 22 },
                Rectangle{ 96, 128, 55, 22 },
                Rectangle{ 151, 128, 72, 22 }
            },
            0,
            0,
            8,
        });
        _core.AddComponent(e, Sprite{WHITE});
        _core.AddComponent(e, Position{Vector2{0, 0}});
        _core.AddComponent(e, InputController{});
        return e;
    }
}