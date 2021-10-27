// COMP 2140 SECTION A01
//
// PURPOSE: This file implements one node in a linked list. Each node stores
// an item of generic type <E> and a reference to the next node in the list.
//

public class Node<E> {
	protected E value;		// value stored at this node
	protected Node<E> next;		// reference to the next list node

	// CONSTRUCTORS

	public Node(E newValue, Node<E> newNext) {
		value = newValue;
		next = newNext;
	}

	public Node(E newValue) { 
		this(newValue, null); 
	}

	// ACCESSOR METHODS

	// METHOD: getValue
	// PURPOSE: Return the value stored in this node.
	public E getValue() { 
		return value;
	}

	// METHOD: getNext
	// PURPOSE: Return the reference to the next node.
	public Node<E> getNext() { 
		return next; 
	}

	// ACTION METHODS

	// METHOD: setValue
	// PURPOSE: Update the value stored at this node.
	public void setValue(E newValue) { 
		value = newValue; 
	}

	// METHOD: setNext
	// PURPOSE: Update the reference to the next node.
	public void setNext(Node<E> newNext) { 
		next = newNext; 
	}

}

