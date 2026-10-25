#ifndef DOD_TOWERDEFENSE_TRIANGLE_H
#define DOD_TOWERDEFENSE_TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape {
public:
    Triangle(Vector2 position, Vector2 movement, Color color, float size)
        : Shape(position, movement, color, ShapeType::Triangle, size) {
    }
};

#endif //DOD_TOWERDEFENSE_TRIANGLE_H
