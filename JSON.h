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
#ifndef JSON_H
#define JSON_H


#include <iostream>
#include <list>
#include <map>
#include <fstream>
#include <string>
#include <variant>

class JSON {
    private:
		std::map<std::string, std::variant<std::string, double, int>> data;///<  Kulcs-érték string páros,
        static std::map<std::string, std::variant<std::string, double, int>> parseJson(std::list<std::string>&); ///<  A Json parzolását ez a függvény hajtja végre
        static bool validateJson(std::list<std::string>); ///<  A Json fájl formátumát vizsgálja, hogy megfelelő-e

    public:
		static JSON parseFromFile(std::string); ///< stringben tárolt JSON fájlt olvas be
		static JSON parseFromString(std::string); ///< stringben tárolt JSON struktúrát olvas be
		static JSON parseFromStream(std::istream&); ///< istreamben lévő JSON struktúrát olvas be
		int count(std::string); ///< Visszaadja a mapben található kulcsok darabszámát

		JSON(std::map<std::string, std::variant<std::string, double, int>>); ///< JSON osztály konstruktora

		template<typename T> ///< Kap egy típust, majd kulcsot stringként és visszaadja a típusra konvertált értéket a mapből
		T get(const std::string& key) {
			return std::get<T>(data[key]);
		};

		class ParseException : std::exception {
		public:
			ParseException() {}; ///< ParseException osztály konstruktora
		};
};

#endif // JSON_H