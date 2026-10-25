//
// Created by Rares on 10/18/2026.
//

#ifndef DOD_TOWERDEFENSE_SQUARE_H
#define DOD_TOWERDEFENSE_SQUARE_H

#include "Shape.h"

class Square : public Shape {
public:
    Square(Vector2 position, Vector2 movement, Color color, float size) : Shape(
        position, movement, color, ShapeType::Square, size) {
    }
};
#endif //DOD_TOWERDEFENSE_SQUARE_H
