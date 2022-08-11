/* Aadiba Haque
* OOP HW 6
* Implements medieval game where warriors battle each other
on behalf of the noble they work for.
*/


#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Noble;

/* warrior class holds name and strength and boss. changes and returns
strength is needed. Changes boss if hired/fired/runs away and 
returns name if asked. warrior can also run away.*/
class Warrior {
	friend ostream& operator<<(ostream& os, const Warrior& warrior);
public:
	Warrior(const string& name, double strength);
	double getStrength() const;
	void changeStrength(double ratio);
	bool runaway();
	const string& getName() const;
	bool isHired();
	void fired();
	void hired(Noble* noble);
private:
	string name;
	double strength;
	Noble* boss = nullptr;
};

/* noble class holds name and its army. Can hire, fire warriors,
battles nobles, be abandoned by warrior, returns name, sums strength of
army if asked.*/
class Noble {
	friend ostream& operator<<(ostream& os, const Noble& noble);
public:
	Noble(const string& name);
	bool hire(Warrior& warrior);
	bool fire(Warrior& warrior);
	bool abandoned(Warrior& warrior);
	double sumStrength();
	void battle(Noble& noble);
	const string& getName() const;
private:
	string name;
	vector<Warrior*> armyVec;
	bool alive = true;
};


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


ostream& operator<<(ostream& os, const Warrior& warrior) {
	os << warrior.name + ": " << warrior.strength << endl;
	return os;
}

ostream& operator<<(ostream& os, const Noble& noble) {
	os << noble.name << " has an army of " << noble.armyVec.size()
		<< endl;
	for (size_t i = 0; i < noble.armyVec.size(); ++i) {
		os << "\t" << noble.armyVec[i]->getName() + ": " <<
			noble.armyVec[i]->getStrength() << endl;
	}
	return os;
}

Warrior::Warrior(const string& name, double strength) :
		name(name), strength(strength) {}


double Warrior::getStrength() const { return strength; }

void Warrior::changeStrength(double ratio) {
	strength = strength - (strength * ratio);
}

bool Warrior::runaway() {
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
void Warrior::fired() { boss = nullptr; }
void Warrior::hired(Noble* noble) { boss = noble; }
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