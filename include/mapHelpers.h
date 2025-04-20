//
// Created by tarshpatar on 13.04.25.
//
#pragma once
#include "joinHeader.h"

namespace MapHelper {
    inline void draw(GameBoy *gb, int x, int y)
    {
        gb->drawPoint(x, y);
    }
}

namespace ChestHelper {
    int blynktime = 150;
    bool isVisible = true;
    unsigned long time = 0;

    inline void draw(GameBoy *gb, int x, int y)
    {
        if (millis() > time + blynktime)
        {
            isVisible = !isVisible;
            time = millis();
        }

        if (isVisible)
        {
            gb->drawPoint(x, y);
            blynktime = 1000;
        } else
        {
            gb->wipePoint(x, y);
            blynktime = 250;
        }
    }
}