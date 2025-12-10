#pragma once
    #include "../Core.hpp"
    #include "System.hpp"
    #include "../Component/Component.hpp"
    #include "../Prefab.hpp"

extern Core _core;

class InputControllerSystem : public System {
    public:
        void Update() override {
            for (auto& entity: _entities) {
                auto& pos = _core.GetComponent<Position>(entity);
                auto& input = _core.GetComponent<InputController>(entity);
                auto& anim = _core.GetComponent<AnimationComponent>(entity);
                if (IsKeyPressed(KEY_SPACE)) {
                    pos.position.x = m_localClientState.x;
                    pos.position.y = m_localClientState.y;
                   anim.rect.x= anim._animationRectangle[anim._current_frame].x;
                   anim.rect.y= anim._animationRectangle[anim._current_frame].y;
                   anim.rect.height = anim._animationRectangle[anim._current_frame].height;
                   anim.rect.width = anim._animationRectangle[anim._current_frame].width;
                }    
                std::cout << "Input controller system" << std::endl;
            }
        }
};