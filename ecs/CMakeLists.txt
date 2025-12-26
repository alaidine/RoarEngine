add_library(ecs
    ECS.h
    Component.h
    RenderSystem.cpp
    RenderSystem.h)

target_include_directories(ecs PRIVATE ${CMAKE_SOURCE_DIR}/renderer)
target_include_directories(ecs PRIVATE ${CMAKE_SOURCE_DIR}/core)
target_link_libraries(ecs PRIVATE renderer raylib boost::boost glm::glm imgui::imgui)
