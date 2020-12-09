/**
 * \class Monster
 *
 * \brief Monster class
 *
 * \author Almási Szabolcs, Beszedics Tamás, Élő Kristóf
 *
 * \date 2020.10.27. 19:05
 *
 * Created on 2020.10.27. 19:05
 */

#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include "damage.h"

class Monster{
protected:
    std::string name; ///< Neve a Monster-nek
    double life; ///< Elete a Monster-nek
    Damage damage; ///< Sebzese a Monster-nek
    double attackcooldown; ///<Ketto sebzes kozotti eltelt ido az adott Monster-n belul
    double defense; ///< A Monster vedekezesi erejenek erteke
    virtual double attack(Monster &); ///< A Monster tamadasa egy masik Monster objektum ellen

public:
    struct Pos_ ///< Pozíció
    {
        int x = -1;
        int y = -1;

        bool operator==(const Pos_& otherPos) { return x == otherPos.x && y == otherPos.y;}
    } pos;
    Monster(std::string, Damage, double, double, double); ///< Monster konstruktora
    double getHealthPoints() const {return life;} ///< Egyszeru konstans Getter fuggveny, ami visszater a Monster eletenek ertekevel
    std::string getName() const {return name;} ///< Egyszeru konstans Getter fuggveny, ami visszater a Monster nevenek ertekevel
    Damage getDamage() const {return damage;} ///< Egyszeru konstans Getter fuggveny, ami visszater a Monster sebzesenek ertekevel
    double getAttackCoolDown() const {return attackcooldown;} ///< Egyszeru konstans Getter fuggveny, ami visszater a Monster 2 tamadasa kozti eltelt ido ertekevel
    double getDefense() const {return defense;} ///< Egyszeru konstans Getter fuggveny, ami visszater a defense ertekevel
    void fightTilDeath(Monster& );
    /**
     * \brief Visszaadja, hogy az adott Monster el-e meg
     */
    bool isAlive() const; ///< Visszaadja, hogy az adott Monster el-e meg
    /**
     * \brief JSON-ben kapott adatokat elemzi
     * \param  stringet kap paraméterben
     * \return Monster-re mutato objektummal ter vissza
     */
    static Monster parse(const std::string& /** [in] string*/);

    
};

#endif // MONSTER_H
