cmake_minimum_required(VERSION 3.28)

project(GhostEscape VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (WIN32)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR})

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_image CONFIG REQUIRED)
find_package(SDL3_mixer CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(${TARGET}
                    src/main.cpp
                    src/core/Game.cpp
                    src/core/ObjectWorld.cpp
                    src/core/Scene.cpp
                    src/core/AssetStore.cpp
                    src/SceneMain.cpp
                    src/Player.cpp
                    )

target_link_libraries(${TARGET}
                        PRIVATE SDL3::SDL3
                        PRIVATE SDL3_image::SDL3_image
                        PRIVATE SDL3_mixer::SDL3_mixer
                        PRIVATE SDL3_ttf::SDL3_ttf
                        PRIVATE glm::glm)