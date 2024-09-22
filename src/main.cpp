#include <raylib.h>
#include <stdlib.h>
#include <time.h>

#include "app.hpp"

int main(void) {
    srand(time(0));

    App app_state = {};
    init(&app_state);

    while (app_state.running) {
        handle_updates(&app_state);
        render_frame(&app_state);
    }

    deinit(&app_state);
}
