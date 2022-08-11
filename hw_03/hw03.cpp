/* Author: Aadiba Haque
OOP HW 03
This program models a medieval game.
It reads information about warriors, their weapons (and strengths),
and their battles from a file and modifies/outputs their information with
certain commands.  */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


//stores and changes information about the warrior
class Warrior {
	friend ostream& operator<<(ostream& os, const Warrior& warrior);
public:
	Warrior(const string& name, const string& weaponName, int strength) : 
		name(name), weapon(weaponName, strength) {}
	const string& getName() const { return name; }

	/*battles the warrior given in the parameter with the warrior in the current 
	warrior class. Compares their weapon's strength, outputting the right
	outcome and changing weapon's strength for certain conditions.*/
	void battle(Warrior& warrior2) {
		string warrior1Name = name;
		string warrior2Name = warrior2.getName();
		cout << warrior1Name + " battles " + warrior2Name << endl;
		int strength1 = weapon.getStrength();
		int strength2 = warrior2.weapon.getStrength();
		if (strength1 == 0 || strength2 == 0) {
			if (strength1 == 0 && strength2 == 0) {
				cout << "Oh, NO! They're both dead! Yuck!" << endl;
			} else if (strength1 == 0) {
				cout << "He's dead, " + warrior2Name << endl;
			} else if (strength2 == 0) {
				cout << "He's dead, " + warrior1Name << endl;
			}
		}
		else {
			if (strength1 >= strength2) {
				weapon.changeStrength(strength2);
				warrior2.weapon.changeStrength(strength2);
			} else {
				weapon.changeStrength(strength1);
				warrior2.weapon.changeStrength(strength1);
			}
			if (strength1 == strength2) {
				cout << "Mutual Annihilation: " + warrior1Name + " and " + warrior2Name +
					" die at each other's hands" << endl;
			} else if (strength1 > strength2) {
				cout << warrior1Name + " defeats " + warrior2Name << endl;
			} else if (strength1 < strength2) {
				cout << warrior2Name + " defeats " + warrior1Name << endl;
			}
		}
	}
private:
	string name;
	/*holds the warrior's weapon and its strength. Modifies and gives strength to
	warrior class if needed. output operator outputs weapon's name and strength*/
	class Weapon {
		friend ostream& operator<<(ostream& os, const Warrior::Weapon& weapon) {
			os << " weapon: " << weapon.weaponName + ", " << weapon.strength;
			return os;
		}
	public:
		Weapon(const string& weaponName, int strength) : 
			weaponName(weaponName), strength(strength) {}
		int getStrength() const { return strength; }
		void changeStrength(int subStrength) {
			strength -= subStrength;
		}
	private:
		string weaponName;
		int strength;
	};
	Weapon weapon;
};

/*overloads output operator to output warrior's name and weapon info 
(by calling weapon's output operator)*/
ostream& operator<<(ostream& os, const Warrior& warrior) {
	os << "Warrior: " << warrior.name << ',' << warrior.weapon;
	return os;
}



int findWarrior(const vector<Warrior>& vectorOfWarriors, 
	const string& warriorName);
void status(const vector<Warrior>& vectorOfWarriors);


/*reads through the file, reading in the command at the beginning of each line,
then accordingly stores other information from the file. It also calls functions/class
that will execute the command.*/
int main() {
	string line;
	string command;
	vector<Warrior> vectorOfWarriors;
	ifstream warriorsTxt("warriors.txt");
	while (warriorsTxt >> command) {
		if (command == "Warrior") {
			string name;
			string weapon;
			int strength;
			warriorsTxt >> name >> weapon >> strength;
			Warrior warrior(name, weapon, strength);
			vectorOfWarriors.push_back(warrior);
		} else if (command == "Battle") {
			string warrior1Name;
			string warrior2Name;
			warriorsTxt >> warrior1Name >> warrior2Name;
			int index1 = findWarrior(vectorOfWarriors, warrior1Name);
			int index2 = findWarrior(vectorOfWarriors, warrior2Name);
			if (index1 != vectorOfWarriors.size() && index2 != vectorOfWarriors.size()){
				vectorOfWarriors[index1].battle(vectorOfWarriors[index2]);
			}
		} else if (command == "Status") {
			status(vectorOfWarriors);
		}
	}
	warriorsTxt.close();
}

/*loops through vector to find index the warrior we are looking for is stored. 
Returns that index, but if index not found (warrior doesn't exist), 
return length of vector. */
int findWarrior(const vector<Warrior>& vectorOfWarriors, 
	const string& warriorName) {
	for (int i = 0; i < vectorOfWarriors.size(); ++i) {
		if (vectorOfWarriors[i].getName() == warriorName) {
			return i;
		}
	}
	return vectorOfWarriors.size();
}

/*diisplays the warrior's information by looping through the vector, 
outputting the warrior, which calls the output stream for warrior.*/
void status(const vector<Warrior>& vectorOfWarriors) {
	cout << "There are: " << vectorOfWarriors.size() << " warriors " << endl;
	for (const Warrior& warrior : vectorOfWarriors) {
		cout << warrior << endl;
	}
}
