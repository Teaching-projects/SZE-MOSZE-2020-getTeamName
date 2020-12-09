#include "game.h"

Game::Game(std::string filename) : map(Map(filename)), gameHero(nullptr) {} 

void Game::setMap(Map& _map) {
    if(!isRunning) {
        if (!hasUnitsOnMap())
        {
            map = _map;
        } else throw Game::AlreadyHasUnitsException();
    } else throw Game::GameAlreadyStarted();
}

void Game::putHero(Hero& hero, int x, int y) {
    if (mapIsSetted() && map.get(x,y) != Map::type::Wall)
    {
        if (map.get(x,y) != Map::type::Monster) {
            if (!heroIsInitialized)
            {
                gameHero = &hero;
                hero.pos.x = x;
                hero.pos.y = y;
                map.setType('H', x, y);
                heroIsInitialized = true;
            } else throw Game::AlreadyHasHeroException();
        } else throw Game::OccupiedException();
    } else throw Map::WrongIndexException();

}

void Game::putMonster(Monster monster, int x, int y) {
    if (mapIsSetted() && map.get(x,y) != Map::type::Wall) {
        if (map.get(x,y) != Map::type::Hero) {
            monster.pos.x = x;
            monster.pos.y = y;
            monsters.push_back(monster);
            map.setType('M', x, y);
        } else throw Game::OccupiedException();
    } else throw Map::WrongIndexException();
}

void Game::print() {
        std::cout << "╔════════════════════════════════════════╗\n" << std::endl;
        for (int y = 0; y < map.getHeight(); y++){
            std::cout << "║ ";
            for (int x = 0; x < map.getWidth(y); x++) {
                if (map.get(x,y) == Map::type::Monster) {
                    
                    int howMany = 0;
                    for (auto & iter : monsters) {
                        if (iter.pos.x == x && iter.pos.y == y)
                        {
                            howMany++;
                        }
                    }
                    if (howMany == 1) std::cout << "M░";
                    else std::cout << "MM";
                }
                switch (map.get(x,y))
                {
                case Map::type::Wall:
                    std::cout << "██";
                    break;
                case Map::type::Free:
                    std::cout << "░░";
                    break;
                case Map::type::Hero:
                    std::cout << "┣┫";
                    break;
                }
            }
            std::cout << " ║\n" << std::endl;
        }
        std::cout << "╚════════════════════════════════════════╝" << std::endl;
}

void Game::run() {
    if (heroIsInitialized && mapIsSetted()) {
        std::string direction = "";
        std::list<Monster> temp = monsters;

        while(monsters.size() > 0) {
            print();
            isRunning = true;
            std::cout << "Please give a direction: ";
            std::cin >> direction;
            move(direction);
            for (Monster monster : monsters) {
                if (monster.pos == gameHero->pos) {
                    
                    gameHero->fightTilDeath(monster);
                    
                    if (gameHero->isAlive())
                    {
                        temp.pop_front();
                    } else {
                        std::cout << "The hero died." << std::endl;
                        return;
                    }
                }
            }
            monsters = temp;
        }
        print();
        std::cout << gameHero->getName() << " cleared the map." << std::endl;
    } else throw Game::NoInitializedException();
}

void Game::move(std::string direction) {
    int tempX=0;
    int tempY=0;
    if (direction == "north") {
        tempX = -1;
        tempY = 0;
    } else if (direction == "south") {
        tempX = 1;
        tempY = 0;
    } else if (direction == "west") {
        tempX = 0;
        tempY = -1;
    } else if (direction == "east") {
        tempX = 0;
        tempY = 1;
    }

    if (isValidMove(tempX, tempY)) {
        map.setType(' ', gameHero->pos.x, gameHero->pos.y);
        gameHero->pos.x += tempY;
        gameHero->pos.y += tempX;
        map.setType('H', gameHero->pos.x, gameHero->pos.y);
    }
}

bool Game::isValidMove(int x, int y) {
    int posX = gameHero->pos.x + y;
    int posY = gameHero->pos.y + x;
    Map::type typeOfPos;

    try{
        typeOfPos = map.get(posX, posY);
    } catch (const Map::WrongIndexException& e) { return false; }

    if (typeOfPos == Map::type::Wall) return false;
    return true;
}

bool Game::mapIsSetted() {
    return !map.getHeight() == 0;
}

bool Game::hasUnitsOnMap() {
    for (int i = 0; i < map.getHeight(); i++)
    {
        for (int j = 0; j < map.getWidth(i); j++)
        {
            if (map.get(i,j) == Map::type::Hero || map.get(i,j) == Map::type::Monster) return true;
        }
        
    }
    return false;
}