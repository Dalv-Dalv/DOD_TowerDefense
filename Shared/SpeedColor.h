
#ifndef DOD_TOWERDEFENSE_SPEEDCOLOR_H
#define DOD_TOWERDEFENSE_SPEEDCOLOR_H

#include "raylib.h"
#include <algorithm>
#include <cmath>

inline Color GetSpeedColor(Vector2 velocity, float speedMultiplier) {
    float speed = sqrtf(velocity.x * velocity.x +
                        velocity.y * velocity.y);

    speed *= speedMultiplier;

    float t = speed / (speed + 150.0f);
    float hue = 240.0f * (1.0f - t);

    return ColorFromHSV(hue, 0.95f, 0.95f);
}

#endif
