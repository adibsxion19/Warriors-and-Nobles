/*Aadiba Haque - OOP
* Noble.h
* Noble header file
* definition of Noble class and its method prototypes
*/

#include <iostream>
#include <string>
#include <vector>
namespace WarriorCraft {
	class Warrior;
	/* noble class holds name and its army. Can hire, fire warriors,
	battles nobles, be abandoned by warrior, returns name, sums strength of
	army if asked.*/
	class Noble {
		friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
	public:
		Noble(const std::string& name);
		bool hire(Warrior& warrior);
		bool fire(Warrior& warrior);
		bool abandoned(Warrior& warrior);
		double sumStrength();
		void battle(Noble& noble);
		const std::string& getName() const;
	private:
		std::string name;
		std::vector<Warrior*> armyVec;
		bool alive = true;
	};
}