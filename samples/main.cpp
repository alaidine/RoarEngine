#include "Application.h"
#include "Layer.h"
#include "WindowEvents.h"

class SamplesApp : public rt::Layer {
  public:
    SamplesApp() {}
    ~SamplesApp() {}

    void OnEvent(rt::Event &event) override {}

    void OnUpdate(float st) override {}
    void OnRender() override {}
};

int main(int argc, char *argv[]) {
    rt::ApplicationSpecification spec;
    spec.Title = "RTEngine Samples";
    spec.Name = "RTEngineSamples";

    rt::Application samples(spec);
    samples.PushLayer<SamplesApp>();
    samples.Run();
}
