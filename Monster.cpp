#include "Monster.h"
#include "JSON.h"

Monster::Monster(std::string name, Damage damage, double life, double attackcooldown, double defense) : name(name), damage(damage), life(life), attackcooldown(attackcooldown), defense(defense){}

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
    if (uj.defense < damage.physical) {
        if (uj.life > 0) {                                                    
            uj.life = (uj.life - this->getDamage().physical - uj.defense); 
            if((uj.life - this->getDamage().magical) > 0){       
                                              
                uj.life = uj.life - this->getDamage().magical; 
            }              
        }    
    }
    
    if (uj.life <= 0) {
        
        if (uj.defense < damage.physical) {
            double tmp = uj.life + damage.physical - uj.defense;
            if(uj.life - damage.magical > 0){
                tmp = uj.life + damage.magical;
            }
            uj.life = 0;
            
            return tmp;  
        }

    } else {
        if(uj.defense < damage.physical){
            if(uj.life - damage.magical > 0){
                return damage.physical - uj.defense + damage.magical;
            }
            return damage.physical - uj.defense;
        }
        
    }
              
}

bool Monster::isAlive() const {
    return this->getHealthPoints() > 0;
}

Monster Monster::parse(const std::string& filename) {
    JSON jsonParser = JSON::parseFromFile(filename);

    Damage damage;

	if(jsonParser.count("physical_damage")){
		damage.physical = jsonParser.get<double>("physical_damage");
    }else{
        damage.physical = 0;
    }
	if(jsonParser.count("magical_damage")){
		damage.magical = jsonParser.get<double>("magical_damage");
    }else{
        damage.magical = 0;
    } 


    return Monster(jsonParser.get<std::string>("name"), damage, jsonParser.get<double>("health_points"), jsonParser.get<double>("attack_cooldown"), jsonParser.get<double>("defense"));
}
