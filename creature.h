#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>


class Creature{

private:
    double life;
    double damage;
    const std::string name;
    double experience;
    int level;
public:
    Creature(std::string, double, double, double,int);
    Creature(const Creature&);
    double getLife() const {return life;}
    std::string getName() const {return name;}
    double getDamage() const {return damage;}
    double getExperience() const {return experience;}
    double getLevel() const {return level;}
    void attack(Creature*) const;
    bool isDead() const;
    void battle(Creature*);
    static Creature* parseUnit(const std::string);
    static bool contains(std::string, char);
};


#endif // CREATURE_H
