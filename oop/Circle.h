
#ifndef DOD_TOWERDEFENSE_CIRCLE_H
#define DOD_TOWERDEFENSE_CIRCLE_H

#include "Shape.h"

class Circle : public Shape {
    public:
    Circle(Vector2 position, Vector2 movement, Color color, float size): Shape(position, movement, color, ShapeType::Circle, size) {}

    void render() const override {
        DrawCircleV(position, size, color);
    }
};
#endif //DOD_TOWERDEFENSE_CIRCLE_H