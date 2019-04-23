#pragma once

#include "Node.h"
#include "Car.h"


template <typename T>
class BinaryNode : private Node<T>{
private: 
	Car* car;		//pointer to Car
	T key;			//key to be sorted
	BinaryNode<T>* lPtr;
	BinaryNode<T>* rPtr;
public:
	BinaryNode();
	BinaryNode(Car* c, T k);
	BinaryNode(Car* c, T k, BinaryNode<T>* l_ptr, BinaryNode<T>* r_ptr);

	void setCar(Car* c) { car = c; }
	void setKey(T k) { key = k; }
	void setLPtr(BinaryNode<T>* l_ptr) { lPtr = l_ptr; }
	void setRPtr(BinaryNode<T>* r_ptr) { rPtr = r_ptr; }
	bool hasLeft() { return lPtr; }
	bool hasRight() { return rPtr; }

	Car* getCar() { return car; }
	T getKey() { return key; }
	BinaryNode<T>* getLPtr(){ return lPtr; }
	BinaryNode<T>* getRPtr(){ return rPtr; }

	bool isLeaf();

};

template <typename T>
BinaryNode<T>::BinaryNode() : Node<T>() {
	car = nullptr;
	key = 0;
	lPtr = nullptr;
	rPtr = nullptr;
}

template <typename T>
BinaryNode<T>::BinaryNode(Car* c, T k) : Node<T>() {
	car = c;
	key = k;
	lPtr = nullptr;
	rPtr = nullptr;
}

template <typename T>
BinaryNode<T>::BinaryNode(Car* c, T k, BinaryNode<T>* l_ptr, BinaryNode<T>* r_ptr) : Node<T>() {
	car = c;
	key = k;
	lPtr = l_ptr;
	rPtr = r_ptr;
}

/*
Pre:
Post:Checks to see if a node is a leaf
Return true - if it is a leaf
	   false - if it is not a leaf
*/
template <typename T>
bool BinaryNode<T>::isLeaf() {
	if (lPtr == nullptr && rPtr == nullptr)
		return true;
	return false;
}