//
// Created by tarshpatar on 07.04.25.
//
#include "player.h"

int Player::getX() const
{
    return this->x - cam->x;
}

int Player::getY() const
{
    return this->y - cam->y;
}

void Player::movePlayer() {
    if (gb->getKey() < 1)
    {
        this->isMoving = false;
        return;
    }

    auto localMove = [this](const int &input,
        const int _x = 0, const int _y = 0)
    {
        this->direction = static_cast<Direction>(input);
        this->isMoving = true;
        if (this->walls_renderer->checkMatrix(
            32,
            this->getX() + _x,
            this->getY() + _y,
            [](GameBoy*, int, int){}
        )) return;
        //if (!(this->gb->isFree(this->getX() + _x, this->getY() + _y))) return;
        this->x += _x;
        this->y += _y;
    };

    const int input = gb->getKey();
    gb->wipePoint(this->getX(), this->getY());
    switch (input) {
    case DIR_UP:
        localMove(input, 0, -1);
        break;
    case DIR_DOWN:
        localMove(input, 0, 1);
        break;
    case DIR_RIGHT:
        localMove(input, 1, 0);
        break;
    case DIR_LEFT:
        localMove(input, -1, 0);
        break;
    default:
        break;
    }


    if (this->getX() > 5 && this->direction == DIR_RIGHT) {
        cam->moveCamera(1, 0);
    } else if (this->getX() < 2 && this->direction == DIR_LEFT)
    {
        cam->moveCamera(-1, 0);
    }
    if (this->getY() > 13 && this->direction == DIR_DOWN)
    {
        cam->moveCamera(0, 1);
    } else if (this->getY() < 2 && this->direction == DIR_UP)
    {
        cam->moveCamera(0, -1);
    }
}

void Player::drawPlayer() {
    if (millis() > this->blymBlymTime + 500)
    {
        this->isVisible = !this->isVisible;
        this->blymBlymTime = millis();
    }

    if (this->isVisible || this->isMoving)
    {
        gb->drawPoint(this->x - cam->x, this->y - cam->y);
    }
    else
    {
        gb->wipePoint(this->x - cam->x, this->y - cam->y);
    }
}
