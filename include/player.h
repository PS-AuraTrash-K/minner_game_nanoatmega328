//
// Created by tarshpatar on 07.04.25.
//
#pragma once
#include "camera.h"
#include <GameBoy.h>

enum Direction {
    DIR_UP = 3,
    DIR_DOWN = 6,
    DIR_LEFT = 4,
    DIR_RIGHT = 5
};

struct Player {
    Direction direction = DIR_DOWN;

    int x = 2;
    int y = 2;

    unsigned long time = 0;
    unsigned long blymBlymTime = 0;

    bool isVisible = true;
    bool isMoving = false;

    Camera *cam;
    GameBoy *gb;

    int getX() const;
    int getY() const;
    void movePlayer();
    void drawPlayer();
};