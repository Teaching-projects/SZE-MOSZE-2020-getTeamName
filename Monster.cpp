#include "Monster.h"
#include "JSON.h"

Monster::Monster(std::string name, double life, double damage, double attackcooldown) : name(name), life(life), damage(damage), attackcooldown(attackcooldown){}

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
    if(uj.life > 0){                                                    
        uj.life = (uj.life - this->getDamage());                   
    }
    if(uj.life < 0){
        double tmp = uj.life + damage;
        uj.life = 0;
        return tmp;  
    }else{
        return damage;
    }
                  
}

bool Monster::isAlive() const {
    return this->getHealthPoints() > 0;
}

Monster Monster::parse(const std::string& filename) {
    JSON jsonParser = JSON::parseFromFile(filename);
    return Monster(jsonParser.get<std::string>("name"), jsonParser.get<double>("health_points"), jsonParser.get<double>("damage"), jsonParser.get<double>("attack_cooldown"));
}
