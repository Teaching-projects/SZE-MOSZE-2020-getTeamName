#ifndef HERO_H
#define HERO_H


#include "Monster.h"


class Hero : public Monster{
private:
    double experience = 0; ///< A Hero tapasztalati pontjai
    int level = 1; ///< A Hero szintje
    double max_life = 0; ///< Maximalis eletereje a Hero-nak
    const double EXP_Bonus; ///< A Hero szintlépéséhez szükséges EXP
    const double HP_Bonus; ///< A Hero szintlépésekor kapott bónusz HP
    const double Damage_Bonus; ///< A Hero szintlépésekor kapott bónusz sebzés
    const double Cooldown_Bonus; ///< A Hero szintlépésekor kapott cooldown szorzó


public:
    Hero(std::string, double, double, double, double, double, double, double); ///< A Hero konstruktora
	Hero(const Hero* other); ///< A Hero copy konstruktora
    double getExperience() const {return experience;} ///< Egyszeru konstans Getter fuggveny, ami visszater a Hero tapasztalati pontjaival
    double getLevel() const {return level;} ///< Egyszeru konstans Getter fuggveny, ami visszater a Hero szintjének értékével
    double getMaxHealthPoints() const {return max_life;} ///< Egyszeru konstans Getter fuggveny, ami visszater a Hero maximalis eleterejenek ertekevel
    static Hero parse(const std::string& /** [in] string*/);

    void levelUp(); ///< Hero osztály szintlépését hajtja végre
    double attack(Monster&); ///< Támadást vezérlő függvény

};

#endif // HERO_H