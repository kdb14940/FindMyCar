

#include "Car.h"

 Car::Car() {
	 modelName = "";
	 make = "";
	 mpg = 0;
	 avgPrice = 0;
	 horsePower = 0;
}

 Car::Car(std::string name, double milesPerGallon, double price, double hp, std::string carMake) {
	 modelName = name;
	 make = carMake;
	 mpg = milesPerGallon;
	 avgPrice = price;
	 horsePower = hp;
 }


 /*
 std::ostream& operator << (std::ostream& os, const Car &c) {

	 os << "MAKE:" << std::setw(24) << std::right <<  c.make 
		 << std::setfill('-') << std::setw(69) << std::endl

		 << "MODEL: \t\t|" << std::setw(31) << std::right << c.modelName << "\t\n"
		 << std::setfill('-') << std::setw(69) << std::endl

		 << "CITY/HWY MPG:\t|" << std::setw(25) << std::right << c.mpg << "\t\t\n"
		 << std::setfill('-') << std::setw(69) << std::endl

		 << "HORSEPOWER:\t|" << std::setw(25) << std::right << c.horsePower << "\t\t\n"
		 << std::setfill('-') << std::setw(69) << std::endl

		 << "MSRP:\t\t|" << std::setw(20) << std::right << "$" << c.avgPrice << "\t\n"
		 << std::setfill('=') << std::setw(69) << std::endl;
	 return os;
 }
 */

 std::istream& operator >> (std::istream& is, Car &c)
 {
	 std::string make;
	 std::string model;
	 double price;
	 double mpg;
	 double hp;

	 std::cout << "Enter the vehicles information: \n"
			   << "\nMake: "; is >> make;

	 std::cout << "\nModel: "; is >> model;

	 std::cout << "\nPrice: "; is >> price;

	 std::cout << "\nMPG: "; is >> mpg;

	 std::cout << "\nHorsepower: "; is >> hp;

	 c.setMake(make);
	 c.setModelName(model);
	 c.setAvgPrice(price);
	 c.setMpg(mpg);
	 c.setHorsePower(hp);

	 return is;
 }
 

 
 std::ostream& operator << (std::ostream& os, const Car &c) {
	 os <<  "\n------------------\n"  
		 << c.make << " " << c.modelName
		 << "\nPrice: " << c.avgPrice
		 << "\nMPG: " << c.mpg << "\nHorsepower: "
		 << c.horsePower << std::endl;
	 return os;
}
 /*
 std::istream& operator >> (std::istream& is, Car &c) {
	 std::cout << "Enter car information in the format : \n"
			   << "Make Model Price MPG Horsepower\n"
			   << "For example: Honda Civic 18940 32 205";
	 std::string make;
	 std::string name;
	 double price;
	 double mpg;
	 double horsePower;
	 is >> make >> name >> price >> mpg >> horsePower;
	 c.setMake(make);
	 c.setModelName(name);
	 c.setAvgPrice(price);
	 c.setMpg(mpg);
	 c.setHorsePower(horsePower);
	 return is;
 }
 */