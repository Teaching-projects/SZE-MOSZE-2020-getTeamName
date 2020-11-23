#include "Hero.h"
#include "JSON.h"

Hero::Hero(std::string name , double life, double damage, double attackcooldown, double defense, double EXP_Bonus, double HP_Bonus, double Damage_Bonus, double Cooldown_Bonus, double defense_bonus_per_level):
    Monster(name, life, damage, attackcooldown, defense), EXP_Bonus(EXP_Bonus), HP_Bonus(HP_Bonus), Damage_Bonus(Damage_Bonus), Cooldown_Bonus(Cooldown_Bonus), defense_bonus_per_level(defense_bonus_per_level) { max_life = life;}

void Hero::levelUp(){
    level += 1;
    damage += Damage_Bonus;
    max_life += HP_Bonus;
    attackcooldown *= Cooldown_Bonus;
    life = max_life;
    defense += defense_bonus_per_level;
}

Hero::Hero(const Hero* param) : Monster(param->getName(), param->getHealthPoints(), param->getDamage(), param->getAttackCoolDown(), param->getDefense()), EXP_Bonus(param->EXP_Bonus), HP_Bonus(param->HP_Bonus), Damage_Bonus(param->Damage_Bonus), Cooldown_Bonus(param->Cooldown_Bonus), defense_bonus_per_level(param->defense_bonus_per_level) {}

double Hero::attack(Monster& uj) {
    if(uj.isAlive()){
        double tmp = Monster::attack(uj);
        experience += tmp;
        int tmp_exp = experience / 20;
       
        while(tmp_exp >= level){
            this->levelUp();
        }

    }
}

Hero Hero::parse(const std::string& filename) {
	JSON json = JSON::parseFromFile(filename);
	return Hero(json.get<std::string>("name"), json.get<double>("health_points"), json.get<double>("damage"), json.get<double>("attack_cooldown"), json.get<double>("defense"), json.get<double>("experience_per_level"), json.get<double>("health_point_bonus_per_level"), json.get<double>("damage_bonus_per_level"), json.get<double>("cooldown_multiplier_per_level"), json.get<double>("defense_bonus_per_level"));

}
