
#pragma once
#include <string>

template<typename T>
class HashNode {
private:
	T data;							// data to be stored
	std::string identity;			// unique identifier
	HashNode *nextNode;
public:
	// default constructor
	HashNode() {
		this->data = ' ';
		this->identity = " ";
		this->nextNode = nullptr;
	}

	// constructor
	HashNode(std::string key, T value) {
		this->data = value;
		this->identity = key;
		this->nextNode = nullptr;
	}

	void setNode(std::string key, T item) {
		data = item;
		identity = key;
	}

	void setNext(HashNode *next) {
		this->nextNode = next;
	}
	T getData() {
		return data;
	}
	std::string getIdentity() {
		return identity;
	}
	HashNode *getNext() {
		return nextNode;
	}
};

template<typename T>
class HashTable {
private:
	HashNode<T> **arr;			// hash array
	int maxSize;				// max size
	int currSize;				// size of array
	int loadFactor;

	int hashFunc(std::string key) {
		int total = 0;
		for (unsigned int i = 0; i < key.length(); i++)
			total += static_cast<int>(key[i]);
		return total % maxSize;
	}
public:
	// constructor
	HashTable();
	~HashTable();
	// setters and getters
	int getCurrSize() {
		return currSize;
	}

	int getMaxSize() {
		return maxSize;
	}

	double getLoadFactor() {
		return (double)loadFactor / (double)currSize;
	}

	int getLongestLinkList();

	double getAverageLinkList();

	bool isEmpty() {
		return (currSize == 0);
	}

	void insert(std::string key, T value);

	void remove(std::string key);

	void clear();

	T retrieve(std::string key);

	bool contains(std::string key);

	void traverse(void(*func)(HashNode<T>*)) const;
};

template<typename T>
HashTable<T>::HashTable()
{
	// create array
	maxSize = 50;
	currSize = 0;
	loadFactor = 0;
	arr = new HashNode<T>*[maxSize];

	for (int i = 0; i < maxSize; i++)
		arr[i] = NULL;
}

template<typename T>
HashTable<T>::~HashTable()
{
	clear();
	delete[] arr;
}

/*
Adds a data entry to the hash table
Pre: string key - search key, T value - data item
Post: Adds the entry to the hash table
Return: Nothing
*/
template<typename T>
void HashTable<T>::insert(std::string key, T value)
{
	int i = hashFunc(key);				// find index location
	if (arr[i] == NULL) {
		arr[i] = new HashNode<T>(key, value);
		loadFactor++;
	}
	else {
		HashNode<T>* temp = arr[i];			// set pointer to array index
		while (temp != nullptr) {
			temp = temp->getNext();			// goes to end of list for the index
		}
		if (temp->getIdentity() == key) {
			temp->setNode(key, value);		// if
		}
		else {
			temp->setNext(new HashNode<T>(key, value));
		}
	}
	currSize++;
}

/*
Removes all entries from the hash table
Pre: None
Post: All entries are deleted
Return: Nothing
*/
template<typename T>
void HashTable<T>::clear()
{
	for (int i = 0; i < maxSize; i++) {
		if (arr[i] != NULL) {
			HashNode<T>* prevNode = NULL;
			HashNode<T>* node = arr[i];
			while (node != NULL) {
				prevNode = node;
				node = node->getNext();
				delete prevNode;
			}
		}
	}
}

/*
Gets a value from a search key
Pre: string key - search key
Post: Data is taken from the hash table using the key
Return: T Data
*/
template<typename T>
T HashTable<T>::retrieve(std::string key) {
	// finding the index using the hash function
	int index = hashFunc(key);
	if (arr[index] == NULL) {
		//T temp;
		//return temp;
		return nullptr;
	}
	else {
		HashNode<T>* node = arr[index];
		while (node != NULL && node->getIdentity() != key)
			node = node->getNext();
		if (arr[index]->getIdentity() == key) {
			return node->getData();
		}
		else {
			//T temp;
			//return temp;
			return nullptr;
		}
	}
}

/*
Checks if there is a data value associated with the key
Pre: string key - search key
Post: returns a bool
Return: true if found, otherwise false
*/
template<typename T>
bool HashTable<T>::contains(std::string key)
{
	int index = hashFunc(key);
	if (arr[index] == NULL) {
		return false;
	}
	else {
		HashNode<T>* node = arr[index];
		while (node != NULL && node->getIdentity() != key)
			node = node->getNext();
		if (arr[index]->getIdentity() == key) {
			return true;
		}
		else {
			return false;
		}
	}
}


