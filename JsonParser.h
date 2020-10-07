#pragma once

#include <iostream>
#include <list>
#include <map>
#include <fstream>
#include <string>


class JsonParser {
	private:
		std::ifstream* file;
		std::map<std::string, std::string> data;
		void parseJson();

	public:
		JsonParser(std::string fName);
		JsonParser(std::ifstream& file);
		double getDouble(std::string) const;
		std::string getString(std::string) const;
		std::map<std::string, std::string> getData() const;
};