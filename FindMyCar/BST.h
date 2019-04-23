#pragma once

#include "Queue.h"
#include "BinaryNode.h"
#include <iostream>



template <typename T>
class BST{
private:
	BinaryNode<T>* root;
	int insertComparisons = 0;
	int delComparisons = 0;
	int averageInsertComparisons = 0;
	int averageDelComparisons = 0;
	int totalInsertComparisons = 0;
	int totalDelComparisons = 0;

	void insertHelper(BinaryNode<T>* data, BinaryNode<T>* r);
	//file output traverse
	void inOrderHelper(BinaryNode<T>* r, void(*func)(BinaryNode<T>*, std::string), std::string fileName);
	void postOrderHelper(BinaryNode<T>* r, void(*func)(BinaryNode<T>*, std::string), std::string fileName);
	void preOrderHelper(BinaryNode<T>* r, void(*func)(BinaryNode<T>*, std::string), std::string fileName);
	//standard output traverse
	void inOrderHelper(BinaryNode<T>* r, void(*func)(BinaryNode<T>*));
	void postOrderHelper(BinaryNode<T>* r, void(*func)(BinaryNode<T>*));
	void preOrderHelper(BinaryNode<T>* r, void(*func)(BinaryNode<T>*));
	//fillNodeArr traverse
	void inOrderHelper(BinaryNode<T>* r, List<BinaryNode<T>*>* list);

	void updateAverageInsert();
	void updateAverageDeletion();

	int getNumberOfNodesHelper(BinaryNode<T>* r);
	void removeSubTree(BinaryNode<T>* r);
	void removeHelper(T key, BinaryNode<T>* parent);
	void removeRoot();
	void removeNodeHelper(BinaryNode<T>* parent, BinaryNode<T>* del, bool isLeft);
	T findSmallestHelper(BinaryNode<T>* r);
	void printIndentedHelper(BinaryNode<T>* r, int spacing, int defaultSpacing);

public:
	BST();
	BST(BinaryNode<T>* r) { root = r; }
	~BST();
	//getters
	int getAverageInsert() { return averageInsertComparisons; }
	int getAverageDel() { return averageDelComparisons; }
	int getTotalInsert() { return totalInsertComparisons; }
	int getTotalDel() { return totalDelComparisons;  }
	BinaryNode<T>* getRoot() { return root; }
	int getNumberOfNodes();

	bool isEmpty() { return !root; }
	void destroyBST();
	void insert(BinaryNode<T>* data);
	//fileoutputtraverse
	void inOrderTraverse(void (*func)(BinaryNode<T>*, std::string), std::string fileName);
	void postOrderTraverse(void(*func)(BinaryNode<T>*, std::string), std::string fileName);
	void preOrderTraverse(void(*func)(BinaryNode<T>*, std::string), std::string fileName);
	void breadthFirstTraverse(void(*func)(BinaryNode<T>*, std::string), std::string fileName);
	//standard output traverse
	void inOrderTraverse(void(*func)(BinaryNode<T>*));
	void postOrderTraverse(void(*func)(BinaryNode<T>*));
	void preOrderTraverse(void(*func)(BinaryNode<T>*));
	void breadthFirstTraverse(void(*func)(BinaryNode<T>*));
	//fillNodeArr traverse
	void inOrderTraverse(List<BinaryNode<T>*>* list);


	void remove(T key);
	void printIndented();
	T findSmallest();
};


/*
Default Constructor
*/
template <typename T>
BST<T>::BST() {
	root = nullptr;
}

/*
Default destructor
Calls removeSubTree starting with the root node
*/
template <typename T>
BST<T>::~BST() {
	removeSubTree(root);
}

/*
Pre:
Post: calls removeSubTree starting with the root node
Return:
*/
template<typename T>
void BST<T>::destroyBST() {
	removeSubTree(root);
}

/*
Pre : BinaryNode<T>* r - root of subtree to be removed
Post: Recursively loops down the left subtree and the right subtree
	  and delete each node
Return:
*/
template <typename T>
void BST<T>::removeSubTree(BinaryNode<T>* r) {
	if (r != nullptr) {
		if (r->hasLeft()) {
			removeSubTree(r->getLPtr());
		}
		if (r->hasRight()) {
			removeSubTree(r->getRPtr());
		}
	}
}

/*
Pre:
Post: Checks if the Tree is empty
	  Otherwise, calls getNumberOfNodesHelper(root)
Return: int count - total number of nodes
*/
template <typename T>
int BST<T>::getNumberOfNodes() {
	int count = 0;
	if (isEmpty())
		return count;
	count = getNumberOfNodesHelper(root);
	return count;
}

