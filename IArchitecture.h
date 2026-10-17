#ifndef DOD_TOWERDEFENSE_IARCHITECTURE_H
#define DOD_TOWERDEFENSE_IARCHITECTURE_H

#include <memory>

class IArchitecture {
public:
    virtual ~IArchitecture() = default;

    virtual void initialize(int initialCount, int screenWidth, int screenHeight) = 0;
    virtual void update(float deltaTime, float speedMultiplier) = 0;
    virtual void render() = 0;

    virtual void setObjectCount(int count) = 0;

    virtual size_t getMemoryUsageBytes() = 0;
};

#endif //DOD_TOWERDEFENSE_IARCHITECTURE_H
