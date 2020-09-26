#include <iostream>
#include "creature.h"

int main(int argc, char *argv[]) {

    Creature* h1 = Creature::parseUnit(argv[1]);
    Creature* h2 = Creature::parseUnit(argv[2]);

    try {
        h1 = Creature::parseUnit(argv[1]);
        h2 = Creature::parseUnit(argv[2]);
    } catch (std::runtime_error re) {
        re.what();
    }

    while(!h1->isDead() && !h2->isDead()){

        if(!h1->isDead()) {
            h1->attack(h2);
        }
        if(!h2->isDead()){
            h2->attack(h1);
        }
    }

    if(h1->isDead()){
        std::cout << h2->getName() << " wins. Remaining HP: " << h2->getLife() << "\n";
    }else{
        std::cout << h1->getName() << " wins. Remaining HP: " << h1->getLife() << "\n";
    }

    std::cout << std::endl;

    delete h1, h2;

    return 0;
}
