//
// Created by tarshpatar on 07.04.25.
//

#pragma once
#include <GameBoy.h>

struct Camera {
    void (*redrawFunc)() {};
    int x = 0;
    int y = 0;

    GameBoy *gb{};

    Camera& setFunc(void (*redrawFunc)())
    {
        this->redrawFunc = redrawFunc;
        return *this;
    }

    void moveCamera(int _x, int _y);
};
