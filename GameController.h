#pragma once
#include "Base.h"
#include "TerrainMap.h"

class GameController {
private:
    std::unique_ptr<UnitFactory> factory;
    std::shared_ptr<Base> base;
    std::shared_ptr<TerrainMap> map;
    int turn;

    void gameLoop();            
    void processTurn(int turn);
    void testTerrainAndCounter();
public:
    GameController();
    void run();
};