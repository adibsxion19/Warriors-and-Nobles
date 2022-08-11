/*Aadiba Haque - OOP
* Noble.cpp
* Noble implementation file
* definition of Noble class methods
*/
#include "Noble.h"
#include "Warrior.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace WarriorCraft {

	ostream& operator<<(ostream& os, const Noble& noble) {
		os << noble.name << " has an army of " << noble.armyVec.size()
			<< endl;
		for (size_t i = 0; i < noble.armyVec.size(); ++i) {
			os << "\t" << noble.armyVec[i]->getName() + ": " <<
				noble.armyVec[i]->getStrength() << endl;
		}
		return os;
	}
	Noble::Noble(const string& name) : name(name) {}

	bool Noble::hire(Warrior& warrior) {
		// Noble hires unemployed warrior.
		if (warrior.isHired()) {
			cout << "Come on Noble " + name + ", Warrior " + warrior.getName() +
				" is already employed. Hiring failed. \n";
		}
		else {
			armyVec.push_back(&warrior);
			warrior.hired(this);
		}
		return warrior.isHired();

	}

	bool Noble::fire(Warrior& warrior) {
		//Noble fires warrior in his army.
		bool found = false;
		for (size_t i = 0; i < armyVec.size(); ++i) {
			if (armyVec[i]->getName() == warrior.getName()) {
				found = true;
				warrior.fired();
			}
			if (found && ((i + 1) < armyVec.size())) {
				armyVec[i] = armyVec[i + 1];
			}

		}
		if (found) {
			armyVec.pop_back();
			cout << "You don't work for me anymore " <<
				warrior.getName() + "! -- " << name + '.' << endl;
		}
		else {
			cout << "Warrior " + warrior.getName() + " is not enlisted in "
				+ name + "'s army. \n";
		}
		return found;
	}

	bool Noble::abandoned(Warrior& warrior) {
		// warrior runs away, abandons noble
		bool found = false;
		for (size_t i = 0; i < armyVec.size(); ++i) {
			if (armyVec[i]->getName() == warrior.getName()) {
				found = true;
				warrior.fired();
			}
			if (found && ((i + 1) < armyVec.size())) {
				armyVec[i] = armyVec[i + 1];
			}

		}
		if (found) {
			armyVec.pop_back();
			cout << warrior.getName() + " flees in terror, abonding his lord, " <<
				name << endl;
		}
		else {
			cout << "Warrior " + warrior.getName() + " is not enlisted in "
				+ name + "'s army. \n";
		}
		return found;
	}

	double Noble::sumStrength() {
		//finds total strengths of warriors in vectors
		double sumStrength = 0;
		for (size_t i = 0; i < armyVec.size(); ++i) {
			sumStrength += armyVec[i]->getStrength();
		}
		return sumStrength;
	}

	void Noble::battle(Noble& noble) {
		//battles nobles, changes strengths, outputs outcomes
		string noble1Name = name;
		string noble2Name = noble.name;
		cout << noble1Name + " battles " + noble2Name << endl;
		double strength1 = this->sumStrength();
		double strength2 = noble.sumStrength();
		if (!alive || !noble.alive) {
			if (!alive && !noble.alive) {
				cout << "Oh, NO! They're both dead! Yuck!" << endl;
			}
			else if (!noble.alive) {
				cout << "He's dead, " + noble1Name << endl;
			}
			else if (!alive) {
				cout << "He's dead, " + noble2Name << endl;
			}
		}
		else {
			for (size_t i = 0; i < armyVec.size(); ++i) {
				if (strength1 > strength2) {
					armyVec[i]->
						changeStrength(strength2 / (strength1 * 1.0));
					noble.alive = false;
					cout << noble1Name + " defeats " + noble2Name << endl;
				}
				else if (strength1 < strength2) {
					armyVec[i]->changeStrength(1.0);
					noble.alive = false;
					cout << noble2Name + " defeats " + noble1Name << endl;
				}
				else if (strength1 == strength2) {
					armyVec[i]->changeStrength(1.0);
					alive = false;
					noble.alive = false;
					cout << "Mutual Annihilation: " + noble1Name +
						" and " + noble2Name + " die at each other's hands" << endl;
				}

			}
			for (size_t i = 0; i < noble.armyVec.size(); ++i) {
				if (strength1 > strength2) {
					noble.armyVec[i]->changeStrength(1.0);
				}
				else if (strength1 < strength2) {
					noble.armyVec[i]->
						changeStrength(strength1 / (strength2 * 1.0));
				}
				else if (strength1 == strength2) {
					noble.armyVec[i]->changeStrength(1.0);
				}
			}



		}
	}

	const string& Noble::getName() const { return name; }
}