/*  Aadiba Haque
 HW 05
 Models medieval game that reads a file of commands, creates Nobles and
 Warriors and send them off to battle.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
class Noble;

/* warrior class holds name and strength and boss. changes and returns
strength is needed. Changes boss if hired/fired and returns name if asked.*/
class Warrior {
	friend ostream& operator<<(ostream& os, const Warrior& warrior) {
		os << warrior.name + ": " << warrior.strength << endl;
		return os;
	}
public:
	Warrior(const string& name, double strength) :
		name(name), strength(strength) {}
	double getStrength() const { return strength; }
	void changeStrength(double ratio) {
		strength = strength - (strength * ratio);
	}
	string getName() const { return name; }
	void fired() { boss = nullptr; }
	void hired(Noble* noble) { boss = noble; }
	bool employed() {
		if (boss) {
			return true;
		} else { return false; }
	}
private:
	string name;
	double strength;
	Noble* boss = nullptr;
};

/* noble class holds name and its army. Can hire, fire warriors,
battles nobles, returns name, sums strength of army if asked.*/
class Noble {
	friend ostream& operator<<(ostream& os, const Noble& noble) {
		os << noble.name << " has an army of " << noble.armyVec.size()
			<< endl;
		for (size_t i = 0; i < noble.armyVec.size(); ++i) {
			os << "\t" + noble.armyVec[i]->getName() + ": " <<
				noble.armyVec[i]->getStrength() << endl;
		}
		return os;
	}
public:
	Noble(const string& name) : name(name) {}
	bool hire(Warrior* warrior) {
		// Noble hires unemployed warrior.
		if (warrior->employed()) {
			cout << "Come on Noble " + name + ", Warrior " + warrior->getName() + 
				" is already employed. Hiring failed. \n";
			return false;
		} else {
			armyVec.push_back(warrior);
			warrior->hired(this);
			return true;
		}
		
	}
	bool fire(Warrior& warrior) {
		//Noble fires warrior in his army.
		bool found = false;
		for (size_t i = 0; i < armyVec.size(); ++i) {
			if (armyVec[i]->getName() == warrior.getName()){
				found = true;
				warrior.fired();
			}
			if (found && ((i+1) < armyVec.size())) {
				armyVec[i] = armyVec[i + 1];
			}

		} 
		if (found) {
			armyVec.pop_back();
			cout << "You don't work for me anymore " <<
				warrior.getName() + "! -- " << name + '.' << endl;
		} else {
			cout << "Warrior " + warrior.getName() + " is not enlisted in " 
				+ name + "'s army. \n";
		}
		return found;
	}
	double sumStrength() {
		//finds total strengths of warriors in vectors
		double sumStrength = 0;
		for (size_t i = 0; i < armyVec.size(); ++i) {
			sumStrength += armyVec[i]->getStrength();
		}
		return sumStrength;
	}
	void battle(Noble& noble) {
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
	string getName() const { return name; }
private:
	string name;
	vector<Warrior*> armyVec;
	bool alive = true;
};




int main() {
	ifstream ifs("nobleWarriors.txt");
	string command;
	vector<Noble*> nobleVec;
	vector<Warrior*> warriorVec;
	while (ifs >> command) {
		if (command == "Noble") {
			/* reads in noble name from file, creates noble on heap if it
			exists, adds to noble vector*/
			string nobleName;
			ifs >> nobleName;
			bool found = false;
			for (size_t i = 0; i < nobleVec.size(); ++i) {
				if (nobleVec[i]->getName() == nobleName) {
					cout << "Noble" + nobleName + 
						"already exists. Creation of noble failed. \n";
					found = true;
				}
			}
			if (found == false) {
				nobleVec.push_back(new Noble(nobleName));
			}
		} else if (command == "Warrior") {
			/*reads warrior name and strength from file, creates warrior on heap if it
			exists, adds to warrior vector*/
			string warriorName;
			double strength;
			ifs >> warriorName >> strength;
			bool found = false;
			for (size_t i = 0; i < warriorVec.size(); ++i) {
				if (warriorVec[i]->getName() == warriorName) {
					cout << "Noble" + warriorName + 
						"already exists. Creation of warrior failed. \n";
					found = true;
				}
			}
			if (found == false) {
				warriorVec.push_back(new Warrior(warriorName, strength));
			}
			
		} else if (command == "Hire") {
			/*reads in warrior and noble names from file, 
			calls Noble's hire method if they exist*/
			string warriorName;
			string nobleName;
			ifs >> nobleName >> warriorName;
			bool missing = true;
			for (size_t i = 0; i < nobleVec.size(); ++i) {
				for (size_t j = 0; j < warriorVec.size(); ++j) {
					if (nobleVec[i]->getName() == nobleName && warriorVec[j]->getName() 
						== warriorName) {
						nobleVec[i]->hire(warriorVec[j]);
						missing = false;
						break;
					}

				}
			}
			if (missing) {
				cout << "The Noble " + nobleName + " or Warrior " + warriorName + 
					" does not exist. Hiring failed. \n";
			}
		} else if (command == "Fire") {
			/*reads in warrior and noble names from file, 
			calls Noble's fire method if they exist*/
			string warriorName;
			string nobleName;
			ifs >> nobleName >> warriorName;
			bool missing = true;
			for (size_t i = 0; i < nobleVec.size(); ++i) {
				for (size_t j = 0; j < warriorVec.size(); ++j) {
					if (nobleVec[i]->getName() == nobleName && warriorVec[j]->getName() 
						== warriorName) {
						nobleVec[i]->fire(*warriorVec[j]);
						missing = false;
						break;
					}
					
				}
			}
			if (missing) {
				cout << "The Noble " + nobleName + " or Warrior " + warriorName + 
					" does not exist. Firing failed. \n";
			}
		} else if (command == "Battle") {
			// reads in noble names from file, calls battle method on them if they exist
			string noble1Name;
			string noble2Name;
			ifs >> noble1Name >> noble2Name;
			bool missing = true;
			for (size_t i = 0; i < nobleVec.size(); ++i) {
				for (size_t j = 0; j < nobleVec.size(); ++j) {
					if (nobleVec[i]->getName() == noble1Name && nobleVec[j]->getName() 
						== noble2Name) {
						nobleVec[i]->battle(*nobleVec[j]);
						missing = false;
						break;
					}
				}
			}
			if (missing) {
				cout << "Noble " + noble1Name + " or Noble " + noble2Name + 
					" does not exist. Cannot battle. \n";
			}
		} else if (command == "Status") {
			/* displays nobles and their armies (names + strengths) 
			and unemployed warriors*/
			cout << "Status \n" << "======\n";
			cout << "Nobles: \n";
			if (nobleVec.size() == 0) {
				cout << "NONE \n";
			}
			for (size_t i = 0; i < nobleVec.size(); ++i) {
				cout << *nobleVec[i];
			}
			cout << "Unemployed Warriors: \n";
			bool allEmployed = true;
			for (size_t i = 0; i < warriorVec.size(); ++i) {
				if (warriorVec[i]->employed() == false) {
					allEmployed = false;
					cout << *warriorVec[i];
				}
			}
			if (allEmployed) {
				cout << "NONE \n";
			}
		
		} else if (command == "Clear") {
			// deletes nobles and warriors from the heap and clear both vectors
			for (size_t i = 0; i < nobleVec.size(); ++i) {
				delete nobleVec[i];
				nobleVec[i] = nullptr;
			}
			nobleVec.clear();
			for (size_t i = 0; i < warriorVec.size(); ++i) {
				delete warriorVec[i];
				warriorVec[i] = nullptr;
			}
			warriorVec.clear();
		}
	}
	ifs.close();
}