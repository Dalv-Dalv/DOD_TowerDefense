#include <memory>

#include "IArchitecture.h"
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"
#include "UIManager.h"

//rares
#include "DoD/DoDArchitecture.h"
#include "OOP/OOPArchitecture.h"
#include "Shared/RenderUtils.h"

using namespace std;

int main() {
    constexpr int screenWidth = 1200;
    constexpr int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "DOD_TowerDefense");

    InitRenderResources();

    UIManager uiManager;
    uiManager.initialize();

    IArchitecture* simulation;
    if (uiManager.getIsOOP()) simulation = new OOPArchitecture();
    else simulation = new DoDArchitecture();

    simulation->initialize(uiManager.getObjectCount(), screenWidth, screenHeight);

    float simSpeed = 1.0f;

    uiManager.onIsOOPChanged([&simulation, &uiManager](bool isOOP) {
        delete simulation;
        if (isOOP) {
            simulation = new OOPArchitecture();
        } else {
            simulation = new DoDArchitecture();
        }
        simulation->initialize(uiManager.getObjectCount(), screenWidth, screenHeight);
    });

    uiManager.onObjectCountChanged([&simulation](int count) {
        if (simulation == nullptr) return;
        simulation->setObjectCount(count);
    });

    uiManager.onSpeedChanged([&simSpeed](float speed) {
        simSpeed = speed;
    });

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);

        if (simulation != nullptr) {
            simulation->update(deltaTime, simSpeed);
            simulation->render();
            uiManager.setMemoryUsageBytes(simulation->getMemoryUsageBytes());
        }

        uiManager.render();

        EndDrawing();
    }

    uiManager.shutdown();
    CloseWindow();

    return 0;
}
