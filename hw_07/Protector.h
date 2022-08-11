/*Aadiba Haque - OOP
* Protector.h
* Protector header file
* definition of Protector class, it's derived classes, and
its method prototypes
*/

#ifndef PROTECTOR_H
#define PROTECTOR_H
#include <iostream>
#include <string>

namespace WarriorCraft {
    class Noble;
    /*Protector can be hired, fired, or quit job to defend a lord. They all
    have strengths and can battle for their lord -- can lose strength, die in
    battle. Types of Protectors: Warrior and Wizards; Type of Warriors: Archers
    and Sworsmen. Each have a class and defend in their own way.*/
    class Protector {
    public:
        Protector(std::string name, double strength);
        const std::string& getName() const;
        bool employed() const;
        void hired(Lord*);
        void fired();
        virtual void defend(const Lord&) const = 0;
        bool quit();
        double getStrength() const;
        void changeStrength(double);
    private:
        std::string name;
        double strength;
        Lord* boss = nullptr;
        bool alive = true;
    };

    class Warrior : public Protector {
    public:
        Warrior(std::string name, double strength);
    };

    class Archer : public Warrior {
    public:
        Archer(std::string name, double strength);
        void defend(const Lord&) const;
    };

    class Swordsman : public Warrior {
    public:
        Swordsman(std::string name, double strength);
        void defend(const Lord&) const;
    };

    class Wizard : public Protector {
    public:
        Wizard(std::string name, double strength);
        void defend(const Lord&) const;
    };
}
#endif