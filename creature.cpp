#include "creature.h"

Creature::Creature(std::string name, double life, double damage, double experience, int level):
    name(name), life(life), damage(damage), experience(experience), level(level) {}

Creature::Creature(const Creature& param):
    name(param.getName()), life(param.getDamage()), damage(param.getDamage()), experience(param.getExperience()), level(param.getLevel()) {}

void Creature::attack(Creature* uj) const {
    if(uj->life > 0){
        uj->life = (uj->life - this->getDamage());
    }

}

void Creature::battle(Creature* uj){
  
    double max_life1 = this->life;
    double max_life2 = uj->life;
    while(!this->isDead() && !uj->isDead())
    {
        this->attack(uj);
        this->experience += this->damage;
        if (this->experience>=100)
        {
            this->level += this->experience/100;
            this->experience = std::fmod(this->experience, 100);
            this->damage += round(0.1 * this->damage);
            max_life1 += round(0.1*max_life1);
            this->life = max_life1;
        }
        if (!uj->isDead())
        {
            uj->attack(this);
            uj->experience += uj->damage;
            if(uj->experience>=100)
            {
                uj->level++;
                uj->experience -= 100;
                uj->damage += round(0.1 * uj->damage);
                max_life2 += round(0.1*max_life2);   
                uj->life = max_life2;
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

                  if(counter < 3){
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
          return new Creature(result[0], std::stod(result[1]), std::stod(result[2]),0,1 );
      }
    }

