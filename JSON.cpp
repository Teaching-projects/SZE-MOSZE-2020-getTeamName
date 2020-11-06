#include "JSON.h"
#include <vector>
#include <sstream>


JSON::JSON(std::map<std::string, std::variant<std::string, double, int>> data_) : data(data_) {}

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

    std::string temp = "";
    bool isKey;
    for (char iter : line) {
        if (iter == ' ' && !isKey) { continue; }
        else if (!isKey && iter == '"') { isKey = true; temp += iter; }
        else if (isKey && iter == '"') { isKey = false; temp += iter; }
        else { temp += iter; }
    }

    std::string a(1,temp[0]);
    std::string b(1,temp[temp.size() - 1]);
    
    lines.push_front(a);

    std::stringstream ss(temp.substr(1, temp.size()-2));

    while(std::getline(ss, tempLine, ',')){
        if (tempLine.empty()) { continue; }
        if (tempLine[0] != '"') { 
            std::string tempasd = lines.back();
            tempasd += tempLine;
            lines.pop_back();
            lines.push_back(tempasd + ",");
            continue;
        }
        lines.push_back(tempLine + ",");
    }

    tempLine = lines.back().substr(0, lines.back().size() - 1);

    lines.pop_back();
    lines.push_back(tempLine);

    lines.push_back(b);

	return JSON(parseJson(lines));
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

std::map<std::string, std::variant<std::string, double, int>> JSON::parseJson(std::list<std::string>& list) {
	std::map<std::string, std::variant<std::string, double, int>> data;
    bool isKey = false;
    std::string line;
    std::list<std::string> lines = list;
    std::list<std::string> keyValues;

    validateJson(lines);

    lines.pop_back();
    lines.pop_front();

    for (std::string line : lines) {
        std::string trimmedLine = "";
        for (char c : line) {
            if (c == ' ' && isKey) {
                trimmedLine += c;
            } else if (c == '"' && !isKey) {
                isKey = true;
            } else if (c == '"' && isKey) {
                isKey = false;
            } else if (c == ' ' && !isKey) {
                continue;
            } else if (c == ',' && isKey) {
				trimmedLine += c;
            } else if (c == ',' && !isKey) {
                continue;
            } else {
                trimmedLine += c;
            }
        }
        keyValues.push_back(trimmedLine);
    }

    lines.clear();

    for (std::string line : keyValues) {
        int index = line.find(':');
        std::string key = line.substr(0,index);
        std::string value = line.substr(index + 1);

		if (key.find("name") != std::string::npos) {
			data.insert(std::make_pair("name", value));
		}
		else if (key.find("attack_cooldown") != std::string::npos) {
			data.insert(std::make_pair("attack_cooldown", std::stod(value)));
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

    }

    keyValues.clear();

	return data;
}

bool JSON::validateJson(std::list<std::string> lines) {
    std::vector<std::string> linesVector;

    for (auto line : lines) {
        linesVector.push_back(line);
    }

    for (int i = 0; i < linesVector.size(); i++) {
        bool isKey = false;
        std::string tempString = "";
        for (char iter : linesVector[i]) {
            if (iter == ' ' && isKey) {
                tempString += iter;
            } else if (iter == '"' && !isKey) {
                isKey = true;
                tempString += iter;
            } else if (iter == '"' && isKey) {
                isKey = false;
                tempString += iter;
            } else if (iter == ' ' && !isKey) {
                continue;
            } else {
                tempString += iter;
            }
        }
        linesVector[i] = tempString;
    }

    if (linesVector[0][0] != '{') {
        throw ParseException();
    } else if (linesVector[linesVector.size() - 1][0] != '}') {
        throw ParseException();
    }

    for(int i = 1; i < linesVector.size() - 2; i++) {
        if (linesVector[i].empty()) { continue; }
        if (linesVector[i][linesVector[i].size() - 1] != ',') {
            throw ParseException();
        }
    }
    if (linesVector[linesVector.size()-2][linesVector[linesVector.size()-2].size()-1] == ',') {
        throw ParseException();
    }

    for(int i = 1; i < linesVector.size() - 1; i++) {
        if (linesVector[i].empty()) { continue; }
        
        int commaCount = 0;
        int commaIndex = 0;
        int thirthCommaIndex = 0;
        for (char& iter : linesVector[i]){
            if (iter == '"') {
                commaCount++;
            }
        }
        if (commaCount == 2) {
            std::string cuttedRow = linesVector[i].substr(1);
            commaIndex = cuttedRow.find_first_of('"');

            if (linesVector[i][commaIndex + 2] != ':') {
                throw ParseException();
            }
        } else if (commaCount == 4) {
            std::string cuttedRow = linesVector[i].substr(1);
            commaIndex = cuttedRow.find_first_of('"');
            int dotIndex = commaIndex + 1;
            thirthCommaIndex = commaIndex + 2;

            if (dotIndex < commaIndex || dotIndex > thirthCommaIndex){
                throw ParseException();
            }
        } else {
            throw ParseException();
        }

        int j = 0;
        for( j = linesVector[i].size(); j > commaIndex; j--) {
            if ((linesVector[i][j] == ':') || (linesVector[i][j] != ' ')) {
                break;
            }
        }

        if (j - 1 == commaIndex + 1) {
            throw ParseException();
        }

        std::string temp = linesVector[i].substr(commaIndex);
        int beforeDD = temp.find_first_of(':');

        for (; beforeDD > 0; beforeDD--) {
            if (linesVector[i][beforeDD] == '"')
            {
                break;
            }
        }

        if (linesVector[i][0] != '"') {
            throw ParseException();
        } else if (linesVector[i][beforeDD] != '"') {
            throw ParseException();
        }
    }
}
