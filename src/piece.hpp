#pragma once

#include <raylib.h>

#include "types.hpp"

#define CELLS_X 4
#define CELLS_Y 4

struct Piece_Cells {
    bool cells[CELLS_X * CELLS_Y]; // Not all pieces need a 4*4 grid, but all pieces fit within it.
};

#define PIECE_ROTATIONS 4

struct Piece_Rotations {
    Piece_Cells pieces[PIECE_ROTATIONS];
};

enum Piece {
    I = 0,
    O,
    T,
    S,
    Z,
    J,
    L,
    LAST,
};
extern Piece_Rotations pieces[Piece::LAST];

Color get_color(Piece piece);
Piece random_piece(void);
Piece_Cells get_piece_cells(Piece piece, u8 rotation);
uint cells_pos_to_index(uint x, uint y);
