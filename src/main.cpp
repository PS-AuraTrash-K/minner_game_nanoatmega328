#include "joinHeader.h"

GameBoy gb;

Thread myThread = Thread();

Camera cam;
Player player;

auto walls_renderer = TileMapElement<uint32_t>();
auto chests = SingleMapElement<char>();

void setup()
{
    gb.begin(1);

    player.gb = &gb;
    player.cam = &cam;
    player.walls_renderer = &walls_renderer;

    cam.gb = &gb;
    cam.setFunc([] {walls_renderer.run();});

    walls_renderer.setCamera(&cam).setData(Map::walls).setGameBoy(&gb).setFunction(MapHelper::draw);
    walls_renderer.run();

    chests.setCamera(&cam).setData(Map::chests).setGameBoy(&gb).setFunction(ChestHelper::draw);
    chests.run();

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
