#ifndef DOD_TOWERDEFENSE_UIMANAGER_H
#define DOD_TOWERDEFENSE_UIMANAGER_H
#include <functional>


class UIManager {
public:
    using IntCallback = std::function<void(int)>;
    using BoolCallback = std::function<void(bool)>;
    using FloatCallback = std::function<void(float)>;

    void onObjectCountChanged(const IntCallback &callback);
    void onIsOOPChanged(const BoolCallback &callback);
    void onSpeedChanged(const FloatCallback &callback);

    void initialize();
    void shutdown();
    void render();

    int getObjectCount() const;
    bool getIsOOP() const;
    float getSimSpeed() const;

    void setMemoryUsageBytes(size_t memoryUsageBytes);

private:
    int objectCount = 1000;
    bool isOOP = false;
    float simSpeed = 1.0f;
    size_t memoryUsageBytes = 0;

    std::vector<IntCallback> objectCountCallbacks;
    std::vector<BoolCallback> isOOPToggleCallbacks;
    std::vector<FloatCallback> speedCallbacks;
};


#endif //DOD_TOWERDEFENSE_UIMANAGER_H
