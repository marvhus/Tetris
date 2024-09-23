#include "game.hpp"

#include <assert.h>

#include "raylib.h"
#include "types.hpp"
#include "piece.hpp"

internal inline uint board_pos_to_index(uint x, uint y) {
    return (y * TILES_X) + x;
}

internal void apply_piece(Game game_state, Board *board_state) {
    Piece_Cells piece_cells = get_piece_cells(game_state.piece, game_state.piece_rotation);
    Color piece_color = get_color(game_state.piece);

    for (int y = 0; y < CELLS_Y; ++y) {
        int board_y = game_state.piece_y + y;
        for (int x = 0; x < CELLS_X; ++x) {
            int board_x = game_state.piece_x + x;

            if (piece_cells.cells[cells_pos_to_index(x, y)] == false) continue;

            if (board_y >= TILES_Y
             || board_y < 0
             || board_x >= TILES_X
             || board_x < 0) continue;

            uint board_pos = board_pos_to_index(board_x, board_y);
            uint piece_pos = cells_pos_to_index(x, y);
            board_state->cells[board_pos] = piece_cells.cells[piece_pos];
            board_state->colors[board_pos] = piece_color;
        }
    }
}

internal inline bool is_game_board_valid(Game game_state) {
    Piece_Cells piece_cells = get_piece_cells(game_state.piece, game_state.piece_rotation);

    for (int y = 0; y < CELLS_Y; ++y) {
        int board_y = game_state.piece_y + y;
        for (int x = 0; x < CELLS_X; ++x) {
            int board_x = game_state.piece_x + x;

            if (piece_cells.cells[cells_pos_to_index(x, y)] == false) continue;

            if (board_y >= TILES_Y
             || board_x >= TILES_X
             || board_x < 0) return false;

            // Check overlap.
            bool filled = game_state.board_state.cells[board_pos_to_index(board_x, board_y)] == true
                       && piece_cells.cells[cells_pos_to_index(x, y)] == true;
            if (filled) return false;
        }
    }

    return true;
}

internal inline bool reset_piece(Game *game_state) {
    game_state->piece = random_piece();
    game_state->piece_rotation = 0;
    game_state->piece_x = 4;
    game_state->piece_y = 0;

    bool valid_start = is_game_board_valid(*game_state) == false;
    return valid_start;
}

internal void clear_lines(Board *board_state) {
    Board new_board_state = {};

    int current_y = TILES_Y - 1;
    for (int y = current_y; y > 0; --y) {

        // Check if current line is filled.
        bool filled = true;
        for (uint x = 0; x < TILES_X; ++x) {
            filled = board_state->cells[board_pos_to_index(x, y)];
            if (filled == false) break;
        }

        // Skip filled lines.
        if (filled) continue;

        // Copy over the line.
        for (uint x = 0; x < TILES_X; ++x) {
            uint current = board_pos_to_index(x, current_y);
            uint reading = board_pos_to_index(x, y);
            new_board_state.cells[current] = board_state->cells[reading];
            new_board_state.colors[current] = board_state->colors[reading];
        }

        // Move to next line.
        current_y--;
    }

    // Copy over new lines.
    *board_state = new_board_state;
}

internal void handle_input(Game *game_state) {
    if (IsKeyPressed(KEY_SPACE)) { // Instant fall.
        // Move to highest point bellow that piece can stop at.
        while (is_game_board_valid(*game_state)) game_state->piece_y += 1;
        game_state->piece_y -= 1;

        apply_piece(*game_state, &game_state->board_state);
        clear_lines(&game_state->board_state);

        game_state->game_over = reset_piece(game_state);
    }

    if (IsKeyPressed(KEY_W)) { // Rotate right.
        game_state->piece_rotation += 1;
        game_state->piece_rotation %= PIECE_ROTATIONS;

        if (is_game_board_valid(*game_state) == false) {
            game_state->piece_rotation -= 1;
            game_state->piece_rotation %= PIECE_ROTATIONS;
        }
    }
    if (IsKeyPressed(KEY_A)) { // Move left.
        game_state->piece_x -= 1;
        if (is_game_board_valid(*game_state) == false) {
            game_state->piece_x += 1;
        }
    }
    if (IsKeyPressed(KEY_D)) { // Move right.
        game_state->piece_x += 1;
        if (is_game_board_valid(*game_state) == false) {
            game_state->piece_x -= 1;
        }
    }

    if (IsKeyDown(KEY_S)) { // Increase fall speed.
        game_state->fall_timer.goal = 0.25f;
    } else {
        game_state->fall_timer.goal = 0.75f;
    }
}

void init(Game *game_state) {
    assert(game_state);

    game_state->board_state = {};

    game_state->game_over = reset_piece(game_state);

    game_state->fall_timer = {
        .goal = 0.75f,
        .passed = 0.0f,
    };
}

void deinit(Game *game_state) {
    assert(game_state);

    // :)
}

void handle_updates(Game *game_state) {
    if (game_state->game_over) return; // No updating while the game is over.

    handle_input(game_state);

    tick(&game_state->fall_timer);
    if (check(&game_state->fall_timer)) { // Piece fall.
        game_state->piece_y += 1;
        game_state->piece_y %= TILES_Y;

        // Reuse to check collision with floor / other pieces.
        if (is_game_board_valid(*game_state) == false) {
            game_state->piece_y -= 1;

            apply_piece(*game_state, &game_state->board_state);
            clear_lines(&game_state->board_state);
            game_state->game_over = reset_piece(game_state);
        }
    }
}

void draw_board(Game *game_state, uint x_pos, uint y_pos, uint height, uint padding) {
    assert(game_state);

    uint tile_size  = (height / TILES_Y);
    uint render_size = tile_size - padding * 2;

    Board render_board = game_state->board_state;

    // Only draw piece when it's not game over.
    if (game_state->game_over == false) apply_piece(*game_state, &render_board);

    for (uint i = 0; i < sizeof game_state->board_state; ++i) {
        bool tile = render_board.cells[i];
        uint x = ((i % TILES_X) * tile_size) + padding + x_pos;
        uint y = ((i / TILES_X) * tile_size) + padding + y_pos;

        Color color = tile ? render_board.colors[i] : BACKGROUND_COLOR;
        DrawRectangle(x, y, render_size, render_size, color);
    }
}
