
#pragma once
#include <iostream>
#include <iomanip>
#include <string> //used for overloaded output

class Car {
private:
	std::string modelName;
	double mpg;
	double avgPrice;
	double horsePower;
	std::string make;
public:
	Car();
	Car(std::string name, double milesPerGallon, double price, double hp, std::string carMake);
	~Car() {};
	//getters
	double getMpg() { return mpg; }
	double getAvgPrice() { return avgPrice; }
	double getHorsePower() { return horsePower; }
	std::string getModelName() { return modelName; }
	std::string getMake() { return make; }
	//setters
	void setMpg(double milesPerGallon) { mpg = milesPerGallon; }
	void setAvgPrice(double price) { avgPrice = price; }
	void setHorsePower(double hp) { horsePower = hp; }
	void setModelName(std::string name) { modelName = name; }
	void setMake(std::string carMake) { make = carMake; }
	//overloaded operators
	friend std::ostream& operator << (std::ostream& os, const Car &);
	friend std::istream& operator >> (std::istream& is, Car &);




};