#pragma once
#include <iostream>
#include <string>


class BadJsonException : public std::runtime_error {
    int errorCode;
    int line;

public:
    BadJsonException(std::string what_, int errorCode_, int line_) : std::runtime_error(what_), errorCode(errorCode_), line(line_)  {};
    int getErrorCode() { return errorCode; }
    const char* what() { return std::runtime_error::what() + '\n' + 'at line: ' + line; }
};