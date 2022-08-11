/*Aadiba Haque - OOP
* Noble.cpp
* Noble implementation file
* definition of Noble and its derived classes' methods
*/

#include "Noble.h"
#include "Protector.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace WarriorCraft {
    Noble::Noble(string name) : name(name) {}

    void Noble::battle(Noble& noble) {
        /*battles nobles, noble (that is alive) is defended (by himself or 
        army), strength is determined (lord - combined strength of army, 
        person with strength - own strength), reduces strength of both nobles
        based on stronger opponent, weaker opponent(s) die, outputs outcomes*/
        string noble1Name = name;
        string noble2Name = noble.name;
        double noble1Strength = getStrength();
        double noble2Strength = noble.getStrength();
        cout << noble1Name + " battles " + noble2Name << endl;
        if (alive) { defend(); }
        if (noble.alive) { noble.defend(); }
        if (!alive && !noble.alive) {
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (!noble.alive) {
            cout << "He's dead, " + noble1Name << endl;
        }
        else if (!alive) {
            cout << "He's dead, " + noble2Name << endl;
        }
        else {
            if (noble1Strength > noble2Strength) {
                changeStrength(noble2Strength / (noble1Strength * 1.0));
                noble.changeStrength(1.0);
                noble.alive = false;
                cout << noble1Name + " defeats " + noble2Name << endl;
            }
            else if (noble1Strength < noble2Strength) {
                changeStrength(1.0);
                noble.changeStrength(noble1Strength / (noble2Strength * 1.0));
                alive = false;
                cout << noble2Name + " defeats " + noble1Name << endl;
            }
            else if (noble1Strength == noble2Strength) {
                changeStrength(1.0);
                noble.changeStrength(1.0);
                alive = false;
                noble.alive = false;
                cout << "Mutual Annihilation: " + noble1Name +
                    " and " + noble2Name + " die at each other's hands" 
                    << endl;
            }
        }
    }

    const string& Noble::getName() const { return name; }

    Lord::Lord(string name) : Noble(name) {}

    bool Lord::hires(Protector& prot) {
        /*if protector given is unemployed, then hired -- added to army vector
        and protector adds boss (calling hired method). return if hiring
        success or fail*/
        if (!prot.employed()) {
            army.push_back(&prot);
            prot.hired(this);
        }
        return prot.employed();
    }

    bool Lord::fires(Protector& prot) {
        /*if protector given is in army, then fired -- taken away from army 
        vector keeping order and protector loses boss (calling 
        fired method). return if firing success or fail*/
        bool found = false;
        for (size_t i = 0; i < army.size(); ++i) {
            if (army[i] == &prot) {
                found = true;
                prot.fired();
            }
            if (found && ((i + 1) < army.size())) {
                army[i] = army[i + 1];
            }

        } if (found) {
            army.pop_back();
        }
        return found;
    }

    void Lord::defend() const {
        // lord is defended by everyone in army
        for (size_t i = 0; i < army.size();++i) {
            army[i]->defend(*this);
        }
    }

    double Lord::getStrength() const {
        //returns strength of lord (combined strength of his army)
        double strength = 0;
        for (size_t i = 0; i < army.size();++i) {
            strength += army[i]->getStrength();
        }
        return strength;
    }

    void Lord::changeStrength(double ratio) {
        //everyone in army loses strength based on ratio
        for (size_t i = 0;i < army.size();++i) {
            army[i]->changeStrength(ratio);
        }
    }

    PersonWithStrengthToFight::PersonWithStrengthToFight
    (string name, double strength) : Noble(name), strength(strength) {}

    //person with strength's defense statement
    void PersonWithStrengthToFight::defend() const { cout << "Ugh!\n"; }

    void PersonWithStrengthToFight::changeStrength(double ratio) {
        // person with strength loses own strength based on ratio
        strength = strength - (strength * ratio);
    }

    // returns own strength of person with strength
    double PersonWithStrengthToFight::getStrength() const { return strength; }

}