// PURPOSE: This file implements a stack using the generic type <E>.
//

public class MyStack<E> {

	// INSTANCE VARIABLES
  
	protected Node<E> top;		// reference to the first linked
    					// list, corresponding to the top of the
					// stack.
	protected int numItems;		// number of elements in the stack

	// CONSTRUCTOR

	public MyStack() { 
		top = null;
		numItems = 0;
	}

	// ACCESSOR METHODS
   
	// METHOD: isEmpty
	// PURPOSE: Return true if the stack is empty.
	public boolean isEmpty() { 
		return (top == null);
	}
    
	// METHOD: top
	// PURPOSE: Return the element at the top of the stack.
	public E top() throws EmptyStackQueueException {
		E result = null;

		if (isEmpty()) 
			throw new EmptyStackQueueException("Stack is empty.");
		else
			result = top.getValue();

		return result;
	}

	// ACTION METHODS

	// METHOD: push
	// PURPOSE: Add elem to the top of the stack.
	public void push(E elem) {
		top = new Node<E>(elem, top);	
		// create a new node and add it to the front of the list
		numItems++;
	}

	// METHOD: pop
	// PURPOSE: Return the element at the top of the stack and remove
	// it from the stack.
	public E pop() /*throws EmptyStackQueueException*/ {
		E result = null;

		if (isEmpty()) 
			throw new EmptyStackQueueException("Stack is empty.");
			
		else {
			result = top.getValue();
			top = top.getNext();	// set top to second item
			numItems--;
		}

		return result;
	}

	// METHOD: print
	// PURPOSE: Print the contents of the stack if its elements are 
	// printable.
	public void print() {
		Node<E> pointer = top;
		int depth = 0;

		if (pointer == null) 
			System.out.println("stack is empty");
		else {
			System.out.println("top of stack");

			while (pointer != null) {
				System.out.println("element at depth " + depth 
					+ ": " + pointer.getValue());

				pointer = pointer.getNext();	// get next list element
				depth++;			// increment depth counter
			}

			System.out.println("bottom of stack\n");
		}
	}

	// METHOD: clearStack
	// PURPOSE: Remove all elements from the stack.
	public void clearStack() {
		top = null;
		numItems = 0;
	}

	// METHOD: size
	// PURPOSE: Return the number of elements in the stack or 0 if
	// the stack is empty.
	public int size() {
		return numItems;
	}

	// METHOD: toString
	// PURPOSE: Return the contents of the stack as a String.
	public String toString() {
		Node<E> pointer = top;
		String result = "";

		while (pointer != null) {
		    result += pointer.getValue();
		    pointer = pointer.getNext();	// get next list element
		}

		return result;
	}
}


