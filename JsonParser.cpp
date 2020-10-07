#include "JsonParser.h"

JsonParser::JsonParser(std::string fName) {
    file = new std::ifstream(fName);
    parseJson();
}

JsonParser::JsonParser(std::ifstream& pFile) {
    file = &pFile;
    parseJson();
}

double JsonParser::getDouble(std::string key) const {
    return std::stod(data.at(key));
}

std::map<std::string, std::string> JsonParser::getData() const { 
    return data; 
}

std::string JsonParser::getString(std::string key) const {
    return data.at(key);
}

void JsonParser::parseJson() {
    bool isKey = false;
    std::string line;
    std::list<std::string> lines;
    std::list<std::string> keyValues;
    
    while (std::getline(*file, line)) {
        lines.push_back(line);
    }
    
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
            } else if (c == ',') {
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
        
        data.insert(std::make_pair(key, value));
    }

    keyValues.clear();
}