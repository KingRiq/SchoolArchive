
import java.util.*;

/**
 * COMP 2140   SECTION A01
 * INSTRUCTOR    Cuneyt Akcora
 * Assignment           2
 * @author       Eriq Hampton
 * @version      02/20/20
 *
 * PURPOSE: To implement Link list merge, fix and conversion methods.
 */

/******************************************
 *
 * LinkedList: A circular (singly-linked)
 * list with a last pointer and the number
 * of nodes.
 *
 ******************************************/

public class LinkedList
{
    public class Node
    {
        public int item;
        public Node next;

        public Node( int newItem, Node newNext )
        {
            item = newItem;
            next = newNext;
        }
    }


    private Node last;
    private int nodeCount;
    private static Random generator = new Random(System.nanoTime());

    public LinkedList()
    {
        last = null;
        nodeCount = 0;
    }

    public int getSize()
    {
        return nodeCount;
    }

    /*******************************************
     *
     *  insertNode: Insert a given node, newNode,
     *  into the list.  Since the list is
     *  unordered and inserting at the front of
     *  the list is easiest, we'll insert there.
     *
     *  Only special case: If the list is empty.
     *
     ********************************************/
    private void insertNode( Node newNode )
    {
        if ( nodeCount == 0 )
        {
            newNode.next = newNode;
            last = newNode;
        }
        else
        {
            newNode.next = last.next;
            last.next = newNode;
        }
        nodeCount++;
    }


     /*******************************************
     *
     *  insertValue: Insert a given item, newItem,
     *  into the list.  Since the list is
     *  unordered and inserting at the front of
     *  the list is easiest, we'll insert there.
     *
     *  Only special case: If the list is empty.
     *
     ********************************************/
    void insertValue(int newItem)
    {
        Node newNode = new Node( newItem, null );
        if ( nodeCount == 0 )
        {
            newNode.next = newNode;
            last = newNode;
        }
        else
        {
            newNode.next = last.next;
            last.next = newNode;
        }
        nodeCount++;
    }
    
    
    /*****************************************************************************
    / corrupt: expects an ordinary linked list with a null pointer in the last node.
    / The latest inserted node sits at index 0.
    / Take the last node in the linked list and change its pointer to the node at the given index.
    / return the value of the corruption index.
    /*****************************************************************************/
    public int corrupt(int index) 
    {
    	int valOfCorruptedNode=Integer.MIN_VALUE;
        Node prev, curr;
        prev = last;
        curr = last;
        
        //first find null pointer
        while(curr.next != null)
        	curr=curr.next;
        
        //advance prev to index
        for(int i = 0; i < index; i++)
        {
        	prev=prev.next;
        }
        
        //corrupt that null pointer
        curr.next= prev;
        valOfCorruptedNode= curr.next.item;
        return valOfCorruptedNode;
    }//end of corrupt

    /******************************************************
    / findCorruption: find if the linked list contains a loop.
    / Corruption is defined as the last node not having a null pointer, but instead pointing to a node in the linked
    / list as its forward node. A circular link is due to a corruption.
    / Do not use the sorted order of the linked list to detect the corruption.
    / A popular interview question, the solution to this question is known as the Floyd’s Cycle-Finding Algorithm.
    / A more difficult version would ask the index/value of the corruption.
    /******************************************************/
    public boolean findCorruption() 
    {
    	
    	//uses floyd's cycle finding algorithm
    	boolean p = false;
    	Node prev, curr; //prev is the slower pointer
    	prev = last;
    	curr = last;
    	
    	
    	while(prev != null && p == false && curr!= null)
    	{
    		
    		if(curr != null)
    		{ 
    			curr = curr.next;
    		}
    		if(curr != null)
    		{
    			curr = curr.next;
    			prev = prev.next;
    		}
    		if(curr == prev)
    			p = true;
    	}

        return p;
    }//end of findCorruption
    
    /***********************************************
    / reset: Remove every node from the linked list. 
    /Do not forget the nodeCount variable.
    /**********************************************/
    public void reset() 
    {
    	last = null;
    	nodeCount = 0;
    }// end of reset

    /**********************
    / deleteOddNodes: delete nodes that have an odd item value.
    / Reassign pointers. Do not create a new linked list.
    /**********************/
    public void deleteOddNodes() 
    {
    	Node prev, curr;
    	prev =last; // node before last.next
    	curr =last.next; //top
    		
    		while(curr !=null) 
    		{
    			if(curr.item%2 != 0) //if odd
    			{
    				//delete nodes
    				prev.next = curr.next;
    				curr = curr.next;
    				nodeCount--;	
    			}
    			else //not odd
    			{
    			prev= prev.next;
    			curr= curr.next;
    			}
    		}
    	
    }//end of deleteOddNodes
    
