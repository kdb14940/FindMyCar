#pragma once
#include "Node.h"


template <typename T>
class List
{
private:
	int count;				// This integer tracks the size of the linked list
	Node<T> *head;			// A pointer pointing to the first node.
	//Node<T> *tail;		// Points to last node
	//isEmpty();			// Checks if head points to nullptr
public:
	List()					// Default constructor. Initialized head pointer to nullptr.
	{
		head = nullptr;
		//tail = nullptr;
	}

	virtual ~List();					// Destructor - Deletes every node

	void addFirst(T data);				// Adds a node to the front of the list

	void addLast(T data);				// Adds a node to the back of the list

	void addAnywhere(T data, int pos);	// Adds a node to a specified location of the list

	void delFirst();					// Deletes the first node of the list

	void delLast();						// Deletes the last node of the list

	void delAnywhere(int pos);			// Deletes a node at a specified location

	T findData(int pos);					// Goes to a position in a list
	T* findDataPtr(int pos);

	int findPos(T data);

	int getCount()						// Returns the amount of nodes in the list
	{
		return count;
	}
	void emptyAll();					// Deletes every node in the list?

	// void newList();
};

// Destructor - Deletes every node in the linked list
template<typename T>
List<T>::~List()
{
	emptyAll();
}

/*
Adds a node to the front of the list.
Pre: T data - Value that the new node will carry.
Post : A node will be added at the front of the list
moving every other node back by one.
Return :
*/
template<typename T>
void List<T>::addFirst(T data)
{
	Node<T> *newNode;	// Pointer to new node
	Node<T> *ptr;		// To move through list

	newNode = new Node<T>(data);	// Allocates a new node

	if (!head)						// If there are no node, make this first node
	{
		head = newNode;
	}
	else							// Otherwise, put insert node at beginning
	{
		ptr = head;					// Initialize ptr to head

		head = newNode;				// Set head to this new node

		newNode->setNext(ptr);		//new node points to second node
	}
	count++;
}

/*
Adds a node to the back of the list.
Pre: T data - Value that the new node will carry.
Post: A node will be added at the back of the list.
Return:
*/
template<typename T>
void List<T>::addLast(T data)
{
	if (count == 0) {
		addFirst(data);
		return;
	}
	Node<T> *newNode;		// Pointer to new node
	Node<T> *ptr;			// To move through list

	newNode = new Node<T>(data);	// Allocates a new node

	if (!head)						// If there are no nodes, make this first node
	{
		head = newNode;
	}
	else							// Otherwise, put node at the end
	{
		ptr = head;					// Initialize ptr to head

		while (ptr->getNext())			// Find the last node
			ptr = ptr->getNext();

		ptr->setNext(newNode);		// set newNode as last node
	}
	count++;
}

/*
Adds a node to a user-defined location.
Pre: T data - Value that the new node will carry
	 int pos - The location of the node.
Post: A node will be added at a user-defined location.
Return:
*/
template<typename T>
void List<T>::addAnywhere(T data, int pos)
{
	if (pos > count || pos < 0)
	{
		std::cout << "Error: position is out of bounds\n";
		return;
	}
	if (pos == 0) {
		addFirst(data);
		return;
	}
	if (pos == count - 1) {
		addLast(data);
		return;
	}

	Node<T> *newNode;		// Pointer to new node
	Node<T> *ptr;			// To move through list
	Node<T> *next;

	newNode = new Node<T>(data);	// Allocates a new node
	ptr = head;						//ptr points to pos 0

	for (int i = 0; i < pos - 1; i++)
	{
		ptr = ptr->getNext(); // set ptr to pos -1 
	}
	next = ptr->getNext();			//sets next to what is currently at pos
	ptr->setNext(newNode);			//inserts new node after pos-1
	newNode->setNext(next);			//points new Node to pos+1

	count++;
}

