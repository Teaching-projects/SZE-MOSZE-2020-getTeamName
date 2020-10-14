/**
 * \class Creature
 *
 * \brief Creature class
 *
 * \author Almási Szabolcs
 *
 * \date 2020.10.07. 22:57
 *
 * Created on 2020.10.07. 22:57
 */

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
    std::string name; ///< Neve a Creature-nek
    double life; ///< Elete a Creature-nek
    double damage; ///< Sebzese a Creature-nek
    double attackcooldown; ///<Ketto sebzes kozotti eltelt ido az adott Creature-n belul
    double experience; ///<A Creature tapasztalati pontjai
    int level; ///<A Creature szintje
    /**
     * \brief A Creature tamadasa egy masik Creature objektum ellen
     *
     * \param Creature objektumra mutato
     */
    void attack(Creature*) const; ///< A Creature tamadasa egy masik Creature objektum ellen

public:
    Creature(std::string, double, double, double, double, int); ///< Creature osztaly konstruktora
    Creature(const Creature&); ///< Creature osztaly konstruktora
    Creature& operator=(const Creature&); ///< Creature osztály hozzárendelés operátora
    double getLife() const {return life;} ///< Egyszeru konstans Getter fuggveny, ami visszater a Creature eletenek ertekevel
    std::string getName() const {return name;} ///< Egyszeru konstans Getter fuggveny, ami visszater a Creature nevenek ertekevel
    double getDamage() const {return damage;} ///< Egyszeru konstans Getter fuggveny, ami visszater a Creature sebzesenek ertekevel
    double getExperience() const {return experience;} ///< Egyszeru konstans Getter fuggveny, ami visszater a Creature tapasztalati pontjaival
    double getLevel() const {return level;} ///< Egyszeru konstans Getter fuggveny, ami visszater a Creature szintjének értékével
    double getAttackcooldown() const {return attackcooldown;} ///< Egyszeru konstans Getter fuggveny, ami visszater a Creature 2 tamadasa kozti eltelt ido ertekevel
    /**
     * \brief Ket Creature objektum kozotti harc megvalositasa
     *
     * \param Creature objektumra mutato
     */
    void fight(Creature*/** [in] Creature objektumra mutato*/); ///< Ket Creature objektum kozotti harc megvalositasa
    /**
     * \brief Visszaadja, hogy az adott Creature el-e meg
     * \return Ha az eletero nulla, akkor true-val ter vissza, ellenben false-al
     */
    bool isDead() const; ///< Visszaadja, hogy az adott Creature el-e meg
    /**
     * \brief JSON-ben kapott adatokat elemzi
     * \param String
     * \return Creature-re mutato objektummal ter vissza
     */
    static Creature* parseUnit(const std::string /** [in] string*/);
    void levelUp(double&, int&, double&, double&, double&, double&); ///< Creature osztály szintlépését hajtja végre
};

#endif // CREATURE_H
