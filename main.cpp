#include <iostream>
#include "creature.h"
#include "BadJsonException.h"

int main(int argc, char *argv[]) {

    if (argc != 3) {
        std::cerr << "Please give two json file to run the game! Example: ./a.out \"Maple.json\" \"Kakarott.json\" \n";
        return 1;
    }

    Creature* h1, *h2;
    
    try {
        h1 = Creature::parseUnit(argv[1]);
    } 
    catch (std::runtime_error& re) {
        std::cerr << re.what();
        return 2;
    }
    catch (std::bad_alloc& ba) {
        std::cerr << ba.what();
        return 3;
    } catch (BadJsonException e) {
        std::cerr << e.what() << std::endl;
        return e.getErrorCode();
    }

    try {
        h2 = Creature::parseUnit(argv[2]);
    } 
    catch (std::runtime_error& re) {
        std::cerr << re.what();
        delete h1;
        return 2;
    }
    catch (std::bad_alloc& ba) {
        std::cerr << ba.what();
        delete h1;
        return 3;
    }

    h1->fight(h2);

    if(h1->isDead()){
        std::cout << h2->getName() << " wins. Remaining HP: " << h2->getLife() << "\n";
    }else{
        std::cout << h1->getName() << " wins. Remaining HP: " << h1->getLife() << "\n";
    }

    delete h1;
    delete h2;
    return 0;
}