/*Aadiba Haque - OOP
* Warrior.cpp
* Warrior implementation file
* definition of Warrior class methods
*/
#include "Noble.h"
#include "Warrior.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace WarriorCraft {
	ostream& operator<<(ostream& os, const Warrior& warrior) {
		os << warrior.name + ": " << warrior.strength << endl;
		return os;
	}

	Warrior::Warrior(const string& name, double strength) :
		name(name), strength(strength) {}


	double Warrior::getStrength() const { return strength; }

	void Warrior::changeStrength(double ratio) {
		strength = strength - (strength * ratio);
	}

	bool Warrior::runaway() {
		//warrior runs away
		return boss->abandoned(*this);
	}

	bool Warrior::isHired() {
		//checks if warrior is employed
		if (boss) {
			return true;
		}
		else {
			return false;
		}
	}

	const string& Warrior::getName() const { return name; }
	//warrior is fired or hired by noble:
	void Warrior::fired() { boss = nullptr; }
	void Warrior::hired(Noble* noble) { boss = noble; }
}