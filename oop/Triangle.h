
#ifndef DOD_TOWERDEFENSE_TRIANGLE_H
#define DOD_TOWERDEFENSE_TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape {
public:
    Triangle(Vector2 position, Vector2 movement, Color color, float size)
        : Shape(position, movement, color, ShapeType::Triangle, size) {}

    void render() const override {
        Vector2 a = {position.x, position.y - size};
        Vector2 b = {position.x - size, position.y + size};
        Vector2 c = {position.x + size, position.y + size};

        DrawTriangle(a, b, c, color);
    }
};

#endif //DOD_TOWERDEFENSE_TRIANGLE_H
