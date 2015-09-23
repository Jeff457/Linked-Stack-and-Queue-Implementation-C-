/*****************************************
	Jeff Stanton
	CS M20 Topic B Project

	LinkedQueue.h
	Status: Extra Credit
*****************************************/

#ifndef _LINKED_QUEUE
#define _LINKED_QUEUE

#include "Node.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class LinkedQueue
{
	// Overloaded stream insertion operator
	template<class ItemType>
	friend std::ostream &operator<<(std::ostream& out, LinkedQueue<ItemType>& aQueue);

private:
	// The queue is implemented as a chain of linked nodes that has 
	// two external pointers, a head pointer for front of the queue and
	// a tail pointer for the back of the queue.
	Node<ItemType>* backPtr;
	Node<ItemType>* frontPtr;

public:
	LinkedQueue() : frontPtr(nullptr), backPtr(nullptr) {};
	LinkedQueue(const LinkedQueue& aQueue);
	LinkedQueue<ItemType> &operator=(const LinkedQueue<ItemType>& aQueue);
	~LinkedQueue();

	// Queue operations
	bool isEmpty() const;
	bool enqueue(const ItemType& newEntry);
	bool dequeue();

	/** @throw PrecondViolatedExcep if the queue is empty */
	ItemType peekFront() const throw(PrecondViolatedExcep);
}; // end LinkedQueue


template<class ItemType>
ostream &operator<<(ostream& out, LinkedQueue<ItemType>& aQueue)
{
	while (!aQueue.isEmpty())
	{
		out << aQueue.peekFront() << endl;
		aQueue.dequeue();
	}
	return out;
} // end overloaded insertion operator

template<class ItemType>
inline LinkedQueue<ItemType>::LinkedQueue(const LinkedQueue & aQueue) : frontPtr(nullptr), backPtr(nullptr)
{
	*this = aQueue;
} // end copy constructor

template<class ItemType>
inline LinkedQueue<ItemType>& LinkedQueue<ItemType>::operator=(const LinkedQueue<ItemType>& aQueue)
{
	if (this == &aQueue)
		return *this;
	while (!this->isEmpty())
		this->dequeue();

	if (aQueue.isEmpty())
	{
		frontPtr = nullptr;
		backPtr = nullptr;
	}
	else
	{
		Node<ItemType>* newNode = aQueue.frontPtr;
		while (newNode != nullptr)
		{
			enqueue(newNode->getItem());
			newNode = newNode->getNext();
		}
	}

	return *this;
		
} // end overloaded assignment operator

template<class ItemType>
inline LinkedQueue<ItemType>::~LinkedQueue()
{
	while (!isEmpty())
		dequeue();
} // end destructor

template<class ItemType>
inline bool LinkedQueue<ItemType>::isEmpty() const
{
	return frontPtr == nullptr;
} // end isEmpty

template<class ItemType>
bool LinkedQueue<ItemType>::enqueue(const ItemType& newEntry)
{
	Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);

	// Insert the new node
	if (isEmpty())
		frontPtr = newNodePtr;        // Insertion into empty queue
	else
		backPtr->setNext(newNodePtr); // Insertion into nonempty queue

	backPtr = newNodePtr;            // New node is at back

	return true;
}  // end enqueue

template<class ItemType>
bool LinkedQueue<ItemType>::dequeue()
{
	bool result = false;
	if (!isEmpty())
	{
		// Queue is not empty; delete front
		Node<ItemType>* nodeToDeletePtr = frontPtr;
		if (frontPtr == backPtr)
		{  // Special case: one node in queue
			frontPtr = nullptr;
			backPtr = nullptr;
		}
		else
			frontPtr = frontPtr->getNext();

		// Return deleted node to system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		result = true;
	}  // end if

	return result;
}  // end dequeue

template<class ItemType>
inline ItemType LinkedQueue<ItemType>::peekFront() const throw(PrecondViolatedExcep)
{
	if (isEmpty())  // Enforce precondition
	{
		string message = "peekFront - Queue empty\n";
		throw(PrecondViolatedExcep(message));
	}
	else  // Stack is not empty, return front of queue
		return frontPtr->getItem();
} // end peekFront

#endif