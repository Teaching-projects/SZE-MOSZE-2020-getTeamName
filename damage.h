#ifndef DAMAGE_H
#define DAMAGE_H

struct Damage{
    
		int physical; ///< A Hero physical támadási ereje.
		int magical; ///< A Hero magical támádási ereje.

        Damage& operator+(const Damage& uj){ ///< A sebzési típusok + operátoros működése
            this->physical + uj.physical;
            this->magical + uj.magical;
            return *this;
        }

        Damage& operator+=(const Damage& uj){ ///< A sebzési típusok += operátoros működése
            this->physical += uj.physical;
            this->magical += uj.magical;
            return *this;
        }

        Damage& operator*=(const Damage& uj){ ///< A sebzési típusok *= operátoros működése
            this->physical *= uj.physical;
            this->magical *= uj.magical;
            return *this;
        }

	};

#endif //DAMAGE_H