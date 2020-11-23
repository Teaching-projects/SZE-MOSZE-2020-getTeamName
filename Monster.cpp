#include "Monster.h"
#include "JSON.h"

Monster::Monster(std::string name, double life, double damage, double attackcooldown, double defense) : name(name), life(life), damage(damage), attackcooldown(attackcooldown), defense(defense){}

void Monster::fightTilDeath(Monster& uj){
    double HeroCooldownTime = getAttackCoolDown();
    double ujCooldownTime= uj.getAttackCoolDown();

    while(this->isAlive() && uj.isAlive()){
        if(HeroCooldownTime <= ujCooldownTime){
            this->attack(uj);
            HeroCooldownTime += this->getAttackCoolDown(); 

        }
        else if(HeroCooldownTime > ujCooldownTime){
            uj.attack(*this);
            ujCooldownTime += uj.getAttackCoolDown(); 
        }
    }
}

double Monster::attack(Monster& uj){
    if (uj.defense < damage) {
        if (uj.life > 0) {                                                    
            uj.life = (uj.life - this->getDamage() - uj.defense);                   
        }    
    }
    
    if (uj.life < 0) {
        if (uj.defense <  damage) {
            double tmp = uj.life + damage - uj.defense;
            uj.life = 0;
            return tmp;  
        }
    } else {
        if (uj.defense <  damage) {
            return damage - uj.defense;
        }
    }          
}

bool Monster::isAlive() const {
    return this->getHealthPoints() > 0;
}

Monster Monster::parse(const std::string& filename) {
    JSON jsonParser = JSON::parseFromFile(filename);
    return Monster(jsonParser.get<std::string>("name"), jsonParser.get<double>("health_points"), jsonParser.get<double>("damage"), jsonParser.get<double>("attack_cooldown"), jsonParser.get<double>("defense"));
}
