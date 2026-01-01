#include "Layer.h"

namespace Roar {

class EditorLayer : public Layer {
  public:
    EditorLayer();
    ~EditorLayer();

    void OnEvent(Event &event) override;
    void OnUpdate(float st) override;
    void OnRender() override;

    bool Open = false;
    bool Focused = false;
};

} // namespace Roar