    /***********************************
    / hasDummies: checks if the linked list has 1) 
    / a dummy header with Integer.MIN_VALUE
    / and a dummy trailer with  Integer.MAX_VALUE.
    /**********************************/

    public boolean hasDummies() 
    {
    	boolean p = false;
    	Node curr = last.next;
    	
    	while(curr.next !=null)	  		
    		curr = curr.next;
    
    	if(last.item == Integer.MIN_VALUE && curr.item == Integer.MAX_VALUE)
			p = true;
       
        return p;
    }//end of hasDummies
    
    /****************************************
    / isOrdinary: checks the type of this list.
    / If the list is in a given type, it returns true, otherwise false.
    / if the list empty, return false.
    /Use the nodecount variable to detect the end
    /***************************************/
    public boolean isOrdinary() 
    {
    	Node curr = last.next;
    	
    	//first assume every list passed is circular
    	boolean p = false;

    	//by definition an empty list is a null at the top but .next should also be null by default
    	// last.next shouldnt point to last in this case
    	if(last.next == null && last.next != last)
    		p= true;
    	else
    		curr =curr.next;
    		while(curr != null && curr != last)
    		{
    			 curr= curr.next;
    			if(curr == null)
    			{
    				p = true;
    			}
    		}
        return p;
    }//end of isOrdinary
   
   /****************************************
   /isCircular: checks the type of this list.
   /If the list is circular, it returns true, otherwise false.
   /if the list empty, return false.
   /Use the nodeCount variable to detect the end
   /***************************************/
    public boolean isCircular() 
    {
        Node curr = last.next;
    	boolean p = false;
    	
    	//if last is null the list is empty and points to last it is circular by definition.
    	if(last == null && last.next == last)
    		p= true;
    	
    	//list is not empty, proceed to check every node for null
    	else 
    	{
    		curr = curr.next;
    		
    		//if curr hits null it is ordinary, if curr = last then we have returned to the beginning
    		while(curr != null && curr != last.next) 
    		{
    			curr=curr.next;
    			if(curr == last.next)
    				p = true;
    		}	
        	
    	}
        return p;
    }//end of isCircular
   
    
    /********************************************
    / addDummies: add a dummy header and a dummy trailer to the linked list.
    / Use Integer.MIN_VALUE and Integer.MAX_VALUE
    /*******************************************/
    public void addDummies() 
    {
    	Node curr;
    	curr= last;
    	Node headerNode = new Node(Integer.MIN_VALUE, last.next ); //first dummy is added
    	last = headerNode;
    	
    	while(curr.next != null)
    		curr=curr.next;

    	Node trailerNode = new Node(Integer.MAX_VALUE, null);
    	curr.next = trailerNode;
    	
    }//end of addDummies
    
    /***********************************************
     *
     * convertCircularToOrdinary:  Convert the list to an ordinary
     * linked list (a single linked list without dummy header or trailer).
     * use the existing last pointer and rewrite
     * its address to point to the first node. Update the last node's forward pointer as well.
     * This linked list class is originally written for a circular linked list,
     * DO NOT CHANGE THE ORIGINAL INSERT OR DELETE METHODS.
     ************************************************/
    public void convertCircularToOrdinary() 
    {
    	Node prev =last;
    	last = last.next;
    	prev.next = null;

    }//end of convertCircularToOrdinary

    /***********************************************
     * convertOrdinaryToCircular:  Convert the list to a circular
     * linked list (without a dummy header or trailer).
     ************************************************/
    public void convertOrdinaryToCircular() 
    {
    	Node prev, curr;
    	prev = last;
    	curr = last.next;
    	if(prev != null)
    	{		
    		while(curr.next != null)  	  
    	    	curr=curr.next;

    		last = curr;
    	    last.next = prev;
    	    	
    	}
    }//end of convertOrdinaryToCircular


    /***********************************************
     *
     * add:  Take the values in the parameter list2
     * and insert them into this list in an order-preserving manner (keep the order as it is in list1).
     * The list2 should not change. Both lists are circular single linked lists (no dummies)
     *
     ************************************************/
    public void add(LinkedList list2) 
    {
    	Node curr, prev;
    	curr= last.next;
    	prev = last;
    	Node curr2 = list2.last.next;
    	int size= list2.getSize() + nodeCount;
    	
    	while(nodeCount < size) //note if we get to the end of list2 we are done
    	{
    		if(curr2.item <= curr.item)
    		{	
    			Node addNode = new Node (curr2.item, null);
    			prev.next = addNode;
    			addNode.next = curr;
    			prev = prev.next;
    			curr2= curr2.next;
    			nodeCount++;
    		}
    		else 
    		{
    			prev= prev.next;
    			curr= curr.next;
    		}
    		
    	}

    }//end of add 


