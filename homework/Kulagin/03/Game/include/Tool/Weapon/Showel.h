#pragma once

#include "Weapon.h"

class Showel : public Weapon {

public:
	// BEGIN---------------------------------------------- CONSTRUCTOR ------------------------------------------------
	Showel(string_t name, uint_t attack_rate, uint_t attack_speed, string_t attack_type) :
		Weapon(name, "showel", attack_rate, attack_speed, attack_type)
	{

	}
	// END------------------------------------------------ CONSTRUCTOR ------------------------------------------------

	// BEGIN---------------------------------------------- SETTERS ----------------------------------------------------
	// END------------------------------------------------ SETTERS ----------------------------------------------------

	// BEGIN---------------------------------------------- GETTERS ----------------------------------------------------
	// END------------------------------------------------ GETTERS ----------------------------------------------------

	// BEGIN---------------------------------------------- METHODS ----------------------------------------------------
	// END------------------------------------------------ METHODS ----------------------------------------------------

	// BEGIN---------------------------------------------- DESTRUCTOR -------------------------------------------------
	~Showel() {}
	// END------------------------------------------------ DESTRUCTOR -------------------------------------------------

private:
};