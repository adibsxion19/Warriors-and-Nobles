/*Aadiba Haque - OOP
* Noble.h
* Noble header file
* definition of Noble class and derived classes and its method prototypes
*/

#ifndef NOBLE_H
#define NOBLE_H
#include <string>
#include <vector>
#include <iostream>
namespace WarriorCraft{
    class Protector;
    /*Classes for Noble and their types: lords and person with strength
    Nobles can battle with each other. Lords' strength comes from their army 
    of Protectors, when they battle, army defends them and loses strength
    simultaneously, and even die -- then Lord also dies. Lords can hire, fire 
    protectors Person with strength have own strength and no army, defends 
    himself, loses strength and can die.*/
    class Noble {
    public:
        Noble(std::string);
        virtual double getStrength() const = 0;
        void battle(Noble&);
        virtual void defend() const = 0;
        virtual void changeStrength(double) = 0;
        const std::string& getName() const;
    private:
        std::string name;
        bool alive = true;
    };

    class Lord : public Noble {
    public:
        Lord(std::string name);
        bool hires(Protector&);
        bool fires(Protector&);
        void defend() const;
        double getStrength() const;
        void changeStrength(double);
    private:
        std::vector<Protector*> army;
    };

    class PersonWithStrengthToFight : public Noble {
    public:
        PersonWithStrengthToFight(std::string name, double strength);
        void defend() const;
        void changeStrength(double);
        double getStrength() const;
    private:
        double strength;
    };
}
#endif