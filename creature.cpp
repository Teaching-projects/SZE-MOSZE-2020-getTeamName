#include "creature.h"

Creature::Creature(std::string name, double life, double damage, double attackcooldown, double experience, int level):
    name(name), life(life), damage(damage), attackcooldown(attackcooldown), experience(experience), level(level) {}

Creature::Creature(const Creature& param):
    name(param.getName()), life(param.getDamage()), damage(param.getDamage()), attackcooldown(param.getAttackcooldown()), experience(param.getExperience()), level(param.getLevel()) {}

Creature& Creature::operator=(const Creature& param)
{
    this->name = param.getName();
    this->life = param.getLife();
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

void Creature::levelUp(double& experience, int& level, double& damage, double& max_life, double& life, double& tmp_cooldown){
    int tmp_exp = experience / 100;
    int counter=1;
    level += experience/100;
    experience = std::fmod(experience, 100);
    while(tmp_exp >= counter){
        damage += round(0.1 * damage);
        tmp_cooldown -= 0.1 * tmp_cooldown;
        max_life += round(0.1*max_life);
        counter++;
    }
    life = max_life;
}

void Creature::fight(Creature* uj){
    double max_life1 = this->life;
    double max_life2 = uj->life;

    double time = 0;
    double tmpCooldown1 = this->attackcooldown;
    double tmpCooldown2 = uj->attackcooldown;
    if(!this->isDead() && !uj->isDead()){
        this->attack(uj);
        this->experience += this->damage;

        if (this->experience>=100){
            levelUp(this->experience, this->level, this->damage, max_life1, this->life, tmpCooldown1);
            this->attackcooldown += tmpCooldown1;
            time += tmpCooldown1;
        }
    }
    if(!uj->isDead()){
        uj->attack(this);
        uj->experience += uj->damage;

        if(uj->experience>=100){
            levelUp(uj->experience, uj->level, uj->damage, max_life2, uj->life, tmpCooldown2);
            uj->attackcooldown += tmpCooldown2;
            time += tmpCooldown2;
        }
    }

    while(!this->isDead() && !uj->isDead()){
        if(this->attackcooldown <= uj->attackcooldown){
            if(!this->isDead()) {
                this->attack(uj);
                this->experience += this->damage;

                if (this->experience>=100){
                   levelUp(this->experience, this->level, this->damage, max_life1, this->life, tmpCooldown1);
                   this->attackcooldown += tmpCooldown1;
                   time += tmpCooldown1;
                }

            }
        }
        else{
            if(!uj->isDead()){
                uj->attack(this);
                uj->experience += uj->damage;

                if(uj->experience>=100){
                    levelUp(uj->experience, uj->level, uj->damage, max_life2, uj->life, tmpCooldown2);
                    uj->attackcooldown += tmpCooldown2;
                    time += tmpCooldown2;
                }

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
        std::string newline;
        std::vector<std::string> result;
        int counter = 1;
        while (std::getline(file, newline)) {

            if (newline != "{" && newline != "}") {
                int split = newline.find(":");
                std::string temp = newline.substr(split + 2);

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
        return new Creature(result[0], std::stod(result[1]), std::stod(result[2]),std::stod(result[3]),0,1 );
    }
}


