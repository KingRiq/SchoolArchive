// COMP 2140 SECTION A01
// Assignment 3
// Eriq Hampton, 7852830
// March 6th, 2020
//
// PURPOSE: This file shows an example of how to use the class MyQueue.
//

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class A3HamptonEriq {

	public static void main(String [] args) {



		MyQueue<Integer> q = new MyQueue<Integer>();

		int testSize = 5;

		for (int i = 0 ; i < testSize ; i++) {
			q.enqueue(new Integer(i));
			System.out.println("enqueued " + i);
		}

		for (int i = 0 ; i < testSize/2 ; i++) {
			System.out.println("dequeued " + q.dequeue());
		}

		for (int i = testSize ; i < 2*testSize ; i++) {
			q.enqueue(new Integer(i));
			System.out.println("enqueued " + i);
		}

		while(!q.isEmpty()) {
			System.out.println("dequeued " + q.dequeue());
		}
		//CORE JAVA: Collections
		//2 - ArrayLists
		List<String> store1 = new ArrayList<>();
		store1.add("https://www.amazon.ca/Coders-Work-Reflections-Craft-Programming/dp/1430219483");// interviews of famous coders
		store1.add("https://www.amazon.ca/Code-Complete-2nd-Steve-McConnell/dp/0735619670/"); // thick book about all you need to know about ADT
		store1.add("https://www.amazon.ca/Mythical-Man-Month-Software-Engineering-Anniversary/dp/0201835959");//Software development bible
		store1.add("https://www.amazon.ca/Clean-Code-Handbook-Software-Craftsmanship/dp/0132350882");//Advanced software practises
		store1.add("https://www.amazon.ca/Computer-Programming-Volumes-1-4A-Boxed/dp/0321751043/");//bible of computer science.
		// Solving the questions of the first volume will get you a job in any country, any company.

		//2a- search the ArrayList class to find the function that can be used to get the element at a given index.
		int index =2;
		String book = store1.get(index);
		System.out.println("Book is retrieved: "+(book.contains("Mythical")));
		//2b- search the ArrayList class to find a way (more than 1 way exist) to add all books in store1 to store2 with a single line of code.
		List store2 = new ArrayList<String>();
		store2.addAll(store1);
		System.out.println("Books are copied:"+(!store2.isEmpty()&&store2.size()==store1.size()));

		List store3 = new LinkedList<String>();
		LinkedList<String> store4 = new LinkedList<String>();

		//related to 2d
		String book2 = store4.peek();//possible
		// but this is not:
		//store3.peek();

		//related to 2e
		//we can change store1 to linkedlist
		store1 = new LinkedList<>();
		//but we cannot change store 4 to an arraylist
		//will not compile: store4 = new ArrayList<String>();
	}
}

//********************************************
//Report
// 
// 2C) The difference between an Arraylist and Linkedlist is that ArrayLists create a new array dynamically 
// to handle the size changes from insertions and deletion of items, this causes them to run slower while 
// LinkedList utilizes more space for the sake of speed, each node has memory for data and pointers.
//
// 2D) store3 uses the List interface and store4 uses LinkedList which implements the list interface.
// It can use many of the functionalities from both interfaces such as peek or clone
// which store3 cannot use.
//
// 2E)Store 3 uses the List interface which is the parent of the LinkedList. This means that lists will not inherit 
// the functionality of its child classes such as the LinkedList or ArrayList. Store4 is an LinkedList which is the child
// of the List and Queue interface. The big advantage is the speed of insertion and deletion of items. The disadvantage
// is that you must search sequentially while for Lists, items can be accessed arbitrarily.
//