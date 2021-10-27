//
// PURPOSE: This file implements a runtime exception thrown by the class
// MyStack when attempting to perform the operations top or
// pop on an empty stack.
//
// This code is based on code written by Michael T. Goodrich 
// and Roberto Tamassia for the textbook Data Structures and Algorithms 
// in Java (4th edition). 
// The original code can be found at java.datastructures.net

public class EmptyStackQueueException extends RuntimeException {  

	// CONSTRUCTOR
	public EmptyStackQueueException(String err) {
		super(err);
	}
}

