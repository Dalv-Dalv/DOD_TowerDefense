#ifndef DOD_TOWERDEFENSE_RENDERUTILS_H
#define DOD_TOWERDEFENSE_RENDERUTILS_H
#include "raylib.h"
#include "ShapeType.h"


inline void RenderShapedObject(const Vector2 &position, ShapeType shapeType, const Color &color, const float& size) {
    switch (shapeType) {
        case ShapeType::Square: {
            Vector2 s = {position.x - size, position.y - size};
            Vector2 l = {2 * size, 2 * size};
            break;
        }

        case ShapeType::Circle: {
            DrawCircleV(position, size, color);
            break;
        }

        case ShapeType::Triangle: {
            const Vector2 a = {position.x, position.y - size};
            const Vector2 b = {position.x - size, position.y + size};
            const Vector2 c = {position.x + size, position.y + size};

            DrawTriangle(a, b, c, color);
            break;
        }

        case ShapeType::Star: {
            DrawPoly(position, 3, size, 0, color);
            DrawPoly(position, 3, size, 60, color);
            break;
        }
    }
}

#endif //DOD_TOWERDEFENSE_RENDERUTILS_H
