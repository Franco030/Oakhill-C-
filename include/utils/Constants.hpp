#pragma once

namespace Constants {

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

constexpr float PLAYER_SPEED = 120.0f;
constexpr float RESIZE_FACTOR = 4.0f;
constexpr int TRANSITION_BIAS = 20;
constexpr int DEATH_DELAY_MS = 3000;

constexpr int INITIAL_ZONE_Y = 5;
constexpr int INITIAL_ZONE_X = 2;

constexpr float MAX_DELTA_TIME = 0.05f;

constexpr int WORLD_MAP_LEVEL[6][6] = {{0, 0, 1, 1, 1, 1}, {0, 1, 1, 0, 0, 0}, {0, 1, 0, 1, 1, 1},
                                       {0, 1, 1, 1, 0, 0}, {0, 0, 1, 0, 1, 0}, {0, 1, 1, 1, 0, 0}};

constexpr int SCHOOL_MAP_LEVEL[5][5] = {
    {1, 1, 0, 1, 0}, {1, 0, 1, 1, 1}, {1, 0, 1, 1, 1}, {1, 1, 1, 0, 1}, {1, 0, 1, 0, 1}};

} // namespace Constants