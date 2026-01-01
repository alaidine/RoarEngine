project(RoarScriptCore LANGUAGES CSharp)

add_library(RoarScriptCore SHARED RoarScriptCore.cs)

add_library(RoarSandbox SHARED RoarSandbox.cs)
target_link_libraries(RoarSandbox RoarScriptCore)
