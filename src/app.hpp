#pragma once

#include "game.hpp"
#include "timer.hpp"

struct App {
    Game game_state;
    bool running;
    uint width;
    uint height;

    bool paused;
    Timer startup_timer;
};

void init(App *app_state);
void deinit(App *app_state);

void render_frame(App *app_state);
void handle_updates(App *app_state);
