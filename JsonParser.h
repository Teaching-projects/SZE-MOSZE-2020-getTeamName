/**
 * \class Creature
 *
 * \brief Creature class
 *
 * \author Almási Szabolcs, Beszedics Tamás, Élő Kristóf
 *
 * \date 2020.10.27. 19:05
 *
 * Created on 2020.10.27. 19:05
 */
#pragma once
#include <iostream>
#include <list>
#include <map>
#include <fstream>
#include <string>
#include "BadJsonException.h"

class JsonParser {
	private:
        std::map<std::string, std::string> data; ///<  Kulcs-érték string páros,
        void parseJson(std::list<std::string>&); ///<  A Json parzolását ez a függvény hajtja végre
        bool validateJson(std::list<std::string>); ///<  A Json fájl formátumát vizsgálja, hogy megfelelő-e

	public:
        JsonParser(std::string fName); ///< JsonParser konstruktora, ami egy stringet vár paraméterben
        JsonParser(std::istream& stream); ///< JsonParser konstruktora, ami egy istreamet vár paraméterben
        double getDouble(std::string) const; ///< A paraméterben kapott kulcs értékét adja vissza double értékként
        std::string getString(std::string) const; ///<  A paraméterben kapott kulcs értékét adja vissza string értékként
        std::map<std::string, std::string> getData() const; ///<  Ez a getter függvény visszaadja a map tartalmát
};
