#include "HeadNode.h"

HeadNode::HeadNode() {
	bstPtr = new BST<std::string>();
	hashPtr = new HashTable<Car*>();
	int count = 0;
	int arrSize = 0;
}

/*
Pre:
Post: Destroys the BST and the HashTable
Return:
*/
void HeadNode::freeLists() {
	bstPtr->destroyBST();
	//hashDestroy
	delete bstPtr;
	delete hashPtr;
}

/*
Pre: Car* c - ptr to car that will be inserted
Post: adds the Car to the BST and the HashTable
Return:
*/
void HeadNode::add(Car* c) {
	BinaryNode<std::string>* node = new BinaryNode<std::string>(c, c->getModelName());
	bstPtr->insert(node);
	hashPtr->insert(c->getModelName(), c);
	count++;
}

/*
Pre: string key - key of the car to be removed from the BST and HashTable
Post: Removes the intended car from the  BST and HashTable
Return:
*/
void HeadNode::del(std::string key) {
	bstPtr->remove(key);
	//hashPtr->remove(key);

}

/*
Pre:
Post: Prints efficiency data from BST and HashTable
Return:
*/
void HeadNode::getEfficiency() {
	std::cout << "Efficiency for BST:\n"
			<< "Total Insert Comparisons : " << bstPtr->getTotalInsert() << std::endl
			<< "Average Insert Comparisons : " << bstPtr->getAverageInsert() << std::endl
			<< "Total Delete Comparisons : " << bstPtr->getTotalDel() << std::endl
			<< "Average Delete Comparisons : " << bstPtr->getAverageDel() << std::endl;
}

/*
Pre: string key - key of the car searched for
Post: checks to see if the car is in the HashTable
Return: bool - true if the HashTable contains the intended car
*/
bool HeadNode::contains(std::string key) {
	return hashPtr->contains(key);
	return false;
}

/*
Pre: string key- key of the car to be removed
Post: Retrieves the intended car from the HashTable
Return: Car* car - car retrieved
*/
Car* HeadNode::retrieve(std::string key) {
	return hashPtr->retrieve(key);
	return nullptr;
}

/*
Pre: 
Post: Creates a new BSt to sort by doubles
	  Creates a list to store the data from BST
	  Creates two lists to hold BinaryNode<double>*
	  Asks user for what attribute to sort by
	  Fills the new BST and sorts it by the attribute chosen
	  Prints out the sorted BST
	  Asks user if they would like to sort again
		if so, calls sortSecondAttribute
Return:
*/
void HeadNode::findMyCar() {
	int choice1;
	BST<double>* nonKeyBST = new BST<double>();
	List<BinaryNode<std::string>*>* keyList = new List<BinaryNode<std::string >*> ();
	List<BinaryNode<double>*>* nonKeyList = new List<BinaryNode<double>*>();
	List<BinaryNode<double>*>* nonKeyListShort = new List<BinaryNode<double>*>();
	char cont;

	bstPtr->inOrderTraverse(keyList); // fill keyList with each Car in BST

	std::cout << "Let's find the best car for you!\n"
		<< "Please choose the most important aspect for you:\n"
		<< "1. MPG\n"
		<< "2. Price\n"
		<< "3. Power\n";
	std::cin >> choice1;

	switch (choice1)
	{
	case 1:
		// fill nonKeyBST with nodes sorted by MPG
		for (int i = 0; i < keyList->getCount(); i++) {
			Car* tempCar = keyList->findData(i)->getCar();
			BinaryNode<double>* tempNode = new BinaryNode<double>(tempCar, tempCar->getMpg());
			nonKeyBST->insert(tempNode);
		}
		nonKeyBST->inOrderTraverse(nonKeyList);
		std::cout << "Here are the top 10 cars sorted by mpg\n";
		for (int i = nonKeyList->getCount() - 1; i > nonKeyList->getCount() - 11; i--) {
			Car* tempCar = nonKeyList->findData(i)->getCar();
			BinaryNode<double>* tempNode = new BinaryNode<double>(tempCar, tempCar->getMpg());
			nonKeyListShort->addLast(tempNode);
			//cout << tempCar->getMake() << " " << tempCar->getModelName()
				//<< ": " << tempCar->getMpg() << " mpg" << endl;
			std::cout << (*tempCar);
		}
		std::cout << "Would you like to narrow the list down using another attribute?(y/n) ";
		std::cin >> cont;
		if (cont == 'y' || cont == 'Y') {
			sortSecondAttribute(nonKeyListShort);
		}

		break;
	case 2:
		// fill nonKeyBST with nodes sorted by price
		for (int i = 0; i < keyList->getCount(); i++) {
			Car* tempCar = keyList->findData(i)->getCar();
			BinaryNode<double>* tempNode = new BinaryNode<double>(tempCar, tempCar->getAvgPrice());
			nonKeyBST->insert(tempNode);
		}
		nonKeyBST->inOrderTraverse(nonKeyList);
		std::cout << "Here are the top 10 cars sorted by price\n";
		for (int i = 0; i < 10; i++) {
			Car* tempCar = nonKeyList->findData(i)->getCar();
			BinaryNode<double>* tempNode = new BinaryNode<double>(tempCar, tempCar->getAvgPrice());
			nonKeyListShort->addLast(tempNode);
			//cout << tempCar->getMake() << " " << tempCar->getModelName()
				//<< ": " << tempCar->getMpg() << " mpg" << endl;
			std::cout << (*tempCar);
		}
		std::cout << "Would you like to narrow the list down using another attribute?(y/n) ";
		std::cin >> cont;
		if (cont == 'y' || cont == 'Y') {
			sortSecondAttribute(nonKeyListShort);
		}
		
		break;
	case 3:
		// fill nonKeyBST with nodes sorted by HP
		for (int i = 0; i < keyList->getCount(); i++) {
			Car* tempCar = keyList->findData(i)->getCar();
			BinaryNode<double>* tempNode = new BinaryNode<double>(tempCar, tempCar->getHorsePower());
			nonKeyBST->insert(tempNode);
		}
		nonKeyBST->inOrderTraverse(nonKeyList);
		std::cout << "Here are the top 10 cars sorted by horse power\n";
		for (int i = nonKeyList->getCount() - 1; i > nonKeyList->getCount() - 11; i--) {
			Car* tempCar = nonKeyList->findData(i)->getCar();
			BinaryNode<double>* tempNode = new BinaryNode<double>(tempCar, tempCar->getHorsePower());
			nonKeyListShort->addLast(tempNode);
			//cout << tempCar->getMake() << " " << tempCar->getModelName()
				//<< ": " << tempCar->getMpg() << " mpg" << endl;
			std::cout << (*tempCar);
		}
		std::cout << "Would you like to narrow the list down using another attribute?(y/n) ";
		std::cin >> cont;
		if (cont == 'y' || cont == 'Y') {
			sortSecondAttribute(nonKeyListShort);
		}
		break;
	default:
		std::cout << "INVALID ENTRY. PLEASE TRY AGAIN\n";
	}
}