/*
Deletes the first node in the list.
Pre:
Post: The front node will be deleted.
Return:
*/
template<typename T>
void List<T>::delFirst()
{
	Node<T> *ptr;						// To move through list
	Node<T> *nextNode = nullptr;		// To point to next node

	ptr = head;							// Sets ptr to head of list

	nextNode = ptr->getNext();			// Saves pointer to next node

	delete ptr;							// Deletes current node

	head = nextNode;					// Sets ptr to next node
	count--;
}

/*
Deletes the last node in the list.
Pre:
Post: The back node will be deleted.
Return:
*/
template<typename T>
void List<T>::delLast()
{
	Node<T> *ptr;						// To move through list
	Node<T> *lastNode = nullptr;		// To point to last node

	ptr = head;							// Sets ptr to head of list

	while (ptr->getNext()) {			// Find the last node
		lastNode = ptr;					//Set previous node to ptr
		ptr = ptr->getNext();			// set ptr to next node
	}

	delete ptr;							// Deletes last node
	lastNode->setNext(nullptr);			// Sets previous node ptr to null 
										// to mark new end	
	count--;
}

/*
Deletes a node at a user-defined position.
Pre: int pos - The location of the node.
Post: A node at location pos will be deleted.
Return:
*/
template<typename T>
void List<T>::delAnywhere(int pos)
{
	if (pos > count || pos < 0)
	{
		std::cout << "Error: position is out of bounds\n";
		return;
	}
	if (pos == 0) {
		delFirst();
		return;
	}
	if (pos == count - 1) {
		delLast();
		return;
	}


	Node<T> *ptr;						// To move through list
	Node<T> *nextNode = nullptr;		// To point to next node
	Node<T> *prevNode;

	prevNode = head;

	for (int i = 0; i < pos - 1; i++)
	{
		prevNode = prevNode->getNext();			//set prevNode to pos - 1
	}
	ptr = prevNode->getNext();			// sets ptr to current node to be deleted
	nextNode = ptr->getNext();			// sets next node

	delete ptr;							// Deletes current node

	prevNode->setNext(nextNode);				// Sets previous to next
	count--;
}


//Position starts at 0
/*
This function returns the data of the node.
Pre: int pos - The location of the node
Post:
Return: The value of the T data type
*/
template<typename T>
T List<T>::findData(int pos)
{
	Node<T>* ptr;
	ptr = head;
	for (int i = 0; i < pos; i++)
	{
		ptr = ptr->getNext();
	}
	return ptr->getData();
}

//Position starts at 0
/*
This function returns the data of the node.
Pre: int pos - The location of the node
Post:
Return: The value of the T data type
*/
template<typename T>
T* List<T>::findDataPtr(int pos)
{
	Node<T>* ptr;
	T* dataPtr;
	ptr = head;
	for (int i = 0; i < pos-1; i++)
	{
		ptr = ptr->getNext();
	}
	dataPtr = &ptr->getData();
		return dataPtr;
}

/*

*/
template <typename T>
int List<T>::findPos(T data)
{
	Node<T> *ptr;						// To move through list
	ptr = head;							// Sets ptr to head of list
	int index = 0;

	if (ptr->getData() == data)			//check if first element is match
		return index;

	while (ptr->getNext()) {
		ptr = ptr->getNext();			//set ptr to next
		index++;
		if (ptr->getData() == data)
			return 	index;
	}
	return -1;							//data not found
}

/*
Deletes the whole list.
Pre:
Post: Deletes every node in the list.
Return:
*/
template<typename T>
void List<T>::emptyAll()
{
	Node<T> *ptr;			// To move through list
	Node<T> *nextNode = nullptr;		// To point to next node

	ptr = head;			// Sets ptr to head of list

	while (ptr != nullptr)	// Goes through linked list deleting every node
	{
		nextNode = ptr->getNext();	// Saves pointer to next node or nullptr if last node

		delete ptr;				// Deletes current node

		ptr = nextNode;			// Sets ptr to next node
	}
	count = 0;
	head = nullptr;
}