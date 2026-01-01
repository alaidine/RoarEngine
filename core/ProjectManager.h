#pragma once

#include "Layer.h"

#include <filesystem>

namespace Roar {

class ProjectManagerLayer : public Layer {
  public:
    void OnEvent(Event &event) override;
    void OnUpdate(float ts) override;
    void OnRender() override;

    void CreateProject();
    bool OpenProject();
    
    std::filesystem::path projectRoot;
    std::filesystem::path scenePath;
    std::filesystem::path gameLibPath;
};

} // namespace Roar
