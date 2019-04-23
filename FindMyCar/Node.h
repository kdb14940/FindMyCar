#pragma once


template <typename T>

class Node
{
protected:
	T data;
	Node<T>* pNext;
public:	
	Node() {
		pNext = nullptr;
	}
	Node(T dataIn, Node<T>* ptrIn) {
		data = dataIn;
		pNext = ptrIn;
	}
	Node(T dataIn) : data(dataIn) {
		pNext = nullptr;
	}
	
	void setData(T dataIn) {
		data = dataIn;
	}
	void setNext(Node<T>* ptrIn) {
		pNext = ptrIn;
	}
	T getData() {
		return data;
	}
	Node<T>* getNext() {
		return pNext;
	}
};
