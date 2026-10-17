#include "UIManager.h"
#include <imgui.h>
#include <rlImGui.h>

void UIManager::onObjectCountChanged(const IntCallback &callback) {
    objectCountCallbacks.push_back(callback);
}
void UIManager::onIsOOPChanged(const BoolCallback &callback) {
    isOOPToggleCallbacks.push_back(callback);
}
void UIManager::onSpeedChanged(const FloatCallback &callback) {
    speedCallbacks.push_back(callback);
}

void UIManager::initialize() {
    rlImGuiSetup(true);
}
void UIManager::render() {
    rlImGuiBegin();

    ImGui::Begin("Controls and Diagnostics");

    ImGui::Text("Settings");
    if (ImGui::SliderInt("Object count", &objectCount, 0, 100'000)) {
        for (const auto& cb : objectCountCallbacks) cb(objectCount);
    }

    if (ImGui::Checkbox("Toggle OOP", &isOOP)) {
        for (const auto& cb : isOOPToggleCallbacks) cb(isOOP);
    }

    if (ImGui::SliderFloat("Simulation Speed", &simSpeed, 0.0f, 5.0f, "%.2fx")) {
        for (const auto& cb : speedCallbacks) cb(simSpeed);
    }


    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::Text("Diagnostics");
    ImGui::Text("FPS: %d (%.3f ms)", GetFPS(), GetFrameTime() * 1000.0f);
    ImGui::Text("Memory Usage: %.2f MB (%zu bytes)", memoryUsageBytes / (1024.0f * 1024.0f), memoryUsageBytes);


    ImGui::End();

    rlImGuiEnd();
}
void UIManager::shutdown() {
    rlImGuiShutdown();
}

int UIManager::getObjectCount() const { return objectCount; }
bool UIManager::getIsOOP() const { return isOOP; }
float UIManager::getSimSpeed() const { return simSpeed; }

void UIManager::setMemoryUsageBytes(size_t memoryUsageBytes) {
    this->memoryUsageBytes = memoryUsageBytes;
}
