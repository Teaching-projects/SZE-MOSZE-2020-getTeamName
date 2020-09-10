#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <string>


class Creature{

private:
    double life;
    double damage;
    std::string name;
public:
    Creature(std::string, double, double);
    double getLife() const {return life;}
    void setLife(double);
    std::string getName() const {return name;}
    double getDamage() const {return damage;}
    void attack(Creature*);
    bool isDead();
};
#endif // CREATURE_H
