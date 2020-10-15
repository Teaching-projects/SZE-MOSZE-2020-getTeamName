#include "JsonParser.h"
#include <vector>

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

bool JsonParser::validateJson(std::list<std::string> lines) {
    std::vector<std::string> linesVector;

    for (auto line : lines) { 
        linesVector.push_back(line);
    }
    
    for (int i = 0; i < linesVector.size(); i++) {
        std::string tempString = "";
        for (char iter : linesVector[i]) {
            if (iter != ' ') {
                tempString += iter;
            }
        }
        linesVector[i] = tempString;
    }

    if (linesVector[0][0] != '{') {
        throw BadJsonException("Missing start sign", 22, 1);
    } else if (linesVector[linesVector.size() - 1][0] != '}') {
        throw BadJsonException("Missing end sign", 23, linesVector.size());
    }

    for(int i = 1; i < linesVector.size() - 2; i++) {
        if (linesVector[i][linesVector[i].size() - 1] != ',') {
            throw BadJsonException("Missing line end \",\" character", 24, i+1);
        }
    }
    if (linesVector[linesVector.size()-2][linesVector[linesVector.size()-2].size()-1] == ',') {
        throw BadJsonException("Trailing comma error", 26, linesVector.size()-1 );
    }
    
    for(int i = 1; i < linesVector.size() - 1; i++) {

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
                throw BadJsonException("Bad : character", 27,i+1);
            }
        } else if (commaCount == 4) {
            std::string cuttedRow = linesVector[i].substr(1);
            commaIndex = cuttedRow.find_first_of('"');
            int dotIndex = commaIndex + 1;
            thirthCommaIndex = commaIndex + 2;

            if (dotIndex < commaIndex || dotIndex > thirthCommaIndex){
                throw BadJsonException("Bad : character", 25, i + 1);
            }
        } else {
            throw BadJsonException("Bad key value declaration (missing '\"' character)", 25, i + 1);
        }

        int j = 0;
        for( j = linesVector[i].size(); j > commaIndex; j--) {
            if ((linesVector[i][j] == ':') || (linesVector[i][j] != ' ')) {
                break;
            }  
        }

        if (j - 1 == commaIndex + 1) {
            throw BadJsonException("value expected", 21, i + 1);
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
            throw BadJsonException("Bad key value declaration (missing '\"' character)", 25, i + 1);
        } else if (linesVector[i][beforeDD] != '"') {
            throw BadJsonException("Bad key value declaration (missing '\"' character)", 25, i + 1);
        }
    }   
}