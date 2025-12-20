#include "application.h"

#include <glm/glm.hpp>

#include <assert.h>
#include <iostream>
#include <ranges>

namespace rt {

static Application *s_Application = nullptr;

static void GLFWErrorCallback(int error, const char *description) { std::cerr << "[GLFW Error]: " << description << std::endl; }

Application::Application(const ApplicationSpecification &specification) : m_Specification(specification) {

}

Application::~Application() {
    // m_Window->Destroy();

    s_Application = nullptr;
}

void Application::Run() {
    m_Running = true;

    float lastTime = GetTime();

    // Main Application loop
    while (m_Running) {
        /*
        if (m_Window->ShouldClose()) {
            Stop();
            break;
        }
        */

        float currentTime = GetTime();
        float timestep = glm::clamp(currentTime - lastTime, 0.001f, 0.1f);
        lastTime = currentTime;

        // Main layer update here
        for (const std::unique_ptr<Layer> &layer : m_LayerStack)
            layer->OnUpdate(timestep);

        // NOTE: rendering can be done elsewhere (eg. render thread)
        for (const std::unique_ptr<Layer> &layer : m_LayerStack)
            layer->OnRender();

        // m_Window->Update();
    }
}

void Application::Stop() { m_Running = false; }

void Application::RaiseEvent(Event &event) {
    for (auto &layer : std::views::reverse(m_LayerStack)) {
        layer->OnEvent(event);
        if (event.Handled)
            break;
    }
}

// glm::vec2 Application::GetFramebufferSize() const { return m_Window->GetFramebufferSize(); }
glm::vec2 Application::GetFramebufferSize() const { return glm::vec2(0); }

Application &Application::Get() {
    assert(s_Application);
    return *s_Application;
}

float Application::GetTime() { return (float)0; }

} // namespace Core
