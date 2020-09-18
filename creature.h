#ifndef CREATURE_H
#define CREATURE_H

#include <iostream>
#include <string>


class Creature{

private:
    double life;
    const double damage;
    const std::string name;
public:
    Creature(std::string, double, double);
    double getLife() const {return life;}
    void setLife(double);
    std::string getName() const {return name;}
    double getDamage() const {return damage;}
    void attack(Creature*) const;
    bool isDead() const;
};


#endif // CREATURE_H
