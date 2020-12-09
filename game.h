/**
 * \class Game
 *
 * \brief Game class
 *
 * \author Almási Szabolcs, Beszedics Tamás, Élő Kristóf
 *
 * \date 2020.12.09. 19:14
 *
 * Created on 2020.12.09. 19:14
 */


#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "Hero.h"
#include <string>
#include <list>

class Game {
protected:
    Map map; ///< Map
    bool isRunning = false; ///< Logikai változó, megnézi, hogy running-e
    bool mapIsSetted(); ///< Van-e map
    bool heroIsInitialized = false; ///< Hero van e inicializálva
    bool hasUnitsOnMap(); ///< Van-e unit a mapon
    bool isValidMove(int x, int y); ///< Helyes lépés-e
    void move(std::string); ///< A Mozgást vezérlő függvény
    Hero* gameHero = nullptr; ///< Hero mutató
    std::list<Monster> monsters; ///< Monstert tároló lista

public:
    ~Game() {  ///< A Game osztály destruktora
        monsters.clear();
    }
    Game() {}; ///< A Game osztály konstruktora
    Game(std::string filename);  ///< A Game osztály konstruktora
    void setMap(Map& _map); ///< Beállítja az adott mapot
    void putHero(Hero& hero, int x, int y); ///< Herot helyezet a map-ra a függvény segítségével
    void putMonster(Monster monster, int x, int y); ///< Szörnyet helyezel a map-ra a függvény segítségével

    void run(); ///< Ez működteti a játékot

    void print(); ///< Egy kiirató függvény

    class OccupiedException : public std::exception {
    public: OccupiedException() {};
    };
    class AlreadyHasHeroException : public std::exception {
    public: AlreadyHasHeroException() {};
    };
    class AlreadyHasUnitsException : public std::exception {
    public: AlreadyHasUnitsException() {};
    };
    class NoInitializedException : public std::exception {
        public: NoInitializedException() {};
    };
    class GameAlreadyStarted : public std::exception {
        public: GameAlreadyStarted() {};
    };
};

#endif // GAME_H