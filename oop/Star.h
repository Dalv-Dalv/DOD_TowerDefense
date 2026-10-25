#ifndef DOD_TOWERDEFENSE_STAR_H
#define DOD_TOWERDEFENSE_STAR_H

#include "Shape.h"

class Star : public Shape {
public:
    Star(Vector2 position, Vector2 movement, Color color, float size)
        : Shape(position, movement, color, ShapeType::Star, size) {
    }
};
#endif //DOD_TOWERDEFENSE_STAR_H
