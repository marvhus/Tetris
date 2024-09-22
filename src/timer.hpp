#pragma once

struct Timer {
    float goal;
    float passed;
};

void init(Timer *timer, float goal);
void tick(Timer *timer);
bool check(Timer *timer);
void reset(Timer *timer);
