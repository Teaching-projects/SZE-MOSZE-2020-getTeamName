#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>


class Creature{

private:
    double life;
    const double damage;
    const std::string name;
    double attackcooldown;
    void attack(Creature*) const;
public:
    Creature(std::string, double, double, double);
    Creature(const Creature&);
    double getLife() const {return life;}
    std::string getName() const {return name;}
    double getDamage() const {return damage;}
    double getAttackcooldown() const {return attackcooldown;}
    void fight(Creature*);
    bool isDead() const;
    static Creature* parseUnit(const std::string);
    static bool contains(std::string, char);
};


#endif // CREATURE_H
