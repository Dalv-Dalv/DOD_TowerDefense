#ifndef DOD_TOWERDEFENSE_RENDERUTILS_H
#define DOD_TOWERDEFENSE_RENDERUTILS_H
#include "raylib.h"
#include "ShapeType.h"

struct RenderResources {
    Texture2D texSquare;
    Texture2D texCircle;
    Texture2D texTriangle;
    Texture2D texStar;
    bool initialized = false;
};

inline RenderResources renderResources;

inline void InitRenderResources() {
    if (renderResources.initialized) return;

    auto generateTexture = [](ShapeType shapeType) -> Texture2D {
        constexpr int size = 64;
        RenderTexture2D target = LoadRenderTexture(size, size);
        BeginTextureMode(target);
        ClearBackground(BLANK);

        switch (shapeType) {
            case ShapeType::Square:
                DrawRectangle(2, 2, size - 4, size - 4, WHITE);
                break;
            case ShapeType::Circle:
                DrawCircle(size / 2, size / 2, size - 2, WHITE);
                break;
            case ShapeType::Triangle:
                DrawTriangle({size / 2, 2}, {2, size - 2}, {size - 2, size - 2}, WHITE);
                break;
            case ShapeType::Star:
                DrawPoly({size / 2, size / 2}, 3, size / 2 - 2, 0, WHITE);
                DrawPoly({size / 2, size / 2}, 3, size / 2 - 2, size - 4, WHITE);
                break;
        }

        EndTextureMode();
        return target.texture;
    };

    renderResources.texSquare = generateTexture(ShapeType::Square);
    renderResources.texCircle = generateTexture(ShapeType::Circle);
    renderResources.texTriangle = generateTexture(ShapeType::Triangle);
    renderResources.texStar = generateTexture(ShapeType::Star);
    renderResources.initialized = true;
}

inline void RenderShapedObject(const Vector2 &position, ShapeType shapeType, const Color &color, const float size) {
    Texture2D tex;
    switch (shapeType) {
        case ShapeType::Square:   tex = renderResources.texSquare; break;
        case ShapeType::Circle:   tex = renderResources.texCircle; break;
        case ShapeType::Triangle: tex = renderResources.texTriangle; break;
        case ShapeType::Star:     tex = renderResources.texStar; break;
    }

    Rectangle sourceRect = { 0.0f, 0.0f, (float)tex.width, (float)tex.height };
    Rectangle destRect = { position.x, position.y, size * 2.0f, size * 2.0f };
    Vector2 origin = { size, size };

    DrawTexturePro(tex, sourceRect, destRect, origin, 0.0f, color);
}

#endif //DOD_TOWERDEFENSE_RENDERUTILS_H
