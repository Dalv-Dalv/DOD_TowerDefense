
#ifndef DOD_TOWERDEFENSE_STAR_H
#define DOD_TOWERDEFENSE_STAR_H

#include "Shape.h"

class Star : public Shape {
public:
    Star(Vector2 position, Vector2 movement, Color color, float size)
        : Shape(position, movement, color, ShapeType::Star, size) {}


    void render() const override {
        DrawPoly(position, 3, size, 0, color);
        DrawPoly(position, 3, size, 60, color);
    }

};
#endif //DOD_TOWERDEFENSE_STAR_H