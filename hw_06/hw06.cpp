/* Aadiba Haque
* OOP HW 6
* Implements medieval game where warriors battle each other
on behalf of the noble they work for.
*/

#include "Noble.h"
#include "Warrior.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace WarriorCraft;

int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	cout << "================ Initial Status ===============" << endl;
	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie;
	cout << "===============================================\n\n";

	cheetah.runaway();
	cout << art << endl;

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

	cout << "\n================ Final Status ===============" << endl;
	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;
	// Tarzan should be unemployed
	cout << "Tarzan's Hire Status: " << boolalpha << cheetah.isHired() << endl;
	cout << "===============================================\n\n";
}

