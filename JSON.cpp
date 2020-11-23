#include "JSON.h"
#include <vector>
#include <sstream>


JSON::JSON(std::map<std::string, std::variant<std::string, double, int, std::list<std::variant<std::string, double, int>>>> data_) : data(data_) {}

JSON JSON::parseFromFile(std::string filename) {
	std::ifstream file;
	file.open(filename);

	std::string lines;

	if (file.good()) {
		
		std::string line;
		while (std::getline(file, line)) {
            if (line.empty()) { continue; }
			lines += line;
		}
	}

	return parseFromString(lines);
}

JSON JSON::parseFromString(std::string line) {
    std::string tempLine = "";
    std::list<std::string> lines;

	bool isKey = false;
	bool isList = false;
	std::string temp = "";
	std::list<std::variant<std::string, double, int>> lista;
	std::list<std::string> lista2;
	
	std::string list = "";

	int id = 0;
	for (char& iter : line) {
		
		if (iter == '"' && isKey) { isKey = false; }
        else if (iter == ' ' && !isKey) { continue; }
		else if (iter == '"' && !isKey) { isKey = true; }
		else if (iter == ' ' && isKey) { temp += iter; }
		else if (iter == '[') { isList = true; lista2.push_back(temp); temp = ""; }
		else if (iter == ']') { 
			isList = false;
			try {
				double x = std::stod(list);
				lista.push_back(x);
			} catch (const std::exception&) {
				lista.push_back(list); 
			}
		}
		else if (iter == ',' && isList && !isKey) { 
			try {
				double x = std::stod(list);
				lista.push_back(x);
			} catch (const std::exception&) {
				lista.push_back(list); 
			}
			list = ""; 
		}
		else if (iter == ',' && !isKey && !isList && line[id-1] != ']') { lista2.push_back(temp); temp = "";}
		else if (isList && iter != ' ') { list += iter; }
		else if (iter == '}') { lista2.push_back(temp); }
		else if (iter != '{' && iter != '}' && iter != ','){ temp += iter; }
		id++;
	}

    validateJson(line);
	return JSON(parseJson(lista, lista2));
}

JSON JSON::parseFromStream(std::istream &stream) {
	std::string lines;
	std::string line;
	while (std::getline(stream, line)) {
		lines += line;
	}
	return parseFromString(lines);
}

int JSON::count(std::string key){
	return data.count(key);
}

std::map<std::string, std::variant<std::string, double, int, std::list<std::variant<std::string, double, int>>>> JSON::parseJson(std::list<std::variant<std::string, double, int>> list, std::list<std::string> list2) {
    std::map<std::string, std::variant<std::string, double, int, std::list<std::variant<std::string, double, int>>>> data;
    bool isKey = false;
    std::string line;


    for (auto iter : list2) {
        int commaid = iter.find(":") + 1;
		if (commaid == iter.length()) { // ha lista
			data.insert(std::make_pair(iter.substr(0, commaid - 1), list));
		}
		else // ha nem lista
		{
            std::string key = iter.substr(0,commaid-1);
            std::string value = iter.substr(commaid);

            if (key.find("name") != std::string::npos) {
			data.insert(std::make_pair("name", value));
            }
            else if (key.find("attack_cooldown") != std::string::npos) {
                data.insert(std::make_pair("attack_cooldown", std::stod(value)));
            }
			else if (key.find("defense") != std::string::npos) {
                data.insert(std::make_pair("defense", std::stod(value)));
            }
			else if ((key.find("defense") != std::string::npos) && (key.find("bonus") != std::string::npos)) {
                data.insert(std::make_pair(key, std::stod(value)));
            }
    
            else if ((key.find("damage") != std::string::npos) && (key.find("bonus") != std::string::npos)) {
                data.insert(std::make_pair(key, std::stod(value)));
            }
            else if ((key.find("health") != std::string::npos) && (key.find("bonus") != std::string::npos)) {
                data.insert(std::make_pair(key, std::stod(value)));
            } 
            else if (key.find("damage") != std::string::npos) {
                data.insert(std::make_pair("damage", std::stod(value)));
            }
            else if (key.find("health") != std::string::npos) {
                data.insert(std::make_pair("health_points", std::stod(value)));
            }
            else {
                try
                {
                    double tmp = std::stod(value);
                    data.insert(std::make_pair(key, tmp));
                }
                catch(const std::exception& e)
                {
                    data.insert(std::make_pair(key, value));
                }
            }
			try {
				double x = std::stod(iter.substr(commaid));
				data.insert(std::make_pair(iter.substr(0, commaid - 1), x));
			}
			catch (const std::exception&) {
				data.insert(std::make_pair(iter.substr(0, commaid - 1), iter.substr(commaid)));
			}
		}
    }
    return data;
}

bool JSON::validateJson(std::string line) {
    if (line[0] != '{') {
        throw ParseException();
    } else if (line[line.length() - 1] != '}') {
        throw ParseException();
    }

    if (line[line.length() - 2] == ',') throw ParseException();

    
}
