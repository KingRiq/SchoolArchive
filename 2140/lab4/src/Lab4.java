
/**********************************************
 *  COMP 2140   Lab 4  Winter 2020
 *
 *  Simulating a simple survivor game with a queue.
 *
 *  N people (numbered 0 to N-1) stand in  circle, 
 *  then every k-th person is counted out (leaves 
 *  the circle), until only one person is left.
 *  
 *  Student name:
 *  Student id:
 * 
 **********************************************/
public class Lab4
{

  // The main method simply tests the survivor method with several sets of parameters.
  public static void main( String[] args )
  {
    System.out.println( "\n\nCOMP 2140 Lab 4   Fall 2015\n" );

    survivor( 7, 2 );

    System.out.println( "\n" );

    survivor( 11, 3 );

    System.out.println( "\n" );

    survivor( 17, 5 );
    
   // survivor( 100000, 30 );

    System.out.println( "\n" );


    System.out.println( "\n\nProgram ends normally.\n" );
  } // end main

  // Simulates the survivor game using a queue for the circle of people.
  public static void survivor( int numPeople, int k )
  {
    Queue circle;
    int person;

    if ( numPeople > 0 && k > 1 )
    {
      System.out.print( numPeople + " people numbered 0 to " + (numPeople-1) + " stand in a circle.\nEvery " );
      if ( k == 2 )
        System.out.print( "second" );
      else if ( k == 3 )
        System.out.print( "third" );
      else
        System.out.print( k + "-th" );
      System.out.println( " person is eliminated repeatedly until only one person is left." );
      System.out.print( "The people are eliminated in the following order:\n     " );
      
      // Set up queue: add people 0 to numPeople-1
      circle = new Queue();
      for ( int i = 0; i < numPeople; i++ )
        circle.enter( i );

      // Now play the game: eliminate every k-th person until empty
 
      while(!circle.isEmpty())
      {
    	  for(int j = 1; j < k; j++)
    	  {
    		  int item = circle.front();
    		  circle.leave();
    		  circle.enter(item);
    	  }
    	  int item = circle.leave();
    	  System.out.print(item+ " ");
    	  
      }
      System.out.println("<=== last person left");   
     
    } // end if at least one person    
  }

}

// A queue implemented as a circular linked list with a last pointer.

class Queue
{
  private class Node
  {
    public int item;
    public Node next;

    public Node( int i, Node n )
    {
      item = i;
      next = n;
    }
  }

  private Node last;  // a pointer to the last node in the circular linked list

  public Queue()
  {
    last = null; // create an empty queue
  }

  public void enter( int newItem )
  {
    if ( last == null )  // add a node to an empty list
    {
      last = new Node( newItem, null );
      last.next = last; // the only node points at itself
    }
    else
    {
      last.next = new Node( newItem, last.next ); // the new node points at the first node
      last = last.next; // the new node is the last node (enter at the end of the queue)
    }
  } // end enter

  public int leave( )
  {
    int result = Integer.MIN_VALUE;

    if ( last != null )  // queue isn't empty
    {
      result = last.next.item; // return the first nodes's item
      if (last.next != last) // more than one item in the queue
      {
        last.next = last.next.next; // remove the first node
      }
      else // only one item in the queue --- it becomes empty
      {
        last = null;
      }
    }
    return result;
  } // end leave

  // Peek at the item at the front of the queue without changing the queue.
  public int front()
  {
    int result = Integer.MIN_VALUE;

    if ( last != null )  // queue isn't empty
    {
      result = last.next.item; // return the first nodes's item
    }
    return result;
  } // end front

  public boolean isEmpty()
  {
    return last == null;
  }

} // end class Queue
