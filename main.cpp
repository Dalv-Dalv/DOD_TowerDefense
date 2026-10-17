#include <memory>

#include "IArchitecture.h"
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include "UIManager.h"

using namespace std;

int main() {
    constexpr int screenWidth = 1200;
    constexpr int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "DOD_TowerDefense");

    UIManager uiManager;
    uiManager.initialize();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        uiManager.render();

        EndDrawing();
    }

    uiManager.shutdown();
    CloseWindow();

    return 0;
}
