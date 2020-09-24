#include "creature.h"

Creature::Creature(std::string name, double life, double damage):
    name(name), life(life), damage(damage) {}

Creature::Creature(const Creature& param):
    name(param.getName()), life(param.getDamage()), damage(param.getDamage()) {}


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

                  if(counter < 3){
                      temp = temp.substr(0,temp.length()-1);
                  }else{
                      counter=1;
                      temp = temp.substr(0,temp.length());
                  }
                  if (contains(temp, '"')) {
                      ReplaceAll2(temp, '"', "");
                  }
                  result.push_back(temp);
                  counter++;
              }
          }
          return new Creature(result[0], std::stod(result[1]), std::stod(result[2]));
      }
    }

bool Creature::contains(std::string from, char find) {
    for (char i : from) {
        if (i == find) {
            return true;
        }
    }
    return false;
}

