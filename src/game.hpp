#pragma once

#include <raylib.h>

#include "timer.hpp"
#include "types.hpp"
#include "piece.hpp"

#define TILES_X 10
#define TILES_Y 18

#define BACKGROUND_COLOR (Color){.r = 24, .g = 24, .b = 24, .a = 255};

struct Board {
    bool  cells[TILES_X * TILES_Y];
    Color colors[TILES_X * TILES_Y];
};

struct Game {
    Board board_state;

    Piece piece;
    u8 piece_rotation;
    int piece_x;
    int piece_y;

    Timer fall_timer;

    bool game_over;
};

void init(Game *game_state);
void deinit(Game *game_state);

void handle_updates(Game *game_state);
void draw_board(Game *game_state, uint x_pos, uint y_pos, uint height, uint padding);
