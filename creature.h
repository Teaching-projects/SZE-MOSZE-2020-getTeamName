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

class Creature{

private:
    double life; ///< Elete a Creature-nek
    const double damage; ///< Sebzese a Creature-nek
    const std::string name; ///< Neve a Creature-nek
    double attackcooldown; ///<Ketto sebzes kozotti eltelt ido az adott Creature-n belul
    /**
     * \brief A Creature tamadasa egy masik Creature objektum ellen
     *
     * \param Creature objektumra mutato
     */
    void attack(Creature*) const; ///< A Creature tamadasa egy masik Creature objektum ellen

public:
    Creature(std::string, double, double, double); ///< Creature osztaly konstruktora
    Creature(const Creature&); ///< Creature osztaly konstruktora
    double getLife() const {return life;} ///< Egyszeru konstans Getter fuggveny, ami visszater a Creature eletenek ertekevel
    std::string getName() const {return name;} ///< Egyszeru konstans Getter fuggveny, ami visszater a Creature nevenek ertekevel
    double getDamage() const {return damage;} ///< Egyszeru konstans Getter fuggveny, ami visszater a Creature sebzesenek ertekevel
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
};

#endif // CREATURE_H
