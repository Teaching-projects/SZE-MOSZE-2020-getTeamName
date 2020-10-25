#include "creature.h"
#include "JsonParser.h"

Creature::Creature(std::string name, double life, double damage, double attackcooldown, double experience, int level):
    name(name), life(life), max_life(life), damage(damage), attackcooldown(attackcooldown), experience(experience), level(level) {}

Creature::Creature(const Creature& param):
    name(param.getName()), life(param.getDamage()), max_life(param.getMax_Life()), damage(param.getDamage()), attackcooldown(param.getAttackcooldown()), experience(param.getExperience()), level(param.getLevel()) {}

Creature& Creature::operator=(const Creature& param)
{
    this->name = param.getName();
    this->life = param.getLife();
    this->max_life = param.getMax_Life();
    this->damage = param.getDamage();
    this->attackcooldown = param.getAttackcooldown();
    this->experience = param.getExperience();
    this->level = param.getLevel();
    return *this;
}

void Creature::attack(Creature* uj) const {
    if(uj->life > 0){
        uj->life = (uj->life - this->getDamage());
    }

}

void Creature::levelUp(){
    int tmp_exp = experience / 100;
    int counter=1;
    level += experience/100;
    experience = std::fmod(experience, 100);
    while(tmp_exp >= counter){
        damage += round(0.1 * damage);
        attackcooldown -= 0.1 * attackcooldown;
        max_life += round(0.1*max_life);
        counter++;
    }
    life = max_life;
}

void Creature::overkill(Creature* uj)
{
    if(uj->life < this->damage){
        this->experience += uj->life;
    }
    else{
        this->experience += this->damage;
    }
}


void Creature::fight(Creature* uj){
    double time = 0;
    double tmpCooldown1 = this->attackcooldown;
    double tmpCooldown2 = uj->attackcooldown;
    if(!this->isDead() && !uj->isDead()){
        this->overkill(uj);
        this->attack(uj);
        if (this->experience>=100){
            this->levelUp();
        }
        tmpCooldown1 = this->attackcooldown;
    }
    if(!uj->isDead()){
        uj->overkill(this);
        uj->attack(this);
        if(uj->experience>=100){
            uj->levelUp();
        }
        tmpCooldown2 = uj->attackcooldown;
    }

    while(!this->isDead() && !uj->isDead()){
        if(tmpCooldown1 <= tmpCooldown2){
            if(!this->isDead()) {
                this->overkill(uj);
                this->attack(uj);
                if (this->experience>=100){
                   this->levelUp();
                }
            time += tmpCooldown1;
            tmpCooldown1 += this->attackcooldown;
            }
        }
        
        else{
            if(!uj->isDead()){
                uj->overkill(this);
                uj->attack(this);
                if(uj->experience>=100){
                    uj->levelUp();
                }
            time += tmpCooldown2;
            tmpCooldown2 += uj->attackcooldown;
            }
        }
    }
}

bool Creature::isDead() const {
    return this->getLife() <= 0;
}

Creature* Creature::parseUnit(const std::string& filename) {
    JsonParser jsonParser(filename);
    return new Creature(jsonParser.getString("name"), jsonParser.getDouble("hp"), jsonParser.getDouble("dmg"), jsonParser.getDouble("attackcooldown"), 0, 1);
}