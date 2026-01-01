#include "ProjectManager.h"
#include "Common.h"

#include "nfd.h"

namespace Roar {

void ProjectManagerLayer::OnEvent(Event &event) {}

void ProjectManagerLayer::OnUpdate(float ts) {}

void ProjectManagerLayer::OnRender() {}

bool ProjectManagerLayer::OpenProject() {
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_PickFolder(NULL, &outPath);

    if (result == NFD_OKAY) {
        RO_LOG_INFO("Success!");
        RO_LOG_INFO(outPath);
        projectRoot = outPath;
        scenePath = projectRoot / "Scenes" / "Game.ro";
        gameLibPath = projectRoot / "Game.dll";
        free(outPath);
    } else if (result == NFD_CANCEL) {
        puts("User pressed cancel.");
    } else {
        RO_LOG_ERR(NFD_GetError());
    }

    if (result == NFD_OKAY)
        return true;
    return false;
}

void ProjectManagerLayer::CreateProject() {}

} // namespace Roar