    /***********************************************
     *
     *  choosePivot:  Randomly choose a pivot from
     *  the list, unlink it from the list and return
     *  a pointer to it.
     *
     *  Assuming that the first node (last.next) is
     *  in position 0 and the last node is in
     *  position nodeCount-1, choose a random
     *  number, randomIndex, in the range 0 to
     *  nodeCount-1, and unlink the node in position
     *  randomIndex to be the pivot.
     *
     ************************************************/

    private Node choosePivot()
    {
        int randomIndex = generator.nextInt( nodeCount );
        Node prev = last;
        Node pivot;
        int i;

        // Find the node before the pivot
        for ( i = 0; i <= randomIndex; i++ )
            prev = prev.next;

        pivot = prev.next;
        if ( last == pivot )
            last = prev;
        prev.next = pivot.next;
        nodeCount--;

        return pivot;
    } // end choosePivot


    /*******************************************
     *
     *  partition: Given a node, pivot (not in the
     *  list), leave all the nodes containing items
     *  >= the pivot's item in the list and move
     *  all nodes containing items < the pivot's item
     *  into a new LinkedList.  That is, at the end,
     *  the bigs remain in the list and the smalls
     *  are moved into a new list (which is returned).
     *
     *  Create two LinkedLists smalls and bigs.
     *  Move each node in the calling LinkedList
     *  into the smalls or the bigs list (compare
     *  each node's item to pivot.item and then
     *  unlink it from the calling list and
     *  use method insertNode() to put it into
     *  the smalls or bigs).
     *
     *  No Nodes should be created or destroyed by
     *  this method, and no item in a Node should
     *  be changed by this method.  This method
     *  simply unlinks and links existing nodes.
     *
     *********************************************/

    public LinkedList partition( Node pivot )
    {
        Node curr;
        LinkedList smalls = new LinkedList();
        LinkedList bigs = new LinkedList();
        int size = nodeCount;
        int i;

        for ( i = 0; i < size; i++ )
        {
            curr = last.next;
            last.next = last.next.next;
            nodeCount--;
            if ( curr.item < pivot.item )
            {
                // curr belongs in the smalls

                smalls.insertNode( curr );
            }
            else
            {
                // curr belongs in the bigs.

                bigs.insertNode( curr );
            }
        }
        last = bigs.last;
        nodeCount = bigs.nodeCount;

        return smalls;
    } // end partition

    /***********************************************
     *
     *  rejoin: Given the sorted smalls list and
     *  a pointer to the pivot, relink into the
     *  sorted list (which contains the sorted bigs)
     *  into the correct positions.
     *
     ************************************************/

    private void rejoin( LinkedList smalls, Node pivot )
    {
        Node firstBig;

        smalls.insertNode( pivot ); // insert pivot at front
        smalls.last = smalls.last.next; // pivot should be last node
        if ( nodeCount != 0 )
        {
            // There are some bigs.

            firstBig = this.last.next;
            this.last.next = smalls.last.next;
            pivot.next = firstBig;
            nodeCount = nodeCount + smalls.nodeCount;
        }
        else
        {
            // There are no bigs.

            this.last = smalls.last;
            nodeCount = smalls.nodeCount;
        }

    } // end rejoin

    /***********************************
     *
     * quickSort: Recursively quick sort a
     *    a circular linked list with no
     *    dummy nodes.
     *
     *   (Since the partition method
     *   puts the smalls into a new
     *   circular linked list, after the
     *   recursive calls, the smalls must
     *   be joined back into the list.)
     *
     **************************************/
    public void quickSort( )
    {
        Node pivot;
        LinkedList smalls;

        if ( nodeCount > 2 )
        {
            pivot = choosePivot(); // removes a pivot
            smalls = partition( pivot ); // bigs in original list
            smalls.quickSort(  );
            quickSort( ); // recursively quick sort the bigs
            rejoin( smalls, pivot ); // rejoin into one circular list
        }
        if ( nodeCount == 2 )
        {
            if ( last.item < last.next.item )
            {
                // swap them: first becomes last
                last = last.next;
            }
        }
        // else do nothing for nodeCount 0 or 1
    } // end quickSort

    /***********************************
     *
     * isSorted: Returns true if the list
     *  is sorted, false otherwise.
     *
     **************************************/

    public boolean isSorted()
    {
        boolean sorted = true;
        Node curr = last.next;

        if ( nodeCount > 1 )
        {
            do
            {
                if ( curr.next.item < curr.item )
                    sorted = false;
                curr = curr.next;
            } while ( ( curr  != last ) && sorted );
        }

        return sorted;
    } // end isSorted

    /***********************************
     *
     * printList: print out all the items
     *  in a list (for debugging purposes)
     *
     **************************************/

    public void printList()
    {
        Node curr;
        int i = 0;
        if (nodeCount > 0)
        {
            curr = last.next;
            do
            {
            	System.out.print(i+ " =");
                System.out.println(curr.item );
                curr = curr.next;
                i++;
            } while ( curr != null && curr != last.next );
        }
    } // end printList




} // end class LinkedList