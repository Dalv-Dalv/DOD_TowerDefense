#include <memory>

#include "IArchitecture.h"
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include "UIManager.h"

//rares
#include "oop/OOPslider.h"

using namespace std;

int main() {
    constexpr int screenWidth = 1200;
    constexpr int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "DOD_TowerDefense");

    UIManager uiManager;
    uiManager.initialize();


    //rares
    OOPslider simulation;
    simulation.initialize(uiManager.getObjectCount(), screenWidth, screenHeight);

    uiManager.onObjectCountChanged([&simulation](int count)
    {
        simulation.setObjectCount(count);
    });

    while (!WindowShouldClose()) {
        simulation.update(GetFrameTime(), uiManager.getSimSpeed());

        BeginDrawing();
        ClearBackground(WHITE);

        simulation.render();
        uiManager.render();

        EndDrawing();
    }

    uiManager.shutdown();
    CloseWindow();

    return 0;
}
