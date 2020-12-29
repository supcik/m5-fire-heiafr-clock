#pragma once
#ifndef _BELL_H
#define _BELL_H

#include <vector>

class Bell {
    int duration;
    std::vector<int> tones;

   public:
    Bell(int duration, std::vector<int> tones);
    void Ring();
};

#endif