#pragma once
#include <vector>
#include <cstdint>
#include "raylib.h"
#include "IArchitecture.h"

enum ShapeType : uint8_t { SQUARE = 0, CIRCLE, TRIANGLE, STAR, COUNT };

struct SimpleGrid {
    static constexpr int CELL_SIZE = 8;
    static constexpr int GRID_COLS = (1200 / CELL_SIZE) + 1;
    static constexpr int GRID_ROWS = (800 / CELL_SIZE) + 1;
    static constexpr int TOTAL_CELLS = GRID_COLS * GRID_ROWS;
    static constexpr int MAX_PER_CELL = 16;

    int count[TOTAL_CELLS];
    int cell[TOTAL_CELLS][MAX_PER_CELL];

    void Clear();
    void Add(int cx, int cy, int id);
};

class DoDArchitecture : public IArchitecture {
private:
    static constexpr int NUM_ELEMENTS = 100000;
    static constexpr float RADIUS = 1.5f;
    static constexpr float DIAMETER = RADIUS * 2.0f;
    static constexpr float DIAMETER_SQ = DIAMETER * DIAMETER;

    std::vector<Vector2> positions;
    std::vector<Vector2> velocities;
    std::vector<Color> colors;
    std::vector<ShapeType> shapes;

    SimpleGrid grid;
    int screenWidth;
    int screenHeight;

    void Collide(Vector2& pos1, Vector2& vel1, Vector2& pos2, Vector2& vel2);

public:
    DoDArchitecture(int width = 1200, int height = 800);
    ~DoDArchitecture() override = default;

    void init();
    void update(float dt);
    void render();
};