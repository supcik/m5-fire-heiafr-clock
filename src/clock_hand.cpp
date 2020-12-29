#include "clock_hand.h"

#include <Arduino.h>
#include <M5Stack.h>

ClockHand::ClockHand(float x0, float y0, float l1, float l2, float d1, float d2)
    : x0{x0}, y0{y0}, l1{l1}, l2{l2}, d1{d1}, d2{d2} {}

void ClockHand::Draw(float angle) {
    int p1x = round(x0 + l1 * cos(angle - d1));
    int p1y = round(y0 - l1 * sin(angle - d1));

    int p2x = round(x0 + l1 * cos(angle + d1));
    int p2y = round(y0 - l1 * sin(angle + d1));

    int p3x = round(x0 + l2 * cos(angle + PI - d2));
    int p3y = round(y0 - l2 * sin(angle + PI - d2));

    int p4x = round(x0 + l2 * cos(angle + PI + d2));
    int p4y = round(y0 - l2 * sin(angle + PI + d2));

    M5.lcd.fillTriangle(p1x, p1y, p2x, p2y, p3x, p3y, 0);
    M5.lcd.fillTriangle(p1x, p1y, p3x, p3y, p4x, p4y, 0);
}