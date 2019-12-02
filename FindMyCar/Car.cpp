

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
