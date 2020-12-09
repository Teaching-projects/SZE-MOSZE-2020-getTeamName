#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <list>

#include "JSON.h"
#include "Hero.h"
#include "Monster.h"
#include "game.h"


const std::map<int,std::string> error_messages = {
    { 1 , "Bad number of arguments. Only a single scenario file should be provided." },
    { 2 , "The provided scenario file is not accessible." },
    { 3 , "The provided scenario file is invalid." },
    { 4 , "JSON parsing error." },
    { 5 , "OccupiedException." },
    { 6 , "AlreadyHasHeroException." },
    { 7 , "AlreadyHasUnitsException." },
    { 8 , "NoInitializedException." },
    { 9 , "GameAlreadyStarted." },
    {10 , "WrongIndex in the map file"}
};

void bad_exit(int exitcode){
    std::cerr
        << (error_messages.count(exitcode) ? error_messages.at(exitcode) : "Unknown error")
        << std::endl;
    exit(exitcode);
}

int main(int argc, char** argv){
    if (argc != 2) bad_exit(1);
    if (!std::filesystem::exists(argv[1])) bad_exit(2);


    std::string hero_file;
    std::list<std::string> monster_files;
    try {
        JSON scenario = JSON::parseFromFile(argv[1]); 
        if (!(scenario.count("hero")&&scenario.count("monsters"))) bad_exit(3);
        else {
            hero_file=scenario.get<std::string>("hero");
            JSON::list monster_file_list=scenario.get<JSON::list>("monsters");
            for(auto monster_file : monster_file_list)
                monster_files.push_back(std::get<std::string>(monster_file));
        }
    } catch (const JSON::ParseException& e) {bad_exit(4);}

    try {
        Hero hero{Hero::parse(hero_file)};
        std::list<Monster> monsters;
        for (const auto& monster_file : monster_files) 
            monsters.push_back(Monster::parse(monster_file));
    
    
        try{
            Game game = Game("map.txt");

            
            game.putHero(hero, 1, 1);
            for (const auto& monster : monsters) {
                game.putMonster(monster, 1,2);
            }
            for (const auto& monster : monsters) {
                game.putMonster(monster, 3,3);
            }
            game.run();
        }catch(Game::OccupiedException& e) {bad_exit(5);}
        catch(Game::AlreadyHasHeroException& e) {bad_exit(6);}
        catch(Game::AlreadyHasUnitsException& e) {bad_exit(7);}
        catch(Game::NoInitializedException& e) {bad_exit(8);}
        catch(Game::GameAlreadyStarted& e) {bad_exit(9);}
        catch(Map::WrongIndexException& e) {bad_exit(10); }

    } catch (const JSON::ParseException& e) {bad_exit(4);}
    return 0;
}