/*
Pre: BinaryNode<T>* r - root of the subtree to be counted
Post: Recursively loops through the tree and increments count for each node found
Return count - total number of nodes counted
*/
template <typename T>
int BST<T>::getNumberOfNodesHelper(BinaryNode<T>* r) {
	int count = 1;
	if (r->hasLeft()) {
		count += getNumberOfNodesHelper(r->getLPtr());
	}
	if (r->hasRight()) {
		count += getNumberOfNodesHelper(r->getRPtr());
	}
	return count;
}

/*
Public function to insert a node into Tree
Calls insertHelper
*/
template <typename T>
void BST<T>::insert(BinaryNode<T>* data) {
	insertHelper(data, root);
	updateAverageInsert();
}

/*
Pre: BinaryNode<T>* data node to be added
	 BinaryNode<T>* r root node
	 int attributeChoice chooses which of the attributes in Node to sort by
Post:Checks whether the first attirbute or the second attribute is to be sorted
	 Recursively loops to either the left or right subtree depending on
	 whether the data is < or > the root
	 If the subtree points to a nullptr - place data there
Return
*/
template <typename T>
void BST<T>::insertHelper(BinaryNode<T>* data, BinaryNode<T>* r) {
	if (isEmpty()) {
		root = data;
		insertComparisons -= 2; // default is 4, but this case only has 2
	}
	//compares first attribute
	else{
		if (data->getKey() < r->getKey()) {
			if (r->hasLeft()) {
				insertHelper(data, r->getLPtr());		//recursive call using Lptr as root
			}
			else {
				r->setLPtr(data);										//sets Lptr if it currently
			}															//points to null
		}
		else if (data->getKey() > r->getKey()) {
			if (r->hasRight()) {
				insertHelper(data, r->getRPtr());		//recursive call using Rptr as root
			}
			else {
				r->setRPtr(data);									//sets Rptr if it currently
			}															//points to null

		}
		else {
			std::cout << "Error " << data->getKey() << " has already been added to the tree\n";
		}
		insertComparisons += 4; // 4 comparisons per pass
								// 3 if comparisons and one function call.
	}
	
}

/*
Public function that calls inOrderHelper
Pre: func - function to process each node
	 string fileName - name of the file for the process function
*/
template <typename T>
void BST<T>::inOrderTraverse(void(*func)(BinaryNode<T>*, std::string), std::string fileName) {
	inOrderHelper(root, func, fileName);
}

/*
Public function that calls inOrderHelper
Pre: func - function to process each node
*/
template <typename T>
void BST<T>::inOrderTraverse(void(*func)(BinaryNode<T>*)) {
	inOrderHelper(root, func);
}

/*
Public function that calls inOrderHelper
Pre: func - function to process each node
*/
template <typename T>
void BST<T>::inOrderTraverse(List<BinaryNode<T>*>* list){
	return inOrderHelper(root, list);
}

/*
Pre: BinaryNode<T>* r - root of the subtree
	 func - function to process each node
	 string fileName - name of the file for the process function
Post: recursievly loops through the tree using a left - root - right algorithm
*/
template <typename T>
void BST<T>::inOrderHelper(BinaryNode<T>* r, void(*func)(BinaryNode<T>*, std::string), std::string fileName) {
	if (!isEmpty()) {
		if (r->hasLeft()) {
			inOrderHelper(r->getLPtr(), func, fileName);
		}
		func(r, fileName);					//outputs to the Birthdays file
		if (r->hasRight()) {
			inOrderHelper(r->getRPtr(), func, fileName);
		}
	}
	else {
		std::cout << "Error Tree is Empty\n";
	}
}

/*
Pre: BinaryNode<T>* r - root of the subtree
	 func - function to process each node
Post: recursievly loops through the tree using a left - root - right algorithm
*/
template <typename T>
void BST<T>::inOrderHelper(BinaryNode<T>* r, void(*func)(BinaryNode<T>*)) {
	if (!isEmpty()) {
		if (r->hasLeft()) {
			inOrderHelper(r->getLPtr(), func);
		}
		func(r);					//outputs to the Birthdays file
		if (r->hasRight()) {
			inOrderHelper(r->getRPtr(), func);
		}
	}
	else {
		std::cout << "Error Tree is Empty\n";
	}
}

