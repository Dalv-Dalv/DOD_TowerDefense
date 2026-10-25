
#include "OOPslider.h"
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "Star.h"

using namespace std;

void OOPslider::initialize(int initialCount, int width, int height)
{

    this->screenWidth = width;
    this->screenHeight =height;

    setObjectCount(initialCount);
}


void OOPslider::setObjectCount(int count) {
    if (count < 0) count = 0;
    if (count > 100000) count = 100000;

    while (objects.size() > count)
    {
        objects.pop_back();
    }

    while (objects.size() < count) {
        Vector2 position =
        {
            static_cast<float>(GetRandomValue(0, screenWidth)),
            static_cast<float>(GetRandomValue(0, screenHeight))
        };

        Vector2 movement =
        {
            static_cast<float>(GetRandomValue(-100, 100)),
            static_cast<float>(GetRandomValue(-100, 100))
        };

        Color color = ColorFromHSV(GetRandomValue(0, 359), 0.8f, 0.9f);

        float size = GetRandomValue(4, 8);
        int shape = GetRandomValue(0, 3);

        switch (shape)
        {
            case 0:
                objects.push_back(make_unique<Circle>(position, movement, color, size));
                break;
            case 1:
                objects.push_back(make_unique<Square>(position, movement, color, size));
                break;
            case 2:
                objects.push_back(make_unique<Triangle>(position, movement, color, size));
                break;
            case 3:
                objects.push_back(make_unique<Star>(position, movement, color, size));
                break;
        }
    }
}


void OOPslider::update(float deltaTime, float speedMultiplier)
{
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    for (auto& object : objects)
    {
        object->update(deltaTime, speedMultiplier);
        object->handleWallCollision(screenWidth, screenHeight);
    }
}



void OOPslider::render() {
    for (auto& object : objects) {
        object->render();
    }
}

//urmeaza
size_t OOPslider::getMemoryUsageBytes() {
    return 0;
}

