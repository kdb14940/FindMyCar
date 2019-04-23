#pragma once

#include "BST.h"
#include "Hash.h"
#include "List.h"
#include <iostream>
#include <fstream>

class HeadNode {
private:
	BST<std::string>* bstPtr;
	HashTable<Car*>* hashPtr;	
	int arrSize;
	int count;

public:
	HeadNode();

	BST<std::string>* getBST() { return bstPtr; }
	HashTable<Car*>* getHash() { return hashPtr; }
	int getCount() { return count; }
	void freeLists();

	bool contains(std::string key);
	void add(Car* c);
	void del(std::string key);
	Car* retrieve(std::string key);
	void getEfficiency();
	void findMyCar();
	void sortSecondAttribute(List<BinaryNode<double>*>* list);

	//void fillLists(std::string fileName);
};