add_library(core
    application.cpp
    application.h
    layer.cpp
    layer.h)

target_link_libraries(core PRIVATE boost::boost glm::glm)
