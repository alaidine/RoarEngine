#include "Application.h"
#include "ECS.h"
#include "Layer.h"
#include "RenderSystem.h"
#include "WindowEvents.h"
#include "framework.h"

class SceneLayer : public rt::Layer {
  public:
    SceneLayer() {
        mScene.Init();

        mScene.RegisterComponent<Transform2D>();
        mScene.RegisterComponent<RectangleShape>();

        mRenderSystem = mScene.RegisterSystem<RenderSystem>();
        {
            Signature signature;
            signature.set(mScene.GetComponentType<RectangleShape>());
            signature.set(mScene.GetComponentType<Transform2D>());
            mScene.SetSystemSignature<RenderSystem>(signature);
        }
        mRenderSystem->Init();

        auto entity = mScene.CreateEntity();
        mScene.AddComponent(entity, RectangleShape{.color = {230, 41, 55, 255}});
        mScene.AddComponent(entity, Transform2D{{0.0f, 0.0f}, {10.0f, 10.0f}});
    }
    ~SceneLayer() {}

    void OnEvent(rt::Event &event) override {}

    void OnUpdate(float st) override { mRenderSystem->Update(mScene, st); }

    void OnRender() override {}

  private:
    Scene mScene;
    std::shared_ptr<RenderSystem> mRenderSystem;
};

int main(int argc, char *argv[]) {
    rt::ApplicationSpecification spec;
    spec.Title = "RTEngine";
    spec.Name = "RTEngine";

    rt::Application samples(spec);
    samples.PushLayer<SceneLayer>();
    samples.Run();
}
