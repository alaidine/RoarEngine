add_library(renderer
    base.cpp
    base.h
    benchmark.hpp
    camera.hpp
    CommandLineParser.hpp
    Entrypoint.h
    keycodes.hpp
    TextureExample.cpp
    VulkanBuffer.cpp
    VulkanBuffer.h
    VulkanDebug.cpp
    VulkanDebug.h
    VulkanDevice.cpp
    VulkanDevice.h
    VulkanInitializers.hpp
    VulkanSwapChain.cpp
    VulkanSwapChain.h
    VulkanTexture.cpp
    VulkanTexture.h
    VulkanTools.h
    VulkanTools.cpp
    VulkanUIOverlay.cpp
    VulkanUIOverlay.h
    Renderer.h
    Renderer.cpp)

target_link_libraries(renderer PRIVATE Vulkan::Vulkan glfw glm::glm KTX::ktx)
target_link_libraries(renderer PUBLIC imgui::imgui)
