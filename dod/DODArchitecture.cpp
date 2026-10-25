#include "DoDArchitecture.h"
#include "rlgl.h"
#include <cmath>
#include <cstdlib>
#include <algorithm>

void SimpleGrid::Clear() {
    std::fill(count, count + TOTAL_CELLS, 0);
}

void SimpleGrid::Add(int cx, int cy, int id) {
    int idx = cy * GRID_COLS + cx;
    if (count[idx] < MAX_PER_CELL) {
        cell[idx][count[idx]++] = id;
    }
}

DoDArchitecture::DoDArchitecture(int width, int height)
    : screenWidth(width), screenHeight(height) {}

void DoDArchitecture::init() {
    positions.resize(NUM_ELEMENTS);
    velocities.resize(NUM_ELEMENTS);
    colors.resize(NUM_ELEMENTS);
    shapes.resize(NUM_ELEMENTS);

    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        positions[i] = {
            RADIUS + (float)(rand() % (int)(screenWidth - DIAMETER)),
            RADIUS + (float)(rand() % (int)(screenHeight - DIAMETER))
        };

        float angle = ((float)rand() / RAND_MAX) * 6.2831853f;
        float speed = 25.0f + ((float)rand() / RAND_MAX) * 35.0f;
        velocities[i] = { cosf(angle) * speed, sinf(angle) * speed };

        colors[i] = Color{
            (unsigned char)(100 + rand() % 155),
            (unsigned char)(100 + rand() % 155),
            (unsigned char)(100 + rand() % 155),
            255
        };

        shapes[i] = static_cast<ShapeType>(rand() % COUNT);
    }
}

inline void DoDArchitecture::Collide(Vector2& pos1, Vector2& vel1, Vector2& pos2, Vector2& vel2) {
    float dx = pos2.x - pos1.x;
    float dy = pos2.y - pos1.y;
    float distSq = dx * dx + dy * dy;

    if (distSq > 0.0f && distSq < DIAMETER_SQ) {
        float dist = sqrtf(distSq);
        float nx = dx / dist;
        float ny = dy / dist;

        float overlap = 0.5f * (DIAMETER - dist);
        pos1.x -= nx * overlap; pos1.y -= ny * overlap;
        pos2.x += nx * overlap; pos2.y += ny * overlap;

        float p = nx * (vel1.x - vel2.x) + ny * (vel1.y - vel2.y);
        vel1.x -= p * nx; vel1.y -= p * ny;
        vel2.x += p * nx; vel2.y += p * ny;
    }
}

void DoDArchitecture::update(float dt) {
    grid.Clear();

    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        positions[i].x += velocities[i].x * dt;
        positions[i].y += velocities[i].y * dt;

        if (positions[i].x <= RADIUS) {
            positions[i].x = RADIUS; velocities[i].x = -velocities[i].x;
        } else if (positions[i].x >= screenWidth - RADIUS) {
            positions[i].x = screenWidth - RADIUS; velocities[i].x = -velocities[i].x;
        }

        if (positions[i].y <= RADIUS) {
            positions[i].y = RADIUS; velocities[i].y = -velocities[i].y;
        } else if (positions[i].y >= screenHeight - RADIUS) {
            positions[i].y = screenHeight - RADIUS; velocities[i].y = -velocities[i].y;
        }

        int cx = std::clamp((int)(positions[i].x / SimpleGrid::CELL_SIZE), 0, SimpleGrid::GRID_COLS - 1);
        int cy = std::clamp((int)(positions[i].y / SimpleGrid::CELL_SIZE), 0, SimpleGrid::GRID_ROWS - 1);
        grid.Add(cx, cy, i);
    }

    #pragma omp parallel for
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        int cx = std::clamp((int)(positions[i].x / SimpleGrid::CELL_SIZE), 0, SimpleGrid::GRID_COLS - 1);
        int cy = std::clamp((int)(positions[i].y / SimpleGrid::CELL_SIZE), 0, SimpleGrid::GRID_ROWS - 1);

        int minX = std::max(0, cx - 1), maxX = std::min(SimpleGrid::GRID_COLS - 1, cx + 1);
        int minY = std::max(0, cy - 1), maxY = std::min(SimpleGrid::GRID_ROWS - 1, cy + 1);

        for (int y = minY; y <= maxY; ++y) {
            for (int x = minX; x <= maxX; ++x) {
                int cellIdx = y * SimpleGrid::GRID_COLS + x;
                int cCount = grid.count[cellIdx];
                for (int k = 0; k < cCount; ++k) {
                    int other = grid.cell[cellIdx][k];
                    if (other > i) {
                        Collide(positions[i], velocities[i], positions[other], velocities[other]);
                    }
                }
            }
        }
    }
}

void DoDArchitecture::render() {
    rlBegin(RL_LINES);
    for (int i = 0; i < NUM_ELEMENTS; ++i) {
        rlColor4ub(colors[i].r, colors[i].g, colors[i].b, 255);
        float px = positions[i].x;
        float py = positions[i].y;

        switch (shapes[i]) {
            case SQUARE:
                rlVertex2f(px - RADIUS, py); rlVertex2f(px + RADIUS, py);
                break;
            case CIRCLE:
                rlVertex2f(px, py - RADIUS); rlVertex2f(px, py + RADIUS);
                break;
            case TRIANGLE:
                rlVertex2f(px - RADIUS, py - RADIUS); rlVertex2f(px + RADIUS, py + RADIUS);
                break;
            case STAR:
                rlVertex2f(px - RADIUS, py); rlVertex2f(px + RADIUS, py);
                rlVertex2f(px, py - RADIUS); rlVertex2f(px, py + RADIUS);
                break;
            default: break;
        }
    }
    rlEnd();
}