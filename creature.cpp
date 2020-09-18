#include "creature.h"

Creature::Creature(std::string name, double life, double damage):
    name(name), life(life), damage(damage) {}

void Creature::attack(Creature* uj) const {
    if(uj->getLife() > 0){
        uj->setLife(uj->getLife() - this->getDamage());
    }
}

void Creature::setLife(double life){
	
    if(life >= 0){
        this->life = life;
    } else {
        this->life = 0;
    }
}

bool Creature::isDead() const {
    return (this->getLife() > 0) ? false : true;
}
