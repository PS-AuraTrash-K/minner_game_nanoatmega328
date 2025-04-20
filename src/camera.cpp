//
// Created by tarshpatar on 07.04.25.
//
#include "camera.h"
#include "variables.h"

void Camera::moveCamera(const int _x, const int _y) {
    if (this->x + _x >= 0 && this->x + _x <= MAP_SIZE_X - CAM_SIZE_X && _x != 0)
    {
        this->x += _x;
        gb->clearDisplay();
        redrawFunc();
    }
    if (this->y + _y >= 0 && this->y + _y <= MAP_SIZE_Y - CAM_SIZE_Y && _y != 0)
    {
        this->y += _y;
        gb->clearDisplay();
        redrawFunc();
    }
}