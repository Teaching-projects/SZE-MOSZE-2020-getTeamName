#include "Hero.h"
#include "JSON.h"

Hero::Hero(std::string name , Damage damage, double life, double attackcooldown, double defense, double EXP_Bonus, double HP_Bonus, double Damage_Bonus, double Cooldown_Bonus, double defense_bonus_per_level, double magical_damage_bonus_per_level):
    Monster(name, damage, life, attackcooldown, defense), EXP_Bonus(EXP_Bonus), HP_Bonus(HP_Bonus), Damage_Bonus(Damage_Bonus), Cooldown_Bonus(Cooldown_Bonus), defense_bonus_per_level(defense_bonus_per_level), magical_damage_bonus_per_level(magical_damage_bonus_per_level) { max_life = life;}

void Hero::levelUp(){
    level += 1;
    damage.physical += Damage_Bonus;
    damage.magical += magical_damage_bonus_per_level;
    max_life += HP_Bonus;
    attackcooldown *= Cooldown_Bonus;
    life = max_life;
    defense += defense_bonus_per_level;
}

Hero::Hero(const Hero* param) : Monster(param->getName(), param->getDamage(),param->getHealthPoints(),  param->getAttackCoolDown(), param->getDefense()), EXP_Bonus(param->EXP_Bonus), HP_Bonus(param->HP_Bonus), Damage_Bonus(param->Damage_Bonus), Cooldown_Bonus(param->Cooldown_Bonus), defense_bonus_per_level(param->defense_bonus_per_level), magical_damage_bonus_per_level(param->magical_damage_bonus_per_level) {}

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

    Damage damage;

	if(json.count("physical_damage")){
		damage.physical = json.get<double>("physical_damage");
    }else{
        damage.physical = 0;
    }
	if(json.count("magical_damage")){
		damage.magical = json.get<double>("magical_damage");
    }else{
        damage.magical = 0;
    } 

	return Hero(json.get<std::string>("name"), damage, json.get<double>("health_points"), json.get<double>("attack_cooldown"), json.get<double>("defense"), json.get<double>("experience_per_level"), json.get<double>("health_point_bonus_per_level"), json.get<double>("physical_damage_bonus_per_level"), json.get<double>("cooldown_multiplier_per_level"), json.get<double>("defense_bonus_per_level"), json.get<double>("magical_damage_bonus_per_level"));

}
