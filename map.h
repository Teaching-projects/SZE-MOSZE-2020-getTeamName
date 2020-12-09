/**
 * \class Map
 *
 * \brief Map class
 *
 * \author Almási Szabolcs, Beszedics Tamás, Élő Kristóf
 *
 * \date 2020.11.23. 21:16
 *
 * Created on 2020.11.23. 21:16
 */

#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

class Map{

protected:
    std::vector<std::string> map; ///< Az RPG játék adott térképe.
public:
    Map() {}; ///< A Map konstruktora
    ~Map() { map.clear(); } ///< A Map destruktora

    enum type{
        Free, ///< A pálya útja
        Wall, ///< A pálya fala
        Hero, ///< A mapon levő Hero
        Monster ///< A mapon levő Monster/-ek
        };

    Map(const std::string& fname);  ///< Map konstruktora

    int getHeight () { return map.size(); }; ///< A map magassága
    int getWidth(int y) { return map[y].length(); }; ///< A map szélessége

    void setType(char, int, int); ///< A mapon egy adott pozícióban szereplő típus beállítása

    Map::type get( int x,  int y) const; ///< X és Y koordináta, visszatér, hogy az adott pont az egy Free vagy Wall

    class WrongIndexException : public std::exception{
    public:
        WrongIndexException() {};
    };
};

#endif // MAP_H