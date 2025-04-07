#include <Arduino.h>
#include <Thread.h>
#include <GameBoy.h>
#include "mapComponents.h"
#include "soundtrack.h"
#define CAM_SIZE_X 8
#define CAM_SIZE_Y 16
#define MAP_SIZE_X 32
#define MAP_SIZE_Y 32

GameBoy gb;

struct Camera {
    int x = 0;
    int y = 0;
};

Camera cam;


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

    int getX() const
    {
        return this->x - cam.x;
    }
    int getY() const
    {
        return this->y - cam.y;
    }
};

Player player;

bool isVisible = true;

void getArray(const uint32_t *map, void (*func)(int x, int y))
{
    for (int elemX = cam.x; elemX < cam.x + CAM_SIZE_X; elemX++) {
        for (int elemY = cam.y; elemY < cam.y + CAM_SIZE_Y; elemY++) {
            if ((pgm_read_dword(&map[elemY]) >> (31 - elemX)) & 1) {
                func(elemX - cam.x, elemY - cam.y);
            }
        }
    }
}

void _drawMap(int x, int y)
{
    gb.drawPoint(x, y);
}

unsigned long chestTime =0;

void _drawChest(int x, int y)
{
    if (millis() > chestTime + 150)
    {
        isVisible = !isVisible;
        chestTime = millis();
    }

    if (isVisible)
    {
        gb.drawPoint(x, y);
    } else
    {
        gb.wipePoint(x, y);
    }
}

void drawMap() {
    getArray(walls, _drawMap);
}

void moveCamera(int x, int y) {
    if (cam.x + x >= 0 && cam.x + x <= MAP_SIZE_X - CAM_SIZE_X && x != 0)
    {
        cam.x += x;
        gb.clearDisplay();
        drawMap();
    }
    if (cam.y + y >= 0 && cam.y + y <= MAP_SIZE_Y - CAM_SIZE_Y && y != 0)
    {
        cam.y += y;
        gb.clearDisplay();
        drawMap();
    }
}

void movePlayer() {
    if (gb.getKey() < 1)
    {
        player.isMoving = false;
        return;
    }

    auto localMove = [](Player &player,const int &input,
        const int x = 0, const int y = 0)
    {
        player.direction = static_cast<Direction>(input);
        player.isMoving = true;
        if (!gb.isFree(player.getX() + x, player.getY() + y)) return false;
        player.x += x;
        player.y += y;
        return true;
    };

    const int input = gb.getKey();
    gb.wipePoint(player.getX(), player.getY());
    switch (input) {
    case DIR_UP:
            localMove(player, input, 0, -1);
            break;
        case DIR_DOWN:
             localMove(player, input, 0, 1);
            break;
        case DIR_RIGHT:
            localMove(player, input, 1, 0);
            break;
        case DIR_LEFT:
            localMove(player, input, -1, 0);
            break;
        default:
            break;
    }


    if (player.getX() > 5 && player.direction == DIR_RIGHT) {
        moveCamera(1, 0);
    } else if (player.getX() < 2 && player.direction == DIR_LEFT)
    {
        moveCamera(-1, 0);
    }
    if (player.getY() > 13 && player.direction == DIR_DOWN)
    {
        moveCamera(0, 1);
    } else if (player.getY() < 2 && player.direction == DIR_UP)
    {
        moveCamera(0, -1);
    }
}

void drawPlayer() {
    if (millis() > player.blymBlymTime + 500)
    {
        player.isVisible = !player.isVisible;
        player.blymBlymTime = millis();
    }

    if (player.isVisible || player.isMoving)
    {
        gb.drawPoint(player.x - cam.x, player.y - cam.y);
    }
    else
    {
        gb.wipePoint(player.x - cam.x, player.y - cam.y);
    }
}


Thread myThread = Thread();

void setup()
{
    gb.begin(1);
    drawMap();
    Serial.begin(9600);
    myThread.onRun(setupSound);
}



void loop() {
    if (millis() > player.time + 150) {
        movePlayer();
        player.time = millis();
    }

    if (myThread.shouldRun()) {
        //myThread.run();
    }


    getArray(chests, _drawChest);

    drawPlayer();
}
