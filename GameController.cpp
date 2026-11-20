#include "GameController.h"
#include <iostream>
#include <memory>

using namespace std;

GameController::GameController(): factory(std::make_unique<ForestFactory>()),
    base(std::make_shared<Base>(1000, 10, 5, 500, factory.get(), 0, 0)),
    map(std::make_shared<TerrainMap>(10, 10)),
    turn(0) {}
void GameController::run() {
    cout << "ИНТЕГРАЦИОННЫЙ СЦЕНАРИЙ" << endl;
    testTerrainAndCounter();
    gameLoop();
}

void GameController::gameLoop() {
    const int MAX_TURNS = 3;
    for (turn = 1; turn <= MAX_TURNS; ++turn) {
        cout << "\nХОД " << turn << endl;
        processTurn(turn);
    }

    cout << "\nИТОГИ" << endl;
    cout << "Юнитов в базе осталось: " << base->getUnitCount() << endl;
    cout << "Уничтоженные юниты (ID): ";
    for (int id : base->getDestroyedUnits()) {
        cout << id << " ";
    }
    cout << endl;
}

void GameController::processTurn(int turn) {
    if (turn == 1) {
        cout << "Создание армии" << endl << endl;
        std::shared_ptr<Unit> infantry = base->createUnit(UnitType::Infantry, 0, 0);
        std::shared_ptr<Unit> archer = base->createUnit(UnitType::Archer, 1, 0);
        std::shared_ptr<Unit> mage = base->createUnit(UnitType::Mage, 2, 0);
        std::shared_ptr<Unit> griffin = base->createUnit(UnitType::Flying, 3, 0);

        if (infantry && archer && mage && griffin) {
            cout << "Создано 4 юнита. Всего в базе: " << base->getUnitCount() << endl;
            map->addUnit(infantry, 0, 0);
            map->addUnit(archer, 1, 0);
            map->addUnit(mage, 2, 0);
            map->addUnit(griffin, 3, 0);
        }
    }

    else if (turn == 2) {
        cout << "Перемещение и взаимодействие" << endl << endl;

        Unit* infantry = map->getUnit(0, 0);
        if (infantry) {
            Terrain* plains = map->getTerrain(0, 0);
            if (plains->isPassable(*infantry)) {
                cout << "Пехота может пройти по равнине. Перемещение." << endl;
                infantry->move(1, 1);
            }
        }

        Unit* archer = map->getUnit(1, 0);
        if (archer) {
            cout << "\nЛучник находит сундук." << endl;
            TreasureChest chest(base.get());
            *archer + chest;
        }

        Unit* mage = map->getUnit(2, 0);
        if (mage) {
            cout << "\nМаг взаимодействует с алтарем." << endl;
            Altar altar;
            *mage* altar;
        }

        Unit* griffin = map->getUnit(3, 0);
        if (griffin) {
            cout << "\nГрифон летит над горами." << endl;
            map->setTerrain(3, 1, std::make_unique<Mountains>());  
            Terrain* mountains = map->getTerrain(3, 1);
            if (mountains->isPassable(*griffin)) {
                cout << "Грифон пролетает над горами. Перемещение." << endl;
                griffin->move(3, 1);
            }
        }
    }

    else if (turn == 3) {
        cout << "Битва и потери" << endl << endl;

        Unit* archer = map->getUnit(1, 0);
        if (archer) {
            cout << "Лучник наступает на ловушку." << endl;
            Trap trap;
            *archer - trap;
        }

        Unit* mage = map->getUnit(2, 0);
        if (mage) {
            cout << "\nМаг получает смертельный урон." << endl;
            mage->takeDamage(999);
        }
    }
}

void GameController::testTerrainAndCounter() {
    cout << "\nТЕСТИРОВАНИЕ ЛАНДШАФТА И СЧЕТЧИКА" << endl;

    ForestFactory factory;
    std::unique_ptr<Unit> infantry = factory.createInfantry(0, 0);
    std::unique_ptr<Unit> griffin = factory.createFlying(0, 0);

    if (infantry && griffin) {
        auto mountainsProxy = std::make_unique<TerrainProxy>(std::make_unique<Mountains>());
        auto forestProxy = std::make_unique<TerrainProxy>(std::make_unique<Forest>());
        auto swampProxy = std::make_unique<TerrainProxy>(std::make_unique<Swamp>());

        cout << "\nПЕХОТА" << endl;
        bool passable = mountainsProxy->isPassable(*infantry);
        cout << "1. Непроходимость гор для Infantry: " << (passable ? "Проходимо (ошибка)" : "Заблокировано (ок)") << endl;

        bool forestPassable = forestProxy->isPassable(*infantry);
        cout << "2. Проходимость леса для Infantry: " << (forestPassable ? "Проходимо (ок)" : "Заблокировано (ошибка)") << endl;

        double defBonus = forestProxy->getDefenseBonus(*infantry);
        cout << "3. Бонус защиты в лесу для Infantry: " << defBonus << " (ожидается 0.2)" << endl;

        double speedMod = swampProxy->getSpeedModifier(*infantry);
        cout << "4. Замедление в болоте для Infantry: " << speedMod << " (ожидается 0.25)" << endl;

        cout << "\nГРИФОН" << endl;
        bool griffinPassable = mountainsProxy->isPassable(*griffin);
        cout << "5. Грифон над горами: " << (griffinPassable ? "Пролетает (ок)" : "Заблокировано (ошибка)") << endl;

        double griffinDefBonus = forestProxy->getDefenseBonus(*griffin);
        cout << "6. Бонус защиты в лесу для грифона: " << griffinDefBonus << " (ожидается 0.0, т.к. летает)" << endl;

        double griffinSpeedMod = swampProxy->getSpeedModifier(*griffin);
        cout << "7. Замедление в болоте для грифона: " << griffinSpeedMod << " (ожидается 1.0, т.к. летает)" << endl;
    }
   
    cout << "\n8. Корректность счетчика базы (до игры): "
        << base->getUnitCount() << " юнитов (ожидается 0)" << endl;
}