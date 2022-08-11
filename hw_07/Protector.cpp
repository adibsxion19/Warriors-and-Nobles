/*Aadiba Haque - OOP
* Protector.cpp
* Protector implementation file
* definition of Protector and its derived classes' methods
*/
#include "Noble.h"
#include "Protector.h"

#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft {
    Protector::Protector(string name, double strength) : 
        name(name), strength(strength) {}

    const string& Protector::getName() const { return name; }

    bool Protector::employed() const {
        //returns employed status -- do they have a boss?
        if (boss) { return true; }
        else { return false; }
    }

    //protector gains a boss
    void Protector::hired(Lord* lord) { boss = lord; }

    //protector loses boss
    void Protector::fired() { boss = nullptr; }

    /* part of defense statement of every warrior -- called in 
    other defense methods*/
    void Protector::defend(const Lord& lord) const {
        cout << getName() << " says: Take that in the name of my lord, "
            << lord.getName() << endl;
    }

    //protector quits - same functions as being fired
    bool Protector::quit() {
        if (boss->fires(*this)) { return true; }
        else { return false; }
    }

    // returns strength of protector
    double Protector::getStrength() const { return strength; }
   
    void Protector::changeStrength(double ratio) {
        //reduces strength by ratio 
        strength = strength - (strength * ratio);
    }

    Warrior::Warrior(string name, double strength) : 
        Protector(name, strength) {}

    Archer::Archer(string name, double strength) : 
        Warrior(name, strength) {}

    
    void Archer::defend(const Lord& lord) const {
        //Archer's defense statement
        cout << "TWANG! ";
        Protector::defend(lord);
    }

    Swordsman::Swordsman(string name, double strength) : 
        Warrior(name, strength) {}

    void Swordsman::defend(const Lord& lord) const {
        //Swordsman's defense statement
        cout << "CLANG! ";
        Protector::defend(lord);
    }

    Wizard::Wizard(string name, double strength) : Protector(name, strength) {}
    
    //Wizard's defense statement
    void Wizard::defend(const Lord& lord) const { cout << "POOF\n"; }

}