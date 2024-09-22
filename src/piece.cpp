#include "piece.hpp"

#include <stdlib.h>
#include <assert.h>
#include <raylib.h>

#include "types.hpp"

internal Piece draw_piece(bool *bag, uint size) {
    uint slot = rand() % size;

    // Find first unused slot in bag after randomly selected slot.
    for (uint offset = 0; offset < size; ++offset) {
        uint i = (slot + offset) % size;
        if (bag[i] == true) {
            bag[i] = false;
            return (Piece) i;
        }
    }

    // Bag is empty, reset it.
    for (uint i = 0; i < size; ++i) bag[i] = true;

    bag[slot] = false;
    return (Piece) slot;
}

Color get_color(Piece piece) {
    switch (piece) {
        case Piece::I:
            return (Color){.r = 000, .g = 255, .b = 255, .a = 255};
        case Piece::O:
            return (Color){.r = 255, .g = 255, .b = 000, .a = 255};
        case Piece::T:
            return (Color){.r = 153, .g = 000, .b = 255, .a = 255};
        case Piece::S:
            return (Color){.r = 000, .g = 255, .b = 000, .a = 255};
        case Piece::Z:
            return (Color){.r = 255, .g = 000, .b = 000, .a = 255};
        case Piece::J:
            return (Color){.r = 000, .g = 000, .b = 255, .a = 255};
        case Piece::L:
            return (Color){.r = 255, .g = 170, .b = 000, .a = 255};
        case Piece::LAST:
            TraceLog(LOG_ERROR, "Invalid piece.");
            assert(false);
    }
    return BLACK;
}

Piece random_piece(void) {
    local_persist bool bag[Piece::LAST] = {};

    return draw_piece(bag, sizeof bag);
}

Piece_Cells get_piece_cells(Piece piece, u8 rotation) {
    rotation %= PIECE_ROTATIONS;

    return pieces[piece].pieces[rotation];
}

uint cells_pos_to_index(uint x, uint y) {
    return (y * CELLS_X) + x;
}

Piece_Rotations pieces[Piece::LAST] = {
    { // Piece::I
        (Piece_Cells){{
            0, 0, 0, 0,
            1, 1, 1, 1,
            0, 0, 0, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 0, 1, 0,
            0, 0, 1, 0,
            0, 0, 1, 0,
            0, 0, 1, 0,
        }},
        (Piece_Cells){{
            0, 0, 0, 0,
            0, 0, 0, 0,
            1, 1, 1, 1,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 0, 0,
        }},
    },
    { // Piece::O
        (Piece_Cells){{
            0, 1, 1, 0,
            0, 1, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 1, 1, 0,
            0, 1, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 1, 1, 0,
            0, 1, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 1, 1, 0,
            0, 1, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        }},
    },
    { // Piece::T
        (Piece_Cells){{
            0, 1, 0, 0,
            1, 1, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 1, 0, 0,
            0, 1, 1, 0,
            0, 1, 0, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 0, 0, 0,
            1, 1, 1, 0,
            0, 1, 0, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 1, 0, 0,
            1, 1, 0, 0,
            0, 1, 0, 0,
            0, 0, 0, 0,
        }},
    },
    { // Piece::S
        (Piece_Cells){{
            0, 1, 1, 0,
            1, 1, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 1, 0, 0,
            0, 1, 1, 0,
            0, 0, 1, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 0, 0, 0,
            0, 1, 1, 0,
            1, 1, 0, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            1, 0, 0, 0,
            1, 1, 0, 0,
            0, 1, 0, 0,
            0, 0, 0, 0,
        }},
    },
    { // Piece::Z
        (Piece_Cells){{
            1, 1, 0, 0,
            0, 1, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 0, 1, 0,
            0, 1, 1, 0,
            0, 1, 0, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 0, 0, 0,
            1, 1, 0, 0,
            0, 1, 1, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 1, 0, 0,
            1, 1, 0, 0,
            1, 0, 0, 0,
            0, 0, 0, 0,
        }},
    },
    { // Piece::J
        (Piece_Cells){{
            1, 0, 0, 0,
            1, 1, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 1, 1, 0,
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 0, 0, 0,
            1, 1, 1, 0,
            0, 0, 1, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 1, 0, 0,
            0, 1, 0, 0,
            1, 1, 0, 0,
            0, 0, 0, 0,
        }},
    },
    { // Piece::L
        (Piece_Cells){{
            0, 0, 1, 0,
            1, 1, 1, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 1, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            0, 0, 0, 0,
            1, 1, 1, 0,
            1, 0, 0, 0,
            0, 0, 0, 0,
        }},
        (Piece_Cells){{
            1, 1, 0, 0,
            0, 1, 0, 0,
            0, 1, 0, 0,
            0, 0, 0, 0,
        }},
    },
};
