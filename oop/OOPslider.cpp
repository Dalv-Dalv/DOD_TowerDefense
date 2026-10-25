
#include "OOPslider.h"
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "Star.h"

#include <algorithm>
#include <cmath>

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

        float size = GetRandomValue(2, 4);
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

    buildGrid();
    checkCollisions();

    for (auto& object : objects) {
        object->handleWallCollision(screenWidth, screenHeight);
    }
}



void OOPslider::render() {
    for (auto& object : objects) {
        object->render();
    }
}


void OOPslider::buildGrid() {
    if (screenWidth <= 0 || screenHeight <= 0) return;

    int columns = (screenWidth + CELL_SIZE - 1) / CELL_SIZE;
    int rows = (screenHeight + CELL_SIZE - 1) / CELL_SIZE;

    head.assign(columns * rows, -1);
    next.resize(objects.size());

    for (int i = 0; i < objects.size(); i++) {
        Vector2 pos = objects[i]->getPosition();

        int cx = clamp(static_cast<int>(pos.x / CELL_SIZE), 0, columns - 1);
        int cy = clamp(static_cast<int>(pos.y / CELL_SIZE), 0, rows - 1);

        int cell = cy * columns + cx;

        next[i] = head[cell];
        head[cell] = i;
    }
}

void OOPslider::checkCollisions() {
    int columns = (screenWidth + CELL_SIZE - 1) / CELL_SIZE;
    int rows = (screenHeight + CELL_SIZE - 1) / CELL_SIZE;

    if (columns <= 0 || rows <= 0) return;

    int collisions = 0;

    for (int i = 0; i < objects.size(); i++) {
        Vector2 pos = objects[i]->getPosition();

        int cx = clamp(static_cast<int>(pos.x / CELL_SIZE), 0, columns - 1);
        int cy = clamp(static_cast<int>(pos.y / CELL_SIZE), 0, rows - 1);

        //3x3
        for (int y=cy -1; y<= cy + 1; y++) {
            if (y<0 || y >= rows) continue;

            for (int x = cx -1; x <= cx +1; x++) {
                if (x<0 || x>= columns) continue;

                int cell = y * columns + x;

                for (int j = head[cell]; j != -1; j = next[j]) {
                    if (j <= i)
                        continue;

                    Vector2 otherPos = objects[j]->getPosition();

                    float dx = otherPos.x - pos.x;
                    float dy = otherPos.y - pos.y;

                    float radiusSum = objects[i]->getCollisionRadius()
                                    + objects[j]->getCollisionRadius();

                    float distSq = dx * dx + dy * dy;

                    if (distSq < radiusSum * radiusSum) {
                        collisions++;
                        handleCollision(*objects[i], *objects[j]);
                    }
                }
            }
        }
    }
}


void OOPslider::handleCollision(Object &a, Object &b) {
    Vector2 PosA = a.getPosition();
    Vector2 PosB = b.getPosition();

    float dx = PosB.x - PosA.x;
    float dy = PosB.y - PosA.y;

    float radSum = a.getCollisionRadius() + b.getCollisionRadius();
    float distSq = dx * dx + dy * dy;

    if (distSq >= radSum * radSum) return;

    float dist = sqrtf(distSq);

    float nx = 1.0f;
    float ny = 0.0f;

    if (dist > 0.0001f) {
        nx = dx / dist;
        ny = dy / dist;
    }

    float overlap = (radSum - dist) / 2.0f;

    PosA.x -= nx*overlap;
    PosA.y -= ny*overlap;
    PosB.x += nx*overlap;
    PosB.y += ny*overlap;

    a.setPosition(PosA);
    b.setPosition(PosB);

    Vector2 velA = a.getMovement();
    Vector2 velB = b.getMovement();


    float relspeed = (velB.x -velA.x) *nx + (velB.y -velA.y) *ny;

    if (relspeed < 0) {
        float impuls = -relspeed;

        velA.x -= impuls * nx;
        velA.y -= impuls * ny;
        velB.x += impuls * nx;
        velB.y += impuls * ny;

        a.setMovement(velA);
        b.setMovement(velB);
    }
}


//urmeaza
size_t OOPslider::getMemoryUsageBytes() {
    static_assert(sizeof(Circle) == sizeof(Square));
    static_assert(sizeof(Circle) == sizeof(Triangle));
    static_assert(sizeof(Circle) == sizeof(Star));

    size_t memory = sizeof(*this);

    memory += objects.capacity() * sizeof(unique_ptr<Object>);
    memory += objects.size() * sizeof(Circle);

    memory += head.capacity() * sizeof(int);
    memory += next.capacity() * sizeof(int);

    return memory;static_assert(sizeof(Circle) == sizeof(Square));
    static_assert(sizeof(Circle) == sizeof(Triangle));
    static_assert(sizeof(Circle) == sizeof(Star));

    memory += objects.capacity() * sizeof(unique_ptr<Object>);
    memory += objects.size() * sizeof(Circle);

    memory += head.capacity() * sizeof(int);
    memory += next.capacity() * sizeof(int);

    return memory;
}