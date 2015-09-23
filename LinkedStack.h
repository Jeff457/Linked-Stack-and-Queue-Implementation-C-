/*****************************************
	Jeff Stanton
	CS M20 Topic B Project

	LinkedStack.h
	Status: Extra Credit
*****************************************/

#ifndef _LINKED_STACK
#define _LINKED_STACK

#include "Node.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class LinkedStack
{
	// Overload stream insertion operator
	template<class ItemType>
	friend std::ostream &operator<<(std::ostream& out, LinkedStack<ItemType>& aStack);

private:
	Node<ItemType>* topPtr; // Pointer to first node in the chain;
							// this node contains the stack's top

public:
	// Constructors and destructor:
	LinkedStack();                                   // Default constructor
	LinkedStack(const LinkedStack<ItemType>& aStack);// Copy constructor 
	LinkedStack<ItemType> &operator=(const LinkedStack<ItemType>& aStack);  // Overloaded assignment operator
	virtual ~LinkedStack();                          // Destructor

	// Stack operations:
	bool isEmpty() const;
	bool push(const ItemType& newItem);
	bool pop();

	/** @throw PrecondViolatedExcep if the stack is empty */
	ItemType peek() const throw (PrecondViolatedExcep);
}; // end LinkedStack


template<class ItemType>
ostream &operator<<(ostream& out, LinkedStack<ItemType>& aStack)
{
	while (!aStack.isEmpty())
	{
		out << aStack.peek() << " ";
		aStack.pop();
	}
	return out;
} // end overloaded insertion operator

template<class ItemType>
LinkedStack<ItemType>::LinkedStack() : topPtr(nullptr)
{
}  // end default constructor

template<class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack) : topPtr(nullptr)
{
	*this = aStack;
}  // end copy constructor

template<class ItemType>
inline LinkedStack<ItemType>& LinkedStack<ItemType>::operator=(const LinkedStack<ItemType>& aStack)
{
	// Point to nodes in original chain
	Node<ItemType>* origChainPtr = aStack.topPtr;

	if (this == &aStack)
		return *this;
	while (!this->isEmpty())
		this->pop();

	if (origChainPtr == nullptr)
		topPtr = nullptr;  // Original stack is empty
	else
	{
		// Copy first node
		topPtr = new Node<ItemType>();
		topPtr->setItem(origChainPtr->getItem());

		// Point to last node in new chain
		Node<ItemType>* newChainPtr = topPtr;

		// Advance original-chain pointer
		origChainPtr = origChainPtr->getNext();

		// Copy remaining nodes
		while (origChainPtr != nullptr)
		{
			// Get next item from original chain
			ItemType nextItem = origChainPtr->getItem();

			// Create a new node containing the next item
			Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

			// Link new node to end of new chain
			newChainPtr->setNext(newNodePtr);

			// Advance pointer to new last node
			newChainPtr = newChainPtr->getNext();

			// Advance original-chain pointer
			origChainPtr = origChainPtr->getNext();
		}  // end while

		newChainPtr->setNext(nullptr);           // Flag end of chain
	} // end else

	return *this;
} // end overloaded assignment operator

template<class ItemType>
LinkedStack<ItemType>::~LinkedStack()
{
	// Pop until stack is empty
	while (!isEmpty())
		pop();
}  // end destructor

template<class ItemType>
bool LinkedStack<ItemType>::isEmpty() const
{
	return topPtr == nullptr;
}  // end isEmpty

template<class ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newItem)
{
	Node<ItemType>* newNodePtr = new Node<ItemType>(newItem, topPtr);
	topPtr = newNodePtr;
	newNodePtr = nullptr;

	return true;
}  // end push

template<class ItemType>
bool LinkedStack<ItemType>::pop()
{
	bool result = false;
	if (!isEmpty())
	{
		// Stack is not empty; delete top
		Node<ItemType>* nodeToDeletePtr = topPtr;
		topPtr = topPtr->getNext();

		// Return deleted node to system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		result = true;
	}  // end if

	return result;
}  // end pop

template<class ItemType>
ItemType LinkedStack<ItemType>::peek() const throw(PrecondViolatedExcep)
{
	if (isEmpty())  // Enforce precondition
	{
		string message = "peek - Stack empty\n";
		throw(PrecondViolatedExcep(message));
	}
	else	// Stack is not empty; return top
		return topPtr->getItem();
}  // end getTop
   // End of implementation

#endif