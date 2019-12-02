



/*
This application helps the user
find a car that suits their needs.

Uses a Car class, Binary Search Tree class,
and Hash Table class.

Kyle Bascomb
*/

#include <iostream>
#include <string>
#include "HeadNode.h"
#include <fstream>
using namespace std;

void fillList(HeadNode &headNode);
void printCar(BinaryNode<string>* node);
void writeCar(BinaryNode<string>* node);
string promptKey();
string getFileName();
Car* addCar();

int main() {
	// Building hash table and bst
	HeadNode headNode;

	fillList(headNode);
	// transfer data file to hash and bst


	// Start User Menu
	int choice;
	cout << "Welcome to findMyCar\n";
	cout << "\"We find your car in record braking time!\"\n";
	do {
		// Menu Prompt
		cout << "(1). Add new data\n"
			<< "(2). Delete data\n"
			<< "(3). Find and display one data record using the primary key\n"
			<< "(4). List data in hash table sequence\n"
			<< "(5). List data in key sequence\n"
			<< "(6). Print indented tree\n"
			<< "(7). Efficiency\n"
			<< "(8). Find a Car For You\n"
			<< "(9). Quit\n";
		cin >> choice;
		switch (choice) {
			// Add new data
		case 1: {
			Car* newCar = addCar();
			if (headNode.contains(newCar->getModelName())) {
			cout << newCar->getModelName() << " is already in the database" << endl;
		}
			else{
			headNode.add(newCar);
			}
			break;
		}
		// Delete data
		case 2: {
			string key = promptKey();
			if (!headNode.contains(key)) {
				cout << "Error " <<key << " " << " is not in the database" << endl;
			}
			else {
				headNode.del(key);
			}
			break;
		}
				// Find and display one data record using the primary key
		case 3: {
			string key = promptKey();
			if (!headNode.contains(key)) {
				cout << "Error " << key << " " << " is not in the database" << endl;
			}
			else {
				Car* car = headNode.retrieve(key);
				cout << (*car);
			}
			break;
		}
				// List data in hash table sequence
		case 4: {
			// call list data in hash (traverseHash) (printCar)
			//headNode.getHash()->traverse();
			break;
		}
				// List data in key sequence (sorted)
		case 5: {
			headNode.getBST()->inOrderTraverse(printCar);
			break;
		}
				// Print indented tree
		case 6: {
			headNode.getBST()->printIndented();
			cout << endl;
			break;
		}
				// Efficiency
		case 7: {
			headNode.getEfficiency();
			break;
		}
				// Find a Car For You
		case 8: {
			headNode.findMyCar();
		}
		case 9: {
			cout << "goodbye\n";
			break;
		}
		default: cout << "Please select a value between 1-9\n";
			// Quit
		}
	} while (choice != 9);
	// Choose file location to save data

	// Destroy bst and hash tables

	// End message

	return 0;
}

/*
*/
Car* addCar() {
	std::string make;
	std::string model;
	double price;
	double mpg;
	double hp;
	string garbage;

	std::cout << "Enter the vehicles information: \n"
			  << "\nMake: "; cin >> make;
	std::cout << "\nModel: "; cin >> model;
	std::cout << "\nPrice: "; cin >> price;
	std::cout << "\nMPG: "; cin >> mpg;
	std::cout << "\nHorsepower: "; cin >> hp;

	Car* c = new Car(model, mpg,price, hp, make);
	return c;
}


/*
Pre: List<Car> &headList - list to store the cars
Post opens file named database.txt and reads in car data
	 Fills the list which each car
Return:
*/
void fillList(HeadNode & headNode) {
	ifstream file;
	string make; 
	string model;
	string garbage;
	double mpg;
	double price;
	double hp;
	file.open("database.txt");

	while (file >> make) {
		file >> model;
		getline(file, garbage);
		file >> mpg;
		getline(file, garbage);
		file >> price;
		getline(file, garbage);
		file >> hp;
		getline(file, garbage);

		Car* car = new Car(model, mpg, price, hp, make);
		headNode.add(car);
	}

}


/*
Pre: BinaryNode<string>* node - node to be printed
Post: prints the car that is stored in the node
Return:
*/
void printCar(BinaryNode<string>* node) {
	Car* c = node->getCar();
	cout << (*c) << endl;
}

void writeCar(BinaryNode<string>* node) {
	// object to write in file
	std::ofstream oFile;
	Car* c = node->getCar();

	// opening file to write
	oFile.open(fileName.c_str());
	oFile << c->getMake() << " " << c->getModelName() << std::endl
		<< c->getMpg() << " mpg" << std::endl
		<< c->getAvgPrice() << " dollars" << std::endl
		<< c->getHorsePower() << " hp" << std::endl;
	oFile.close();
}

/*
Pre : 
Post: Prompts user to input a string
Return string prompt - key for finding a car
*/
std::string promptKey()
{
	std::string prompt;
	std::cout << "Enter the model of the car you wish to find: \n";
	std::cin >> prompt;

	return prompt;
}

string getFileName() {
	cout << "\nEnter the file name / directory of where you would like to save the database:\n";
	string fileName;
	cin >> fileName;
	return fileName;
}