/*
Pre: BinaryNode<T>* r - root of the subtree
	 func - function to process each node
Post: recursievly loops through the tree using a left - root - right algorithm
*/
template <typename T>
void BST<T>::inOrderHelper(BinaryNode<T>* r, List<BinaryNode<T>*>* list) {
	if (!isEmpty()) {
		if (r->hasLeft()) {
			inOrderHelper(r->getLPtr(), list);
		}
		if (list->getCount() == 0)
			list->addFirst(r);
		else
			list->addLast(r);
		if (r->hasRight()) {
			inOrderHelper(r->getRPtr(), list);
		}
	}
	else {
		std::cout << "Error Tree is Empty\n";
	}
}

/*
Public function that calls postOrderHelper
Pre: func - function to process each node
	 string fileName - name of the file for the process function
*/
template <typename T>
void BST<T>::postOrderTraverse(void(*func)(BinaryNode<T>*, std::string), std::string fileName) {
	postOrderHelper(root, func, fileName);
}

/*
Public function that calls postOrderHelper
Pre: func - function to process each node
*/
template <typename T>
void BST<T>::postOrderTraverse(void(*func)(BinaryNode<T>*)) {
	postOrderHelper(root, func);
}

/*
Pre: BinaryNode<T>* r - root of the subtree
	 func - function to process each node
	 string fileName - name of the file for the process function
Post: Recursively loops through tree using a left - right - root algorith
Return :
*/
template <typename T>
void BST<T>::postOrderHelper(BinaryNode<T>* r, void(*func)(BinaryNode<T>*, std::string), std::string fileName) {
	if (!isEmpty()) {
		if (r->hasLeft()) {
			postOrderHelper(r->getLPtr(), func, fileName);
		}
		if (r->hasRight()) {
			postOrderHelper(r->getRPtr(), func, fileName);
		}
		func(r, fileName);						
	}
	else {
		std::cout << "Error Tree is Empty\n";
	}
}

/*
Pre: BinaryNode<T>* r - root of the subtree
	 func - function to process each node
	 string fileName - name of the file for the process function
Post: Recursively loops through tree using a left - right - root algorith
Return :
*/
template <typename T>
void BST<T>::postOrderHelper(BinaryNode<T>* r, void(*func)(BinaryNode<T>*)) {
	if (!isEmpty()) {
		if (r->hasLeft()) {
			postOrderHelper(r->getLPtr(), func);
		}
		if (r->hasRight()) {
			postOrderHelper(r->getRPtr(), func);
		}
		func(r);						
	}
	else {
		std::cout << "Error Tree is Empty\n";
	}
}


/*
public function that calls preOrderHelper
Pre: func - function to process each node
	 string fileName - name of the file for the process function
*/
template <typename T>
void BST<T>::preOrderTraverse(void(*func)(BinaryNode<T>*, std::string), std::string fileName) {
	preOrderHelper(root, func, fileName);
}

/*
public function that calls preOrderHelper
Pre: func - function to process each node
*/
template <typename T>
void BST<T>::preOrderTraverse(void(*func)(BinaryNode<T>*)) {
	preOrderHelper(root, func);
}



/*
Pre: BinaryNode<T>* r - root of a subtree
	 func - function to process each node
	 string fileName - name of the file for the process function
Post: Recursively loops using a root - left - right algorithm
Return:
*/
template <typename T>
void BST<T>::preOrderHelper(BinaryNode<T>* r, void(*func)(BinaryNode<T>*, std::string), std::string fileName) {
	if (!isEmpty()) {
		func(r, fileName);								
		if (r->hasLeft()) {
			preOrderHelper(r->getLPtr(), func, fileName);
		}
		if (r->hasRight()) {
			preOrderHelper(r->getRPtr(), func, fileName);
		}
	}
	else {
		std::cout << "Error Tree is Empty\n";
	}
}

/*
Pre: BinaryNode<T>* r - root of a subtree
	 func - function to process each node
Post: Recursively loops using a root - left - right algorithm
Return:
*/
template <typename T>
void BST<T>::preOrderHelper(BinaryNode<T>* r, void(*func)(BinaryNode<T>*)) {
	if (!isEmpty()) {
		func(r);								
		if (r->hasLeft()) {
			preOrderHelper(r->getLPtr(), func);
		}
		if (r->hasRight()) {
			preOrderHelper(r->getRPtr(), func);
		}
	}
	else {
		std::cout << "Error Tree is Empty\n";
	}
}




/*
Pre: func - function to process each node
	 string fileName - name of the file for the process function
Post: Does a breadth first traversal using a queue
Return :
*/

