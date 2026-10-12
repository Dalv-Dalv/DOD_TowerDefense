#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

int main() {
    InitWindow(800, 450, "DOD_TowerDefense");
    SetTargetFPS(60);

    // Initialize the ImGui binding after raylib's InitWindow
    rlImGuiSetup(true);

    bool showWindow = true;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // 1. Start the ImGui context
        rlImGuiBegin();

        // 2. Draw an ImGui window
        if (showWindow) {
            ImGui::Begin("Tower Defense Debug", &showWindow);
            ImGui::Text("ImGui is successfully linked with Raylib!");
            ImGui::End();
        }

        // 3. End ImGui context (this actually draws the UI to the screen)
        rlImGuiEnd();

        EndDrawing();
    }

    // Clean up ImGui before closing the window
    rlImGuiShutdown();
    CloseWindow();

    return 0;
}
