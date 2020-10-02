#include "creature.h"

Creature::Creature(std::string name, double life, double damage, double attackcooldown):
    name(name), life(life), damage(damage), attackcooldown(attackcooldown) {}

Creature::Creature(const Creature& param):
    name(param.getName()), life(param.getDamage()), damage(param.getDamage()), attackcooldown(param.getAttackcooldown()) {}


void Creature::attack(Creature* uj) const {
    if(uj->life > 0){
        uj->life = (uj->life - this->getDamage());
    }

}

void Creature::fight(Creature* uj){
    if(!this->isDead() && !uj->isDead()){
        this->attack(uj);
    }
    if(!this->isDead() && !uj->isDead()){
        uj->attack(this);
    }

    double time = 0;
    double tmpCooldown1 = this->attackcooldown;
    double tmpCooldown2 = uj->attackcooldown;
    while(!this->isDead() && !uj->isDead()){

        if(this->attackcooldown <= uj->attackcooldown){
            if(!this->isDead()) {
                this->attack(uj);

                this->attackcooldown += tmpCooldown1;
                time += tmpCooldown1;
            }
        }
        else{
            if(!uj->isDead()){
                uj->attack(this);

                uj->attackcooldown += tmpCooldown2;
                time += tmpCooldown2;
            }
        }

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
      std::ifstream file(filename);
      if (!file.good()) {
        throw std::runtime_error(filename + " does not exists...\n");
      } else {
        std::string name, newline;
          std::vector<std::string> result;
          int counter = 1;
          while (std::getline(file, newline)) {

              if (newline != "{" && newline != "}") {
                  int split = newline.find(":");
                  std::string temp = newline.substr(2,split - 2 );
                  temp = newline.substr(split + 2);

                  if(counter < 4){
                      temp = temp.substr(0,temp.length()-1);
                  }else{
                      counter=1;
                      temp = temp.substr(0,temp.length());
                  }
                  if (newline.find(temp)!= std::string::npos){
                      ReplaceAll2(temp, '"', "");
                  }
                  result.push_back(temp);
                  counter++;
              }
          }
          return new Creature(result[0], std::stod(result[1]), std::stod(result[2]),std::stod(result[3]) );
      }
    }

