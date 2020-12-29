#include "bell.h"

#include <M5Stack.h>

Bell::Bell(int duration, std::vector<int> tones)
    : duration{duration}, tones{tones} {}

void Bell::Ring() {
    M5.Speaker.begin();
    for (auto t : this->tones) {
        M5.Speaker.tone(t);
        delay(this->duration);
    }
    M5.Speaker.mute();
    M5.Speaker.end();
}
