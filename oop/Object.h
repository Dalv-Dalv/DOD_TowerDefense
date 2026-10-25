
#ifndef DOD_TOWERDEFENSE_OBJECT_H
#define DOD_TOWERDEFENSE_OBJECT_H

#include "raylib.h"

enum class ShapeType {
    Circle,
    Square,
    Triangle,
    Star
};

class Object {
protected:
    Vector2 position;
    Vector2 movement;
    Color color;
    ShapeType shape;

public:
    Object(Vector2 position, Vector2 movement, Color color, ShapeType shape)
        : position(position), movement(movement), color(color), shape(shape) {}

    virtual ~Object() = default;

    virtual void update(float deltaTime, float speedMultiplier)
    {
        position.x += movement.x * deltaTime * speedMultiplier;
        position.y += movement.y * deltaTime * speedMultiplier;
    }

    virtual void render() const = 0;

    virtual void handleWallCollision(int width, int height) = 0;

};
#endif //DOD_TOWERDEFENSE_OBJECT_H