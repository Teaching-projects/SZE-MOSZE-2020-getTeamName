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

class Map{

private:
    std::vector<std::string> map; ///< Az RPG játék adott térképe.
public:

    enum type{
        Free, ///< A pálya útja
        Wall ///< A pálya fala
        };

    Map(const std::string& fname);  ///< Map konstruktora

    Map::type get( int x,  int y) const; ///< X és Y koordináta, visszatér, hogy az adott pont az egy Free vagy Wall

    class WrongIndexException : public std::runtime_error{
    public:
        WrongIndexException(const std::string& err_message) : std::runtime_error(err_message){}
    };
};

#endif // MAP_H