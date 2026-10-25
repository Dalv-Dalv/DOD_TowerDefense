#ifndef DOD_TOWERDEFENSE_SHAPE_H
#define DOD_TOWERDEFENSE_SHAPE_H

#include "Object.h"
#include "../Shared/RenderUtils.h"

class Shape : public Object {
protected:
    float size;

public:
    Shape(Vector2 position, Vector2 movement, Color color, ShapeType shapeType, float size) : Object(position, movement,
        color, shapeType), size(size) {
    }


    void handleWallCollision(int width, int height) override {
        if (position.x - size < 0) {
            position.x = size;
            if (movement.x < 0)
                movement.x = -movement.x;
        }

        if (position.x + size > width) {
            position.x = width - size;
            if (movement.x > 0)
                movement.x = -movement.x;
        }

        if (position.y - size < 0) {
            position.y = size;
            if (movement.y < 0)
                movement.y = -movement.y;
        }

        if (position.y + size > height) {
            position.y = height - size;
            if (movement.y > 0)
                movement.y = -movement.y;
        }
    }

    float getCollisionRadius() const override {
        return size;
    }

    void render() const override {
        RenderShapedObject(position, shape, color, size);
    }
};

#endif //DOD_TOWERDEFENSE_SHAPE_H