template <typename T>
void BST<T>::breadthFirstTraverse(void(*func)(BinaryNode<T>*, std::string), std::string fileName) {
	Queue<BinaryNode<T>*> queue = Queue<BinaryNode<T>*>();
	BinaryNode<T>* temp = root;
	if (isEmpty()) {
		std::cout << "Error Tree is empty\n";
		return;
	}
	queue.enqueue(root);
	while (!queue.isEmpty()) {
		temp = queue.dequeue();
		func(temp, fileName);
		if (temp->getLPtr()) {
			queue.enqueue(temp->getLPtr());
		}

		if (temp->getRPtr()) {
			queue.enqueue(temp->getRPtr());
		}
	}
	queue.destroyQueue();
}

/*
Pre: func - function to process each node
Post: Does a breadth first traversal using a queue
Return :
*/

template <typename T>
void BST<T>::breadthFirstTraverse(void(*func)(BinaryNode<T>*)) {
	Queue<BinaryNode<T>*> queue = Queue<BinaryNode<T>*>();
	BinaryNode<T>* temp = root;
	if (isEmpty()) {
		std::cout << "Error Tree is empty\n";
		return;
	}
	queue.enqueue(root);
	while (!queue.isEmpty()) {
		temp = queue.dequeue();
		func(temp);
		if (temp->getLPtr()) {
			queue.enqueue(temp->getLPtr());
		}

		if (temp->getRPtr()) {
			queue.enqueue(temp->getRPtr());
		}
	}
	queue.destroyQueue();
}


/*
Pre: T key: key to remove
Post: calls removeHelper
Return :
*/
template <typename T>
void BST<T>::remove(T key) {
	removeHelper(key, root);
	updateAverageDeletion();
}

/*
Pre: T key - key to remove
	 BinaryNode<T>* parent - parent node
Post: Traverses down the tree until it finds the node that matches the key
	  Calls removeNodeHelper to remove the key and properly relink the tree
Return :
*/
template <typename T>
void BST<T>::removeHelper(T key, BinaryNode<T>* parent) {
	if (!isEmpty()) {
		if (root->getKey() == key) {
			removeRoot();
			delComparisons += 3;
		}
		else {
			if (key < parent->getKey() && parent->hasLeft()) {
				if ((parent->getLPtr())->getKey() == key) {
					removeNodeHelper(parent, parent->getLPtr(), true);
					delComparisons += 6;
				}
				else {
					removeHelper(key, parent->getLPtr());
					delComparisons += 6;
				}
			}
			else if (key > parent->getKey() && parent->hasRight()) {
				if ((parent->getRPtr())->getKey() == key) {
					removeNodeHelper(parent, parent->getRPtr(), false);
					delComparisons += 8;
				}
				else {
					removeHelper(key, parent->getRPtr());
					delComparisons += 8;
				}
			}
			else {
				std::cout << "The Key " << key << "was not found\n";
				delComparisons += 7;
			}
		}
	}
	else {
		std::cout << "The Tree is Empty\n";
		delComparisons += 1;
	}
}

/*
Pre: BinaryNode<T>* parent - parent node
	 BinaryNode<T>* del - node to be deleted
	 bool isLeft - boolean to determine whether del is the left or right
				   child of parent
Post: Determines whether del has 0 1 or 2 children
	  Removes the node and relinks the tree to keep a valid Binary Search Tree
Return:

*/
template <typename T>
void BST<T>::removeNodeHelper(BinaryNode<T>* parent, BinaryNode<T>* del, bool isLeft) {
	if (!isEmpty()) {
		BinaryNode<T>* delPtr;
		T delKey = del->getKey();
		T smallRight;

		// del has zero children
		if (del->isLeaf()) {
			delPtr = del;
			if (isLeft)
				parent->setLPtr(nullptr);
			else
				parent->setRPtr(nullptr);
			delete delPtr;
			delComparisons += 6;
		}
		//del has one child
		else if (del->getLPtr() == nullptr && del->hasRight()) {
			if (isLeft)
				parent->setLPtr(del->getRPtr());
			else
				parent->setRPtr(del->getRPtr());
			del->setRPtr(nullptr);
			delPtr = del;
			delete delPtr;
			delComparisons += 10;
		}
		else if (del->getRPtr() == nullptr && del->hasLeft()) {
			if (isLeft)
				parent->setLPtr(del->getLPtr());
			else
				parent->setRPtr(del->getLPtr());
			del->setLPtr(nullptr);
			delPtr = del;
			delete delPtr;
			delComparisons += 12;
		}
		// del has two children
		else {
			smallRight = findSmallestHelper(del->getRPtr());
			removeHelper(smallRight, del);
			del->getKey() = smallRight;
			delComparisons += 10;
		}
	}
	else {
		std::cout << "Error Tree is Empty\n";
		delComparisons += 2;
	}
}

