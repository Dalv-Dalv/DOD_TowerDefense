cmake_minimum_required(VERSION 4.3)
project(DOD_TowerDefense)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        6.0
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG        v1.92.7
)
FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
        rlImGui
        GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
        GIT_TAG        Raylib_6_0
)
FetchContent_MakeAvailable(rlImGui)

file(GLOB IMGUI_SOURCES "${imgui_SOURCE_DIR}/*.cpp")

add_library(raylib_imgui STATIC ${IMGUI_SOURCES} "${rlimgui_SOURCE_DIR}/rlImGui.cpp")

target_include_directories(raylib_imgui PUBLIC
        "${imgui_SOURCE_DIR}"
        "${rlimgui_SOURCE_DIR}"
)
target_link_libraries(raylib_imgui PUBLIC raylib)

add_executable(DOD_TowerDefense main.cpp
        UIManager.cpp
        UIManager.h
        IArchitecture.h
        oop/Object.h
        oop/Shape.h
        oop/Circle.h
        oop/Square.h
        oop/Triangle.h
        oop/Star.h
        oop/OOPslider.h
        oop/OOPslider.cpp)

target_link_libraries(DOD_TowerDefense PRIVATE raylib raylib_imgui)