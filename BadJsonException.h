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
#include <string>


class BadJsonException : public std::runtime_error {
    int errorCode; ///< Hibakód
    int line; ///< Melyik sorban van a hiba

public:
    BadJsonException(std::string what_, int errorCode_, int line_) : std::runtime_error(what_), errorCode(errorCode_), line(line_)  {}; ///< BadJsonException konstruktora, ami paraméterben várja a hibaüzenet szövegét, a hibakódot és azt, hogy melyik sorban található
    int getErrorCode() { return errorCode; } ///< Ez egy getter függvény, ami visszaadja a hibakódot
    const char* what() { return std::runtime_error::what() + '\n' + 'at line: ' + line; } ///< Hibaüzenet kiíratása
};