/*
Pre:
Post: Determines whether the root has 0 1 or 2 children
	  Removes the root and relinks the tree to keep a valid Binary Search Tree
Return:
*/
	template <typename T>
	void BST<T>::removeRoot() {
		if (!isEmpty()) {
			BinaryNode<T>* delPtr = root;			//
			T rootKey = root->getKey();				//attribute 1 of root
			T smallRight;							//smallest value in the right subtree 

			//0 children
			if (root->isLeaf()) {
				root = nullptr;
				delete delPtr;
				delComparisons += 5;
			}
			//1 child
			else if (root->getLPtr() == nullptr && root->hasRight()) {
				root = root->getRPtr();
				delete delPtr;
				delComparisons += 7;
			}
			else if (root->getRPtr() == nullptr && root->hasLeft()) {
				root = root->getLPtr();
				delete delPtr;
				delComparisons += 9;
			}
			//2 children
			else {
				smallRight = findSmallestHelper(root->getRPtr());
				removeHelper(smallRight, root);
				root->setKey(smallRight);
				delComparisons += 10;
			}
		}
		else {
			std::cout << "Error Tree is Empty\n";
			delComparisons += 3;
		}
	}

/*
Pre:
Post: calls findSmallestHelper(root)
Return: Key value of the smallest Node
*/
template<typename T>
T BST<T>::findSmallest() {
	return findSmallestHelper(root);
}

/*
Pre: BinaryNode<T>* r - root of a subtree
Post: traverses left down the tree until lPtr is null
Return: Key value of the smallest node
*/
template<typename T>
T BST<T>::findSmallestHelper(BinaryNode<T>* r) {
	if (isEmpty()) {
		std::cout << "Error Tree is Empty\n";
		delComparisons += 1;
	}
	else {
		if (r->hasLeft()) {
			return findSmallestHelper(r->getLPtr());
			delComparisons += 3;
		}
		else {
			return r->getKey();
			delComparisons += 3;
		}
	}
}


/*
Pre: BinaryNode<T>* r - root of a subtree
Post: Calls the printIndentedHelper(root, 0 , 2)
	 0 means the default starting position(leftmost on the screen)
	 2 means the number of \t printed between each key
Return:
*/
template <typename T>
void BST<T>::printIndented() {
	printIndentedHelper(root, 0, 2);
}

/*
Pre: BinaryNode<T>* r - root of a subtree
	 int spacing - variable to hold current spacing location to print to
	 int defaultSpacing - default space between names in terms of tabs
Post: Traverses through the tree using a right - root - left algorithm
	  prints the proper amount of spacing and the key
Return:
*/
template <typename T>
void BST<T>::printIndentedHelper(BinaryNode<T>* r, int spacing, int defaultSpacing) {
	if (r == nullptr) {
		return;
	}
		spacing += defaultSpacing;
		if (r->hasRight()) {
			printIndentedHelper(r->getRPtr(), spacing, defaultSpacing);
		}
		std::cout << "\n";
		for (int i = defaultSpacing; i < spacing; i++)
			std::cout << "\t";
		std::cout<< r->getKey();
		if (r->hasLeft()) {
			printIndentedHelper(r->getLPtr(), spacing, defaultSpacing);
		}
}

/*
Pre:
Post: Recomputes the average amount of comparisons with a new comparison amount
	  Adds new comparison amount to toal comparisons
	  Resets comparison amount to 0
Return :
*/
template <typename T>
void BST<T>::updateAverageInsert() {
	if (averageInsertComparisons == 0)
		averageInsertComparisons = insertComparisons;
	else {
		averageInsertComparisons = (averageInsertComparisons + insertComparisons) / 2;
	}
	totalInsertComparisons += insertComparisons;
	insertComparisons = 0;
}

/*
Pre:
Post: Recomputes the average amount of comparisons with a new comparison amount
	  Adds new comparison amount to toal comparisons
	  Resets comparison amount to 0
Return : 
*/
template <typename T>
void BST<T>::updateAverageDeletion() {
	if (averageDelComparisons == 0)
		averageDelComparisons = delComparisons;
	else
		averageDelComparisons = (averageDelComparisons + delComparisons) / 2; 
	totalDelComparisons += delComparisons;
	delComparisons = 0;
}