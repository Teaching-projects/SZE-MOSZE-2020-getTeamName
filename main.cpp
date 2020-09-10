#include <iostream>

using namespace std;

#include "creature.h"

int main() {
    Creature* h1 = new Creature("Maple", 150, 10);
    Creature* h2 = new Creature("Sally", 45, 30);
    while(!h1->isDead() && !h2->isDead()){
        if(!h1->isDead()){
            std::cout << h1->getName() << " -> " << h2->getName() << "\n";
            h1->attack(h2);
            std::cout << h1->getName() << ": HP: " << h1->getLife() << ", DMG: " <<h1->getDamage() << "\n";
            std::cout << h2->getName() << ": HP: " << h2->getLife() << ", DMG: " <<h2->getDamage() << "\n";
        }

        std::cout << "\n";

        if(!h2->isDead()){
            std::cout << h2->getName() << " -> " << h1->getName() << "\n";
            h2->attack(h1);
            std::cout << h1->getName() << ": HP: " << h1->getLife() << ", DMG: " <<h1->getDamage() << "\n";
            std::cout << h2->getName() << ": HP: " << h2->getLife() << ", DMG: " <<h2->getDamage() << "\n";
        }

        std::cout << "\n";
    }
    if(h1->isDead()){
        std::cout << h1->getName() << " died. " << h2->getName() << " wins. \n";
    }else{
        std::cout << h2->getName() << " died. " << h1->getName() << " wins. \n";
    }
    std::cout << std::endl;
    return 0;
}
