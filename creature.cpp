#include "creature.h"
#include "JsonParser.h"

Creature::Creature(std::string name, double life, double damage):
    name(name), life(life), damage(damage) {}

Creature::Creature(const Creature& param):
    name(param.getName()), life(param.getDamage()), damage(param.getDamage()) {}


void Creature::attack(Creature* uj) const {
    if(uj->life > 0){
        uj->life = (uj->life - this->getDamage());
    }

}

bool Creature::isDead() const {
    return this->getLife() <= 0;
}

static inline void ReplaceAll2(std::string &str, const char& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, 1, to);
        start_pos += to.length();
    }
}

Creature* Creature::parseUnit(const std::string filename) {
    JsonParser jsonParser(filename);
    return new Creature(jsonParser.getString("name"), jsonParser.getDouble("hp"), jsonParser.getDouble("dmg"));
}

