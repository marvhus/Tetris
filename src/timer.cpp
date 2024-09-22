#include "timer.hpp"

#include <assert.h>
#include <raylib.h>

void init(Timer *timer, float goal) {
    assert(timer);

    timer->goal = goal;
    timer->passed = 0.0f;
}

void tick(Timer *timer) {
    assert(timer);

    timer->passed += GetFrameTime();
}

bool check(Timer *timer) {
    assert(timer);

    if (timer->passed >= timer->goal) {
        timer->passed -= timer->goal;
        return true;
    }

    return false;
}

void reset(Timer *timer) {
    assert(timer);

    timer->passed = 0.0f;
}