/*
Pre: List<BinaryNode<double>*> list - shortened list to sort by new attribute
Post: Asks the user for which attribute they would like to sort by
	  Creates a new BST and fills it from the list
	  Sorts the BST depending on which attribute is chosen
	  Prints out the sorted BST
*/
void HeadNode::sortSecondAttribute(List<BinaryNode<double>*>* list) {
	int choice1;
	BST<double>* nonKeyBST = new BST<double>();
	List<BinaryNode<double>*>* nonKeyList = new List<BinaryNode<double>*>();
	std::cout
		<< "Please choose the second most important aspect for you:\n"
		<< "1. MPG\n"
		<< "2. Price\n"
		<< "3. Power\n";
	std::cin >> choice1;

	switch (choice1)
	{

	case 1:
		for (int i = 0; i < list->getCount(); i++) {
			Car* tempCar = list->findData(i)->getCar();
			BinaryNode<double>* tempNode = new BinaryNode<double>(tempCar, tempCar->getMpg());
			nonKeyBST->insert(tempNode);
		}
		nonKeyBST->inOrderTraverse(nonKeyList);
		std::cout << "Here are the cars sorted by mpg\n";
		for (int i = nonKeyList->getCount() - 1; i >= 0; i--) {
			Car* tempCar = nonKeyList->findData(i)->getCar();
			std::cout << (*tempCar);
		}
		break;

	case 2:
		for (int i = 0; i < list->getCount(); i++) {
			Car* tempCar = list->findData(i)->getCar();
			BinaryNode<double>* tempNode = new BinaryNode<double>(tempCar, tempCar->getAvgPrice());
			nonKeyBST->insert(tempNode);
		}
		nonKeyBST->inOrderTraverse(nonKeyList);
		std::cout << "Here are the cars sorted by price\n";
		for (int i = 0; i < 10; i++) {
			Car* tempCar = nonKeyList->findData(i)->getCar();
			std::cout << (*tempCar);
		}
		break;
	case 3:
		for (int i = 0; i < list->getCount(); i++) {
			Car* tempCar = list->findData(i)->getCar();
			BinaryNode<double>* tempNode = new BinaryNode<double>(tempCar, tempCar->getHorsePower());
			nonKeyBST->insert(tempNode);
		}
		nonKeyBST->inOrderTraverse(nonKeyList);
		std::cout << "Here are the cars sorted by horse power\n";
		for (int i = nonKeyList->getCount() - 1; i >= 0; i--) {
			Car* tempCar = nonKeyList->findData(i)->getCar();
			std::cout << (*tempCar);
		}
		break;
	default:
		std::cout << "INVALID ENTRY. PLEASE TRY AGAIN\n";
	}
}