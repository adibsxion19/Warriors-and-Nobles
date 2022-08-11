/* Author: Aadiba Haque, 
OOP HW 2, 
Description: Our program  reads in Warrior, Battle, and Status commands, with
info about warriors, their strengths, and who they battle. It outputs
the warriors and their strengths if status is called,
and the outcome of the battles. */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/* Known problems: Assumme all commands are given on seperate lines.
Code doesn't output properly otherwise, because each command is read
in as the first string of each line. Also, don't make a warrior battle
himself,because then two different warriors aren't compared and their strengths
modified, as the code does.
*/


// struct holds info about a warrior: name and their strength.
struct Warrior {
	string name;
	int strength = 0;
};


void readLines(ifstream& warriorsTxt, string& command, int count);
void warriorCommand(vector<Warrior>& vectorOfWarriors, const string& name,
	int strength);
void battleCommand(vector<Warrior>& vectorOfWarriors, const string& warriorOne,
	const string& warriorTwo);
void statusCommand(const vector<Warrior>& vectorOfWarriors);
void changeStrength(vector<Warrior>& vectorOfWarriors, const string&
	warriorOne, const string& warriorTwo, int strengthOne, int strengthTwo);




/* Reads in text file, counts number of lines in file, clears and starts from
top of file, calls readLines function, and closes file.
*/
int main() {
	ifstream warriorsTxt("warriors.txt");
	string line;
	string command;
	int count = 0;
	while (getline(warriorsTxt, line)) { 
		++count;
	}
	warriorsTxt.clear();
	warriorsTxt.seekg(0);
	readLines(warriorsTxt, command, count);
	warriorsTxt.close();
}



/* Initialized vector to hold warrior info.
loops through for the number of lines in the file,
reads the first word of every line of the file,
a command, and nothing else, warrior name and strength, OR two names 
(depending on the command), calls the respective function to carry out command.
*/
void readLines(ifstream& warriorsTxt, string& command, int count) {
	vector<Warrior> vectorOfWarriors;
	for (int i = 0; i < count; ++i) {
		warriorsTxt >> command;
		if (command == "Warrior") {
			string name;
			int strength;
			warriorsTxt >> name >> strength;
			warriorCommand(vectorOfWarriors, name, strength);
		}
		else if (command == "Battle") {
			string warriorOne;
			string warriorTwo;
			warriorsTxt >> warriorOne >> warriorTwo;
			battleCommand(vectorOfWarriors, warriorOne, warriorTwo);
		}
		else if (command == "Status") {
			statusCommand(vectorOfWarriors);
		}
	}
}



// Creates new warrior struct and adds Warrior to the vector.
void warriorCommand(vector<Warrior>& vectorOfWarriors, const string& name,
	int strength) {
	Warrior warrior;
	warrior.name = name;
	warrior.strength = strength;
	vectorOfWarriors.push_back(warrior);
}



/* displays who battles whom, loops through vector to find the warriors' 
strengths, compares strength to determine outcome. Displays different outcomes
for different scenarios, calls changeStrength function if strength of warriors
change (when neither strength is 0) to modify warriors' strengths.
*/
void battleCommand(vector<Warrior>& vectorOfWarriors, const string& warriorOne,
	const string& warriorTwo) {
	int strengthOne = 0;
	int strengthTwo = 0;
	string output;
	cout << warriorOne + " battles " + warriorTwo << endl;
	for  (const Warrior& warrior : vectorOfWarriors) {
		if (warrior.name == warriorOne) {
			// warriorOne has strengthOne
			strengthOne = warrior.strength;
		} else if (warrior.name == warriorTwo) {
			// warriorTwo has strengthTwo
			strengthTwo = warrior.strength;
		}
	}

	if (strengthOne == 0 || strengthTwo == 0) {
		if (strengthOne == 0 && strengthTwo == 0) {
			output = "Oh, NO! They're both dead! Yuck!";
		} else if (strengthOne == 0) {
			output = "He's dead, " + warriorTwo;
		} else if (strengthTwo == 0) {
			output = "He's dead, " + warriorOne;
		} 

	} else {
		changeStrength(vectorOfWarriors, warriorOne, warriorTwo, strengthOne,
			strengthTwo);
		if (strengthOne == strengthTwo) {
			output = "Mutual Annihilation: " + warriorOne + " and " + warriorTwo +
				" die at each other's hands";
		} else if (strengthOne > strengthTwo) {
			output = warriorOne + " defeats " + warriorTwo;
		} else if (strengthOne < strengthTwo) {
			output = warriorTwo + " defeats " + warriorOne;
		}
	}
	cout << output << endl;
}



/*loops through the vector, accessing each warrior's information.
if warriors have the same strength, both strengths change to 0,
else, both strengths decrease by the value of the lower strength
*/
void changeStrength(vector<Warrior>& vectorOfWarriors, const string&
	warriorOne, const string& warriorTwo, int strengthOne, int strengthTwo) {
	for ( Warrior& warrior : vectorOfWarriors) {
		if (warrior.name == warriorOne || warrior.name == warriorTwo) {
			if (strengthOne == strengthTwo) {
				warrior.strength = 0;
			} else if (strengthOne > strengthTwo) {
				warrior.strength -= strengthTwo;
			} else if (strengthOne < strengthTwo) {
				warrior.strength -= strengthOne;
			}
		}
	}
}



/*displays number of warriors on first line. On every line after that,
displays warrior name and strength information.
*/
void statusCommand(const vector<Warrior>& vectorOfWarriors) {
	cout << "There are: " << vectorOfWarriors.size() << " warriors " << endl;
	for (const Warrior& warrior : vectorOfWarriors) {
		cout << "Warrior: " + warrior.name + ", strength: " << warrior.strength
			<< endl;
	}
}