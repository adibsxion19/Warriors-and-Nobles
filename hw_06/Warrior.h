/*Aadiba Haque - OOP
* Warrior.h
* Warrior header file
* definition of Warrior class and its method prototypes
*/

#include <iostream>
#include <string>
#include <vector>
namespace WarriorCraft {
	class Noble;
	/* warrior class holds name and strength and boss. changes and returns
	strength is needed. Changes boss if hired/fired/runs away 
	and returns name if asked. warrior can also run away.*/
	class Warrior {
		friend std::ostream& operator<<(std::ostream& os, const Warrior& warrior);
	public:
		Warrior(const std::string& name, double strength);
		double getStrength() const;
		void changeStrength(double ratio);
		bool runaway();
		const std::string& getName() const;
		bool isHired();
		void fired();
		void hired(Noble* noble);
	private:
		std::string name;
		double strength;
		Noble* boss = nullptr;
	};
}