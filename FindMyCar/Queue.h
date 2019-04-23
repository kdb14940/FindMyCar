#pragma once
#include "List.h"
#include "Node.h"

template <typename T>
class Queue : protected List<T> {
public:
	// Constructor
	Queue() : List<T>() {}

	// Destructor
	~Queue() {
		this->emptyAll();								// Destroys queue
	}

	void enqueue(T data) {
		this->addLast(data);							// Adds a value of T data type to the back of the queue
	}

	T dequeue() {
		T data = this->findData(0);						// deletes and returns the value of the first node
		this->delFirst();
		return data;
	}

	T front() {
		return this->findData(0);						// Returns the value of the first node
	}

	T rear(){
		return this->findData(queueCount() - 1);		// Returns the value of the last node
	}

	int queueCount() {
		return this->getCount();						// Returns the number of nodes in the queue
	}

	void destroyQueue() {
		this->emptyAll();								// Empties the queue
	}

	bool isEmpty() {
		if (queueCount() > 0)							// Checks if the queue is empty
			return false;
		return true;
	}
};