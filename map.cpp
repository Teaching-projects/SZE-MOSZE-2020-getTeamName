#include "map.h"
#include <algorithm>


Map::Map(const std::string& fname){
    std::ifstream MapTxt(fname);
    if(MapTxt.good()) 
    {
        std::string line;
        while (getline(MapTxt, line)){
            line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
            line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
            map.push_back(line);
        }
    }
    else throw std::runtime_error("File does not exist: " + fname);
    MapTxt.close();
}

Map::type Map::get( int x,  int y) const{
    if (y >= map.size() || x >= map[y].size()){
        throw WrongIndexException();
    }
    if(map[y][x] == ' ') return Map::type::Free;
    else if (map[y][x] == 'H') return Map::type::Hero;
    else if (map[y][x] == 'M') return Map::type::Monster;
    else return Map::type::Wall;
}

void Map::setType(char type, int x, int y) {
    map[y][x] = type;
}
