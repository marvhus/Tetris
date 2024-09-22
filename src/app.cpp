#include "app.hpp"

#include <assert.h>
#include <raylib.h>

#include "game.hpp"

internal inline void reset(App *app_state) {
    deinit(&app_state->game_state);
    init(&app_state->game_state);

    reset(&app_state->startup_timer);
    app_state->paused = true;
}

void init(App *app_state) {
    assert(app_state);

    app_state->game_state = {};
    init(&app_state->game_state);

    app_state->running = true;

    app_state->width = 360;
    app_state->height = 640;

    app_state->paused = true;

    init(&app_state->startup_timer, 1.0);

    InitWindow(app_state->width, app_state->height, "Tetris");
    SetTargetFPS(60);
}

void deinit(App *app_state) {
    assert(app_state);

    CloseWindow();

    deinit(&app_state->game_state);
}

void render_frame(App *app_state) {
    assert(app_state);

    if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) app_state->running = false;

    if (app_state->game_state.game_over) {
        if (IsKeyPressed(KEY_SPACE)) reset(app_state);
    } else {
        if (IsKeyPressed(KEY_BACKSPACE)) reset(app_state);
    }

    if (app_state->paused) {
        tick(&app_state->startup_timer);
        if (check(&app_state->startup_timer)) app_state->paused = false;
    } else {
        handle_updates(&app_state->game_state);
    }
}

void handle_updates(App *app_state) {
    assert(app_state);

    BeginDrawing();
        ClearBackground(BLACK);

        draw_board(&app_state->game_state, 5, 5, app_state->height - 10, 2);
    EndDrawing();
}
