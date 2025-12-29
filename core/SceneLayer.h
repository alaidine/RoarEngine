#include "Layer.h"
#include "Common.h"
#include "RenderSystem.h"
#include "ScriptSystem.h"

namespace Roar {

class SceneLayer : public Layer {
  public:
    SceneLayer();
    ~SceneLayer();

    void OnEvent(Roar::Event &event) override;
    void OnUpdate(float st) override;
    void OnRender() override;

  private:
    Ref<Scene> mScene;
    std::shared_ptr<RenderSystem> mRenderSystem;
    std::shared_ptr<ScriptSystem> mScriptSystem;
};

} // namespace Roar
