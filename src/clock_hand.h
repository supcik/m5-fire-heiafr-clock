#pragma once
#ifndef _CLOCK_HAND_H
#define _CLOCK_HAND_H

class ClockHand {
    float x0, y0, l1, l2, d1, d2;

   public:
    ClockHand(float x0, float y0, float l1, float l2, float d1, float d2);
    void Draw(float angle);
};

#endif