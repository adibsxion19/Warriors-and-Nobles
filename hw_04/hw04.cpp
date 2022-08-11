/*
Aadiba Haque
hw 04
Models a medeival games where warriors fight each other on behalf of nobles.
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

/* stores warrior name and strength, gives name and strength if 
asked and changes warrior strength after nobles battles*/
class Warrior {
public:
    Warrior(const string& name, int strength) :
        name(name), strength(strength) {}
    int getStrength() const { return strength; }
    void changeStrength(double ratio) {
        strength = strength - (strength * ratio);
    }
    string getName() const { return name; }
private:
    string name;
    int strength;
};

/*stores Noble's information and lets them fire and hire warriors
and battle with each other*/
class Noble {
    friend ostream& operator<<(ostream& os, const Noble& noble);
public:
    Noble(const string& name) :
        name(name) {}
    bool hire(Warrior& warrior) { 
        //adds warrior to noble's army if he's alive
        if (warrior.getStrength() == 0) {
            return false;
        } else {
            vectorOfWarriors.push_back(&warrior);
            return true;
        }

    }

    bool fire(Warrior& warrior) {
        //takes warrior out of vector if it can
        int index = 0;
        for (size_t i = 0; i < vectorOfWarriors.size(); ++i) {
            if (&warrior == vectorOfWarriors[i]) {
                index = i;
            }
            if (index >= i and i+1 > vectorOfWarriors.size()) {
                vectorOfWarriors[i] = vectorOfWarriors[i + 1];
            }

        }
        if (index == 0) {
            return false;
        } else {
            cout << "You don't work for me anymore " <<
                warrior.getName() + "! -- " << name + '.' << endl;
            vectorOfWarriors.pop_back();
            return true;
        }
    }
    int sumStrength() {
        //adds strengths of warriors in vectors
        int sumStrength = 0;
        for (size_t i = 0; i < vectorOfWarriors.size(); ++i) {
            sumStrength += vectorOfWarriors[i]->getStrength();
        }
        return sumStrength;
    }
    void battle(Noble& noble) {
        //battles nobles, changes strengths, outputs outcomes
        string noble1Name = name;
        string noble2Name = noble.name;
        cout << noble1Name + " battles " + noble2Name << endl;
        int strength1 = this->sumStrength();
        int strength2 = noble.sumStrength();
        if (strength1 == 0 || strength2 == 0) {
            if (strength1 == 0 && strength2 == 0) {
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
            else if (strength2 == 0) {
                cout << "He's dead, " + noble1Name << endl;
            }
            else if (strength1 == 0) {
                cout << "He's dead, " + noble2Name << endl;
            }
        } else {
            for (size_t i = 0; i < vectorOfWarriors.size(); ++i) {
                    if (strength1 > strength2) {
                        vectorOfWarriors[i]->
                            changeStrength(strength2 / (strength1 * 1.0));
                        cout << noble1Name + " defeats " + noble2Name << endl;
                    }
                    else if (strength1 < strength2) {
                        vectorOfWarriors[i]->changeStrength(1.0);
                        cout << noble2Name + " defeats " + noble1Name << endl;
                    }
                    else if (strength1 == strength2) {
                        vectorOfWarriors[i]->changeStrength(1.0);
                        cout << "Mutual Annihilation: " + noble1Name + 
                            " and " + noble2Name + " die at each other's hands" << endl;
                    }

            }
            for (size_t i = 0; i < noble.vectorOfWarriors.size(); ++i) {
                    if (strength1 > strength2) {
                        noble.vectorOfWarriors[i]->changeStrength(1.0);
                    }
                    else if (strength1 < strength2) {
                        noble.vectorOfWarriors[i]->
                            changeStrength(strength1 / (strength2 * 1.0));
                    }
                    else if (strength1 == strength2) {
                        noble.vectorOfWarriors[i]->changeStrength(1.0);
                    }
            }



        }
    }
private:
    vector<Warrior*> vectorOfWarriors;
    string name;
};

//displays noble name and army size, and each warrior name and strength in their army
ostream& operator<<(ostream& os, const Noble& noble) {
    os << noble.name << " has an army of " << noble.vectorOfWarriors.size()
        << endl;
    for (size_t i = 0; i < noble.vectorOfWarriors.size(); ++i) {
        os << "\t" + noble.vectorOfWarriors[i]->getName() + ": " << 
            noble.vectorOfWarriors[i]->getStrength() << endl;
    }
    return os;
}

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

    cout << "==========\n"
        << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

    art.fire(cheetah);
    cout << art << endl;
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
    cout << "==========\n"
        << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

}


