#pragma once
#include <iostream>
#include <list>
#include <map>
#include <fstream>
#include <string>
#include "BadJsonException.h"

class JsonParser {
	private:
		std::map<std::string, std::string> data;
		void parseJson(std::list<std::string>&);
		bool validateJson(std::list<std::string>);

	public:
		JsonParser(std::string fName);
		JsonParser(std::istream& stream);
		double getDouble(std::string) const;
		std::string getString(std::string) const;
		std::map<std::string, std::string> getData() const;
};