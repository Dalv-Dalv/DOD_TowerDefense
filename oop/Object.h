#ifndef DOD_TOWERDEFENSE_OBJECT_H
#define DOD_TOWERDEFENSE_OBJECT_H

#include "raylib.h"
#include "../Shared/ShapeType.h"

class Object {
protected:
    Vector2 position;
    Vector2 movement;
    Color color;
    ShapeType shape;

public:
    Object(Vector2 position, Vector2 movement, Color color, ShapeType shape)
        : position(position), movement(movement), color(color), shape(shape) {
    }

    virtual ~Object() = default;

    virtual void update(float deltaTime, float speedMultiplier) {
        position.x += movement.x * deltaTime * speedMultiplier;
        position.y += movement.y * deltaTime * speedMultiplier;
    }


    Vector2 getPosition() const {
        return position;
    }

    Vector2 getMovement() const {
        return movement;
    }

    void setPosition(Vector2 newPosition) {
        position = newPosition;
    }

    void setMovement(Vector2 newMovement) {
        movement = newMovement;
    }

    virtual float getCollisionRadius() const = 0;


    virtual void render() const = 0;

    virtual void handleWallCollision(int width, int height) = 0;
};
#endif //DOD_TOWERDEFENSE_OBJECT_H
