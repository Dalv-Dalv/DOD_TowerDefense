
#ifndef DOD_TOWERDEFENSE_SHAPE_H
#define DOD_TOWERDEFENSE_SHAPE_H

#include "Object.h"

class Shape : public Object {
protected:
    float size;

public:
    Shape(Vector2 position, Vector2 movement, Color color, ShapeType shapeType, float size): Object(position, movement, color, shapeType), size(size) {}
};

#endif //DOD_TOWERDEFENSE_SHAPE_H