#include <Arduino.h>
#include <Thread.h>
#include <GameBoy.h>
#include "mapElement.h"
#include "mapComponents.h"
#include "soundtrack.h"
#include "camera.h"
#include "player.h"
#include "variables.h"

GameBoy gb;

int blynkChestTime = 150;




bool isVisible = true;



void _drawMap(int x, int y)
{
    gb.drawPoint(x, y);
}

unsigned long chestTime =0;

void _drawChest(int x, int y)
{
    if (millis() > chestTime + blynkChestTime)
    {
        isVisible = !isVisible;
        chestTime = millis();
    }

    if (isVisible)
    {
        gb.drawPoint(x, y);
        blynkChestTime = 1000;
    } else
    {
        gb.wipePoint(x, y);
        blynkChestTime = 250;
    }
}


// void moveCamera(int x, int y) {
//     if (cam.x + x >= 0 && cam.x + x <= MAP_SIZE_X - CAM_SIZE_X && x != 0)
//     {
//         cam.x += x;
//         gb.clearDisplay();
//         drawMap();
//     }
//     if (cam.y + y >= 0 && cam.y + y <= MAP_SIZE_Y - CAM_SIZE_Y && y != 0)
//     {
//         cam.y += y;
//         gb.clearDisplay();
//         drawMap();
//     }
// }

// void movePlayer() {
//     if (gb.getKey() < 1)
//     {
//         player.isMoving = false;
//         return;
//     }
//
//     auto localMove = [](Player &player,const int &input,
//         const int x = 0, const int y = 0)
//     {
//         player.direction = static_cast<Direction>(input);
//         player.isMoving = true;
//         if (!gb.isFree(player.getX() + x, player.getY() + y)) return false;
//         player.x += x;
//         player.y += y;
//         return true;
//     };
//
//     const int input = gb.getKey();
//     gb.wipePoint(player.getX(), player.getY());
//     switch (input) {
//     case DIR_UP:
//             localMove(player, input, 0, -1);
//             break;
//         case DIR_DOWN:
//              localMove(player, input, 0, 1);
//             break;
//         case DIR_RIGHT:
//             localMove(player, input, 1, 0);
//             break;
//         case DIR_LEFT:
//             localMove(player, input, -1, 0);
//             break;
//         default:
//             break;
//     }
//
//
//     if (player.getX() > 5 && player.direction == DIR_RIGHT) {
//         moveCamera(1, 0);
//     } else if (player.getX() < 2 && player.direction == DIR_LEFT)
//     {
//         moveCamera(-1, 0);
//     }
//     if (player.getY() > 13 && player.direction == DIR_DOWN)
//     {
//         moveCamera(0, 1);
//     } else if (player.getY() < 2 && player.direction == DIR_UP)
//     {
//         moveCamera(0, -1);
//     }
// }
//
// void drawPlayer() {
//     if (millis() > player.blymBlymTime + 500)
//     {
//         player.isVisible = !player.isVisible;
//         player.blymBlymTime = millis();
//     }
//
//     if (player.isVisible || player.isMoving)
//     {
//         gb.drawPoint(player.x - cam.x, player.y - cam.y);
//     }
//     else
//     {
//         gb.wipePoint(player.x - cam.x, player.y - cam.y);
//     }
// }


Thread myThread = Thread();

Camera cam;
Player player;

MapElement<uint32_t> walls_renderer = MapElement<uint32_t>();

void setup()
{
    player.gb = &gb;
    player.cam = &cam;

    cam.gb = &gb;
    cam.setFunc([](){walls_renderer.runMatrix();});

    walls_renderer.setCamera(&cam).setData(Map::walls).setFunction(_drawMap);
    walls_renderer.runMatrix();

    gb.begin(1);

    Serial.begin(9600);
    myThread.onRun(setupSound);
}



void loop() {
    if (millis() > player.time + 150) {
        player.movePlayer();
        player.time = millis();
    }

    if (myThread.shouldRun()) {
        //myThread.run();
    }


    player.drawPlayer();
}
