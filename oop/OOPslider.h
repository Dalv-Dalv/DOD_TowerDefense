
#ifndef DOD_TOWERDEFENSE_OOPSLIDER_H
#define DOD_TOWERDEFENSE_OOPSLIDER_H

#include <vector>
#include <memory>
#include "../IArchitecture.h"
#include "Object.h"

using namespace std;

class OOPslider : public IArchitecture
{

private:
    vector<unique_ptr<Object>> objects;
    int screenWidth;
    int screenHeight;

public:
    void initialize(int initialCount, int screenWidth, int screenHeight) override;
    void update(float deltaTime, float speedMultiplier) override;
    void render() override;
    void setObjectCount(int count) override;
    size_t getMemoryUsageBytes() override;
};

#endif
