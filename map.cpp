#include "map.h"
#include <fstream>

Map::Map(const std::string& fname){
    std::ifstream MapTxt(fname);
    if(MapTxt.good()) 
    {
        std::string line;
        while (getline(MapTxt, line))
            map.push_back(line);
    }
    else throw std::runtime_error("File does not exist: " + fname);
    MapTxt.close();
}

Map::type Map::get( int x,  int y) const{
    if (y >= map.size() || x >= map[y].size()){
        throw WrongIndexException("Wrong coordinate! Outside of the map!");
    }
    if(map[y][x] == ' '){
        return Map::type::Free;
    } 
    else{
        return Map::type::Wall;
    }
}